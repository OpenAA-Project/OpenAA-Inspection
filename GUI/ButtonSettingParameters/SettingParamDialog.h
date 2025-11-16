/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingParameters\SettingParamDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
