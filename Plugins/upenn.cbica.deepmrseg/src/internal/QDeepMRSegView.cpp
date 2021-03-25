#include "QDeepMRSegView.h"

#include <QMessageBox>

#include "DeepMRSegMediator.h"

const std::string QDeepMRSegView::VIEW_ID =
    "upenn.cbica.deepmrseg.view";


QDeepMRSegView::QDeepMRSegView()
{
  // ---- General setup operations ----
}

QDeepMRSegView::~QDeepMRSegView()
{

}

void QDeepMRSegView::CreateQtPartControl(QWidget *parent)
{
  // ---- Setup the basic GUI of this view ----
  m_Parent = parent;
  m_Controls.setupUi(parent);

  //hide temporarily since python side doesn't yet thrown progress
  m_Controls.progressBar->hide(); 

  //temporarily disabled since this would change
  m_Controls.groupBox_DataSelection->setDisabled(true); 

  connect(m_Controls.pushButtonRun, SIGNAL(clicked()),
	  this, SLOT(OnDoStuffButtonClicked()));

  connect(m_Controls.pushButtonRunScript, SIGNAL(clicked()),
	  this, SLOT(OnRunScriptClicked()));
  
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

void QDeepMRSegView::OnDoStuffButtonClicked()
{
    //QMessageBox msgError;
    //msgError.setText("Hello, I am DeepMRSeg.");
    //msgError.setIcon(QMessageBox::Critical);
    //msgError.setWindowTitle("DeepMRSeg");
    //msgError.exec();

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
				auto filter = DeepMRSegMediator();
				auto filterPtr = &filter;

				filterPtr->SetInput(image);
				filterPtr->Update();
				mitk::Image::Pointer processedImage = filterPtr->GetOutput();

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
				QString name = QString("%1_inverted").arg(imageName.c_str());
				processedImageDataNode->SetName(name.toStdString());

				// Finally, add the new node to the data storage.
				ds->Add(processedImageDataNode);

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