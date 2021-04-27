/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QMITKDeepMRSegAPPLICATIONPLUGIN_H_
#define QMITKDeepMRSegAPPLICATIONPLUGIN_H_

#include <berryAbstractUICTKPlugin.h>

#include <QString>

class QmitkDeepMRSegApplicationPlugin : public berry::AbstractUICTKPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "upenn_cbica_deepmrseg_application")
  Q_INTERFACES(ctkPluginActivator)

public:

  QmitkDeepMRSegApplicationPlugin();
  ~QmitkDeepMRSegApplicationPlugin() override;

  static QmitkDeepMRSegApplicationPlugin* GetDefault();

  ctkPluginContext* GetPluginContext() const;

  void start(ctkPluginContext*) override;

  QString GetQtHelpCollectionFile() const;

private:

  static QmitkDeepMRSegApplicationPlugin* inst;

  ctkPluginContext* context;
};

#endif /* QMITKDeepMRSegAPPLICATIONPLUGIN_H_ */
