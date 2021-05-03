/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QMITKMODULEVIEW_H
#define QMITKMODULEVIEW_H

#include <berryQtViewPart.h>

class QTableView;

class QmitkModuleView : public berry::QtViewPart
{
  Q_OBJECT

public:
  QmitkModuleView();

protected:

  void SetFocus() override;
  void CreateQtPartControl(QWidget *parent) override;

  void Init(berry::IViewSite::Pointer site, berry::IMemento::Pointer memento) override;
  void SaveState(berry::IMemento::Pointer memento) override;

private:

  QTableView* tableView;
  berry::IMemento::Pointer viewState;
};

#endif // QMITKMODULEVIEW_H
