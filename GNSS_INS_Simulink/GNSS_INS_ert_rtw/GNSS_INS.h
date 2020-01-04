/*
 * GNSS_INS.h
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "GNSS_INS".
 *
 * Model version              : 1.73
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Sun Jan  5 00:00:22 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_GNSS_INS_h_
#define RTW_HEADER_GNSS_INS_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef GNSS_INS_COMMON_INCLUDES_
# define GNSS_INS_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* GNSS_INS_COMMON_INCLUDES_ */

#include "GNSS_INS_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T F[256];
  real_T F_m[256];
  real_T F_c[256];
  real_T P[256];
  real_T W[256];
  real_T P_k[256];
  real_T P_c[256];
  real_T W_b[256];
  real_T P_p[256];
  real_T G[192];
  real_T G_c[192];
  real_T U[144];
  SL_Bus_GNSS_INS_nav_msgs_Odometry BusAssignment;/* '<Root>/Bus Assignment' */
  real_T H[64];
  real_T W_f[64];
  real_T A_tmp[64];
  real_T H_g[64];
  SL_Bus_GNSS_INS_sensor_msgs_Imu In1; /* '<S9>/In1' */
  SL_Bus_GNSS_INS_sensor_msgs_Imu b_varargout_2;
  SL_Bus_GNSS_INS_sensor_msgs_NavSatFix In1_c;/* '<S10>/In1' */
  SL_Bus_GNSS_INS_sensor_msgs_NavSatFix b_varargout_2_p;
  real_T H_g1[32];
  real_T W_m[32];
  real_T y[32];
  real_T H_n[32];
  SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped b_varargout_2_l;
  real_T x[16];
  real_T x_j[16];
  real_T x_d[16];
  real_T dv[16];
  real_T A[16];
  real_T Rpos[9];
  real_T Rvel[9];
  real_T gyroVar[9];
  real_T gyroBiasVar[9];
  real_T accelVar[9];
  real_T accelBiasVar[9];
  real_T R[4];
  real_T S[4];
  real_T h[4];
  real_T pos[4];
  real_T dv1[3];
  real_T dv2[3];
  real_T pos_g[3];
  real_T dv3[3];
  real_T dv4[3];
  real_T h_l[2];
  real_T dv5[2];
  real_T dt;
  real_T accelBiasDecayFactor;
  real_T gyroBiasDecayFactor;
  real_T a21;
  real_T a22;
  real_T a22_tmp;
  real_T n;
  real_T qparts_idx_0;
  real_T courseR;
  real_T smax;
  real_T y_d;
  real_T z_idx_1;
  real_T z_idx_2;
  real_T z_idx_3;
  real_T d;
  real_T d1;
  real_T d2;
  real_T d3;
  real_T d4;
  real_T d5;
  real_T d6;
  real_T d7;
  real_T d8;
  real_T d9;
  real_T d10;
  real_T d11;
  real_T d12;
  real_T d13;
  real_T d14;
  real_T d15;
  real_T d16;
  real_T d17;
  real_T d18;
  real_T d19;
  real_T d20;
  real_T d21;
  real_T d22;
  real_T d23;
  real_T d24;
  real_T d25;
  real_T d26;
  real_T d27;
  real_T d28;
  real_T d29;
  real_T d30;
  real_T d31;
  real_T d32;
  real_T d33;
  real_T d34;
  real_T d35;
  real_T d36;
  real_T d37;
  real_T d38;
  real_T d39;
  real_T d40;
  real_T d41;
  real_T d42;
  real_T d43;
  real_T d44;
  real_T d45;
  real_T d46;
  real_T d47;
  real_T d48;
  real_T d49;
  real_T d50;
  real_T d51;
  real_T d52;
  real_T d53;
  real_T d54;
  real_T d55;
  real_T d56;
  real_T d57;
  real_T d58;
  real_T d59;
  real_T d60;
  real_T d61;
  real_T d62;
  real_T d63;
  real_T d64;
  real_T d65;
  real_T d66;
  real_T d67;
  real_T d68;
  real_T d69;
  real_T d70;
  real_T d71;
  real_T d72;
  real_T d73;
  real_T d74;
  real_T d75;
  real_T d76;
  real_T d77;
  real_T d78;
  real_T d79;
  real_T d80;
  real_T d81;
  real_T d82;
  real_T d83;
  real_T d84;
  real_T d85;
  real_T d86;
  real_T d87;
  real_T d88;
  real_T d89;
  real_T d90;
  real_T d91;
  real_T d92;
  real_T d93;
  real_T d94;
  real_T d95;
  real_T d96;
  real_T d97;
  real_T d98;
  real_T d99;
  real_T d100;
  real_T d101;
  real_T d102;
  real_T d103;
  real_T d104;
  real_T d105;
  real_T d106;
  real_T d107;
  real_T d108;
  real_T d109;
  real_T d110;
  real_T d111;
  real_T d112;
  real_T d113;
  real_T d114;
  real_T d115;
  real_T d116;
  real_T d117;
  real_T d118;
  real_T d119;
  real_T cosphi;
  real_T sinphi;
  real_T coslambda;
  real_T sinlambda;
  real_T tmp;
  real_T ecefPosWithENUOrigin_idx_0;
  real_T ecefPosWithENUOrigin_idx_1;
  real_T ecefPosWithENUOrigin_idx_2;
  real_T sinphi_d;
  real_T F_tmp;
  real_T F_tmp_l;
  real_T F_tmp_o;
  real_T F_tmp_b;
  real_T F_tmp_n;
  real_T F_tmp_tmp;
  real_T F_tmp_bs;
  real_T F_tmp_tmp_l;
  real_T F_tmp_h;
  real_T F_tmp_bn;
  real_T H_tmp;
  real_T H_tmp_d;
  real_T H_tmp_e;
  real_T H_tmp_b;
  real_T H_tmp_j;
  real_T H_tmp_f;
  real_T H_tmp_a;
  real_T H_tmp_ju;
  real_T H_tmp_jz;
  real_T G_tmp;
  real_T G_tmp_o;
  real_T G_tmp_tmp;
  real_T G_tmp_n;
  real_T G_tmp_i;
} B_GNSS_INS_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  c_fusion_internal_coder_insfi_T gndFusion;/* '<Root>/MATLAB Function5' */
  ros_slros_internal_block_Publ_T obj; /* '<S5>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_n;/* '<S8>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_m;/* '<S7>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_nf;/* '<S6>/SourceBlock' */
  real_T robotVel[3];                  /* '<Root>/MATLAB Function' */
  boolean_T objisempty;                /* '<S8>/SourceBlock' */
  boolean_T objisempty_l;              /* '<S7>/SourceBlock' */
  boolean_T objisempty_g;              /* '<S6>/SourceBlock' */
  boolean_T objisempty_j;              /* '<S5>/SinkBlock' */
  boolean_T gndFusion_not_empty;       /* '<Root>/MATLAB Function5' */
} DW_GNSS_INS_T;

