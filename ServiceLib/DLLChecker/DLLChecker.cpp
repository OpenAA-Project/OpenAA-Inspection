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

#include "DLLChecker.h"
#include "CheckDLLForm.h"
#include "EditAlgorithmList.h"
#include "XGeneralDialog.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XGUIFormBase.h"
#include "ShowSystemVersionDialog.h"


static	int	SDebug;

DLLChecker::DLLChecker(LayersBase *Base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base),GUIPack(Base,Base->GetGuiInitializer())
{
	ui.setupUi(this);

	GetLayersBase()->GetEntryPoint()->GUISetEditMode(true);
	ParamGUI		*Pg=GetLayersBase()->GetParamGUI();
	int	LastCount=0;
	try{
		for(GuiDLLItem *w=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetFirst();w!=NULL;w=w->GetNext()){
			GetLayersBase()->TestLoadDLL(w->FileName);
			if(w->FileName=="GUI\\MatchShiftRotationImagePanel.dll")
				SDebug++;
			w->SetLanguageCode(GetLayersBase()->GetLanguageCode());
			GUIFormBase	*GF=w->CreateInstance(GetLayersBase(),NULL);
			int	n=Pg->GetCount();
			if(n!=LastCount){
				GUIItemInstance	*Inst=new GUIItemInstance(&GUIPack);
				Inst->DLLAccess=w;
				Inst->Handle=GF;
				GUIPack.AppendList(Inst);
				LastCount=n;
			}
			else{
				w->DeleteInstance(GF);
			}
		}
	}
	catch(...){
	}
}

DLLChecker::~DLLChecker()
{

}


void DLLChecker::on_pushButtonEditAlgorithm_clicked()
{
	GeneralDialog	D(NULL,new EditAlgorithmList(GetLayersBase()),this);
	D.exec();
}

void DLLChecker::on_pushButtonCheckDLL_clicked()
{
	GeneralDialog	D(NULL,new CheckDLLForm(GetLayersBase()),this);
	D.exec();
}

void DLLChecker::on_pushButtonClose_clicked()
{
	close();
}

void DLLChecker::on_pushButtonDLLVersionList_clicked()
{
	ShowSystemVersionDialog	D(GetLayersBase(),NULL);
	D.exec();
}