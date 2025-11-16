#include "ButtonShowConfirmResource.h"
#include "ConfirmForm.h"
#include "ui_ConfirmForm.h"
#include "XDisplayImage.h"
#include "swap.h"
#include "XIntegrationBase.h"
#include "ButtonShowConfirm.h"
#include "XConfirmPacket.h"
#include "XCriticalFunc.h"

#include "XAlignmentLargeLibrary.h"
#include "XBCRInspectionLibrary.h"
#include "XColorDifferenceLibrary.h"
#include "XDotColorMatchingLibrary.h"
#include "XMeasureLineMoveLibrary.h"

#include "ConfirmPropAlignmentForm.h"
#include "ConfirmPropBCRInspectionForm.h"
#include "ConfirmPropColorDifferenceForm.h"
#include "ConfirmPropDotColorMatchingForm.h"
#include "ConfirmPropMeasureLineMoveForm.h"
#include "ImageBank.h"
#include "ConfirmItemListForm.h"
#include "XPacketAlignmentLarge.h"
#include "XPropertyDotColorMatchingPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ConfirmForm::ConfirmForm(LayersBase *Base ,ButtonShowConfirm *p,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,Parent(p),
    ui(new Ui::ConfirmForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::WindowTitleHint);

	OnChanging=false;
	ReEntrant	=false;
	ImagePanel.SetMode(mtFrameDraw::fdRectangle);
	ImagePanel.SetFrameColor(Qt::red);

	ImagePanel.setParent(ui->frameImagePanel);
	ImagePanel.setGeometry(0,0,ui->frameImagePanel->width(),ui->frameImagePanel->height());
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
		int		x1,y1,x2,y2;
		if(m->GetXY(x1,y1,x2,y2)==true){
			ImagePanel.SetAreaSize(x2,y2);
		}
	}

	bool	ErrorOccurs=false;
	if(!connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(CanvasSlotDrawEnd(void)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(CanvasSlotOnPaint(QPainter &)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseMove(int,int)),this,SLOT(SlotMouseMove(int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseWheel(int,int,int)),this,SLOT(SlotMouseWheel(int,int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseLDownWithShift(int,int)),this,SLOT(SlotMouseLDownWithShift(int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseLDown(int,int)),this,SLOT(SlotMouseLDown(int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseRDown(int,int)),this,SLOT(SlotMouseRDown(int,int)))){
		ErrorOccurs=true;
	}

	::SetColumnWidthInTable(ui->tableWidgetResult,0,7);
	::SetColumnWidthInTable(ui->tableWidgetResult,1,28);
	::SetColumnWidthInTable(ui->tableWidgetResult,2,30);
	::SetColumnWidthInTable(ui->tableWidgetResult,3,35);

	AlgoList[0]		=new ConfirmPropAlignmentForm(this);
	AlgoList[1]		=new ConfirmPropDotColorMatchingForm(this);
	AlgoList[2]		=new ConfirmPropMeasureLineMoveForm(this);
	AlgoList[3]		=new ConfirmPropColorDifferenceForm(this);
	AlgoList[4]		=new ConfirmPropBCRInspectionForm(this);
	
	int	W=(ui->frameAlgo->width()-4)/(sizeof(AlgoList)/sizeof(AlgoList[0]));
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		AlgoList[i]->GetPropertyWidget()->setParent(ui->stackedWidgetProperty->widget(i));
		AlgoList[i]->GetPropertyWidget()->move(0,0);
		AlgoList[i]->GetPropertyWidget()->show();
		AlgoButton[i]=new QToolButton();
		AlgoButton[i]->setParent(ui->frameAlgo);
		AlgoButton[i]->setGeometry(W*i,0,W-2,ui->frameAlgo->height()-1);
		AlgoButton[i]->setCheckable(true);
		AlgoButton[i]->setAutoExclusive(true);
		connect(AlgoButton[i],SIGNAL(clicked()),this,SLOT(SlotButtonClicked()));
		AlgoButton[i]->setText(AlgoList[i]->GetButtonName());
		AlgoList[i]->SetButton(AlgoButton[i]);
		AlgoButton[i]->show();
	}
	AlgoButton[0]->setChecked(true);

	ConfirmItemListWindow=new ConfirmItemListForm(GetLayersBase(),this);

	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	ui->stackedWidgetProperty->setCurrentIndex(0);

	SetupPassword();
	InstallOperationLog(this);
}

ConfirmForm::~ConfirmForm()
{
    delete ui;
	ConfirmItemListWindow->deleteLater();
}

void	ConfirmForm::ShowItemList(void)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		AlgoList[i]->MakeConfirmItemList();
	}

}

