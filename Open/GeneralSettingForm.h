/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\GeneralSettingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef GENERALSETTINGFORM_H
#define GENERALSETTINGFORM_H

#include <QDialog>
#include <QLibrary>
#include "ui_GeneralSettingForm.h"

class RepairBase;

class GeneralSettingForm : public QDialog
{
    Q_OBJECT

public:
	GeneralSettingForm(RepairBase *ParentClass,QWidget *parent);
	~GeneralSettingForm();

protected:

private slots:
	void on_pbSetColor_clicked();
	void pbMasterDirClicked();
	void chNGBlinkEnableToggled(bool Tog);
	void pbReturnSettingClicked();
	void pbReturnDefaultClicked();
	void pbSaveDirNGImageClicked();
	void pbShowSigGraphClicked();
	void tbPieceColorClicked();
	void tbOnlyFColorClicked();
	void tbOnlyBColorClicked();
	void tbFBColorClicked();
	void pbOKClicked();
	void pbCancelClicked();

	void pbMMCSettingClicked();

private:
    Ui::GeneralSettingClass ui;
	RepairBase *PClass;
	QString		SaveDatPath;
	QString		XmlConnectDatPath;
	QStringList	SaveDatList;
	QStringList	XmlConnectDatList;
	bool		ApplySigmoid;
	bool		(*DLL_GetName)(QString &str);
	void		(*DLL_FormShow)(void);
	bool		(*DLL_MMCSettingFormShow)(QStringList &List);
//	bool LoadSaveDat();
//	bool LoadXmlConnectDat();
//	bool LoadRepairSettingDat();
};

#endif // GENERALSETTINGFORM_H
