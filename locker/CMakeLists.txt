
set(LOCKER_BIN backend_locker)

add_executable(${LOCKER_BIN}
	SignalHandler.cpp
	DbLocker.cpp
    main.cpp
)

target_link_libraries(${LOCKER_BIN}
	Qt5::Core
)

# delivery targets
add_custom_target(deliver_locker 
	COMMAND ${CMAKE_COMMAND} -DOUT_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY} -DBIN_NAME=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${LOCKER_BIN} -P ${PROJECT_SOURCE_DIR}/cmake/deliver.cmake
	DEPENDS ${LOCKER_BIN}
	COMMENT "Deliver Backend Locker"
)
add_dependencies(deliver deliver_locker)


# delivery targets
add_custom_target(clean_locker 
	COMMAND ${CMAKE_COMMAND}  -DCLEAN=1 -DOUT_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY} -DBIN_NAME=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${LOCKER_BIN} -P ${PROJECT_SOURCE_DIR}/cmake/deliver.cmake
	COMMENT "Clean Backend Locker"
)
add_dependencies(clean-all clean_locker)

