project(DeepMRSegApp)

set(_app_options)
if(MITK_SHOW_CONSOLE_WINDOW)
  list(APPEND _app_options SHOW_CONSOLE)
endif()

# Create a cache entry for the provisioning file which is used to export
# the file name in the MITKConfig.cmake file. This will keep external projects
# which rely on this file happy.
set(MITK_DeepMRSegApp_PROVISIONING_FILE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DeepMRSegApp.provisioning" CACHE INTERNAL "DeepMRSegApp provisioning file" FORCE)

set(_plugins
 org.mitk.gui.qt.stdmultiwidgeteditor
 org.mitk.gui.qt.datamanager
 org_mitk_planarfigure
 org.blueberry.ui.qt.help

 upenn.cbica.deepmrseg.ui
 upenn.cbica.deepmrseg.application
 #upenn.cbica.captk.common
 upenn.cbica.deepmrseg

 org.mitk.gui.qt.imagenavigator
 org.mitk.gui.qt.measurementtoolbox
 org.mitk.gui.qt.segmentation
 org.mitk.gui.qt.multilabelsegmentation
)

# For DeepMRSegApp icon to be included (this cmake file is in CMake/)
include(DeepMRSegAppInstallRules)

# For the git tag to get picked up
include(mitkFunctionGetVersionDescription)
mitkFunctionGetVersionDescription(${PROJECT_SOURCE_DIR} DeepMRSegApp)

mitkFunctionCreateBlueBerryApplication(
  NAME DeepMRSegApp
  DESCRIPTION "DeepMRSegApp"
  PLUGINS ${_plugins}
  # EXCLUDE_PLUGINS(_exclude_plugins)
  ${_app_options}
)

mitk_use_modules(TARGET DeepMRSegApp
  MODULES MitkAppUtil
)

# subproject support
#add_dependencies(MITK-CoreUI DeepMRSegApp)

# Add meta dependencies (e.g. on auto-load modules from depending modules)
if(TARGET ${CMAKE_PROJECT_NAME}-autoload)
  add_dependencies(DeepMRSegApp ${CMAKE_PROJECT_NAME}-autoload)
endif()

#Setting application icon for macOS systems
#set_target_properties(DeepMRSegApp PROPERTIES MACOSX_BUNDLE_ICON_FILE "icon.icns")

#if(APPLE)
#  install(FILES "icons/icon.icns" DESTINATION "DeepMRSegApp.app/Contents/Resources")
#endif(APPLE)

# Add a build time dependency to legacy BlueBerry bundles.
if(MITK_MODULES_ENABLED_PLUGINS)
  add_dependencies(DeepMRSegApp ${MITK_MODULES_ENABLED_PLUGINS})
endif()

