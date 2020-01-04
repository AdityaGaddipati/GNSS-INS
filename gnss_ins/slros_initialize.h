#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block GNSS_INS/Subscribe
extern SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_GNSS_INS_sensor_msgs_Imu> Sub_GNSS_INS_1;

// For Block GNSS_INS/Subscribe1
extern SimulinkSubscriber<sensor_msgs::NavSatFix, SL_Bus_GNSS_INS_sensor_msgs_NavSatFix> Sub_GNSS_INS_4;

// For Block GNSS_INS/Subscribe2
extern SimulinkSubscriber<geometry_msgs::Vector3Stamped, SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped> Sub_GNSS_INS_21;

// For Block GNSS_INS/Publish
extern SimulinkPublisher<nav_msgs::Odometry, SL_Bus_GNSS_INS_nav_msgs_Odometry> Pub_GNSS_INS_12;

void slros_node_init(int argc, char** argv);

#endif
