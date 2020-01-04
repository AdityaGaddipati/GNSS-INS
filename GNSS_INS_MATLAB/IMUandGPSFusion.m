%% SETUP
% Start or connect to ROS master
rosshutdown;
ipAddr = '192.168.0.102';
rosinit(ipAddr)

%Load Parameters
imuFs = 50;
gpsFs = 1;
localOrigin = [18.954817 72.811367 0];

%% Fusion Filter
% Create the filter to fuse IMU + GPS measurements. The fusion filter uses
% an extended Kalman filter to track orientation (as a quaternion),
% position, velocity, and sensor biases.
%
% The |insfilterNonholonomic| object that has two main methods: |predict|
% and |fusegps|. The |predict| method takes the accelerometer and gyroscope
% samples from the IMU as input. Call the |predict| method each time the
% accelerometer and gyroscope are sampled. This method predicts the states
% forward one time step based on the accelerometer and gyroscope. The error
% covariance of the extended Kalman filter is updated in this step.
%
% The |fusegps| method takes the GPS samples as input. This method updates
% the filter states based on the GPS sample by computing a Kalman gain that
% weights the various sensor inputs according to their uncertainty. An
% error covariance is also updated in this step, this time using the Kalman
% gain as well.
%
% The |insfilterNonholonomic| object has two main properties:
% |IMUSampleRate| and |DecimationFactor|. The ground vehicle has two
% velocity constraints that assume it does not bounce off the ground or
% slide on the ground. These constraints are applied using the extended
% Kalman filter update equations. These updates are applied to the filter
% states at a rate of |IMUSampleRate/DecimationFactor| Hz.

global gndFusion
gndFusion = insfilterNonholonomic('ReferenceFrame', 'ENU', ...
    'IMUSampleRate', imuFs, ...
    'ReferenceLocation', localOrigin, ...
    'DecimationFactor', 2);

%% Initialize the States of the |insfilterNonholonomic|
% The states are:
% 
%  States                            Units    Index
%  Orientation (quaternion parts)             1:4  
%  Gyroscope Bias (XYZ)              rad/s    5:7  
%  Position (NED)                    m        8:10 
%  Velocity (NED)                    m/s      11:13
%  Accelerometer Bias (XYZ)          m/s^2    14:16
%
% Ground truth is used to help initialize the filter states, so the filter
% converges to good answers quickly.

% Initialize the states of the filter
gndFusion.State(1:4) = [0.707,0,0,0.707];
gndFusion.State(5:7) = [0,0,0];
gndFusion.State(8:10) = [0,0,0];
gndFusion.State(11:13) = [0,0,0];
gndFusion.State(14:16) = [0,0,0];

%% Initialize the Variances of the |insfilterNonholonomic|
% The measurement noises describe how much noise is corrupting the GPS 
% reading based on the |gpsSensor| parameters and how much uncertainty is 
% in the vehicle dynamic model.
%
% The process noises describe how well the filter equations describe the
% state evolution. Process noises are determined empirically using
% parameter sweeping to jointly optimize position and orientation
% estimates from the filter. 

% The dynamic model of the ground vehicle for this filter assumes there is
% no side slip or skid during movement. This means that the velocity is 
% constrained to only the forward body axis. The other two velocity axis 
% readings are corrected with a zero measurement weighted by the 
% |ZeroVelocityConstraintNoise| parameter.
gndFusion.ZeroVelocityConstraintNoise = 1e-2;

% Process noises
gndFusion.GyroscopeNoise = 2.5e-5;
gndFusion.GyroscopeBiasNoise = 1.4e-8;
gndFusion.AccelerometerNoise = 2.5e-5;
gndFusion.AccelerometerBiasNoise = 1.4e-8;

% Initial error covariance
gndFusion.StateCovariance = 1e-9*ones(16);

% Create ROS subscribers
imuSub = rossubscriber('/imu_data', @imuCallback);
gpsSub = rossubscriber('/fix', @gpsCallback);
velSub = rossubscriber('/vel', @velCallback);

while(1)
    [pos,or,vel] = pose(gndFusion);
    disp(pos);
    disp(or);
    disp(vel);
    pause(1);
end