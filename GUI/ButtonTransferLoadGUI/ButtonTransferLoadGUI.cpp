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

#include "ButtonTransferLoadGUIResource.h"

#include "ButtonTransferLoadGUI.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "EditTransferHostDialog.h"

static	const	char	*sRoot=/**/"Transfer";
static	const	char	*sName=/**/"LoadGUI";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Transfer Load GUI");
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
	return(new ButtonTransferLoadGUI(Base,parent));
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
	Data[0].Pointer				 =&((ButtonTransferLoadGUI *)Instance)->Msg;
	Data[0].Translatable		 =true;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferLoadGUI.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonTransferLoadGUI::ButtonTransferLoadGUI(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer load GUI";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(RightClicked()), this ,SLOT(SlotRightClicked()));
}


void	ButtonTransferLoadGUI::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferLoadGUI::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferLoadGUI::SlotClicked (bool checked)
{
	QString FileName=GetLayersBase()->LGetOpenFileName(0
									, LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_1)/*"Load GUI file and change GUI"*/
									, LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_2)/*"GUI(*.gui)"*/);
	if(FileName.isEmpty()==true)
		return;

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_3)/*"Transfering data"*/);
	if(GetLayersBase()->GetMTransfer()->ChangeGUI(FileName)==false){
		QMessageBox::warning(NULL
							,LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_4)/*"Error"*/
							,LangSolver.GetString(ButtonTransferLoadGUI_LS,LID_5)/*"Can not load GUI"*/);
	}

	GetLayersBase()->CloseProcessingForm ();
}
void	ButtonTransferLoadGUI::SlotRightClicked()
{
	QMenu	Menu(this);
	Menu.addAction (QString(tr("Reset fixed host"))	, this, SLOT(SlotResetFixedHost()));
	Menu.addAction (QString(tr("Edit host"))		, this, SLOT(SlotEditHost()));

	QPoint Q=QCursor::pos();
	Menu.exec(Q);
}

void	ButtonTransferLoadGUI::SlotResetFixedHost()
{
	GetLayersBase()->GetMTransfer()->ResetFixedHost();
}
void	ButtonTransferLoadGUI::SlotEditHost()
{
	EditTransferHostDialog	D(GetLayersBase());
	D.exec();
}