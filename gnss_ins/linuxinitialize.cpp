/* Copyright 2013-2018 The MathWorks, Inc. */


/* ---------------------------- */
/* RTOS-specific headers        */
/* Note: must be included first */
/* ---------------------------- */
#include "linuxinitialize.h"
#include "rtwtypes.h"
/* ---------------------------- */
/* Required Coder Target header */
/* ---------------------------- */
#include "MW_custom_RTOS_header.h"

#if defined(MW_SOC_ENABLED) && defined(MW_KERNEL_PROFILING_ON)   
#include "kernelprofiler-tp.h"
#endif

#define NAMELEN 16

typedef struct {
    void* (*pAsyncTasks)(void* arg);
    char taskName[NAMELEN];
    int priority;
    int policy;
    int coreSelection;
    int coreNum;
} MW_AsyncTaskCodeGenInfo_Type;


#if (defined(MW_TSKMGR_EVENT_DRIVEN_TASKS) && (MW_TSKMGR_EVENT_DRIVEN_TASKS > 0))
static MW_AsyncTaskCodeGenInfo_Type asyncTaskCodeGenInfo[MW_TSKMGR_EVENT_DRIVEN_TASKS];

void mw_setAsyncTaskCodeGenInfo(void * (*taskHandler)(void *), 
        const char* taskName, int priority, int policy, 
        int coreSelection, int coreNum, int idx)
{
    asyncTaskCodeGenInfo[idx].pAsyncTasks = taskHandler;
    snprintf(asyncTaskCodeGenInfo[idx].taskName, NAMELEN, "%s", taskName);
    asyncTaskCodeGenInfo[idx].priority = priority;
    asyncTaskCodeGenInfo[idx].policy = policy;
    asyncTaskCodeGenInfo[idx].coreSelection = coreSelection;
    asyncTaskCodeGenInfo[idx].coreNum = coreNum;
}
#endif
extern volatile boolean_T runModel;
/* ---------------------------- */
/* RTOS-specific declarations   */
/* ---------------------------- */
typedef struct {
    double period;
} baseRateInfo_t;

pthread_t baseTimerThread;

pthread_attr_t attr;
baseRateInfo_t info;
struct sched_param sp;

/* MW_NUM_SUBRATES is set to 0 if we are in single-tasking mode or number of subrates are 0 */
#define MW_SP_SCHED_FIFO   ((MW_NUMBER_SUBRATES > 0) || !defined(MW_SCHED_OTHER))
#ifdef MW_RTOS_DEBUG
    #define MW_DEBUG_LOG(str)  printf(str); fflush(stdout)
#else
    #define MW_DEBUG_LOG(str)
#endif

#ifdef MW_HAS_COMM_SERVICE
    extern int makeCSTaskIdle();
#endif

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)
    sem_t timerTaskSem[MW_NUMBER_TIMER_DRIVEN_TASKS];
    int timer_fd[MW_NUMBER_TIMER_DRIVEN_TASKS];
    double timer_period[MW_NUMBER_TIMER_DRIVEN_TASKS];
#endif
    
int mw_CreateArmedTimer(double periodInSeconds)
{
    int status;
    int fd;
    struct itimerspec its;

    /* Create the timer */
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1) {
        fprintf(stderr, "Call to timerfd_create failed.\n"); 
        perror("timerfd_create");
        fflush(stderr); 
        exit(EXIT_FAILURE);
    }

    /* Make the timer periodic */
    its.it_value.tv_sec = (time_t)periodInSeconds;
    its.it_value.tv_nsec = (periodInSeconds - (time_t)periodInSeconds) * 1000000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    status = timerfd_settime(fd, 0, &its, NULL);
    CHECK_STATUS(status, 0, "timer_settime");
    
    return fd;
}

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)
void mw_init_timerTaskSem(int idx)
{
    int status;
    status = sem_init(&timerTaskSem[idx], 0, 0);
    CHECK_STATUS(status, 0, "sem_init:mw_init_timerTaskSem");
}

