cmake_minimum_required(VERSION 4.0)
project(LR1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

if(MSVC)
    add_compile_options(/utf-8)
else()
endif()

add_executable(LR1 main.cpp
        tree.cpp
        tree.h
        queue.cpp
        queue.h
        doubly_list.cpp
        doubly_list.h
        forward_list.cpp
        forward_list.h
        stack.cpp
        stack.h
        array.cpp
        array.h)
