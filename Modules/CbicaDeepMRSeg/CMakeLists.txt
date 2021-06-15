
mitk_create_module(
  INCLUDE_DIRS PUBLIC include
  PACKAGE_DEPENDS ITK VTK Qt5|Core+Widgets # External package dependencies added here
  DEPENDS PUBLIC MitkCore MitkPython# Module dependencies - be sure to add as needed
)

# You can add subdirectories as needed 
#add_subdirectory(cmdapps) # -> for cmd app

# You can also add additional commands here as needed.

# Deploy Python files to bin
# Copy resources to bin in build tree
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/bin/MitkCbicaDeepMRSeg)

# Deploy resources to install tree
set(_install_DESTINATION "MitkCbicaDeepMRSeg")
MITK_INSTALL( DIRECTORY resources)