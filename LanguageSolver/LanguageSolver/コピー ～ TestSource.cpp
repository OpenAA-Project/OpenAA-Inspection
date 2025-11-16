/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\コピー ～ TestSource.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


		"あいうえお"
#include <QBuffer>
#include <QMessageBox>
#include <QSqlRecord>

#include "RepairStation.h"
#include "XDataInLayer.h"
#include "ImageDataUnit.h"


//extern	EntryPointForGlobal	EntryPointToFunc;

RepairStation::RepairStation(QWidget *parent, Qt::WindowFlags flags)
{
	ui.setupUi(this);

	//作業者選択画面の表示
	WorkerSelectForm WorkerSelectDialog(this);
//	if(!WorkerSelectDialog.exec())
	WorkerSelectDialog.exec();
//		return;

	//初期処理
	Init();

	/*
	//RepairSetting.datの読み込み
	QStringList RepairSettingList;
	if(LoadFile("C:\\Regulus64v5\\RepairSetting.dat",RepairSettingList)){
		MasterDir=RepairSettingList.at(0);		//MasterData Directory
	}
*/
}

RepairStation::~RepairStation()
{
	delete IDataUnit;
}

void RepairStation::pbMasterSelectClicked()
{
	QString MasterImagePath=QFileDialog::getOpenFileName(
							this,tr("Please choose a '.pix' file."),"","ImageBuffer (*.pix)");
	if(MasterImagePath=="")
		return;
	char	*Q1="あいうえお";
	char	*Q2="かきく"
			"けこ"
			"さしすせそ";
}



