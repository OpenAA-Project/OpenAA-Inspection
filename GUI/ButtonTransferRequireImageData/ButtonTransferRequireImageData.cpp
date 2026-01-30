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


#include "ButtonTransferRequireImageData.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "EditTransferHostDialog.h"

static	const	char	*sRoot=/**/"Transfer";
static	const	char	*sName=/**/"RequireImageData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Transfer Requiring Image");
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
	return(new ButtonTransferRequireImageData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonTransferRequireImageData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"SrcMasterImage";
	Data[1].Pointer				 =&((ButtonTransferRequireImageData *)Instance)->SrcMasterImage;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"DstMasterImage";
	Data[2].Pointer				 =&((ButtonTransferRequireImageData *)Instance)->DstMasterImage;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ChangeXY";
	Data[3].Pointer				 =&((ButtonTransferRequireImageData *)Instance)->ChangeXY;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferRequireImageData.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonTransferRequireImageData::ButtonTransferRequireImageData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SrcMasterImage	=false;
	DstMasterImage	=false;
	ChangeXY		=true;

	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer Req image";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(RightClicked()), this ,SLOT(SlotRightClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonTransferRequireImageData::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferRequireImageData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferRequireImageData::SlotClicked (bool checked)
{
	GetLayersBase()->ShowProcessingForm ("Transfering image data");
	if(GetLayersBase()->GetMTransfer()->ReqImageData(SrcMasterImage,DstMasterImage,ChangeXY)==false){
		QMessageBox::warning(NULL
							,"Error"
							,"Can not receive Master image");
	}

	GetLayersBase()->CloseProcessingForm ();
}
void	ButtonTransferRequireImageData::SlotRightClicked()
{
	QMenu	Menu(this);
	Menu.addAction (QString(tr("Reset fixed host"))	, this, SLOT(SlotResetFixedHost()));
	Menu.addAction (QString(tr("Edit host"))		, this, SLOT(SlotEditHost()));

	QPoint Q=QCursor::pos();
	Menu.exec(Q);
}

void	ButtonTransferRequireImageData::SlotResetFixedHost()
{
	GetLayersBase()->GetMTransfer()->ResetFixedHost();
}
void	ButtonTransferRequireImageData::SlotEditHost()
{
	EditTransferHostDialog	D(GetLayersBase());
	D.exec();
}