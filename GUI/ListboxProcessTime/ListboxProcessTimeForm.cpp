#include "ListboxProcessTimeResource.h"
#include "ListboxProcessTimeForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool    ExecuteTimeAlgorithm::Save(QIODevice *f)
{
	if(ExecuteTimeClass::Save(f)==false)
		return false;
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	return true;
}
bool    ExecuteTimeAlgorithm::Load(QIODevice *f)
{
	if(ExecuteTimeClass::Load(f)==false)
		return false;
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	return true;
}
ExecuteTimeClass	&ExecuteTimeAlgorithm::operator=(ExecuteTimeClass &src)
{
	ExecuteTimeClass::operator=(src);
	ExecuteTimeAlgorithm	*s=dynamic_cast<ExecuteTimeAlgorithm *>(&src);
	if(s!=NULL){
		DLLRoot=s->DLLRoot;
		DLLName=s->DLLName;
	}
	return *this;
}

//=============================================================================

ListboxProcessTimeForm::ListboxProcessTimeForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	AlgorithmCount	=GetLayersBase()->GetLogicDLLBase()->GetDLLCounts();
	ListByPage	=new ExecuteTimeAlgorithm*[AlgorithmCount];

	for(int i=0;i<AlgorithmCount;i++){
		ListByPage[i]=new ExecuteTimeAlgorithm[GetPageNumb()];
	}
	ui.tableWidgetAlgorithm->setRowCount(AlgorithmCount);
	int	Row=0;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		SetDataToTable(ui.tableWidgetAlgorithm,0,Row,L->GetDLLRoot());
		SetDataToTable(ui.tableWidgetAlgorithm,1,Row,L->GetDLLName());
		Row++;
	}

	ui.tableWidget->setColumnCount(GetPageNumb()+1);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(ListboxProcessTimeForm_LS,LID_0)/*"PC Total"*/);
	for(int page=0;page<GetPageNumb();page++){
		ui.tableWidget->setColumnWidth (page+1, 50);
		HeaderLabel.append(QString(/**/"Page")+QString::number(page));
	}
	ui.tableWidget->setHorizontalHeaderLabels(HeaderLabel);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ListboxProcessTimeForm::~ListboxProcessTimeForm()
{
	if(ListByPage!=NULL){
		for(int i=0;i<AlgorithmCount;i++){
			delete	[]ListByPage[i];
		}
		delete	[]ListByPage;
	}
	ListByPage=NULL;
}

void	ListboxProcessTimeForm::ResizeAction()
{
	int	L=height()-ui.tableWidgetAlgorithm->height()-ui.frameBottom->height();
	ui.tableWidget->resize(width(),L);
	ui.frameBottom->move(0,ui.tableWidget->geometry().bottom()+1);
	ui.frameBottom->resize(width(),ui.frameBottom->height());
}

void ListboxProcessTimeForm::on_pushButtonView_clicked()
{
	int	*FilterTimeInPage=new int[GetPageNumb()];
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqProcessTime	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdSendProcessTime	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true && ACmd.IsReceived()==true){
			for(int i=0;i<AlgorithmCount && i<ACmd.AlgorithmCount;i++){
				ListByPage[i][page]=ACmd.ExecuteTimeData[i];
			}
			FilterTimeInPage[page]=ACmd.FilterTime;
		}
	}

	int	Row=ui.tableWidgetAlgorithm->currentRow();
	if(Row<0){
		delete	[]FilterTimeInPage;
		return;
	}
	LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetItem(Row);
	if(L==NULL){
		delete	[]FilterTimeInPage;
		return;
	}

	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForDraw();
	
	if(Res!=NULL){
		SetDataToTable(ui.tableWidget,0,0,/**/"");
		SetDataToTable(ui.tableWidget,0,1,/**/"");
		SetDataToTable(ui.tableWidget,0,2,/**/"");
		SetDataToTable(ui.tableWidget,0,3,(int)Res->ExecTime.TM_ExecutePreAlignment);
		SetDataToTable(ui.tableWidget,0,4,(int)Res->ExecTime.TM_ExecuteAlignment);
		SetDataToTable(ui.tableWidget,0,5,(int)Res->ExecTime.TM_ExecutePreProcessing);
		SetDataToTable(ui.tableWidget,0,6,(int)(Res->ExecTime.TM_ExecuteProcessing+Res->ExecTime.TM_ExecuteProcessingRevived));
		SetDataToTable(ui.tableWidget,0,7,(int)Res->ExecTime.TM_ExecutePostProcessing);
		SetDataToTable(ui.tableWidget,0,8,/**/"");
		SetDataToTable(ui.tableWidget,0,9,/**/"");
		SetDataToTable(ui.tableWidget,0,10,/**/"");
		int	Dtm	=Res->ExecTime.TM_ExecutePreAlignment
				+Res->ExecTime.TM_ExecuteAlignment
				+Res->ExecTime.TM_ExecutePreProcessing
				+Res->ExecTime.TM_ExecuteProcessing
				+Res->ExecTime.TM_ExecuteProcessingRevived
				+Res->ExecTime.TM_ExecutePostProcessing;
		SetDataToTable(ui.tableWidget,0,11,Dtm);
	}
	for(int page=0;page<GetPageNumb();page++){
		int	Index;
		for(Index=0;Index<AlgorithmCount;Index++){
			if(ListByPage[Index][page].DLLRoot==L->GetDLLRoot()
			&& ListByPage[Index][page].DLLName==L->GetDLLName())
				break;
		}
		if(Index>=AlgorithmCount)
			continue;
		ExecuteTimeAlgorithm	*p=&ListByPage[Index][page];
		SetDataToTable(ui.tableWidget,page+1,0,(int)FilterTimeInPage[page]);
		SetDataToTable(ui.tableWidget,page+1,1,(int)p->GetMilisecExecuteInitialAfterEdit());
		SetDataToTable(ui.tableWidget,page+1,2,(int)p->GetMilisecExecuteStartByInspection());
		SetDataToTable(ui.tableWidget,page+1,3,(int)p->GetMilisecExecutePreAlignment());
		SetDataToTable(ui.tableWidget,page+1,4,(int)p->GetMilisecExecuteAlignment());
		SetDataToTable(ui.tableWidget,page+1,5,(int)p->GetMilisecExecutePreProcessing());
		SetDataToTable(ui.tableWidget,page+1,6,(int)p->GetMilisecExecuteProcessing());
		SetDataToTable(ui.tableWidget,page+1,7,(int)p->GetMilisecExecutePostProcessing());
		SetDataToTable(ui.tableWidget,page+1,8,(int)p->GetMilisecExecutePreScanning());
		SetDataToTable(ui.tableWidget,page+1,9,(int)p->GetMilisecExecuteScanning());
		SetDataToTable(ui.tableWidget,page+1,10,(int)p->GetMilisecExecutePostScanning());
		int	Dtm	=p->GetMilisecExecuteStartByInspection()
				+p->GetMilisecExecutePreAlignment()
				+p->GetMilisecExecuteAlignment()
				+p->GetMilisecExecutePreProcessing()
				+p->GetMilisecExecuteProcessing()
				+p->GetMilisecExecutePostProcessing();

		SetDataToTable(ui.tableWidget,page+1,11,Dtm);
	}
	delete	[]FilterTimeInPage;
}

