cmake_minimum_required(VERSION 3.16)

project(GotusEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost REQUIRED)

set(SOURCES src/main.cpp
            forms/mwnd.cpp
            src/renderpanel.cpp
            src/qsettingsstorage.cpp
            src/gotusdocument.cpp
            src/rendercontext.cpp
            src/gotuscircle.cpp
            src/gotuspoint.cpp
            src/gotuselementfabric.cpp
            src/documentstorage.cpp
        )

set(HEADERS forms/mwnd.h
            hdr/igotuselement.h
            hdr/internaltypes.h
            hdr/isettingsstorage.h
            hdr/gotuselementfabric.h
            hdr/qsettingsstorage.h
            hdr/renderpanel.h
            hdr/gotusdocument.h
            hdr/rendercontext.h
            hdr/gotuscircle.h
            hdr/gotuspoint.h
            hdr/documentstorage.h
            hdr/uuidgenerator.h
        )

set(FORMS forms/mwnd.ui)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} )

source_group("Sources" ${SOURCES})
source_group("Headers" ${HEADERS})
source_group("Forms" ${FORMS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Boost::boost)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/hdr ${PROJECT_SOURCE_DIR}/forms)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE
                                                 CXX_STANDARD 14
                                                 CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
