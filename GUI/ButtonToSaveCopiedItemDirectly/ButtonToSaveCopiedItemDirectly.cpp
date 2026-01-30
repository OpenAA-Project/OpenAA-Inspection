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

#include "ButtonToSaveCopiedItemDirectlyResource.h"

#include "ButtonToSaveCopiedItemDirectly.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveCopiedItemDirectly";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Save copied items Directly");
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
	return(new ButtonToSaveCopiedItemDirectly(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"ImagePanelName";
	Data[4].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->ImagePanelName;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"FileName";
	Data[5].Pointer				 =&((ButtonToSaveCopiedItemDirectly *)Instance)->FileName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToSaveCopiedItemDirectly.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonToSaveCopiedItemDirectly	*V=dynamic_cast<ButtonToSaveCopiedItemDirectly *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveCopiedItem(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save CopiedItemDirectly");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

//==================================================================================================
ButtonToSaveCopiedItemDirectly::ButtonToSaveCopiedItemDirectly(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Selection";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonToSaveCopiedItemDirectly::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonToSaveCopiedItemDirectly::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonToSaveCopiedItemDirectly::SlotClicked (bool checked)
{
	QString	LFileName;
	if(FileName.isEmpty()==true){
		LFileName=GetLayersBase()->LGetSaveFileName (this
													, LangSolver.GetString(ButtonToSaveCopiedItemDirectly_LS,LID_0)/*"Save CopiedItem file"*/
													, QString()
													, tr(/**/"SaveCopiedItem File (*.psi)") );
	}
	else{
		LFileName=FileName;
	}
	SaveCopiedItem(LFileName);
}

bool	ButtonToSaveCopiedItemDirectly::SaveCopiedItem(QString LFileName)
{
	GUIFormBase	*v=GetLayersBase()->FindByName(ImagePanelName);
	if(v==NULL){
		return false;
	}
	DisplayImageWithAlgorithm	*DisplayImageWithAlgorithmVar=dynamic_cast<DisplayImageWithAlgorithm *>(v);
	if(DisplayImageWithAlgorithmVar==NULL){
		return false;
	}
	QStringList Args;
	bool ExeReturn;
	if(DisplayImageWithAlgorithmVar->ExecuteMacro(/**/"CopyItems", Args, ExeReturn)==false){
		return false;
	}
	if(ExeReturn==false){
		return false;
	}
	Args.append(LFileName);
	if(DisplayImageWithAlgorithmVar->ExecuteMacro(/**/"SaveTopPastedItems", Args, ExeReturn)==false){
		return false;
	}
	if(ExeReturn==false){
		return false;
	}
	return true;
}