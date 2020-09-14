
#### SETTINGS
set(CATALOG_BIN catalog_edit)

set(LOCAL_UI rc/mainwindow.ui )
set(LOCAL_RC rc/editabletreemodel.qrc )


#### BUILD
QT5_WRAP_UI(CATALOG_UI_FILES ${LOCAL_UI} )
QT5_ADD_RESOURCES(CATALOG_RC_FILES ${LOCAL_RC} )
 
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${CATALOG_BIN}
    ## resources
	${CATALOG_UI_FILES}
    ${CATALOG_RC_FILES}
    
	## code
	src/main.cpp
	src/mainwindow.cpp
    src/treemodel.cpp
	src/treeitem.cpp
)

target_link_libraries(${CATALOG_BIN}
	${Qt5Core_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
)

#### INSTALL
install(TARGETS ${CATALOG_BIN} 
	RUNTIME DESTINATION bin
)

# all catalogs must have predefined name template
# find all catalogs
file(GLOB CATALOG_LIST ${CMAKE_CURRENT_SOURCE_DIR}/files/catalog_v*.json)
	 
install(
	FILES ${CATALOG_LIST}
	DESTINATION ${PROJECT_CONFIG_DIR}/catalog
	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

#### DELIVERY
deliver_target(${CATALOG_BIN} "catalog" "Catalog Editor")





	