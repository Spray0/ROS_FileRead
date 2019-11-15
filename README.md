# ROS_MapFile_Read
ROS MAP文件类型读取,ROS环境。 

![cpp](https://img.shields.io/badge/Use-C++-red)
![os1](https://img.shields.io/badge/x64_Ubuntu-success-green) ![os2](https://img.shields.io/badge/ARM_Linux-unknown-yellow)
### Support:
![pgmp5](https://img.shields.io/badge/File-PGM__P5-lightgrey) 读取ros_server保存的pgm MAP文件，格式为P5类型。

![pgmp5](https://img.shields.io/badge/File-yaml-ff69b4) 使用launch文件加载yaml文件，通过n.getParam获取参数。

### yaml说明

image:指定包含occupancy data的image文件路径; 可以是绝对路径，也可以是相对于YAML文件的对象路径 。

resolution:地图分辨率，单位是meters/pixel 。

origin:图中左下角像素的二维位姿，如（x，y，yaw），yaw逆时针旋转(yaw=0表示没有旋转)。系统的很多部分现在忽略yaw值。

negate:无论白色或黑色，占用或自由，语义应该是颠倒的（阈值的解释不受影响）。

occupied_thresh:像素占用率大于这个阈值则认为完全占用。

free_thresh:像素占用率比该阈值小被则认为完全自由。

