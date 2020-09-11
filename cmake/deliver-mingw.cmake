
if("${OUT_DIR}" STREQUAL "")
	message(FATAL_ERROR "Must set output directory with OUT_DIR variable")
elseif("${BIN_NAME}" STREQUAL "" )
	message(FATAL_ERROR "Must set executable to check with BIN_NAME variable")
elseif("${SYSROOT}" STREQUAL "" )
	message(FATAL_ERROR "Must set sys root path with SYSROOT variable")
else()
	message(STATUS "Copy into: ${OUT_DIR}")
	message(STATUS "Target: ${BIN_NAME}")	
	message(STATUS "Sys root path: ${SYSROOT}")	
	
	list(APPEND SYSDLLS KERNEL.dll)
	set(MORE 1)
	while(${MORE} GREATER 0)
		set(MORE 0)

		file(GLOB listFile ${OUT_DIR}/*.dll)
		# message(STATUS "found root files ${listFile}")
		
		foreach(file ${listFile} ${BIN_NAME}.exe)	
			execute_process (
				COMMAND bash -c "strings ${file}"
				COMMAND bash -c "grep -i '\\.dll\$'"
				COMMAND bash -c "tr '\n' ';'"
				OUTPUT_VARIABLE listDep
			)

			foreach(dep ${listDep})
				# message(STATUS "dependency on ${dep}, SYSDLLS: (${SYSDLLS})")
				if(NOT EXISTS "${OUT_DIR}/${dep}")
					list(FIND SYSDLLS ${dep} DEPFOUND)
					
					if(${DEPFOUND} LESS 0)
						# message(STATUS "\tFind and copy")
						file(GLOB DEPPATH ${SYSROOT}/*/${dep})
							
						if("${DEPPATH}" STREQUAL "")
							# message(STATUS "\tSystem DLL")
							list(APPEND SYSDLLS ${dep})
						else()
							configure_file(${DEPPATH} ${OUT_DIR} COPYONLY)
							
							MATH(EXPR MORE "${MORE}+1")
						endif()
					else () 
						# message(STATUS "Already found")
					endif()
				else () 
					# message(STATUS "Dependency satisfied")
				endif()	
			endforeach()
		endforeach()
	endwhile()
	message(STATUS "SYSDLLS: (${SYSDLLS})")
endif()