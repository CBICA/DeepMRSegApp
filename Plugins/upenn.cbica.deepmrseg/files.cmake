set(SRC_CPP_FILES
  
)

set(INTERNAL_CPP_FILES
  DeepMRSegPluginActivator.cpp
  QDeepMRSegView.cpp
)

set(UI_FILES
  src/internal/QDeepMRSegControls.ui
)

set(MOC_H_FILES
  src/internal/DeepMRSegPluginActivator.h
  src/internal/QDeepMRSegView.h
)

set(CACHED_RESOURCE_FILES
  resources/dmrs-logo.svg
  plugin.xml
)

set(QRC_FILES

)

### Don't change below

set(CPP_FILES)

foreach(file ${SRC_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
