/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistory\ListHistoryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTHISTORYFORM_H
#define LISTHISTORYFORM_H

#include "XGUIFormBase.h"
#include "ui_ListHistoryForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ListHistoryForm : public GUIFormBase
{
	Q_OBJECT

	bool	SyncMode;
	bool	LocalMode;
	int		ColumnNoID		;
	int		ColumnNoTime	;
	int		ColumnNoOKNG	;	
	int		ColumnNoSV		;
	int		ColumnNoMS		;

	QString	StrResultNot;
	QString	StrResultOK;
	QString	StrResultTMHalt;
	QString	StrResultErHalt;
	QString	StrResultNG;
	QString	StrResultNGOther;
	QString	StrWrittenTrue;
	QString	StrWrittenFalse;

public:
	QColor	ColorOK;
	QColor	ColorNG;
	QColor	ColorNot;
	QColor	ColorIrregular;
	bool	ShowColumnID	;
	bool	ShowColumnTime	;
	bool	ShowColumnOKNG	;
	bool	ShowColumnSV	;
	bool	ShowColumnMS	;

	ListHistoryForm(LayersBase *Base ,QWidget *parent = 0);
	~ListHistoryForm();

	virtual void	Prepare(void)			override;
	virtual void	ReadyParam(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)		override;
	virtual void	RxSync(QByteArray &f)	override;

	QString	OutputFileName;
	bool	EditMode;

private:
	Ui::ListHistoryFormClass ui;

private slots:
	void on_tableWidgetHistory_doubleClicked(QModelIndex);
	void on_ButtonReset_clicked();
	void	ResizeAction();
};


class	GUIReqRemoveHistry : public GUICmdPacketBase
{
public:

	GUIReqRemoveHistry(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // LISTHISTORYFORM_H
