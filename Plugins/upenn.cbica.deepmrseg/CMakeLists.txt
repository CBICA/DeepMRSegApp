project(upenn_cbica_deepmrseg)

include_directories(${CTK_INCLUDE_DIRS})

mitk_create_plugin(
  EXPORT_DIRECTIVE UPENN_CBICA_DEEPMRSEG
)