/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkAboutHandler.h"

#include <QmitkAboutDialog.h>

#include <QMessageBox>

berry::Object::Pointer QmitkAboutHandler::Execute(const berry::SmartPointer<const berry::ExecutionEvent>& /*event*/)
{
  // QMessageBox mb("CaPTk",
  //                QString("Cancer Imaging Phenomics Toolkit\n\n")
  //                   + QString("by CBICA (Center for Biomedical Image Computing & Analytics)\n\n")
  //                   + QString("University of Pennsylvania"),
  //               QMessageBox::NoIcon,
  //               QMessageBox::Yes | QMessageBox::Default,
  //               QMessageBox::NoButton,
  //               QMessageBox::NoButton);
  // QPixmap upennIcon(":/upenn.cbica.captk.ui/upenn.png");
  // mb.setIconPixmap(upennIcon);

  // Is this function useless?

  return berry::Object::Pointer(); // for some reason

  // auto   aboutDialog = new QmitkAboutDialog(QApplication::activeWindow(), nullptr);
  // aboutDialog->open();
  // return berry::Object::Pointer();
}
