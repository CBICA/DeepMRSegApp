/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
**/
#include "QDeepMRSegView.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QMetaEnum>

#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateProperty.h>
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateOr.h>

#include "DeepMRSegMediator.h"

const std::string QDeepMRSegView::VIEW_ID = "upenn.cbica.deepmrseg.view";

QDeepMRSegView::QDeepMRSegView()
{
	//default task type
	this->m_taskType = TaskType::SELECTTASK;

  // ---- General setup operations ----
	mitk::TNodePredicateDataType<mitk::Image>::Pointer isImage = mitk::TNodePredicateDataType<mitk::Image>::New();
	mitk::NodePredicateProperty::Pointer isBinary =	mitk::NodePredicateProperty::New("binary", mitk::BoolProperty::New(true));
	mitk::NodePredicateAnd::Pointer isMask = mitk::NodePredicateAnd::New(isBinary, isImage);

	auto isSegment = mitk::NodePredicateDataType::New("Segment");

	mitk::NodePredicateOr::Pointer validImages = mitk::NodePredicateOr::New();
	validImages->AddPredicate(mitk::NodePredicateAnd::New(isImage, mitk::NodePredicateNot::New(isSegment)));

	m_T1Predicate = mitk::NodePredicateAnd::New();
	m_T1Predicate->AddPredicate(validImages);
	m_T1Predicate->AddPredicate(mitk::NodePredicateNot::New(isMask));
	m_T1Predicate->AddPredicate(mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object")));

	m_FlairPredicate = mitk::NodePredicateAnd::New();
	m_FlairPredicate->AddPredicate(validImages);
	m_FlairPredicate->AddPredicate(mitk::NodePredicateNot::New(isMask));
	m_FlairPredicate->AddPredicate(mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object")));

}

QDeepMRSegView::~QDeepMRSegView()
{

}

void QDeepMRSegView::CreateQtPartControl(QWidget *parent)
{
  // ---- Setup the basic GUI of this view ----
  m_Parent = parent;
  m_Controls.setupUi(parent);

  //populate tasks
  m_Controls.comboBox_tasks->insertItem(TaskType::BRAINEXTRACTION, "Brain Extraction");
  m_Controls.comboBox_tasks->insertItem(TaskType::LESIONSEGMENTATION, "Lesion Segmentation");
  m_Controls.comboBox_tasks->insertItem(TaskType::MUSESEGMENTATION, "Muse Segmentation");
  m_Controls.comboBox_tasks->insertItem(TaskType::SELECTTASK, "Select a task");

  //by default show 'select task'
  m_Controls.comboBox_tasks->setCurrentIndex(TaskType::SELECTTASK);

  //hide temporarily since python side doesn't yet throw progress
  m_Controls.progressBar->hide(); 

  //data selection from data storage
  m_Controls.comboBox_t1->SetAutoSelectNewItems(true);
  m_Controls.comboBox_t1->SetPredicate(m_T1Predicate);
  m_Controls.comboBox_t1->SetDataStorage(this->GetDataStorage());

  m_Controls.comboBox_flair->SetAutoSelectNewItems(true);
  m_Controls.comboBox_flair->SetPredicate(m_FlairPredicate);
  m_Controls.comboBox_flair->SetDataStorage(this->GetDataStorage());

  // signals/slots connections
  connect(m_Controls.pushButtonRun, SIGNAL(clicked()),this, SLOT(OnRunButtonClicked()));
  connect(m_Controls.comboBox_tasks, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTaskChanged(int)));
  connect(m_Controls.comboBox_t1, SIGNAL(OnSelectionChanged(const mitk::DataNode *)), this, SLOT(OnT1SelectionChanged(const mitk::DataNode *)));
  connect(m_Controls.comboBox_flair, SIGNAL(OnSelectionChanged(const mitk::DataNode *)), this, SLOT(OnFlairSelectionChanged(const mitk::DataNode *)));
  connect(m_Controls.pushButton_selectModel, SIGNAL(clicked()), this, SLOT(OnSelectModelButtonClicked()));
  
}

void QDeepMRSegView::Activated()
{
  // Not yet implemented
}

void QDeepMRSegView::Deactivated()
{
  // Not yet implemented
}

void QDeepMRSegView::Visible()
{
  // Not yet implemented
}

void QDeepMRSegView::Hidden()
{
  // Not yet implemented
}

/************************************************************************/
/* protected slots                                                      */
/************************************************************************/

void QDeepMRSegView::OnRunButtonClicked()
{
	//check for T1 ( used for all supported task types )
	mitk::DataNode::Pointer t1Node = m_Controls.comboBox_t1->GetSelectedNode();

	// is something selected
	if (t1Node.IsNull())
	{
		QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a T1 image before proceeding.");
		return;
	}

	// Something is selected, but does it contain data?
	mitk::BaseData::Pointer t1data = t1Node->GetData();
	if (t1data.IsNull())
	{
		QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a T1 image before proceeding.");
		return;
	}

	// Something is selected and it contains data, but is it an image?
	mitk::Image::Pointer t1image = dynamic_cast<mitk::Image*>(t1data.GetPointer());
	if (t1image.IsNull())
	{
		QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a T1 image before proceeding.");
		return;
	}

	mitk::DataNode::Pointer flNode;
	mitk::BaseData::Pointer fldata;
	mitk::Image::Pointer flimage;

	//check for Flair ( used only in case of lesion segmentation task )
	if (this->m_taskType == TaskType::LESIONSEGMENTATION)
	{
		flNode = m_Controls.comboBox_flair->GetSelectedNode();

		// is something selected
		if (flNode.IsNull())
		{
			QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a Flair image before proceeding.");
			return;
		}

		// Something is selected, but does it contain data?
		fldata = flNode->GetData();
		if (fldata.IsNull())
		{
			QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a Flair image before proceeding.");
			return;
		}

		// Something is selected and it contains data, but is it an image?
		flimage = dynamic_cast<mitk::Image*>(fldata.GetPointer());
		if (flimage.IsNull())
		{
			QMessageBox::information(nullptr, "New DeepMRSeg Session", "Please load a Flair image before proceeding.");
			return;
		}
	}

	//call deepmrsegmediator
	auto mediator = DeepMRSegMediator();
	auto mediatorPtr = &mediator;

	mediatorPtr->SetT1Image(t1image);

	//in case of LesionSegmentation we also set the flair image
	if (this->m_taskType == TaskType::LESIONSEGMENTATION)
		mediatorPtr->SetFlairImage(flimage);

	mediatorPtr->Update();
	mitk::Image::Pointer processedImage = mediatorPtr->GetOutput();

	// Double check to make sure we aren't adding uninitalized or null images. 
	if (processedImage.IsNull() || !processedImage->IsInitialized())
		// Could do more diagnostics or raise an error message here...
		return;

	MITK_INFO << "  done";

	auto processedImageDataNode = mitk::DataNode::New(); // Create a new node
	MITK_INFO << "Adding to a data node";
	processedImageDataNode->SetData(processedImage); // assign the inverted image to the node

	auto metaEnum = QMetaEnum::fromType<TaskType>();
	QString selectTask = metaEnum.valueToKey(this->m_taskType);

	MITK_INFO << "Adding a name";
	// Add a suffix so users can easily see what it is
	QString name = QString("%1_segmented").arg(selectTask);
	processedImageDataNode->SetName(name.toStdString());

	// Finally, add the new node to the data storage.
	auto ds = this->GetDataStorage();
	ds->Add(processedImageDataNode);

}

/************************************************************************/
/* protected                                                            */
/************************************************************************/

void QDeepMRSegView::OnTaskChanged(int index)
{
	this->m_taskType = TaskType(index);

	if (index == TaskType::BRAINEXTRACTION)
	{
		m_Controls.comboBox_flair->hide();
		m_Controls.label_flair->hide();
	}
	else if (index == TaskType::LESIONSEGMENTATION)
	{
		m_Controls.comboBox_flair->show();
		m_Controls.label_flair->show();
	}
	else if (index == TaskType::MUSESEGMENTATION)
	{
		m_Controls.comboBox_flair->hide();
		m_Controls.label_flair->hide();
	}
	else if (index == TaskType::SELECTTASK)
	{
		m_Controls.comboBox_flair->show();
		m_Controls.label_flair->show();
	}
}

void QDeepMRSegView::OnT1SelectionChanged(const mitk::DataNode *)
{
	// Not yet implemented
}

void QDeepMRSegView::OnFlairSelectionChanged(const mitk::DataNode *)
{
	// Not yet implemented
}

void QDeepMRSegView::OnSelectModelButtonClicked()
{
	auto dirName = QFileDialog::getExistingDirectory(m_Parent,
		tr("Select model directory"),
		qApp->applicationDirPath(), 
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (dirName.isEmpty() || dirName.isNull()) 
	{ 
		return; 
	}

	// if not dir, we return
	QFileInfo file(dirName);
	if (!file.isDir()) 
	{ 
		return; 
	}

	// Set the path to the QLineEdit
	m_Controls.lineEdit_model->setText(dirName);
}

void QDeepMRSegView::OnSelectionChanged(berry::IWorkbenchPart::Pointer, const QList<mitk::DataNode::Pointer>& /*nodes*/)
{
	// Not yet implemented
}

void QDeepMRSegView::OnPreferencesChanged(const berry::IBerryPreferences* /*prefs*/)
{
	// Not yet implemented
}

void QDeepMRSegView::NodeAdded(const mitk::DataNode* /*node*/)
{
	// Not yet implemented
}

void QDeepMRSegView::NodeRemoved(const mitk::DataNode* /*node*/)
{
	// Not yet implemented
}

void QDeepMRSegView::SetFocus()
{
	// Not yet implemented
}

void QDeepMRSegView::UpdateControls()
{
  // Here you can hide views that are not useful and more
}

void QDeepMRSegView::InitializeListeners()
{
	// Not yet implemented
}