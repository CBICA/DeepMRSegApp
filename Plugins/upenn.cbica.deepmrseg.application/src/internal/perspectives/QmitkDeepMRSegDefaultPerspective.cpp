/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegDefaultPerspective.h"
#include "berryIViewLayout.h"

QmitkDeepMRSegDefaultPerspective::QmitkDeepMRSegDefaultPerspective()
{
}

void QmitkDeepMRSegDefaultPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout)
{
  QString editorArea = layout->GetEditorArea();

  // Show interactive segmentation by default. In the future change this to a 
  // non-closable "Start" menu of DeepMRSeg, that also offers shortcuts
  // for different perspectives for Brain, Breast, Lung Cancer etc
  layout->AddView(
    "upenn.cbica.DeepMRSeg.views.interactivesegmentation", berry::IPageLayout::RIGHT, 
    0.6f, editorArea
  );

  // Data manager
  layout->AddView("org.mitk.views.datamanager", berry::IPageLayout::TOP, 0.3f, editorArea);
  berry::IViewLayout::Pointer lo = layout->GetViewLayout("org.mitk.views.datamanager");
  lo->SetCloseable(false);

  // Image navigator (slice sliders etc)
  layout->AddView("org.mitk.views.imagenavigator",
      berry::IPageLayout::RIGHT, 0.5f, "org.mitk.views.datamanager");

  // Bottom bar
  berry::IPlaceholderFolderLayout::Pointer bottomFolder = 
      layout->CreatePlaceholderFolder("bottom", berry::IPageLayout::BOTTOM, 
                                      0.7f, editorArea);
  bottomFolder->AddPlaceholder("org.blueberry.views.logview");
  bottomFolder->AddPlaceholder("org.mitk.views.modules");

  layout->AddPerspectiveShortcut("org.mitk.deepmrseg.perspectives.editor");
  layout->AddPerspectiveShortcut("org.mitk.deepmrseg.perspectives.visualization");
}
