cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Matrix VERSION 0.1 LANGUAGES CXX)

find_package(Boost REQUIRED)

set(SOURCES src/main.cpp)

set(HEADERS hdr/matrix.h hdr/unlmatrix.h )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Sources" ${SOURCES})
source_group("Headers" ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/hdr)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::program_options)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
