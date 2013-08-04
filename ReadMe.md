FaceSearcher
==============
##介绍

本软件用于在大量图片中搜索含有人脸的图片，同时显示出来，操作系统为Linux（Ubuntu）开发语言采用C++，人脸识别算法采用OpenCV开源框架，软件UI采用Qt组件。 [软件视频](FaceSearcher.mpeg)

##环境搭建
1. 配置OpenCV：本人写了一个shell脚本[OpenCV-install.sh](OpenCV-install.sh)，可以直接运行安装OpenCV,详细也可见本人博客：[Linux(Ubuntu 11.04)中一键安装OpenCV-2.2](http://blog.sina.com.cn/s/blog_69b6a7c601010hsn.html)
		sudo chmod +x OpenCV-install.sh
		sudo ./OpenCV-install.sh2. 安装配置QT开发组件，命令如下：
		sudo apt-get install qt4-dev-tools qt4-doc qt4-qtconfig qt4-designer