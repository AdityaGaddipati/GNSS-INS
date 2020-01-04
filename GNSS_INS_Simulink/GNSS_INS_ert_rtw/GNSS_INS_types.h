/*
 * GNSS_INS_types.h
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

#ifndef RTW_HEADER_GNSS_INS_types_h_
#define RTW_HEADER_GNSS_INS_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_ros_time_Time_

typedef struct {
  real_T Sec;
  real_T Nsec;
} SL_Bus_GNSS_INS_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_std_msgs_Header_

typedef struct {
  uint32_T Seq;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
  SL_Bus_GNSS_INS_ros_time_Time Stamp;
} SL_Bus_GNSS_INS_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Point_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_GNSS_INS_geometry_msgs_Point;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Quaternion_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_GNSS_INS_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Pose_

typedef struct {
  SL_Bus_GNSS_INS_geometry_msgs_Point Position;
  SL_Bus_GNSS_INS_geometry_msgs_Quaternion Orientation;
} SL_Bus_GNSS_INS_geometry_msgs_Pose;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance_

typedef struct {
  real_T Covariance[36];
  SL_Bus_GNSS_INS_geometry_msgs_Pose Pose;
} SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_GNSS_INS_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Twist_

typedef struct {
  SL_Bus_GNSS_INS_geometry_msgs_Vector3 Linear;
  SL_Bus_GNSS_INS_geometry_msgs_Vector3 Angular;
} SL_Bus_GNSS_INS_geometry_msgs_Twist;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance_

typedef struct {
  real_T Covariance[36];
  SL_Bus_GNSS_INS_geometry_msgs_Twist Twist;
} SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_nav_msgs_Odometry_

typedef struct {
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_GNSS_INS_std_msgs_Header Header;
  SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance Pose;
  SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance Twist;
} SL_Bus_GNSS_INS_nav_msgs_Odometry;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_Imu_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_Imu_

typedef struct {
  real_T OrientationCovariance[9];
  real_T AngularVelocityCovariance[9];
  real_T LinearAccelerationCovariance[9];
  SL_Bus_GNSS_INS_std_msgs_Header Header;
  SL_Bus_GNSS_INS_geometry_msgs_Quaternion Orientation;
  SL_Bus_GNSS_INS_geometry_msgs_Vector3 AngularVelocity;
  SL_Bus_GNSS_INS_geometry_msgs_Vector3 LinearAcceleration;
} SL_Bus_GNSS_INS_sensor_msgs_Imu;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus_

typedef struct {
  int8_T Status;
  uint16_T Service;
} SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_NavSatFix_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_sensor_msgs_NavSatFix_

typedef struct {
  real_T Latitude;
  real_T Longitude;
  real_T Altitude;
  uint8_T PositionCovarianceType;
  real_T PositionCovariance[9];
  SL_Bus_GNSS_INS_std_msgs_Header Header;
  SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus Status;
} SL_Bus_GNSS_INS_sensor_msgs_NavSatFix;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped_

typedef struct {
  SL_Bus_GNSS_INS_std_msgs_Header Header;
  SL_Bus_GNSS_INS_geometry_msgs_Vector3 Vector_;
} SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped;

#endif

#ifndef typedef_ros_slros_internal_block_Publ_T
#define typedef_ros_slros_internal_block_Publ_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Publ_T;

#endif                               /*typedef_ros_slros_internal_block_Publ_T*/

#ifndef typedef_ros_slros_internal_block_Subs_T
#define typedef_ros_slros_internal_block_Subs_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Subs_T;

#endif                               /*typedef_ros_slros_internal_block_Subs_T*/

/* Custom Type definition for MATLAB Function: '<Root>/MATLAB Function5' */
#ifndef typedef_c_fusion_internal_coder_insfi_T
#define typedef_c_fusion_internal_coder_insfi_T

typedef struct {
  real_T State[16];
  real_T StateCovariance[256];
  real_T IMUSampleRate;
  real_T ReferenceLocation[3];
  int32_T DecimationFactor;
  real_T GyroscopeNoise[3];
  real_T AccelerometerNoise[3];
  real_T GyroscopeBiasNoise[3];
  real_T GyroscopeBiasDecayFactor;
  real_T AccelerometerBiasNoise[3];
  real_T AccelerometerBiasDecayFactor;
  real_T ZeroVelocityConstraintNoise;
  int32_T applyConstraintCount;
} c_fusion_internal_coder_insfi_T;

#endif                               /*typedef_c_fusion_internal_coder_insfi_T*/

/* Parameters (default storage) */
typedef struct P_GNSS_INS_T_ P_GNSS_INS_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_GNSS_INS_T RT_MODEL_GNSS_INS_T;

#endif                                 /* RTW_HEADER_GNSS_INS_types_h_ */
