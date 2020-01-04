#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "GNSS_INS";

// For Block GNSS_INS/Subscribe
SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_GNSS_INS_sensor_msgs_Imu> Sub_GNSS_INS_1;

// For Block GNSS_INS/Subscribe1
SimulinkSubscriber<sensor_msgs::NavSatFix, SL_Bus_GNSS_INS_sensor_msgs_NavSatFix> Sub_GNSS_INS_4;

// For Block GNSS_INS/Subscribe2
SimulinkSubscriber<geometry_msgs::Vector3Stamped, SL_Bus_GNSS_INS_geometry_msgs_Vector3Stamped> Sub_GNSS_INS_21;

// For Block GNSS_INS/Publish
SimulinkPublisher<nav_msgs::Odometry, SL_Bus_GNSS_INS_nav_msgs_Odometry> Pub_GNSS_INS_12;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

