cmake_minimum_required(VERSION 2.8.11)

project(s6)

add_executable(test_behaviour test_behaviour.c)
target_link_libraries(test_behaviour behaviour)
