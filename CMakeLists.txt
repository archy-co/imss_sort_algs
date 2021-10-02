cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME sort)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_MODULE_PATH "~/Downloads/cmake/externals/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
set(SANITIZE_ADDRESS OFF)
set(SANITIZE_UNDEFINED OFF)
#set(SANITIZE_MEMORY ON)

find_package(Sanitizers)

set(SORT_ALGORITHMS ${CMAKE_SOURCE_DIR}/include/algorithms.h ${CMAKE_SOURCE_DIR}/src/algorithms.cpp ${CMAKE_SOURCE_DIR}/src/insertion_sort.cpp ${CMAKE_SOURCE_DIR}/src/merge_sort.cpp ${CMAKE_SOURCE_DIR}/src/selection_sort.cpp ${CMAKE_SOURCE_DIR}/src/shell_sort.cpp)
set(OTHER_DEPS ${CMAKE_SOURCE_DIR}/src/experiment.cpp ${CMAKE_SOURCE_DIR}/include/experiment.h)

add_executable(${PROJECT_NAME} ${SORT_ALGORITHMS} ${OTHER_DEPS} ${CMAKE_SOURCE_DIR}/main.cpp)
add_sanitizers(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})


set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

