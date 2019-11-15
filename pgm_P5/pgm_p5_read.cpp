/*
 * 	此文件是用来处理ROS_Server保存的地图文件里的PGM
 *
 * 	Spray0		2019-11-14
 */

#include	"ros/ros.h"
#include	"std_msgs/String.h"
#include 	<sstream>
#include 	<iostream>
#include 	<stdio.h>
#include  "pgmP5/pgmP5_Class.cpp"

pgmP5  pgmfile,*MapPGM=&pgmfile;
int	main(int argc, char **argv)
{
	//如果输入的参数为空则退出
	if(argv[1]==NULL){
		ROS_ERROR("Input Path: Null");ROS_FATAL("Exit");
		return 0;
	}
	 //显示路径
	ROS_INFO("Input Path: %s",argv[1]);

	//读取文件
	if(MapPGM->LoadFile(argv[1])==true){
		ROS_INFO("Size of the file: %ld Bytes",MapPGM->FileSize_Bytes);	//显示文件大小
		ROS_INFO("PGM file format: %s",MapPGM->__Format_Info_Ptr);	//显示图像格式
		ROS_INFO("PGM file Info: %s",MapPGM->__INFO_Ptr);	//显示图像创建信息
		ROS_INFO("PGM file width=%d length=%d",MapPGM->Size.width,MapPGM->Size.length);	//显示图像尺寸
	}
	else{
		ROS_ERROR("Load PGM file failed.");ROS_FATAL("Exit");
		return 0;
	}

	return 0;
}






























