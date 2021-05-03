/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#ifndef QmitkExternalProgramsPreferencePage_h
#define QmitkExternalProgramsPreferencePage_h

#include <berryIPreferences.h>
#include <berryIQtPreferencePage.h>
#include <QProcess>
#include <QScopedPointer>

namespace Ui
{
  class QmitkExternalProgramsPreferencePage;
}

class QmitkExternalProgramsPreferencePage : public QObject, public berry::IQtPreferencePage
{
  Q_OBJECT
  Q_INTERFACES(berry::IPreferencePage)

public:
  QmitkExternalProgramsPreferencePage();
  ~QmitkExternalProgramsPreferencePage() override;

  void CreateQtControl(QWidget* parent) override;
  QWidget* GetQtControl() const override;
  void Init(berry::IWorkbench::Pointer) override;
  void PerformCancel() override;
  bool PerformOk() override;
  void Update() override;

private slots:
  void OnFFmpegButtonClicked();
  void OnFFmpegProcessError(QProcess::ProcessError error);
  void OnFFmpegProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

  void OnGnuplotButtonClicked();
  void OnGnuplotProcessError(QProcess::ProcessError error);
  void OnGnuplotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
  berry::IPreferences::Pointer m_Preferences;
  QScopedPointer<Ui::QmitkExternalProgramsPreferencePage> m_Ui;
  QWidget* m_Control;

  QProcess* m_FFmpegProcess;
  QString m_FFmpegPath;

  QProcess* m_GnuplotProcess;
  QString m_GnuplotPath;
};

#endif
