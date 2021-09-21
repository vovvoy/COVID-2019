cmake_minimum_required(VERSION 3.20)
project(opencv_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp Weapon.cpp Enemy.cpp Game.cpp)
#set(SOURCE_FILES color_detection.cpp)
#set(SOURCE_FILES bla.cpp)+
add_executable( opencv_project ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )