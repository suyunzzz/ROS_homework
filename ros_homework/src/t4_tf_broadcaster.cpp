//本节点"tf_broadcaster" 订阅lidar_point的话题base_laser_point，并发布tf变换
#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<ros_homework/laser_point.h>

void pointCallback(const ros_homework::laser_pointConstPtr& msg)
{
    static tf::TransformBroadcaster br;

    tf::Transform transform;                  //平移的变换
    transform.setOrigin(tf::Vector3(0.1 , 0 , 0.2));

    tf::Quaternion q;              //旋转的变换
    q.setRPY(0, 0, 0);
    transform.setRotation(q);

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "base_laser"));    //goal_frame,source_frame
}      

int main(int argc, char *argv[])
{
    /* code for main function */
    ros::init(argc, argv, "tf_broadcaster");               //节点名称tf_broadcaster
    ros::NodeHandle node;                           //创建句柄
    ros::Subscriber sub = node.subscribe("base_laser_point",10,&pointCallback);    //订阅话题base_laser_point,发布tf变换
    
    ROS_INFO("TF has published!");
    ros::spin();

    return 0;
}

