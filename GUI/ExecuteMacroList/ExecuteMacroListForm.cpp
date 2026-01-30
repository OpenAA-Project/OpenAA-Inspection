/*
 * Copyright (C) 2022
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

#include "ExecuteMacroListResource.h"
#include "ExecuteMacroListForm.h"
#include "XDataInLayer.h"
#include <QMessageBox>

ExecuteMacroListForm::ExecuteMacroListForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ExecuteMacroListForm::~ExecuteMacroListForm()
{

}


void ExecuteMacroListForm::on_pushButtonLoadMacro_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName(0, LangSolver.GetString(ExecuteMacroListForm_LS,LID_0)/*"Load Macro file"*/);
	if(FileName.isEmpty()==false){
		QFile	FL(FileName);
		FL.open(QIODevice::ReadOnly | QIODevice::Text);
		QString ErrorLine;
		if(SContainer.LoadFromMacro(FL,ErrorLine)==false){
			QMessageBox::critical ( NULL, LangSolver.GetString(ExecuteMacroListForm_LS,LID_1)/*"Loading Error"*/, ErrorLine, QMessageBox::Ok);
			return;
		}
		ShowList();
	}
}

void ExecuteMacroListForm::ShowList(void)
{
	ui.listWidgetMacro->clear();
	for(MacroSentenseBase *a=SContainer.GetFirst();a!=NULL;a=a->GetNext()){
		ui.listWidgetMacro->addItem(a->GetTextLine());
	}
}

void ExecuteMacroListForm::on_pushButtonStartExecute_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ShowList();
	ReEntrant=true;
	CancelMode=false;
	ui.pushButtonStartExecute->setEnabled(false);
	int	Row=0;
	for(MacroSentenseBase *a=SContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		ui.listWidgetMacro->setCurrentRow(Row);
		bool ExeReturn;
		a->ExecuteLine(GetLayersBase(),ExeReturn);
		for(int i=0;i<10;i++){
			QCoreApplication::processEvents();
		}
		if(CancelMode==true){
			break;
		}
	}
	ui.pushButtonStartExecute->setEnabled(true);
	ReEntrant=false;
}

void ExecuteMacroListForm::on_pushButtonStopExecute_clicked()
{
	CancelMode=true;
}
