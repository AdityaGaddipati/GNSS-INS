/*
 * GNSS_INS.cpp
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

#include "GNSS_INS.h"
#include "GNSS_INS_private.h"

/* Block signals (default storage) */
B_GNSS_INS_T GNSS_INS_B;

/* Block states (default storage) */
DW_GNSS_INS_T GNSS_INS_DW;

/* Real-time model */
RT_MODEL_GNSS_INS_T GNSS_INS_M_ = RT_MODEL_GNSS_INS_T();
RT_MODEL_GNSS_INS_T *const GNSS_INS_M = &GNSS_INS_M_;

/* Forward declaration for local functions */
static void GN_IMUBasicEKF_repairQuaternion(real_T x[16]);
static void NHConstrainedIMUGPSFuserBase_hu(real_T x[16], real_T dt, const
  real_T accelMeas[3], const real_T gyroMeas[3], real_T accelBiasDecayFactor,
  real_T gyroBiasDecayFactor);
static void NHConstrainedIMUGPSFuserBase_st(const real_T x[16], real_T dt, const
  real_T accelMeas[3], const real_T gyroMeas[3], real_T accelBiasDecayFactor,
  real_T gyroBiasDecayFactor, real_T F[256]);
static void NHConstrainedIMUGPSFuserBase__h(const real_T x[16], real_T dt,
  real_T G[192]);
static void NHConstrainedIMUGPSFuserBase__d(const
  c_fusion_internal_coder_insfi_T *obj, real_T U[144]);
static void NHConstrainedIMUGPSFuserBase_me(const real_T x[16], real_T h[2]);
static void NHConstrainedIMUGPSFuserBase__g(const real_T x[16], real_T H[32]);
static void NHConstrainedIMUGPSFuserBase__o(const
  c_fusion_internal_coder_insfi_T *obj, real_T R[4]);
static void GNSS_INS_IMUBasicEKF_correctEqn(real_T x[16], real_T P[256], const
  real_T h[2], const real_T H[32], const real_T z[2], const real_T R[4]);
static void NHConstrainedIMUGPSFuserBase_co(c_fusion_internal_coder_insfi_T *obj);
static void NHConstrainedIMUGPSFuserBase_pr(c_fusion_internal_coder_insfi_T *obj,
  const real_T accelMeas[3], const real_T gyroMeas[3]);
static void IMUBasicEKF_validateExpandNoise(real_T Rin, real_T Rout[9]);
static void NHConstrainedIMUGPSFuserBase_hv(const real_T x[16], real_T h[4]);
static void NHConstrainedIMUGPSFuserBase__m(const real_T x[16], real_T H[64]);
static void NHConstrainedIMUGPSFuserBase_ve(const real_T vel[3], const real_T
  velR[9], real_T *course, real_T *courseR);
static void NHConstrainedIMUGPSFuserBase_ad(real_T *zCourse, real_T hCourse);
static void GNSS_INS_cosd(real_T *x);
static void GNSS_INS_sind(real_T *x);
static void GNSS_INS_lla2ecef(const real_T llaPos[3], real_T ecefPos[3]);
static void GNSS_INS_ENU_lla2frame(const real_T llaMeas[3], const real_T refloc
  [3], real_T pos[3]);
static void GNSS_INS_blkdiag(const real_T varargin_1[9], real_T varargin_2,
  real_T y[16]);
static void GNSS_I_IMUBasicEKF_correctEqn_l(real_T x[16], real_T P[256], const
  real_T h[4], const real_T H[64], const real_T z[4], const real_T R[16]);
static void NHConstrainedIMUGPSFuserBase_fu(c_fusion_internal_coder_insfi_T *obj,
  const real_T gpsLLA[3], real_T RposIn, const real_T gpsVel[3], real_T RvelIn);
