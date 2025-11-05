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
        src/tree.cpp
        src/tree.h
        src/queue.cpp
        src/queue.h
        src/doubly_list.cpp
        src/doubly_list.h
        src/forward_list.cpp
        src/forward_list.h
        src/stack.cpp
        src/stack.h
        src/array.cpp
        src/array.h)
