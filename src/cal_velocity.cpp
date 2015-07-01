#include<iostream>
#include"ros/ros.h"
#include"kobuki_msgs/SensorState.h"
#define WHEEL_RADIUS    0.035
#define WHEEL_GAP          0.24

int delta_right_encorder = 0;
int befor_right_encorder = 0;
int delta_left_encorder = 0;
int befor_left_encorder = 0;
double delta_Time = 0;
double befor_Time = 0;
void msgSensor(const kobuki_msgs::SensorState smsg)
{
    int right_encoder = smsg.right_encoder;
    int left_encoder = smsg.left_encoder;
    double now_sec =  ros::Time::now().toSec();
    delta_right_encorder = right_encoder - befor_right_encorder;
    delta_left_encorder = left_encoder - befor_left_encorder;
    delta_Time = now_sec - befor_Time;
    float velocity = WHEEL_RADIUS*(delta_left_encorder+delta_right_encorder)/(2*delta_Time);
    float angular_v = WHEEL_RADIUS*(delta_right_encorder-delta_left_encorder)/(WHEEL_GAP*delta_Time);


    ROS_INFO("right_encoder = %d\n", right_encoder);
    ROS_INFO("left_encoder = %d\n", left_encoder);

    ROS_INFO("delta_right_encorder = %d\n", delta_right_encorder);
    ROS_INFO("delta_left_encorder = %d\n", delta_left_encorder);
    ROS_INFO("delta_Time = %f\n", delta_Time);

    ROS_INFO("velocity = %f\n", velocity);
    ROS_INFO("angular velocity = %f\n", angular_v);

    befor_left_encorder = left_encoder;
    befor_right_encorder = right_encoder;
    befor_Time = now_sec;

    ros::Duration(0.2).sleep();

}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"cal_velocity");
	ros::NodeHandle nh;	
    ROS_INFO("init cal_");
    ros::Subscriber kobuki_core = nh.subscribe("/mobile_base/sensors/core",10,msgSensor);
	
	ros::spin();
	return 0;
}
