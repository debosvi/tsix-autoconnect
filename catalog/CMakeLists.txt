
# all catalogs must have predefined name template
# find all catalogs
file(GLOB CATALOG_LIST ${CMAKE_CURRENT_SOURCE_DIR}/files/catalog_v*.json)
	 
install(
	FILES ${CATALOG_LIST}
	DESTINATION ${PROJECT_CONFIG_DIR}/catalog
	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
	