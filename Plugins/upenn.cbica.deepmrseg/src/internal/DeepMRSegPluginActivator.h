/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
**/
#ifndef upenn_cbica_deepmrseg_Activator_h
#define upenn_cbica_deepmrseg_Activator_h

#include <ctkPluginActivator.h>

  class DeepMRSegPluginActivator : public QObject, public ctkPluginActivator
  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "upenn_cbica_deepmrseg")
    Q_INTERFACES(ctkPluginActivator)

  public:
    void start(ctkPluginContext *context);
    void stop(ctkPluginContext *context);

    static ctkPluginContext* getContext();

  private:
    static ctkPluginContext* m_Context;
  };


#endif // ! upenn_cbica_deepmrseg_Activator_h
