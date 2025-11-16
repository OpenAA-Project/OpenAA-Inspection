#include "PropertyMakeAverageImageResource.h"
#include "PropertyMakeAverageImageForm.h"
#include "ui_PropertyMakeAverageImageForm.h"
#include "XPropertyMakeAverageImagePacket.h"
#include "XMakeAverageImagePacket.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMakeAverageImageForm::PropertyMakeAverageImageForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyMakeAverageImageForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
}

PropertyMakeAverageImageForm::~PropertyMakeAverageImageForm()
{
    delete ui;
}

void	PropertyMakeAverageImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdMakeAverageImageDrawAttr	*CmdMakeAverageImageDrawAttrVar=dynamic_cast<CmdMakeAverageImageDrawAttr *>(packet);
	if(CmdMakeAverageImageDrawAttrVar!=NULL){
		CmdMakeAverageImageDrawAttrVar->ModeShowItems=ui->toolButtonDrawPartialArea->isChecked();
		if(ui->toolButtonDrawImage->isChecked()==true)
			CmdMakeAverageImageDrawAttrVar->DrawMode=MakeAverageImageDrawAttr::_None;
		if(ui->toolButtonDrawDarkImage->isChecked()==true)
			CmdMakeAverageImageDrawAttrVar->DrawMode=MakeAverageImageDrawAttr::_Dark;
		if(ui->toolButtonDrawLightImage->isChecked()==true)
			CmdMakeAverageImageDrawAttrVar->DrawMode=MakeAverageImageDrawAttr::_Light;
		if(ui->toolButtonDrawAverageImage->isChecked()==true)
			CmdMakeAverageImageDrawAttrVar->DrawMode=MakeAverageImageDrawAttr::_Average;
		if(ui->toolButtonDrawVariableImage->isChecked()==true)
			CmdMakeAverageImageDrawAttrVar->DrawMode=MakeAverageImageDrawAttr::_Variable;
		
		CmdMakeAverageImageDrawAttrVar->VariableStrength=ui->horizontalSliderVariableStrength->value();

		return;
	}
	GUICmdMakeAverageImageDrawEnd	*GUICmdMakeAverageImageDrawEndVar=dynamic_cast<GUICmdMakeAverageImageDrawEnd *>(packet);
	if(GUICmdMakeAverageImageDrawEndVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual MakeAverageImageUsageAreaItem");

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(GUICmdMakeAverageImageDrawEndVar->Area, PageList);
		for(IntClass *P=PageList.GetFirst();P != NULL;P=P->GetNext()) {
			int	page=P->GetValue();
			DataInPage *pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=GUICmdMakeAverageImageDrawEndVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte() > 0) {
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSendAddMakeAverageImageUsageAreaItem	Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
				Cmd.LocalArea=A;
				Cmd.SendOnly(GlobalPage, 0);
			}
		}
		return;
	}
	CmdReqReset	*CmdReqResetVar=dynamic_cast<CmdReqReset *>(packet);
	if(CmdReqResetVar!=NULL){
		on_pushButtonResetAverage_clicked();
		return;
	}
}

