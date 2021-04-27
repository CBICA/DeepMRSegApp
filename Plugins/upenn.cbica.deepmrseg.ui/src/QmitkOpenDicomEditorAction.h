/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QMITKOPENDICOMEDITORACTION_H_
#define QMITKOPENDICOMEDITORACTION_H_

#include <QAction>
#include <QIcon>

#include <upenn_cbica_deepmrseg_ui_Export.h>

#include <berryIWorkbenchWindow.h>
#include <berryIPreferences.h>

class MITK_QT_COMMON_EXT_EXPORT QmitkOpenDicomEditorAction : public QAction
{
  Q_OBJECT

public:
  QmitkOpenDicomEditorAction(berry::IWorkbenchWindow::Pointer window);
  QmitkOpenDicomEditorAction(const QIcon & icon, berry::IWorkbenchWindow::Pointer window);

protected slots:

  void Run();

private:
  void init ( berry::IWorkbenchWindow::Pointer window );
  berry::IWorkbenchWindow::Pointer m_Window;
  berry::IPreferences::WeakPtr m_GeneralPreferencesNode;
};


#endif /*QMITKOPENDICOMEDITORACTION_H_*/
