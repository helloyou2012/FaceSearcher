if [ $(id -u) != "0" ]; then
    echo "错误：您需要使用管理员权限安装，请运行sudo ./my.sh."
    exit 1
fi
apt-get install cmake
apt-get install libv4l-dev
cur_dir=$(pwd)
apt-get install build-essential libgtk2.0-dev libjpeg62-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy libtbb-dev libeigen2-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev
echo "=========================== ffmpeg intalling========================"
cd $cur_dir
if [ -s ffmpeg-0.7-rc1.tar.gz ]; then
echo "ffmpeg-0.7-rc1.tar.gz [found]"
else
echo "Error: ffmpeg-0.7-rc1.tar.gz not found!!!download now......"
wget -c http://ffmpeg.org/releases/ffmpeg-0.7-rc1.tar.gz
fi
tar zxvf ffmpeg-0.7-rc1.tar.gz
cd ffmpeg-0.7-rc1
./configure --enable-gpl --enable-version3 --enable-nonfree --enable-postproc --enable-libfaac --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libtheora --enable-libvorbis --enable-libxvid --enable-x11grab --enable-swscale --enable-shared
make&&make install
cd ../
echo "=========================== OpenCV intalling========================"
cd $cur_dir
if [ -s OpenCV-2.2.0.tar.bz2 ]; then
echo "OpenCV-2.2.0.tar.bz2 [found]"
else
echo "Error: OpenCV-2.2.0.tar.bz2 not found!!!download now......"
wget -c http://downloads.sourceforge.net/project/opencvlibrary/opencv-unix/2.2/OpenCV-2.2.0.tar.bz2
fi
tar jxvf OpenCV-2.2.0.tar.bz2
cd OpenCV-2.2.0
sed -i '21 i#cmakedefine HAVE_LIBV4L' cvconfig.h.cmake
sed -i 's/^        #if defined (HAVE_CAMV4L) || defined (HAVE_CAMV4L2)/        #if defined HAVE_LIBV4L || (defined (HAVE_CAMV4L) \&\& defined (HAVE_CAMV4L2))/' modules/highgui/src/cap.cpp
sed -i 's/^#if !defined WIN32 \&\& defined HAVE_CAMV4L \&\& defined HAVE_CAMV4L2/#if !defined WIN32 \&\& defined HAVE_LIBV4L/' modules/highgui/src/cap_libv4l.cpp
sed -i '244 i#ifdef HAVE_CAMV4L' modules/highgui/src/cap_libv4l.cpp
sed -i '246 i#endif' modules/highgui/src/cap_libv4l.cpp
sed -i '247 i#ifdef HAVE_CAMV4L2' modules/highgui/src/cap_libv4l.cpp
sed -i '249 i#endif' modules/highgui/src/cap_libv4l.cpp
sed -i 's/^#include <linux\/videodev.h>/#include <libv4l1-videodev.h>/' modules/highgui/src/cap_v4l.cpp
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_TBB=ON -D WITH_V4L=OFF -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON ..
make&&make install
cd ../
cd ../
echo "=========================== Configuring========================"
touch /etc/ld.so.conf.d/opencv.conf
echo "/usr/local/lib" >/etc/ld.so.conf.d/opencv.conf
ldconfig
echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" >>/etc/bash.bashrc
echo "export PKG_CONFIG_PATH" >>/etc/bash.bashrc
echo "=========================== Complete!========================"
cd $cur_dir
cd OpenCV-2.2.0/samples/c
chmod +x build_all.sh
./build_all.sh
./facedetect --cascade="/usr/local/share/opencv/haarcascades/haarcascade_frontalface_alt.xml" --scale=1.5 lena.jpg