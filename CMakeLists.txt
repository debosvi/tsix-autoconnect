cmake_minimum_required(VERSION 3.1.0)
project(tsix-autoconnect)

message(STATUS "CYGWIN: " ${CYGWIN})
message(STATUS "WINDOWS: " ${WIN32})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# some additional settings
add_definitions(-Wall -Werror)

include(cmake/macros.cmake)

# define custom output dirs
set(PROJECT_CONFIG_DIR ${CMAKE_INSTALL_PREFIX}/etc)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.built/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.built/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.built/bin)

# delivery targets
add_custom_target(deliver
	COMMENT "Deliver addtional stuffs"
)

# clean targets
add_custom_target(distclean
	COMMAND ${CMAKE_BUILD_TOOL} clean
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_CONFIG_DIR}
)

add_subdirectory(locker)
add_subdirectory(catalog)

##
get_filename_component(RELARCHIVE ${CMAKE_INSTALL_PREFIX} NAME)
add_custom_target(do_package
	COMMAND bash -c "tar -cf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.tar.bz2 -C ${CMAKE_BINARY_DIR}/ ./${RELARCHIVE}/ "
	DEPENDS deliver
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
	COMMENT "Do final Archive"
)
