/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QMITKDeepMRSegAPPWORKBENCHADVISOR_H_
#define QMITKDeepMRSegAPPWORKBENCHADVISOR_H_

#include <berryQtWorkbenchAdvisor.h>

class QmitkDeepMRSegAppWorkbenchAdvisor: public berry::QtWorkbenchAdvisor
{
public:

  static const QString DEFAULT_PERSPECTIVE_ID; // = "org.mitk.DeepMRSegapp.defaultperspective"

  void Initialize(berry::IWorkbenchConfigurer::Pointer configurer) override;

  berry::WorkbenchWindowAdvisor* CreateWorkbenchWindowAdvisor(
      berry::IWorkbenchWindowConfigurer::Pointer configurer) override;

  QString GetInitialWindowPerspectiveId() override;

private:
  // For DeepMRSeg's about menu
  berry::IWorkbenchWindowConfigurer::Pointer m_WorkbenchWindowConfigurer;

};

#endif /*QMITKDeepMRSegAPPWORKBENCHADVISOR_H_*/
