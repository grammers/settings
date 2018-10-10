cmake_minimum_required(VERSION 3.0)
project(settings)

find_package(catkin_simple REQUIRED)

catkin_simple()

cs_add_executable(${PROJECT_NAME} src/settings_node.cpp)

cs_install()

cs_export()
