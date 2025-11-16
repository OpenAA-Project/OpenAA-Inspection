/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartStatisticScanButton\StartStatisticScanButtonForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTSTATISTICSCANBUTTONFORM_H
#define STARTSTATISTICSCANBUTTONFORM_H

#include "XGUIFormBase.h"
#include "ui_StartStatisticScanButtonForm.h"
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "StartStatisticScanBase.h"

class StartStatisticScanButtonForm : public GUIFormBase , public StartStatisticScanBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	int		Counter;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
public:
	StartStatisticScanButtonForm(LayersBase *Base ,QWidget *parent = 0);
	~StartStatisticScanButtonForm();

	virtual void	Prepare(void)	override;
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;

private:
	Ui::StartStatisticScanButtonFormClass ui;

protected:
	virtual	bool OnIdle(void)		override;

	virtual	void OnIdleEnd(void)	override;
	virtual	void OnToggled(void)	override;

private slots:
	//void SlotClicked (bool checked);
	void	SlotToggled (bool checked);
	void	ResizeAction();
};
//==============================================================

#endif // STARTSTATISTICSCANBUTTONFORM_H
