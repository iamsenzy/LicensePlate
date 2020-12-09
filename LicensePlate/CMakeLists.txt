project(LicensePlate)
cmake_minimum_required(VERSION 3.19)

add_executable(LicensePlate main.cpp LicensePlateDetection.cpp LicensePlateDetection.h Includes.h)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

find_package( PkgConfig REQUIRED)
pkg_search_module( TESSERACT REQUIRED tesseract )
pkg_search_module( LEPTONICA REQUIRED lept )
include_directories( ${TESSERACT_INCLUDE_DIRS} )
include_directories( ${LEPTONICA_INCLUDE_DIRS} )
link_directories( ${TESSERACT_LIBRARY_DIRS} )
link_directories( ${LEPTONICA_LIBRARY_DIRS} )
target_link_libraries( ${PROJECT_NAME} ${TESSERACT_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${LEPTONICA_LIBRARIES} )