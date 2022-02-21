cmake_minimum_required(VERSION 3.16.3)
project(probt3c CXX)

if(NOT RAPIDCHECK_INCLUDE_DIR)
    message( FATAL_ERROR "Please specify RAPIDCHECK_INCLUDE_DIR" )
endif()

if(NOT RAPIDCHECK_LIB_DIR)
    message( FATAL_ERROR "Please specify RAPIDCHECK_LIB_DIR" )
endif()

include_directories(${RAPIDCHECK_INCLUDE_DIR})
add_executable(probt3c probt3c.cpp)

target_link_libraries(probt3c PRIVATE ${RAPIDCHECK_LIB_DIR}/librapidcheck.a)
