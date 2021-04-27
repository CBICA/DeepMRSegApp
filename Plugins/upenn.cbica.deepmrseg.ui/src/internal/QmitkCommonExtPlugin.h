/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QMITKCOMMONEXTPLUGIN_H_
#define QMITKCOMMONEXTPLUGIN_H_

#include <ctkPluginActivator.h>

class QmitkCommonExtPlugin : public QObject, public ctkPluginActivator
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "upenn_cbica_captk_ui")
  Q_INTERFACES(ctkPluginActivator)

public:

  void start(ctkPluginContext* context) override;
  void stop(ctkPluginContext* context) override;

  static ctkPluginContext* getContext();

private:

  void loadDataFromDisk(const QStringList& args, bool globalReinit);
  void startNewInstance(const QStringList& args, const QStringList &files);

private Q_SLOTS:

  void handleIPCMessage(const QByteArray &msg);

private:

  static ctkPluginContext* _context;

};

#endif /* QMITKCOMMONEXTPLUGIN_H_ */
