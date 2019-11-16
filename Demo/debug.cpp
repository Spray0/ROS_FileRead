#include	"ros/ros.h"
#include 	"MapFile_Read/ros_MapFile.h"

int main(int argc, char **argv) {

	ros::init(argc, argv, "MapFile");
	ros::NodeHandle n;

	ROS_MapFile mymap;
	mymap.Load(n);

	long cnt = mymap.data.len;
	long c0 = 0;
	long c205 = 0;
	long c254 = 0;
	for (long c = 0; c < cnt; c++) {
		if (*(mymap.data.ptr + c) == 0)
			c0++;
		else
			if (*(mymap.data.ptr + c) == 205)
				c205++;
			else
				if (*(mymap.data.ptr + c) == 254)
					c254++;
	}
	ROS_INFO_STREAM("[0]:"<<c0<<"	[205]:"<<c205<<"	[254]:"<<c254);
	ROS_INFO_STREAM("SUM:"<<c0+c205+c254<<"	It should be:"<<mymap.data.len);
	return 0;
}
