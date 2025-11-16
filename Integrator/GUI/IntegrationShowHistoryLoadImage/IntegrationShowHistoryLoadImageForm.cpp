#include "IntegrationShowHistoryLoadImageResource.h"
#include "IntegrationShowHistoryLoadImageForm.h"
#include "ui_IntegrationShowHistoryLoadImageForm.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

InspectionLine::InspectionLine(void)
{
	for(int i=0;i<sizeof(InspectionPointer)/sizeof(InspectionPointer[0]);i++){
		InspectionPointer[i]=NULL;
	}
}

XDateTime	InspectionLine::GetTime(void)
{
	for(int i=0;i<sizeof(InspectionPointer)/sizeof(InspectionPointer[0]);i++){
		if(InspectionPointer[i]!=NULL){
			return InspectionPointer[i]->InspectionTime;
		}
	}
	return XDateTime();
}
bool	InspectionLine::IsAllOK(void)
{
	for(int i=0;i<sizeof(InspectionPointer)/sizeof(InspectionPointer[0]);i++){
		if(InspectionPointer[i]!=NULL){
			if(InspectionPointer[i]->GetNGCount()>0){
				return false;
			}
		}
	}
	return true;
}

IntegrationShowHistoryLoadImageForm::IntegrationShowHistoryLoadImageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationShowHistoryLoadImageForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	DefaultNGOnly	=true;

	labelFileNameS0Height=0;
	for(int i=0;i<sizeof(Image)/sizeof(Image[0]);i++){
		Image[i]=NULL;
	}
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationShowHistoryLoadImageForm::~IntegrationShowHistoryLoadImageForm()
{
    delete ui;
}

void	IntegrationShowHistoryLoadImageForm::Prepare(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount();
		int	H=4+(ui->labelS0->height()+4)*N +ui->labelTotal->height();
		ui->frameBottom->resize(width(),H);

		int	n=0;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),n++){
			{
				QLabel	*SLabel=new QLabel();
				SLabel->setParent(ui->frameBottom);
				SLabel->setText(m->GetMachineName());
				int	x=ui->labelS0->geometry().left();
				int	y=ui->labelS0->height()*n+4 ;
				int	w=ui->labelS0->width();
				int	h=ui->labelS0->height();
				SLabel->setGeometry(x,y ,w,h);
			}
			{
				FileNameLabel[n]=new QLabel();
				FileNameLabel[n]->setParent(ui->frameBottom);
				FileNameLabel[n]->setText(/**/"");
				int	x=ui->labelFileNameS0->geometry().left();
				int	y=ui->labelFileNameS0->height()*n+4 ;
				int	w=ui->labelFileNameS0->width();	//-ui->labelS0->width()-4;
				int	h=ui->labelFileNameS0->height();
				FileNameLabel[n]->setGeometry(x,y,w,h);
			}
		}
		labelFileNameS0Height=ui->labelFileNameS0->height();
		delete	ui->labelS0;
		ui->labelS0=NULL;
		delete	ui->labelFileNameS0;
		ui->labelFileNameS0=NULL;
	}
	ui->toolButtonOnlyNG->setCheckable(true);
	ui->toolButtonOnlyNG->setChecked(DefaultNGOnly);
}
void	IntegrationShowHistoryLoadImageForm::ResizeAction()
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	MCount=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount();
		int	H=labelFileNameS0Height*MCount+4+4+ui->labelTotal->height();
		ui->toolButtonOnlyNG->move(0,H-ui->toolButtonOnlyNG->height());
		ui->labelTotal		->setGeometry(ui->toolButtonOnlyNG->width(),H-ui->labelTotal->height(),width()-100,ui->labelTotal->height());
		ui->labelTotalCount	->setGeometry(width()-100+4,H-ui->labelTotal->height(),92,ui->labelTotal->height());
		ui->frameBottom->setGeometry(0,height()-H,width(),H);

		ui->tableWidget->resize(width(),height()-H);
	}
}

struct	InspectionStruct
{
	InspectionList	*Inspection;
	EachMaster		*Master;
};

int	InspectionStructFunc(const void *a ,const void *b)
{
	struct	InspectionStruct	*aa=(struct	InspectionStruct *)a;
	struct	InspectionStruct	*bb=(struct	InspectionStruct *)b;

	XDateTime	At1=aa->Inspection->InspectionTime.addSecs(aa->Master->GetSlave()->MinAdditionalSec);
	XDateTime	At2=aa->Inspection->InspectionTime.addSecs(aa->Master->GetSlave()->MaxAdditionalSec);
	XDateTime	Bt1=bb->Inspection->InspectionTime.addSecs(bb->Master->GetSlave()->MinAdditionalSec);
	XDateTime	Bt2=bb->Inspection->InspectionTime.addSecs(bb->Master->GetSlave()->MaxAdditionalSec);
	
	if(At2<Bt1)
		return -1;
	if(Bt2<At1)
		return 1;
	if(At1<Bt1)
		return -1;
	if(Bt1<At1)
		return 1;
	int	n=aa->Master->GetMachineCode()-bb->Master->GetMachineCode();
	return n;
}

struct	InspectionByMachine
{
	NPListPack<InspectionListPointer>	InspectionPointer;
	EachMaster		*Master;
};

