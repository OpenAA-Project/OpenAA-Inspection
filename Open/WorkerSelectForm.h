/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\WorkerSelectForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef WORKERSELECTFORM_H
#define WORKERSELECTFORM_H

#include <QDialog>
#include "ui_WorkerSelectForm.h"

class RepairBase;

class WorkerSelectForm : public QDialog
{
    Q_OBJECT

public:
	WorkerSelectForm(RepairBase *ParentClass,QWidget *parent=0);
	~WorkerSelectForm();

protected:

signals:
	void SignalClose();

private slots:
	void pbOKClicked();
	void WorkerListChanged(const QModelIndex &CIndex);		//作業者リストのChangedイベント

private:
    Ui::WorkerSelectClass ui;
	QStringList WFieldNames;
	RepairBase *PClass;

	void SelectData();
};

#endif // WORKERSELECTFORM_H