void ListboxProcessTimeForm::on_pushButtonClear_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqClearProcessTime	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
	on_pushButtonView_clicked();
}

void ListboxProcessTimeForm::on_tableWidgetAlgorithm_clicked(const QModelIndex &)
{
	on_pushButtonView_clicked();
}

//=============================================================================

GUICmdReqProcessTime::GUICmdReqProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqProcessTime::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendProcessTime	*SendBack=GetSendBack(GUICmdSendProcessTime,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->MakeData(localPage);
	SendBack->FilterTime=GetLayersBase()->GetMilisecExecuteFilter();
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendProcessTime::GUICmdSendProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AlgorithmCount	=0;
	ExecuteTimeData	=NULL;
}
GUICmdSendProcessTime::~GUICmdSendProcessTime(void)
{
	if(ExecuteTimeData!=NULL)
		delete	[]ExecuteTimeData;
	ExecuteTimeData=NULL;
}

void	GUICmdSendProcessTime::MakeData(int localPage)
{
	int	iAlgorithmCount	=GetLayersBase()->GetLogicDLLBase()->GetDLLCounts();
	if(AlgorithmCount!=iAlgorithmCount){
		if(ExecuteTimeData!=NULL)
			delete	[]ExecuteTimeData;
		AlgorithmCount=iAlgorithmCount;
		ExecuteTimeData	=new ExecuteTimeAlgorithm[AlgorithmCount];
	}
	int	Row=0;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		ExecuteTimeData[Row]=L->GetInstance()->GetPageData(localPage)->GetExecuteTime();
		ExecuteTimeData[Row].DLLRoot=L->GetDLLRoot();
		ExecuteTimeData[Row].DLLName=L->GetDLLName();
	}
}

bool	GUICmdSendProcessTime::Load(QIODevice *f)
{
	int	iAlgorithmCount;
	if(::Load(f,iAlgorithmCount)==false)
		return false;
	if(AlgorithmCount!=iAlgorithmCount){
		if(ExecuteTimeData!=NULL)
			delete	[]ExecuteTimeData;
		AlgorithmCount=iAlgorithmCount;
		ExecuteTimeData	=new ExecuteTimeAlgorithm[AlgorithmCount];
	}
	for(int i=0;i<AlgorithmCount;i++){
		if(ExecuteTimeData[i].Load(f)==false){
			return false;
		}
	}
	if(::Load(f,FilterTime)==false)
		return false;
	return true;
}
bool	GUICmdSendProcessTime::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmCount)==false)
		return false;
	for(int i=0;i<AlgorithmCount;i++){
		if(ExecuteTimeData[i].Save(f)==false){
			return false;
		}
	}
	if(::Save(f,FilterTime)==false)
		return false;
	return true;
}

void	GUICmdSendProcessTime::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


GUICmdReqClearProcessTime::GUICmdReqClearProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqClearProcessTime::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->GetInstance()->GetPageData(localPage)->ClearExecuteTime();
	}
	GetLayersBase()->ClearMilisecExecuteFilter();
}