int mw_CreateUnarmedTimer(double periodInSeconds, int idx)
{
    int fd;
    int status;

    /* Create the timer */
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    timer_fd[idx] = fd;
    timer_period[idx] = periodInSeconds;
    if (fd == -1) {
        fprintf(stderr, "Call to timerfd_create failed.\n"); 
        perror("timerfd_create");
        fflush(stderr); 
        exit(EXIT_FAILURE);
    }     
    /* Signal that the timer has been created. */
    status = sem_post(&timerTaskSem[idx]); 
    CHECK_STATUS(status, 0, "sem_post:mw_CreateUnarmedTimer");     
    #ifdef MW_RTOS_DEBUG
        printf("Created unarmed timer # %d %d.\n", fd, idx);
        fflush(stdout);
    #endif    
    return fd;
}
#endif

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)
void mw_ArmTimer(int idx)
{
    int status;
    struct itimerspec its;
    int fd = timer_fd[idx];
    double periodInSeconds = timer_period[idx];
    
    its.it_interval.tv_sec = (time_t)periodInSeconds;
    its.it_interval.tv_nsec = (periodInSeconds - (time_t)periodInSeconds) * 1000000000;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 1.0;
    #ifdef MW_RTOS_DEBUG
        printf("About to arm timer # %d %d.\n", fd, idx);
        fflush(stdout);
    #endif
    status = timerfd_settime(fd, 0, &its, NULL);
    #ifdef MW_RTOS_DEBUG
        printf("Armed timer # %d %d.\n", fd, idx);
        fflush(stdout);
    #endif
    
    CHECK_STATUS(status, 0, "timer_settime"); 
}
#endif

void mw_WaitForTimerEvent(int fd)
{
    unsigned long long missed;
    int status;
    
    /* Wait for the next timer event. If we have missed any the
       number is written to "missed" */
    while ((status = read(fd, &missed, sizeof(missed)) == -1) && (errno == EINTR)) {
        /* Restart if interrupted by a signal */
        continue;
    }
    if (status == -1) {
        perror("read(timerfd)");
    }
}

void mw_WaitForTimerEventCatchup(int fd)
{
    unsigned long long missed = 0;
    int status = 0;
    static unsigned int outstanding = 0;
    
    /* Wait for the next timer event. If we have missed any the
     * number is written to "missed" */
    if (outstanding == 0)
    {
        while ((status = read(fd, &missed, sizeof(missed)) == -1) && (errno == EINTR)) {
            /* Restart if interrupted by a signal */
            continue;
        }
        if (status == -1) {
            perror("read(timerfd)");
        }
        if (missed > 1) {
            #ifdef MW_RTOS_DEBUG
            printf("Missed %llu events for the timer # %d.\n", missed, fd);
            fflush(stdout);
            #endif
            outstanding = outstanding + missed - 1;
        }
    }
    else
    {
        #ifdef MW_RTOS_DEBUG
        printf("Catching up with the missed events for timer # %d.\n", fd);
        fflush(stdout);
        #endif
        outstanding--;
    }
}

/* ---------------------------- */
/* Internally visible functions */
/* ---------------------------- */


#ifdef MW_SOC_ENABLED
void *baseTimerTask(void* arg)
{
    /* SOCB product installed and used */
    int fd;
    baseRateInfo_t info = *((baseRateInfo_t *)arg);

    MW_DEBUG_LOG("schedulerTask entered\n");
    fd = mw_CreateArmedTimer(info.period);  
    SOCB_RateCounterFcn();   
    while(1) {
        mw_WaitForTimerEvent(fd);
        SOCB_RateCounterFcn();
    }
}
#else 
void *schedulerTask(void* arg)
{
    /* SOCB product not installed or not used */
    int fd;
    baseRateInfo_t info = *((baseRateInfo_t *)arg);

    MW_DEBUG_LOG("schedulerTask entered\n");
    fd = mw_CreateArmedTimer(info.period);
    sem_post(&baserateTaskSem); 
    while(runModel) {
        mw_WaitForTimerEvent(fd);
        #ifdef DETECT_OVERRUNS        
            testForRateOverrun(0);
        #endif
        sem_post(&baserateTaskSem);
    }
}
#endif


/* Should use this fcn, but currently are not using it */
/* Why: it is safe ??? from interruption */
void my_sem_wait(sem_t *sem)
{
    int status;
    while (((status = sem_wait(sem)) == -1) && (errno == EINTR)) {
        /* Restart if interrupted by a signal */
        continue;
    }
    CHECK_STATUS(status, 0, "my_sem_wait");
}

static void setThreadPriority(const int priority, pthread_attr_t *attr, struct sched_param *sp)
{
#if MW_SP_SCHED_FIFO
    int status;
    
    sp->sched_priority = priority;
    status = pthread_attr_setschedparam(attr, sp);
    CHECK_STATUS(status, 0, "pthread_attr_setschedparam");
#endif
}

/* ---------------------------- */
/* Externally visible functions */
/* ---------------------------- */

