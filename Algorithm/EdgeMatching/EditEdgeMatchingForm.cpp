#include "EditEdgeMatchingForm.h"
#include "ui_EditEdgeMatchingForm.h"
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"	
#include "XDataInLayerCommander.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelEdgeMatching::DisplaySimPanelEdgeMatching(LayersBase *base ,EditEdgeMatchingForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
	DividedAreaNumber=-1;
}

void	DisplaySimPanelEdgeMatching::DrawOther(QPainter &Pnt)
{
	ResultInItemRoot	*R=GetResult();
	//EdgeMatchingResultPosList	*r=dynamic_cast<EdgeMatchingResultPosList *>(R->GetPosListFirst());
	//if(r!=NULL){
	//	int	Lx1=(r->X1+MovX)*ZoomRate;
	//	int Ly1=(r->Y1+MovY)*ZoomRate;
	//	int	Lx2=(r->X2+MovX)*ZoomRate;
	//	int Ly2=(r->Y2+MovY)*ZoomRate;
	//	Pnt.setPen(Qt::yellow);
	//	Pnt.drawLine(Lx1,Ly1,Lx2,Ly2);
	//}
}

void	DisplaySimPanelEdgeMatching::GetDrawInformation(QByteArray &Something)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,DividedAreaNumber);
	Something=Buff.buffer();
}

void	DisplaySimPanelEdgeMatching::mouseMoveEvent ( QMouseEvent * e )
{
	DisplaySimPanel::mouseMoveEvent(e);
	int	px=e->x();
	int	py=e->y();
	int GlobalX	=px/ZoomRate-MovX;
	int GlobalY	=py/ZoomRate-MovY;

	int	LocalX,LocalY;
	//int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX,GlobalY,LocalX,LocalY);
}

void     DisplaySimPanelEdgeMatching::SetDividedAreaNumber(int Number)
{
	DividedAreaNumber = Number;
}
	
//======================================================================================


EditEdgeMatchingForm::EditEdgeMatchingForm(LayersBase *Base, QWidget *parent)
    : QWidget(parent)
    , ServiceForLayers(Base)
    , PasswordInQWodget(Base, this)
    ,SimPanel(Base,this,parent)
    , ui(new Ui::EditEdgeMatchingForm)
{
    ui->setupUi(this);

    OnChanging	= false;
	Preparing	=true;
    IData = NULL;

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(sRoot,sName);
	SimPanel.SetGUI(/**/"Button",/**/"PropertyEdgeMatching");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());

    InstallOperationLog(this);
}

EditEdgeMatchingForm::~EditEdgeMatchingForm()
{
    delete ui;
	Preparing=true;
}
void	EditEdgeMatchingForm::showEvent ( QShowEvent * event )
{
	Preparing=false;
	CalcFunc();
}
void EditEdgeMatchingForm::Initial(AlgorithmBase *InstBase, AlgorithmItemIndependentPack &Data)
{
    if (IData != NULL) {
        delete IData;
    }
    IData = new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
    *IData = Data;
    GlobalPage = 0;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(-1);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			EdgeMatchingItem	*BData=dynamic_cast<EdgeMatchingItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock	(ui->toolButtonSimShowItem ->isChecked());
            }
		}
	}
    ShowDataToWindow();

	CalcFunc();
}

void EditEdgeMatchingForm::GetDataFromWindow(void)
{
    for (AlgorithmItemIndependent *D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
        AlgorithmItemRoot *DA = D->Data;
        if (DA == NULL) continue;
        
        EdgeMatchingItem *BData = dynamic_cast<EdgeMatchingItem *>(DA);
        if (BData == NULL) continue;
        
        EdgeMatchingThreshold *Thr = BData->GetThresholdW(GetLayersBase());

        Thr->FocusRadius    = ui->EditFocusRadius->value();
        Thr->Layer          = ui->EditLayer->value();
        Thr->SearchDotX     = ui->EditSearchDotX->value();
        Thr->SearchDotY     = ui->EditSearchDotY->value();
        Thr->SearchByPixel  = ui->EditSearchByPixel->value();
        Thr->ThresholdDiv   = ui->EditThresholdDiv->value();
        //Thr->ThresholdDirection = ui->EditThresholdDirection->value();
        Thr->BlockSizeX     = ui->EditBlockSizeX->value();
        Thr->BlockSizeY     = ui->EditBlockSizeY->value();
		Thr->UseDivided		= ui->checkBoxUseDivided->isChecked();
    }
}

void EditEdgeMatchingForm::ShowDataToWindow(void)
{
    for (AlgorithmItemIndependent *D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
        AlgorithmItemRoot *DA = D->Data;
        if (DA != NULL) {
            EdgeMatchingItem *BData = dynamic_cast<EdgeMatchingItem *>(DA);
            if (BData != NULL) {
                const EdgeMatchingThreshold *Thr = BData->GetThresholdR(GetLayersBase());

                ui->EditFocusRadius     ->setValue(Thr->FocusRadius);
                ui->EditLayer           ->setValue(Thr->Layer);
                ui->EditSearchDotX      ->setValue(Thr->SearchDotX);
                ui->EditSearchDotY      ->setValue(Thr->SearchDotY);
                ui->EditSearchByPixel   ->setValue(Thr->SearchByPixel);
                ui->EditThresholdDiv    ->setValue(Thr->ThresholdDiv);
                //ui->EditThresholdDirection->setValue(Thr->ThresholdDirection);
                ui->EditBlockSizeX      ->setValue(Thr->BlockSizeX);
                ui->EditBlockSizeY      ->setValue(Thr->BlockSizeY);
				ui->checkBoxUseDivided	->setChecked(Thr->UseDivided);
                break;
            }
        }
    }
}

