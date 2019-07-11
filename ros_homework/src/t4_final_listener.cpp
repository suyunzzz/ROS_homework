#include<ros/ros.h>
#include<ros_homework/laser_point.h>

void Callback(const ros_homework::laser_pointConstPtr& msg)
{
    ROS_INFO("The laser_point in the base_link is %f,%f,%f",msg->x,msg->y,msg->z);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "final_listener");
    ros::NodeHandle node;

    ros::Subscriber point_sub = node.subscribe("base_link_point",10,&Callback);

    ros::spin();
    return 0;
}