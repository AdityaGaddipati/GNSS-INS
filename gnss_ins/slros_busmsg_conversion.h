#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistWithCovariance.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <nav_msgs/Odometry.h>
#include <ros/time.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/NavSatStatus.h>
#include <std_msgs/Header.h>
#include "GNSS_INS_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(geometry_msgs::Point* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Point const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Point* busPtr, geometry_msgs::Point const* msgPtr);

void convertFromBus(geometry_msgs::Pose* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Pose const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Pose* busPtr, geometry_msgs::Pose const* msgPtr);

void convertFromBus(geometry_msgs::PoseWithCovariance* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_PoseWithCovariance* busPtr, geometry_msgs::PoseWithCovariance const* msgPtr);

void convertFromBus(geometry_msgs::Quaternion* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Quaternion const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Quaternion* busPtr, geometry_msgs::Quaternion const* msgPtr);

void convertFromBus(geometry_msgs::Twist* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Twist const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Twist* busPtr, geometry_msgs::Twist const* msgPtr);

void convertFromBus(geometry_msgs::TwistWithCovariance* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_TwistWithCovariance* busPtr, geometry_msgs::TwistWithCovariance const* msgPtr);

void convertFromBus(geometry_msgs::Vector3* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Vector3 const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Vector3* busPtr, geometry_msgs::Vector3 const* msgPtr);

void convertFromBus(geometry_msgs::Vector3Stamped* msgPtr, SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped* busPtr, geometry_msgs::Vector3Stamped const* msgPtr);

void convertFromBus(nav_msgs::Odometry* msgPtr, SL_Bus_GNSS_INS_nav_msgs_Odometry const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_nav_msgs_Odometry* busPtr, nav_msgs::Odometry const* msgPtr);

void convertFromBus(ros::Time* msgPtr, SL_Bus_GNSS_INS_ros_time_Time const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_ros_time_Time* busPtr, ros::Time const* msgPtr);

void convertFromBus(sensor_msgs::Imu* msgPtr, SL_Bus_GNSS_INS_sensor_msgs_Imu const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_sensor_msgs_Imu* busPtr, sensor_msgs::Imu const* msgPtr);

void convertFromBus(sensor_msgs::NavSatFix* msgPtr, SL_Bus_GNSS_INS_sensor_msgs_NavSatFix const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_sensor_msgs_NavSatFix* busPtr, sensor_msgs::NavSatFix const* msgPtr);

void convertFromBus(sensor_msgs::NavSatStatus* msgPtr, SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_sensor_msgs_NavSatStatus* busPtr, sensor_msgs::NavSatStatus const* msgPtr);

void convertFromBus(std_msgs::Header* msgPtr, SL_Bus_GNSS_INS_std_msgs_Header const* busPtr);
void convertToBus(SL_Bus_GNSS_INS_std_msgs_Header* busPtr, std_msgs::Header const* msgPtr);


#endif