void PropertyMakeAverageImageForm::on_toolButtonDrawPartialArea_clicked()
{
	if(ui->toolButtonDrawPartialArea->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				GUIFormBase	*p=d->GetImageControlTools();
				if(p!=NULL){
					CmdReqImageLayer	RCmd(GetLayersBase(),GetLayersBase()->GetMaxLayerNumb());
					p->TransmitDirectly(&RCmd);
					d->ChangeDisplayType(RCmd.DType);
				}
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_toolButtonDrawImage_clicked()
{
	if(ui->toolButtonDrawImage->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				GUIFormBase	*p=d->GetImageControlTools();
				if(p!=NULL){
					CmdReqImageLayer	RCmd(GetLayersBase(),GetLayersBase()->GetMaxLayerNumb());
					p->TransmitDirectly(&RCmd);
					d->ChangeDisplayType(RCmd.DType);
				}
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_toolButtonDrawDarkImage_clicked()
{
	if(ui->toolButtonDrawDarkImage->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				d->ChangeDisplayType(DisplayImage::__NoImage);
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_toolButtonDrawLightImage_clicked()
{
	if(ui->toolButtonDrawLightImage->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				d->ChangeDisplayType(DisplayImage::__NoImage);
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_toolButtonDrawAverageImage_clicked()
{
	if(ui->toolButtonDrawAverageImage->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				d->ChangeDisplayType(DisplayImage::__NoImage);
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_toolButtonDrawVariableImage_clicked()
{
	if(ui->toolButtonDrawVariableImage->isChecked()==true){
		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
		if(F!=NULL){
			DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
			if(d!=NULL){
				d->ChangeDisplayType(DisplayImage::__NoImage);
			}
		}
	}
	BroadcastRepaintAll();
}

void PropertyMakeAverageImageForm::on_pushButtonSetAverageToMaster_clicked()
{
	for(int Page=0;Page<GetPageNumb();Page++){
		int	GlobalPage=Page;
		GUICmdSetAverageToMaster	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	PropertyMakeAverageImageForm::ShowInScanning(int64 shownInspectionID)
{
	for(int Page=0;Page<GetPageNumb();Page++){
		int	GlobalPage=Page;
		GUICmdReqAverageCount	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckAverageCount	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ui->lineEditAverageCount->setText(QString::number(ACmd.AddedCount));
			break;
		}
	}
}

void PropertyMakeAverageImageForm::on_pushButtonResetAverage_clicked()
{
	for(int Page=0;Page<GetPageNumb();Page++){
		int	GlobalPage=Page;
		GUICmdResetAverage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
	ui->lineEditAverageCount->setText(QString::number(0));
}
void    PropertyMakeAverageImageForm::ResetAverage(void)
{
	on_pushButtonResetAverage_clicked();
}

void PropertyMakeAverageImageForm::on_horizontalSliderVariableStrength_valueChanged(int value)
{
	GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"MakeAverageImagePanel",/**/"");
	if(F!=NULL){
		DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(F);
		if(d!=NULL){
			d->Repaint();
		}
	}
}


//=====================================================================================

GUICmdSetAverageToMaster::GUICmdSetAverageToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSetAverageToMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdSetAverageToMaster	RCmd(GetLayersBase());
	AP->TransmitDirectly(&RCmd);
}

//=====================================================================================

GUICmdReqAverageCount::GUICmdReqAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAverageCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAverageCount	*SendBack=GetSendBack(GUICmdAckAverageCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(AlignBase==NULL)
		return;
	MakeAverageImageInPage	*AP=dynamic_cast<MakeAverageImageInPage *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	if(AP->AllocatedLayers!=0){
		SendBack->AddedCount=AP->ALayerImages[0]->AddedCount;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckAverageCount::GUICmdAckAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAverageCount::Load(QIODevice *f)
{
	if(::Load(f,AddedCount)==false)
		return false;
	return true;
}
bool	GUICmdAckAverageCount::Save(QIODevice *f)
{
	if(::Save(f,AddedCount)==false)
		return false;
	return true;
}


//=====================================================================================
GUICmdSendAddMakeAverageImageUsageAreaItem::GUICmdSendAddMakeAverageImageUsageAreaItem(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage)
	:GUICmdPacketBase(Base, emitterRoot, emitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdSendAddMakeAverageImageUsageAreaItem::Load(QIODevice *f)
{
	if(LocalArea.Load(f) == false)
		return false;
	return true;
}
bool	GUICmdSendAddMakeAverageImageUsageAreaItem::Save(QIODevice *f)
{
	if(LocalArea.Save(f) == false)
		return false;
	return true;
}

void	GUICmdSendAddMakeAverageImageUsageAreaItem::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	MakeAverageImageBase *BBase=(MakeAverageImageBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MakeAverageImage");
	if(BBase != NULL) {
		MakeAverageImageInPage *PData=dynamic_cast<MakeAverageImageInPage *>(BBase->GetPageData(localPage));
		if(PData != NULL) {
			CmdAddAverageArea	Cmd(this);
			Cmd.Area=LocalArea;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=====================================================================================

GUICmdResetAverage::GUICmdResetAverage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdResetAverage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdResetAverage	RCmd(GetLayersBase());
	AP->TransmitDirectly(&RCmd);
}
