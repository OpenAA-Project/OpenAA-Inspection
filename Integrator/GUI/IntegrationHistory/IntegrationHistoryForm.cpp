#include "IntegrationHistoryResource.h"
#include "IntegrationHistoryForm.h"
#include "ui_IntegrationHistoryForm.h"
#include "XGeneralFunc.h"
#include "IntegrationStackNGThumbnailForm.h"
#include "XIntegrationStackNGThumbnailPacket.h"

IntegrationHistoryForm::IntegrationHistoryForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationHistoryForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	CurrentOKCount	=0;
	AllocatedCount	=20;
	IDDim			=NULL;
	ScrollerWidth	=48;
	ShowOnlyNG		=false;
	ShowTotal		=true;

	ui->tableWidgetHistory->setColumnWidth(0,120);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationHistoryForm::~IntegrationHistoryForm()
{
    delete ui;
	if(IDDim!=NULL){
		delete	[]IDDim;
		IDDim=NULL;
	}
}
void	IntegrationHistoryForm::Prepare(void)
{
	ui->tableWidgetHistory->setFont(CharFont);
	ui->label_Total		->setFont(CharFont);
	ui->label_OK		->setFont(CharFont);
	ui->label_NG		->setFont(CharFont);
	ui->label_TitleTotal->setFont(CharFont);
	ui->label_TitleOK	->setFont(CharFont);
	ui->label_TitleNG	->setFont(CharFont);
	IDDim=new int[AllocatedCount];
	ui->tableWidgetHistory->setRowCount(AllocatedCount);

	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		int	IndependentMachineCount=0;
		for(int i=0;i<MachineCount;i++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL && m->IsDependent()==false){
				IndependentMachineCount++;
			}
		}

		ui->tableWidgetHistory->setColumnCount(IndependentMachineCount+1);
		for(int i=0;i<IndependentMachineCount;i++){
			ui->tableWidgetHistory->setColumnWidth(i+1,50);
		}
		for(int row=0;row<AllocatedCount;row++){
			::SetDataToTable(ui->tableWidgetHistory ,0,row ,/**/"");
			for(int i=0;i<IndependentMachineCount;i++){
				::SetDataToTable(ui->tableWidgetHistory ,i+1,row ,/**/"");
			}
		}
		QStringList	SlaveLabels;
		SlaveLabels.append(LangSolver.GetString(IntegrationHistoryForm_LS,LID_0)/*"Time"*/);
		for(int i=0;i<MachineCount;i++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL && m->IsDependent()==false){
				SlaveLabels.append(m->GetMachineName());
			}
			//else{
			//	SlaveLabels.append(/**/"");
			//}
		}
		ui->tableWidgetHistory->setHorizontalHeaderLabels(SlaveLabels);
	}
}

void	IntegrationHistoryForm::ResizeAction()
{
	if(ShowTotal==true){
		ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
		ui->tableWidgetHistory	->resize(width(),height()-ui->frame->height());
	}
	else{
		ui->frame->setVisible(false);
		ui->tableWidgetHistory	->resize(width(),height());
	}
	int	W=ui->tableWidgetHistory->width()-ScrollerWidth-48-60;
	if(W<=30)
		W=30;
	int	MachineCount		=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	int	SpecialColumnCount	=SpecialHistoryColumnContainer.GetCount();

	int	IndependentMachineCount=0;
	for(int i=0;i<MachineCount;i++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL && m->IsDependent()==false){
			IndependentMachineCount++;
		}
	}
	ui->tableWidgetHistory->setColumnWidth(0,60);
	if((IndependentMachineCount+SpecialColumnCount)!=0){
		int	LW=W/(IndependentMachineCount+SpecialColumnCount);
		for(int i=0;i<(IndependentMachineCount+SpecialColumnCount);i++){
			ui->tableWidgetHistory->setColumnWidth(1+i,LW);
		}
	}

	QString	s=QString(/**/"QScrollBar:vertical { width: ")
			+ QString::number(ScrollerWidth)
			+ QString(/**/"px; }");
	ui->tableWidgetHistory->setStyleSheet(s);
}
void IntegrationHistoryForm::on_tableWidgetHistory_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetHistory->currentRow();
	if(Row<0)
		return;
	CmdSelectResult	ICmd;
	ICmd.ResultID=IDDim[Row];
	if(ICmd.ResultID>=0){
		BroadcastSpecifiedDirectly(&ICmd);
	}
}
void	IntegrationHistoryForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdReqUpdateHistory	*CmdReqUpdateHistoryVar=dynamic_cast<CmdReqUpdateHistory *>(v);
	if(CmdReqUpdateHistoryVar!=NULL){
		if(CmdReqUpdateHistoryVar->SlaveNo>=0){
			ShowList();
		}
		return;
	}
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdChangeLotIDVar!=NULL){
		StartLot();
		return;
	}
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	if(CmdChangeNewLotIDVar!=NULL){
		ShowList();
		return;
	}
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		ClearList();
		return;
	}
}

