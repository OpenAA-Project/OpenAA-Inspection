#include "BCRInspectionResource.h"
#include "SetThresholdForm.h"
#include "ui_SetThresholdForm.h"
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XBCRInspection.h"
#include <QFileDialog>
#include <QFile>

extern	const	char	*sRoot;
extern	const	char	*sName;

SetThresholdForm::SetThresholdForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::SetThresholdForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	IData		=NULL;
	OnChanging	=false;

	int	W=ui->tableWidgetGradeList->width()-ui->tableWidgetGradeList->verticalHeader()->width()-40;
	ui->tableWidgetGradeList->setColumnWidth(0,W*0.5);
	ui->tableWidgetGradeList->setColumnWidth(1,W*0.5);

	ui->tableWidgetBarcodeType->setRowCount(GetBarcodeTypeTableCount());
	for(int i=0;i<GetBarcodeTypeTableCount();i++){
		QString TypeName;
		GetBarcodeTypeTable(i,TypeName);
		BarcodeTypeTableCb[i]=::SetDataToTableCheckable(ui->tableWidgetBarcodeType
														, 0, i
														,TypeName , false);
	}
	ui->tableWidgetBarcodeOrientation->setRowCount(GetBarcodeOrientationTableCount());
	for(int i=0;i<GetBarcodeOrientationTableCount();i++){	
		QString TypeName;
		GetBarcodeOrientationTable(i,TypeName);
		BarcodeOrientationTableCb[i]=::SetDataToTableCheckable(ui->tableWidgetBarcodeOrientation
																, 0, i
																,TypeName , false);
	}
	on_comboBoxCheckType_currentIndexChanged(0);

	InstallOperationLog(this);
}

SetThresholdForm::~SetThresholdForm()
{
    delete ui;
}

void	SetThresholdForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			DA->SetParentPointer(InstBase,D->PhaseCode,D->GlobalPage,D->Layer);
			BCRInspectionItem	*BData=dynamic_cast<BCRInspectionItem *>(DA);
			if(BData!=NULL){
				const	BCRInspectionThreshold	*R=BData->GetThresholdR(GetLayersBase());
				SetDataToWindow(R);
				//BData->TF_EnumHistList(HContainer);
				CalcResult();
				break;
			}
		}
	}
}

void	SetThresholdForm::SetDataToWindow(const	BCRInspectionThreshold	*R)
{
	ui->comboBoxCheckType			->setCurrentIndex(R->CheckType);
	ui->doubleSpinBoxQuilityGrade	->setValue(R->QuilityGrade);
	for(int i=0;i<GetBarcodeTypeTableCount();i++){	
		if(BarcodeTypeTableCb[i]!=NULL){
			QString TypeName;
			uint32	m=GetBarcodeTypeTable(i,TypeName);
			if((R->BarcodeType & m)==m){
				BarcodeTypeTableCb[i]->setChecked(true);
			}
			else{
				BarcodeTypeTableCb[i]->setChecked(false);
			}
		}
	}
	for(int i=0;i<GetBarcodeOrientationTableCount();i++){	
		if(BarcodeOrientationTableCb[i]!=NULL){
			QString TypeName;
			uint32	m=GetBarcodeOrientationTable(i,TypeName);
			if((R->BarcodeOrientation & m)==m){
				BarcodeOrientationTableCb[i]->setChecked(true);
			}
			else{
				BarcodeOrientationTableCb[i]->setChecked(false);
			}
		}
	}
	ui->checkBoxBarcodeIsOnlyDigit->setChecked(R->BarcodeIsOnlyDigit);
	ShowGradeList(((BCRInspectionThreshold *)R)->GradeList);
}

void	SetThresholdForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BCRInspectionItem	*BData=dynamic_cast<BCRInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		BData->GetThresholdW(GetLayersBase())->CheckType	=ui->comboBoxCheckType	->currentIndex();
		BData->GetThresholdW(GetLayersBase())->QuilityGrade	=ui->doubleSpinBoxQuilityGrade	->value();
		LoadGradeListFromWindow(BData->GetThresholdW()->GradeList);

		BData->GetThresholdW(GetLayersBase())->BarcodeType			=0;
		BData->GetThresholdW(GetLayersBase())->BarcodeOrientation	=0;

		for(int i=0;i<GetBarcodeTypeTableCount();i++){	
			bool	b=::GetCheckedFromTable(ui->tableWidgetBarcodeType, 0, i);
			if(b==true){
				QString TypeName;
				BData->GetThresholdW(GetLayersBase())->BarcodeType |=GetBarcodeTypeTable(i,TypeName);
			}
		}
		for(int i=0;i<GetBarcodeOrientationTableCount();i++){	
			bool	b=::GetCheckedFromTable(ui->tableWidgetBarcodeOrientation, 0, i);
			if(b==true){
				QString TypeName;
				BData->GetThresholdW(GetLayersBase())->BarcodeOrientation |=GetBarcodeOrientationTable(i,TypeName);
			}
		}
		BData->GetThresholdW(GetLayersBase())->BarcodeIsOnlyDigit	=ui->checkBoxBarcodeIsOnlyDigit->isChecked();
		//return;
	}
}

