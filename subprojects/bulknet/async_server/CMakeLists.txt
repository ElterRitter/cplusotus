cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(BulkServer)

find_package(Boost REQUIRED)

set(SOURCES src/main.cpp
            src/bulkserver.cpp
            src/tcpsession.cpp
            src/netcommandprocessor.cpp)

set(HEADERS hdr/bulkserver.h
            hdr/tcpsession.h
            hdr/netcommandprocessor.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Sources" ${SOURCES})
source_group("Headers" ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/hdr)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_WIN)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_UNIX)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options Boost::headers asyncnet)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
