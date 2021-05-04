/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegAppWorkbenchAdvisor.h"
#include "internal/QmitkDeepMRSegApplicationPlugin.h"

#include <QmitkExtWorkbenchWindowAdvisor.h>
#include <src/internal/QmitkDeepMRSegApplicationPlugin.h>

#include <QMessageBox>
#include <QMainWindow>
#include <QMenuBar>

const QString QmitkDeepMRSegAppWorkbenchAdvisor::DEFAULT_PERSPECTIVE_ID =
    "org.mitk.deepmrsegapp.defaultperspective";

void
QmitkDeepMRSegAppWorkbenchAdvisor::Initialize(berry::IWorkbenchConfigurer::Pointer configurer)
{
  berry::QtWorkbenchAdvisor::Initialize(configurer);

  configurer->SetSaveAndRestore(true);

  // // Change the about page to DeepMRSeg's
  // QMainWindow* mainWindow =
  //   qobject_cast<QMainWindow*>(m_WorkbenchWindowConfigurer->GetWindow()->GetShell()->GetControl());
  // QList<QMenu*> menus = mainWindow->menuBar()->findChildren<QMenu*>();
  // for (QMenu* menu : menus)
  // {
  //   for (QAction* action : menu->actions())
  //   {
  //     if (action->text() != nullptr && action->text() == "About")
  //     {
  //       // menu->removeAction(action);
  //       // QAction* newAboutAction = new QAction("About", menu);
  //       // newAboutAction
  //       menu->addAction("About", 
  //         [this]()
  //         {
  //           QMessageBox msgError;
  //           msgError.setText(
  //               "UPenn"
  //           );
  //           // msgError.setIcon(QMessageBox::Critical);
  //           msgError.setWindowTitle("CaPTk");
  //           msgError.exec();
  //         }
  //       );
  //       break;
  //     }
  //   }
  // }
}

berry::WorkbenchWindowAdvisor*
QmitkDeepMRSegAppWorkbenchAdvisor::CreateWorkbenchWindowAdvisor(
        berry::IWorkbenchWindowConfigurer::Pointer configurer)
{
  QmitkExtWorkbenchWindowAdvisor* advisor = new
    QmitkExtWorkbenchWindowAdvisor(this, configurer);

  // Exclude the help perspective from org.blueberry.ui.qt.help from
  // the normal perspective list.
  // The perspective gets a dedicated menu entry in the help menu
  QList<QString> excludePerspectives;
  excludePerspectives.push_back("org.blueberry.perspectives.help");
  advisor->SetPerspectiveExcludeList(excludePerspectives);

  // Exclude some views from the normal view list
  QList<QString> excludeViews;
  excludeViews.push_back("org.mitk.views.modules");
  excludeViews.push_back( "org.blueberry.ui.internal.introview" );
  advisor->SetViewExcludeList(excludeViews);

  //title bar icon
  advisor->SetWindowIcon(":/upenn.cbica.deepmrseg.application/icon.png");

  m_WorkbenchWindowConfigurer = configurer; // Used for changing "about" to CaPTk's

  return advisor;
}

QString QmitkDeepMRSegAppWorkbenchAdvisor::GetInitialWindowPerspectiveId()
{
  return DEFAULT_PERSPECTIVE_ID;
}
