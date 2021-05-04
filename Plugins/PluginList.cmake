### Add upenn.cbica.* to the list of allowed naming schemes
list(APPEND MITK_PLUGIN_REGEX_LIST "^upenn_cbica_[a-zA-Z0-9_]+$")

set(MITK_PLUGINS
  upenn.cbica.deepmrseg:ON
  upenn.cbica.deepmrseg.ui:ON
  #upenn.cbica.captk.common:ON
  upenn.cbica.deepmrseg.application:ON
)
