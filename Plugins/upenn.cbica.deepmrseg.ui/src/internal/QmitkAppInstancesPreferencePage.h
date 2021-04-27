/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QMITKAPPINSTANCESPREFERENCEPAGE_H_
#define QMITKAPPINSTANCESPREFERENCEPAGE_H_

#include <berryIQtPreferencePage.h>
#include <berryIPreferences.h>

#include <ui_QmitkAppInstancesPreferencePage.h>


class QmitkAppInstancesPreferencePage : public QObject, public berry::IQtPreferencePage
{

  Q_OBJECT
  Q_INTERFACES(berry::IPreferencePage)

public:

  QmitkAppInstancesPreferencePage();
  QmitkAppInstancesPreferencePage(const QmitkAppInstancesPreferencePage& other);

  void Init(berry::IWorkbench::Pointer workbench) override;

  void CreateQtControl(QWidget* parent) override;
  QWidget* GetQtControl() const override;

  bool PerformOk() override;
  void PerformCancel() override;
  void Update() override;

private:

  Ui::QmitkAppInstancesPreferencePage controls;

  berry::IPreferences::Pointer prefs;

  QWidget* mainWidget;
};

#endif /* QMITKAPPINSTANCESPREFERENCEPAGE_H_ */