void	IntegrationHistoryForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddSpecialHistoryColumnPacket	*CmdAddSpecialHistoryColumnPacketVar=dynamic_cast<CmdAddSpecialHistoryColumnPacket *>(packet);
	if(CmdAddSpecialHistoryColumnPacketVar!=NULL){
		SpecialHistoryColumnContainer.AppendList(CmdAddSpecialHistoryColumnPacketVar->NewColumn);
		int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		int	SpecialColumnCount=SpecialHistoryColumnContainer.GetCount();

		int	IndependentMachineCount=0;
		for(int i=0;i<MachineCount;i++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL && m->IsDependent()==false){
				IndependentMachineCount++;
			}
		}
		QStringList	Labels;
		for(int i=0;i<ui->tableWidgetHistory->columnCount() && i<(IndependentMachineCount+1);i++){
			QTableWidgetItem *H=ui->tableWidgetHistory->horizontalHeaderItem(i);
			if(H!=NULL){
				Labels.append(H->text());
			}
		}
		Labels.append(CmdAddSpecialHistoryColumnPacketVar->NewColumn->ColumnName);
		ui->tableWidgetHistory->setColumnCount(Labels.count());
		ui->tableWidgetHistory->setHorizontalHeaderLabels(Labels);

		ResizeAction();
		return;
	}
	CmdPressLine	*CmdPressLineVar=dynamic_cast<CmdPressLine *>(packet);
	if(CmdPressLineVar!=NULL){
		for(int	Row=0;Row<AllocatedCount;Row++){
			if(IDDim[Row]==CmdPressLineVar->InspectionID){
				::SetCurrentRow(ui->tableWidgetHistory,Row);
				break;
			}
		}
		return;
	}
}

void	IntegrationHistoryForm::StartLot(void)
{
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		LotList	*L=m->GetCurrentLot();
		m->AppendSelectLot(L);
	}
	int	Col=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount();
	
	ClearList();
	ShowList();
}

void	IntegrationHistoryForm::ClearList(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		for(int row=0;row<AllocatedCount;row++){
			::SetDataToTable(ui->tableWidgetHistory ,0,row ,/**/"");
			int	ColumnCount=ui->tableWidgetHistory->columnCount();
			for(int i=1;i<ColumnCount;i++){
				::SetDataToTable(ui->tableWidgetHistory ,i,row ,/**/"");
				::SetTableColor	(ui->tableWidgetHistory ,i,row ,Qt::white);
			}
		}
	}
}

