#include "ShowBindNGNamingListForm.h"
#include "ui_ShowBindNGNamingListForm.h"
#include "XGeneralFunc.h"
#include "XShowBindNGNamingPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowBindNGNamingListForm::ShowBindNGNamingListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowBindNGNamingListForm)
{
    ui->setupUi(this);
	NGData	=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowBindNGNamingListForm::~ShowBindNGNamingListForm()
{
    delete ui;
	if(NGData!=NULL){
		delete	[]NGData;
		NGData=NULL;
	}
}

void	ShowBindNGNamingListForm::Prepare(void)
{
	ShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());

	if(NGData!=NULL){
		delete	[]NGData;
		NGData=NULL;
	}
	int	PhaseNumb=GetPhaseNumb();
	NGData=new NGAreaListContainer[PhaseNumb];
}

void	ShowBindNGNamingListForm::ResizeAction()
{
	ui->tableWidgetTotal->setGeometry(0,height()-ui->tableWidgetTotal->height()
									  ,width(),ui->tableWidgetTotal->height());
	ui->tableWidgetNGArea->resize(width(),height()-ui->tableWidgetTotal->height()-1);

	ui->tableWidgetTotal->setRowCount(1);
	int	PhaseNumb=GetPhaseNumb();
	ui->tableWidgetNGArea	->setColumnCount(PhaseNumb);
	ui->tableWidgetTotal	->setColumnCount(PhaseNumb+1);
	int Percentage=100/PhaseNumb;
	for(int phase=0;phase<PhaseNumb;phase++){
		::SetColumnWidthInTable(ui->tableWidgetNGArea ,phase, Percentage);
	}
	Percentage=100/(PhaseNumb+1);
	for(int phase=0;phase<PhaseNumb;phase++){
		::SetColumnWidthInTable(ui->tableWidgetTotal  ,phase, Percentage);
	}
	::SetColumnWidthInTable(ui->tableWidgetTotal  ,PhaseNumb, Percentage);
}

void	ShowBindNGNamingListForm::OnTheWayInPlayer(int64 shownInspectionID)
{
	ShowInPlayer(shownInspectionID);
}
void	ShowBindNGNamingListForm::ShowInPlayer(int64 shownInspectionID)
{
	if(NGData==NULL)
		return;

	int	PhaseNumb=GetPhaseNumb();
	int Percentage=100/PhaseNumb;
	for(int phase=0;phase<PhaseNumb;phase++){
		NGData[phase].RemoveAll();
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqNGNamingPhaseList	CmdReq(GetLayersBase(),sRoot,sName,page);
			CmdReq.ShownInspectionID=shownInspectionID;
			CmdReq.Phase=phase;
			GUICmdSendNGNamingPhaseList	CmdAck(GetLayersBase(),sRoot,sName,page);
			if(CmdReq.Send(page ,0,CmdAck)==true){
				NGAreaList *e;
				while((e=CmdAck.NGData.GetFirst())!=NULL){
					CmdAck.NGData.RemoveList(e);
					NGAreaList *c=NGData[phase].Search(e->GetAreaName());
					if(c==NULL){
						NGData[phase].AppendList(e);
					}
					else{
						c->SetNGCount(c->GetNGCount()+e->GetNGCount());
						delete	e;
					}
				}
			}
		}
	}
	NGNameContainer.RemoveAll();
	for(int phase=0;phase<PhaseNumb;phase++){
		for(NGAreaList *c=NGData[phase].GetFirst();c!=NULL;c=c->GetNext()){
			bool	Found=false;
			for(NGListInAreaName *q=NGNameContainer.GetFirst();q!=NULL;q=q->GetNext()){
				if(q->AreaPoint->GetAreaName()==c->GetAreaName()){
					if(q->PhaseList.IsInclude(phase)==false){
						q->PhaseList.Add(phase);
					}
					Found=true;
					break;
				}
			}
			if(Found==false){
				NGListInAreaName *q=new NGListInAreaName();
				q->AreaPoint=c;
				q->PhaseList.Add(phase);
				NGNameContainer.AppendList(q);
			}
		}
	}

	int	LNumb=NGNameContainer.GetNumber();
	ui->tableWidgetNGArea->setRowCount(LNumb);
	ui->tableWidgetNGArea->clearSelection();
	ui->tableWidgetNGArea->setUpdatesEnabled(false);

	int	PhaseCount[1000];
	for(int phase=0;phase<PhaseNumb;phase++){
		PhaseCount[phase]=0;
	}
	int	MultiPhase=0;
	int	row=0;
	for(NGListInAreaName *e=NGNameContainer.GetFirst();e!=NULL;e=e->GetNext(),row++){
		for(int phase=0;phase<PhaseNumb;phase++){
			if(e->PhaseList.IsInclude(phase)==false){
				::SetDataToTable(ui->tableWidgetNGArea, phase, row, /**/"");
			}
		}
		for(IntClass *v=e->PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int	Phase=v->GetValue();
			::SetDataToTable(ui->tableWidgetNGArea, Phase, row, e->AreaPoint->GetAreaName());
			PhaseCount[Phase]++;
		}
		if(e->PhaseList.GetCount()>1){
			MultiPhase++;
		}
	}
	ui->tableWidgetNGArea->setUpdatesEnabled(true);

	ui->tableWidgetTotal->setUpdatesEnabled(false);
	for(int phase=0;phase<PhaseNumb;phase++){
		::SetDataToTable(ui->tableWidgetTotal, phase, 0, QString::number(PhaseCount[phase]));
	}
	::SetDataToTable(ui->tableWidgetTotal, PhaseNumb, 0, QString::number(NGNameContainer.GetNumber()));
	ui->tableWidgetTotal->setUpdatesEnabled(true);
}

