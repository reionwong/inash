cmake_minimum_required(VERSION 3.14)

project(inash)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(IMOBILEDEVICE REQUIRED libimobiledevice-1.0)
message(STATUS "libimobiledevice: ${IMOBILEDEVICE_INCLUDE_DIRS} ${IMOBILEDEVICE_LIBRARIES}")

set(PROJECT_SOURCES
    src/main.cpp
    src/idevice.cpp
    src/devicemanager.cpp
    src/devicemodel.cpp
    src/ieventmonitor.cpp
    qml.qrc
)

add_executable(inash
    ${PROJECT_SOURCES}
)

target_link_libraries(inash
  PRIVATE
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
  ${IMOBILEDEVICE_LDFLAGS}
)