void	IntegrationShowHistoryLoadImageForm::StartLot	(void)
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationShowHistoryLoadImageForm_LS,LID_0)/*"Loading Lot dat"*/);
	GetLayersBase()->SetMaxProcessing(-1);
	int	IndexMachine=0;
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		struct	InspectionByMachine	*IByMachine=new struct	InspectionByMachine[GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount()];
		
		int	MaxID=0;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			IByMachine[IndexMachine].Master=m;
			for(InspectionList *s=m->GetCurrentInspection().GetFirst();s!=NULL;s=s->GetNext()){
				if(s->ID>MaxID){
					MaxID=s->ID;
				}
				IByMachine[IndexMachine].InspectionPointer.AppendList(new InspectionListPointer(s));
			}
			//IByMachine[IndexMachine].Current=IByMachine[IndexMachine].InspectionPointer.GetFirst();
			IndexMachine++;
		}
		Inspections.RemoveAll();
		for(int InspectionID=0;InspectionID<=MaxID;InspectionID++){
			InspectionLine	*L=new InspectionLine();
			L->ID=InspectionID;
			int	DataCount=0;
			for(int i=0;i<IndexMachine;i++){
				for(InspectionListPointer *s=IByMachine[i].InspectionPointer.GetFirst();s!=NULL;s=s->GetNext()){
					if(s->Pointer->ID==InspectionID){
						L->InspectionPointer[i]=s->Pointer;
						DataCount++;
						break;
					}
				}
			}
			if(DataCount>0)
				Inspections.AppendList(L);
			else
				delete	L;
		}
		delete	[]IByMachine;
	}
	if(ui->toolButtonOnlyNG->isChecked()==true){
		for(InspectionLine *L=Inspections.GetFirst();L!=NULL;){
			InspectionLine *Next=L->GetNext();
			if(L->IsAllOK()==true){
				Inspections.RemoveList(L);
				delete	L;
			}
			L=Next;
		}
	}
	
	int	Row=0;
	ui->tableWidget->setColumnCount(2+GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount());
	ui->tableWidget->setRowCount(Inspections.GetCount());
	ui->tableWidget->setColumnWidth(0,130);
	ui->tableWidget->setColumnWidth(1,36);
	int	ColWidth=(ui->tableWidget->width()-166-80)/GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount();
	QStringList	HLabels;
	HLabels.append(LangSolver.GetString(IntegrationShowHistoryLoadImageForm_LS,LID_1)/*"Time"*/);
	HLabels.append(LangSolver.GetString(IntegrationShowHistoryLoadImageForm_LS,LID_2)/*"No"*/);
	int	row=0;
	for(EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),row++){
		HLabels.append(m->GetMachineName());
		ui->tableWidget->setColumnWidth(2+row,ColWidth);
	}
	ui->tableWidget->setHorizontalHeaderLabels(HLabels);

	for(InspectionLine *L=Inspections.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget,0 ,Row ,L->GetTime().toString(/**/"yyMMdd-hhmmss"));
		::SetDataToTable(ui->tableWidget,1 ,Row ,QString::number(L->ID));
		int	Col=0;
		for(EachMaster	*k=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();k!=NULL;k=k->GetNext(),Col++){
			//::SetDataToTable(ui->tableWidget,1+Col ,Row ,QString(/**/""));
			QTableWidgetItem *L=ui->tableWidget->item ( Row, Col+2);
			if(L==NULL){
				L=new QTableWidgetItem();
				ui->tableWidget->setItem(Row,Col+2,L);
			}
			L->setText(/**/"");
		}

		for(int i=0;i<IndexMachine;i++){
			if(L->InspectionPointer[i]!=NULL){
				int	NGCount=L->InspectionPointer[i]->GetNGCount();
				EachMaster	*m=L->InspectionPointer[i]->GetMaster();
				int	Col=0;
				for(EachMaster	*k=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();k!=NULL;k=k->GetNext(),Col++){
					if(m->GetMachineCode()==k->GetMachineCode()){
						break;
					}
				}
				if(NGCount==0){
					::SetTableColor(ui->tableWidget,2+Col ,Row ,Qt::white);
					::SetDataToTable(ui->tableWidget,2+Col ,Row ,QString(LangSolver.GetString(IntegrationShowHistoryLoadImageForm_LS,LID_3)/*"OK"*/));
				}
				else{
					::SetTableColor(ui->tableWidget,2+Col ,Row ,Qt::red);
					::SetDataToTable(ui->tableWidget,2+Col ,Row ,QString(LangSolver.GetString(IntegrationShowHistoryLoadImageForm_LS,LID_4)/*"NG"*/));
				}
			}
		}
	}
	ui->labelTotalCount->setText(QString::number(Row));

	GetLayersBase()->CloseProcessingForm();
}
void IntegrationShowHistoryLoadImageForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	QTableWidgetItem *Item=ui->tableWidget->currentItem ();
	if(Item==NULL)
		return;
	int	Row=Item->row();
	int	Col=Item->column();

	InspectionLine *L=Inspections[Row];
	if(L==NULL)
		return;
	InspectionList *p=L->InspectionPointer[Col-2];
	if(p==NULL)
		return;
	if(p->FileName.isEmpty()==true)
		p->FileName=p->RemarkData;
	QString	FileName=p->FileName;

	p->GetMaster()->LoadTargetImage(p,FileName);

	int	n=0;
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),n++){
		if(n==Col-2){
			QFileInfo	FInfo(FileName);
			//FileNameLabel[n]->setText(FInfo.fileName());
			FileNameLabel[n]->setText(FileName);
		}
		else{
			FileNameLabel[n]->setText(/**/"");
		}
	}

	CmdLoadedImage	RCmd;
	RCmd.Pointer=p;
	BroadcastSpecifiedDirectly(&RCmd);
}

void	IntegrationShowHistoryLoadImageForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdReqUpdateHistory	*CmdReqUpdateHistoryVar=dynamic_cast<CmdReqUpdateHistory *>(v);
	if(CmdReqUpdateHistoryVar!=NULL){
		StartLot();
		return;
	}
}

void IntegrationShowHistoryLoadImageForm::on_toolButtonOnlyNG_clicked()
{
	StartLot();
}
