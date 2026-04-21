
cmake_minimum_required(VERSION 3.10)
project(WEB_Server C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_library(UUID_LIB NAMES uuid REQUIRED)

file(GLOB SOURCES "src/*.c")
file(GLOB LIB_FILES "bin/*.c")

add_library(mylib ${LIB_FILES})
target_include_directories(mylib PUBLIC include)


target_link_libraries(mylib PUBLIC Threads::Threads ${UUID_LIB})

add_executable(web_server ${SOURCES})
target_link_libraries(web_server PRIVATE mylib)