void IntegrationHistoryForm::ShowList(void)
{
	int	IndependentMachineCount=0;
	CurrentOKCount	=0;
	TMOutCount		=0;
	MaxID=0;
	int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	ID=0;
		if(m->GetCurrentInspection().GetLast()!=NULL){
			ID=m->GetCurrentInspection().GetLast()->ID;
		}
		if(MaxID<ID){
			MaxID=ID;
		}
	}
	int	Col=0;
	InspectionList	*MPointer[100][2];
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL && Col<100;m=m->GetNext()){
		if(m->IsDependent()==false){
			MPointer[Col][0]=m->GetCurrentInspection().GetLast();
			MPointer[Col][1]=NULL;
			Col++;
			IndependentMachineCount++;
		}
		else{
			if(Col>0){
				MPointer[Col-1][1]=m->GetCurrentInspection().GetLast();
			}
		}
	}
	//ui->tableWidgetHistory->setRowCount(MaxID+1);
	for(int i=0;i<AllocatedCount;i++){
		IDDim[i]=-1;
	}
	int	Row=0;
	for(int ID=MaxID;ID>=0 && Row<AllocatedCount;ID--){
		XDateTime	InspectionTime;
		for(int i=0;i<Col;i++){
			if(MPointer[i][0]!=NULL && MPointer[i][0]->ID==ID){
				InspectionTime=MPointer[i][0]->InspectionTime;
				break;
			}
			if(MPointer[i][1]!=NULL && MPointer[i][1]->ID==ID){
				InspectionTime=MPointer[i][1]->InspectionTime;
				break;
			}
		}
		bool	OK=true;
		bool	TimeOut[100];
		bool	ColumnOK[100];
		InspectionList	*CurrentPointer[100][2];
		for(int i=0;i<Col;i++){
			CurrentPointer[i][0]=MPointer[i][0];
			CurrentPointer[i][1]=MPointer[i][1];
			ColumnOK[i]=true;
			TimeOut[i]=false;
			if(MPointer[i][0]!=NULL && MPointer[i][0]->ID==ID){
				if(MPointer[i][0]->GetNGCount()!=0){
					ColumnOK[i]=false;
					OK=false;
				}
				if(MPointer[i][0]->Result==100){
					TimeOut[i]=true;
					OK=false;
				}
				MPointer[i][0]=MPointer[i][0]->GetPrev();
			}
			else
			if(MPointer[i][1]!=NULL && MPointer[i][1]->ID==ID){
				if(MPointer[i][1]->GetNGCount()!=0){
					ColumnOK[i]=false;
					OK=false;
				}
				if(MPointer[i][1]->Result==100){
					TimeOut[i]=true;
					OK=false;
				}
				MPointer[i][1]=MPointer[i][1]->GetPrev();
			}
		}
		bool	TMOut=false;
		if(ShowOnlyNG==false || (ShowOnlyNG==true && OK==false)){
			::SetDataToTable(ui->tableWidgetHistory ,0,Row ,InspectionTime.toString(/**/"hh:mm:ss"));
			for(int i=0;i<Col;i++){
				if(TimeOut[i]==true){
					::SetDataToTable(ui->tableWidgetHistory ,i+1,Row ,/**/"TMO");
					::SetTableColor	(ui->tableWidgetHistory ,i+1,Row ,Qt::yellow);
					TMOut=true;
				}
				else if(ColumnOK[i]==true){
					::SetDataToTable(ui->tableWidgetHistory ,i+1,Row ,/**/"OK");
					::SetTableColor	(ui->tableWidgetHistory ,i+1,Row ,Qt::white);
				}
				else{
					::SetDataToTable(ui->tableWidgetHistory ,i+1,Row ,/**/"NG");
					::SetTableColor	(ui->tableWidgetHistory ,i+1,Row ,Qt::red);
				}
			}

			int	sCol=Col;
			QColor ColumnColor;
			for(SpecialHistoryColumn *L=SpecialHistoryColumnContainer.GetFirst();L!=NULL;L=L->GetNext(),sCol++){
				::SetDataToTable(ui->tableWidgetHistory ,sCol+1,Row ,L->JudgeFunc(CurrentPointer,IndependentMachineCount,ColumnColor));
				::SetTableColor	(ui->tableWidgetHistory ,sCol+1,Row ,ColumnColor);
			}

			IDDim[Row]=ID;
			Row++;
		}
		if(OK==true){
			CurrentOKCount++;
		}
		if(TMOut==true){
			TMOutCount++;
		}
	}
	ui->label_Total	->setText(QString::number(MaxID+1));
	ui->label_OK	->setText(QString::number(CurrentOKCount));
	ui->label_NG	->setText(QString::number(MaxID+1-CurrentOKCount));
	ui->label_TMOut	->setText(QString::number(TMOutCount));
}
