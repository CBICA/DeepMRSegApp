/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QMITKABOUTHANDLER_H
#define QMITKABOUTHANDLER_H

#include <berryAbstractHandler.h>

class QmitkAboutHandler : public berry::AbstractHandler
{
  Q_OBJECT

public:

  Object::Pointer Execute(const berry::SmartPointer<const berry::ExecutionEvent>& event) override;
};

#endif // QMITKABOUTHANDLER_H
