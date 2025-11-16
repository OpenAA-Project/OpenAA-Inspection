#ifndef LIVECAMERADFK31AF03_H
#define LIVECAMERADFK31AF03_H

#include "LiveCameraDFK31AF03_global.h"

#include "ui_LiveCameraDFK31AF03Form.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"

#include "AreaCamera.h"

//#include "AreaCameraLib.h"

// テンプレートGUIReview
class LIVECAMERADFK31AF03_EXPORT LiveCameraDFK31AF03 : public GUIFormBase
{
	Q_OBJECT

public:
	LiveCameraDFK31AF03(LayersBase *Base,QWidget *parent);
	~LiveCameraDFK31AF03();

public:
	// 更新要求を受け取り、m_mapを更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void mousePressEvent(QMouseEvent *)	override;

public:
	void updateGUI();// ReviewStructureからデータを取得してm_mapの情報を更新する

public slots:
	void ResizeAction(void);

private:
	Ui::LiveCameraDFK31AF03Class ui;
	QWidget *widget;
};


#endif // LIVECAMERADFK31AF03_H
