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


#include "ButtonAutoGenerateMeasureLineMove.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"

#include "AutoGenerateSettingDialog.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"AutoGenerateMeasureLineMove";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to generate MeasureLineMove automatically");
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
	return(new ButtonAutoGenerateMeasureLineMove(Base,parent));
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
	Data[0].Pointer				 =&((ButtonAutoGenerateMeasureLineMove *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAutoGenerateMeasureLineMove *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAutoGenerateMeasureLineMove *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAutoGenerateMeasureLineMove *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAutoGenerateMeasureLineMove.png")));
}

//==================================================================================================
ButtonAutoGenerateMeasureLineMove::ButtonAutoGenerateMeasureLineMove(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonAutoGenerateMeasureLineMove");
	Msg=/**/"Auto Gen";
	GUIInst=/**/"PropertyMeasureLineMove1";

	BladePickupRL	=200;
	BladePickupRH	=255;
	BladePickupGL	=200;
	BladePickupGH	=255;
	BladePickupBL	=200;
	BladePickupBH	=255;
	LineLib			=-1;
	DistanceLib		=-1;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&AutoGenInfo, /**/"ButtonAutoGenerateMeasureLineMove", /**/"AutoGenInfo"		
											 , "Auto generate Info"		);

	GetParamGUI()->SetParam(&BladePickupRL	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupRL"	,/**/"Pickup RL"	);
	GetParamGUI()->SetParam(&BladePickupRH	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupRH"	,/**/"Pickup RH"	);
	GetParamGUI()->SetParam(&BladePickupGL	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupGL"	,/**/"Pickup GL"	);
	GetParamGUI()->SetParam(&BladePickupGH	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupGH"	,/**/"Pickup GH"	);
	GetParamGUI()->SetParam(&BladePickupBL	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupBL"	,/**/"Pickup BL"	);
	GetParamGUI()->SetParam(&BladePickupBH	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"BladePickupBH"	,/**/"Pickup BH"	);
	GetParamGUI()->SetParam(&LineLib		, /**/"ButtonAutoGenerateMeasureLineMove",/**/"LineLib"			,/**/"Line Lib"		);
	GetParamGUI()->SetParam(&DistanceLib	, /**/"ButtonAutoGenerateMeasureLineMove",/**/"DistanceLib"		,/**/"Distance Lib"	);
		
	bool	Ret=(connect(GetParamGUI(),SIGNAL(SignalExecuteForByteArray(const QString & ,const QString & ,QByteArray &)),this,SLOT(SlotExecuteForByteArray(const QString & ,const QString & ,QByteArray &))))?true:false;
}

ButtonAutoGenerateMeasureLineMove::~ButtonAutoGenerateMeasureLineMove(void)
{
}

void	ButtonAutoGenerateMeasureLineMove::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonAutoGenerateMeasureLineMove::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonAutoGenerateMeasureLineMove::SlotClicked (bool checked)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",GUIInst);
	if(f!=NULL){
		CmdGenerateMeasure	RCmd(GetLayersBase());
		RCmd.BladePickupRL		=BladePickupRL;
		RCmd.BladePickupRH		=BladePickupRH;
		RCmd.BladePickupGL		=BladePickupGL;
		RCmd.BladePickupGH		=BladePickupGH;
		RCmd.BladePickupBL		=BladePickupBL;
		RCmd.BladePickupBH		=BladePickupBH;
		RCmd.LineLib			=LineLib;
		RCmd.DistanceLib		=DistanceLib;
		RCmd.BladeMeasureData	=BladeMeasureData;
		f->TransmitDirectly(&RCmd);
	}
}

void	ButtonAutoGenerateMeasureLineMove::SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	AutoGenerateSettingDialog	D(GetLayersBase(),BladeMeasureData);
	D.exec();
}