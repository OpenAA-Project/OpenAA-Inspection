#ifndef GUIREVIEWTEMPLATE_H
#define GUIREVIEWTEMPLATE_H

#include "GUIReviewTemplate_global.h"

#include "ui_GUIReviewTemplateForm.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"

// テンプレートGUIReview
class GUIREVIEWTEMPLATE_EXPORT GUIReviewTemplate : public GUIFormBase
{
	Q_OBJECT

public:
	GUIReviewTemplate(LayersBase *Base,QWidget *parent);
	~GUIReviewTemplate();

public:
	// 更新要求を受け取り、m_mapを更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructureからデータを取得してm_mapの情報を更新する

public slots:
	void ResizeAction(void);

private:
	Ui::GUIReviewTemplateClass ui;
};


#endif // GUIREVIEWTEMPLATE_H
