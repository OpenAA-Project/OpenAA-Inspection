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

#include "SaveNewMasterResource.h"

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
	//�ۑ��{�^���N���b�N����
	QString MasterName	=ui.leMasterName->text();
	QString Remarks		=ui.leRemarks->text();

	//�v���V�[�W���[�ɂ��郌�R�[�h�̍쐬
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
	//MASTERCODE�̍ő��l���擾
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