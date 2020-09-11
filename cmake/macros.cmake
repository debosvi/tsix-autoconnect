
macro(deliver_target target name desc)
	if("${target}" STREQUAL "")
		message(FATAL_ERROR "Must set 'target' to deliver")
	endif()
	if("${name}" STREQUAL "")
		message(FATAL_ERROR "Must set 'name' to deliver")
	endif()
	if("${desc}" STREQUAL "")
		message(FATAL_ERROR "Must set 'desc' to deliver")
	endif()
	
	if(${CYGWIN}) 
		add_custom_target(deliv_${name}
			COMMAND ${CMAKE_COMMAND} 
				-DOUT_DIR="${CMAKE_INSTALL_PREFIX}/bin" 
				-DBIN_NAME="${CMAKE_INSTALL_PREFIX}/bin/${target}" 
				-P ${PROJECT_SOURCE_DIR}/cmake/deliver-cygwin.cmake
			DEPENDS ${target} 
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
			COMMENT "Deliver ${desc}"
		)
		add_dependencies(deliver deliv_${name})
	elseif(${WIN32})
		add_custom_target(deliv_${name} 
			COMMAND ${CMAKE_COMMAND} 
				-DSYSROOT="${CMAKE_FIND_ROOT_PATH}" 
				-DOUT_DIR="${CMAKE_INSTALL_PREFIX}/bin" 
				-DBIN_NAME="${CMAKE_INSTALL_PREFIX}/bin/${target}" 
				-P ${PROJECT_SOURCE_DIR}/cmake/deliver-mingw.cmake
			DEPENDS ${target} 
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
			COMMENT "Deliver ${desc}"
		)
		add_dependencies(deliver deliv_${name})
	endif()

endmacro()