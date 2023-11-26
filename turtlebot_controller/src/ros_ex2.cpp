#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/Kill.h"
//Add the required header



ros::Publisher pub;


void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
	{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;
	
	int x=msg->x;
	int theta=msg->theta;
	//modify the code for implementing the required behaviour
	if(x<10.5)
	{
		my_vel.linear.x =1;
	}
	else if(theta==0)
	{
		my_vel.angular.z=1.57;
	}
	if(theta!=0)
	{
		my_vel.linear.x=1;
	}
	pub.publish(my_vel);
	
        }
       



int main (int argc, char **argv)
{
// Initialize the node, setup the NodeHandle for handling the communication with the ROS //system  
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	// Define the subscriber to turtle's position  
	pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1);  //check the topic name
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1,turtleCallback);  //check the topic name
	ros::ServiceClient client1 =  nh.serviceClient<turtlesim::Spawn>("/spawn");
	//add the required client
	
	//call the service for "killing" turtle1
	ros::ServiceClient client2 =  nh.serviceClient<turtlesim::Kill>("/kill");
	
	turtlesim::Kill srv2;
	
	srv2.request.name="turtle1";
	
	client2.call(srv2);
	
	
	//modify the starting position of "my_turtle"
	
	turtlesim::Spawn srv1;
	srv1.request.x = 5.0;  
	srv1.request.y = 6.0;
	srv1.request.theta = 0.0;
	srv1.request.name = "rpr_turtle";
	client1.call(srv1);
	
	pub = nh.advertise<geometry_msgs::Twist>("rpr_turtle/cmd_vel",1);  //check the topic name
	ros::Subscriber sub1 = nh.subscribe("rpr_turtle/pose", 1,turtleCallback);  //check the topic name
 
 
	ros::spin();
	return 0;
}

