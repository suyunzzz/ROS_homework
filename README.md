# ROS_homework
wheel_chair_description是机器人的模型功能包，改功能包是gyj的网课的第三周和第四周作业，一些建模步骤移步https://blog.csdn.net/suyunzzz/article/details/95522243

ros_homework是第二周的作业

robot_voice是第5周作业的语音控制部分，其中运行步骤是：1>唯一的launch文件，2>rosrun robot_voice my_voice_assitant（目前存在的问题：这一步中当两个指令都不是时，机器人不能按照我想的那样说“您说的我没听懂”。） 3>开一个终端输入激活消息rostopic pub /voiceWakeup std_msgs/String "data: 'any thing'"，根据提示发出语音指令即可（目前仅支持两个英文单词：forward，stop)。查看消息类型是使用rostopic echo /voiceWords.

mbot_gazebo mbot_teleop mbot_description2  这三个功能包是用于建图 