void ConfirmForm::showEvent(QShowEvent *event)
{
	ConfirmItemListWindow->BuildShowItemList();
	ConfirmItemListWindow->show();

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
		int		x1,y1,x2,y2;
		if(m->GetXY(x1,y1,x2,y2)==true){
			ImagePanel.SetAreaSize(x2,y2);
		}
		QStringList	PhaseNames;
		m->ReqPhaseNames(PhaseNames);
		if(PhaseNames.count()>0){
			ui->listWidgetPhase->clear();
			ui->listWidgetPhase->addItems(PhaseNames);
			ui->listWidgetPhase->setCurrentRow(0);
		}
	}
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		AlgoList[i]->InitialShow();
	}

	ImagePanel.ZoomDrawWhole();
	on_toolButtonImageBankOnlyNG_clicked();
	UpdateImageBank();
}

void ConfirmForm::UpdateImageBank(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ImageBank",/**/"");
	if(f!=NULL){
		CmdReqImageBankGridList Cmd(GetLayersBase());
		f->TransmitDirectly(&Cmd);
		ImageBankGridList=Cmd.GridList;

		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		if(N>0){
			ui->tableWidgetImageBank->setColumnCount(N+1);
			QStringList HLabelList;
			HLabelList.append(LangSolver.GetString(ConfirmForm_LS,LID_1)/*"ID"*/);
			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			    EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			    if(m!=NULL){
			        HLabelList.append(m->GetMachineName());
			    }
			}
			ui->tableWidgetImageBank->setHorizontalHeaderLabels(HLabelList);

			int	Percentage=80/N;
			::SetColumnWidthInTable(ui->tableWidgetImageBank ,0, 20);
			 for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				 ::SetColumnWidthInTable(ui->tableWidgetImageBank ,SlaveNo+1, Percentage);
			 }

			int RowCount=ImageBankGridList.GetCount();
			if(RowCount>0){
				ui->tableWidgetImageBank->setRowCount(RowCount);
				int Row=0;
				for(ListImageBankPointerContainer *s=ImageBankGridList.GetFirst();s!=NULL;s=s->GetNext(),Row++){
				    ListImageBankPointer   *p=s->NPListPack<ListImageBankPointer>::GetFirst();
				    ::SetDataToTable(ui->tableWidgetImageBank, 0, Row, QString::number(p->Pointer->InspectionID));

				    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				        ListImageBankPointer *q;
				        for(q=p;q!=NULL;q=q->GetNext()){
				            if(q->Pointer->SlaveID==SlaveNo){
				                break;
				            }
				        }
				        if(q!=NULL){
							int32	ProcessMSec=p->Pointer->ProcessMSec;
							::SetDataToTable(ui->tableWidgetImageBank, 1+SlaveNo, Row, QString::number(ProcessMSec));
				            if(q->Pointer->ResultOK==true){
				               ::SetTableColor(ui->tableWidgetImageBank, 1+SlaveNo, Row,Qt::green);
				            }
				            else{
				               ::SetTableColor(ui->tableWidgetImageBank, 1+SlaveNo, Row,Qt::red);
				            }
				        }
						else{
				            ::SetDataToTable(ui->tableWidgetImageBank, 1+SlaveNo, Row, QString(/**/""));
							::SetDataColorToTable(ui->tableWidgetImageBank, 1+SlaveNo, Row,Qt::white);
				        }
				    }
				}
			}
		}
	}
}

