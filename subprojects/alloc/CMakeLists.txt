cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

option(USE_TESTING "Including unit tests" OFF)

project(allocator LANGUAGES CXX VERSION 0.1)

#target_compile_definitions(-D_USE_MATH_DEFINES)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(HEADERS src/allocatorfixed.h src/mylist.h src/factorial.h)
set(SOURCES src/main.cpp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)

source_group ("Sources" FILES ${SOURCES})
source_group ("Headers" FILES ${HEADERS})


if(USE_TESTING)
	add_library(${PROJECT_NAME}_STATIC STATIC ${SOURCES} ${HEADERS})
    set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 14
                                                            CXX_STANDARD_REQUIRED ON)
endif()

if(USE_TESTING)
	add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()
