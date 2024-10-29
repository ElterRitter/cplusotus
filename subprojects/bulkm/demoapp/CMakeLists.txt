cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Bulkm VERSION 0.1 LANGUAGES CXX)

find_package(Boost REQUIRED)

set(SRC_MAIN src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SRC_MAIN})

source_group("Sources" "${SOURCES};${SRC_MAIN}")
source_group("Headers" ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/hdr)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_WIN)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_UNIX)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options Boost::headers async)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
