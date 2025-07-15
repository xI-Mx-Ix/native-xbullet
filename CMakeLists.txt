cmake_minimum_required(VERSION 3.15)
project(XBullet)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# JNI finden
find_package(JNI REQUIRED)

# Include-Pfade
include_directories(
    include               # Deine lokalen Header (falls vorhanden)
    dependencies          # Hier liegt dein Jolt-Ordner, damit #include <Jolt/...> funktioniert
    ${JNI_INCLUDE_DIRS}   # JNI Header (Platform-spezifisch)
)

add_library(xbullet SHARED ${SOURCES})

# JNI und evtl. andere Libraries linken
target_link_libraries(xbullet PRIVATE ${JNI_LIBRARIES})
