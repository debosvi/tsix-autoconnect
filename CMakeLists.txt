cmake_minimum_required(VERSION 3.1.0)

project(tsix-autoconnect)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)

add_definitions(-Wall -Werror)

add_executable(lock_app
    main.cpp
)

target_link_libraries(lock_app Qt5::Core)

add_custom_target(deliver ALL
	COMMAND ${CMAKE_COMMAND} -DOUT_DIR=${PROJECT_BINARY_DIR} -P ${PROJECT_SOURCE_DIR}/cmake/deliver.cmake
	DEPENDS lock_app
)