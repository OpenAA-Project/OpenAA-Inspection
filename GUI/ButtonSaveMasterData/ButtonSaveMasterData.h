/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveMasterData\ButtonSaveMasterData.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSAVEMASTERDATA_H
#define BUTTONSAVEMASTERDATA_H

#include "buttonsavemasterdata_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveMasterData : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString ErrorMessageOfFalse;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ModeCheckDupName;
	bool	ExecuteInitialAfterSaving;

	ButtonSaveMasterData(LayersBase *Base ,QWidget *parent);
	~ButtonSaveMasterData(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	
	bool	CommandSaveMaster	(QString &tMasterName,QString &tRemark ,bool SilentMode);
	int		CommandSearchMaster	(QString &tMasterName);
public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};


#endif // BUTTONSAVEMASTERDATA_H
