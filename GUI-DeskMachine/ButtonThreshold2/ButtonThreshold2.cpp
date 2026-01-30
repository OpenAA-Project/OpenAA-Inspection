/*
 * Copyright (C) 2022
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

#include "ButtonThreshold2.h"
#include "XGeneralFunc.h"
//#include "XGeneralDialog.h"
#include "ThresholdSettingForm.h"
#include "XFileRegistry.h"
#include "PasswordForm.h"



char	*sRoot=/**/"Button";
char	*sName=/**/"ButtonThreshold2";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button Threshold2");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
///	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonThreshold2(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1){
		return(-1);
	}
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Password";
	Data[0].Pointer				 =&((ButtonThreshold2 *)Instance)->Password;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonThreshold2.png")));
}

//=========================================================================================================

ButtonThreshold2::ButtonThreshold2(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//�����Ή�
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/ThresholdImage.bmp",	//���{��
		/**/":Resources/ThresholdImage-en.bmp",	//English
		/**/":Resources/ThresholdImage-en.bmp",	//�ȑ̒���
		/**/":Resources/ThresholdImage-en.bmp",	//�ɑ̒���
		/**/":Resources/ThresholdImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked()),this,SLOT(SlotClicked()));
	connect(this,	SIGNAL(SignalResize()),	this,SLOT(ResizeAction()));

	//PixelLibrarySetting.dat�̎w��
	PixelLibSettingFileName=/**/"";
	GetParamGUI()->SetParam(&PixelLibSettingFileName, /**/"ButtonThreshold2",/**/"PixelLibSettingFileName","Pixel Library Setting File Name");
}

void	ButtonThreshold2::Prepare(void)
{
	ResizeAction();
}
void	ButtonThreshold2::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonThreshold2::SlotClicked()
{
	//Password
	if(Password.trimmed().isEmpty()==false){
		PasswordForm PForm(Password.trimmed());
		if(PForm.exec()==false){
			return;
		}
	}

	PixelInspectionBase	*PBase=(PixelInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");

	ThresholdSettingForm	ThresholdSetting(NULL,this,PBase);
/*
	int Value;
	int Level=PBase->InspectionLevel;

//	if(Level<200){
//		Value=1;
//	}
//	else if(Level<216){
//		Value=2;
//	}
//	else if(Level<232){
//		Value=3;
//	}
//	else if(Level<248){
//		Value=4;
//	}
//	else{
//		Value=5;
//	}

	if(Level<196){
		Value=1;
	}
	else if(Level<204){
		Value=2;
	}
	else if(Level<212){
		Value=3;
	}
	else if(Level<220){
		Value=4;
	}
	else if(Level<228){
		Value=5;
	}
	else if(Level<236){
		Value=6;
	}
	else if(Level<244){
		Value=7;
	}
	else if(Level<252){
		Value=8;
	}
	else{
		Value=9;
	}
*/
	//ThresholdSetting.SetInspectionLevel			(PBase->InspectionLevel);
	//ThresholdSetting.SetNGThresholdP			(PBase->NGThresholdP);
	//ThresholdSetting.SetNGThresholdR			(PBase->NGThresholdR);
	//ThresholdSetting.SetMinimumNGSizeP			(PBase->MinimumNGSizeP);
	//ThresholdSetting.SetDoneResistIns			(PBase->DoneResistIns);
	//ThresholdSetting.SetNGThresholdForResist	(PBase->NGThresholdForResist);
	//ThresholdSetting.SetMinimumNGSizeForResist	(PBase->MinimumNGSizeForResist);
	//ThresholdSetting.SetDonePadIns				(PBase->DonePadIns);
	//ThresholdSetting.SetNGThresholdForPad		(PBase->NGThresholdForPad);
	//ThresholdSetting.SetMinimumNGSizeForPad		(PBase->MinimumNGSizeForPad);

	if(ThresholdSetting.exec()==false){
		return;
	}

	int Level=ThresholdSetting.GetInspectionLevel();
/*
	if(Level==1){
		PBase->InspectionLevel=191;
	}
	else if(Level==2){
		PBase->InspectionLevel=207;
	}
	else if(Level==3){
		PBase->InspectionLevel=223;
	}
	else if(Level==4){
		PBase->InspectionLevel=239;
	}
	else{
		PBase->InspectionLevel=255;
	}
*/
	if(Level==1){
		PBase->setInspectionLevel(191);
	}
	else if(Level==2){
		PBase->setInspectionLevel(199);
	}
	else if(Level==3){
		PBase->setInspectionLevel(207);
	}
	else if(Level==4){
		PBase->setInspectionLevel(215);
	}
	else if(Level==5){
		PBase->setInspectionLevel(223);
	}
	else if(Level==6){
		PBase->setInspectionLevel(231);
	}
	else if(Level==7){
		PBase->setInspectionLevel(239);
	}
	else if(Level==8){
		PBase->setInspectionLevel(247);
	}
	else{
		PBase->setInspectionLevel(255);
	}

	//�p�����[�^�ɕۑ�
	GetLayersBase()->WriteAllSettingFiles();

	//�������l�Đݒ菈�������s
	CmdReqCalcThresholdPacket	CmdReqCalcThr(GetLayersBase());
	PBase->TransmitDirectly(&CmdReqCalcThr);
}