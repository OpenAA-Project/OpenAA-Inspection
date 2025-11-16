#include "CheckShiftMarkForm.h"
#include "ui_CheckShiftMarkForm.h"
#include "XShiftMark.h"
#include "XShiftMarkLibrary.h"
#include "XDataInLayerCommander.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XShiftMarkAlgoPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CheckShiftMarkForm::CheckShiftMarkForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
    ,ui(new Ui::CheckShiftMarkForm)
{
    ui->setupUi(this);
    IData=NULL;
	EnableCalc	=true;
    InstallOperationLog(this);
}

CheckShiftMarkForm::~CheckShiftMarkForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	
    delete ui;
}

void	CheckShiftMarkForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	ShowThreshold();
	Calc();
}

void	CheckShiftMarkForm::ShowThreshold(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			{
				ShiftMarkItem	*BData=dynamic_cast<ShiftMarkItem *>(DA);
				if(BData!=NULL){
					EnableCalc=false;
					const	ShiftMarkThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
					ui->EditSearchDotEdge		->setValue(RThr->SearchDotEdge);
					ui->EditSearchDotMarkMin	->setValue(RThr->SearchDotMarkMin);
					ui->EditSearchDotMarkMax	->setValue(RThr->SearchDotMarkMax);
					ui->checkBoxNGByLosingMark	->setChecked(RThr->NGByLosingMark);
					ui->EditThresholdLost		->setValue(RThr->ThresholdLost);
					ui->checkBoxEnableMark		->setChecked(RThr->EnableMark);
					ui->checkBoxColorMatch		->setChecked(RThr->ColorMatch);
					EnableCalc=true;
				}
			}
		}
	}
}

void CheckShiftMarkForm::on_EditSearchDotEdge_valueChanged(int arg1)
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_EditSearchDotMark_valueChanged(int arg1)
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_checkBoxNGByLosingMark_clicked()
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_EditThresholdLost_valueChanged(int arg1)
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_checkBoxEnableMark_clicked()
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_checkBoxColorMatch_clicked()
{
	if(EnableCalc==true){
		Calc();
	}
}

void CheckShiftMarkForm::on_EditSearchDotMarkMin_valueChanged(int arg1)
{
	if(EnableCalc==true){
		Calc();
	}
}


void CheckShiftMarkForm::on_EditSearchDotMarkMax_valueChanged(int arg1)
{
	if(EnableCalc==true){
		Calc();
	}
}



void CheckShiftMarkForm::on_ButtonReflectOnlyShiftMark_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE mark threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one mark threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndepenShiftMarkItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}


void CheckShiftMarkForm::on_ButtonReflectAllShiftMark_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL marks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all marks threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndepenShiftMarkItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}


void CheckShiftMarkForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ShiftMarkItem	*BData=dynamic_cast<ShiftMarkItem *>(DA);
		if(BData==NULL)
			continue;
		GetDataFromWindow();
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			ShiftMarkLibrary	*ALib=dynamic_cast<ShiftMarkLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			ShiftMarkThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);

			ALib->SearchDotEdge		=BData->GetThresholdR(GetLayersBase())->SearchDotEdge	;
			ALib->SearchDotMarkMin	=BData->GetThresholdR(GetLayersBase())->SearchDotMarkMin	;
			ALib->SearchDotMarkMax	=BData->GetThresholdR(GetLayersBase())->SearchDotMarkMax	;
			ALib->NGByLosingMark	=BData->GetThresholdR(GetLayersBase())->NGByLosingMark	;
			ALib->ThresholdLost		=BData->GetThresholdR(GetLayersBase())->ThresholdLost	;	
			ALib->EnableMark		=BData->GetThresholdR(GetLayersBase())->EnableMark	;
			ALib->ColorMatch		=BData->GetThresholdR(GetLayersBase())->ColorMatch	;

			Container->Update(DestLib);
			return;
		}
	}
}


void CheckShiftMarkForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ShiftMarkItem	*BData=dynamic_cast<ShiftMarkItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			ShiftMarkLibrary	*ALib=dynamic_cast<ShiftMarkLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			ShiftMarkThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			return;
		}
	}
}

void CheckShiftMarkForm::on_ButtonClose_clicked()
{
	close();
}


void	CheckShiftMarkForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			{
				ShiftMarkItem	*BData=dynamic_cast<ShiftMarkItem *>(DA);
				if(BData!=NULL){
					ShiftMarkThreshold	*Thr=BData->GetThresholdW(GetLayersBase());


					Thr->SearchDotEdge		=ui->EditSearchDotEdge	->value();
					Thr->SearchDotMarkMin	=ui->EditSearchDotMarkMin	->value();
					Thr->SearchDotMarkMax	=ui->EditSearchDotMarkMax	->value();
					Thr->NGByLosingMark		=ui->checkBoxNGByLosingMark	->isChecked();
					Thr->ThresholdLost		=ui->EditThresholdLost	->value();
					Thr->EnableMark			=ui->checkBoxEnableMark		->isChecked();
					Thr->ColorMatch			=ui->checkBoxColorMatch		->isChecked();
				}
			}
		}
	}
}

void	CheckShiftMarkForm::Calc(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		{
			ShiftMarkItem	*nBData=dynamic_cast<ShiftMarkItem *>(DA);
			if(nBData!=NULL){

				GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				PacketReq.BuildData(sRoot,sName,ShiftMarkReqTryThresholdCommand ,ShiftMarkSendTryThresholdCommand);
				ShiftMarkItem	*BData=&((ShiftMarkReqTryThreshold *)PacketReq.Data)->Threshold;
				((ShiftMarkReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
				((ShiftMarkReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

				ShiftMarkThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->SearchDotEdge		=ui->EditSearchDotEdge	->value();
				Thr->SearchDotMarkMin	=ui->EditSearchDotMarkMin	->value();
				Thr->SearchDotMarkMax	=ui->EditSearchDotMarkMax	->value();
				Thr->NGByLosingMark		=ui->checkBoxNGByLosingMark	->isChecked();
				Thr->ThresholdLost		=ui->EditThresholdLost	->value();
				Thr->EnableMark			=ui->checkBoxEnableMark		->isChecked();
				Thr->ColorMatch			=ui->checkBoxColorMatch		->isChecked();

				GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

					ShiftMarkSendTryThreshold	*R=((ShiftMarkSendTryThreshold *)PacketSend.Data);

					ui->labelResultShift	->setText(QString::number(R->ResultMPos ,'f',1));
					ui->labelResultMatch	->setText(QString::number(R->ResultMatchMark ,'f',3));
					ui->labelResultRotation	->setText(QString::number(R->ResultMarkAngle*360.0/(2*M_PI) ,'f',2));
					QPalette	P=ui->frameResult->palette();
					if(R->ResultOK==true){
						P.setColor(QPalette::Window,Qt::green);
					}
					else{
						P.setColor(QPalette::Window,Qt::red);
					}
					ui->frameResult->setPalette(P);
					break;
				}
			}
		}
	}
}
