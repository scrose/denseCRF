project(densecrf)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # symbol generation
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG") # enable C++17 standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # enable C++17 standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # enable C++17 standard

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


include_directories( include )

add_subdirectory (src)
add_subdirectory (examples)
add_subdirectory (external)
