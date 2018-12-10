#include <ros/ros.h>
#include <std_msgs/Int8MultiArray.h>
#include <sensor_msgs/Joy.h>

#define NODE_NAME "settings"
#define PUB_CHEANEL "relay_controll"
#define SUB_CHANEL "controll_panel"
#define JOY_SUB_NODE "joy"

std_msgs::Int8MultiArray p_data;
ros::Publisher p_relay;

struct toggleButton {
		bool state;
		bool joy_last;
};

struct toggleButton emergensy_stop = {.state = true, .joy_last = false}; // A controlling engine
struct toggleButton saft_blandare = {.state = true, .joy_last = false}; // Y controling satf_blandare

void pubData();
void dataCallback(const std_msgs::Int8MultiArray::ConstPtr& array);
void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);
void toggel(int val, struct toggleButton *b);

void dataCallback(const std_msgs::Int8MultiArray::ConstPtr& array)
{
	emergensy_stop.state = (array->data[0] == 1);
	saft_blandare.state = (array->data[2] == 1);
	pubData();
}

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
		toggel(msg->buttons[0], &emergensy_stop); // A
		toggel(msg->buttons[3], &saft_blandare); // Y
		pubData();

}

// togel state iff the last state of the buttun wos off
// these prohibit multipel trigers on singel press.
void toggel(int val, struct toggleButton *b)
{
	if (val == 1 && !b->joy_last)
		b->state = !b->state;
	b->joy_last = (val == 1);
}


// relay postion
// [0] -> engine
// [1] -> engien
// [2] -> sart_balndare
// [3] -> not used
void pubData()
{
	p_data.data.push_back(emergensy_stop.state);
	p_data.data.push_back(emergensy_stop.state);
	p_data.data.push_back(saft_blandare.state);
	p_data.data.push_back(0);

	p_relay.publish(p_data);
	p_data.data.clear();
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, NODE_NAME);
	ros::NodeHandle n;
	
	ros::Rate loop_rate(100);	
	p_relay = n.advertise<std_msgs::Int8MultiArray>(PUB_CHEANEL, 10);

	// from control panel
	ros::Subscriber s_data = n.subscribe<std_msgs::Int8MultiArray>(SUB_CHANEL, 10, dataCallback);
	// form PadPub
	ros::Subscriber s_joy = n.subscribe<sensor_msgs::Joy>(JOY_SUB_NODE, 200, joyCallback);
	
	while(ros::ok())
	{
		ros::spinOnce();
	}
	return 0;
}
