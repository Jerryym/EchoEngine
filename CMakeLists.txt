# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.16)

#设置版本号
set(ECHO_VERSION_MAJOR 0)
set(ECHO_VERSION_MINOR 3)
set(ECHO_VERSION_PATCH 0)
set(ECHO_VERSION "${ECHO_VERSION_MAJOR}.${ECHO_VERSION_MINOR}.${ECHO_VERSION_PATCH}")
message(STATUS "EchoEngine Version: ${ECHO_VERSION}")
project(EchoEngine VERSION ${ECHO_VERSION} LANGUAGES CXX)