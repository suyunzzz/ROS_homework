/*
*此节点订阅语音消息，发布速度指令
*/
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<std_msgs/String.h>
#include<string>



//string forward = "forward";
//String backward = "向后";
//String leftward = "向左";
//String rightward = "向右";

geometry_msgs::Twist vel_msg;          //发布的速度消息


void voiceCallback(const std_msgs::StringConstPtr& msg)//回调函数，接收到voice后启动该函数
{

    //ROS_INFO("msg get!");

      // 将接收到的消息打印出来
    ROS_INFO("I heard: [%s]", msg->data.c_str());


    if (msg->data == "forward\u3002")
    {
       vel_msg.linear.x = 1.0;
       ROS_INFO("forward vel_msg has been modifided!");
    }

    if (msg->data == "stop\uFF01")
    {
       vel_msg.linear.x = 0.0;
       ROS_INFO("stop!!");
    }

    
/*
    if (msg->data = backword)
    {
        
    }
    
        if (msg->data = leftward)
    {

    }

    if (msg->data = rightword)
    {
        
    }
  */  
    


}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "voice_controll");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("voiceWords",1000,voiceCallback);  //订阅语音识别之后的话题
    
    ros::Publisher pub = node.advertise<geometry_msgs::Twist>("/cmd_vel",10);//定义一个速度发布者

    ros::Rate rate(10);  //频率

    while (ros::ok())
    {
        pub.publish(vel_msg);

        

        ros::spinOnce();

        rate.sleep();
    }
    



    
    return 0;
}