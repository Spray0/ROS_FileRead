/*
 * 	此文件是用来处理ROS launch 加载的yaml
 *
 * 	Spray0		2019-11-15
 */

#include	"ros/ros.h"
#include	"std_msgs/String.h"
#include 	<sstream>

template<typename T>
T ReadParam(ros::NodeHandle n, std::string name) {
	T ans;
	if (n.getParam(name, ans))
		ROS_INFO_STREAM("Loaded Param	" << name << ": " << ans);
	else {
		ROS_ERROR_STREAM("Failed to load	" << name);
		n.shutdown();
	}
	return ans;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "para_read");
	ros::NodeHandle n;

	std::string image = ReadParam<std::string>(n, "sp/image");

	double resolution = ReadParam<double>(n, "sp/resolution");

	XmlRpc::XmlRpcValue origin_temp = ReadParam<XmlRpc::XmlRpcValue>(n, "sp/origin");

	int negate = ReadParam<int>(n, "sp/negate");

	float occupied_thresh = ReadParam<float>(n, "sp/occupied_thresh");

	float free_thresh = ReadParam<float>(n, "sp/free_thresh");

	//double origin[3]={origin_temp[0],origin_temp[1],origin_temp[2]};
	// ROS_INFO_STREAM("ORIGIN: "<<origin[0]<<' '<<origin[1]<<' '<<origin[2]);

	return 0;
}
