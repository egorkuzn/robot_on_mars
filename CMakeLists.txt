cmake_minimum_required(VERSION 3.0.0)
project(robot_on_mars VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB cmode.cpp
                collector.cpp
                data.cpp
                getch.cpp
                item.cpp
                robot.cpp
                planet.cpp
                ui.cpp
                sapper.cpp   )

add_library(libs STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main libs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
