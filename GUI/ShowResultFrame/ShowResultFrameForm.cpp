#include "ShowResultFrameForm.h"
#include "ui_ShowResultFrameForm.h"
#include "XFrameDefCommon.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowResultFrameForm::ShowResultFrameForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowResultFrameForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowResultFrameForm::~ShowResultFrameForm()
{
    delete ui;
}

	
void	ShowResultFrameForm::Prepare(void)
{
}
void	ShowResultFrameForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
	int	w=(width()-24)/3;
	ui->tableWidget->setColumnWidth(0,w);
	ui->tableWidget->setColumnWidth(1,w);
	ui->tableWidget->setColumnWidth(2,w);
}
void	ShowResultFrameForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqShowInitial	*CmdReqShowInitialVar=dynamic_cast<CmdReqShowInitial *>(packet);
	if(CmdReqShowInitialVar!=NULL){
		BuildForShow();
	}
}
void	Merge(GroupFrameNumberResultContainer &Dest ,GroupFrameNumberResultContainer &Src)
{
	for(GroupFrameNumberResultList *s=Src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(GroupFrameNumberResultList *d=Dest.GetFirst();d!=NULL;d=d->GetNext()){
			if(s->GroupNumber==d->GroupNumber && s->FrameNumber==d->FrameNumber){
				Found=true;
				break;
			}
		}
		if(Found==false){
			GroupFrameNumberResultList	*m=new GroupFrameNumberResultList();
			*m=*s;
			Dest.AppendList(m);
		}
	}
}

int	StructureSortFunc(const void *a ,const void *b)
{
	GroupFrameNumberResultList	*pa=((GroupFrameNumberResultList **)a)[0];
	GroupFrameNumberResultList	*pb=((GroupFrameNumberResultList **)b)[0];
	if(pa->GroupNumber<pb->GroupNumber)
		return -1;
	if(pa->GroupNumber>pb->GroupNumber)
		return 1;
	if(pa->FrameNumber<pb->FrameNumber)
		return -1;
	if(pa->FrameNumber>pb->FrameNumber)
		return 1;
	return 0;
}

void	ShowResultFrameForm::BuildForShow(void)
{
	Structure.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqGroupFrameList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckGroupFrameList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			Merge(Structure,ACmd.Structure);
		}
	}
	Structure.Sort(StructureSortFunc);
	ui->tableWidget->setRowCount(Structure.GetCount());
	int	Row=0;
	for(GroupFrameNumberResultList *s=Structure.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		SetDataToTable(ui->tableWidget ,0 ,Row ,QString::number(s->GroupNumber));
		SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(s->FrameNumber));
		SetDataToTable(ui->tableWidget ,2 ,Row ,QString::number(0));
	}
}
	
void	ShowResultFrameForm::ShowInPlayer(int64 shownInspectionID)
{
	for(GroupFrameNumberResultList *s=Structure.GetFirst();s!=NULL;s=s->GetNext()){
		s->NGCount=0;
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqResultGroupFrameList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckResultGroupFrameList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==false){
			for(GroupFrameNumberResultList *s=ACmd.Structure.GetFirst();s!=NULL;s=s->GetNext()){
				for(GroupFrameNumberResultList *d=Structure.GetFirst();d!=NULL;d=d->GetNext()){
					if(s->GroupNumber==d->GroupNumber && s->FrameNumber==d->FrameNumber){
						d->NGCount+=s->NGCount;
						break;
					}
				}
			}
		}
	}
	int	Row=0;
	for(GroupFrameNumberResultList *s=Structure.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		SetDataToTable(ui->tableWidget ,2 ,Row ,QString::number(s->NGCount));
	}
}

//----------------------------------------------------------------------------------

GUICmdReqGroupFrameList::GUICmdReqGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqGroupFrameList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGroupFrameList	*SendBack=GetSendBack(GUICmdAckGroupFrameList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	FrameDefInPage	*PPage=dynamic_cast<FrameDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqGroupFrameList	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->Structure	=Da.GroupFrameList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckGroupFrameList::GUICmdAckGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckGroupFrameList::Load(QIODevice *f)
{
	if(Structure.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckGroupFrameList::Save(QIODevice *f)
{
	if(Structure.Save(f)==false)
		return false;
	return true;
}

//----------------------------------------------------------------------------------

GUICmdReqResultGroupFrameList::GUICmdReqResultGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqResultGroupFrameList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultGroupFrameList	*SendBack=GetSendBack(GUICmdAckResultGroupFrameList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	FrameDefInPage	*PPage=dynamic_cast<FrameDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqGroupFrameResultList	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->Structure	=Da.GroupFrameList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckResultGroupFrameList::GUICmdAckResultGroupFrameList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckResultGroupFrameList::Load(QIODevice *f)
{
	if(Structure.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckResultGroupFrameList::Save(QIODevice *f)
{
	if(Structure.Save(f)==false)
		return false;
	return true;
}

