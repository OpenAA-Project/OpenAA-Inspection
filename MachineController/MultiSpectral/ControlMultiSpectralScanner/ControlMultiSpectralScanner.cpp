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


#include "ControlMultiSpectralScanner.h"
#include "XGeneralDialog.h"
#include "ControlMultiSpectralScannerDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"MultiSpectral";
const	char	*sName=/**/"Control";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Control scanner for MultiSpectral");
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
	return(new ControlMultiSpectralScanner(Base,parent));
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
	Data[0].Pointer				 =&((ControlMultiSpectralScanner *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ControlMultiSpectralScanner *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ControlMultiSpectralScanner *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ControlMultiSpectralScanner *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ControlMultiSpectralScanner.png")));
}

//==================================================================================================
ControlMultiSpectralScanner::ControlMultiSpectralScanner(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ControlMultiSpectralScanner");
	Msg=/**/"Control Scanner";
	ioJDimL	=NULL;
	ioJDimH	=NULL;
	ioConstV=NULL;
	ioOK	=NULL;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ControlMultiSpectralScanner::~ControlMultiSpectralScanner(void)
{
}

void	ControlMultiSpectralScanner::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){

			ioJDimL	=new SignalOperandInt(this,360,"ControlMultiSpectralScanner-ioJDimL");
			ioJDimH	=new SignalOperandInt(this,361,"ControlMultiSpectralScanner-ioJDimH");
			ioConstV=new SignalOperandInt(this,362,"ControlMultiSpectralScanner-ioConstV");
			ioOK	=new SignalOperandBit(this,360,"ControlMultiSpectralScanner-ioOK");
			ioJDimL	->Set(0);
			ioJDimH	->Set(0);
			ioConstV->Set(0);
			ioOK	->Set(0);

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioJDimL	,&Error)==false){
				ioJDimL->ShowErrorMessage(Error);
				return;
			}
			if(Param->SetSpecialOperand(ioJDimH	,&Error)==false){
				ioJDimH->ShowErrorMessage(Error);
				return;
			}
			if(Param->SetSpecialOperand(ioConstV,&Error)==false){
				ioConstV->ShowErrorMessage(Error);
				return;
			}
			if(Param->SetSpecialOperand(ioOK	,&Error)==false){
				ioOK->ShowErrorMessage(Error);
				return;
			}
		}
	}

	ResizeAction();
}

void	ControlMultiSpectralScanner::ResizeAction()
{
	Button.resize(width(),height());
}

void ControlMultiSpectralScanner::SlotClicked (bool checked)
{
	ControlMultiSpectralScannerDialog	D(GetLayersBase());
	if(D.exec()==true && ioJDimL!=NULL){
		ioJDimL	->Set(D.JDim&0xFFFFFFFF);
		ioJDimH	->Set((D.JDim>>32)&0xFFFFFFFF);
		ioConstV->Set(D.ConstV);
		ioOK	->Set(1);
	}
}