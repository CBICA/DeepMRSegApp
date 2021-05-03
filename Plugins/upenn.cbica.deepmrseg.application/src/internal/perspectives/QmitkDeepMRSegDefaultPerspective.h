/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/


#ifndef QMITKDeepMRSegDEFAULTPERSPECTIVE_H_
#define QMITKDeepMRSegDEFAULTPERSPECTIVE_H_

#include <berryIPerspectiveFactory.h>

class QmitkDeepMRSegDefaultPerspective : public QObject, public berry::IPerspectiveFactory
{
  Q_OBJECT
  Q_INTERFACES(berry::IPerspectiveFactory)

public:

  QmitkDeepMRSegDefaultPerspective();

  void CreateInitialLayout(berry::IPageLayout::Pointer layout) override;

};

#endif /* QMITKDeepMRSegDEFAULTPERSPECTIVE_H_ */
