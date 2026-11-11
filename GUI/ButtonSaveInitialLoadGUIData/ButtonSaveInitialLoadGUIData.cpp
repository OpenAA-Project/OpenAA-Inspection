/*
 * Copyright (C) 2025
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

//#include "ButtonSaveInitialLoadGUIDataResource.h"
#include "ButtonSaveInitialLoadGUIData.h"
#include <QMessageBox>
#include <QApplication>
#include "XGUIDLL.h"
#include "SaveInitialLoadGUIDataDialog.h"
#include "XGUI.h"

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"SaveInitialLoadGUIData";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Save/InitialLoad GUI data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveInitialLoadGUIData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSaveInitialLoadGUIData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveInitialLoadGUIData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveInitialLoadGUIData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveInitialLoadGUIData *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"InitialFileName";
	Data[4].Pointer				 =&((ButtonSaveInitialLoadGUIData *)Instance)->InitialFileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveInitialLoadGUIData.png")));
}

//==================================================================================================
GUIDataList::GUIDataList(const GUIDataList &src)
{
	DLLRoot	=src.DLLRoot	;
	DLLName	=src.DLLName	;
	InstName=src.InstName	;
	Data	=src.Data		;
}

bool	GUIDataList::operator=(const GUIDataList &src)
{
	DLLRoot	=src.DLLRoot	;
	DLLName	=src.DLLName	;
	InstName=src.InstName	;
	Data	=src.Data		;
	return true;
}
bool	GUIDataList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver		)==false)	return false;
	if(::Save(f,DLLRoot	)==false)	return false;
	if(::Save(f,DLLName	)==false)	return false;
	if(::Save(f,InstName)==false)	return false;
	if(::Save(f,Data	)==false)	return false;
	return true;
}
bool	GUIDataList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver		)==false)	return false;
	if(::Load(f,DLLRoot	)==false)	return false;
	if(::Load(f,DLLName	)==false)	return false;
	if(::Load(f,InstName)==false)	return false;
	if(::Load(f,Data	)==false)	return false;
	return true;
}


GUIDataList *GUIDataListContainer::Create(void)	
{
	return new GUIDataList();
}

bool	GUIDataListContainer::HasSameData(GUIDataList *data)
{
	for(GUIDataList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->DLLRoot	==data->DLLRoot	&&
		   p->DLLName	==data->DLLName	&&
		   p->InstName	==data->InstName){
			return true;
		}
	}
	return false;
}

bool	GUIDataListContainer::GetContentData(GUIInitializer *GInitialier)
{
	for(GUIDataList *p=GetFirst();p!=NULL;p=p->GetNext()){
		GUIFormBase	*form=GInitialier->Search(p->DLLRoot ,p->DLLName ,p->InstName);
		if(form!=NULL){
			QBuffer		Buffer;
			Buffer.open(QIODevice::WriteOnly);
			form->SaveContent(&Buffer);
			p->Data=Buffer.buffer();
		}
	}
	return true;
}

bool	GUIDataListContainer::RefrectContentData(GUIInitializer *GInitialier)
{
	for(GUIDataList *p=GetFirst();p!=NULL;p=p->GetNext()){
		GUIFormBase	*form=GInitialier->Search(p->DLLRoot ,p->DLLName ,p->InstName);
		if(form!=NULL){
			QBuffer		Buffer(&p->Data);
			Buffer.open(QIODevice::ReadOnly);
			form->LoadContent(&Buffer);
		}
	}
	return true;
}

//==================================================================================================

ButtonSaveInitialLoadGUIData::ButtonSaveInitialLoadGUIData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save GUI";
	resize(60,25);
	InitialFileName	=/**/"InitialGUIFile.dat";

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveInitialLoadGUIData::~ButtonSaveInitialLoadGUIData(void)
{
}

void	ButtonSaveInitialLoadGUIData::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveInitialLoadGUIData::AfterStartSequence(void)
{
	LoadDataAndReflect();
}

void	ButtonSaveInitialLoadGUIData::ResizeAction()
{
	Button.resize(width(),height());
}

bool	ButtonSaveInitialLoadGUIData::SaveData(void)
{
	QFile	File(InitialFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		Data.GetContentData(GetLayersBase()->GetGuiInitializer());
		Data.Save(&File);
		return true;
	}
	return false;
}
bool	ButtonSaveInitialLoadGUIData::LoadDataAndReflect(void)
{
	QFile	File(InitialFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		Data.Load(&File);
		Data.RefrectContentData(GetLayersBase()->GetGuiInitializer());
		return true;
	}
	return false;
}

void ButtonSaveInitialLoadGUIData::SlotClicked (bool checked)
{
	SaveInitialLoadGUIDataDialog	D(this);
	if(D.exec()==true){
		SaveData();
	}
}