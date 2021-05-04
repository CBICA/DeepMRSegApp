# Install DeepMRSegApp ico

if( ${MITK_BUILD_APP_DeepMRSegApp} )
  get_filename_component(ABSOLUTE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/../Applications/DeepMRSegApp/icons/icon.ico"
	ABSOLUTE
  )
endif( ${MITK_BUILD_APP_DeepMRSegApp} )

message("Path is ${ABSOLUTE_PATH}")
MITK_INSTALL(FILES ${ABSOLUTE_PATH})