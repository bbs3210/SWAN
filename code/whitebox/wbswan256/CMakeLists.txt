﻿#1.cmake verson，指定cmake版本
cmake_minimum_required(VERSION 3.2)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(wbswan_256)

#3.head file path，头文件目录
INCLUDE_DIRECTORIES(include)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c99 -g3")
#4.source directory，源文件目录
AUX_SOURCE_DIRECTORY(library LIB_SRCS)
AUX_SOURCE_DIRECTORY(library/m4ri LIB_SRCS)
AUX_SOURCE_DIRECTORY(library/math LIB_SRCS)

# SWAN

AUX_SOURCE_DIRECTORY(library/wbswan LIB_SRCS)
AUX_SOURCE_DIRECTORY(library/wbswan256 LIB_SRCS)


#test
AUX_SOURCE_DIRECTORY(test TEST_EXEC)
AUX_SOURCE_DIRECTORY(test/util TEST_EXEC)

# set name for build
SET(BUILD_NAME ${PROJECT_NAME})
SET(TEST_EXEC_NAME ${PROJECT_NAME}_MAIN)

ADD_LIBRARY(${BUILD_NAME} SHARED ${LIB_SRCS})
ADD_EXECUTABLE(${TEST_EXEC_NAME} ${LIB_SRCS} ${TEST_EXEC})
target_link_libraries(${TEST_EXEC_NAME} m)
