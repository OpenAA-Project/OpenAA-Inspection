#include "TreeMasterShowResultListResource.h"
#include "TreeMasterShowResultForm.h"
#include "ui_TreeMasterShowResultForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


TreeMasterShowResultForm::TreeMasterShowResultForm(LayersBase *base,QWidget *parent) :
     GUIFormBase(base,parent),
    ui(new Ui::TreeMasterShowResultForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth (0,40);
	ui->tableWidget->setColumnWidth (1,100);
	ui->tableWidget->setColumnWidth (2,80);
	ui->tableWidget->setColumnWidth (3,80);
	ui->tableWidget->setColumnWidth (4,80);
}

TreeMasterShowResultForm::~TreeMasterShowResultForm()
{
    delete ui;
}

int	PointerListFunc(const void *a ,const void *b)
{
	TreeMasterResultList	**ai=(TreeMasterResultList **)a;
	TreeMasterResultList	**bi=(TreeMasterResultList **)b;
	if(ai[0]->ItemID>bi[0]->ItemID){
		return -1;
	}
	if(ai[0]->ItemID<bi[0]->ItemID){
		return 1;
	}

	return 0;
}
void	TreeMasterShowResultForm::ShowInPlayer(int64 shownInspectionID)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	TreeMasterInfo.RemoveAll();

	GUICmdReqTreeMasterResultList	**BmpRequester=new GUICmdReqTreeMasterResultList*[GetParamGlobal()->PageNumb];
	GUICmdSendTreeMasterResultList	**BmpReceiver=new GUICmdSendTreeMasterResultList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpRequester[page]	=new GUICmdReqTreeMasterResultList	(GetLayersBase(),sRoot,sName,globalPage);
		BmpReceiver[page]	=new GUICmdSendTreeMasterResultList	(GetLayersBase(),sRoot,sName,globalPage);
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			for(TreeMasterResultList *L=BmpReceiver[page]->TreeMasterInfo.GetFirst();L!=NULL;L=L->GetNext()){
				TreeMasterResultList *a=TreeMasterInfo.FindByItemID(L->ItemID);
				if(a==NULL){
					TreeMasterResultList	*d=new TreeMasterResultList();
					*d=*L;
					TreeMasterInfo.AppendList(d);
				}else{
					if(L->ResultE == 0.0)
						continue;
					if(a->ResultE==0.0 || a->ResultE > L->ResultE)
						a->ResultE = L->ResultE;
				}
			}
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	Numb=TreeMasterInfo.GetNumber();

	TreeMasterResultList	**PointerList;
	PointerList=new TreeMasterResultList*[Numb];
	for(int	N=0;N<Numb;N++){
		TreeMasterResultList *a=TreeMasterInfo.GetFirst();
		TreeMasterInfo.RemoveList(a);
		PointerList[N]=a;
	}
	QSort(PointerList,Numb,sizeof(PointerList[0]),PointerListFunc);
	for(int	N=0;N<Numb;N++){
		TreeMasterInfo.AppendList(PointerList[N]);
	}
	delete	[]PointerList;

	ui->tableWidget->setRowCount(Numb);
	for(int	N=0;N<Numb;N++){
		TreeMasterResultList *a=TreeMasterInfo[N];
		::SetDataToTable(ui->tableWidget,0,N,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidget,1,N,a->CatName);
		::SetDataToTable(ui->tableWidget,2,N,QString::number(a->MasterCode));
		::SetDataToTable(ui->tableWidget,3,N,QString::number(a->ResultE));
	}

	ReEntrant=false;	
}


//======================================================================================
GUICmdReqTreeMasterResultList::GUICmdReqTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqTreeMasterResultList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTreeMasterResultList	*SendBack=GetSendBack(GUICmdSendTreeMasterResultList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	SendBack->MakeTreeMasterResultList(localPage,GetLayersBase());

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendTreeMasterResultList::GUICmdSendTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTreeMasterResultList::Load(QIODevice *f)
{
	if(TreeMasterInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendTreeMasterResultList::Save(QIODevice *f)
{
	if(TreeMasterInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendTreeMasterResultList::MakeTreeMasterResultList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(ABase==NULL)
		return;
	TreeMasterInfo.RemoveAll();

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			TreeMasterItem	*MItem=dynamic_cast<TreeMasterItem *>(item);
			if(MItem!=NULL){
				TreeMasterResultList	*L=new TreeMasterResultList();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				int x1 ,y1 ,x2 ,y2;
				MItem->GetXY(x1 ,y1 ,x2 ,y2);
				L->CatName		=MItem->CatName;
				L->MasterCode	=MItem->MasterCode;
				L->ItemID		=MItem->TMItemID;
				L->ResultE		=MItem->ResultE;

				TreeMasterInfo.AppendList(L);				
			}
		}
	}
}