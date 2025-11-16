/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\AddFileDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QDialog>
#include "ui_AddFileDialog.h"
#include "XLearning.h"
#include "XServiceForLayers.h"

class AddFileDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddFileDialog(LayersBase *base, QWidget *parent);
	~AddFileDialog();

	int	SelectedPage;
	LearningFileListContainer	SelectedList;
private:
	Ui::AddFileDialogClass ui;

	void	ShowList();
	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
	void on_comboBoxPage_currentIndexChanged(int);
	void on_comboBoxPage_textChanged(QString);
	void on_pushButtonCancel_clicked();
	void on_pushButtonAdd_clicked();
};

#endif // ADDFILEDIALOG_H