double	ConfirmForm::GetZoomRate(void)			{	return ImagePanel.GetZoomRate();		}
mtGraphicUnit	*ConfirmForm::GetCanvas(void)	{	return &ImagePanel;						}
int		ConfirmForm::GetMovx(void)				{	return(ImagePanel.GetMovx());			}
int		ConfirmForm::GetMovy(void)				{	return(ImagePanel.GetMovy());			}
int		ConfirmForm::GetCanvasWidth(void)		{	return(ImagePanel.GetCanvasWidth());	}
int		ConfirmForm::GetCanvasHeight(void)		{	return(ImagePanel.GetCanvasHeight());	}
void	ConfirmForm::SetMovXY(int mx,int my)	{	ImagePanel.SetMovXY(mx,my);				}
double	ConfirmForm::GetZoomRateForWhole(void)	{	return ImagePanel.GetZoomRateForWhole();}
double	ConfirmForm::GetZoomRateForFit(void)	{	return ImagePanel.GetZoomRateForFit();	}
void	ConfirmForm::SetZoomRate(double ZoomRate){	ImagePanel.SetZoomRate(ZoomRate);		}
double	ConfirmForm::GetMaxZoomValue(void)		{	return ImagePanel.GetMaxZoomRate();		}
double	ConfirmForm::GetMinZoomValue(void)		{	return ImagePanel.GetMinZoomRate();		}
void	ConfirmForm::SetMaxZoomValue(double d)	{	ImagePanel.SetMaxZoomRate(d);			}
void	ConfirmForm::SetMinZoomValue(double d)	{	ImagePanel.SetMinZoomRate(d);			}

void	ConfirmForm::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)
{
	Gx=(Dx+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
	Gy=(Dy+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
}
void	ConfirmForm::ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)
{
	Dx=Gx/ImagePanel.GetZoomRate() - ImagePanel.GetMovx();
	Dy=Gy/ImagePanel.GetZoomRate() - ImagePanel.GetMovy();
}

void	ConfirmForm::SlotTimeOut()
{
	DrawModeSelectedArea=!DrawModeSelectedArea;
	ImagePanel.Repaint();
}

void	ConfirmForm::CanvasSlotDrawEnd(void)
{
	FlexArea resultarea;
	DisplayImage::ToFlexArea(ImagePanel.GetCanvas()->SData,resultarea);

	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->CanvasSlotDrawEnd(resultarea);
		}
	}
	ImagePanel.Clear();
}
void	ConfirmForm::SlotMouseMove(int ux ,int uy)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->AlgoMouseMove(ux ,uy);
		}
	}
}
void	ConfirmForm::SlotMouseLDownWithShift(int ux,int uy)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->AlgoMouseLDownWithShift(ux ,uy);
		}
	}
}
void	ConfirmForm::SlotMouseLDown(int ux ,int uy)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->AlgoMouseLDown(ux ,uy);
		}
	}
}
void	ConfirmForm::SlotMouseRDown(int ux ,int uy)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->AlgoMouseRDown(ux ,uy);
		}
	}
}

bool	ConfirmForm::GetDrawModeSelectedArea(void)
{
	return DrawModeSelectedArea;
}

