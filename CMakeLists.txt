cmake_minimum_required(VERSION 3.10)
project(da_t2)

set(CMAKE_CXX_STANDARD 17)

set(CREATE_EXE TRUE)

add_executable(da_t2 main.cpp include/objs.h include/readFiles.h src/readFiles.cpp
        include/minHeap.h include/graph.h src/graph.cpp include/menu.h src/menu.cpp)


