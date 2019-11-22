# ROS_MapFile_Read
ROS MAP文件类型读取,并发布地图话题，ROS环境。 

![cpp](https://img.shields.io/badge/Use-C++-red) ![me](https://img.shields.io/badge/2019/11-Spray0-blue) ![os1](https://img.shields.io/badge/x64_Ubuntu-success-green) ![os2](https://img.shields.io/badge/ARM_Linux-unknown-yellow)

### 文件类型:

![pgmp5](https://img.shields.io/badge/File-PGM__P5-lightgrey) 读取ros_server保存的pgm MAP文件，格式为P5类型。

![pgmp5](https://img.shields.io/badge/File-yaml-ff69b4) 使用launch文件加载yaml文件，通过n.getParam获取参数。

### 描述：

yaml文件通过launch加载，随后读取路径path，打开地图文件。

将地图文件数据转成Rviz显示用的数据，并发布话题/map。

