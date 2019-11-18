/*
 * 此文件是地图文件读取类　Demo
 *
 * Spray0 2019-11-18
 */
#ifndef ROS_MAPFILE_H
#define ROS_MAPFILE_H

#include	"ros/ros.h"
#include	"std_msgs/String.h"
#include 	<sstream>
#include 	<geometry_msgs/PoseStamped.h>
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
		int height;
	};
	struct data_t {
		long len;
		unsigned char *ptr;
	};
public:
	bool Load(ros::NodeHandle n);
	std::string image;
	double resolution;
	geometry_msgs::Point position;
	int negate;
	float occupied_thresh;
	float free_thresh;
	mapsize size;
	data_t data;
};

#endif
