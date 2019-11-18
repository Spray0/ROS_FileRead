/*
 * 	此文件是用来处理ROS_Server保存的地图文件里的PGM
 *
 * 	Spray0		2019-11-14
 */

#include 	<stdio.h>
#include 	<stdlib.h>

struct Size_T {
	unsigned int width;
	unsigned int height;
};

class pgmP5 {
public:
	unsigned long FileSize_Bytes = 0;	//数据长度
	unsigned char *__DPtr = NULL;		//数据指针
	unsigned char *__INFO_Ptr = NULL;	//图像创建信息指针
	unsigned char *__Format_Info_Ptr = (unsigned char*) "PGM P5 8bit";	//图像格式信息
	Size_T Size;	//图像尺寸
	bool LoadFile(char *path);	//读取文件
private:
	FILE *pFile = NULL;	//文件指针
	bool Get_INFO(); 	//获取图像信息
};

// 读取pgmP5文件
bool pgmP5::LoadFile(char *path) {

	if (path == NULL)
		return false;	 //如果输入的参数为空则退出

	pgmP5::pFile = fopen(path, "rb");	//打开文件

	if (pgmP5::pFile == NULL)
		return false;
	else {
		fseek(pgmP5::pFile, 0, SEEK_END);
		pgmP5::FileSize_Bytes = ftell(pgmP5::pFile);	//打开文件成功 获取文件大小
		fseek(pgmP5::pFile, 0, SEEK_SET);		//光标移回到文件开始

		//申请空间存放文件数据
		pgmP5::__DPtr = (unsigned char*) malloc(sizeof(unsigned char) * (pgmP5::FileSize_Bytes + 1));

		//开始读取
		if (fread(pgmP5::__DPtr, 1, pgmP5::FileSize_Bytes, pgmP5::pFile) == pgmP5::FileSize_Bytes) {
			fclose(pgmP5::pFile);	//关闭文件
			if (Get_INFO() == false)
				return false;
			return true;
		}
		return false;
	}
}

//读取文件信息
bool pgmP5::Get_INFO() {
	//检查格式	P5
	if ((*pgmP5::__DPtr == 'P') && (*(pgmP5::__DPtr + 1) == '5') && (*(pgmP5::__DPtr + 2) == '\n')) {
		unsigned long temp = 0;
		if (*(pgmP5::__DPtr + 3) == '#') {	//如果这行是信息
			for (temp = 4; temp < pgmP5::FileSize_Bytes; temp++) {
				if (*(pgmP5::__DPtr + temp) == '\n')
					break;
			}
			//文件信息存储
			pgmP5::__INFO_Ptr = (unsigned char*) malloc(sizeof(unsigned char) * (temp - 3 + 1));
			for (int c = 0; c < temp - 3; c++)
				*(pgmP5::__INFO_Ptr + c) = *(pgmP5::__DPtr + 3 + c);
			temp = temp + 1;
		}

		//尺寸信息

		char buf[10];
		char bufcnt = 0;
		while ((*(pgmP5::__DPtr + temp) != ' ') || (temp != pgmP5::FileSize_Bytes)) {
			if ((*(pgmP5::__DPtr + temp) >= '0') && (*(pgmP5::__DPtr + temp) <= '9')) {
				buf[bufcnt] = *(pgmP5::__DPtr + temp);
				bufcnt = bufcnt + 1;
			} else
				break;
			temp = temp + 1;
		}
		if (temp == pgmP5::FileSize_Bytes)
			return false;
		//存储宽度
		pgmP5::Size.width = atoi(buf);
		temp = temp + 1;

		char buf2[10] = { };
		char bufcnt2 = 0;
		while ((*(pgmP5::__DPtr + temp) != '\n') || (temp != pgmP5::FileSize_Bytes)) {
			if ((*(pgmP5::__DPtr + temp) >= '0') && (*(pgmP5::__DPtr + temp) <= '9')) {
				buf2[bufcnt2] = *(pgmP5::__DPtr + temp);
				bufcnt2 = bufcnt2 + 1;
			} else
				break;
			temp = temp + 1;
		}
		if (temp == pgmP5::FileSize_Bytes)
			return false;
		//存储宽度
		pgmP5::Size.height = atoi(buf2);
		temp = temp + 1;

		//检查文件位数
		if ((*(pgmP5::__DPtr + temp) == '2') && (*(pgmP5::__DPtr + temp + 1) == '5') && (*(pgmP5::__DPtr + temp + 2) == '5') && (*(pgmP5::__DPtr + temp + 3) == '\n')) {
			temp = temp + 4;
		} else
			return false;
		pgmP5::__DPtr = pgmP5::__DPtr + temp;

		//检查完整性
		if (temp + (unsigned long) (pgmP5::Size.height * pgmP5::Size.width) != pgmP5::FileSize_Bytes)
			return false;

		//通过
		return true;
	} else
		return false;
}

