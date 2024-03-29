/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
**/
#ifndef QDeepMRSegView_h
#define QDeepMRSegView_h

#include <QmitkAbstractView.h>
#include <mitkILifecycleAwarePart.h>
#include <mitkNodePredicateAnd.h>

#include "ui_QDeepMRSegControls.h"

class QDeepMRSegView : public QmitkAbstractView, 
                              public mitk::ILifecycleAwarePart
{
  Q_OBJECT

public:
	enum TaskType
	{
		BRAINEXTRACTION = 0,
		LESIONSEGMENTATION,
		MUSESEGMENTATION,
		SELECTTASK
	};

  static const std::string VIEW_ID;

  QDeepMRSegView();
  virtual ~QDeepMRSegView();

  Q_ENUM(TaskType)

  // GUI setup
  void CreateQtPartControl(QWidget *parent);

  // ILifecycleAwarePart interface
  void Activated();
  void Deactivated();
  void Visible();
  void Hidden();

protected slots:

  /** \brief "Do Stuff" Button clicked slot */
  void OnRunButtonClicked();

  /** \brief task changed slot */
  void OnTaskChanged(int);

  /** \brief T1 selection changed slot */
  void OnT1SelectionChanged(const mitk::DataNode *);

  /** \brief Flair selection changed slot */
  void OnFlairSelectionChanged(const mitk::DataNode *);

  /** \brief Flair selection changed slot */
  void OnSelectModelButtonClicked();

protected:

  // reimplemented from QmitkAbstractView
  void OnSelectionChanged(berry::IWorkbenchPart::Pointer part, const QList<mitk::DataNode::Pointer> &nodes) override;

  // reimplemented from QmitkAbstractView
  void OnPreferencesChanged(const berry::IBerryPreferences *prefs) override;

  // reimplemented from QmitkAbstractView
  void NodeAdded(const mitk::DataNode *node) override;

  // reimplemented from QmitkAbstractView
  void NodeRemoved(const mitk::DataNode *node) override;

  void SetFocus();

  void UpdateControls();

  void InitializeListeners();

  /// \brief the Qt parent of our GUI (NOT of this object)
  QWidget *m_Parent;

  /// \brief Qt GUI file
  Ui::QDeepMRSegControls m_Controls;

  mitk::NodePredicateAnd::Pointer m_T1Predicate;
  mitk::NodePredicateAnd::Pointer m_FlairPredicate;

  TaskType m_taskType;
};

#endif // ! QDeepMRSegView_h