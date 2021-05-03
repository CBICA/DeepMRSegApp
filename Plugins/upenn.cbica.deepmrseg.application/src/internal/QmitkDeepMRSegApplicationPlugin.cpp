/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegApplicationPlugin.h"
#include "perspectives/QmitkDeepMRSegDefaultPerspective.h"
#include "perspectives/QmitkDeepMRSegEditorPerspective.h"
#include "perspectives/QmitkDeepMRSegVisualizationPerspective.h"
#include "QmitkDeepMRSegIntroPart.h"
#include "QmitkDeepMRSegApplication.h"

#include "mitkWorkbenchUtil.h"
#include <mitkVersion.h>
#include <mitkLogMacros.h>

#include <service/cm/ctkConfigurationAdmin.h>
#include <service/cm/ctkConfiguration.h>

#include <QFileInfo>
#include <QDateTime>

QmitkDeepMRSegApplicationPlugin* QmitkDeepMRSegApplicationPlugin::inst = nullptr;

QmitkDeepMRSegApplicationPlugin::QmitkDeepMRSegApplicationPlugin()
{
  inst = this;
}

QmitkDeepMRSegApplicationPlugin::~QmitkDeepMRSegApplicationPlugin()
{
}

QmitkDeepMRSegApplicationPlugin* QmitkDeepMRSegApplicationPlugin::GetDefault()
{
  return inst;
}

void QmitkDeepMRSegApplicationPlugin::start(ctkPluginContext* context)
{
  berry::AbstractUICTKPlugin::start(context);

  this->context = context;

  BERRY_REGISTER_EXTENSION_CLASS(QmitkDeepMRSegDefaultPerspective, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkDeepMRSegEditorPerspective, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkDeepMRSegIntroPart, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkDeepMRSegApplication, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkDeepMRSegVisualizationPerspective, context);


  ctkServiceReference cmRef = context->getServiceReference<ctkConfigurationAdmin>();
  ctkConfigurationAdmin* configAdmin = nullptr;
  if (cmRef)
  {
    configAdmin = context->getService<ctkConfigurationAdmin>(cmRef);
  }

  // Use the CTK Configuration Admin service to configure the BlueBerry help system
  if (configAdmin)
  {
    ctkConfigurationPtr conf = configAdmin->getConfiguration("org.blueberry.services.help", QString());
    ctkDictionary helpProps;
    helpProps.insert("homePage", "qthelp://upenn.cbica.deepmrseg.application/bundle/index.html");
    conf->update(helpProps);
    context->ungetService(cmRef);
  }
  else
  {
    MITK_WARN << "Configuration Admin service unavailable, cannot set home page url.";
  }

  // Set CBICA logo
  mitk::WorkbenchUtil::SetDepartmentLogoPreference(":/upenn.cbica.deepmrseg.application/cbica-logo.png", context);
}

ctkPluginContext* QmitkDeepMRSegApplicationPlugin::GetPluginContext() const
{
  return context;
}
