#include "ThresholdAreaShader.h"
#include "ui_ThresholdAreaShader.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XAreaShader.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

ThresholdAreaShader::ThresholdAreaShader(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::ThresholdAreaShader)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	IData=NULL;
	InstallOperationLog(this);
}

ThresholdAreaShader::~ThresholdAreaShader()
{
    delete ui;
}

void	ThresholdAreaShader::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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

void	ThresholdAreaShader::CreateThreshld(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,AreaShaderReqThresholdReqCommand ,AreaShaderReqThresholdSendCommand);
		((AreaShaderThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((AreaShaderThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((AreaShaderThresholdReq *)PacketReq.Data)->ItemID		=DA->GetID();
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		AreaShaderThresholdSend	*ThrePoint=(AreaShaderThresholdSend *)PacketSend.GetData();
		CellSize	=ThrePoint->CellSize;
		AdoptRate	=ThrePoint->AdoptRate;	//Ì—p—¦
		Fixed		=ThrePoint->Fixed;
		Average		=ThrePoint->Average;
		Sigma		=ThrePoint->Sigma;		//•W€•Î·

		break;
	}
	ShowLibrary();
}

void	ThresholdAreaShader::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
		if(BData==NULL)
			continue;

		AreaShaderThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CellSize	=ui->spinBoxCellSize		->value();
		Thr->AdoptRate	=ui->doubleSpinBoxAdoptRate	->value();
		Thr->Fixed		=ui->checkBoxFixed			->isChecked();
		Thr->Average	=ui->doubleSpinBoxAverage	->value();
		Thr->Sigma		=ui->doubleSpinBoxSigma		->value();
	}
}

void	ThresholdAreaShader::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
		ui->spinBoxCellSize			->setValue(BData->GetThresholdR(GetLayersBase())->CellSize);
		ui->doubleSpinBoxAdoptRate	->setValue(BData->GetThresholdR(GetLayersBase())->AdoptRate);
		ui->checkBoxFixed			->setChecked(BData->GetThresholdR(GetLayersBase())->Fixed);
		ui->doubleSpinBoxAverage	->setValue(BData->GetThresholdR(GetLayersBase())->Average);
		ui->doubleSpinBoxSigma		->setValue(BData->GetThresholdR(GetLayersBase())->Sigma);
		return;
	}
}

void ThresholdAreaShader::on_pushButtonChangeLib_clicked()
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
			AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}

void ThresholdAreaShader::on_ButtonReflectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting only area");

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

void ThresholdAreaShader::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting all areas");

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

void ThresholdAreaShader::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(DestLib.GetLibrary());
			BData->GetThresholdW()->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ThresholdAreaShader::on_ButtonLoadFromLibrary_clicked()
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		AreaShaderItem	*BData=dynamic_cast<AreaShaderItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(SrcLib.GetLibrary());
			BData->GetThresholdW()->FromLibrary(ALib);
			ShowLibrary();
			//ShowThreshold();
			return;
		}
	}
}

void ThresholdAreaShader::on_ButtonReflectSaveParts_clicked()
{
	GetDataFromWindow();

	AreaShaderItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		BData=dynamic_cast<AreaShaderItem *>(DA);
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
			QMessageBox::warning (NULL, /**/"Error", /**/"Error occurs in saving algorithm data of parts" );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, /**/"Error", /**/"Error occurs in saving algorithm data of parts" );
		}
	}
}

void ThresholdAreaShader::on_ButtonClose_clicked()
{
	close();
}
