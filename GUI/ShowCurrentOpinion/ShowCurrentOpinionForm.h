/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowCurrentOpinion\ShowCurrentOpinionForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWCURRENTOPINIONFORM_H
#define SHOWCURRENTOPINIONFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowCurrentOpinionForm.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowCurrentOpinionForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowCurrentOpinionForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowCurrentOpinionForm();

	virtual void	Prepare(void)	override;
private:
	Ui::ShowCurrentOpinionFormClass ui;

private slots:
	void on_tableWidgetGUI_clicked(const QModelIndex &);
	void on_pushButtonUpdate_clicked();
    void on_listWidgetCommentOpinionList_clicked(const QModelIndex &index);
};

#endif // SHOWCURRENTOPINIONFORM_H
