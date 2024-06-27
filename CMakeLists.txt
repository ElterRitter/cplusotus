cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# generate version information from git
set(OTUS_PROJECT_VERSION "0.1.0")
set(OTUS_PROJECT_VERSION_FULL "${OTUS_PROJECT_VERSION}.g0000000")
find_package(Git QUIET)
if(Git_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} "describe" "--tags" "--long"  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                                                            RESULTS_VARIABLE GIT_DESCRIBE_RET
                                                                            OUTPUT_VARIABLE GIT_PROJECT_DESCRIPTION)
    if(GIT_PROJECT_DESCRIPTION)
        string(STRIP ${GIT_PROJECT_DESCRIPTION} GIT_PROJECT_DESCRIPTION)
        string(REPLACE "." ";" LIST_VERSIONS ${GIT_PROJECT_DESCRIPTION})
        string(REPLACE "-" ";" LIST_VERSIONS "${LIST_VERSIONS}")

        list(GET LIST_VERSIONS 0 OTUS_PROJECT_VERSION_MAJOR)
        list(GET LIST_VERSIONS 1 OTUS_PROJECT_VERSION_MINOR)
        list(GET LIST_VERSIONS 2 OTUS_PROJECT_VERSION_PATCH)
        list(GET LIST_VERSIONS 3 OTUS_PROJECT_VERSION_REVISION)
        set(OTUS_PROJECT_VERSION "${OTUS_PROJECT_VERSION_MAJOR}.${OTUS_PROJECT_VERSION_MINOR}.${OTUS_PROJECT_VERSION_PATCH}")
        set(OTUS_PROJECT_VERSION_FULL "${OTUS_PROJECT_VERSION}.${OTUS_PROJECT_VERSION_REVISION}")
    else()
        set(OTUS_PROJECT_VERSION_PATCH "-1")
    endif()
endif()

# defina a project
project(OtusLessions LANGUAGES CXX VERSION ${OTUS_PROJECT_VERSION})
message(STATUS "Project ${PROJECT_NAME} have version ${OTUS_PROJECT_VERSION_FULL}")

# define variables and make version header
set(VERSION_STRING "${OTUS_PROJECT_VERSION_FULL}")
set(BUILD_NUMBER ${OTUS_PROJECT_VERSION_PATCH})
set(VERSION_HEADER "${PROJECT_BINARY_DIR}/versionInfo.h")
configure_file(${PROJECT_SOURCE_DIR}/misc/versioninfo.h.in ${VERSION_HEADER} @ONLY)

# define project sources and headers
set(SRCS src/main.cpp)
set(HDRS "")

# append version header to project headers
list(APPEND HDRS ${VERSION_HEADER})

# define executable target with sources and headers
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

# define a source groups ( helpfull for some IDEs )
source_group("Sources" FILES ${SRCS})
source_group("Headers" FILES ${HDRS})

# add binary dir as an include directory ( for version header )
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})


# testing
enable_testing()
find_package(GTest QUIET)
if(BUILD_TESTS AND GTest_FOUND)
    set(TESTING_TARGET "${PROJECT_NAME}_TEST")
    set(SRC_TESTS "tests/test_version.cpp")
    add_executable(${TESTING_TARGET} ${SRC_TESTS})
    target_include_directories(${TESTING_TARGET} PRIVATE ${PROJECT_BINARY_DIR})
    gtest_discover_tests(${TESTING_TARGET})
    target_link_libraries(${TESTING_TARGET} PRIVATE GTest::GTest GTest::Main)
elseif(NOT GTest_FOUND)
    message(WARNING "Can't find GTest library needed for testing ${PROJECT_NAME}")
elseif(NOT BUILD_TESTS)
    message(WARNING "Unit-testing is disabled for {PROJECT_NAME}")
endif()
