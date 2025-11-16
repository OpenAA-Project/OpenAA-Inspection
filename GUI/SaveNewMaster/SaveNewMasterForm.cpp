#include "SaveNewMasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveNewMaster\SaveNewMasterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QSqlQuery>
#include "SaveNewMasterForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"

SaveNewMasterForm::SaveNewMasterForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

SaveNewMasterForm::~SaveNewMasterForm()
{
}

void SaveNewMasterForm::on_pbSave_clicked()
{
	//保存ボタンクリック処理
	QString MasterName	=ui.leMasterName->text();
	QString Remarks		=ui.leRemarks->text();

	//プロシージャーによるレコードの作成
	QSqlQuery insertQuery(GetLayersBase()->GetDatabase());
//	insertQuery.prepare("EXECUTE PROCEDURE ProcMasterInsert");
/*
	insertQuery.prepare("EXECUTE PROCEDURE PROC_Test(?,?)");
	insertQuery.addBindValue(MasterName);
	insertQuery.addBindValue(Remarks);
	insertQuery.addBindValue(0,QSql::Out);
	insertQuery.exec();
	int MaxID=insertQuery.boundValue(2).toInt();
*/
	//MASTERCODEの最大値を取得
	QSqlQuery query(/**/"SELECT MAX(MASTERCODE) from MASTERDATA" ,GetLayersBase()->GetDatabase());
	query.next ();
	int	MasterCode = query.value(0).toInt()+1;
/*
	QSqlQuery query("SELECT GEN_ID(TestTable_ID_GEN,1) from rdb$database" ,GetLayersBase()->GetDatabase());
	query.next ();
	int	MasterCode = query.value(0).toInt();
*/
	insertQuery.prepare(/**/"INSERT INTO MASTERDATA(MASTERCODE,MASTERNAME,REMARK) VALUES(?,?,?)");
	insertQuery.addBindValue(MasterCode);
	insertQuery.addBindValue(MasterName);
	insertQuery.addBindValue(Remarks);
	if(insertQuery.exec()==false){
		ui.lbMasterID->setText(/**/"");
		return;
	}
	ui.lbMasterID->setText(QString::number(MasterCode));
}
