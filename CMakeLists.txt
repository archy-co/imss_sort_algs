cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME sort)
project(${PROJECT_NAME} CXX)


add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/algrorithms.cpp ${CMAKE_SOURCE_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
