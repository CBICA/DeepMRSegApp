/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegEditorPerspective.h"

void QmitkDeepMRSegEditorPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout)
{
  layout->GetEditorArea();

  layout->AddPerspectiveShortcut("org.mitk.deepmrsegapp.defaultperspective");
  layout->AddPerspectiveShortcut("org.mitk.deepmrseg.perspectives.visualization");
}
