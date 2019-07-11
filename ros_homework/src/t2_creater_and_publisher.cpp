/*****
*此代码是第一周作业2,将生产一只乌龟，名叫turtle2,并且创建一个节点（turtle2_creater），该节点发布话题turtle2/cmd_vel，该话题由turtlesim订阅。并且订阅/turtle2/pose。
*作者：苏云征
***/
#include<ros/ros.h>
#include<turtlesim/Spawn.h>
#include<turtlesim/Pose.h>
#include<geometry_msgs/Twist.h>


void turtle2_call_back(const turtlesim::PoseConstPtr& msg)  //自定义定义回调函数
{
    ROS_INFO("Turtle2 postion : (%f,%f,%f,%f,%f)",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);
}


int main(int argc, char **argv)
{

   ros::init(argc , argv, "turtle2_creater");   //初始化节点，节点名为create_turtle2,当使用rosrun命令后，节点的名称。（roslaunch可以改变节点运行后的名称！）

   ros::NodeHandle node;         //创建一个句柄


   ros::service::waitForService("/spawn");       //调用服务spawn，产生第二只海龟turtle2
   ros::ServiceClient new_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
   turtlesim::Spawn srv;   //创建一个对象srv
   srv.request.x = 5;
   srv.request.y = 5;     
   srv.request.name = "turtle2";
   new_turtle.call(srv);  //通过call来调用spawn
   
   ROS_INFO("turtle2 has been spawn!");



   ros::Subscriber sub = node.subscribe("turtle2/pose",10,&turtle2_call_back);         //订阅话题turtle2/pose
   //定义一个速度发布器，以便发布速度给tuetlesim仿真器
   ros::Publisher turtle_vel = node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel" , 10);  //声明一个发布者
   ros::Rate rate(10.0);  //创建一个rate对象，是Rate类，频率初值为10.0
  
   while(node.ok())
   {
      geometry_msgs::Twist vel_msg;  //创建一个对象vel_msg
      vel_msg.angular.z = 1;
      vel_msg.linear.x = 2;
      turtle_vel.publish(vel_msg);      //通过publish来发布速度信息

      ros::spinOnce();
      rate.sleep();
   }
   return 0;
}
