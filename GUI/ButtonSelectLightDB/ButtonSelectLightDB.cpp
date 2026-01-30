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

#include "ButtonSelectLightDBResource.h"

#include "ButtonSelectLightDB.h"
#include "XDataInLayer.h"
#include "XLightClass.h"
#include "XGeneralDialog.h"
#include "SelectLightForm.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ButtonSelectLightDB";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show button to select Light on DB");
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
	return(new ButtonSelectLightDB(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectLightDB *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectLightDB *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectLightDB *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectLightDB *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectLightDB.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSelectLightDB::ButtonSelectLightDB(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	SelectedLightID	=-1;
	Button.move(0,0);
	Msg=/**/"Select Light";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSelectLightDB::~ButtonSelectLightDB(void)
{
}

void	ButtonSelectLightDB::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectLightDB::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectLightDB::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		SelectLightForm	*DForm=new SelectLightForm(GetLayersBase(),true,true, GetLayersBase()->GetMachineID(),NULL);
		DForm->SelectedLightID=-1;
		GeneralDialog	D(GetLayersBase(),DForm,this);
		D.exec();
		SelectedLightID=DForm->SelectedLightID;
		BroadcastShowInEdit();
	}
}

void	ButtonSelectLightDB::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqCurrentSelectedLightID	*CmdReqCurrentSelectedLightIDVar=dynamic_cast<CmdReqCurrentSelectedLightID *>(packet);
	if(CmdReqCurrentSelectedLightIDVar!=NULL){
		CmdReqCurrentSelectedLightIDVar->SelectedLightID=SelectedLightID;
		return;
	}
}