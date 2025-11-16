#include "ButtonStartLearningResource.h"
#include "StartLearningForm.h"
#include "XGeneralFunc.h"
#include <QProgressBar>


extern	const	char	*sRoot;
extern	const	char	*sName;

StartLearningForm::StartLearningForm(LayersBase *base,QWidget *parent)
	: GUIFormBase(base,parent)
{
	ui.setupUi(this);
}

StartLearningForm::~StartLearningForm()
{

}


void StartLearningForm::on_pushButtonStart_clicked()
{
	int	LoopCount=10;
	ui.progressBar->setMaximum(PWAFilesName.count()*LoopCount);

	for(int page=0;page<GetPageNumb();page++){
		GUICmdLearningExeTop	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.Send(NULL,page,0);
	}

	LearningLeafForSaveContainer	*GData=new LearningLeafForSaveContainer[GetPageNumb()];

	for(int Loop=0;Loop<LoopCount;Loop++){
		for(int i=0;i<PWAFilesName.count();i++){
			ui.progressBar->setValue(i);
			QString	FileName=PWAFilesName[i];
			QFile	FL(FileName);
			double	ResultValue=0;
			GetLayersBase()->LoadPixWithAlgorithm(&FL);

			for(int page=0;page<GetPageNumb();page++){
				GUICmdLearningSetData	RCmd(GetLayersBase(),sRoot,sName ,page);
				if(GData[page].GetNumber()!=0){
					RCmd.Data=GData[page];
					RCmd.Send(NULL,page,0);
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				GUICmdLearningExeLoopTop	RCmd(GetLayersBase(),sRoot,sName ,page);
				RCmd.Send(NULL,page,0);
			}
			if(FL.open(QIODevice::ReadOnly)==true){
				for(int page=0;page<GetPageNumb();page++){
					GUICmdLearningReqStartOne	RCmd(GetLayersBase(),sRoot,sName ,page);
					GUICmdLearningAckStartOne	ACmd(GetLayersBase(),sRoot,sName ,page);
					RCmd.Send(page,0,ACmd);
					ResultValue +=ACmd.ResultValueInPage;
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				GUICmdLearningExeLoopNext	RCmd(GetLayersBase(),sRoot,sName ,page);
				RCmd.ResultValueInPage=ResultValue;
				RCmd.Send(NULL,page,0);
			}
			for(int page=0;page<GetPageNumb();page++){
				GUICmdLearningReqData	RCmd(GetLayersBase(),sRoot,sName ,page);
				GUICmdLearningAckData	ACmd(GetLayersBase(),sRoot,sName ,page);
				RCmd.Send(page,0,ACmd);
				GData[page]=ACmd.Data;
			}
		}
	}

	/*
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase("Basic" ,"Learning");
	if(L==NULL)
		return;
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqStartLearning	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.MasterCode		=GetLayersBase()->GetMasterCode();
		RCmd.LotAutoCount	=GetLayersBase()->GetLotAutoCount();
		RCmd.Send(NULL,page,0);
	}
	*/
	delete	[]GData;
}

void StartLearningForm::on_pushButton_clicked()
{
	QStringList HFiles=GetLayersBase()->LGetOpenFileNames(this
										, LangSolver.GetString(StartLearningForm_LS,LID_0)/*"Load files"*/
										, QString()
										, /**/"Pix with Algorithms file(*.PWA)");
	if(HFiles.count()==0){
		return;
	}
	PWAFilesName=HFiles;
	ui.listWidgetFiles->addItems(PWAFilesName);
}

void StartLearningForm::on_pushButtonClear_clicked()
{
	PWAFilesName.clear();
	ui.listWidgetFiles->addItems(PWAFilesName);
}
//------------------------------------------------------------------------------------------------

GUICmdReqStartLearning::GUICmdReqStartLearning(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqStartLearning::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	return true;
}
bool	GUICmdReqStartLearning::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	return true;
}
void	GUICmdReqStartLearning::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CmdReqStartLearning	Cmd(this);
	Cmd.MasterCode=MasterCode;
	Cmd.LotAutoCount=LotAutoCount;
	PData->TransmitDirectly(&Cmd);
}


GUICmdLearningReqStartOne::GUICmdLearningReqStartOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdLearningReqStartOne::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdLearningAckStartOne	*SendBack=GetSendBack(GUICmdLearningAckStartOne,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningReqStartOne	Cmd(this);
	PData->TransmitDirectly(&Cmd);

	SendBack->ResultValueInPage=Cmd.ResultValueInPage;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdLearningAckStartOne::GUICmdLearningAckStartOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultValueInPage=0;
}

bool	GUICmdLearningAckStartOne::Load(QIODevice *f)
{
	::Load(f,ResultValueInPage);
	return true;
}
bool	GUICmdLearningAckStartOne::Save(QIODevice *f)
{
	::Load(f,ResultValueInPage);
	return true;
}
void	GUICmdLearningAckStartOne::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//----------------------------------------------------------------------

GUICmdLearningExeTop::GUICmdLearningExeTop(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdLearningExeTop::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningExeTop	Cmd(this);
	PData->TransmitDirectly(&Cmd);

	SendAck(localPage);
}


GUICmdLearningExeLoopTop::GUICmdLearningExeLoopTop(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdLearningExeLoopTop::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningExeLoopTop	Cmd(this);
	PData->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

GUICmdLearningExeLoopNext::GUICmdLearningExeLoopNext(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultValueInPage=0;
}

bool	GUICmdLearningExeLoopNext::Load(QIODevice *f)
{
	::Load(f,ResultValueInPage);
	return true;
}
bool	GUICmdLearningExeLoopNext::Save(QIODevice *f)
{
	::Save(f,ResultValueInPage);
	return true;
}

void	GUICmdLearningExeLoopNext::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningExeLoopNext	Cmd(this);
	Cmd.ResultValueInPage=ResultValueInPage;

	PData->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//----------------------------------------------------------------------

GUICmdLearningReqData::GUICmdLearningReqData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdLearningReqData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdLearningAckData	*SendBack=GetSendBack(GUICmdLearningAckData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	GetLayersBase()->GetLearningRegData()->Save(SendBack->Data);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdLearningAckData::GUICmdLearningAckData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLearningAckData::Load(QIODevice *f)
{
	if(Data.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdLearningAckData::Save(QIODevice *f)
{
	if(Data.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdLearningAckData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdLearningSetData::GUICmdLearningSetData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLearningSetData::Load(QIODevice *f)
{
	if(Data.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdLearningSetData::Save(QIODevice *f)
{
	if(Data.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdLearningSetData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetLearningRegData()->Load(Data);

	SendAck(localPage);
}