void mw_CreateTask(void * (*taskHandler)(void *), const char* taskName, int priority, int policy, int coreSelection, int coreNum)
{
    int status;
    int inherit;
    pthread_attr_t attr;
    pthread_t thread;
    struct sched_param param;
    size_t stackSize;
    pthread_attr_init(&attr);
    cpu_set_t cpuset;
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    char thisTaskName[MW_MAX_TASKNAME];
#endif

    /* Set thread inherit attribute */
    inherit = PTHREAD_EXPLICIT_SCHED;
    status = pthread_attr_setinheritsched(&attr, inherit);
    CHECK_STATUS(status, 0, "pthread_attr_setinheritsched");

    /* Set thread detach attribute */
    status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    CHECK_STATUS(status, 0, "pthread_attr_setdetachstate");

    /* Set thread stack size attribute */
    stackSize = (512 > PTHREAD_STACK_MIN) ? 512:PTHREAD_STACK_MIN;
    status = pthread_attr_setstacksize(&attr, stackSize);
    CHECK_STATUS(status, 0, "pthread_attr_setstacksize");

    /* Set thread schedule policy attribute */
    policy = SCHED_FIFO;
    status = pthread_attr_setschedpolicy(&attr, policy);
    CHECK_STATUS(status, 0, "pthread_attr_setschedpolicy");

    /* Set thread priority attribute */
    param.sched_priority = priority;
    status = pthread_attr_setschedparam(&attr, &param);
    CHECK_STATUS(status, 0, "pthread_attr_setschedparam");
    
    /* Set the thread core affinity */
    if (2 == coreSelection) 
    {
        CPU_ZERO(&cpuset);
        CPU_SET(coreNum, &cpuset);
        status =  pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
        CHECK_STATUS(status, 0, "pthread_attr_setaffinity_np");
    }

    /* Create the thread */
    status = pthread_create(&thread, &attr, taskHandler, NULL);
    CHECK_STATUS(status, 0, "pthread_create");
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    /* Set name of the thread */
    snprintf(thisTaskName, MW_MAX_TASKNAME, "%s", taskName);
    status = pthread_setname_np(thread, thisTaskName);
    CHECK_STATUS(status, 0, "pthread_setname_np at mw_CreateTask");
#endif
    pthread_attr_destroy(&attr);
}

void myAddBlockForThisEvent(int sigNo)
{
    int status;
    sigset_t sigMask;

    sigemptyset(&sigMask);
    sigaddset(&sigMask, sigNo);
    status = pthread_sigmask(SIG_BLOCK, &sigMask, NULL);
    CHECK_STATUS(status, 0, "pthread_sigmask");
}

void myAddHandlerForThisEvent(int sigNo, int sigToBlock[], int numSigToBlock, void (*sigHandler)(int))
{
    int idx;
    int status;
    struct sigaction sa;

    sa.sa_handler = (__sighandler_t) sigHandler;
    sigemptyset(&sa.sa_mask);
    for (idx=0; idx<numSigToBlock; idx++) {
            sigaddset(&sa.sa_mask, sigToBlock[idx]);
    }
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
    status = sigaction(sigNo, &sa, NULL);
    CHECK_STATUS_NOT(status, -1, "sigaction to register a signal handler");
}

void myRestoreDefaultHandlerForThisEvent(int sigNo)
{
    int status;
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
    status = sigaction(sigNo, &sa, NULL);
    CHECK_STATUS_NOT(status, -1, "sigaction to restore default signal handler");
}

/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/

