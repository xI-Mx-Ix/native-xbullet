cmake_minimum_required(VERSION 3.15)

project(XBullet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    message(STATUS "Found and configured joltjni for this platform in: ${JOLTJNI_LIB_DIR}")

    target_link_directories(xbullet PRIVATE ${JOLTJNI_LIB_DIR})

    # Wichtig: Linke explizit die joltjni.lib, damit Abhängigkeit entsteht!
    target_link_libraries(xbullet PRIVATE
        joltjni
        ${JNI_LIBRARIES}
    )
else()
    message(FATAL_ERROR "Unsupported OS/Architecture combination. Could not find a matching joltjni library.")
endif()
