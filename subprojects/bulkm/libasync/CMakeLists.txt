cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(async VERSION 0.1 LANGUAGES CXX)

find_package(Boost REQUIRED)

set(SOURCES src/commandprocessor.cpp
            src/command.cpp
            src/commandfabric.cpp
            src/listcommadstorage.cpp
            src/bulkprinterfile.cpp
            src/bulkprinterconsole.cpp
            src/bulkprocessor.cpp
            src/libasync.cpp)

set(HEADERS hdr/commandprocessor.h
            hdr/command.h
            hdr/icommand.h
            hdr/commandfabric.h
            hdr/icommandstorage.h
            hdr/listcommadstorage.h
            hdr/ibulkprinter.h
            hdr/bulkprinterfile.h
            hdr/ibulkpublisher.h
            hdr/bulkprinterconsole.h
            hdr/bulkprocessor.h
            hdr/libasync.h)


add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Sources" ${SOURCES})
source_group("Headers" ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/hdr)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_WIN)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DOS_UNIX)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options Boost::headers)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
