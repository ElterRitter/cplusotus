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

find_package(Boost COMPONENTS program_options CONFIG REQUIRED)

# define variables and make version header
set(VERSION_STRING "${OTUS_PROJECT_VERSION_FULL}")
set(BUILD_NUMBER ${OTUS_PROJECT_VERSION_PATCH})
set(VERSION_HEADER "${PROJECT_BINARY_DIR}/versionInfo.h")
configure_file(${PROJECT_SOURCE_DIR}/misc/versioninfo.h.in ${VERSION_HEADER} @ONLY)

# option for building documentation
option(BUILD_DOCUMENTATION "Create and install documentation ( doxygen requires )" OFF)
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen for building documention - not found")
    endif()
    configure_file(${PROJECT_SOURCE_DIR}/misc/doxyfile.in ${PROJECT_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doxyfile WORKING_DIRECTORY)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EDITOR "Build creator" OFF)
if(BUILD_EDITOR)
    add_subdirectory(subprojects/editor)
endif()

option(BUILD_BULK "Build Bulk task" OFF)
if(BUILD_BULK)
    add_subdirectory(subprojects/bulk)
endif()

option(BUILD_MATRIX "Build Matrix task" OFF)
if(BUILD_MATRIX)
    add_subdirectory(subprojects/matrix)
endif()

option(BUILD_BULK_M "Build Multithreaded Bulk" OFF)
if(BUILD_BULK_M)
    add_subdirectory(subprojects/bulkm)
endif()

option(BUILD_BULK_NET "Build network bulk" OFF)
if(BUILD_BULK_NET)
    add_subdirectory(subprojects/bulknet)
endif()

# define project sources and headers
set(MSRCS src/main.cpp)
set(SRCS src/ipfilter.cpp
)
set(HDRS hdr/ipfilter.h
         hdr/sfinaelesson.h
)

# append version header to project headers
list(APPEND HDRS ${VERSION_HEADER})

# define executable target with sources and headers
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${MSRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON)

# define a source groups ( helpfull for some IDEs )
source_group("Sources" FILES "${SRCS};${MSRCS}")
source_group("Headers" FILES ${HDRS})

# add binary dir as an include directory ( for version header )
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}
                                           PRIVATE ${PROJECT_SOURCE_DIR}/hdr)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
                                           PRIVATE -D_WIN32_WINNT=0x0601)

# link with libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options Boost::headers)


# testing
include(CTest)
find_package(GTest QUIET)
if(BUILD_TESTING AND GTest_FOUND)
    set(TESTING_TARGET "${PROJECT_NAME}_TEST")
    set(SRC_TESTS tests/test_version.cpp tests/test_ipfilter.cpp)
    set(HDR_TESTS tests/test_ipfilter.h)
    add_executable(${TESTING_TARGET} ${SRC_TESTS} ${HDR_TESTS} ${SRCS})
    set_target_properties(${TESTING_TARGET} PROPERTIES CXX_STANDARD 17
                                                       CXX_STANDARD_REQUIRED ON)
    target_include_directories(${TESTING_TARGET} PRIVATE ${PROJECT_BINARY_DIR}
                                                 PRIVATE ${PROJECT_SOURCE_DIR}/hdr)

    target_compile_definitions(${TESTING_TARGET} PRIVATE -D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
                                                          PRIVATE -D_WIN32_WINNT=0x0601)

    gtest_discover_tests(${TESTING_TARGET})
    target_link_libraries(${TESTING_TARGET} PRIVATE GTest::GTest GTest::Main Boost::program_options)
    add_custom_target(COPY_TEST_DATA ALL ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tests/test_data.tsv ${PROJECT_BINARY_DIR}/test_data.tsv)
elseif(NOT GTest_FOUND)
    message(WARNING "Can't find GTest library needed for testing project ${PROJECT_NAME}")
elseif(NOT BUILD_TESTS)
    message(WARNING "Unit-testing is disabled for project ${PROJECT_NAME}")
endif()


# installation
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)


# packaging
if(UNIX)
    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_CONTACT "Aleksei Tihonov <atichonov@yandex.ru>")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libgcc1")
    set(CPACK_STRIP_FILES ON)
    if(NOT DEFINED CPACK_PACKAGE_VERSION)
        set(CPACK_PACKAGE_VERSION "${OTUS_PROJECT_VERSION}")
    endif()

    # detect os version and release number
    find_program( LSB_RELEASE_EXECUTABLE lsb_release )
    execute_process(COMMAND ${LSB_RELEASE_EXECUTABLE} -is
                    OUTPUT_VARIABLE OS_RELEASE_NAME
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND ${LSB_RELEASE_EXECUTABLE} -rs
                    OUTPUT_VARIABLE OS_RELEASE_VERSION
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    # detect architecture
    execute_process(COMMAND "dpkg" "--print-architecture"
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                    RESULT_VARIABLE DPKG_RES
                    OUTPUT_VARIABLE DPKG_ARCH
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                    ERROR_STRIP_TRAILING_WHITESPACE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${OS_RELEASE_NAME}_${OS_RELEASE_VERSION}_${DPKG_ARCH}")
    include(CPack)
endif()
