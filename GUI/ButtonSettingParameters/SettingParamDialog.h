/*
 * Copyright (C) 2024
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


#ifndef SETTINGPARAMDIALOG_H
#define SETTINGPARAMDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include "ui_SettingParamDialog.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"
#include "FormCommSetting.h"
#include "FormScanStrategy.h"
#include "EditOutlineOffset.h"
#include "XServiceForLayers.h"
#include "FormDirectionOnEachPage.h"

class	WEditParameterTab;
class	EditScanPhaseNumber;

class SettingParamDialog : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingParamDialog(LayersBase *Base,QWidget *parent);
	~SettingParamDialog();

private:
	Ui::SettingParamDialogClass ui;

	WEditParameterTab		*WTabGeneral;
	FormCommSetting			*WTabFormCommSetting;
	FormScanStrategy		*WTabFormScanStrategy;
	EditOutlineOffset		*WTabFormOutlineOffset;
	WEditParameterTab		*WTabGUI;
	FormDirectionOnEachPage	*WTabDirection;
	EditScanPhaseNumber		*WEditScanPhaseNumber;

protected:
	virtual	void resizeEvent(QResizeEvent *e)	override;
private slots:
	void on_tabWidgetAllParam_currentChanged(int);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void SlotRefrect();
    void on_ButtonOutlineOffset_clicked();
    void on_pushButtonRowImageTable_clicked();
    void on_pushButtonLoadImageTable_clicked();
    void on_pushButtonEachPage_clicked();
};

class	GUICmdSettingParamImageTable: public GUICmdPacketBase
{
public:
	bool	MoveUseStraight;
	bool	MoveLoadFromDefault;

	GUICmdSettingParamImageTable(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SETTINGPARAMDIALOG_H