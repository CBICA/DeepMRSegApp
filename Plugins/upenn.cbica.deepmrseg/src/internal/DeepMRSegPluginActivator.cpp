#include "DeepMRSegPluginActivator.h"

#include "QDeepMRSegView.h"

#include <usModuleInitialization.h>

ctkPluginContext* DeepMRSegPluginActivator::m_Context = nullptr;

US_INITIALIZE_MODULE 

void DeepMRSegPluginActivator::start(ctkPluginContext *context)
{
  BERRY_REGISTER_EXTENSION_CLASS(QDeepMRSegView, context)

  m_Context = context;
}

void DeepMRSegPluginActivator::stop(ctkPluginContext*)
{
}

ctkPluginContext* DeepMRSegPluginActivator::getContext()
{
  return m_Context;
}
