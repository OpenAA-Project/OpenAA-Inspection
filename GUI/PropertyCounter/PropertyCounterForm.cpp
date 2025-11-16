#include "PropertyCounterForm.h"
#include "ui_PropertyCounterForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyCounterPacket.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XAlgorithmLibrary.h"
#include "XCounter.h"
#include "ButtonAutoMode.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyCounterForm::PropertyCounterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyCounterForm)
{
    ui->setupUi(this);

	FlipMask		=true;
	FoundItemImage	=false;

	ui->label_Result->setText(/**/"--");
	ui->tableWidgetAngle->setColumnWidth(0,48);

	on_horizontalSliderThreshold_valueChanged(0);
	on_horizontalSliderAdoptPixelsRate_valueChanged(0);

	BlinkMaskTimer.setSingleShot(false);
	BlinkMaskTimer.setInterval(200);
	connect(&BlinkMaskTimer,SIGNAL(timeout()),this,SLOT(SlotBlinkMask()));
	BlinkMaskTimer.start();

	ui->tabWidgetItem->setCurrentIndex(0);
	MaskingButtonEnabler=new ButtonRightClickEnabler(ui->toolButtonMaskArea);
	connect(MaskingButtonEnabler,SIGNAL(RightClicked(QAbstractButton *)),this,SLOT(SlotMaskRightClicked(QAbstractButton *)));
}

PropertyCounterForm::~PropertyCounterForm()
{
    delete ui;
}

