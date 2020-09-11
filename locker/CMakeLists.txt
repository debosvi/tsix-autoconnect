
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


#### DELIVERY
deliver_target(${LOCKER_BIN} "locker" "Backend Locker")
