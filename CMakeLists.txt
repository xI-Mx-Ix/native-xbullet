cmake_minimum_required(VERSION 3.15)
project(XBullet)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(
    include
    dependencies/Jolt
    dependencies/JNI
)


add_library(xbullet SHARED ${SOURCES})