void	ConfirmForm::CanvasSlotOnPaint(QPainter &pnt)
{
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	AlgorithmLibTypeWithAttrDataContainer	ALgorithmLibTypeContainer;
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->SetDrawAttr(ALgorithmLibTypeContainer);
		}
	}

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationReqConfirmPanelImage	RCmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			RCmd.ImageStructData.ZoomRate	=GetZoomRate();
			RCmd.ImageStructData.movx		=GetMovx();
			RCmd.ImageStructData.movy		=GetMovy();
			RCmd.ImageStructData.ImageW		=GetCanvasWidth();
			RCmd.ImageStructData.ImageH		=GetCanvasHeight();
			RCmd.ImageStructData.Phase		=m->GetCurrentPhase();
			RCmd.ImageStructData.MasterImage=ui->pushButtonMasterImage->isChecked();
			RCmd.ALgorithmLibTypeContainer=ALgorithmLibTypeContainer;
			IntegrationAckConfirmPanelImage	ACmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			if(RCmd.Send(Parent->SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){

				for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
					if(AlgoButton[i]->isChecked()==true){
						AlgoList[i]->CanvasSlotOnPaint(ImagePanel,page,Parent->TargetImageWithNG);
					}
				}
				pnt.drawImage(0,0,Parent->TargetImageWithNG);
			}

			if(GetDrawModeSelectedArea()==true){
				if(ImageSelectedArea.width()!=ImagePanel.GetCanvasWidth()
				|| ImageSelectedArea.height()!=ImagePanel.GetCanvasHeight()){
					ImageSelectedArea=QImage(ImagePanel.GetCanvasWidth(),ImagePanel.GetCanvasHeight(),QImage::Format_ARGB32);
				}
				ImageSelectedArea.fill(qRgba(0,0,0,0));
				SelectedArea.DrawAlpha(0,0,&ImageSelectedArea ,qRgba(255,0,0,80)
									   ,ImagePanel.GetZoomRate() ,ImagePanel.GetMovx() ,ImagePanel.GetMovy());
				pnt.drawImage(0,0,ImageSelectedArea);
			}
		}
	}

	ReEntrant=false;
}
void	ConfirmForm::SetSelectedArea(FlexArea &_SelectedArea)
{
	SelectedArea=_SelectedArea;
}
void	ConfirmForm::SlotMouseWheel(int delta,int globalX,int globalY)
{
	if(delta>0){
		if(ImagePanel.GetZoomRate()<GetMaxZoomValue()){
			int Gx,Gy;
			ChangeDxy2Gxy(globalX,globalY,Gx,Gy);
			ImagePanel.ZoomIn(Gx,Gy);

			ImagePanel.Repaint();
		}
	}
	else if(delta<0){
		if(ImagePanel.GetZoomRate()>GetMinZoomValue()){
			int Gx,Gy;
			ChangeDxy2Gxy(globalX,globalY,Gx,Gy);
			ImagePanel.ZoomOut(Gx,Gy);

			ImagePanel.Repaint();
		}
	}
}

void	ConfirmForm::ZoomArea(int ux1,int uy1,int ux2,int uy2)
{
	ImagePanel.ZoomRectU(ux1,uy1,ux2,uy2);
}

void ConfirmForm::resizeEvent(QResizeEvent *event)
{
	ui->tableWidgetImageBank->resize(ui->tableWidgetImageBank->width()
											,height()-ui->toolButtonImageBankOnlyNG->height() - ui->frameImageBankControl->height());
	ui->frameImageBankControl->move		(0,height()-ui->frameImageBankControl->height());
	ui->frameRightTop		->setGeometry(width()-ui->frameRightTop->width(),0
									   ,ui->frameRightTop->width(),height()-ui->stackedWidgetProperty->height()-ui->frameControl->height());

	ui->stackedWidgetProperty->move(width()-ui->stackedWidgetProperty->width()
									,height()-ui->stackedWidgetProperty->height()-ui->frameControl->height());
	ui->frameControl->move(width()-ui->frameControl->width()
						   ,height()-ui->frameControl->height());
	ui->frameImagePanel->resize(width()-ui->tableWidgetImageBank->width()-ui->frameRightTop->width()
								,height()-ui->frameImagePanel->geometry().top());

	ui->tableWidgetResult->resize(ui->tableWidgetResult->width(),ui->frameRightTop->height());
	ui->listWidgetPhase	 ->resize(ui->listWidgetPhase->width(),ui->frameRightTop->height());
	ImagePanel.setGeometry(0,0,ui->frameImagePanel->width(),ui->frameImagePanel->height());
}

