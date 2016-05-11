cmake_minimum_required(VERSION 2.6)
project(AsyncTCPServer)

add_executable(AsyncTCPServer src/AsyncTCPServer.cpp src/Session.cpp src/TCPServer.cpp)
target_link_libraries (AsyncTCPServer boost_system)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