void EditEdgeMatchingForm::on_EditFocusRadius_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditLayer_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditSearchDotX_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditSearchDotY_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditSearchByPixel_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditThresholdDiv_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_EditThresholdDirection_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

void EditEdgeMatchingForm::on_pushButtonReflectOnly_clicked()
{
    GetLayersBase()->ClearAllAckFlag();
    GetLayersBase()->ShowProcessingForm("Change one point");

    GetLayersBase()->GetUndoStocker().SetNewTopic("Change one point");
    GetDataFromWindow();
    
    GUICmdSendAlgorithmItemIndependentPack Packet(IData->Base, QString("ANY"), QString("ANY"), -1, true);
    Packet.Command = SetIndependentItemDataCommand_OnlyOne;
    Packet.IData = *IData;
    
    for (int page = 0; page < GetPageNumb(); page++) {
        Packet.Send(NULL, page, 0);
    }
    
    GetLayersBase()->WaitAllAcknowledged(60 * 10);
    GetLayersBase()->CloseProcessingForm();
}

void EditEdgeMatchingForm::on_pushButtonReflectAll_clicked()
{
    GetLayersBase()->ClearAllAckFlag();
    GetLayersBase()->ShowProcessingForm("Change all points");

    GetLayersBase()->GetUndoStocker().SetNewTopic("Change all points");
    GetDataFromWindow();
    
    GUICmdSendAlgorithmItemIndependentPack Packet(IData->Base, QString("ANY"), QString("ANY"), -1, true);
    Packet.Command = SetIndependentItemDataCommand_All;
    Packet.IData = *IData;
    
    for (int page = 0; page < GetPageNumb(); page++) {
        Packet.Send(NULL, page, 0);
    }
    
    GetLayersBase()->WaitAllAcknowledged(60 * 10);
    GetLayersBase()->CloseProcessingForm();
}

void EditEdgeMatchingForm::on_pushButtonClose_clicked()
{
    close();
}
void EditEdgeMatchingForm::CalcFunc()
{
	if(Preparing==false){
		IntList LayerList;

		for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			EdgeMatchingItem	*nBData=dynamic_cast<EdgeMatchingItem *>(DA);
			if(nBData==NULL)
				continue;

			GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			PacketReq.BuildData(sRoot,sName,EdgeMatchingReqTryThresholdCommand ,EdgeMatchingSendTryThresholdCommand);
			EdgeMatchingItem	*BData=&((EdgeMatchingReqTryThreshold *)PacketReq.Data)->Threshold;
			((EdgeMatchingReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
			((EdgeMatchingReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
			((EdgeMatchingReqTryThreshold *)PacketReq.Data)->EdgeMatchingItemID	=DA->GetID();

			EdgeMatchingThreshold	*DThr=BData->GetThresholdW(GetLayersBase());
			DThr->FocusRadius	= ui->EditFocusRadius->value();
			DThr->Layer			= ui->EditLayer->value();
			DThr->SearchDotX	= ui->EditSearchDotX->value();
			DThr->SearchDotY	= ui->EditSearchDotY->value();
			DThr->SearchByPixel	= ui->EditSearchByPixel->value();
			DThr->ThresholdDiv	= ui->EditThresholdDiv->value();
			DThr->BlockSizeX	= ui->EditBlockSizeX->value();
			DThr->BlockSizeY	= ui->EditBlockSizeY->value();
			DThr->UseDivided	= ui->checkBoxUseDivided->isChecked();

			GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){
				EdgeMatchingSendTryThreshold	*R=((EdgeMatchingSendTryThreshold *)PacketSend.Data);
				ui->listWidgetCoef->clear();
				for(DoubleClass	*a=R->CoefList.GetFirst();a!=NULL;a=a->GetNext()){
					ui->listWidgetCoef->addItem(QString::number(a->GetValue()));
				}
				ui->EditResultValue->setValue(R->ResultValue);

				SimPanel.SetResult(R->Result);
				SimPanel.repaint();
				break;
			}
		}
	}
}
void EditEdgeMatchingForm::on_listWidgetCoef_itemSelectionChanged()
{
	int	Index = ui->listWidgetCoef->currentRow();
	SimPanel.SetDividedAreaNumber(Index);
	SimPanel.repaint();
}


void EditEdgeMatchingForm::on_listWidgetCoef_itemClicked(QListWidgetItem *item)
{
	on_listWidgetCoef_itemSelectionChanged();
}


void EditEdgeMatchingForm::on_checkBoxUseDivided_checkStateChanged(const Qt::CheckState &arg1)
{
	if(OnChanging==true)
		return;
	CalcFunc();
}