void ConfirmForm::on_toolButtonImageBankOnlyNG_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ImageBank",/**/"");
	if(f!=NULL){
		CmdSetStateImageBank Cmd(GetLayersBase());
		Cmd.ONMode		=true;
		Cmd.StoreOnlyOK	=(ui->toolButtonImageBankOnlyNG->isChecked()==true)?false:true;
		Cmd.StoreOnlyNG	=true;
		Cmd.ListCount	=Parent->ImageBankListCount;
		f->TransmitDirectly(&Cmd);
	}
}

void ConfirmForm::on_tableWidgetImageBank_itemSelectionChanged()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ImageBank",/**/"");
	if(f!=NULL){
		int	Row=ui->tableWidgetImageBank->currentRow();
		if(Row<0)
			return;
		CmdReqListImageBankPointerContainer	Cmd(GetLayersBase());
		Cmd.Pointer		=ImageBankGridList[Row];
		Cmd.ExeRetry	=false;
		f->TransmitDirectly(&Cmd);

		ShowNGList();
	}
}

void	ConfirmForm::UpdateAgain(void)
{
	ShowNGList();
}

void ConfirmForm::on_tableWidgetImageBank_clicked(const QModelIndex &index)
{
	on_tableWidgetImageBank_itemSelectionChanged();
}

void ConfirmForm::on_pushButtonWhole_clicked()
{
	ImagePanel.ZoomDrawWhole();
}
void	ConfirmForm::SlotButtonClicked()
{
	ImagePanel.Repaint();
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			ui->stackedWidgetProperty->setCurrentIndex(i);
		}
	}
}

void ConfirmForm::on_tableWidgetResult_itemSelectionChanged()
{
	int	Row=ui->tableWidgetResult->currentRow();
	if(Row<0)
		return;
	ResultForConfirmList *r=ResultContainer.GetItem(Row);
	if(r!=NULL){
		int	W2=ImagePanel.GetCanvasWidth() /2/ImagePanel.GetZoomRate();
		int	H2=ImagePanel.GetCanvasHeight()/2/ImagePanel.GetZoomRate();
		ZoomArea(r->NGInfoData.cx-W2,r->NGInfoData.cy-H2,r->NGInfoData.cx+W2,r->NGInfoData.cy+H2);

		for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
			if(AlgoList[i]->GetLibType()==r->NGInfoData.NGLibType){
				AlgoList[i]->GetButton()->click();
				AlgoList[i]->SelectedItems.RemoveAll();
				AlgoList[i]->SelectedItems.Add		(r->NGInfoData.NGPhase
													,r->NGInfoData.NGPhase
													,r->NGInfoData.NGLayer
													,r->NGInfoData.NGItemID);
				AlgoList[i]->SetSelectItemsByGroupID(r->NGInfoData.NGErrorGroupID);
				AlgoList[i]->ShowItemData();
				AlgoList[i]->SetSelectItems();
				AlgoList[i]->ShowResult();
			}
		}
	}
}

void ConfirmForm::on_tableWidgetResult_clicked(const QModelIndex &index)
{
	on_tableWidgetResult_itemSelectionChanged();
}

void	ConfirmForm::ShowNGList(void)
{
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
		ResultContainer.RemoveAll();
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationReqCurrentResult	RCmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			IntegrationAckCurrentResult	ACmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			if(RCmd.Send(Parent->SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				ResultContainer+=ACmd.ResultContainer;
			}
		}
		ui->tableWidgetResult->setRowCount(ResultContainer.GetCount());
		int	row=0;
		for(ResultForConfirmList *r=ResultContainer.GetFirst();r!=NULL;r=r->GetNext(),row++){
			::SetDataToTable(ui->tableWidgetResult,0,row,QString::number(r->NGInfoData.NGPhase));
			::SetDataToTable(ui->tableWidgetResult,1,row,QString::number(r->NGInfoData.cx)
														+QString(/**/",")
														+QString::number(r->NGInfoData.cy));
			::SetDataToTable(ui->tableWidgetResult,2,row,r->Cause);
			::SetDataToTable(ui->tableWidgetResult,3,row,r->Message);
		}
	}
	//ui->tableWidgetResult->setVisible(false);
	//ui->tableWidgetResult->setVisible(true);
	::SetColumnWidthInTable(ui->tableWidgetResult,0,7);
	::SetColumnWidthInTable(ui->tableWidgetResult,1,28);
	::SetColumnWidthInTable(ui->tableWidgetResult,2,30);
	::SetColumnWidthInTable(ui->tableWidgetResult,3,35);
}
void	ConfirmForm::ClearRegisterComponent(void)
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		AlgoList[i]->ClearRegisterComponent();
	}
}
void ConfirmForm::on_pushButtonClose_clicked()
{
	hide();
	ConfirmItemListWindow->hide();
}

