#include "EasyPropertyDotColorMatchResource.h"
#include "EasyPropertyDotColorMatchForm.h"
#include "ui_EasyPropertyDotColorMatchForm.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XPropertyMaskingPacket.h"
#include "PropertyAlignmentLargePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EasyPropertyDotColorMatchForm::EasyPropertyDotColorMatchForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertyDotColorMatchForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo	=0;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

EasyPropertyDotColorMatchForm::~EasyPropertyDotColorMatchForm()
{
    delete ui;
}

void	EasyPropertyDotColorMatchForm::ResizeAction()
{
}

void	EasyPropertyDotColorMatchForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdDotColorMatchingSetLevel	*CmdDotColorMatchingSetLevelVar=dynamic_cast<CmdDotColorMatchingSetLevel *>(packet);
	if(CmdDotColorMatchingSetLevelVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetLevel	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.Level	=CmdDotColorMatchingSetLevelVar->Level;
			Cmd.Type	=CmdDotColorMatchingSetLevelVar->Type;
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
	IntegrationGenerateAutomatically	*IntegrationGenerateAutomaticallyVar=dynamic_cast<IntegrationGenerateAutomatically *>(packet);
	if(IntegrationGenerateAutomaticallyVar!=NULL){
		GenerateAutomatically();
		GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
		return;
	}
	IntegrationAutoGeneration	*IntegrationAutoGenerationVar=dynamic_cast<IntegrationAutoGeneration *>(packet);
	if(IntegrationAutoGenerationVar!=NULL){
		on_toolButtonAutoGenerate_clicked();
		return;
	}
}

void EasyPropertyDotColorMatchForm::on_toolButtonAutoGenerate_clicked()
{
	GenerateAutomatically();
	GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
	emit	SignalBusy();

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();
	RepaintAll();
}

void	EasyPropertyDotColorMatchForm::GenerateAutomatically(void)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		IntegrationCmdGenerate	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(SlaveNo==0){
			if(GProp->ParamInMaster.Slave0LibID.GetCount()!=0)
				RCmd.GeneratedLibs.Merge(GProp->ParamInMaster.Slave0LibID);
			else{
				if(GProp->Param.DotColorMatchLibPattern1!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibPattern1);
				if(GProp->Param.DotColorMatchLibPattern2!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibPattern2);
				if(GProp->Param.DotColorMatchLibPattern3!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibPattern3);
				if(GProp->Param.DotColorMatchLibPattern4!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibPattern4);
			}
		}
		else if(SlaveNo==1){
			if(GProp->ParamInMaster.Slave1LibID.GetCount()!=0)
				RCmd.GeneratedLibs.Merge(GProp->ParamInMaster.Slave1LibID);
			else{
				if(GProp->Param.DotColorMatchLibFlat1!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibFlat1);
				if(GProp->Param.DotColorMatchLibFlat2!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibFlat2);
				if(GProp->Param.DotColorMatchLibFlat3!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibFlat3);
				if(GProp->Param.DotColorMatchLibFlat4!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchLibFlat4);
			}
		}
		else if (SlaveNo == 2) {
			if(GProp->ParamInMaster.Slave2LibID.GetCount()!=0)
				RCmd.GeneratedLibs.Merge(GProp->ParamInMaster.Slave2LibID);
			else{
				if(GProp->Param.DotColorMatchMonoInspection1!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchMonoInspection1);
				if(GProp->Param.DotColorMatchMonoInspection2!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchMonoInspection2);
				if(GProp->Param.DotColorMatchMonoInspection3!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchMonoInspection3);
				if(GProp->Param.DotColorMatchMonoInspection4!=0)
					RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchMonoInspection4);
			}
		}
		if((SlaveNo==0 && GProp->Param.GenerateBradeTop==true)
		|| (SlaveNo==1 && GProp->Param.GenerateBradeBottom==true)){
			if(GProp->Param.DotColorMatchBladeLib1>0)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchBladeLib1);
			if(GProp->Param.DotColorMatchBladeLib2>0)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchBladeLib2);
		}

		IntegrationCmdReqLimitedMask	RMCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationCmdAckLimitedMask	AMCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(RMCmd.Send(SlaveNo,0,AMCmd)==true){
			RCmd.GeneratedLibs.Merge(AMCmd.LimitedLib);
			/*
			if(AMCmd.LimitedLib.IsInclude(GProp->Param.DotColorMatchCADLib1)==true)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchCADLib1);
			if(AMCmd.LimitedLib.IsInclude(GProp->Param.DotColorMatchCADLib2)==true)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchCADLib2);
			if(AMCmd.LimitedLib.IsInclude(GProp->Param.DotColorMatchCADLib3)==true)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchCADLib3);
			if(AMCmd.LimitedLib.IsInclude(GProp->Param.DotColorMatchCADLib4)==true)
				RCmd.GeneratedLibs.Add(GProp->Param.DotColorMatchCADLib4);
			*/
		}

		RCmd.Send(NULL,SlaveNo,0);
	}
}


