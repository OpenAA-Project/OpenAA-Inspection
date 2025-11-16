#include "XLineEnhancerResource.h"
#include "ThresholdLineEnhancer.h"
#include "XLineEnhancer.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

ThresholdLineEnhancer::ThresholdLineEnhancer(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	IData=NULL;

	InstallOperationLog(this);
}

ThresholdLineEnhancer::~ThresholdLineEnhancer()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	ThresholdLineEnhancer::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();
}


void	ThresholdLineEnhancer::CreateThreshld(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,LineEnhancerReqThresholdReqCommand ,LineEnhancerReqThresholdSendCommand);
		((LineEnhancerThresholdReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((LineEnhancerThresholdReq *)PacketReq.Data)->ItemID	=DA->GetID();
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LineEnhancerThresholdSend	*ThrePoint=(LineEnhancerThresholdSend *)PacketSend.GetData();
			EmphasizeRate	=ThrePoint->EmphasizeRate;
			MaxLineWidth	=ThrePoint->MaxLineWidth;		
			StepDot			=ThrePoint->StepDot;		
			SelfSearch		=ThrePoint->SelfSearch;		

			break;
		}
	}
	ShowLibrary();
}

void	ThresholdLineEnhancer::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;
		LineEnhancerThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->EmphasizeRate	=ui.doubleSpinBoxEmphasizeRate	->value();
		Thr->MaxLineWidth	=ui.EditMaxLineWidth		->value();
		Thr->SelfSearch		=ui.EditSelfSearch			->value();
	}
}

void	ThresholdLineEnhancer::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui.EditLibID->setText(/**/"");
			ui.EditLibName->setText(/**/"");
		}
		else{
			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			ui.EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		ui.doubleSpinBoxEmphasizeRate	->setValue(BData->GetThresholdR(GetLayersBase())->EmphasizeRate);
		ui.EditMaxLineWidth				->setValue(BData->GetThresholdR(GetLayersBase())->MaxLineWidth);
		ui.EditSelfSearch				->setValue(BData->GetThresholdR(GetLayersBase())->SelfSearch);

		return;
	}
}

void ThresholdLineEnhancer::on_ButtonReflectSaveParts_clicked()
{
	GetDataFromWindow();

	LineEnhancerItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;

		int	Page=D->GlobalPage;
		GUICmdReqUpdateAlgorithmOnPiece	Req(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		Req.PieceCode=BData->GetPartsID();
		Req.DLLRoot=sRoot;
		Req.DLLName=sName;
		Req.IData=*IData;
		Req.Command=SetIndependentItemDataCommand_All;
		GUICmdAckUpdateAlgorithmOnPiece	Ack(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		if(Req.Send(Page ,0,Ack)==false)
			QMessageBox::warning (NULL, LangSolver.GetString(ThresholdLineEnhancer_LS,LID_6)/*"Error"*/, LangSolver.GetString(ThresholdLineEnhancer_LS,LID_7)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, LangSolver.GetString(ThresholdLineEnhancer_LS,LID_8)/*"Error"*/, LangSolver.GetString(ThresholdLineEnhancer_LS,LID_9)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void ThresholdLineEnhancer::on_ButtonReflectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE item threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ThresholdLineEnhancer::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL items\' threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ThresholdLineEnhancer::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			LineEnhancerThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ThresholdLineEnhancer::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			LineEnhancerThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			//ShowThreshold();
			return;
		}
	}
}

void ThresholdLineEnhancer::on_ButtonClose_clicked()
{
	close();
}

void ThresholdLineEnhancer::on_pushButtonChangeLib_clicked()
{
	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	int		RetSelectedLibID;
	QString RetSelectedLibName;
	ExeSelectLibraryForm(ABase->GetLibType(),IData->Base, this
						,RetSelectedLibID
						,RetSelectedLibName);
	if(RetSelectedLibID>=0){
		for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			LineEnhancerItem	*BData=dynamic_cast<LineEnhancerItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}