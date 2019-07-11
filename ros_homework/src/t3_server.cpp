#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<ros_homework/PostionAction.h>

typedef actionlib::SimpleActionServer<ros_homework::PostionAction> Server;

void execute(const ros_homework::PostionGoalConstPtr& goal,Server* as)
{
    ros::Rate r(1);
    ros_homework::PostionFeedback feedback;      //创建对象feedback

    ROS_INFO("Now go to (x : %f , y : %f)",goal->x,goal->y);

    for(int i=1;i<=10;i++)
    {
        feedback.percent = i*10;
        as->publishFeedback(feedback);        //发布”feedback“对象给client
        r.sleep(); 
    }

    ROS_INFO("Postion (x : %f , y : %f) move complete",goal->x,goal->y);
    as->setSucceeded();
    
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "move_server");    //初始化节点 “t3_server”
    ros::NodeHandle node;    //创建一个句柄

    Server server(node,"move_to_goal",boost::bind(&execute, _1,&server),false);  //定义一个服务器,话题是move_to_goal


    server.start();   //开始运行服务器
    ros::spin();
    
    return 0;
}