void ConfirmForm::on_pushButtonSetting_clicked()
{
	for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
		if(AlgoButton[i]->isChecked()==true){
			AlgoList[i]->SetProperty();
		}
	}
}

void ConfirmForm::on_toolButtonImageBankRetryAll_clicked()
{
   int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
   for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
	    IntegrationConfirmRetry	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	    RCmd.SendReqAck(NULL,SlaveNo,0);
    }
	UpdateImageBank();
}

void ConfirmForm::on_pushButtonMasterImage_clicked()
{
	ImagePanel.Repaint();
}

void ConfirmForm::on_toolButtonImageBankUpdate_clicked()
{
	UpdateImageBank();
	ShowNGList();
}

void ConfirmForm::on_listWidgetPhase_itemSelectionChanged()
{
	int	PhaseCode=ui->listWidgetPhase->currentRow();
	GetLayersBase()->GetIntegrationBasePointer()->SetCurrentPhase(Parent->SlaveNo ,PhaseCode);
}

void ConfirmForm::on_tableWidgetImageBank_doubleClicked(const QModelIndex &index)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ImageBank",/**/"");
	if(f!=NULL){
		int	Row=ui->tableWidgetImageBank->currentRow();
		if(Row<0)
			return;
		CmdReqListImageBankPointerContainer	Cmd(GetLayersBase());
		Cmd.Pointer		=ImageBankGridList[Row];
		Cmd.ExeRetry	=true;
		f->TransmitDirectly(&Cmd);

		UpdateImageBank();

		DWORD	MiliSec=0;
		int		SlaveNo=Parent->SlaveNo;
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationReqCurrentProcessTime	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckCurrentProcessTime	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
					MiliSec=max(MiliSec,ACmd.MiliSec);
				}
			}
		}
		::SetDataToTable(ui->tableWidgetImageBank, 1+SlaveNo, Row, QString::number(MiliSec));

		ShowNGList();

		for(int i=0;i<sizeof(AlgoList)/sizeof(AlgoList[0]);i++){
			AlgoList[i]->ForceDraw();
		}
		ShowItemList();
		ConfirmItemListWindow->BuildShowItemList();
		ConfirmItemListWindow->show();
	}
}

void	ConfirmForm::ShowConfirmItem(ConfirmAlgorithm *Algo,ConfirmItemList *Item)
{
	ui->listWidgetPhase->setCurrentRow(Item->Phase);
	Algo->PushButton();
	Algo->ShowConfirmItem(Item);

	int	SlaveNo=Algo->GetSlaveNo();
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
    if(m!=NULL){
		IntegrationReqConfirmItemInfo	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckConfirmItemInfo	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=Algo->GetLibType();
		RCmd.ItemIndex.Data.Phase	=m->GetCurrentPhase();
		RCmd.ItemIndex.Data.Layer	=Item->Layer;
		RCmd.ItemIndex.Data.Page	=Item->Page;
		RCmd.ItemIndex.Data.ItemID	=Item->ItemID;
		if(RCmd.Send(SlaveNo ,Item->Page,ACmd)==true){
			int	W=ACmd.Data.x2-ACmd.Data.x1;
			int	H=ACmd.Data.y2-ACmd.Data.y1;
			ZoomArea(ACmd.Data.x1-W/2,ACmd.Data.y1-H/2
					,ACmd.Data.x2+W/2,ACmd.Data.y2+H/2);
		}
	}
}

