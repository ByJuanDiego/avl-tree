cmake_minimum_required(VERSION 3.24)
project(avl_tree)

include_directories("./include" "./src")

set(CMAKE_CXX_STANDARD 20)

add_executable(avl_tree src/main.cpp src/avltree.cpp include/avltree.hpp src/node.cpp include/node.hpp)
