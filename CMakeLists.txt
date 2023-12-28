cmake_minimum_required(VERSION 3.27)
project(identicon_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(identicon_cpp main.cpp
        Identicon.cpp
        include/Identicon.h
        Image.cpp
        include/Image.h)