void EasyPropertyDotColorMatchForm::on_toolButtonDeleteAll_clicked()
{
	IntegrationDeleteAll	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.Send(NULL,SlaveNo,0);
	GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
	RepaintAll();
}

//============================================================================
IntegrationCmdGenerate::IntegrationCmdGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdGenerate::Load(QIODevice *f)
{
	if(GeneratedLibs.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdGenerate::Save(QIODevice *f)
{
	if(GeneratedLibs.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdGenerate::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*g=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	if(g!=NULL){
		CmdClickAreaButton	RCmd(GetLayersBase());
		g->TransmitDirectly(&RCmd);
	}
		
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDotColorMatching",/**/"");
	if(f!=NULL){
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"ClearLibList", Args, ExeReturn);
		}
		for(IntClass *a=GeneratedLibs.GetFirst();a!=NULL;a=a->GetNext()){
			QStringList Args;
			bool ExeReturn;
			Args.append(QString::number(a->GetValue()));
			f->ExecuteMacro(/**/"SetLib", Args, ExeReturn);
		}
		if(GeneratedLibs.GetCount()>0){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"Generate", Args, ExeReturn);
		}
	}
}

//============================================================================
IntegrationDeleteAll::IntegrationDeleteAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationDeleteAll::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"DotColorMatchingImagePanel",/**/"");
	if(f!=NULL){
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"SelectAllItems", Args, ExeReturn);
		}
		{
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"DeleteItems", Args, ExeReturn);
		}
	}
}

//============================================================================
GUICmdSetLevel::GUICmdSetLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Level=5;
}

bool	GUICmdSetLevel::Load(QIODevice *f)
{
	if(::Load(f,Level)==false)
		return false;
	if(::Load(f,Type)==false)
		return false;
	return true;
}
bool	GUICmdSetLevel::Save(QIODevice *f)
{
	if(::Save(f,Level)==false)
		return false;
	if(::Save(f,Type)==false)
		return false;
	return true;
}

void	GUICmdSetLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			CmdDotColorMatchingSetLevel	Cmd(GetLayersBase());
			Cmd.Level=Level;
			Cmd.Type=Type;
			Ap->TransmitDirectly(&Cmd);
		}
	}
}

//============================================================================
IntegrationCmdReqLimitedMask::IntegrationCmdReqLimitedMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdReqLimitedMask::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckLimitedMask	*SendBack=GetSendBackIntegration(IntegrationCmdAckLimitedMask,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyMaskingForm",/**/"");
	if(f!=NULL){
		CmdReqLimitedLibMask	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		SendBack->LimitedLib=RCmd.LimitedLib;
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}
IntegrationCmdAckLimitedMask::IntegrationCmdAckLimitedMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckLimitedMask::Load(QIODevice *f)
{
	if(LimitedLib.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAckLimitedMask::Save(QIODevice *f)
{
	if(LimitedLib.Save(f)==false)	return false;
	return true;
}
void EasyPropertyDotColorMatchForm::on_toolButtonShrinkOutline_clicked()
{

}

