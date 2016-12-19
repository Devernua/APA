cmake_minimum_required(VERSION 3.6)
project(APA)

#set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c APA.h APA.c)
add_executable(APA ${SOURCE_FILES})