void	PropertyCounterForm::ReadyParam(void)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase->ShowDebugMode==false){
		ui->tabWidgetItem	->removeTab(2);
		ui->tabWidgetItem	->removeTab(1);
		ui->pushButtonSave	->setVisible(false);
		ui->pushButtonLoad	->setVisible(false);
		ui->toolButtonFilter->setVisible(false);

		ui->label_ItemImage->setParent(this);
		QRect	R=ui->tabWidgetItem->geometry();
		ui->label_ItemImage->setGeometry(R);
		ui->label_ItemImage->show();
		ui->tabWidgetItem->hide();
	}
	ui->tabWidgetItem->setCurrentIndex(0);
}
void	PropertyCounterForm::BuildForShow(void)
{
	ShowItemImage();
	ReqThreshold();
}
void	PropertyCounterForm::ShowItemImage(void)
{
	FoundItemImage=false;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqItemImage	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Width	=ui->label_ItemImage->width();
		RCmd.Height	=ui->label_ItemImage->height();
		GUICmdAckItemImage	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ItemImage		=ACmd.ItemImage;
			ItemBackGround	=ACmd.ItemBackGround;
			ItemImageWithMask=ACmd.ItemImageWithMask;
			if(ItemImage.isNull()==false){
				ui->label_ItemImage		 ->setText(/**/"");
				ui->label_ItemImage		 ->setPixmap(QPixmap::fromImage(ItemImage));
				ui->label_BackGroundImage->setPixmap(QPixmap::fromImage(ItemBackGround));	
				FoundItemImage=true;
			}
			Angles			=ACmd.Angles;
			RotatedImages	=ACmd.RotatedImages;
			ui->tableWidgetAngle->setUpdatesEnabled(false);
			ui->tableWidgetAngle->setRowCount(Angles.GetCount());
			int	row=0;
			for(DoubleClass *d=Angles.GetFirst();d!=NULL;d=d->GetNext(),row++){
				::SetDataToTable(ui->tableWidgetAngle, 0, row, QString::number(d->GetValue(),'f',3));
			}
			ui->tableWidgetAngle->setUpdatesEnabled(true);
		}
	}
	if(FoundItemImage==false){
		ui->label_ItemImage		 ->clear();
		ui->label_BackGroundImage->clear();
		ui->label_ItemImage		 ->setText("カウント対象を矩形で囲って登録すればここに表示されます。");
	}
}
void	PropertyCounterForm::ReqThreshold(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		{
			GUICmdReqAdoptedRate	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			GUICmdAckAdoptedRate	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				ui->horizontalSliderThreshold->setValue(ACmd.AdoptedRate*100);
				ui->labelThresholdValue->setText(QString::number(ACmd.AdoptedRate*100.0,'f',1));
			}
		}
		{
			GUICmdReqAdoptPixelsRate	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			GUICmdAckAdoptPixelsRate	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				ui->horizontalSliderAdoptPixelsRate->setValue(ACmd.AdoptPixelsRate*100);
				ui->labelAdoptPixelsRate->setText(QString::number(ACmd.AdoptPixelsRate*100.0,'f',1));
			}
		}
		{
			GUICmdReqFocusLevel	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			GUICmdAckFocusLevel	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				ui->horizontalSliderFocusLevel->setValue(ACmd.FocusLevel);
				ui->labelFocusLevel->setText(QString::number(ACmd.FocusLevel));
			}
		}
	}
}
void	PropertyCounterForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCounterDrawModePacket	*CmdCounterDrawModePacketVar=dynamic_cast<CmdCounterDrawModePacket *>(packet);
	if(CmdCounterDrawModePacketVar!=NULL){
		QWidget *w=ui->tabWidgetItem->currentWidget();
		QString	Str=w->objectName();
		if(Str=="tabBackGround" || Str=="tabRotation"){
			CmdCounterDrawModePacketVar->ShowExecuteMap=true;
		}
		else{
			CmdCounterDrawModePacketVar->ShowExecuteMap=false;
		}
		if(Str=="tabRotation"){
			CmdCounterDrawModePacketVar->ShowItems=false;
		}
		else{
			CmdCounterDrawModePacketVar->ShowItems=true;
		}
		return;
	}
	CmdCounterDrawEnd	*CmdCounterDrawEndVar=dynamic_cast<CmdCounterDrawEnd *>(packet);
	if(CmdCounterDrawEndVar!=NULL){
		bool	AutoModeOn=false;
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual CounterItem");
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
		if(f!=NULL){
			CmdGetStateOnAutoMode	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			AutoModeOn=RCmd.AutoModeOn;

			CmdSetStateOnAutoMode	SCmd(GetLayersBase());
			SCmd.AutoModeOn=false;
			f->TransmitDirectly(&SCmd);
		}
		ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(E!=NULL){
			while(E->GetMode()!=ExecuteInspectBase::_CaptureNone){
				GSleep(100);
			}
		}
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdCounterDrawEndVar->Area, PageList);
		if(ui->toolButtonMaskArea->isChecked()==false){
			CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
			if(BBase->MaxAreaPiece>=CmdCounterDrawEndVar->Area.GetPatternByte()){

				for(IntClass *P=PageList.GetFirst();P != NULL;P=P->GetNext()) {
					int	page=P->GetValue();
					DataInPage *pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=CmdCounterDrawEndVar->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte() > 0) {
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdAddAreaManual	Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
						Cmd.LocalArea=A;
						Cmd.SendOnly(GlobalPage, 0);
					}
				}
				ShowItemImage();
				ReqThreshold();
			}
			else{
				int	N=sqrt(BBase->MaxAreaPiece);
				QString	Msg=QString("計数対象が大きすぎて作成できません(最大面積：")
							+QString::number(N)
							+QString("×")
							+QString::number(N)
							+QString("ピクセル)");
				QMessageBox::warning(NULL,"警告",Msg);
			}
		}
		else
		if(ui->toolButtonMaskArea->isChecked()==true){
			for(IntClass *P=PageList.GetFirst();P != NULL;P=P->GetNext()) {
				int	page=P->GetValue();
				DataInPage *pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=CmdCounterDrawEndVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte() > 0) {
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdAddMaskForCounter	Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
					Cmd.LocalArea=A;
					Cmd.SendOnly(GlobalPage, 0);
				}
			}
		}

		if(f!=NULL){
			CmdSetStateOnAutoMode	SCmd(GetLayersBase());
			SCmd.AutoModeOn=AutoModeOn;
			f->TransmitDirectly(&SCmd);
		}
		return;
	}
}

void	PropertyCounterForm::SlotBlinkMask()
{
	if(FoundItemImage==true){
		if(FlipMask==true){
			ui->label_ItemImage		 ->setPixmap(QPixmap::fromImage(ItemImageWithMask));
		}
		else{
			ui->label_ItemImage		 ->setPixmap(QPixmap::fromImage(ItemImage));
		}
	}
	FlipMask=!FlipMask;
}

void PropertyCounterForm::on_toolButtonRegisterItem_clicked()
{

}

void PropertyCounterForm::on_toolButtonRegisterBackGround_clicked()
{
	if(ui->toolButtonRegisterBackGround->isChecked()==true){
		ui->toolButtonMaskArea->setChecked(false);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRegisterBackGround	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.SetBackGround=ui->toolButtonRegisterBackGround->isChecked();
		RCmd.Send(NULL,GlobalPage,0);
	}
	ShowItemImage();
}

void PropertyCounterForm::on_horizontalSliderThreshold_valueChanged(int value)
{
	double		AdoptedRate=ui->horizontalSliderThreshold->value()/100.0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendAdoptedRate	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		SCmd.AdoptedRate=AdoptedRate;
		SCmd.Send(NULL,GlobalPage,0);
	}
	ui->labelThresholdValue->setText(QString::number(AdoptedRate*100.0,'f',1));
}

