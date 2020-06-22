
if("${OUT_DIR}" STREQUAL "")
	message(FATAL_ERROR "Must set output directory with OUT_DIR variable")
else()
	execute_process (
		COMMAND bash -c "ldd lock_app"
		COMMAND bash -c "grep -s 'cyg.*\\.dll\ ='"
		COMMAND bash -c "cut -d\" \" -f3"
		COMMAND bash -c "tr '\n' ';'"
		OUTPUT_VARIABLE outLDD
	)

	message(STATUS "Files to copy for delivery: ${outLDD}")
	message(STATUS "Copy into: ${OUT_DIR}")

	foreach(file ${outLDD})
	  configure_file(${file} ${OUT_DIR} COPYONLY)
	endforeach()

endif()