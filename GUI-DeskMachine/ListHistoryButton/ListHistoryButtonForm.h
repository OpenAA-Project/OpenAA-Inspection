/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButtonForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTHISTORYBUTTONFORM_H
#define LISTHISTORYBUTTONFORM_H

#include "ui_ListHistoryButtonForm.h"
#include "XGUIPacketForDLL.h"
#include "ListHistoryButton.h"
#include<QDialog>

class ListHistoryButtonForm : public QDialog
{
	Q_OBJECT

	LayersBase	*LBase;
	ListHistoryButton	*ParentWidget;

public:
	ListHistoryButtonForm(LayersBase *Base ,QWidget *parent = 0);
	~ListHistoryButtonForm();

	QTableWidget	*GetTableWidgetHistory()	{	return ui.tableWidgetHistory;	}
	QLabel			*GetLabelOK()				{	return ui.labelOK;				}
	QLabel			*GetLabelNG()				{	return ui.labelNG;				}
	QLabel			*GetLabelSUM()				{	return ui.labelSUM;				}

public slots:
	void tableWidgetHistoryDoubleClicked(QModelIndex);
	void ButtonResetClicked();

private:
	Ui::ListHistoryButtonFormClass ui;
	bool	PopupForm;

	void	ExecCmdListHistoryButtonUpdate();
};

class	GUIReqRemoveHistry : public GUICmdPacketBase
{
public:

	GUIReqRemoveHistry(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LISTHISTORYBUTTONFORM_H
