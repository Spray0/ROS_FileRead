#ifndef ROS_MAPFILE_H
#define ROS_MAPFILE_H

#include	"ros/ros.h"
#include	"std_msgs/String.h"
#include 	<sstream>

class ROS_MapFile {
private:
	template<typename T>
	T ReadParam(ros::NodeHandle n, std::string name);
	XmlRpc::XmlRpcValue origin_temp;
	struct origin_T {
		double x;
		double y;
		double yaw;
	};
	struct mapsize {
		int width;
		int length;
	};
	struct data_t {
		long len;
		unsigned char *ptr;
	};
public:
	bool Load(ros::NodeHandle n);
	std::string image;
	double resolution;
	origin_T origin;
	int negate;
	float occupied_thresh;
	float free_thresh;
	mapsize size;
	data_t data;
};

#endif
