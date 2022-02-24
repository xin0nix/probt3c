# Basic config
cmake_minimum_required(VERSION 3.16.3)
project(probt3c CXX)

# RapidCheck config
if(NOT RAPIDCHECK_INCLUDE_DIR)
    message( FATAL_ERROR "Please specify RAPIDCHECK_INCLUDE_DIR" )
endif()
if(NOT RAPIDCHECK_LIB_DIR)
    message( FATAL_ERROR "Please specify RAPIDCHECK_LIB_DIR" )
endif()

# Dependencies used throught the code like includes, libs, flags and so on
set(PROBT3C_INCLUDE_DIRECTORIES "")
set(PROBT3C_LIBRARIES "")

list(APPEND PROBT3C_INCLUDE_DIRECTORIES ${RAPIDCHECK_INCLUDE_DIR})
list(APPEND PROBT3C_LIBRARIES "${RAPIDCHECK_LIB_DIR}/librapidcheck.a")

add_subdirectory(src)

# Check whether the dependencies have been properly initialized
message(STATUS "PROBT3C_INCLUDE_DIRECTORIES: ${PROBT3C_INCLUDE_DIRECTORIES}")
message(STATUS "PROBT3C_LIBRARIES: ${PROBT3C_LIBRARIES}")

# Apply everything to the target
include_directories(${PROBT3C_INCLUDE_DIRECTORIES})
add_executable(probt3c probt3c.cpp)
target_link_libraries(probt3c PRIVATE ${PROBT3C_LIBRARIES})
