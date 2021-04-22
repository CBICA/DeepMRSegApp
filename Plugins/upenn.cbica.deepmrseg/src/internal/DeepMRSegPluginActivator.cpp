/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
**/
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