static void matlabCodegenHandle_matlabCod_d(ros_slros_internal_block_Subs_T *obj);
static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj);

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GN_IMUBasicEKF_repairQuaternion(real_T x[16])
{
  real_T qparts_idx_1;
  real_T qparts_idx_2;
  GNSS_INS_B.n = sqrt(((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) + x[3] * x[3]);
  GNSS_INS_B.qparts_idx_0 = x[0] / GNSS_INS_B.n;
  qparts_idx_1 = x[1] / GNSS_INS_B.n;
  qparts_idx_2 = x[2] / GNSS_INS_B.n;
  GNSS_INS_B.n = x[3] / GNSS_INS_B.n;
  if (GNSS_INS_B.qparts_idx_0 < 0.0) {
    x[0] = -GNSS_INS_B.qparts_idx_0;
    x[1] = -qparts_idx_1;
    x[2] = -qparts_idx_2;
    x[3] = -GNSS_INS_B.n;
  } else {
    x[0] = GNSS_INS_B.qparts_idx_0;
    x[1] = qparts_idx_1;
    x[2] = qparts_idx_2;
    x[3] = GNSS_INS_B.n;
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_hu(real_T x[16], real_T dt, const
  real_T accelMeas[3], const real_T gyroMeas[3], real_T accelBiasDecayFactor,
  real_T gyroBiasDecayFactor)
{
  real_T tmp;
  real_T tmp_0;
  GNSS_INS_B.d2 = x[1];
  GNSS_INS_B.d3 = x[0];
  GNSS_INS_B.d4 = x[4];
  GNSS_INS_B.d5 = x[3];
  GNSS_INS_B.d6 = x[5];
  GNSS_INS_B.d7 = x[2];
  GNSS_INS_B.d8 = x[6];
  GNSS_INS_B.d9 = x[2];
  GNSS_INS_B.d10 = x[3];
  GNSS_INS_B.d11 = x[4];
  GNSS_INS_B.d12 = x[0];
  GNSS_INS_B.d13 = x[5];
  GNSS_INS_B.d14 = x[1];
  GNSS_INS_B.d15 = x[6];
  GNSS_INS_B.d16 = x[3];
  GNSS_INS_B.d17 = x[2];
  GNSS_INS_B.d18 = x[4];
  GNSS_INS_B.d19 = x[1];
  GNSS_INS_B.d20 = x[5];
  GNSS_INS_B.d21 = x[0];
  GNSS_INS_B.d22 = x[6];
  GNSS_INS_B.d23 = x[4];
  GNSS_INS_B.d24 = x[5];
  GNSS_INS_B.d25 = x[6];
  GNSS_INS_B.d26 = x[7];
  GNSS_INS_B.d27 = x[10];
  GNSS_INS_B.d28 = x[8];
  GNSS_INS_B.d29 = x[11];
  GNSS_INS_B.d30 = x[9];
  GNSS_INS_B.d31 = x[12];
  GNSS_INS_B.d32 = x[10];
  GNSS_INS_B.d33 = x[0];
  GNSS_INS_B.d34 = x[0];
  GNSS_INS_B.d35 = x[13];
  GNSS_INS_B.d36 = x[3];
  GNSS_INS_B.d37 = x[14];
  GNSS_INS_B.d38 = x[2];
  GNSS_INS_B.d39 = x[15];
  GNSS_INS_B.d40 = x[2];
  GNSS_INS_B.d41 = x[1];
  GNSS_INS_B.d42 = x[14];
  GNSS_INS_B.d43 = x[2];
  GNSS_INS_B.d44 = x[13];
  GNSS_INS_B.d45 = x[0];
  GNSS_INS_B.d46 = x[15];
  GNSS_INS_B.d47 = x[1];
  GNSS_INS_B.d48 = x[1];
  GNSS_INS_B.d49 = x[13];
  GNSS_INS_B.d50 = x[2];
  GNSS_INS_B.d51 = x[14];
  GNSS_INS_B.d52 = x[3];
  GNSS_INS_B.d53 = x[15];
  GNSS_INS_B.d54 = x[3];
  GNSS_INS_B.d55 = x[3];
  GNSS_INS_B.d56 = x[13];
  GNSS_INS_B.d57 = x[0];
  GNSS_INS_B.d58 = x[14];
  GNSS_INS_B.d59 = x[1];
  GNSS_INS_B.d60 = x[15];
  GNSS_INS_B.d61 = x[11];
  GNSS_INS_B.d62 = x[0];
  GNSS_INS_B.d63 = x[3];
  GNSS_INS_B.d64 = x[13];
  GNSS_INS_B.d65 = x[0];
  GNSS_INS_B.d66 = x[14];
  GNSS_INS_B.d67 = x[1];
  GNSS_INS_B.d68 = x[15];
  GNSS_INS_B.d69 = x[1];
  GNSS_INS_B.d70 = x[1];
  GNSS_INS_B.d71 = x[14];
  GNSS_INS_B.d72 = x[2];
  GNSS_INS_B.d73 = x[13];
  GNSS_INS_B.d74 = x[0];
  GNSS_INS_B.d75 = x[15];
  GNSS_INS_B.d76 = x[2];
  GNSS_INS_B.d77 = x[1];
  GNSS_INS_B.d78 = x[13];
  GNSS_INS_B.d79 = x[2];
  GNSS_INS_B.d80 = x[14];
  GNSS_INS_B.d81 = x[3];
  GNSS_INS_B.d82 = x[15];
  GNSS_INS_B.d83 = x[3];
  GNSS_INS_B.d84 = x[0];
  GNSS_INS_B.d85 = x[13];
  GNSS_INS_B.d86 = x[3];
  GNSS_INS_B.d87 = x[14];
  GNSS_INS_B.d88 = x[2];
  GNSS_INS_B.d89 = x[15];
  GNSS_INS_B.d90 = x[12];
  GNSS_INS_B.d91 = x[0];
  GNSS_INS_B.d92 = x[1];
  GNSS_INS_B.d93 = x[14];
  GNSS_INS_B.d94 = x[2];
  GNSS_INS_B.d95 = x[13];
  GNSS_INS_B.d96 = x[0];
  GNSS_INS_B.d97 = x[15];
  GNSS_INS_B.d98 = x[1];
  GNSS_INS_B.d99 = x[3];
  GNSS_INS_B.d100 = x[13];
  GNSS_INS_B.d101 = x[0];
  GNSS_INS_B.d102 = x[14];
  GNSS_INS_B.d103 = x[1];
  GNSS_INS_B.d104 = x[15];
  GNSS_INS_B.d105 = x[2];
  GNSS_INS_B.d106 = x[0];
  GNSS_INS_B.d107 = x[13];
  GNSS_INS_B.d108 = x[3];
  GNSS_INS_B.d109 = x[14];
  GNSS_INS_B.d110 = x[2];
  GNSS_INS_B.d111 = x[15];
  GNSS_INS_B.d112 = x[3];
  GNSS_INS_B.d113 = x[1];
  GNSS_INS_B.d114 = x[13];
  GNSS_INS_B.d115 = x[2];
  GNSS_INS_B.d116 = x[14];
  GNSS_INS_B.d117 = x[3];
  GNSS_INS_B.d118 = x[15];
  GNSS_INS_B.d119 = x[13];
  tmp = x[14];
  tmp_0 = x[15];
  x[0] = (((x[4] / 2.0 - gyroMeas[0] / 2.0) * (dt * x[1]) + x[0]) + (x[5] / 2.0
           - gyroMeas[1] / 2.0) * (dt * x[2])) + (x[6] / 2.0 - gyroMeas[2] / 2.0)
    * (dt * x[3]);
  x[1] = ((GNSS_INS_B.d2 - (GNSS_INS_B.d4 / 2.0 - gyroMeas[0] / 2.0) * (dt *
            GNSS_INS_B.d3)) + (GNSS_INS_B.d6 / 2.0 - gyroMeas[1] / 2.0) * (dt *
           GNSS_INS_B.d5)) - (GNSS_INS_B.d8 / 2.0 - gyroMeas[2] / 2.0) * (dt *
    GNSS_INS_B.d7);
  x[2] = ((GNSS_INS_B.d9 - (GNSS_INS_B.d11 / 2.0 - gyroMeas[0] / 2.0) * (dt *
            GNSS_INS_B.d10)) - (GNSS_INS_B.d13 / 2.0 - gyroMeas[1] / 2.0) * (dt *
           GNSS_INS_B.d12)) + (GNSS_INS_B.d15 / 2.0 - gyroMeas[2] / 2.0) * (dt *
    GNSS_INS_B.d14);
  x[3] = (((GNSS_INS_B.d18 / 2.0 - gyroMeas[0] / 2.0) * (dt * GNSS_INS_B.d17) +
           GNSS_INS_B.d16) - (GNSS_INS_B.d20 / 2.0 - gyroMeas[1] / 2.0) * (dt *
           GNSS_INS_B.d19)) - (GNSS_INS_B.d22 / 2.0 - gyroMeas[2] / 2.0) * (dt *
    GNSS_INS_B.d21);
  GNSS_INS_B.d2 = (1.0 - gyroBiasDecayFactor) * dt - 1.0;
  x[4] = GNSS_INS_B.d2 * -GNSS_INS_B.d23;
  x[5] = GNSS_INS_B.d2 * -GNSS_INS_B.d24;
  x[6] = GNSS_INS_B.d2 * -GNSS_INS_B.d25;
  x[7] = dt * GNSS_INS_B.d27 + GNSS_INS_B.d26;
  x[8] = dt * GNSS_INS_B.d29 + GNSS_INS_B.d28;
  x[9] = dt * GNSS_INS_B.d31 + GNSS_INS_B.d30;
  x[10] = ((((((GNSS_INS_B.d35 - accelMeas[0]) * GNSS_INS_B.d34 -
               (GNSS_INS_B.d37 - accelMeas[1]) * GNSS_INS_B.d36) +
              (GNSS_INS_B.d39 - accelMeas[2]) * GNSS_INS_B.d38) * GNSS_INS_B.d33
             + (((GNSS_INS_B.d42 - accelMeas[1]) * GNSS_INS_B.d41 -
                 (GNSS_INS_B.d44 - accelMeas[0]) * GNSS_INS_B.d43) +
                (GNSS_INS_B.d46 - accelMeas[2]) * GNSS_INS_B.d45) *
             GNSS_INS_B.d40) + (((GNSS_INS_B.d49 - accelMeas[0]) *
              GNSS_INS_B.d48 + (GNSS_INS_B.d51 - accelMeas[1]) * GNSS_INS_B.d50)
             + (GNSS_INS_B.d53 - accelMeas[2]) * GNSS_INS_B.d52) *
            GNSS_INS_B.d47) - (((GNSS_INS_B.d56 - accelMeas[0]) * GNSS_INS_B.d55
             + (GNSS_INS_B.d58 - accelMeas[1]) * GNSS_INS_B.d57) -
            (GNSS_INS_B.d60 - accelMeas[2]) * GNSS_INS_B.d59) * GNSS_INS_B.d54) *
    dt + GNSS_INS_B.d32;
  x[11] = ((((((GNSS_INS_B.d64 - accelMeas[0]) * GNSS_INS_B.d63 +
               (GNSS_INS_B.d66 - accelMeas[1]) * GNSS_INS_B.d65) -
              (GNSS_INS_B.d68 - accelMeas[2]) * GNSS_INS_B.d67) * GNSS_INS_B.d62
             - (((GNSS_INS_B.d71 - accelMeas[1]) * GNSS_INS_B.d70 -
                 (GNSS_INS_B.d73 - accelMeas[0]) * GNSS_INS_B.d72) +
                (GNSS_INS_B.d75 - accelMeas[2]) * GNSS_INS_B.d74) *
             GNSS_INS_B.d69) + (((GNSS_INS_B.d78 - accelMeas[0]) *
              GNSS_INS_B.d77 + (GNSS_INS_B.d80 - accelMeas[1]) * GNSS_INS_B.d79)
             + (GNSS_INS_B.d82 - accelMeas[2]) * GNSS_INS_B.d81) *
            GNSS_INS_B.d76) + (((GNSS_INS_B.d85 - accelMeas[0]) * GNSS_INS_B.d84
             - (GNSS_INS_B.d87 - accelMeas[1]) * GNSS_INS_B.d86) +
            (GNSS_INS_B.d89 - accelMeas[2]) * GNSS_INS_B.d88) * GNSS_INS_B.d83) *
    dt + GNSS_INS_B.d61;
  x[12] = (((((((GNSS_INS_B.d93 - accelMeas[1]) * GNSS_INS_B.d92 -
                (GNSS_INS_B.d95 - accelMeas[0]) * GNSS_INS_B.d94) +
               (GNSS_INS_B.d97 - accelMeas[2]) * GNSS_INS_B.d96) *
              GNSS_INS_B.d91 - 9.81) + (((GNSS_INS_B.d100 - accelMeas[0]) *
    GNSS_INS_B.d99 + (GNSS_INS_B.d102 - accelMeas[1]) * GNSS_INS_B.d101) -
              (GNSS_INS_B.d104 - accelMeas[2]) * GNSS_INS_B.d103) *
             GNSS_INS_B.d98) - (((GNSS_INS_B.d107 - accelMeas[0]) *
              GNSS_INS_B.d106 - (GNSS_INS_B.d109 - accelMeas[1]) *
              GNSS_INS_B.d108) + (GNSS_INS_B.d111 - accelMeas[2]) *
             GNSS_INS_B.d110) * GNSS_INS_B.d105) + (((GNSS_INS_B.d114 -
              accelMeas[0]) * GNSS_INS_B.d113 + (GNSS_INS_B.d116 - accelMeas[1])
             * GNSS_INS_B.d115) + (GNSS_INS_B.d118 - accelMeas[2]) *
            GNSS_INS_B.d117) * GNSS_INS_B.d112) * dt + GNSS_INS_B.d90;
  GNSS_INS_B.d2 = (1.0 - accelBiasDecayFactor) * dt - 1.0;
  x[13] = GNSS_INS_B.d2 * -GNSS_INS_B.d119;
  x[14] = GNSS_INS_B.d2 * -tmp;
  x[15] = GNSS_INS_B.d2 * -tmp_0;
  GN_IMUBasicEKF_repairQuaternion(x);
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_st(const real_T x[16], real_T dt, const
  real_T accelMeas[3], const real_T gyroMeas[3], real_T accelBiasDecayFactor,
  real_T gyroBiasDecayFactor, real_T F[256])
{
  real_T F_tmp;
  real_T F_tmp_tmp;
  real_T F_tmp_0;
  real_T F_tmp_1;
  F[0] = 1.0;
  GNSS_INS_B.F_tmp = x[4] / 2.0 - gyroMeas[0] / 2.0;
  GNSS_INS_B.F_tmp_bn = GNSS_INS_B.F_tmp * dt;
  F[16] = GNSS_INS_B.F_tmp_bn;
  GNSS_INS_B.F_tmp_tmp = x[5] / 2.0 - gyroMeas[1] / 2.0;
  GNSS_INS_B.F_tmp_o = GNSS_INS_B.F_tmp_tmp * dt;
  F[32] = GNSS_INS_B.F_tmp_o;
  GNSS_INS_B.F_tmp_l = x[6] / 2.0 - gyroMeas[2] / 2.0;
  GNSS_INS_B.F_tmp_bs = GNSS_INS_B.F_tmp_l * dt;
  F[48] = GNSS_INS_B.F_tmp_bs;
  F_tmp_tmp = dt * x[1];
  GNSS_INS_B.F_tmp_h = F_tmp_tmp / 2.0;
  F[64] = GNSS_INS_B.F_tmp_h;
  GNSS_INS_B.F_tmp_n = dt * x[2];
  F_tmp = GNSS_INS_B.F_tmp_n / 2.0;
  F[80] = F_tmp;
  GNSS_INS_B.F_tmp_tmp_l = dt * x[3];
  GNSS_INS_B.F_tmp_b = GNSS_INS_B.F_tmp_tmp_l / 2.0;
  F[96] = GNSS_INS_B.F_tmp_b;
  F[112] = 0.0;
  F[128] = 0.0;
  F[144] = 0.0;
  F[160] = 0.0;
  F[176] = 0.0;
  F[192] = 0.0;
  F[208] = 0.0;
  F[224] = 0.0;
  F[240] = 0.0;
  GNSS_INS_B.F_tmp *= -dt;
  F[1] = GNSS_INS_B.F_tmp;
  F[17] = 1.0;
  GNSS_INS_B.F_tmp_l *= -dt;
  F[33] = GNSS_INS_B.F_tmp_l;
  F[49] = GNSS_INS_B.F_tmp_o;
  GNSS_INS_B.F_tmp_o = -(dt * x[0]) / 2.0;
  F[65] = GNSS_INS_B.F_tmp_o;
  F[81] = GNSS_INS_B.F_tmp_b;
  F[97] = -GNSS_INS_B.F_tmp_n / 2.0;
  F[113] = 0.0;
  F[129] = 0.0;
  F[145] = 0.0;
  F[161] = 0.0;
  F[177] = 0.0;
  F[193] = 0.0;
  F[209] = 0.0;
  F[225] = 0.0;
  F[241] = 0.0;
  GNSS_INS_B.F_tmp_n = GNSS_INS_B.F_tmp_tmp * -dt;
  F[2] = GNSS_INS_B.F_tmp_n;
  F[18] = GNSS_INS_B.F_tmp_bs;
  F[34] = 1.0;
  F[50] = GNSS_INS_B.F_tmp;
  F[66] = -GNSS_INS_B.F_tmp_tmp_l / 2.0;
  F[82] = GNSS_INS_B.F_tmp_o;
  F[98] = GNSS_INS_B.F_tmp_h;
  F[114] = 0.0;
  F[130] = 0.0;
  F[146] = 0.0;
  F[162] = 0.0;
  F[178] = 0.0;
  F[194] = 0.0;
  F[210] = 0.0;
  F[226] = 0.0;
  F[242] = 0.0;
  F[3] = GNSS_INS_B.F_tmp_l;
  F[19] = GNSS_INS_B.F_tmp_n;
  F[35] = GNSS_INS_B.F_tmp_bn;
  F[51] = 1.0;
  F[67] = F_tmp;
  F[83] = -F_tmp_tmp / 2.0;
  F[99] = GNSS_INS_B.F_tmp_o;
  F[115] = 0.0;
  F[131] = 0.0;
  F[147] = 0.0;
  F[163] = 0.0;
  F[179] = 0.0;
  F[195] = 0.0;
  F[211] = 0.0;
  F[227] = 0.0;
  F[243] = 0.0;
  F[4] = 0.0;
  F[20] = 0.0;
  F[36] = 0.0;
  F[52] = 0.0;
  GNSS_INS_B.F_tmp = 1.0 - (1.0 - gyroBiasDecayFactor) * dt;
  F[68] = GNSS_INS_B.F_tmp;
  F[84] = 0.0;
  F[100] = 0.0;
  F[116] = 0.0;
  F[132] = 0.0;
  F[148] = 0.0;
  F[164] = 0.0;
  F[180] = 0.0;
  F[196] = 0.0;
  F[212] = 0.0;
  F[228] = 0.0;
  F[244] = 0.0;
  F[5] = 0.0;
  F[21] = 0.0;
  F[37] = 0.0;
  F[53] = 0.0;
  F[69] = 0.0;
  F[85] = GNSS_INS_B.F_tmp;
  F[101] = 0.0;
  F[117] = 0.0;
  F[133] = 0.0;
  F[149] = 0.0;
  F[165] = 0.0;
  F[181] = 0.0;
  F[197] = 0.0;
  F[213] = 0.0;
  F[229] = 0.0;
  F[245] = 0.0;
  F[6] = 0.0;
  F[22] = 0.0;
  F[38] = 0.0;
  F[54] = 0.0;
  F[70] = 0.0;
  F[86] = 0.0;
  F[102] = GNSS_INS_B.F_tmp;
  F[118] = 0.0;
  F[134] = 0.0;
  F[150] = 0.0;
  F[166] = 0.0;
  F[182] = 0.0;
  F[198] = 0.0;
  F[214] = 0.0;
  F[230] = 0.0;
  F[246] = 0.0;
  F[7] = 0.0;
  F[23] = 0.0;
  F[39] = 0.0;
  F[55] = 0.0;
  F[71] = 0.0;
  F[87] = 0.0;
  F[103] = 0.0;
  F[119] = 1.0;
  F[135] = 0.0;
  F[151] = 0.0;
  F[167] = dt;
  F[183] = 0.0;
  F[199] = 0.0;
  F[215] = 0.0;
  F[231] = 0.0;
  F[247] = 0.0;
  F[8] = 0.0;
  F[24] = 0.0;
  F[40] = 0.0;
  F[56] = 0.0;
  F[72] = 0.0;
  F[88] = 0.0;
  F[104] = 0.0;
  F[120] = 0.0;
  F[136] = 1.0;
  F[152] = 0.0;
  F[168] = 0.0;
  F[184] = dt;
  F[200] = 0.0;
  F[216] = 0.0;
  F[232] = 0.0;
  F[248] = 0.0;
  F[9] = 0.0;
  F[25] = 0.0;
  F[41] = 0.0;
  F[57] = 0.0;
  F[73] = 0.0;
  F[89] = 0.0;
  F[105] = 0.0;
  F[121] = 0.0;
  F[137] = 0.0;
  F[153] = 1.0;
  F[169] = 0.0;
  F[185] = 0.0;
  F[201] = dt;
  F[217] = 0.0;
  F[233] = 0.0;
  F[249] = 0.0;
  GNSS_INS_B.F_tmp = x[13] - accelMeas[0];
  GNSS_INS_B.F_tmp_bn = x[14] - accelMeas[1];
  GNSS_INS_B.F_tmp_o = x[15] - accelMeas[2];
  GNSS_INS_B.F_tmp_tmp = (2.0 * x[0] * GNSS_INS_B.F_tmp - 2.0 * x[3] *
    GNSS_INS_B.F_tmp_bn) + 2.0 * x[2] * GNSS_INS_B.F_tmp_o;
  GNSS_INS_B.F_tmp_l = GNSS_INS_B.F_tmp_tmp * dt;
  F[10] = GNSS_INS_B.F_tmp_l;
  GNSS_INS_B.F_tmp_bs = ((2.0 * x[1] * GNSS_INS_B.F_tmp + 2.0 * x[2] *
    GNSS_INS_B.F_tmp_bn) + 2.0 * x[3] * GNSS_INS_B.F_tmp_o) * dt;
  F[26] = GNSS_INS_B.F_tmp_bs;
  GNSS_INS_B.F_tmp_h = (2.0 * x[1] * GNSS_INS_B.F_tmp_bn - 2.0 * x[2] *
                        GNSS_INS_B.F_tmp) + 2.0 * x[0] * GNSS_INS_B.F_tmp_o;
  GNSS_INS_B.F_tmp_n = GNSS_INS_B.F_tmp_h * dt;
  F[42] = GNSS_INS_B.F_tmp_n;
  GNSS_INS_B.F_tmp = (2.0 * x[3] * GNSS_INS_B.F_tmp + 2.0 * x[0] *
                      GNSS_INS_B.F_tmp_bn) - 2.0 * x[1] * GNSS_INS_B.F_tmp_o;
  F[58] = GNSS_INS_B.F_tmp * -dt;
  F[74] = 0.0;
  F[90] = 0.0;
  F[106] = 0.0;
  F[122] = 0.0;
  F[138] = 0.0;
  F[154] = 0.0;
  F[170] = 1.0;
  F[186] = 0.0;
  F[202] = 0.0;
  GNSS_INS_B.F_tmp_bn = x[0] * x[0];
  GNSS_INS_B.F_tmp_o = x[1] * x[1];
  F_tmp = x[2] * x[2];
  GNSS_INS_B.F_tmp_b = x[3] * x[3];
  F[218] = (((GNSS_INS_B.F_tmp_bn + GNSS_INS_B.F_tmp_o) - F_tmp) -
            GNSS_INS_B.F_tmp_b) * dt;
  F_tmp_tmp = 2.0 * x[0] * x[3];
  GNSS_INS_B.F_tmp_tmp_l = 2.0 * x[1] * x[2];
  F[234] = (F_tmp_tmp - GNSS_INS_B.F_tmp_tmp_l) * -dt;
  F_tmp_0 = 2.0 * x[0] * x[2];
  F_tmp_1 = 2.0 * x[1] * x[3];
  F[250] = (F_tmp_0 + F_tmp_1) * dt;
  GNSS_INS_B.F_tmp *= dt;
  F[11] = GNSS_INS_B.F_tmp;
  F[27] = GNSS_INS_B.F_tmp_h * -dt;
  F[43] = GNSS_INS_B.F_tmp_bs;
  F[59] = GNSS_INS_B.F_tmp_l;
  F[75] = 0.0;
  F[91] = 0.0;
  F[107] = 0.0;
  F[123] = 0.0;
  F[139] = 0.0;
  F[155] = 0.0;
  F[171] = 0.0;
  F[187] = 1.0;
  F[203] = 0.0;
  F[219] = (F_tmp_tmp + GNSS_INS_B.F_tmp_tmp_l) * dt;
  GNSS_INS_B.F_tmp_bn -= GNSS_INS_B.F_tmp_o;
  F[235] = ((GNSS_INS_B.F_tmp_bn + F_tmp) - GNSS_INS_B.F_tmp_b) * dt;
  GNSS_INS_B.F_tmp_o = 2.0 * x[0] * x[1];
  GNSS_INS_B.F_tmp_l = 2.0 * x[2] * x[3];
  F[251] = (GNSS_INS_B.F_tmp_o - GNSS_INS_B.F_tmp_l) * -dt;
  F[12] = GNSS_INS_B.F_tmp_n;
  F[28] = GNSS_INS_B.F_tmp;
  F[44] = GNSS_INS_B.F_tmp_tmp * -dt;
  F[60] = GNSS_INS_B.F_tmp_bs;
  F[76] = 0.0;
  F[92] = 0.0;
  F[108] = 0.0;
  F[124] = 0.0;
  F[140] = 0.0;
  F[156] = 0.0;
  F[172] = 0.0;
  F[188] = 0.0;
  F[204] = 1.0;
  F[220] = (F_tmp_0 - F_tmp_1) * -dt;
  F[236] = (GNSS_INS_B.F_tmp_o + GNSS_INS_B.F_tmp_l) * dt;
  F[252] = ((GNSS_INS_B.F_tmp_bn - F_tmp) + GNSS_INS_B.F_tmp_b) * dt;
  F[13] = 0.0;
  F[29] = 0.0;
  F[45] = 0.0;
  F[61] = 0.0;
  F[77] = 0.0;
  F[93] = 0.0;
  F[109] = 0.0;
  F[125] = 0.0;
  F[141] = 0.0;
  F[157] = 0.0;
  F[173] = 0.0;
  F[189] = 0.0;
  F[205] = 0.0;
  GNSS_INS_B.F_tmp = 1.0 - (1.0 - accelBiasDecayFactor) * dt;
  F[221] = GNSS_INS_B.F_tmp;
  F[237] = 0.0;
  F[253] = 0.0;
  F[14] = 0.0;
  F[30] = 0.0;
  F[46] = 0.0;
  F[62] = 0.0;
  F[78] = 0.0;
  F[94] = 0.0;
  F[110] = 0.0;
  F[126] = 0.0;
  F[142] = 0.0;
  F[158] = 0.0;
  F[174] = 0.0;
  F[190] = 0.0;
  F[206] = 0.0;
  F[222] = 0.0;
  F[238] = GNSS_INS_B.F_tmp;
  F[254] = 0.0;
  F[15] = 0.0;
  F[31] = 0.0;
  F[47] = 0.0;
  F[63] = 0.0;
  F[79] = 0.0;
  F[95] = 0.0;
  F[111] = 0.0;
  F[127] = 0.0;
  F[143] = 0.0;
  F[159] = 0.0;
  F[175] = 0.0;
  F[191] = 0.0;
  F[207] = 0.0;
  F[223] = 0.0;
  F[239] = 0.0;
  F[255] = GNSS_INS_B.F_tmp;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase__h(const real_T x[16], real_T dt,
  real_T G[192])
{
  int32_T i;
  real_T G_tmp;
  real_T G_tmp_tmp;
  real_T G_tmp_0;
  int32_T G_tmp_1;
  G_tmp_tmp = dt * x[1];
  GNSS_INS_B.G_tmp_i = -G_tmp_tmp / 2.0;
  G[0] = GNSS_INS_B.G_tmp_i;
  GNSS_INS_B.G_tmp_o = dt * x[2];
  G_tmp = -GNSS_INS_B.G_tmp_o / 2.0;
  G[16] = G_tmp;
  GNSS_INS_B.G_tmp_tmp = dt * x[3];
  GNSS_INS_B.G_tmp = -GNSS_INS_B.G_tmp_tmp / 2.0;
  G[32] = GNSS_INS_B.G_tmp;
  G[48] = 0.0;
  G[64] = 0.0;
  G[80] = 0.0;
  G[96] = 0.0;
  G[112] = 0.0;
  G[128] = 0.0;
  G[144] = 0.0;
  G[160] = 0.0;
  G[176] = 0.0;
  GNSS_INS_B.G_tmp_n = dt * x[0] / 2.0;
  G[1] = GNSS_INS_B.G_tmp_n;
  G[17] = GNSS_INS_B.G_tmp;
  G[33] = GNSS_INS_B.G_tmp_o / 2.0;
  G[49] = 0.0;
  G[65] = 0.0;
  G[81] = 0.0;
  G[97] = 0.0;
  G[113] = 0.0;
  G[129] = 0.0;
  G[145] = 0.0;
  G[161] = 0.0;
  G[177] = 0.0;
  G[2] = GNSS_INS_B.G_tmp_tmp / 2.0;
  G[18] = GNSS_INS_B.G_tmp_n;
  G[34] = GNSS_INS_B.G_tmp_i;
  G[50] = 0.0;
  G[66] = 0.0;
  G[82] = 0.0;
  G[98] = 0.0;
  G[114] = 0.0;
  G[130] = 0.0;
  G[146] = 0.0;
  G[162] = 0.0;
  G[178] = 0.0;
  G[3] = G_tmp;
  G[19] = G_tmp_tmp / 2.0;
  G[35] = GNSS_INS_B.G_tmp_n;
  G[51] = 0.0;
  G[67] = 0.0;
  G[83] = 0.0;
  G[99] = 0.0;
  G[115] = 0.0;
  G[131] = 0.0;
  G[147] = 0.0;
  G[163] = 0.0;
  G[179] = 0.0;
  G[10] = 0.0;
  G[26] = 0.0;
  G[42] = 0.0;
  G[58] = 0.0;
  G[74] = 0.0;
  G[90] = 0.0;
  GNSS_INS_B.G_tmp_i = x[0] * x[0];
  GNSS_INS_B.G_tmp_o = x[1] * x[1];
  G_tmp = x[2] * x[2];
  GNSS_INS_B.G_tmp = x[3] * x[3];
  G[106] = (((GNSS_INS_B.G_tmp_i + GNSS_INS_B.G_tmp_o) - G_tmp) -
            GNSS_INS_B.G_tmp) * -dt;
  GNSS_INS_B.G_tmp_n = 2.0 * x[0] * x[3];
  G_tmp_tmp = 2.0 * x[1] * x[2];
  G[122] = (GNSS_INS_B.G_tmp_n - G_tmp_tmp) * dt;
  GNSS_INS_B.G_tmp_tmp = 2.0 * x[0] * x[2];
  G_tmp_0 = 2.0 * x[1] * x[3];
  G[138] = (GNSS_INS_B.G_tmp_tmp + G_tmp_0) * -dt;
  G[154] = 0.0;
  G[170] = 0.0;
  G[186] = 0.0;
  G[11] = 0.0;
  G[27] = 0.0;
  G[43] = 0.0;
  G[59] = 0.0;
  G[75] = 0.0;
  G[91] = 0.0;
  G[107] = (GNSS_INS_B.G_tmp_n + G_tmp_tmp) * -dt;
  GNSS_INS_B.G_tmp_i -= GNSS_INS_B.G_tmp_o;
  G[123] = ((GNSS_INS_B.G_tmp_i + G_tmp) - GNSS_INS_B.G_tmp) * -dt;
  GNSS_INS_B.G_tmp_o = 2.0 * x[0] * x[1];
  GNSS_INS_B.G_tmp_n = 2.0 * x[2] * x[3];
  G[139] = (GNSS_INS_B.G_tmp_o - GNSS_INS_B.G_tmp_n) * dt;
  G[155] = 0.0;
  G[171] = 0.0;
  G[187] = 0.0;
  G[12] = 0.0;
  G[28] = 0.0;
  G[44] = 0.0;
  G[60] = 0.0;
  G[76] = 0.0;
  G[92] = 0.0;
  G[108] = (GNSS_INS_B.G_tmp_tmp - G_tmp_0) * dt;
  G[124] = (GNSS_INS_B.G_tmp_o + GNSS_INS_B.G_tmp_n) * -dt;
  G[140] = ((GNSS_INS_B.G_tmp_i - G_tmp) + GNSS_INS_B.G_tmp) * -dt;
  G[156] = 0.0;
  G[172] = 0.0;
  G[188] = 0.0;
  for (i = 0; i < 12; i++) {
    G_tmp_1 = i << 4;
    G[G_tmp_1 + 4] = 0.0;
    G[G_tmp_1 + 5] = 0.0;
    G[G_tmp_1 + 6] = 0.0;
    G[G_tmp_1 + 7] = 0.0;
    G[G_tmp_1 + 8] = 0.0;
    G[G_tmp_1 + 9] = 0.0;
    G[G_tmp_1 + 13] = 0.0;
    G[G_tmp_1 + 14] = 0.0;
    G[G_tmp_1 + 15] = 0.0;
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase__d(const
  c_fusion_internal_coder_insfi_T *obj, real_T U[144])
{
  int32_T i;
  int32_T U_tmp;
  int32_T U_tmp_0;
  int32_T U_tmp_1;
  int32_T U_tmp_2;
  memset(&GNSS_INS_B.gyroVar[0], 0, 9U * sizeof(real_T));
  memset(&GNSS_INS_B.gyroBiasVar[0], 0, 9U * sizeof(real_T));
  memset(&GNSS_INS_B.accelVar[0], 0, 9U * sizeof(real_T));
  memset(&GNSS_INS_B.accelBiasVar[0], 0, 9U * sizeof(real_T));
  GNSS_INS_B.gyroVar[0] = obj->GyroscopeNoise[0];
  GNSS_INS_B.gyroVar[4] = obj->GyroscopeNoise[1];
  GNSS_INS_B.gyroVar[8] = obj->GyroscopeNoise[2];
  GNSS_INS_B.gyroBiasVar[0] = obj->GyroscopeBiasNoise[0];
  GNSS_INS_B.gyroBiasVar[4] = obj->GyroscopeBiasNoise[1];
  GNSS_INS_B.gyroBiasVar[8] = obj->GyroscopeBiasNoise[2];
  GNSS_INS_B.accelVar[0] = obj->AccelerometerNoise[0];
  GNSS_INS_B.accelVar[4] = obj->AccelerometerNoise[1];
  GNSS_INS_B.accelVar[8] = obj->AccelerometerNoise[2];
  GNSS_INS_B.accelBiasVar[0] = obj->AccelerometerBiasNoise[0];
  GNSS_INS_B.accelBiasVar[4] = obj->AccelerometerBiasNoise[1];
  GNSS_INS_B.accelBiasVar[8] = obj->AccelerometerBiasNoise[2];
  memset(&U[0], 0, 144U * sizeof(real_T));
  for (i = 0; i < 3; i++) {
    U[12 * i] = GNSS_INS_B.gyroVar[3 * i];
    U_tmp_0 = 12 * (i + 3);
    U[U_tmp_0 + 3] = GNSS_INS_B.gyroBiasVar[3 * i];
    U_tmp_1 = 12 * (i + 6);
    U[U_tmp_1 + 6] = GNSS_INS_B.accelVar[3 * i];
    U_tmp_2 = 12 * (i + 9);
    U[U_tmp_2 + 9] = GNSS_INS_B.accelBiasVar[3 * i];
    U_tmp = 3 * i + 1;
    U[12 * i + 1] = GNSS_INS_B.gyroVar[U_tmp];
    U[U_tmp_0 + 4] = GNSS_INS_B.gyroBiasVar[U_tmp];
    U[U_tmp_1 + 7] = GNSS_INS_B.accelVar[U_tmp];
    U[U_tmp_2 + 10] = GNSS_INS_B.accelBiasVar[U_tmp];
    U_tmp = 3 * i + 2;
    U[12 * i + 2] = GNSS_INS_B.gyroVar[U_tmp];
    U[U_tmp_0 + 5] = GNSS_INS_B.gyroBiasVar[U_tmp];
    U[U_tmp_1 + 8] = GNSS_INS_B.accelVar[U_tmp];
    U[U_tmp_2 + 11] = GNSS_INS_B.accelBiasVar[U_tmp];
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_me(const real_T x[16], real_T h[2])
{
  real_T h_tmp;
  real_T h_tmp_0;
  real_T h_tmp_1;
  real_T h_tmp_2;
  h_tmp = (x[0] * x[12] - x[1] * x[11]) + x[2] * x[10];
  h_tmp_0 = (x[1] * x[12] + x[0] * x[11]) - x[3] * x[10];
  h_tmp_1 = (x[3] * x[11] - x[2] * x[12]) + x[0] * x[10];
  h_tmp_2 = (x[3] * x[12] + x[2] * x[11]) + x[1] * x[10];
  h[0] = ((h_tmp_0 * x[0] + h_tmp * x[1]) + h_tmp_2 * x[2]) - h_tmp_1 * x[3];
  h[1] = ((h_tmp * x[0] - h_tmp_0 * x[1]) + h_tmp_1 * x[2]) + h_tmp_2 * x[3];
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase__g(const real_T x[16], real_T H[32])
{
  real_T H_tmp;
  real_T H_tmp_0;
  real_T H_tmp_1;
  real_T H_tmp_2;
  GNSS_INS_B.H_tmp_d = 2.0 * x[3] * x[10];
  GNSS_INS_B.H_tmp_e = 2.0 * x[0] * x[11];
  GNSS_INS_B.H_tmp_b = 2.0 * x[1] * x[12];
  H[0] = (GNSS_INS_B.H_tmp_b + GNSS_INS_B.H_tmp_e) - GNSS_INS_B.H_tmp_d;
  GNSS_INS_B.H_tmp = (2.0 * x[0] * x[12] - 2.0 * x[1] * x[11]) + 2.0 * x[2] * x
    [10];
  H[2] = GNSS_INS_B.H_tmp;
  GNSS_INS_B.H_tmp_ju = (2.0 * x[3] * x[12] + 2.0 * x[2] * x[11]) + 2.0 * x[1] *
    x[10];
  H[4] = GNSS_INS_B.H_tmp_ju;
  GNSS_INS_B.H_tmp_j = 2.0 * x[3] * x[11];
  GNSS_INS_B.H_tmp_f = 2.0 * x[2] * x[12];
  GNSS_INS_B.H_tmp_a = 2.0 * x[0] * x[10];
  H[6] = (GNSS_INS_B.H_tmp_f - GNSS_INS_B.H_tmp_j) - GNSS_INS_B.H_tmp_a;
  H[8] = 0.0;
  H[10] = 0.0;
  H[12] = 0.0;
  H[14] = 0.0;
  H[16] = 0.0;
  H[18] = 0.0;
  H[20] = 2.0 * x[1] * x[2] - 2.0 * x[0] * x[3];
  H_tmp_0 = x[0] * x[0] - x[1] * x[1];
  H_tmp_1 = x[2] * x[2];
  H_tmp_2 = x[3] * x[3];
  H[22] = (H_tmp_0 + H_tmp_1) - H_tmp_2;
  GNSS_INS_B.H_tmp_jz = 2.0 * x[2] * x[3];
  H_tmp = 2.0 * x[0] * x[1];
  H[24] = H_tmp + GNSS_INS_B.H_tmp_jz;
  H[26] = 0.0;
  H[28] = 0.0;
  H[30] = 0.0;
  H[1] = GNSS_INS_B.H_tmp;
  H[3] = (GNSS_INS_B.H_tmp_d - GNSS_INS_B.H_tmp_e) - GNSS_INS_B.H_tmp_b;
  H[5] = (GNSS_INS_B.H_tmp_j - GNSS_INS_B.H_tmp_f) + GNSS_INS_B.H_tmp_a;
  H[7] = GNSS_INS_B.H_tmp_ju;
  H[9] = 0.0;
  H[11] = 0.0;
  H[13] = 0.0;
  H[15] = 0.0;
  H[17] = 0.0;
  H[19] = 0.0;
  H[21] = 2.0 * x[0] * x[2] + 2.0 * x[1] * x[3];
  H[23] = GNSS_INS_B.H_tmp_jz - H_tmp;
  H[25] = (H_tmp_0 - H_tmp_1) + H_tmp_2;
  H[27] = 0.0;
  H[29] = 0.0;
  H[31] = 0.0;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase__o(const
  c_fusion_internal_coder_insfi_T *obj, real_T R[4])
{
  real_T R_tmp;
  R[0] = obj->ZeroVelocityConstraintNoise;
  R_tmp = obj->ZeroVelocityConstraintNoise * 0.0;
  R[1] = R_tmp;
  R[2] = R_tmp;
  R[3] = obj->ZeroVelocityConstraintNoise;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_IMUBasicEKF_correctEqn(real_T x[16], real_T P[256], const
  real_T h[2], const real_T H[32], const real_T z[2], const real_T R[4])
{
  int32_T r1;
  int32_T r2;
  int32_T W_tmp;
  int32_T y_tmp;
  int32_T W_tmp_0;
  for (r1 = 0; r1 < 2; r1++) {
    for (r2 = 0; r2 < 16; r2++) {
      W_tmp = (r2 << 1) + r1;
      GNSS_INS_B.W_m[r2 + (r1 << 4)] = H[W_tmp];
      GNSS_INS_B.H_n[W_tmp] = 0.0;
      for (W_tmp_0 = 0; W_tmp_0 < 16; W_tmp_0++) {
        GNSS_INS_B.H_n[W_tmp] += H[(W_tmp_0 << 1) + r1] * P[(r2 << 4) + W_tmp_0];
      }
    }
  }

  for (r1 = 0; r1 < 2; r1++) {
    for (r2 = 0; r2 < 2; r2++) {
      GNSS_INS_B.a21 = 0.0;
      for (W_tmp_0 = 0; W_tmp_0 < 16; W_tmp_0++) {
        GNSS_INS_B.a21 += GNSS_INS_B.H_n[(W_tmp_0 << 1) + r2] * GNSS_INS_B.W_m
          [(r1 << 4) + W_tmp_0];
      }

      W_tmp = (r1 << 1) + r2;
      GNSS_INS_B.S[W_tmp] = R[W_tmp] + GNSS_INS_B.a21;
    }

    for (r2 = 0; r2 < 16; r2++) {
      W_tmp = r1 << 4;
      y_tmp = r2 + W_tmp;
      GNSS_INS_B.y[y_tmp] = 0.0;
      for (W_tmp_0 = 0; W_tmp_0 < 16; W_tmp_0++) {
        GNSS_INS_B.y[y_tmp] += P[(W_tmp_0 << 4) + r2] * GNSS_INS_B.W_m[W_tmp +
          W_tmp_0];
      }
    }
  }

  if (fabs(GNSS_INS_B.S[1]) > fabs(GNSS_INS_B.S[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  GNSS_INS_B.a21 = GNSS_INS_B.S[r2] / GNSS_INS_B.S[r1];
  GNSS_INS_B.a22_tmp = GNSS_INS_B.S[r1 + 2];
  GNSS_INS_B.a22 = GNSS_INS_B.S[r2 + 2] - GNSS_INS_B.a22_tmp * GNSS_INS_B.a21;
  for (y_tmp = 0; y_tmp < 16; y_tmp++) {
    W_tmp = y_tmp + (r1 << 4);
    GNSS_INS_B.W_m[W_tmp] = GNSS_INS_B.y[y_tmp] / GNSS_INS_B.S[r1];
    W_tmp_0 = y_tmp + (r2 << 4);
    GNSS_INS_B.W_m[W_tmp_0] = (GNSS_INS_B.y[y_tmp + 16] - GNSS_INS_B.W_m[W_tmp] *
      GNSS_INS_B.a22_tmp) / GNSS_INS_B.a22;
    GNSS_INS_B.W_m[W_tmp] -= GNSS_INS_B.W_m[W_tmp_0] * GNSS_INS_B.a21;
  }

  GNSS_INS_B.a22_tmp = z[0] - h[0];
  GNSS_INS_B.a22 = z[1] - h[1];
  for (r1 = 0; r1 < 16; r1++) {
    GNSS_INS_B.a21 = GNSS_INS_B.W_m[r1 + 16];
    x[r1] += GNSS_INS_B.a21 * GNSS_INS_B.a22 + GNSS_INS_B.W_m[r1] *
      GNSS_INS_B.a22_tmp;
    for (r2 = 0; r2 < 16; r2++) {
      W_tmp = r1 + (r2 << 4);
      GNSS_INS_B.W[W_tmp] = 0.0;
      W_tmp_0 = r2 << 1;
      GNSS_INS_B.W[W_tmp] += H[W_tmp_0] * GNSS_INS_B.W_m[r1];
      GNSS_INS_B.W[W_tmp] += H[W_tmp_0 + 1] * GNSS_INS_B.a21;
    }

    for (r2 = 0; r2 < 16; r2++) {
      GNSS_INS_B.a21 = 0.0;
      for (W_tmp_0 = 0; W_tmp_0 < 16; W_tmp_0++) {
        GNSS_INS_B.a21 += GNSS_INS_B.W[(W_tmp_0 << 4) + r1] * P[(r2 << 4) +
          W_tmp_0];
      }

      W_tmp = (r2 << 4) + r1;
      GNSS_INS_B.P_k[W_tmp] = P[W_tmp] - GNSS_INS_B.a21;
    }
  }

  memcpy(&P[0], &GNSS_INS_B.P_k[0], sizeof(real_T) << 8U);
  GN_IMUBasicEKF_repairQuaternion(x);
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_co(c_fusion_internal_coder_insfi_T *obj)
{
  memcpy(&GNSS_INS_B.x_j[0], &obj->State[0], sizeof(real_T) << 4U);
  memcpy(&GNSS_INS_B.P[0], &obj->StateCovariance[0], sizeof(real_T) << 8U);
  NHConstrainedIMUGPSFuserBase_me(obj->State, GNSS_INS_B.h_l);
  NHConstrainedIMUGPSFuserBase__g(obj->State, GNSS_INS_B.H_g1);
  NHConstrainedIMUGPSFuserBase__o(obj, GNSS_INS_B.R);
  GNSS_INS_B.dv5[0] = 0.0;
  GNSS_INS_B.dv5[1] = 0.0;
  GNSS_INS_IMUBasicEKF_correctEqn(GNSS_INS_B.x_j, GNSS_INS_B.P, GNSS_INS_B.h_l,
    GNSS_INS_B.H_g1, GNSS_INS_B.dv5, GNSS_INS_B.R);
  memcpy(&obj->StateCovariance[0], &GNSS_INS_B.P[0], sizeof(real_T) << 8U);
  memcpy(&obj->State[0], &GNSS_INS_B.x_j[0], sizeof(real_T) << 4U);
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_pr(c_fusion_internal_coder_insfi_T *obj,
  const real_T accelMeas[3], const real_T gyroMeas[3])
{
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T F_tmp;
  int32_T F_tmp_0;
  GNSS_INS_B.dt = 1.0 / obj->IMUSampleRate;
  GNSS_INS_B.accelBiasDecayFactor = obj->AccelerometerBiasDecayFactor;
  GNSS_INS_B.gyroBiasDecayFactor = obj->GyroscopeBiasDecayFactor;
  memcpy(&GNSS_INS_B.x[0], &obj->State[0], sizeof(real_T) << 4U);
  NHConstrainedIMUGPSFuserBase_hu(obj->State, GNSS_INS_B.dt, accelMeas, gyroMeas,
    obj->AccelerometerBiasDecayFactor, obj->GyroscopeBiasDecayFactor);
  NHConstrainedIMUGPSFuserBase_st(GNSS_INS_B.x, GNSS_INS_B.dt, accelMeas,
    gyroMeas, GNSS_INS_B.accelBiasDecayFactor, GNSS_INS_B.gyroBiasDecayFactor,
    GNSS_INS_B.F);
  NHConstrainedIMUGPSFuserBase__h(GNSS_INS_B.x, GNSS_INS_B.dt, GNSS_INS_B.G);
  NHConstrainedIMUGPSFuserBase__d(obj, GNSS_INS_B.U);
  for (i = 0; i < 16; i++) {
    for (i_0 = 0; i_0 < 16; i_0++) {
      F_tmp = i_0 << 4;
      F_tmp_0 = i + F_tmp;
      GNSS_INS_B.F_m[F_tmp_0] = 0.0;
      for (i_1 = 0; i_1 < 16; i_1++) {
        GNSS_INS_B.F_m[F_tmp_0] += GNSS_INS_B.F[(i_1 << 4) + i] *
          obj->StateCovariance[F_tmp + i_1];
      }
    }

    for (i_0 = 0; i_0 < 12; i_0++) {
      F_tmp = i + (i_0 << 4);
      GNSS_INS_B.G_c[F_tmp] = 0.0;
      for (i_1 = 0; i_1 < 12; i_1++) {
        GNSS_INS_B.G_c[F_tmp] += GNSS_INS_B.G[(i_1 << 4) + i] * GNSS_INS_B.U[12 *
          i_0 + i_1];
      }
    }

    for (i_0 = 0; i_0 < 16; i_0++) {
      F_tmp = i + (i_0 << 4);
      GNSS_INS_B.F_c[F_tmp] = 0.0;
      for (i_1 = 0; i_1 < 16; i_1++) {
        F_tmp_0 = i_1 << 4;
        GNSS_INS_B.F_c[F_tmp] += GNSS_INS_B.F_m[F_tmp_0 + i] *
          GNSS_INS_B.F[F_tmp_0 + i_0];
      }
    }
  }

  for (i = 0; i < 16; i++) {
    for (i_0 = 0; i_0 < 16; i_0++) {
      F_tmp = i + (i_0 << 4);
      GNSS_INS_B.F[F_tmp] = 0.0;
      for (i_1 = 0; i_1 < 12; i_1++) {
        F_tmp_0 = i_1 << 4;
        GNSS_INS_B.F[F_tmp] += GNSS_INS_B.G_c[F_tmp_0 + i] *
          GNSS_INS_B.G[F_tmp_0 + i_0];
      }
    }
  }

  for (i = 0; i < 256; i++) {
    obj->StateCovariance[i] = GNSS_INS_B.F_c[i] + GNSS_INS_B.F[i];
  }

  if (obj->applyConstraintCount > 2147483646) {
    obj->applyConstraintCount = MAX_int32_T;
  } else {
    obj->applyConstraintCount++;
  }

  if (obj->applyConstraintCount == obj->DecimationFactor) {
    NHConstrainedIMUGPSFuserBase_co(obj);
    obj->applyConstraintCount = 0;
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void IMUBasicEKF_validateExpandNoise(real_T Rin, real_T Rout[9])
{
  memset(&Rout[0], 0, 9U * sizeof(real_T));
  Rout[0] = Rin;
  Rout[4] = Rin;
  Rout[8] = Rin;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(static_cast<real_T>(u0_0), static_cast<real_T>(u1_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_hv(const real_T x[16], real_T h[4])
{
  h[0] = x[7];
  h[1] = x[8];
  h[2] = x[9];
  h[3] = rt_atan2d_snf(x[0] * x[3] * 2.0 + x[1] * x[2] * 2.0, (x[0] * x[0] * 2.0
    - 1.0) + x[1] * x[1] * 2.0);
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase__m(const real_T x[16], real_T H[64])
{
  int32_T i;
  real_T a_tmp;
  real_T d_a_tmp;
  int32_T H_tmp;
  static const int8_T b[16] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T c[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };

  static const int8_T d[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };

  a_tmp = (x[0] * x[0] * 2.0 + x[1] * x[1] * 2.0) - 1.0;
  d_a_tmp = 2.0 * x[0] * x[3] + 2.0 * x[1] * x[2];
  for (i = 0; i < 16; i++) {
    H_tmp = i << 2;
    H[H_tmp] = b[i];
    H[H_tmp + 1] = c[i];
    H[H_tmp + 2] = d[i];
  }

  H[3] = (2.0 * x[3] / a_tmp - d_a_tmp * (4.0 * x[0]) / (a_tmp * a_tmp)) *
    (a_tmp * a_tmp) / (a_tmp * a_tmp + d_a_tmp * d_a_tmp);
  H[7] = (2.0 * x[2] / a_tmp - d_a_tmp * (4.0 * x[1]) / (a_tmp * a_tmp)) *
    (a_tmp * a_tmp) / (a_tmp * a_tmp + d_a_tmp * d_a_tmp);
  H[11] = a_tmp * (2.0 * x[1]) / (a_tmp * a_tmp + d_a_tmp * d_a_tmp);
  H[15] = a_tmp * (2.0 * x[0]) / (a_tmp * a_tmp + d_a_tmp * d_a_tmp);
  H[19] = 0.0;
  H[23] = 0.0;
  H[27] = 0.0;
  H[31] = 0.0;
  H[35] = 0.0;
  H[39] = 0.0;
  H[43] = 0.0;
  H[47] = 0.0;
  H[51] = 0.0;
  H[55] = 0.0;
  H[59] = 0.0;
  H[63] = 0.0;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_ve(const real_T vel[3], const real_T
  velR[9], real_T *course, real_T *courseR)
{
  real_T groundspeed;
  real_T groundspeedR;
  real_T scale;
  real_T absxk;
  real_T t;
  groundspeed = sqrt(vel[0] * vel[0] + vel[1] * vel[1]);
  scale = 3.3121686421112381E-170;
  absxk = fabs(velR[0]);
  if (absxk > 3.3121686421112381E-170) {
    groundspeedR = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    groundspeedR = t * t;
  }

  absxk = fabs(velR[1]);
  if (absxk > scale) {
    t = scale / absxk;
    groundspeedR = groundspeedR * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    groundspeedR += t * t;
  }

  absxk = fabs(velR[3]);
  if (absxk > scale) {
    t = scale / absxk;
    groundspeedR = groundspeedR * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    groundspeedR += t * t;
  }

  absxk = fabs(velR[4]);
  if (absxk > scale) {
    t = scale / absxk;
    groundspeedR = groundspeedR * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    groundspeedR += t * t;
  }

  groundspeedR = scale * sqrt(groundspeedR);
  *courseR = groundspeedR / (groundspeed * groundspeed);
  *course = rt_atan2d_snf(vel[1], vel[0]);
  if (*course < 0.0) {
    *course += 6.2831853071795862;
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_ad(real_T *zCourse, real_T hCourse)
{
  if (*zCourse - hCourse > 3.1415926535897931) {
    *zCourse -= 6.2831853071795862;
  }
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = fabs(u0 / u1);
      if (fabs(u1_0 - floor(u1_0 + 0.5)) <= DBL_EPSILON * u1_0) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_cosd(real_T *x)
{
  int8_T n;
  real_T b_x;
  real_T absx;
  if (rtIsInf(*x) || rtIsNaN(*x)) {
    *x = (rtNaN);
  } else {
    b_x = rt_remd_snf(*x, 360.0);
    absx = fabs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = fabs(b_x);
    }

    if (absx <= 45.0) {
      b_x *= 0.017453292519943295;
      *x = cos(b_x);
    } else {
      if (absx <= 135.0) {
        if (b_x > 0.0) {
          b_x = (b_x - 90.0) * 0.017453292519943295;
          n = 1;
        } else {
          b_x = (b_x + 90.0) * 0.017453292519943295;
          n = -1;
        }
      } else if (b_x > 0.0) {
        b_x = (b_x - 180.0) * 0.017453292519943295;
        n = 2;
      } else {
        b_x = (b_x + 180.0) * 0.017453292519943295;
        n = -2;
      }

      if (n == 1) {
        *x = -sin(b_x);
      } else if (n == -1) {
        *x = sin(b_x);
      } else {
        *x = -cos(b_x);
      }
    }
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_sind(real_T *x)
{
  int8_T n;
  real_T c_x;
  real_T absx;
  if (rtIsInf(*x) || rtIsNaN(*x)) {
    *x = (rtNaN);
  } else {
    c_x = rt_remd_snf(*x, 360.0);
    absx = fabs(c_x);
    if (absx > 180.0) {
      if (c_x > 0.0) {
        c_x -= 360.0;
      } else {
        c_x += 360.0;
      }

      absx = fabs(c_x);
    }

    if (absx <= 45.0) {
      c_x *= 0.017453292519943295;
      *x = sin(c_x);
    } else {
      if (absx <= 135.0) {
        if (c_x > 0.0) {
          c_x = (c_x - 90.0) * 0.017453292519943295;
          n = 1;
        } else {
          c_x = (c_x + 90.0) * 0.017453292519943295;
          n = -1;
        }
      } else if (c_x > 0.0) {
        c_x = (c_x - 180.0) * 0.017453292519943295;
        n = 2;
      } else {
        c_x = (c_x + 180.0) * 0.017453292519943295;
        n = -2;
      }

      if (n == 1) {
        *x = cos(c_x);
      } else if (n == -1) {
        *x = -cos(c_x);
      } else {
        *x = -sin(c_x);
      }
    }
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_lla2ecef(const real_T llaPos[3], real_T ecefPos[3])
{
  real_T N;
  real_T b;
  real_T c;
  real_T d;
  GNSS_INS_B.sinphi_d = llaPos[0];
  GNSS_INS_sind(&GNSS_INS_B.sinphi_d);
  N = 6.378137E+6 / sqrt(1.0 - GNSS_INS_B.sinphi_d * GNSS_INS_B.sinphi_d *
    0.0066943799901413165);
  b = llaPos[0];
  GNSS_INS_cosd(&b);
  b *= N + llaPos[2];
  c = llaPos[1];
  GNSS_INS_cosd(&c);
  d = llaPos[1];
  GNSS_INS_sind(&d);
  ecefPos[0] = b * c;
  ecefPos[1] = b * d;
  ecefPos[2] = (N * 0.99330562000985867 + llaPos[2]) * GNSS_INS_B.sinphi_d;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_ENU_lla2frame(const real_T llaMeas[3], const real_T refloc
  [3], real_T pos[3])
{
  GNSS_INS_B.cosphi = refloc[0];
  GNSS_INS_cosd(&GNSS_INS_B.cosphi);
  GNSS_INS_B.sinphi = refloc[0];
  GNSS_INS_sind(&GNSS_INS_B.sinphi);
  GNSS_INS_B.coslambda = refloc[1];
  GNSS_INS_cosd(&GNSS_INS_B.coslambda);
  GNSS_INS_B.sinlambda = refloc[1];
  GNSS_INS_sind(&GNSS_INS_B.sinlambda);
  GNSS_INS_lla2ecef(llaMeas, GNSS_INS_B.dv3);
  GNSS_INS_lla2ecef(refloc, GNSS_INS_B.dv4);
  GNSS_INS_B.ecefPosWithENUOrigin_idx_0 = GNSS_INS_B.dv3[0] - GNSS_INS_B.dv4[0];
  GNSS_INS_B.ecefPosWithENUOrigin_idx_1 = GNSS_INS_B.dv3[1] - GNSS_INS_B.dv4[1];
  GNSS_INS_B.ecefPosWithENUOrigin_idx_2 = GNSS_INS_B.dv3[2] - GNSS_INS_B.dv4[2];
  GNSS_INS_B.tmp = GNSS_INS_B.coslambda * GNSS_INS_B.ecefPosWithENUOrigin_idx_0
    + GNSS_INS_B.sinlambda * GNSS_INS_B.ecefPosWithENUOrigin_idx_1;
  pos[0] = -GNSS_INS_B.sinlambda * GNSS_INS_B.ecefPosWithENUOrigin_idx_0 +
    GNSS_INS_B.coslambda * GNSS_INS_B.ecefPosWithENUOrigin_idx_1;
  pos[1] = -GNSS_INS_B.sinphi * GNSS_INS_B.tmp + GNSS_INS_B.cosphi *
    GNSS_INS_B.ecefPosWithENUOrigin_idx_2;
  pos[2] = GNSS_INS_B.cosphi * GNSS_INS_B.tmp + GNSS_INS_B.sinphi *
    GNSS_INS_B.ecefPosWithENUOrigin_idx_2;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_INS_blkdiag(const real_T varargin_1[9], real_T varargin_2,
  real_T y[16])
{
  int32_T i;
  int32_T y_tmp;
  memset(&y[0], 0, sizeof(real_T) << 4U);
  for (i = 0; i < 3; i++) {
    y_tmp = i << 2;
    y[y_tmp] = varargin_1[3 * i];
    y[y_tmp + 1] = varargin_1[3 * i + 1];
    y[y_tmp + 2] = varargin_1[3 * i + 2];
  }

  y[15] = varargin_2;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void GNSS_I_IMUBasicEKF_correctEqn_l(real_T x[16], real_T P[256], const
  real_T h[4], const real_T H[64], const real_T z[4], const real_T R[16])
{
  int8_T ipiv[4];
  int32_T jAcol;
  int32_T kBcol;
  int32_T c;
  int32_T ix;
  int32_T b_ix;
  int32_T c_ix;
  int32_T ijA;
  int32_T A_tmp_tmp;
  for (c = 0; c < 4; c++) {
    for (b_ix = 0; b_ix < 16; b_ix++) {
      A_tmp_tmp = (b_ix << 2) + c;
      GNSS_INS_B.A_tmp[b_ix + (c << 4)] = H[A_tmp_tmp];
      GNSS_INS_B.H_g[A_tmp_tmp] = 0.0;
      for (ix = 0; ix < 16; ix++) {
        GNSS_INS_B.H_g[A_tmp_tmp] += H[(ix << 2) + c] * P[(b_ix << 4) + ix];
      }
    }
  }

  for (c = 0; c < 4; c++) {
    for (b_ix = 0; b_ix < 4; b_ix++) {
      GNSS_INS_B.smax = 0.0;
      for (ix = 0; ix < 16; ix++) {
        GNSS_INS_B.smax += GNSS_INS_B.H_g[(ix << 2) + c] * GNSS_INS_B.A_tmp
          [(b_ix << 4) + ix];
      }

      A_tmp_tmp = (b_ix << 2) + c;
      GNSS_INS_B.A[A_tmp_tmp] = R[A_tmp_tmp] + GNSS_INS_B.smax;
    }

    ipiv[c] = static_cast<int8_T>((c + 1));
  }

  for (A_tmp_tmp = 0; A_tmp_tmp < 3; A_tmp_tmp++) {
    c = A_tmp_tmp * 5;
    b_ix = 0;
    ix = c;
    GNSS_INS_B.smax = fabs(GNSS_INS_B.A[c]);
    for (jAcol = 2; jAcol <= 4 - A_tmp_tmp; jAcol++) {
      ix++;
      GNSS_INS_B.y_d = fabs(GNSS_INS_B.A[ix]);
      if (GNSS_INS_B.y_d > GNSS_INS_B.smax) {
        b_ix = jAcol - 1;
        GNSS_INS_B.smax = GNSS_INS_B.y_d;
      }
    }

    if (GNSS_INS_B.A[c + b_ix] != 0.0) {
      if (b_ix != 0) {
        ix = A_tmp_tmp + b_ix;
        ipiv[A_tmp_tmp] = static_cast<int8_T>((ix + 1));
        GNSS_INS_B.smax = GNSS_INS_B.A[A_tmp_tmp];
        GNSS_INS_B.A[A_tmp_tmp] = GNSS_INS_B.A[ix];
        GNSS_INS_B.A[ix] = GNSS_INS_B.smax;
        b_ix = A_tmp_tmp + 4;
        ix += 4;
        GNSS_INS_B.smax = GNSS_INS_B.A[b_ix];
        GNSS_INS_B.A[b_ix] = GNSS_INS_B.A[ix];
        GNSS_INS_B.A[ix] = GNSS_INS_B.smax;
        b_ix += 4;
        ix += 4;
        GNSS_INS_B.smax = GNSS_INS_B.A[b_ix];
        GNSS_INS_B.A[b_ix] = GNSS_INS_B.A[ix];
        GNSS_INS_B.A[ix] = GNSS_INS_B.smax;
        b_ix += 4;
        ix += 4;
        GNSS_INS_B.smax = GNSS_INS_B.A[b_ix];
        GNSS_INS_B.A[b_ix] = GNSS_INS_B.A[ix];
        GNSS_INS_B.A[ix] = GNSS_INS_B.smax;
      }

      b_ix = (c - A_tmp_tmp) + 4;
      for (ix = c + 1; ix < b_ix; ix++) {
        GNSS_INS_B.A[ix] /= GNSS_INS_B.A[c];
      }
    }

    b_ix = c;
    ix = c + 4;
    for (jAcol = 0; jAcol <= 2 - A_tmp_tmp; jAcol++) {
      if (GNSS_INS_B.A[ix] != 0.0) {
        GNSS_INS_B.smax = -GNSS_INS_B.A[ix];
        c_ix = c + 1;
        kBcol = (b_ix - A_tmp_tmp) + 8;
        for (ijA = b_ix + 5; ijA < kBcol; ijA++) {
          GNSS_INS_B.A[ijA] += GNSS_INS_B.A[c_ix] * GNSS_INS_B.smax;
          c_ix++;
        }
      }

      ix += 4;
      b_ix += 4;
    }
  }

  for (c = 0; c < 4; c++) {
    for (b_ix = 0; b_ix < 16; b_ix++) {
      A_tmp_tmp = c << 4;
      jAcol = b_ix + A_tmp_tmp;
      GNSS_INS_B.W_f[jAcol] = 0.0;
      for (ix = 0; ix < 16; ix++) {
        GNSS_INS_B.W_f[jAcol] += P[(ix << 4) + b_ix] *
          GNSS_INS_B.A_tmp[A_tmp_tmp + ix];
      }
    }
  }

  for (b_ix = 0; b_ix < 4; b_ix++) {
    ix = b_ix << 4;
    jAcol = b_ix << 2;
    for (c_ix = 0; c_ix < b_ix; c_ix++) {
      kBcol = c_ix << 4;
      c = c_ix + jAcol;
      if (GNSS_INS_B.A[c] != 0.0) {
        for (ijA = 0; ijA < 16; ijA++) {
          A_tmp_tmp = ijA + ix;
          GNSS_INS_B.W_f[A_tmp_tmp] -= GNSS_INS_B.A[c] * GNSS_INS_B.W_f[ijA +
            kBcol];
        }
      }
    }

    GNSS_INS_B.smax = 1.0 / GNSS_INS_B.A[b_ix + jAcol];
    for (c = 0; c < 16; c++) {
      A_tmp_tmp = c + ix;
      GNSS_INS_B.W_f[A_tmp_tmp] *= GNSS_INS_B.smax;
    }
  }

  for (b_ix = 3; b_ix >= 0; b_ix--) {
    ix = b_ix << 4;
    jAcol = (b_ix << 2) - 1;
    for (c_ix = b_ix + 2; c_ix < 5; c_ix++) {
      kBcol = (c_ix - 1) << 4;
      c = c_ix + jAcol;
      if (GNSS_INS_B.A[c] != 0.0) {
        for (ijA = 0; ijA < 16; ijA++) {
          A_tmp_tmp = ijA + ix;
          GNSS_INS_B.W_f[A_tmp_tmp] -= GNSS_INS_B.A[c] * GNSS_INS_B.W_f[ijA +
            kBcol];
        }
      }
    }
  }

  for (c = 2; c >= 0; c--) {
    if (c + 1 != ipiv[c]) {
      b_ix = ipiv[c] - 1;
      for (ix = 0; ix < 16; ix++) {
        jAcol = (c << 4) + ix;
        GNSS_INS_B.smax = GNSS_INS_B.W_f[jAcol];
        A_tmp_tmp = (b_ix << 4) + ix;
        GNSS_INS_B.W_f[jAcol] = GNSS_INS_B.W_f[A_tmp_tmp];
        GNSS_INS_B.W_f[A_tmp_tmp] = GNSS_INS_B.smax;
      }
    }
  }

  GNSS_INS_B.y_d = z[0] - h[0];
  GNSS_INS_B.z_idx_1 = z[1] - h[1];
  GNSS_INS_B.z_idx_2 = z[2] - h[2];
  GNSS_INS_B.z_idx_3 = z[3] - h[3];
  for (c = 0; c < 16; c++) {
    GNSS_INS_B.smax = GNSS_INS_B.W_f[c + 16];
    GNSS_INS_B.d = GNSS_INS_B.W_f[c + 32];
    GNSS_INS_B.d1 = GNSS_INS_B.W_f[c + 48];
    x[c] += ((GNSS_INS_B.smax * GNSS_INS_B.z_idx_1 + GNSS_INS_B.W_f[c] *
              GNSS_INS_B.y_d) + GNSS_INS_B.d * GNSS_INS_B.z_idx_2) +
      GNSS_INS_B.d1 * GNSS_INS_B.z_idx_3;
    for (b_ix = 0; b_ix < 16; b_ix++) {
      A_tmp_tmp = c + (b_ix << 4);
      GNSS_INS_B.W_b[A_tmp_tmp] = 0.0;
      jAcol = b_ix << 2;
      GNSS_INS_B.W_b[A_tmp_tmp] += H[jAcol] * GNSS_INS_B.W_f[c];
      GNSS_INS_B.W_b[A_tmp_tmp] += H[jAcol + 1] * GNSS_INS_B.smax;
      GNSS_INS_B.W_b[A_tmp_tmp] += H[jAcol + 2] * GNSS_INS_B.d;
      GNSS_INS_B.W_b[A_tmp_tmp] += H[jAcol + 3] * GNSS_INS_B.d1;
    }

    for (b_ix = 0; b_ix < 16; b_ix++) {
      GNSS_INS_B.smax = 0.0;
      for (ix = 0; ix < 16; ix++) {
        GNSS_INS_B.smax += GNSS_INS_B.W_b[(ix << 4) + c] * P[(b_ix << 4) + ix];
      }

      A_tmp_tmp = (b_ix << 4) + c;
      GNSS_INS_B.P_p[A_tmp_tmp] = P[A_tmp_tmp] - GNSS_INS_B.smax;
    }
  }

  memcpy(&P[0], &GNSS_INS_B.P_p[0], sizeof(real_T) << 8U);
  GN_IMUBasicEKF_repairQuaternion(x);
}

/* Function for MATLAB Function: '<Root>/MATLAB Function5' */
static void NHConstrainedIMUGPSFuserBase_fu(c_fusion_internal_coder_insfi_T *obj,
  const real_T gpsLLA[3], real_T RposIn, const real_T gpsVel[3], real_T RvelIn)
{
  IMUBasicEKF_validateExpandNoise(RposIn, GNSS_INS_B.Rpos);
  IMUBasicEKF_validateExpandNoise(RvelIn, GNSS_INS_B.Rvel);
  memcpy(&GNSS_INS_B.x_d[0], &obj->State[0], sizeof(real_T) << 4U);
  memcpy(&GNSS_INS_B.P_c[0], &obj->StateCovariance[0], sizeof(real_T) << 8U);
  NHConstrainedIMUGPSFuserBase_hv(obj->State, GNSS_INS_B.h);
  NHConstrainedIMUGPSFuserBase__m(obj->State, GNSS_INS_B.H);
  NHConstrainedIMUGPSFuserBase_ve(gpsVel, GNSS_INS_B.Rvel, &GNSS_INS_B.pos[3],
    &GNSS_INS_B.courseR);
  NHConstrainedIMUGPSFuserBase_ad(&GNSS_INS_B.pos[3], GNSS_INS_B.h[3]);
  GNSS_INS_ENU_lla2frame(gpsLLA, obj->ReferenceLocation, GNSS_INS_B.pos_g);
  GNSS_INS_blkdiag(GNSS_INS_B.Rpos, GNSS_INS_B.courseR, GNSS_INS_B.dv);
  GNSS_INS_B.pos[0] = GNSS_INS_B.pos_g[0];
  GNSS_INS_B.pos[1] = GNSS_INS_B.pos_g[1];
  GNSS_INS_B.pos[2] = GNSS_INS_B.pos_g[2];
  GNSS_I_IMUBasicEKF_correctEqn_l(GNSS_INS_B.x_d, GNSS_INS_B.P_c, GNSS_INS_B.h,
    GNSS_INS_B.H, GNSS_INS_B.pos, GNSS_INS_B.dv);
  memcpy(&obj->StateCovariance[0], &GNSS_INS_B.P_c[0], sizeof(real_T) << 8U);
  memcpy(&obj->State[0], &GNSS_INS_B.x_d[0], sizeof(real_T) << 4U);
}

static void matlabCodegenHandle_matlabCod_d(ros_slros_internal_block_Subs_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void GNSS_INS_step(void)
{
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  boolean_T b_varargout_1_1;
  int32_T i;
  static const int8_T b[16] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* MATLABSystem: '<S6>/SourceBlock' incorporates:
   *  Inport: '<S9>/In1'
   */
  b_varargout_1 = Sub_GNSS_INS_1.getLatestMessage(&GNSS_INS_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (b_varargout_1) {
    GNSS_INS_B.In1 = GNSS_INS_B.b_varargout_2;
  }

  /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S7>/SourceBlock' incorporates:
   *  Inport: '<S10>/In1'
   */
  b_varargout_1_0 = Sub_GNSS_INS_4.getLatestMessage(&GNSS_INS_B.b_varargout_2_p);

  /* Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (b_varargout_1_0) {
    GNSS_INS_B.In1_c = GNSS_INS_B.b_varargout_2_p;
  }

  /* End of Outputs for SubSystem: '<S7>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe2' */
  /* MATLABSystem: '<S8>/SourceBlock' */
  b_varargout_1_1 = Sub_GNSS_INS_21.getLatestMessage(&GNSS_INS_B.b_varargout_2_l);

  /* Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  MATLABSystem: '<S8>/SourceBlock'
   */
  if (b_varargout_1_1) {
    GNSS_INS_DW.robotVel[0] = GNSS_INS_B.b_varargout_2_l.Vector_.X;
    GNSS_INS_DW.robotVel[1] = GNSS_INS_B.b_varargout_2_l.Vector_.Y;
    GNSS_INS_DW.robotVel[2] = GNSS_INS_B.b_varargout_2_l.Vector_.Z;
  }

  /* End of Outputs for SubSystem: '<S8>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe2' */

  /* MATLAB Function: '<Root>/MATLAB Function5' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   *  MATLABSystem: '<S6>/SourceBlock'
   *  MATLABSystem: '<S7>/SourceBlock'
   */
  if (!GNSS_INS_DW.gndFusion_not_empty) {
    for (i = 0; i < 16; i++) {
      GNSS_INS_DW.gndFusion.State[i] = b[i];
    }

    GNSS_INS_DW.gndFusion.GyroscopeBiasDecayFactor = 0.999;
    GNSS_INS_DW.gndFusion.AccelerometerBiasDecayFactor = 0.9999;
    GNSS_INS_DW.gndFusion.applyConstraintCount = 0;
    GNSS_INS_DW.gndFusion.IMUSampleRate = 50.0;
    GNSS_INS_DW.gndFusion.ReferenceLocation[0] = 18.954817;
    GNSS_INS_DW.gndFusion.ReferenceLocation[1] = 72.811367;
    GNSS_INS_DW.gndFusion.ReferenceLocation[2] = 0.0;
    GNSS_INS_DW.gndFusion.DecimationFactor = 2;
    GNSS_INS_DW.gndFusion_not_empty = true;
    GNSS_INS_DW.gndFusion.State[0] = 0.707;
    GNSS_INS_DW.gndFusion.State[1] = 0.0;
    GNSS_INS_DW.gndFusion.State[2] = 0.0;
    GNSS_INS_DW.gndFusion.State[3] = 0.707;
    memset(&GNSS_INS_DW.gndFusion.State[4], 0, 9U * sizeof(real_T));
    GNSS_INS_DW.gndFusion.ZeroVelocityConstraintNoise = 0.01;
    GNSS_INS_DW.gndFusion.State[13] = 0.0;
    GNSS_INS_DW.gndFusion.GyroscopeNoise[0] = 2.5E-5;
    GNSS_INS_DW.gndFusion.GyroscopeBiasNoise[0] = 1.4E-8;
    GNSS_INS_DW.gndFusion.AccelerometerNoise[0] = 2.5E-5;
    GNSS_INS_DW.gndFusion.AccelerometerBiasNoise[0] = 1.4E-8;
    GNSS_INS_DW.gndFusion.State[14] = 0.0;
    GNSS_INS_DW.gndFusion.GyroscopeNoise[1] = 2.5E-5;
    GNSS_INS_DW.gndFusion.GyroscopeBiasNoise[1] = 1.4E-8;
    GNSS_INS_DW.gndFusion.AccelerometerNoise[1] = 2.5E-5;
    GNSS_INS_DW.gndFusion.AccelerometerBiasNoise[1] = 1.4E-8;
    GNSS_INS_DW.gndFusion.State[15] = 0.0;
    GNSS_INS_DW.gndFusion.GyroscopeNoise[2] = 2.5E-5;
    GNSS_INS_DW.gndFusion.GyroscopeBiasNoise[2] = 1.4E-8;
    GNSS_INS_DW.gndFusion.AccelerometerNoise[2] = 2.5E-5;
    GNSS_INS_DW.gndFusion.AccelerometerBiasNoise[2] = 1.4E-8;
    for (i = 0; i < 256; i++) {
      GNSS_INS_DW.gndFusion.StateCovariance[i] = 1.0E-9;
    }
  }

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  if (b_varargout_1) {
    /* MATLAB Function: '<Root>/MATLAB Function1' */
    GNSS_INS_B.dv1[0] = GNSS_INS_B.In1.LinearAcceleration.X;
    GNSS_INS_B.dv1[1] = GNSS_INS_B.In1.LinearAcceleration.Y;
    GNSS_INS_B.dv1[2] = -GNSS_INS_B.In1.LinearAcceleration.Z;
    GNSS_INS_B.dv2[0] = GNSS_INS_B.In1.AngularVelocity.X;
    GNSS_INS_B.dv2[1] = GNSS_INS_B.In1.AngularVelocity.Y;
    GNSS_INS_B.dv2[2] = GNSS_INS_B.In1.AngularVelocity.Z;
    NHConstrainedIMUGPSFuserBase_pr(&GNSS_INS_DW.gndFusion, GNSS_INS_B.dv1,
      GNSS_INS_B.dv2);
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  if (b_varargout_1_0) {
    /* MATLAB Function: '<Root>/MATLAB Function' */
    GNSS_INS_B.dv1[0] = GNSS_INS_B.In1_c.Latitude;
    GNSS_INS_B.dv1[1] = GNSS_INS_B.In1_c.Longitude;
    GNSS_INS_B.dv1[2] = GNSS_INS_B.In1_c.Altitude;
    NHConstrainedIMUGPSFuserBase_fu(&GNSS_INS_DW.gndFusion, GNSS_INS_B.dv1, 0.0,
      GNSS_INS_DW.robotVel, 0.01);
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Constant: '<S1>/Constant'
   *  MATLAB Function: '<Root>/MATLAB Function5'
   */
  GNSS_INS_B.BusAssignment = GNSS_INS_P.Constant_Value;
  GNSS_INS_B.BusAssignment.Pose.Pose.Position.X = GNSS_INS_DW.gndFusion.State[7];
  GNSS_INS_B.BusAssignment.Pose.Pose.Position.Y = GNSS_INS_DW.gndFusion.State[8];
  GNSS_INS_B.BusAssignment.Pose.Pose.Position.Z = GNSS_INS_DW.gndFusion.State[9];
  GNSS_INS_B.BusAssignment.Pose.Pose.Orientation.X =
    GNSS_INS_DW.gndFusion.State[1];
  GNSS_INS_B.BusAssignment.Pose.Pose.Orientation.Y =
    GNSS_INS_DW.gndFusion.State[2];
  GNSS_INS_B.BusAssignment.Pose.Pose.Orientation.Z =
    GNSS_INS_DW.gndFusion.State[3];
  GNSS_INS_B.BusAssignment.Pose.Pose.Orientation.W =
    GNSS_INS_DW.gndFusion.State[0];
  GNSS_INS_B.BusAssignment.Twist.Twist.Linear.X = GNSS_INS_DW.gndFusion.State[10];
  GNSS_INS_B.BusAssignment.Twist.Twist.Linear.Y = GNSS_INS_DW.gndFusion.State[11];
  GNSS_INS_B.BusAssignment.Twist.Twist.Linear.Z = GNSS_INS_DW.gndFusion.State[12];

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S5>/SinkBlock' */
  Pub_GNSS_INS_12.publish(&GNSS_INS_B.BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model initialize function */
void GNSS_INS_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset((static_cast<void *>(&GNSS_INS_B)), 0,
                sizeof(B_GNSS_INS_T));

  /* states (dwork) */
  (void) memset(static_cast<void *>(&GNSS_INS_DW), 0,
                sizeof(DW_GNSS_INS_T));

  {
    char_T tmp[15];
    char_T tmp_0[5];
    char_T tmp_1[10];
    int32_T i;
    static const char_T tmp_2[9] = { '/', 'i', 'm', 'u', '_', 'd', 'a', 't', 'a'
    };

    static const char_T tmp_3[14] = { '/', 'g', 'n', 's', 's', '_', 'i', 'n',
      's', '_', 'o', 'd', 'o', 'm' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S6>/SourceBlock' */
    GNSS_INS_DW.obj_nf.matlabCodegenIsDeleted = false;
    GNSS_INS_DW.objisempty_g = true;
    GNSS_INS_DW.obj_nf.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      tmp_1[i] = tmp_2[i];
    }

    tmp_1[9] = '\x00';
    Sub_GNSS_INS_1.createSubscriber(tmp_1, 10);
    GNSS_INS_DW.obj_nf.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S7>/SourceBlock' */
    GNSS_INS_DW.obj_m.matlabCodegenIsDeleted = false;
    GNSS_INS_DW.objisempty_l = true;
    GNSS_INS_DW.obj_m.isInitialized = 1;
    tmp_0[0] = '/';
    tmp_0[1] = 'f';
    tmp_0[2] = 'i';
    tmp_0[3] = 'x';
    tmp_0[4] = '\x00';
    Sub_GNSS_INS_4.createSubscriber(tmp_0, 10);
    GNSS_INS_DW.obj_m.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe2' */
    /* Start for MATLABSystem: '<S8>/SourceBlock' */
    GNSS_INS_DW.obj_n.matlabCodegenIsDeleted = false;
    GNSS_INS_DW.objisempty = true;
    GNSS_INS_DW.obj_n.isInitialized = 1;
    tmp_0[0] = '/';
    tmp_0[1] = 'v';
    tmp_0[2] = 'e';
    tmp_0[3] = 'l';
    tmp_0[4] = '\x00';
    Sub_GNSS_INS_21.createSubscriber(tmp_0, 10);
    GNSS_INS_DW.obj_n.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/Subscribe2' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S5>/SinkBlock' */
    GNSS_INS_DW.obj.matlabCodegenIsDeleted = false;
    GNSS_INS_DW.objisempty_j = true;
    GNSS_INS_DW.obj.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      tmp[i] = tmp_3[i];
    }

    tmp[14] = '\x00';
    Pub_GNSS_INS_12.createPublisher(tmp, 10);
    GNSS_INS_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S9>/Out1' */
  GNSS_INS_B.In1 = GNSS_INS_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S10>/Out1' */
  GNSS_INS_B.In1_c = GNSS_INS_P.Out1_Y0_h;

  /* End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function' */
  GNSS_INS_DW.robotVel[0] = 0.0;
  GNSS_INS_DW.robotVel[1] = 0.0;
  GNSS_INS_DW.robotVel[2] = 0.0;

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function5' */
  GNSS_INS_DW.gndFusion_not_empty = false;
}

/* Model terminate function */
void GNSS_INS_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S6>/SourceBlock' */
  matlabCodegenHandle_matlabCod_d(&GNSS_INS_DW.obj_nf);

  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S7>/SourceBlock' */
  matlabCodegenHandle_matlabCod_d(&GNSS_INS_DW.obj_m);

  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe2' */
  /* Terminate for MATLABSystem: '<S8>/SourceBlock' */
  matlabCodegenHandle_matlabCod_d(&GNSS_INS_DW.obj_n);

  /* End of Terminate for SubSystem: '<Root>/Subscribe2' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S5>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&GNSS_INS_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
