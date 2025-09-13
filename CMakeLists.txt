cmake_minimum_required(VERSION 4.1.1)

project(
    "Chromium Based Browser API"
    VERSION 1.0.0
    LANGUAGES C
)

# C Standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

# Flags for Debug
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -Wextra")

# Flags for Release
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -march=native -flto -funroll-loops -fomit-frame-pointer")

# Linker flags Release
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")

# CCACHE
find_program(CCACHE_PROGRAM "ccache")
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

# Set build shared library to OFF
set(BUILD_SHARED_LIBS OFF)

# FetchContent
include(FetchContent)

# JSON-C (JSON library)
FetchContent_Declare(
    "json-c"
    GIT_REPOSITORY https://github.com/json-c/json-c
    GIT_TAG json-c-0.18-20240915
)
FetchContent_MakeAvailable("json-c")

# Naett (Tiny HTTP client library)
FetchContent_Declare(
    "naett"
    GIT_REPOSITORY https://github.com/erkkah/naett
    GIT_TAG "v0.3.3"
)

FetchContent_MakeAvailable("naett")

add_library(
    "naett"
    STATIC
    "${naett_SOURCE_DIR}/naett.c"
)

target_include_directories(
    "naett"
    INTERFACE
    "${naett_SOURCE_DIR}"
)

# wsServer (Tiny WebSocket server library)
FetchContent_Declare(
    "wsServer"
    GIT_REPOSITORY https://github.com/Theldus/wsServer
    GIT_TAG "5ef631d1bb6c6ea51abd156b05b1f11147bfdba4"
)

FetchContent_MakeAvailable("wsServer")

# CBBAPI LIB
file(
    GLOB_RECURSE
    "CBBAPI_SOURCE_FILES"
    "src/*.c"
)

add_library(
    "cbbapi"
    STATIC
    ${CBBAPI_SOURCE_FILES}
)

target_include_directories(
    "cbbapi"
    PRIVATE
    "include/private"
    INTERFACE
    "include/interface"
)

if (WIN32)
    target_link_libraries(
        "cbbapi"
        PRIVATE
        "ws2_32"
        "winhttp"
    )
endif()

target_link_libraries(
    "cbbapi"
    PRIVATE
    "json-c"
    "naett"
    "ws"
)

# Examples
add_subdirectory("examples")