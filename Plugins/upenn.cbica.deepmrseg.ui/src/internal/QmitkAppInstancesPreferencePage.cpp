/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkAppInstancesPreferencePage.h"

#include <berryIPreferencesService.h>
#include <berryQtPreferences.h>
#include <berryPlatform.h>

QmitkAppInstancesPreferencePage::QmitkAppInstancesPreferencePage()
{

}

void QmitkAppInstancesPreferencePage::Init(berry::IWorkbench::Pointer )
{

}

void QmitkAppInstancesPreferencePage::CreateQtControl(QWidget* parent)
{
  mainWidget = new QWidget(parent);
  controls.setupUi(mainWidget);

  berry::IPreferencesService* prefService = berry::Platform::GetPreferencesService();
  prefs = prefService->GetSystemPreferences()->Node("/General");

  Update();
}

QWidget* QmitkAppInstancesPreferencePage::GetQtControl() const
{
  return mainWidget;
}

bool QmitkAppInstancesPreferencePage::PerformOk()
{
  prefs->PutBool("newInstance.always", controls.newInstanceAlways->isChecked());
  prefs->PutBool("newInstance.scene", controls.newInstanceScene->isChecked());
  return true;
}

void QmitkAppInstancesPreferencePage::PerformCancel()
{

}

void QmitkAppInstancesPreferencePage::Update()
{
  bool always = prefs->GetBool("newInstance.always", false);
  bool scene = prefs->GetBool("newInstance.scene", true);

  controls.newInstanceAlways->setChecked(always);
  controls.newInstanceScene->setChecked(scene);
}
