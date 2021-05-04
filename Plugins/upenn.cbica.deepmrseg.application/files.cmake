set(SRC_CPP_FILES
)

set(INTERNAL_CPP_FILES
  QmitkDeepMRSegApplication.cpp
  QmitkDeepMRSegApplicationPlugin.cpp
  QmitkDeepMRSegAppWorkbenchAdvisor.cpp
  QmitkDeepMRSegIntroPart.cpp
  perspectives/QmitkDeepMRSegEditorPerspective.cpp
  perspectives/QmitkDeepMRSegDefaultPerspective.cpp
  perspectives/QmitkDeepMRSegVisualizationPerspective.cpp
)

set(MOC_H_FILES
  src/internal/QmitkDeepMRSegApplication.h
  src/internal/QmitkDeepMRSegApplicationPlugin.h
  src/internal/QmitkDeepMRSegIntroPart.h
  src/internal/perspectives/QmitkDeepMRSegEditorPerspective.h
  src/internal/perspectives/QmitkDeepMRSegDefaultPerspective.h
  src/internal/perspectives/QmitkDeepMRSegVisualizationPerspective.h
)

set(UI_FILES
  src/internal/perspectives/QmitkDeepMRSegWelcomeScreenViewControls.ui
)

set(CACHED_RESOURCE_FILES
# list of resource files which can be used by the plug-in
# system without loading the plug-ins shared library,
# for example the icon used in the menu and tabs for the
# plug-in views in the workbench
  plugin.xml
  resources/icon_research.xpm
  resources/perspectives/eye.png
  resources/perspectives/viewer_icon.png
)

set(QRC_FILES
resources/QmitkDeepMRSegApplication.qrc
resources/welcome/QmitkDeepMRSegWelcomeScreenView.qrc
)

set(CPP_FILES )

foreach(file ${SRC_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})

