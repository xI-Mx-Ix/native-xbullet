# Mindestversion für CMake festlegen
cmake_minimum_required(VERSION 3.15)

# Projektname definieren
project(XBullet LANGUAGES CXX)

# C++17 Standard verwenden
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# --- Quellcode-Dateien und Bibliothek definieren ---
file(GLOB SOURCES "src/*.cpp")
add_library(xbullet SHARED ${SOURCES})

# --- JNI finden ---
find_package(JNI REQUIRED)

# --- Header-Verzeichnisse für xbullet ---
target_include_directories(xbullet PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Jolt"
    ${JNI_INCLUDE_DIRS}
)


# ==============================================================================
#  DAS HERZSTÜCK: Plattform- und Architektur-spezifisches Linken gegen joltjni
# ==============================================================================

# Variable, die den Pfad zum korrekten lib-Ordner speichern wird
set(JOLTJNI_LIB_DIR "")

# CMake-Variable für die Prozessor-Architektur prüfen
# Übliche Werte: "x86_64", "AMD64", "aarch64", "arm64"

# --- 1. Fall: Windows ---
if(WIN32)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/windows-x86_64")
    endif()

# --- 2. Fall: macOS ---
elseif(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/macos-x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/macos-aarch64")
    endif()

# --- 3. Fall: Linux (und andere Unix-Systeme) ---
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/linux-x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(JOLTJNI_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/linux-aarch64")
    endif()
endif()

# --- Linken, aber nur wenn eine passende Bibliothek gefunden wurde ---
if(JOLTJNI_LIB_DIR)
    # Dem Linker sagen, wo er suchen soll
    target_link_directories(xbullet PRIVATE ${JOLTJNI_LIB_DIR})

    # Gegen "joltjni" linken. CMake findet die .lib, .so oder .dylib automatisch.
    # Dies ist der Befehl, der die Verknüpfung zu Jolt Physics herstellt.
    target_link_libraries(xbullet PRIVATE joltjni)
    
    message(STATUS "Found and configured joltjni for this platform in: ${JOLTJNI_LIB_DIR}")
else()
    # Build abbrechen, wenn die Kombination nicht unterstützt wird
    message(FATAL_ERROR "Unsupported OS/Architecture combination. Could not find a matching joltjni library.")
endif()


# --- Zum Schluss gegen die JNI-Bibliotheken linken ---
target_link_libraries(xbullet PRIVATE ${JNI_LIBRARIES})