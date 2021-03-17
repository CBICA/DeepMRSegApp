#include "QDeepMRSegView.h"

#include <QMessageBox>


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
    this, SLOT(OnDoStuffButtonClicked())
  );
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
    QMessageBox msgError;
    msgError.setText("Hello, I am DeepMRSeg.");
    msgError.setIcon(QMessageBox::Critical);
    msgError.setWindowTitle("DeepMRSeg");
    msgError.exec();
}

/************************************************************************/
/* protected                                                            */
/************************************************************************/

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