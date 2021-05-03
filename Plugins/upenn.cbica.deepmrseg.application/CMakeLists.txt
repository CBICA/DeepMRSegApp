project(upenn_cbica_deepmrseg_application)

mitk_create_plugin(
  EXPORT_DIRECTIVE MITK_QT_DEEPMRSEGAPP
  EXPORTED_INCLUDE_SUFFIXES src
  PACKAGE_DEPENDS Qt5|WebEngineWidgets
)
