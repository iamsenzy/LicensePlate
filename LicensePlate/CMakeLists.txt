project(LicensePlate)
cmake_minimum_required(VERSION 3.19)

add_executable(LicensePlate main.cpp LicensePlateDetection.cpp LicensePlateDetection.h Includes.h)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
