#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<ros_homework/PostionAction.h>

typedef actionlib::SimpleActionClient<ros_homework::PostionAction> Client;

void doneCb(const actionlib::SimpleClientGoalState& state,const ros_homework::PostionResultConstPtr& result)
{
    ROS_INFO("Move complete!");
    ros::shutdown();

}

void activeCb()
{
    ROS_INFO("Move to goal start!");
}

void feedbackCb(const ros_homework::PostionFeedbackConstPtr& feedback)
{
    ROS_INFO("Percent complete : %f%%",feedback->percent);
}


int main(int argc,char** argv)
{
    ros::init(argc, argv, "move_client");  //初始化节点
    Client client("move_to_goal",true);    //定义一个客户端，话题是move_to_goal

    //等待服务器端运行
    ROS_INFO("Witting for move_server......"); 
    client.waitForServer();
    ROS_INFO("Now , Move to goal!");

    //创建一个action的goal
    ros_homework::PostionGoal goal;
    goal.x = 5.0;
    goal.y = 5.0;

    //发送goal给服务器，并设置回调函数
    client.sendGoal(goal,&doneCb,&activeCb,&feedbackCb);

    ros::spin();

    return 0;

    
}