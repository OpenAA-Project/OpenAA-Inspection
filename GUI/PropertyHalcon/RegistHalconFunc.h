/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\RegistHalconFunc.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef REGISTHALCONFUNC_H
#define REGISTHALCONFUNC_H

#include <QDialog>
#include "ui_RegistHalconFunc.h"
#include "PropertyHalconForm.h"

class RegistHalconFunc : public QDialog
{
	Q_OBJECT

public:
	RegistHalconFunc(PropertyHalconForm *parent);
	~RegistHalconFunc();

private:
	Ui::RegistHalconFuncClass ui;

	QLabel		*HLabel[10];
	QComboBox	*ComboBox[10];
	QLabel		*FLabel[10];

	PropertyHalconForm *PClass;
	QStringList	ArgRegionList;
	QStringList	ArgTupleList;

	QStringList HLabelStringList;
	QStringList FLabelStringList;

	ArgType		ATypeList[10];
	QString		*HalconFuncString;

	void VisibleSet(bool Visible,int VisibleCnt);
	void SetCombInformation(ArgType Type1,int CntType1,ArgType Type2,int CntType2);
	void SetCombInformation(ArgType Type,int CntType,int Index=0);
	void SetCombInformation(char **List,int Index);

private slots:
	void cbFunCcurrentIndexChanged(int Index);
	void pbOKClicked();
	void pbCancelClicked();
};

#endif // REGISTHALCONFUNC_H
