/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QmitkExtFileSaveProjectAction_H_
#define QmitkExtFileSaveProjectAction_H_

#include <QAction>

#include <upenn_cbica_deepmrseg_ui_Export.h>

#include <berrySmartPointer.h>

namespace berry {
struct IWorkbenchWindow;
}

class MITK_QT_COMMON_EXT_EXPORT QmitkExtFileSaveProjectAction : public QAction
{
  Q_OBJECT

public:

  QmitkExtFileSaveProjectAction(berry::SmartPointer<berry::IWorkbenchWindow> window);
  QmitkExtFileSaveProjectAction(berry::IWorkbenchWindow* window);

protected slots:

  void Run();

private:

  void Init(berry::IWorkbenchWindow* window);

  berry::IWorkbenchWindow* m_Window;
};


#endif /*QmitkExtFileSaveProjectAction_H_*/
