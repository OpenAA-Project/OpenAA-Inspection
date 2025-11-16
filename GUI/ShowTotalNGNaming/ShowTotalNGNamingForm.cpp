#include "ShowTotalNGNamingResource.h"
#include "ShowTotalNGNamingForm.h"
#include "ui_ShowTotalNGNamingForm.h"
#include "XGeneralFunc.h"
#include "XLotInformation.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowTotalNGNamingForm::ShowTotalNGNamingForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowTotalNGNamingForm)
{
    ui->setupUi(this);

	LastMasterID	=-1;
	
	TotalNGCount	=0;
	TotalOKCount	=0;
	TotalCount		=0;
	InspectedCount	=0;

	ui->tableWidgetList->setColumnWidth(0,100);
	ui->tableWidgetList->setColumnWidth(1,40);
	ui->tableWidgetList->setColumnWidth(2,40);
}

ShowTotalNGNamingForm::~ShowTotalNGNamingForm()
{
    delete ui;
}
void	ShowTotalNGNamingForm::BuildForShow(void)
{
	NamingData.clear();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSendNamingAreasList		BmpReceiver	(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdReqNamingAreasList		BmpRequester(GetLayersBase(),sRoot,sName,globalPage);
		if(BmpRequester.Send(BmpRequester.GetGlobalPage(),0,BmpReceiver)==true){
			for(int i=0;i<BmpReceiver.NamingData.count();i++){
				int j;
				for(j=0;j<NamingData.count();j++){
					if(BmpReceiver.NamingData[i]==NamingData[j]){
						break;
					}
				}
				if(j>=NamingData.count()){
					NamingData.append(BmpReceiver.NamingData[i]);
				}
			}
		}
	}
}

void	ShowTotalNGNamingForm::ShowInPlayer(int64 shownInspectionID)
{
	if(LastMasterID!=GetLayersBase()->GetMasterCode() || LastLotAutoCountList!=GetLayersBase()->GetLotBase()->GetLotAutoCount()){
		on_pushButtonReset_clicked();
		LastMasterID		=GetLayersBase()->GetMasterCode();
		LastLotAutoCountList=GetLayersBase()->GetLotBase()->GetLotAutoCount();
	}

	NGAreaListContainer	TmpNGData;
	InspectedCount++;

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqNGNamingList	CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendNGNamingList	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			NGAreaList *e;
			for(e=CmdAck.NGData.GetFirst();e!=NULL;e=e->GetNext()){
				if(e->GetNGCount()>0){
					NGAreaList *a;
					for(a=TmpNGData.GetFirst();a!=NULL;a=a->GetNext()){
						if(e->GetAreaName()==a->GetAreaName()){
							a->SetNGCount(1);
							break;	
						}
					}
					if(a==NULL){
						TmpNGData.AppendList(new NGAreaList(e->GetAreaName(),1));
					}
				}
			}
		}
	}
	for(NGAreaList *a=TmpNGData.GetFirst();a!=NULL;a=a->GetNext()){
		NGAreaList *t;
		for(t=NGData.GetFirst();t!=NULL;t=t->GetNext()){
			if(a->GetAreaName()==t->GetAreaName()){
				t->SetNGCount(t->GetNGCount()+1);
				break;
			}
		}
		if(t==NULL){
			t=new NGAreaList(a->GetAreaName(),1);
			NGData.AppendList(t);
		}
	}

	TotalNGCount=0;
	for(NGAreaList *a=NGData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetNGCount()!=0){
			TotalNGCount+=a->GetNGCount();
		}
	}
	TotalCount		+=NamingData.count();
	TotalOKCount	=TotalCount-TotalNGCount;

	ShowAll();
}
void	ShowTotalNGNamingForm::ShowAll(void)
{
	int	RowCount=NGData.GetCount();
	ui->tableWidgetList->setRowCount(RowCount);
	int	row=0;
	for(NGAreaList *a=NGData.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetList,0,row,a->GetAreaName());
		::SetDataToTable(ui->tableWidgetList,1,row,QString::number(InspectedCount-a->GetNGCount()));
		::SetDataToTable(ui->tableWidgetList,2,row,QString::number(a->GetNGCount()));
	}

	ui->lineEditTotalNG	->setText(QString::number(TotalNGCount));
	ui->lineEditTotalOK	->setText(QString::number(TotalOKCount));

}
void ShowTotalNGNamingForm::on_pushButtonReset_clicked()
{
	NGData.RemoveAll();
	for(int i=0;i<NamingData.count();i++){
		NGData.AppendList(new NGAreaList(NamingData[i],0));
	}
	TotalNGCount	=0;
	TotalOKCount	=0;
	TotalCount		=0;
	InspectedCount	=0;
	ShowAll();
}


//===========================================================================================================

GUICmdReqNGNamingList::GUICmdReqNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdReqNGNamingList::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}
bool	GUICmdReqNGNamingList::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqNGNamingList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGNamingList	*SendBack=GetSendBack(GUICmdSendNGNamingList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		NGAreaListContainer		RData;
		R->BindNGAreaListContainer(localPage,RData);
		for(NGAreaList *a=RData.GetFirst();a!=NULL;a=a->GetNext()){
			NGAreaList *b;
			for(b=SendBack->NGData.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->GetAreaName()==b->GetAreaName()){
					if(a->GetNGCount()>0){
						b->SetNGCount(1);
						break;
					}
				}
			}
			if(b==NULL){
				NGAreaList	*h=new NGAreaList(a->GetAreaName(),(a->GetNGCount()>0)?1:0);
				SendBack->NGData.AppendList(h);
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendNGNamingList::GUICmdSendNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendNGNamingList::Load(QIODevice *f)
{
	if(NGData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNGNamingList::Save(QIODevice *f)
{
	if(NGData.Save(f)==false)
		return false;
	return true;
}

//==============================================================================

GUICmdReqNamingAreasList::GUICmdReqNamingAreasList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqNamingAreasList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingAreasList	*SendBack=GetSendBack(GUICmdSendNamingAreasList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;
	ReqNamingAreas	SGCmd(GetLayersBase());
	NamingBase->GetPageData(localPage)->TransmitDirectly(&SGCmd);

	SendBack->NamingData	=SGCmd.Areas;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNamingAreasList::GUICmdSendNamingAreasList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNamingAreasList::Load(QIODevice *f)
{
	if(::Load(f,NamingData)==false)
		return false;
	return true;
}
bool	GUICmdSendNamingAreasList::Save(QIODevice *f)
{
	if(::Save(f,NamingData)==false)
		return false;
	return true;
}