cmake_minimum_required(VERSION 3.10)
project(da_t2)

set(CMAKE_CXX_STANDARD 17)

set(CREATE_EXE TRUE)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(da_t2 main.cpp include/objs.h include/readFiles.h src/readFiles.cpp
        include/minHeap.h include/graph.h src/graph.cpp include/menu.h src/menu.cpp Tests/maxHeapTests.cpp include/maxHeap.h)

target_link_libraries(da_t2 gtest gtest_main)
