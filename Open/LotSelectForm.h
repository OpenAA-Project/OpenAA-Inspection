/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\LotSelectForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef LOTSELECTFORM_H
#define LOTSELECTFORM_H

#include <QDialog>
#include "ui_LotSelectForm.h"

class RepairBase;
class ProcessingForm;

class LotSelectForm : public QDialog
{
    Q_OBJECT

public:
	LotSelectForm(RepairBase *ParentClass,QWidget *parent = 0);
	~LotSelectForm();

	bool GetResult()			{	return Result;	}
	void SetBoth(bool Flag)		{	IsBoth=Flag;	}
	bool GetBoth()				{	return IsBoth;	}
	bool ExecSelectLot(QString LotName,QString LotID);

protected:

signals:
	void SignalClose();

private slots:
	void pbSearchClicked();
	void leSearchLotNameTextChanged(QString text);
	void pbSelectClicked();
	void pbAllSelectClicked();
	void pbCancelClicked();

private:
    Ui::LotSelectClass ui;
	RepairBase			*PClass;
	QStringList			 LFieldNames;
	QList<QByteArray>	 RetList;
//	ProcessingForm		*LotProcessing;

	bool Result;
	bool IsBoth;
};

#endif // LOTSELECTFORM_H
