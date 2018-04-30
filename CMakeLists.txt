PROJECT(lsys)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES(src)

FILE(GLOB sources src/lsys/*.cpp src/lsys/machinedesc/*.cpp src/os/*.cpp)
ADD_LIBRARY(lsys STATIC ${sources})

ADD_SUBDIRECTORY(demos)
