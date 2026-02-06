cmake_minimum_required(VERSION 3.10)
project(Panorama)

set(CMAKE_CXX_STANDARD 17)

# Calea către OpenCV
set(OpenCV_DIR "C:/OpenCV/opencv/build/x64/vc16/lib")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(panorama src/main.cpp)

target_link_libraries(panorama ${OpenCV_LIBS})