void myRTOSInit(double baseRatePeriod, int numSubrates)
{
    int i;
    int status;
    uid_t euid;
    size_t stackSize;
    unsigned long cpuMask = 0x1;
    unsigned int len = sizeof(cpuMask);  
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    char thisTaskName[MW_MAX_TASKNAME];
#endif

#if (defined(MW_TSKMGR_EVENT_DRIVEN_TASKS) && (MW_TSKMGR_EVENT_DRIVEN_TASKS > 0))
    {
        int idx;
        for (idx=0;idx < MW_TSKMGR_EVENT_DRIVEN_TASKS;idx++)
        {
            mw_CreateTask(asyncTaskCodeGenInfo[idx].pAsyncTasks, \
                    (const char*) asyncTaskCodeGenInfo[idx].taskName,\
                    asyncTaskCodeGenInfo[idx].priority, \
                    asyncTaskCodeGenInfo[idx].policy, \
                    asyncTaskCodeGenInfo[idx].coreSelection, \
                    asyncTaskCodeGenInfo[idx].coreNum);
        }
    }
#endif
    UNUSED(baseRatePeriod);
    UNUSED(numSubrates);
        
    if (!MW_IS_CONCURRENT) {
        /* All threads created by this process will run on a single CPU */
        status = sched_setaffinity(0, len, (cpu_set_t *) &cpuMask);
        CHECK_STATUS(status, 0, "sched_setaffinity");
    }

#if MW_SP_SCHED_FIFO && !defined (_POSIX_THREAD_PRIORITY_SCHEDULING)
    fprintf(stderr, "Priority scheduling is NOT supported by your system.\n");
    fprintf(stderr, "The generated code will not run correctly because your\n");
    fprintf(stderr, "model contains multiple rates and uses multi-tasking\n");
    fprintf(stderr, "code generation mode. You can only run the generated code\n");
    fprintf(stderr, "in single-tasking mode in your system. Open\n");
    fprintf(stderr, "Simulation -> Configuration Parameters -> Solver dialog\n");
    fprintf(stderr, "and set \"Tasking mode for periodic sample times\" parameter to SingleTasking.\n");
    fprintf(stderr, "Re-build the Simulink model with the new settings and try executing the generated code again.\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
#endif
    
#if MW_SP_SCHED_FIFO
    /* Need root privileges for real-time scheduling */
    euid = geteuid();
    if (euid != 0) {
        fprintf(stderr, "You must have root privileges to run the generated code because\n");
        fprintf(stderr, "generated code requires SCHED_FIFO scheduling class to run correctly.\n");
        fprintf(stderr, "Try running the executable with the following command: sudo ./<executable name>\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
#endif

    status = sem_init(&baserateTaskSem, 0, 0);
    CHECK_STATUS(status, 0, "sem_init:baserateTaskSemSem");
    status = sem_init(&stopSem, 0, 0);
    CHECK_STATUS(status, 0, "sem_init:stopSem");
    
#if MW_SP_SCHED_FIFO
    /* Set scheduling policy of the main thread to SCHED_FIFO */
    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
    status = sched_setscheduler(0, SCHED_FIFO, &sp);
    CHECK_STATUS(status, 0, "sched_setscheduler");
#endif

    /* Create threads executing the Simulink model */
    pthread_attr_init(&attr);
    status = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    CHECK_STATUS(status, 0, "pthread_attr_setinheritsched");
#if MW_SP_SCHED_FIFO
    status = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
#else
    status = pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
#endif
    CHECK_STATUS(status, 0, "pthread_attr_setschedpolicy");
    status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    CHECK_STATUS(status, 0, "pthread_attr_setdetachstate");

    /* Set thread stack size if necessary */
    status = pthread_attr_getstacksize(&attr, &stackSize);
    CHECK_STATUS(status, 0, "pthread_attr_getstacksize");
    if (stackSize < STACK_SIZE) {
        /* Make sure that stackSize is a multiple of 8 */
        stackSize = (STACK_SIZE + 7) & (~0x7);
        pthread_attr_setstacksize(&attr, stackSize);
        CHECK_STATUS(status, 0, "pthread_attr_setstacksize");
    }

    signal(SIGTERM, exitFcn);     /* kill */
    signal(SIGHUP, exitFcn);      /* kill -HUP */
    signal(SIGINT, exitFcn);      /* Interrupt from keyboard */
    signal(SIGQUIT, exitFcn);     /* Quit from keyboard */

#ifdef MW_STANDALONE_EXECUTION_PROFILER_ON
    status = pthread_mutex_init(&profilingDataStoreMutex, NULL);    
#endif
    
#ifdef MW_HAS_MULTIPLE_RATES
    MW_DEBUG_LOG("**creating subrate task threads**\n");   
    for (i = 0; i < MW_NUMBER_SUBRATES; i++) {
        taskId[i] = i;
        status = sem_init(&subrateTaskSem[i], 0, 0);
        CHECK_STATUS(status, 0, "sem_init");
        setThreadPriority(subratePriority[i], &attr, &sp);
        status = pthread_create(&subRateThread[i], &attr, &subrateTask, (void *)&taskId[i]);
        CHECK_STATUS(status, 0, "pthread_create");
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
        /* Set name of sub-rate threads */
        snprintf(thisTaskName, MW_MAX_TASKNAME, "%s", _mwTskMgrTimerDrivenTaskNames[i+1]);
        MW_DEBUG_LOG(thisTaskName);   
        status = pthread_setname_np(subRateThread[i], thisTaskName);
        CHECK_STATUS(status, 0, "pthread_setname_np at subRateThread");
#endif        
#ifdef DETECT_OVERRUNS
        status = pthread_mutex_init(&rateTaskFcnRunningMutex[i+1], NULL);
        CHECK_STATUS(status, 0, "pthread_mutex_init");
#endif        
#ifdef COREAFFINITYREQUIRED
        if (coreAffinity[i] >= 0) {
             cpu_set_t cpuset;
             CPU_ZERO(&cpuset);
             CPU_SET(coreAffinity[i], &cpuset);
             status = pthread_setaffinity_np(subRateThread[i], sizeof(cpu_set_t), &cpuset);
             CHECK_STATUS(status, 0, "pthread_setaffinity_np");
         }
#endif
    }
#endif

    MW_DEBUG_LOG("**creating the base rate task thread**\n");    
    setThreadPriority(MW_BASERATE_PRIORITY, &attr, &sp);  
    status = pthread_create(&baseRateThread, &attr, &baseRateTask, NULL);
    CHECK_STATUS(status, 0, "pthread_create");
    
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    /* Set name of the base-rate thread */
    snprintf(thisTaskName, MW_MAX_TASKNAME, _mwTskMgrTimerDrivenTaskNames[0]);
    status = pthread_setname_np(baseRateThread, thisTaskName);
    CHECK_STATUS(status, 0, "pthread_setname_np at baserateThread");
#endif
    
#ifdef DETECT_OVERRUNS
    status = pthread_mutex_init(&rateTaskFcnRunningMutex[0], NULL);
    CHECK_STATUS(status, 0, "pthread_mutex_init");
#endif

#ifdef COREAFFINITYREQUIRED
    if (coreAffinityBaseRate >= 0) {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(coreAffinityBaseRate, &cpuset);
        status = pthread_setaffinity_np(baseRateThread, sizeof(cpu_set_t), &cpuset);
        CHECK_STATUS(status, 0, "pthread_setaffinity_np");
    }   
#endif

#ifdef MW_SOC_ENABLED    
    MW_DEBUG_LOG("**creating the socb base rate timer handler thread**\n");  
    /* Set the priority higher (higher number) than the base rate */    
    setThreadPriority(MW_BASERATE_PRIORITY + 2, &attr, &sp);
    info.period = MW_BASERATE_PERIOD;
    status = pthread_create(&baseTimerThread, &attr, &baseTimerTask, (void *) &info);
    CHECK_STATUS(status, 0, "pthread_create");
    status = pthread_setname_np(baseTimerThread, "baseTimerTask");
#endif 
    
    MW_DEBUG_LOG("**creating the scheduler thread**\n");  
    /* Set the priority higher (higher number) than the base rate */    
    setThreadPriority(MW_BASERATE_PRIORITY + 1, &attr, &sp);
    info.period = MW_BASERATE_PERIOD;
    status = pthread_create(&schedulerThread, &attr, &schedulerTask, (void *) &info);
    CHECK_STATUS(status, 0, "pthread_create");
       
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    /* Set name of the scheduler thread */
    snprintf(thisTaskName, MW_MAX_TASKNAME, "scheduler");
    status = pthread_setname_np(schedulerThread, thisTaskName);
    CHECK_STATUS(status, 0, "pthread_setname_np at scheduler thread");
#endif

#ifdef MW_HAS_APERIODIC_TASKS
    MW_DEBUG_LOG("**creating asynchronously triggered task threads**\n"); 
    /* Set the priority higher (higher number) than the base rate */    
    sp.sched_priority = MW_BASERATE_PRIORITY + 1;
    for (i = 0; i < MW_NUMBER_APERIODIC_TASKS; i++) {
        status = pthread_create(&asyncThread[i], &attr, (void *) pAsyncTasks[i], NULL);
        CHECK_STATUS(status, 0, "pthread_create");
    }
#endif
    
#ifdef MW_NEEDS_BACKGROUND_TASK
    MW_DEBUG_LOG("**creating the background thread**\n");
    status = pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
    CHECK_STATUS(status, 0, "pthread_attr_setschedpolicy");
    setThreadPriority(0, &attr, &sp);
    status = pthread_create(&backgroundThread, &attr, &backgroundTask, NULL);
    CHECK_STATUS(status, 0, "pthread_create");
#ifdef MW_TSKMGR_TIMER_DRIVEN_TASKS
    /* Set name of the background thread */
    snprintf(thisTaskName, MW_MAX_TASKNAME, "background");
    status = pthread_setname_np(backgroundThread, thisTaskName);
    CHECK_STATUS(status, 0, "pthread_setname_np at backgroundThread");
#endif 
#if MW_SP_SCHED_FIFO == 0
    status = pthread_setschedparam(backgroundThread, SCHED_IDLE, &sp);
    CHECK_STATUS(status, 0, "pthread_setschedparam");
#ifdef MW_HAS_COMM_SERVICE
    status = makeCSTaskIdle();
    CHECK_STATUS(status, 0, "pthread_setschedparam");
#endif 
#endif
#endif

    pthread_attr_destroy(&attr);
    fflush(stdout);
}