/* Parameters (default storage) */
struct P_GNSS_INS_T_ {
  SL_Bus_GNSS_INS_nav_msgs_Odometry Constant_Value;/* Computed Parameter: Constant_Value
                                                    * Referenced by: '<S1>/Constant'
                                                    */
  SL_Bus_GNSS_INS_sensor_msgs_Imu Out1_Y0;/* Computed Parameter: Out1_Y0
                                           * Referenced by: '<S9>/Out1'
                                           */
  SL_Bus_GNSS_INS_sensor_msgs_Imu Constant_Value_d;/* Computed Parameter: Constant_Value_d
                                                    * Referenced by: '<S6>/Constant'
                                                    */
  SL_Bus_GNSS_INS_sensor_msgs_NavSatFix Out1_Y0_h;/* Computed Parameter: Out1_Y0_h
                                                   * Referenced by: '<S10>/Out1'
                                                   */
  SL_Bus_GNSS_INS_sensor_msgs_NavSatFix Constant_Value_dl;/* Computed Parameter: Constant_Value_dl
                                                           * Referenced by: '<S7>/Constant'
                                                           */
  SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped Out1_Y0_a;/* Computed Parameter: Out1_Y0_a
                                                          * Referenced by: '<S11>/Out1'
                                                          */
  SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped Constant_Value_h;/* Computed Parameter: Constant_Value_h
                                                                 * Referenced by: '<S8>/Constant'
                                                                 */
};

/* Real-time Model Data Structure */
struct tag_RTM_GNSS_INS_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_GNSS_INS_T GNSS_INS_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern B_GNSS_INS_T GNSS_INS_B;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern DW_GNSS_INS_T GNSS_INS_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void GNSS_INS_initialize(void);
  extern void GNSS_INS_step(void);
  extern void GNSS_INS_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_GNSS_INS_T *const GNSS_INS_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'GNSS_INS'
 * '<S1>'   : 'GNSS_INS/Blank Message'
 * '<S2>'   : 'GNSS_INS/MATLAB Function'
 * '<S3>'   : 'GNSS_INS/MATLAB Function1'
 * '<S4>'   : 'GNSS_INS/MATLAB Function5'
 * '<S5>'   : 'GNSS_INS/Publish'
 * '<S6>'   : 'GNSS_INS/Subscribe'
 * '<S7>'   : 'GNSS_INS/Subscribe1'
 * '<S8>'   : 'GNSS_INS/Subscribe2'
 * '<S9>'   : 'GNSS_INS/Subscribe/Enabled Subsystem'
 * '<S10>'  : 'GNSS_INS/Subscribe1/Enabled Subsystem'
 * '<S11>'  : 'GNSS_INS/Subscribe2/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_GNSS_INS_h_ */
