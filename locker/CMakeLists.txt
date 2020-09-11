
set(LOCKER_BIN backend_locker)

add_executable(${LOCKER_BIN}
	SignalHandler.cpp
	DbLocker.cpp
    main.cpp
)

target_link_libraries(${LOCKER_BIN}
	Qt5::Core
)

#### INSTALL
install(TARGETS ${LOCKER_BIN} 
	RUNTIME DESTINATION bin
)

# delivery targets
get_filename_component(RELARCHIVE ${CMAKE_INSTALL_PREFIX} NAME)
if(${CYGWIN}) 
	add_custom_target(deliver_locker 
		COMMAND ${CMAKE_COMMAND} 
			-DOUT_DIR="${CMAKE_INSTALL_PREFIX}/bin" 
			-DBIN_NAME="${CMAKE_INSTALL_PREFIX}/bin/${LOCKER_BIN}" 
			-P ${PROJECT_SOURCE_DIR}/cmake/deliver-cygwin.cmake
		COMMAND bash -c "tar -cvf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.tar.bz2 -C ${CMAKE_BINARY_DIR}/ ./${RELARCHIVE}/ "
		DEPENDS ${LOCKER_BIN} 
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
		COMMENT "Deliver Backend Locker"
	)
	add_dependencies(deliver deliver_locker)
elseif(${WIN32})
	add_custom_target(deliver_locker 
		COMMAND ${CMAKE_COMMAND} 
			-DSYSROOT="${CMAKE_FIND_ROOT_PATH}" 
			-DOUT_DIR="${CMAKE_INSTALL_PREFIX}/bin" 
			-DBIN_NAME="${CMAKE_INSTALL_PREFIX}/bin/${LOCKER_BIN}" 
			-P ${PROJECT_SOURCE_DIR}/cmake/deliver-mingw.cmake
		COMMAND bash -c "tar -cvf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.tar.bz2 -C ${CMAKE_BINARY_DIR}/ ./${RELARCHIVE}/ "
		DEPENDS ${LOCKER_BIN} 
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
		COMMENT "Deliver Backend Locker"
	)
	add_dependencies(deliver deliver_locker)
endif()



