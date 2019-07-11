/*****
*此节点是作业2的listener,将订阅/turtle2/pose,消息类型是turtlesim::Pose
*此节点可有可无，因为订阅该话题完全可以由turtle2_creater节点实现（与turtlesim双向通信)
*作者：苏云征
***/
#include<ros/ros.h>
//#include<geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>

void turtle2_call_back(const turtlesim::PoseConstPtr msg)  //自定义定义回调函数
{
    ROS_INFO("Turtle2 postion : (%f,%f,%f,%f,%f)",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);
}


int main (int argc,char **argv)
{
    ros::init(argc, argv, "turtle2_listener");   //初始化节点名称
    ros::NodeHandle node;        //创建句柄

    ros::Subscriber sub = node.subscribe("turtle2/pose",10,turtle2_call_back);   //定义一个订阅者，订阅的话题是turtle2/pose

    ros::spin();

    return 0;
}
    
