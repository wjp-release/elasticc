# CMakeList.txt: elasticc 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 静态链接libcurl
add_definitions(-DCURL_STATICLIB)

# 将源代码添加到此项目的可执行文件。
add_executable (elasticc "elasticc.cpp" "elasticc.h")
# libcurl依赖一些库也要链接进来
target_link_libraries(elasticc libcurl_a.lib ws2_32.lib Wldap32.lib winmm.lib Crypt32.lib normaliz.lib)

# TODO: 如有需要，请添加测试并安装目标。
