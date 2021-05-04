/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegApplication.h"

#include <berryPlatformUI.h>

#include "QmitkDeepMRSegAppWorkbenchAdvisor.h"

QmitkDeepMRSegApplication::QmitkDeepMRSegApplication()
{

}

QVariant QmitkDeepMRSegApplication::Start(berry::IApplicationContext* /*context*/)
{
  QScopedPointer<berry::Display> display(berry::PlatformUI::CreateDisplay());

  QScopedPointer<QmitkDeepMRSegAppWorkbenchAdvisor> wbAdvisor(new QmitkDeepMRSegAppWorkbenchAdvisor());
  int code = berry::PlatformUI::CreateAndRunWorkbench(display.data(), wbAdvisor.data());

  // exit the application with an appropriate return code
  return code == berry::PlatformUI::RETURN_RESTART
              ? EXIT_RESTART : EXIT_OK;
}

void QmitkDeepMRSegApplication::Stop()
{

}
