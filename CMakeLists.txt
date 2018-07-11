cmake_minimum_required(VERSION 3.10)
project(compress)

include_directories(inc ${Boost_INCLUDE_DIRS} )
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem thread)
link_directories(compress ${Boost_LIBRARY_DIRS})

add_executable(compress
        inc/compress.hpp
        src/main.cpp
        src/parcer.cpp)

target_link_libraries(compress ${Boost_LIBRARIES})