void SetThresholdForm::on_pushButtonSet_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SetThresholdForm_LS,LID_6)/*"Change one point"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one point");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void SetThresholdForm::on_pushButtonClose_clicked()
{
	close();
}

void    SetThresholdForm::ShowGradeList(BCRGradeListContainer &List)
{
	ui->tableWidgetGradeList->setRowCount(List.GetCount());
	int	Row=0;
	for(BCRGradeList *a=List.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetGradeList, 0, Row, a->Grade, Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetGradeList, 1, Row, QString::number(a->Quality,'f',3), Qt::ItemIsEditable);
	}
}
void    SetThresholdForm::LoadGradeListFromWindow(BCRGradeListContainer &List)
{
	List.RemoveAll();
	int	N=ui->tableWidgetGradeList->rowCount();
	for(int Row=0;Row<N;Row++){
		BCRGradeList *a=new BCRGradeList();
		a->Grade	=GetDataToTable(ui->tableWidgetGradeList, 0, Row);
		a->Quality	=GetDataToTable(ui->tableWidgetGradeList, 1, Row).toDouble();;
		List.AppendList(a);
	}
}
void SetThresholdForm::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr,LangSolver.GetString(SetThresholdForm_LS,LID_12)/*"Load BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade:dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){

			BCRGradeListContainer	List;
			if(List.Load(&File)==true){
				ShowGradeList(List);
			}
		}
	}
}

void SetThresholdForm::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(nullptr,LangSolver.GetString(SetThresholdForm_LS,LID_13)/*"Save BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade:dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){

			BCRGradeListContainer	List;
			LoadGradeListFromWindow(List);
			List.Save(&File);
		}
	}
}

void SetThresholdForm::on_pushButtonAdd_clicked()
{
	int	N=ui->tableWidgetGradeList->rowCount();
	ui->tableWidgetGradeList->setRowCount(N+1);
}

void SetThresholdForm::on_pushButtonSub_clicked()
{
	int	N=ui->tableWidgetGradeList->rowCount();
	ui->tableWidgetGradeList->setRowCount(N-1);
}

void SetThresholdForm::on_comboBoxCheckType_currentIndexChanged(int index)
{
	if(ui->comboBoxCheckType->currentIndex()==0)
		ui->stackedWidget->setCurrentIndex(0);
	else
	if(ui->comboBoxCheckType->currentIndex()==1)
		ui->stackedWidget->setCurrentIndex(1);
	else
		ui->stackedWidget->setCurrentIndex(0);
}

void    SetThresholdForm::CalcResult(void)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;

	int		                CheckType;		    //0:Read	1:Quality Check
	double	                QuilityGrade;
	BCRGradeListContainer	GradeList;
    BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
    bool					BarcodeIsOnlyDigit;

	CheckType		=ui->comboBoxCheckType	->currentIndex();
	QuilityGrade	=ui->doubleSpinBoxQuilityGrade	->value();
	BarcodeType		=0;
	BarcodeOrientation	=0;

	for(int i=0;i<GetBarcodeTypeTableCount();i++){	
		bool	b=::GetCheckedFromTable(ui->tableWidgetBarcodeType, 0, i);
		if(b==true){
			QString TypeName;
			BarcodeType |=GetBarcodeTypeTable(i,TypeName);
		}
	}
	for(int i=0;i<GetBarcodeOrientationTableCount();i++){	
		bool	b=::GetCheckedFromTable(ui->tableWidgetBarcodeOrientation, 0, i);
		if(b==true){
			QString TypeName;
			BarcodeOrientation |=GetBarcodeOrientationTable(i,TypeName);
		}
	}
	BarcodeIsOnlyDigit	=ui->checkBoxBarcodeIsOnlyDigit->isChecked();

	LoadGradeListFromWindow(GradeList);

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BCRInspectionItem	*nBData=dynamic_cast<BCRInspectionItem *>(DA);
		if(nBData==NULL)
			continue;
	
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BCRInspectionReqTryThresholdCommand ,BCRInspectionSendTryThresholdCommand);
		BCRInspectionItem	*BData=&((BCRInspectionReqTryThreshold *)PacketReq.Data)->Threshold;
		BCRInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CopyFrom(*nBData->GetThresholdW());
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->GlobalPage			=D->GlobalPage;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->BCRInspectionItemID	=DA->GetID();
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.GlobalPage		=D->GlobalPage;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.ItemID			=DA->GetID();
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.CheckType			=CheckType			;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.QuilityGrade			=QuilityGrade		;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.GradeList			=GradeList			;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.BarcodeOrientation	=BarcodeOrientation	;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.BarcodeType			=BarcodeType		;
		((BCRInspectionReqTryThreshold *)PacketReq.Data)->Data.BarcodeIsOnlyDigit	=BarcodeIsOnlyDigit	;

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){
	
			BCRInspectionSendTryThreshold	*R=((BCRInspectionSendTryThreshold *)PacketSend.Data);
	
			ui->labelResultQuality	->setText(R->ResultStr);
			ui->labelResultBarCode	->setText(R->ResultStr);
			break;
		}
	}

	OnChanging=false;
}

void SetThresholdForm::on_doubleSpinBoxQuilityGrade_valueChanged(double arg1)
{
	CalcResult();
}


void SetThresholdForm::on_checkBoxBarcodeIsOnlyDigit_clicked(bool checked)
{
	CalcResult();
}


void SetThresholdForm::on_tableWidgetBarcodeType_cellChanged(int row, int column)
{
	CalcResult();
}


void SetThresholdForm::on_tableWidgetBarcodeOrientation_cellChanged(int row, int column)
{
	CalcResult();
}


void SetThresholdForm::on_tableWidgetGradeList_cellChanged(int row, int column)
{
	CalcResult();
}

