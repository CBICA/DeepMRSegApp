/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file:
https://github.com/CBICA/InciSe/blob/main/LICENSE
**/

#include "QmitkDeepMRSegIntroPart.h"

#include <berryIWorkbenchWindow.h>
#include <berryIWorkbench.h>
#include <berryIWorkbenchPage.h>
#include <berryIPerspectiveRegistry.h>
#include <berryWorkbenchPreferenceConstants.h>
#include <berryIPreferences.h>
#include <berryIPreferencesService.h>
#include <berryPlatform.h>

#include <berryIEditorReference.h>
#include <berryIEditorInput.h>

#include <ctkPluginContext.h>

#include <mitkIDataStorageService.h>
#include <mitkDataStorageEditorInput.h>

#include <mitkLogMacros.h>

#include <QLabel>
#include <QMessageBox>
#include <QtCore/qconfig.h>

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QChar>
#include <QByteArray>
#include <QDesktopServices>

#include "QmitkDeepMRSegApplicationPlugin.h"
#include "mitkDataStorageEditorInput.h"
#include <string>

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QUrlQuery>

class QmitkDeepMRSegIntroPart::Impl
{
public:
  Impl()
    : View(nullptr)
  {
  }

  ~Impl()
  {
  }

  QWebEngineView* View;

private:
  Impl(const Impl&);
  Impl& operator=(const Impl&);
};

namespace
{
  class QmitkWebEnginePage final : public QWebEnginePage
  {
  public:
    explicit QmitkWebEnginePage(QmitkDeepMRSegIntroPart* introPart, QObject* parent = nullptr);
    ~QmitkWebEnginePage() override;

  private:
    bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame) override;

    QmitkDeepMRSegIntroPart* m_IntroPart;
  };

  QmitkWebEnginePage::QmitkWebEnginePage(QmitkDeepMRSegIntroPart* introPart, QObject* parent)
    : QWebEnginePage(parent),
      m_IntroPart(introPart)
  {
  }

  QmitkWebEnginePage::~QmitkWebEnginePage()
  {
  }

  bool QmitkWebEnginePage::acceptNavigationRequest(const QUrl& url, NavigationType, bool)
  {
    QString scheme = url.scheme();

    if (scheme.contains("mitk"))
    {
      if (url.path().isEmpty())
        return false;

      if (url.host().contains("perspectives"))
      {
        QString id = url.path().simplified().replace("/", "");

        auto introSite = m_IntroPart->GetIntroSite();
        auto workbenchWindow = introSite->GetWorkbenchWindow();
        auto workbench = workbenchWindow->GetWorkbench();

        workbench->ShowPerspective(id, workbenchWindow);

        auto context = QmitkDeepMRSegApplicationPlugin::GetDefault()->GetPluginContext();
        auto serviceReference = context->getServiceReference<mitk::IDataStorageService>();

        mitk::IDataStorageService* service = serviceReference
          ? context->getService<mitk::IDataStorageService>(serviceReference)
          : nullptr;

        if (service)
        {
          berry::IEditorInput::Pointer editorInput(new mitk::DataStorageEditorInput(service->GetActiveDataStorage()));

          auto page = introSite->GetPage();
          auto editorPart = page->FindEditor(editorInput);

          if (editorPart.IsNotNull())
            page->Activate(editorPart);
        }
      }
    }
    else if (scheme.contains("http"))
    {
      QDesktopServices::openUrl(url);
    }
    else
    {
      return true;
    }

    return false;
  }
}

QmitkDeepMRSegIntroPart::QmitkDeepMRSegIntroPart()
  : m_Controls(nullptr),
    m_Impl(new Impl)
{
  berry::IPreferences::Pointer workbenchPrefs = QmitkDeepMRSegApplicationPlugin::GetDefault()->GetPreferencesService()->GetSystemPreferences();
  workbenchPrefs->PutBool(berry::WorkbenchPreferenceConstants::SHOW_INTRO, true);
  workbenchPrefs->Flush();
}

QmitkDeepMRSegIntroPart::~QmitkDeepMRSegIntroPart()
{
  // if the workbench is not closing (that means, welcome screen was closed explicitly), set "Show_intro" false
  if (!this->GetIntroSite()->GetPage()->GetWorkbenchWindow()->GetWorkbench()->IsClosing())
  {
    berry::IPreferences::Pointer workbenchPrefs = QmitkDeepMRSegApplicationPlugin::GetDefault()->GetPreferencesService()->GetSystemPreferences();
    workbenchPrefs->PutBool(berry::WorkbenchPreferenceConstants::SHOW_INTRO, false);
    workbenchPrefs->Flush();
  }
  else
  {
    berry::IPreferences::Pointer workbenchPrefs = QmitkDeepMRSegApplicationPlugin::GetDefault()->GetPreferencesService()->GetSystemPreferences();
    workbenchPrefs->PutBool(berry::WorkbenchPreferenceConstants::SHOW_INTRO, true);
    workbenchPrefs->Flush();
  }

  // if workbench is not closing (Just welcome screen closing), open last used perspective
  if (this->GetIntroSite()->GetPage()->GetPerspective()->GetId()
    == "org.mitk.deepmrseg.perspectives.editor" && !this->GetIntroSite()->GetPage()->GetWorkbenchWindow()->GetWorkbench()->IsClosing())
    {
    berry::IPerspectiveDescriptor::Pointer perspective = this->GetIntroSite()->GetWorkbenchWindow()->GetWorkbench()->GetPerspectiveRegistry()->FindPerspectiveWithId("org.mitk.deepmrseg.perspectives.editor");
    if (perspective)
    {
      this->GetIntroSite()->GetPage()->SetPerspective(perspective);
    }
  }

  delete m_Impl;
}

void QmitkDeepMRSegIntroPart::CreateQtPartControl(QWidget* parent)
{
  if (!m_Controls)
  {
    // create GUI widgets
    m_Controls = new Ui::QmitkDeepMRSegWelcomeScreenViewControls;
    m_Controls->setupUi(parent);

    // create a QWebView as well as a QWebPage and QWebFrame within the QWebview
    m_Impl->View = new QWebEngineView(parent);

    auto page = new QmitkWebEnginePage(this, parent);
    m_Impl->View->setPage(page);

    QUrl urlQtResource(QString("qrc:/upenn.cbica.deepmrseg.deepmrsegwelcomescreen/deepmrsegwelcomeview.html"),  QUrl::TolerantMode );
    m_Impl->View->load( urlQtResource );

    // adds the webview as a widget
    parent->layout()->addWidget(m_Impl->View);

    this->CreateConnections();
  }
}

void QmitkDeepMRSegIntroPart::CreateConnections()
{
}

void QmitkDeepMRSegIntroPart::StandbyStateChanged(bool /*standby*/)
{
}

void QmitkDeepMRSegIntroPart::SetFocus()
{
}