void PropertyCounterForm::on_horizontalSliderAdoptPixelsRate_valueChanged(int value)
{
	double		AdoptPixelsRate=ui->horizontalSliderAdoptPixelsRate->value()/100.0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendAdoptPixelsRate	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		SCmd.AdoptPixelsRate=AdoptPixelsRate;
		SCmd.Send(NULL,GlobalPage,0);
	}
	ui->labelAdoptPixelsRate->setText(QString::number(AdoptPixelsRate*100.0,'f',1));
}

void	PropertyCounterForm::ShowInPlayer(int64 shownInspectionID)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqResultCounter	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckResultCounter	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ResultCount=ACmd.Count;
			if(ACmd.TimeOut==true){
				ui->label_Result->setText(QString("Timeout - ")+QString::number(ResultCount));
			}
			else{
				ui->label_Result->setText(QString::number(ResultCount));
			}
		}
	}
}
void	PropertyCounterForm::AddCount(int n)
{
	ResultCount+=n;
	ui->label_Result->setText(QString::number(ResultCount));
}
void PropertyCounterForm::on_tableWidgetAngle_itemSelectionChanged()
{
	int	Row=ui->tableWidgetAngle->currentRow();
	if(0<=Row && Row<RotatedImages.count()){
		ui->label_ItemImageRotated ->setPixmap(QPixmap::fromImage(RotatedImages[Row]));
	}
}

void PropertyCounterForm::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(nullptr,"Save Item area"
												  ,QString()
												  ,/**/"Area data(*.item)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqItemArea	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				GUICmdAckItemArea	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				if(RCmd.Send(GlobalPage,0,ACmd)==true){
					if(::Save(&File,page)==false)
						return;
					if(ACmd.Areas.Save(&File)==false)
						return;
				}
			}
		}
	}
}

void PropertyCounterForm::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr,"Load Item area"
												  ,QString()
												  ,/**/"Area data(*.item)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				if(::Load(&File,page)==false)
					return;
				PureFlexAreaListContainer	Areas;

				if(Areas.Load(&File)==false)
					return;
				if(Areas.GetCount()!=0){
					GUICmdAddAreaManual	Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
					Cmd.LocalArea=*Areas.GetFirst();
					Cmd.SendOnly(GlobalPage, 0);

					ShowItemImage();
					ReqThreshold();
					return;
				}
			}
		}
	}
}

void PropertyCounterForm::on_toolButtonFilter_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetFilterMode	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.FilterON=ui->toolButtonFilter->isChecked();
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyCounterForm::on_horizontalSliderFocusLevel_valueChanged(int value)
{
	int		FocusLevel=ui->horizontalSliderFocusLevel->value();
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendFocusLevel	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		SCmd.FocusLevel=FocusLevel;
		SCmd.Send(NULL,GlobalPage,0);
	}
	ui->labelFocusLevel->setText(QString::number(FocusLevel));
}

void PropertyCounterForm::on_checkBoxOutsideCalc_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendOutsideCalc	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		SCmd.OutsideCalc=ui->checkBoxOutsideCalc->isChecked();
		SCmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyCounterForm::on_tabWidgetItem_currentChanged(int index)
{
	BroadcastRepaintAll();
}

void PropertyCounterForm::on_toolButtonMaskArea_clicked()
{
	if(ui->toolButtonMaskArea->isChecked()==true){
		ui->toolButtonRegisterBackGround->setChecked(false);
		on_toolButtonRegisterBackGround_clicked();
	}
	else{
		int	MaskCount=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqMaskCount	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			GUICmdAckMaskCount	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				MaskCount+=ACmd.MaskCount;
			}
		}
		if(MaskCount!=0){
			if(QMessageBox::question(NULL
							  ,"確認"
							  ,"カウント除外領域をリセットしますか?"
							  ,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
				bool	AutoModeOn=false;
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual CounterItem");
				GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
				if(f!=NULL){
					CmdGetStateOnAutoMode	RCmd(GetLayersBase());
					f->TransmitDirectly(&RCmd);
					AutoModeOn=RCmd.AutoModeOn;

					CmdSetStateOnAutoMode	SCmd(GetLayersBase());
					SCmd.AutoModeOn=false;
					f->TransmitDirectly(&SCmd);
				}
				ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
				if(E!=NULL){
					while(E->GetMode()!=ExecuteInspectBase::_CaptureNone){
						GSleep(100);
					}
				}
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdRemoveMask	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
					RCmd.Send(NULL,GlobalPage,0);
				}
				if(f!=NULL){
					CmdSetStateOnAutoMode	SCmd(GetLayersBase());
					SCmd.AutoModeOn=AutoModeOn;
					f->TransmitDirectly(&SCmd);
				}
			}
		}
	}
}

void	PropertyCounterForm::SlotMaskRightClicked(QAbstractButton *obj)
{

}