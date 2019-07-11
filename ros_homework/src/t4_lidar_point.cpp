//本节点只发布一个点 laser_point(自定义)
#include<ros/ros.h>
#include<ros_homework/laser_point.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "lidar_point");     //初始化节点
    
    ros::NodeHandle node;          //创建一个句柄

    ros::Publisher pub = node.advertise<ros_homework::laser_point>("base_laser_point",10);  //创建一个发布者，并指定发布的话题

    ros::Rate rate(10);              //实例化一个对象并设置初值（频率)为10Hz

    while(ros::ok())
    {
        ros_homework::laser_point point;    //创建一个消息
        point.x = 0;
        point.y = 0;
        point.z = 0;

        pub.publish(point);      //发布一个消息

        ROS_INFO("Original base_laser_point:%f,%f,%f",point.x,point.y,point.z); //输出原始在lidar坐标系下的原始坐标点

        ros::spinOnce();        

        rate.sleep();    
    }

    
    return 0;
}