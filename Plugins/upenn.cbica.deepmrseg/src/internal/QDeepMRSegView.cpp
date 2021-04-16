#include "QDeepMRSegView.h"

#include <QMessageBox>

#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateProperty.h>
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateOr.h>

#include "DeepMRSegMediator.h"

const std::string QDeepMRSegView::VIEW_ID =
    "upenn.cbica.deepmrseg.view";

QDeepMRSegView::QDeepMRSegView()
{
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

  //hide temporarily since python side doesn't yet thrown progress
  m_Controls.progressBar->hide(); 

  m_Controls.comboBox_t1->SetAutoSelectNewItems(true);
  m_Controls.comboBox_t1->SetPredicate(m_T1Predicate);
  m_Controls.comboBox_t1->SetDataStorage(this->GetDataStorage());

  m_Controls.comboBox_flair->SetAutoSelectNewItems(true);
  m_Controls.comboBox_flair->SetPredicate(m_FlairPredicate);
  m_Controls.comboBox_flair->SetDataStorage(this->GetDataStorage());

  // signals/slots connections
  connect(m_Controls.pushButtonRun, SIGNAL(clicked()),this, SLOT(OnRunButtonClicked()));

  connect(m_Controls.pushButtonRunScript, SIGNAL(clicked()),this, SLOT(OnRunScriptClicked()));

  connect(m_Controls.comboBox_tasks, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTaskChanged(int)));

  connect(m_Controls.comboBox_t1, SIGNAL(OnSelectionChanged(const mitk::DataNode *)), this, SLOT(OnT1SelectionChanged(const mitk::DataNode *)));

  connect(m_Controls.comboBox_flair, SIGNAL(OnSelectionChanged(const mitk::DataNode *)), this, SLOT(OnFlairSelectionChanged(const mitk::DataNode *)));
  
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
	//get datastorage( we use it further down )
	auto ds = this->GetDataStorage();

	//get selected nodes
	QList<mitk::DataNode::Pointer> nodes = this->GetDataManagerSelection();

	//we don't handle the case where data is not loaded or more than 1 nodes are selected
	if (nodes.empty() || nodes.size() > 1)
	{
		QMessageBox msgError;
		msgError.setText("Please load and select a dataset.");
		msgError.setIcon(QMessageBox::Critical);
		msgError.setWindowTitle("selection error");
		msgError.exec();
	}
	else
	{
		//get first node from list
		mitk::DataNode *node = nodes.front();

		auto data = node->GetData();
		// node has data?
		if (data != nullptr)
		{
			// get smart pointer from data
			mitk::Image::Pointer image = dynamic_cast<mitk::Image*>(data);
			// ... has IMAGE data? :D
			if (image.IsNotNull())
			{
				auto imageName = node->GetName();
				MITK_INFO << "Processing image \"" << imageName << "\" ...";

				// get our inverter filter class (note this isn't a proper ITK-style smart pointer --
				// change this in your code if you are using a proper filter.
				auto mediator = DeepMRSegMediator();
				auto mediatorPtr = &mediator;

				mediatorPtr->SetInput(image);
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

				MITK_INFO << "Adding a name";
				// Add a suffix so users can easily see what it is
				QString name = QString("%1_segmented").arg(imageName.c_str());
				processedImageDataNode->SetName(name.toStdString());

				// Finally, add the new node to the data storage.
				ds->Add(processedImageDataNode,node);

			}
		}
	}
}

/************************************************************************/
/* protected                                                            */
/************************************************************************/

void QDeepMRSegView::OnRunScriptClicked()
{
	MITK_INFO << "  script button clicked ";
	DeepMRSegMediator dmrs_mediator;
	dmrs_mediator.RunSampleScript();
}

void QDeepMRSegView::OnTaskChanged(int index)
{
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
	//TBD: if we want to do something when T1 selection changes
}

void QDeepMRSegView::OnFlairSelectionChanged(const mitk::DataNode *)
{
	//TBD: if we want to do something when Flair selection changes
}

void QDeepMRSegView::OnSelectionChanged(berry::IWorkbenchPart::Pointer, const QList<mitk::DataNode::Pointer>& /*nodes*/)
{

}

void QDeepMRSegView::OnPreferencesChanged(const berry::IBerryPreferences* /*prefs*/)
{

}

void QDeepMRSegView::NodeAdded(const mitk::DataNode* /*node*/)
{

}

void QDeepMRSegView::NodeRemoved(const mitk::DataNode* /*node*/)
{

}

void QDeepMRSegView::SetFocus()
{

}

void QDeepMRSegView::UpdateControls()
{
  // Here you can hide views that are not useful and more
}

void QDeepMRSegView::InitializeListeners()
{

}