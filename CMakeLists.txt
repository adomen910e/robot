cmake_minimum_required(VERSION 2.8.11)

project(s6)

add_library(behaviour behaviour.c)
target_link_libraries(behaviour m)

add_subdirectory(tests)
