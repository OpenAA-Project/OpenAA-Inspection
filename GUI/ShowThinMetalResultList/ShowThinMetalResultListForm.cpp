#include "ShowThinMetalResultListForm.h"
#include "ui_ShowThinMetalResultListForm.h"
#include "XThinMetal.h"
#include "XGeneralFunc.h"
#include "SelectDialog.h"
#include "ButtonLoadBmpJpg.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool	ThinMetalSamplingResult::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}
bool	ThinMetalSamplingResult::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	return true;
}


ShowThinMetalResultListForm::ShowThinMetalResultListForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowThinMetalResultListForm)
{
    ui->setupUi(this);

	CurrentPage	=0;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowThinMetalResultListForm::~ShowThinMetalResultListForm()
{
    delete ui;
}
void	ShowThinMetalResultListForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
	ui->tableWidget->setColumnWidth(0,width()-100);
	ui->tableWidget->setColumnWidth(1,width()-50);
}
void	ShowThinMetalResultListForm::ShowInPlayer(int64 shownInspectionID)
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(CurrentPage);
	GUICmdReqThinMetalSamplingResultConatiner	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
	RCmd.MaxCount=height()/30;
	GUICmdAckThinMetalSamplingResultConatiner	ACmd(GetLayersBase() ,sRoot,sName ,GlobalPage);

	ui->tableWidget->setRowCount(0);
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		CurrentContainer=ACmd.CurrentContainer;

		ui->tableWidget->setRowCount(CurrentContainer.GetCount());
		int	Row=0;
		for(ThinMetalSamplingResult *a=CurrentContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			::SetDataToTable(ui->tableWidget ,0 ,Row ,a->FileName);
			::SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(a->MatchingRate*100.0,'f',1));
		}
	}
}

void ShowThinMetalResultListForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;

	SelectDialog	D(GetLayersBase());
	int	Ret=D.exec();
	if(Ret==1){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(CurrentPage);
		GUICmdDelThinMetalSampling	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
		ThinMetalSamplingResult *a=CurrentContainer[Row];
		RCmd.DeleteFileName=a->FileName;
		RCmd.Send(NULL,GlobalPage,0);
		ShowInPlayer(0);
	}
	else if(Ret==2){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(CurrentPage);
		GUICmdLoadThinMetalSampling	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
		ThinMetalSamplingResult *a=CurrentContainer[Row];
		RCmd.FileName=a->FileName;
		RCmd.Send(NULL,GlobalPage,0);
		RepaintAll();
	}
}

//===========================================================================================
	
GUICmdReqThinMetalSamplingResultConatiner::GUICmdReqThinMetalSamplingResultConatiner(LayersBase *Base ,const QString &EmitterRoot,const QString& EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer	=-1;
	ItemID	=-1;
	MaxCount=30;
}
bool	GUICmdReqThinMetalSamplingResultConatiner::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,MaxCount)==false)
		return false;
	return true;
}
bool	GUICmdReqThinMetalSamplingResultConatiner::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,MaxCount)==false)
		return false;
	return true;
}

void	GUICmdReqThinMetalSamplingResultConatiner::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThinMetalSamplingResultConatiner	*SendBack=GetSendBack(GUICmdAckThinMetalSamplingResultConatiner,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			ThinMetalInPage	*TMPage=(ThinMetalInPage *)Ap;
			ThinMetalInLayer	*AL=(ThinMetalInLayer *)TMPage->GetLayerData((Layer>=0)?Layer:0);
			if(AL!=NULL){
				ThinMetalItem	*c=(ThinMetalItem *)AL->SearchIDItem(ItemID);
				if(c==NULL){
					c=(ThinMetalItem *)AL->GetFirstData();
				}
				if(c!=NULL){
					for(int i=0;i<c->MListNumb;i++){
						if(c->MList[i].Point==NULL){
							continue;
						}
						ThinMetalSamplingResult *a;
						for(a=SendBack->CurrentContainer.GetFirst();a!=NULL;a=a->GetNext()){
							if(a->FileName==c->MList[i].Point->TargetFileName){
								break;
							}
						}
						if(a==NULL){
							ThinMetalSamplingResult	*r=new ThinMetalSamplingResult();
							r->FileName		=c->MList[i].Point->TargetFileName;
							r->MatchingRate	=c->MList[i].Result;
							SendBack->CurrentContainer.AppendList(r);
							if(SendBack->CurrentContainer.GetCount()>=MaxCount){
								break;
							}
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);	
}

GUICmdAckThinMetalSamplingResultConatiner::GUICmdAckThinMetalSamplingResultConatiner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckThinMetalSamplingResultConatiner::Load(QIODevice *f)
{
	if(CurrentContainer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckThinMetalSamplingResultConatiner::Save(QIODevice *f)
{
	if(CurrentContainer.Save(f)==false)
		return false;
	return true;

}

//===========================================================================================
	
GUICmdDelThinMetalSampling::GUICmdDelThinMetalSampling(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer	=-1;
	ItemID	=-1;
}
bool	GUICmdDelThinMetalSampling::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,DeleteFileName)==false)
		return false;
	return true;
}
bool	GUICmdDelThinMetalSampling::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,DeleteFileName)==false)
		return false;
	return true;
}

void	GUICmdDelThinMetalSampling::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			ThinMetalInPage	*TMPage=(ThinMetalInPage *)Ap;
			ThinMetalInLayer	*AL=(ThinMetalInLayer *)TMPage->GetLayerData((Layer>=0)?Layer:0);
			if(AL!=NULL){
				ThinMetalItem	*c=(ThinMetalItem *)AL->SearchIDItem(ItemID);
				if(c==NULL){
					c=(ThinMetalItem *)AL->GetFirstData();
				}
				if(c!=NULL){
					for(CoeffImageList *a=c->SampleImages.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->TargetFileName==DeleteFileName){
							c->SampleImages.RemoveList(a);
							for(int i=0;i<c->MListNumb;i++){
								if(c->MList[i].Point==a){
									c->MList[i].Point=NULL;
								}
							}

							delete	a;
							break;
						}
					}
				}
			}
		}
	}
}

//===========================================================================================
	
GUICmdLoadThinMetalSampling::GUICmdLoadThinMetalSampling(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer	=-1;
	ItemID	=-1;
}
bool	GUICmdLoadThinMetalSampling::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	return true;
}
bool	GUICmdLoadThinMetalSampling::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	return true;
}

void	GUICmdLoadThinMetalSampling::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			ThinMetalInPage	*TMPage=(ThinMetalInPage *)Ap;
			ThinMetalInLayer	*AL=(ThinMetalInLayer *)TMPage->GetLayerData((Layer>=0)?Layer:0);
			if(AL!=NULL){
				ThinMetalItem	*c=(ThinMetalItem *)AL->SearchIDItem(ItemID);
				if(c==NULL){
					c=(ThinMetalItem *)AL->GetFirstData();
				}
				if(c!=NULL){
					int	Row=0;
					for(CoeffImageList *a=c->SampleImages.GetFirst();a!=NULL;a=a->GetNext(),Row++){
						if(a->TargetFileName==FileName){
							GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
							if(f!=NULL){
								CmdLoadBmpJpgPacketMaster	Cmd(GetLayersBase());
								Cmd.FileName	=a->TargetFolder
												+GetSeparator()
												+a->TargetFileName;
								f->TransmitDirectly(&Cmd);
								break;
							}
						}
					}
				}
			}
		}
	}
}