#ifndef BUTTONTOSHOWREVIEWSETTING_H
#define BUTTONTOSHOWREVIEWSETTING_H

#include "ButtonToShowReviewSetting_global.h"

#include "ui_ButtonToShowReviewSettingForm.h"
#include "ReviewSettingFormBase.h"

#include "XDLLOnly.h"

// 設定画面を表示するボタンのGUI
class BUTTONTOSHOWREVIEWSETTING_EXPORT ButtonToShowReviewSetting : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonToShowReviewSetting(LayersBase *Base,QWidget *parent);
	~ButtonToShowReviewSetting();

public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructureからデータを取得してm_mapの情報を更新する

public slots:
	void ResizeAction(void);
	void clicked();

private:
	Ui::ButtonToShowReviewSettingClass ui;
};


#endif // GUIREVIEWTEMPLATE_H
