cmake_minimum_required(VERSION 3.1.0)
project(tsix-autoconnect)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)

# some additional settings
add_definitions(-Wall -Werror)

# define custom output dirs
set(PROJECT_CONFIG_DIR ${CMAKE_INSTALL_PREFIX}/etc)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# delivery targets
add_custom_target(deliver ALL
	COMMENT "Deliver addtional stuffs"
)

# clean targets
add_custom_target(distclean
	COMMAND ${CMAKE_BUILD_TOOL} clean
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_CONFIG_DIR}
)

add_subdirectory(locker)
add_subdirectory(catalog)

