cmake_minimum_required(VERSION 3.15)

project(XBullet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.cpp")

add_library(xbullet SHARED ${SOURCES})

find_package(JNI REQUIRED)

target_include_directories(xbullet PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies"
    ${JNI_INCLUDE_DIRS}
)

set(JOLTJNI_LIB_DIR "")

if(WIN32)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/windows-x86_64")
    endif()
elseif(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/macos-x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/macos-aarch64")
    endif()
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/linux-x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/linux-aarch64")
    endif()
endif()

if(JOLTJNI_LIB_DIR)

    target_link_directories(xbullet PRIVATE ${JOLTJNI_LIB_DIR})

    target_link_libraries(xbullet PRIVATE joltjni)

    if (MSVC)
        target_link_options(xbullet PRIVATE "/WHOLEARCHIVE:joltjni.lib")
    endif()

    message(STATUS "✅ joltjni gefunden: ${JOLTJNI_LIB_DIR}")
else()
    message(FATAL_ERROR "❌ Unsupported OS/Architecture: joltjni library nicht gefunden.")
endif()

target_link_libraries(xbullet PRIVATE ${JNI_LIBRARIES})

message(STATUS "JNI_INCLUDE_DIRS: ${JNI_INCLUDE_DIRS}")
message(STATUS "JNI_LIBRARIES: ${JNI_LIBRARIES}")