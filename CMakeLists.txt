cmake_minimum_required(VERSION 3.27)
project(GPU_MPM CXX)

find_package(PDAL 2.0.0 REQUIRED CONFIG)

if(NOT WIN32)
    find_program(HAS_CCACHE "ccache")
    if(HAS_CCACHE)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    endif()
endif()

if(WIN32)
    set(ARCH x64)
    add_definitions(-D_WIN64=1)
    link_directories("lib/windows/vs160${ARCH}")
elseif(APPLE)
    execute_process(COMMAND uname -m
            OUTPUT_VARIABLE CMAKE_OSX_ARCHITECTURES
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(ARCH ${CMAKE_OSX_ARCHITECTURES})
    add_definitions(-D_MACOS=1)
    link_directories("lib/macos/${ARCH}")
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE
        include/tellusim include/lib src
        ${PDAL_INCLUDE_DIRS}
        ${PDAL_INCLUDE_DIRS}/pdal)

target_link_libraries(${PROJECT_NAME} Tellusim_${ARCH}d  ${PDAL_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")