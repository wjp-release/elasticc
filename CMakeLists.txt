# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("elasticc")
    
set(CMAKE_CXX_FLAGS_RELEASE "/MD")   
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")

include_directories(./libcurl-x64-debug/include)
link_directories(./libcurl-x64-debug/lib)

# 包含子项目。
add_subdirectory ("elasticc")
