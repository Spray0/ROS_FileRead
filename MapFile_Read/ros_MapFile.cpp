/*
 * 此文件是地图文件读取类　Demo
 *
 * Spray0 2019-11-18
 */
#include 	"MapFile_Read/ros_MapFile.h"
#include	"pgmP5_Class.cpp"
pgmP5 pgmfile, *MapPGM = &pgmfile;

template<typename T>
T ROS_MapFile::ReadParam(ros::NodeHandle n, std::string name) {
	T ans;
	if (n.getParam(name, ans))
		ROS_INFO_STREAM("Loaded Param	" << name << ": " << ans);
	else {
		ROS_ERROR_STREAM("Failed to load	" << name);
		n.shutdown();
	}
	return ans;
}

bool ROS_MapFile::Load(ros::NodeHandle n) {
	ROS_INFO_STREAM("Start to load MapFile...");

	ROS_MapFile::image = ReadParam<std::string>(n, "sp/image");
	ROS_MapFile::resolution = ReadParam<double>(n, "sp/resolution");
	ROS_MapFile::origin_temp = ReadParam<XmlRpc::XmlRpcValue>(n, "sp/origin");
	ROS_MapFile::negate = ReadParam<int>(n, "sp/negate");
	ROS_MapFile::occupied_thresh = ReadParam<float>(n, "sp/occupied_thresh");
	ROS_MapFile::free_thresh = ReadParam<float>(n, "sp/free_thresh");
	ROS_MapFile::position.x=origin_temp[0];
	ROS_MapFile::position.y=origin_temp[1];
	ROS_MapFile::position.z=origin_temp[2];


	//载入文件
	if (MapPGM->LoadFile(const_cast<char*>(ROS_MapFile::image.c_str())) == true) {
		ROS_INFO("PGM file size:   %ld Bytes", MapPGM->FileSize_Bytes);	//显示文件大小
		ROS_INFO("PGM file format: %s", MapPGM->__Format_Info_Ptr);	//显示图像格式
		ROS_INFO("PGM file Info:   %s", MapPGM->__INFO_Ptr);	//显示图像创建信息
		ROS_INFO("PGM file width=%d length=%d", MapPGM->Size.width, MapPGM->Size.height);	//显示图像尺寸
	} else {
		ROS_ERROR("Load PGM file failed.");
		return false;
	}

	ROS_MapFile::size.width = MapPGM->Size.width;
	ROS_MapFile::size.height = MapPGM->Size.height;
	ROS_MapFile::data.len = MapPGM->Size.width * MapPGM->Size.height;
	ROS_MapFile::data.ptr = MapPGM->__DPtr;

	ROS_INFO_STREAM("Loading done.");

	return true;
}

