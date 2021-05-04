/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QmitkDeepMRSegVisualizationPerspective_H_
#define QmitkDeepMRSegVisualizationPerspective_H_

#include <berryIPerspectiveFactory.h>

class QmitkDeepMRSegVisualizationPerspective : public QObject, public berry::IPerspectiveFactory
{
  Q_OBJECT
  Q_INTERFACES(berry::IPerspectiveFactory)

public:

  QmitkDeepMRSegVisualizationPerspective() {}
  ~QmitkDeepMRSegVisualizationPerspective() override {}

  void CreateInitialLayout(berry::IPageLayout::Pointer layout) override;
};

#endif /* QmitkDeepMRSegVisualizationPerspective_H_ */
