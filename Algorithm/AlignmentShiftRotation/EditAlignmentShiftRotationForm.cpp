#include "EditAlignmentShiftRotationForm.h"
#include "ui_EditAlignmentShiftRotationForm.h"
#include "XAlignmentShiftRotation.h"
#include "XDataInLayerCommander.h"
#include "swap.h"

EditAlignmentShiftRotationForm::EditAlignmentShiftRotationForm(LayersBase *Base,QWidget *parent)
    : QWidget(parent)
    ,ServiceForLayers(Base),PasswordInQWodget(Base,this)
    , ui(new Ui::EditAlignmentShiftRotationForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);

	OnChanging=false;
	IData=NULL;

	InstallOperationLog(this);
}

EditAlignmentShiftRotationForm::~EditAlignmentShiftRotationForm()
{
    delete ui;
}

void	EditAlignmentShiftRotationForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	GlobalPage=0;

	ShowDataToWindow();
}

void	EditAlignmentShiftRotationForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentShiftRotationItem	*BData=dynamic_cast<AlignmentShiftRotationItem *>(DA);
		if(BData==NULL)
			continue;
		AlignmentShiftRotationThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->Threshold		=ui->EditThreshold	->value();
		Thr->LineCount		=ui->EditLineCount	->value();
		Thr->TargetLayer	=ui->EditTargetLayer->value();
		Thr->LineLen		=ui->EditLineLen	->value();
		Thr->SearchDotX		=ui->EditSearchDotX	->value();
		Thr->SearchDotY		=ui->EditSearchDotY	->value();
		Thr->SparseAngle	=ui->EditSparseAngle->value();
		Thr->Rotation		=Rotation;
		//return;
	}
}
void	EditAlignmentShiftRotationForm::ShowDataToWindow(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AlignmentShiftRotationItem	*BData=dynamic_cast<AlignmentShiftRotationItem *>(DA);
			if(BData!=NULL){
				const	AlignmentShiftRotationThreshold	*Thr=BData->GetThresholdR(GetLayersBase());

				ui->EditThreshold	->setValue(Thr->Threshold	);
				ui->EditLineCount	->setValue(Thr->LineCount	);
				ui->EditTargetLayer	->setValue(Thr->TargetLayer	);
				ui->EditLineLen		->setValue(Thr->LineLen		);
				ui->EditSearchDotX	->setValue(Thr->SearchDotX	);
				ui->EditSearchDotY	->setValue(Thr->SearchDotY	);
				ui->EditSparseAngle	->setValue(Thr->SparseAngle	);

				Rotation=BData->GetThresholdR(GetLayersBase())->Rotation;
				int	row = 0;
				ui->tableWidgetAngleList->setRowCount(Rotation.GetCount());
				for(RotationRange *r=Rotation.GetFirst();r!=NULL;r=r->GetNext(),row++){
					::SetDataToTable(ui->tableWidgetAngleList, 0, row, QString::number(r->MinAngleDegree,'f',2));
					::SetDataToTable(ui->tableWidgetAngleList, 1, row, QString::number(r->MaxAngleDegree,'f',2));
				}

				if(BData->GetLibID()<0){
					ui->EditLibID->setValue(0);
					ui->EditLibName->setText(/**/"");
				}
				else{
					ui->EditLibID	->setValue(BData->GetLibID());
					QString LibName = GetLayersBase()->GetLibraryName(DefLibTypeAlignmentShiftRotation,BData->GetLibID());
					ui->EditLibName->setText(LibName);
				}

				ui->listWidgetAngleImage->clear();
				for(AlignmentShiftRotationItem::VHLines *L=BData->VHLinesRotation.GetFirst();L!=NULL;L=L->GetNext()){
					ui->listWidgetAngleImage->addItem(QString::number(L->AngleRadian*180.0/M_PI,'f',3));
				}

				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
}

void EditAlignmentShiftRotationForm::on_pushButtonAddAngle_clicked()
{

}


void EditAlignmentShiftRotationForm::on_pushButtonSubAngle_clicked()
{

}


void EditAlignmentShiftRotationForm::on_tableWidgetAngleList_cellDoubleClicked(int row, int column)
{

}


void EditAlignmentShiftRotationForm::on_pushButtonReflectOnly_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change one point");

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


void EditAlignmentShiftRotationForm::on_pushButtonReflectAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change all points");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all points");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}


void EditAlignmentShiftRotationForm::on_pushButtonClose_clicked()
{
	close();
}


void EditAlignmentShiftRotationForm::on_listWidgetAngleImage_itemSelectionChanged()
{
	int	Index=ui->listWidgetAngleImage->currentRow();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AlignmentShiftRotationItem	*BData=dynamic_cast<AlignmentShiftRotationItem *>(DA);
			if(BData!=NULL){
				AlignmentShiftRotationItem::VHLines *L=BData->VHLinesRotation[Index];
				if(L!=NULL){
					int	x1=L->Image.GetMinX();
					int y1=L->Image.GetMinY();
					int W=L->Image.GetWidth();
					int H=L->Image.GetHeight();
					QImage	Img(W,H,QImage::Format_RGB32);
					Img.fill(Qt::black);
					L->Image.DrawImage(-x1,-y1,&Img
										,1.0,0,0
										,true ,true,true);
					int	Dx=L->Image.GetMinX();
					int	Dy=L->Image.GetMinY();
					L->Draw(Img, -Dx,-Dy,1.0);

					double	Zx=ui->labelAngleImage->width() /((double)W);
					double	Zy=ui->labelAngleImage->height()/((double)H);
					double	Z=min(Zx,Zy);
					QPixmap	PMap=QPixmap::fromImage(Img);
					ui->labelAngleImage->setPixmap(PMap.scaled(QSize(W*Z,H*Z)));
				}
			}
		}
	}
}

