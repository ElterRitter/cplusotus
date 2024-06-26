cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(OTUS_PROJECT_VERSION "0.1.0")
# find_package(Git QUIET)
# if(Git_FOUND)
#     execute_process(COMMAND ${GIT_EXECUTABLE} "describe --long" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                                                                 RESULTS_VARIABLE GIT_DESCRIBE_RET
#                                                                 OUTPUT_VARIABLE GIT_PROJECT_DESCRIPTION)
#     message(STATUS "GIT_PROJECT_DESCRIPTION = ${GIT_PROJECT_DESCRIPTION}")
# endif()

# defina a project
project(OtusLessions LANGUAGES CXX VERSION ${OTUS_PROJECT_VERSION})

# define variables and make version header
set(VERSION_STRING "${OTUS_PROJECT_VERSION}")
set(BUILD_NUMBER 0)
set(VERSION_HEADER "${PROJECT_BINARY_DIR}/versionInfo.h")
configure_file(${PROJECT_SOURCE_DIR}/misc/versioninfo.h.in ${VERSION_HEADER} @ONLY)

# define project sources and headers
set(SRCS src/main.cpp)
set(HDRS "")

# append version header
list(APPEND HDRS ${VERSION_HEADER})

# define executable target
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

# define a source groups ( helpfull for some IDEs )
source_group("Sources" FILES ${SRCS})
source_group("Headers" FILES ${HDRS})

# add binary dir as an include directory ( for version header )
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})


