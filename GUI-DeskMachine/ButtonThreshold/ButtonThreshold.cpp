#include "ButtonThresholdResource.h"
#include "ButtonThreshold.h"
#include "XGeneralFunc.h"
//#include "XGeneralDialog.h"
#include "ThresholdSettingForm.h"
#include "XFileRegistry.h"
#include "PasswordForm.h"
#include "ShowThresholdFileNamePacket.h"
#include "ChoicePhaseDialog.h"



char	*sRoot=/**/"Button";
char	*sName=/**/"ButtonThreshold";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button Threshold");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonThreshold(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3){
		return(-1);
	}
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Password";
	Data[0].Pointer				 =&((ButtonThreshold *)Instance)->Password;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"DefaultDirectory";
	Data[1].Pointer				 =&((ButtonThreshold *)Instance)->DefaultDirectory;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"AutoSelectFile";
	Data[2].Pointer				 =&((ButtonThreshold *)Instance)->AutoSelectFile;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonThreshold.png")));
}

//=========================================================================================================

ButtonThreshold::ButtonThreshold(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//言語対応
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/ThresholdImage.bmp",	//日本語
		/**/":Resources/ThresholdImage-en.bmp",	//English
		/**/":Resources/ThresholdImage-en.bmp",	//簡体中文
		/**/":Resources/ThresholdImage-en.bmp",	//繁体中文
		/**/":Resources/ThresholdImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonThreshold");
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked()),this,SLOT(SlotClicked()));
	connect(this,	SIGNAL(SignalResize()),	this,SLOT(ResizeAction()));
///	GetParamGUI()->SetParam(&LoadGUIFile, /**/"ButtonThreshold",/**/"LoadGUIFile","True if loading last ID"		);

	//Initial
	AutoSelectFile=false;
}

void	ButtonThreshold::Prepare(void)
{
	ResizeAction();
}
void	ButtonThreshold::ResizeAction()
{
	Button.resize(width(),height());
}

bool ButtonThreshold::CheckInspectionLevel(int Level)
{
	if(wInspectionLevel!=Level){
		return false;
	}
	return true;
}

void ButtonThreshold::ExecCmdShowThresholdFileName()
{
	GUIFormBase	*pShowThresholdFileNameBase=GetLayersBase()->FindByName(/**/"Panel",/**/"ShowThresholdFileName" ,/**/"");
	if(pShowThresholdFileNameBase!=NULL){
		CmdShowThresholdFileName	CmdShowThresholdFile(GetLayersBase());
		CmdShowThresholdFile.ThresholdFileName=LoadParamFilePath.split(/**/"/").last().remove(/**/".dat");
		pShowThresholdFileNameBase->TransmitDirectly(&CmdShowThresholdFile);
	}
}

void ButtonThreshold::SlotClicked()
{
	//Password
	if(Password.trimmed().isEmpty()==false){
		PasswordForm PForm(Password.trimmed());
		if(PForm.exec()==false){
			return;
		}
	}

	PixelInspectionBase	*PBase=(PixelInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	if(PBase->GetPhaseNumb()>1){
		ChosenPhase *chosenPhase = new ChosenPhase(PBase->GetLayersBase()->GetCurrentPhase());
		for(;;){
			ChoicePhaseDialog ChoicePhase(chosenPhase,PBase->GetLayersBase());
			ChoicePhase.exec();
			if(ChoicePhase.isQuit())
				break;
			Execute(PBase,chosenPhase);
		}
		PBase->GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
	}
	else
		Execute(PBase);
}

void	ButtonThreshold::Execute(PixelInspectionBase *PBase){
	ThresholdSettingForm	ThresholdSetting(this,this,PBase);
	FlgLoadParamFilePath=false;
	if(ThresholdSetting.exec()==false){
		if(FlgLoadParamFilePath==true){
			LoadParamFilePath.clear();
			ExecCmdShowThresholdFileName();
			FlgLoadParamFilePath=false;
		}
		return;
	}

	int Level=ThresholdSetting.GetInspectionLevel();

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

	//パラメータに保存
	GetLayersBase()->WriteAllSettingFiles();

	//CmdShowThresholdFileName
	if(CheckInspectionLevel(Level)==false){
		LoadParamFilePath.clear();
		ExecCmdShowThresholdFileName();
	}
	if(FlgLoadParamFilePath==true){
		FlgLoadParamFilePath=false;
	}
}

void	ButtonThreshold::Execute(PixelInspectionBase *PBase,ChosenPhase *chosenPhase){
	ThresholdSettingForm	ThresholdSetting(this,this,PBase,chosenPhase);
	FlgLoadParamFilePath=false;
	if(ThresholdSetting.exec()==false){
		if(FlgLoadParamFilePath==true){
			LoadParamFilePath.clear();
			ExecCmdShowThresholdFileName();
			FlgLoadParamFilePath=false;
		}
		return;
	}

	int Level=ThresholdSetting.GetInspectionLevel();

	PBase->GetLayersBase()->TF_SetCurrentScanPhaseNumber(chosenPhase->getPhaseNumber());

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

	//パラメータに保存
	GetLayersBase()->WriteAllSettingFiles();

	//CmdShowThresholdFileName
	if(CheckInspectionLevel(Level)==false){
		LoadParamFilePath.clear();
		ExecCmdShowThresholdFileName();
	}
	if(FlgLoadParamFilePath==true){
		FlgLoadParamFilePath=false;
	}
}