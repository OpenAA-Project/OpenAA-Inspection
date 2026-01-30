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

#include "ButtonExecuteMacro.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include <QMessageBox>

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ExecuteMacro";


static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to execute macro");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdReqCalcFinalization(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonExecuteMacro(Base,parent));
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
	Data[0].Pointer				 =&((ButtonExecuteMacro *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonExecuteMacro *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonExecuteMacro *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonExecuteMacro *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"MacroFileName";
	Data[4].Pointer				 =&((ButtonExecuteMacro *)Instance)->MacroFileNameByEditGUI;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonExecuteMacro.png")));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Execute";
		Functions[ret].Explain.append(/**/"Execute calc-finalization");
		Functions[ret].DLL_ExcuteMacro	=MacroExecute;
		ret++;
	}
	return ret;
}

static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonExecuteMacro	*V=dynamic_cast<ButtonExecuteMacro *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}


//==================================================================================================
ButtonExecuteMacro::ButtonExecuteMacro(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonExecuteMacro");
	Msg=/**/"Button to execute Macro";

	GetParamGUI()->SetParam(&MacroFileName, /**/"ButtonExecuteMacro",/**/"MacroFileName","Macro file name"		);

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonExecuteMacro::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonExecuteMacro::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonExecuteMacro::SlotClicked (bool checked)
{
	QString	FileName=MacroFileNameByEditGUI;
	if(FileName.isEmpty()==true)
		FileName=MacroFileName;

	QFile	FL(FileName);
	if(FL.open(QIODevice::ReadOnly)==false){
		QMessageBox::critical ( NULL
							, "Loading Error"
							, "No macro file"
							, QMessageBox::Ok);
		return;
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Execute macro");

	/*
	QString ErrorLine;
	if(SContainer.LoadFromMacro(FL,ErrorLine)==false){
		QMessageBox::critical ( NULL
							, "Loading Error"
							, ErrorLine, QMessageBox::Ok);
		GetLayersBase()->CloseProcessingForm ();
		return;
	}
	int	Row=0;
	for(MacroSentenseBase *a=SContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		bool ExeReturn;
		a->ExecuteLine(GetLayersBase(),ExeReturn);
		for(int i=0;i<10;i++){
			QCoreApplication::processEvents();
		}
	}
	*/
	BatchData.LoadText(&FL);

	for(BatchLine *L=BatchData.GetFirst();L!=NULL;L=L->GetNext()){
		bool ExeReturn=L->ExecuteLine(GetLayersBase());
		for(int i=0;i<10;i++){
			QCoreApplication::processEvents();
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	BroadcastDirectly(_BC_BuildForShow	,0);
}

void	ButtonExecuteMacro::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
									,"Execute"
									,"Execute macro"
									,this);
	p->SetMenuNumber(1055);
	Info.AppendList(p);
}
void	ButtonExecuteMacro::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
