/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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