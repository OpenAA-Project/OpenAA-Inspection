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

#include "ButtonTransferRequireGlobalParamResource.h"

#include "ButtonTransferRequireGlobalParam.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"
#include "XParamGlobal.h"
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "EditTransferHostDialog.h"

static	const	char	*sRoot=/**/"Transfer";
static	const	char	*sName=/**/"RequireGlobalParam";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Transfer Requiring GlobalParam");
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
	return(new ButtonTransferRequireGlobalParam(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonTransferRequireGlobalParam *)Instance)->Msg;
	Data[0].Translatable		 =true;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferRequireGlobalParam.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonTransferRequireGlobalParam::ButtonTransferRequireGlobalParam(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer Req GlobalParam";
	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(RightClicked()), this ,SLOT(SlotRightClicked()));
}

void	ButtonTransferRequireGlobalParam::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferRequireGlobalParam::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferRequireGlobalParam::SlotClicked (bool checked)
{
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_0)/*"Transfering data"*/);
	ParamGlobal TmpGlobalParam(GetLayersBase());
	if(GetLayersBase()->GetMTransfer()->ReqGlobalParam(TmpGlobalParam)==true){
		QString	FileName=GetLayersBase()->LGetSaveFileName	(0
										, LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_1)/*"Save GlobalParam into file"*/
										, LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_2)/*"File name"*/
										, LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_3)/*"*.dat(*.dat)"*/);
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			TmpGlobalParam.SaveParam(&File);
		}
	}
	else{
		QMessageBox::warning(NULL
							,LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_4)/*"Error"*/
							,LangSolver.GetString(ButtonTransferRequireGlobalParam_LS,LID_5)/*"Can not reveive GlobalParam"*/);
	}
	GetLayersBase()->CloseProcessingForm ();
}
void	ButtonTransferRequireGlobalParam::SlotRightClicked()
{
	QMenu	Menu(this);
	Menu.addAction (QString(tr("Reset fixed host"))	, this, SLOT(SlotResetFixedHost()));
	Menu.addAction (QString(tr("Edit host"))		, this, SLOT(SlotEditHost()));

	QPoint Q=QCursor::pos();
	Menu.exec(Q);
}

void	ButtonTransferRequireGlobalParam::SlotResetFixedHost()
{
	GetLayersBase()->GetMTransfer()->ResetFixedHost();
}
void	ButtonTransferRequireGlobalParam::SlotEditHost()
{
	EditTransferHostDialog	D(GetLayersBase());
	D.exec();
}