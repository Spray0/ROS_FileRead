/*
 * 此文件是发布地图话题　Demo
 *
 * Spray0 2019-11-18
 */

#include	"ros/ros.h"
#include 	"MapFile_Read/ros_MapFile.h"
#include 	"nav_msgs/OccupancyGrid.h"
#include 	<geometry_msgs/Quaternion.h>
#include 	<geometry_msgs/PoseStamped.h>
#include 	<tf/tf.h>

int main(int argc, char **argv) {

	//初始化节点
	ros::init(argc, argv, "MapFile");
	ros::NodeHandle n;

	//创建地图文件对象
	ROS_MapFile mymap;
	mymap.Load(n);

	//定义地图发布器
	ROS_INFO_STREAM("Start to pub map...");
	ros::Publisher map_pub = n.advertise<nav_msgs::OccupancyGrid>("map", 1000);

	//创建地图对象
	nav_msgs::OccupancyGrid map;

	//设置地图属性
	std::string frame_str = "map";
	map.header.frame_id = frame_str;
	map.header.stamp = ros::Time::now();
	map.info.resolution = mymap.resolution;
	map.info.width = mymap.size.width;
	map.info.height = mymap.size.height;

	//设置启始位姿
	//map.info.origin.position=mymap.position;
	map.info.origin.position.x = 0;
	map.info.origin.position.y = 0;
	map.info.origin.position.z = 0;
	map.info.origin.orientation = tf::createQuaternionMsgFromYaw(0);

	//将灰度数据转成RVIZ地图数据格式　并赋值给地图对象
	std::vector<unsigned char> temp(mymap.data.ptr, mymap.data.ptr + mymap.data.len);
	std::vector<signed char> array(mymap.data.len, 0);
	long index = -1;
	for (auto c : temp)
		array[++index] = (c == 0 ? 100 : c == 254 ? 0 : c == 205 ? 50 : array[index]);
	map.data = array;

	//初始化ros定时器　１hz
	ros::Time::init();
	ros::Rate loop_rate(1);

	while (ros::ok()) {

		ROS_INFO("pub loop 1s");

		//发布地图
		map_pub.publish(map);

		//ros
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
