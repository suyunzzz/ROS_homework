//此节点tf_listener,订阅base_laser_point话题 查找tf变换，并发布变换之后的坐标
#include<ros/ros.h>
#include<tf/transform_listener.h>
#include<ros_homework/laser_point.h>
float a,b,c;

void laser_pointCallback(const ros_homework::laser_point::ConstPtr& msg)   //回调函数，接收并存储base_laser_point的数据
{
    a = msg->x;
    b = msg->y;
    c = msg->z;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tf_listener");                            //节点名称tf_listener
    ros::NodeHandle node;

    ros::Subscriber subscriber = node.subscribe("base_laser_point",10,&laser_pointCallback); //订阅第一个节点发布的话题"base_laser_point"

    ros::Publisher publish = node.advertise<ros_homework::laser_point>("base_link_point",10);     //创建一个发布者 话题是base_link_point

    tf::TransformListener listener;

    ros::Rate rate(10);

    while(ros::ok())
    {
        tf::StampedTransform transform;          //监听tf变换，并将监听到的值放到transfrom中
        try
        {
            listener.waitForTransform("base_link","base_laser",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("base_link","base_laser",ros::Time(0),transform);

        }
        catch (tf::TransformException &ex)
        {
            ROS_INFO("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        
        
        

        ros_homework::laser_point base_link_point;      //创建一个新点
        base_link_point.x = a + transform.getOrigin().x();     //新的在base_link下的点 = 原来的在lidar下的点 + tf变换
        base_link_point.y = b + transform.getOrigin().y();  
        base_link_point.z = c + transform.getOrigin().z(); 

        ROS_INFO("base_laser_point(%f, %f, %f)------->>>>base_link_point(%f, %f, %f)",a, b, c, base_link_point.x, base_link_point.y ,base_link_point.z  );
        
        publish.publish(base_link_point);
        ros::spinOnce();
        rate.sleep();


    }

    
    return 0;
}   