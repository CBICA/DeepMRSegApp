/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QMITKDeepMRSegAPPLICATION_H_
#define QMITKDeepMRSegAPPLICATION_H_

#include <berryIApplication.h>


class QmitkDeepMRSegApplication : public QObject, public berry::IApplication
{
  Q_OBJECT
  Q_INTERFACES(berry::IApplication)

public:

  QmitkDeepMRSegApplication();

  QVariant Start(berry::IApplicationContext* context) override;
  void Stop() override;
};

#endif /*QMITKDeepMRSegAPPLICATION_H_*/
