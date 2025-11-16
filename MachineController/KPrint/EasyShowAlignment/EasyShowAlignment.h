#pragma once

#include "easyshowalignment_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>
#include <QPushButton>

class EasyShowAlignmentForm;

class EasyShowAlignment: public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	EasyShowAlignmentForm	*Window;
	QImage	PanelImage;
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	EasyShowAlignment(LayersBase *Base ,QWidget *parent = 0);
	virtual	~EasyShowAlignment();

	virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual void	ShowInPlayer		(int64 shownInspectionID=-1)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
