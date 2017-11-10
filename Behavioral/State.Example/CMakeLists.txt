get_filename_component(PROJECT_NAME_STR ${CMAKE_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${PROJECT_NAME_STR})

cmake_minimum_required(VERSION 2.8)
project(${PROJECT_NAME_STR})

#----------------------------------------
# set compiler
#----------------------------------------
add_definitions(-std=c++14)

#----------------------------------------
# set Threads
#----------------------------------------
find_package(Threads REQUIRED)

#----------------------------------------
# Application
#----------------------------------------

# Sources
aux_source_directory(./src SRC_LIST)

# Headers
file(GLOB HEADERS_LIST "./src/*.h" "./src/*.hpp") 
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_lib)
add_library(${PROJECT_LIB_NAME} ${SRC_LIST})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB_NAME})

if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

enable_testing()
add_subdirectory(tests)