/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonUpdateMasterData\ButtonUpdateMasterData.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONUPDATEMASTERDATA_H
#define BUTTONUPDATEMASTERDATA_H

#include "buttonupdatemasterdata_global.h"

#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonUpdateMasterData : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString ErrorMessageOfFalse;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	UpdateGeneralSetting;

	ButtonUpdateMasterData(LayersBase *Base ,QWidget *parent);
	~ButtonUpdateMasterData(void);
	
	virtual void	Prepare(void)			override;

	bool	CommandUpdateMaster(QString &tMasterName,QString &tRemark ,bool SilentMode);
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)		override;

	virtual	void	RxSync(QByteArray &f)	override;
public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};

#endif // BUTTONUPDATEMASTERDATA_H
