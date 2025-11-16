/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\StartCaptureButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTCAPTUREBUTTON_H
#define STARTCAPTUREBUTTON_H

#include "startcapturebutton_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	StartCaptureButton : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;

	int		ClickOn;
	bool	Calculating;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	ImageType;	//"Master" "Target"
	QColor	NormalColor;
	QColor	PushedColor;

	bool	MasterImageMode;

	StartCaptureButton(LayersBase *Base ,QWidget *parent);
	~StartCaptureButton(void);
	
	virtual void	Prepare(void)			override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;
	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandStart(void);
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
protected:
	virtual	bool OnIdle(void)	override;
public slots:
	//void	SlotClicked (bool checked);
	void	SlotToggled (bool checked);
	void	ResizeAction();
};


#endif // STARTCAPTUREBUTTON_H
