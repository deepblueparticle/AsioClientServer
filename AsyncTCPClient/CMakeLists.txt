cmake_minimum_required(VERSION 2.6)
project(AsyncTCPClient)

add_executable(AsyncTCPClient src/TCPClient.cpp src/AsyncTCPClient.cpp)
target_link_libraries (AsyncTCPClient boost_system)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
