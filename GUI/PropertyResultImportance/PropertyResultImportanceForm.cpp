#include "PropertyResultImportanceResource.h"
#include "PropertyResultImportanceForm.h"
#include "ui_PropertyResultImportanceForm.h"
#include "editimportanceform.h"
#include "XResultImportancePacket.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include <QColorDialog>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyResultImportanceForm::PropertyResultImportanceForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::PropertyResultImportanceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->tableWidgetImportanceList->setColumnWidth (0,150);
	ui->tableWidgetImportanceList->setColumnWidth (1,150);

	ui->tableWidgetAreaList->setColumnWidth (0,40);
	ui->tableWidgetAreaList->setColumnWidth (1,200);
	ui->tableWidgetAreaList->setColumnWidth (2,80);

	PointerList=NULL;
	ResultImportanceColor=QColor(Qt::red);

	connect(ui->tbImportanceColor,SIGNAL(clicked()),this,SLOT(tbImportanceColorClicked()));
	GetParamGUI()->SetParam(&ResultImportanceColor,/**/"PropertyResultImportanceForm",/**/"ResultImportanceColor",LangSolver.GetString(PropertyResultImportanceForm_LS,LID_0)/*"Result Importance Color"*/);
}

PropertyResultImportanceForm::~PropertyResultImportanceForm()
{
	if(PointerList!=NULL){
		delete	[]PointerList;
		PointerList=NULL;
	}
    delete ui;
}
ResultImportanceBase	*PropertyResultImportanceForm::GetResultImportanceBase(void)
{
	return (ResultImportanceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ResultImportance");
}

void	PropertyResultImportanceForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdResultImportanceDrawEnd	*CmdResultImportanceDrawEndVar=dynamic_cast<CmdResultImportanceDrawEnd *>(packet);
	if(CmdResultImportanceDrawEndVar!=NULL){
		EditImportanceForm	D(GetLayersBase(),this);
		if(D.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdResultImportanceDrawEndVar->GlobalArea,PageList);
			if(PageList.GetFirst()==NULL){
				return;
			}
			for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
				int	globalPage=PageClass->GetValue();
				FlexArea	A;
				//A=GlobalPickupArea;
				A=CmdResultImportanceDrawEndVar->GlobalArea;
				GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

				GUICmdAddResultImportanceArea	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Area=A;
				RCmd.ImportanceLevel	=D.ImportanceLevel;
				RCmd.Send(NULL,globalPage,0);
			}
	
			ShowAreaGrid();
		}
	}
}

void	PropertyResultImportanceForm::BuildForShow(void)
{
	ShowAreaGrid();

	//StyleSheet?A?F?d?\?|
	SetBackgroundColor(ui->tbImportanceColor,ResultImportanceColor);

	//PixelInspection?E???‹?e
	SetResultImportanceColor(ResultImportanceColor);
}
void	PropertyResultImportanceForm::ShowInEdit(void)
{
	ShowAreaGrid();
}

int	PointerListFunc(const void *a ,const void *b)
{
	ResultImportanceList	**ai=(ResultImportanceList **)a;
	ResultImportanceList	**bi=(ResultImportanceList **)b;
	if(ai[0]->ImportanceLevel>bi[0]->ImportanceLevel){
		return -1;
	}
	if(ai[0]->ImportanceLevel<bi[0]->ImportanceLevel){
		return 1;
	}
	if(ai[0]->Page>bi[0]->Page){
		return -1;
	}
	if(ai[0]->Page<bi[0]->Page){
		return 1;
	}
	return 0;
}


void PropertyResultImportanceForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	ResultImportanceInfo.RemoveAll();

	GUICmdReqResultImportanceList	**BmpRequester=new GUICmdReqResultImportanceList*[GetParamGlobal()->PageNumb];
	GUICmdSendResultImportanceList	**BmpReceiver=new GUICmdSendResultImportanceList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpRequester[page]	=new GUICmdReqResultImportanceList	(GetLayersBase(),sRoot,sName,globalPage);
		BmpReceiver[page]	=new GUICmdSendResultImportanceList	(GetLayersBase(),sRoot,sName,globalPage);
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			ResultImportanceInfo+=BmpReceiver[page]->ResultImportanceInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	Numb=ResultImportanceInfo.GetNumber();

	if(PointerList!=NULL){
		delete	[]PointerList;
	}
	PointerList=new ResultImportanceList*[Numb];
	int	N=0;
	for(ResultImportanceList *a=ResultImportanceInfo.GetFirst();a!=NULL;a=a->GetNext()){
		PointerList[N]=a;
		N++;
	}
	QSort(PointerList,N,sizeof(PointerList[0]),PointerListFunc);

	ImportanceCounterContainer.RemoveAll();
	for(ResultImportanceList *a=ResultImportanceInfo.GetFirst();a!=NULL;a=a->GetNext()){
		ImportanceCounter *b;
		for(b=ImportanceCounterContainer.GetFirst();b!=NULL;b=b->GetNext()){
			if(a->ImportanceLevel==b->ImportanceLevel){
				break;
			}
		}
		if(b==NULL){
			b=new ImportanceCounter();
			b->ImportanceLevel=a->ImportanceLevel;
			ImportanceCounterContainer.AppendList(b);
		}
		b->Counter++;
	}
	ui->tableWidgetImportanceList->setRowCount(ImportanceCounterContainer.GetCount());
	N=0;
	for(ImportanceCounter *a=ImportanceCounterContainer.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidgetImportanceList,0,N,QString::number(a->ImportanceLevel));
		::SetDataToTable(ui->tableWidgetImportanceList,1,N,QString::number(a->Counter));
		N++;
	}

	ui->tableWidgetAreaList->setRowCount(Numb);
	for(int i=0;i<Numb;i++){
		ResultImportanceList	*a=PointerList[i];
		::SetDataToTable(ui->tableWidgetAreaList,0,i,QString::number(a->Page));

		QString	s=QString(/**/"(")
				+ QString::number(a->x1)+QString(/**/",")+QString::number(a->y1)
				+ QString(/**/")-(")
				+ QString::number(a->x2)+QString(/**/",")+QString::number(a->y2)
				+ QString(/**/")");
		::SetDataToTable(ui->tableWidgetAreaList ,1,i,s);

		SetDataToTable(ui->tableWidgetAreaList ,2,i,QString::number(a->ImportanceLevel));
	}

	ReEntrant=false;
}

void PropertyResultImportanceForm::on_tableWidgetImportanceList_doubleClicked(const QModelIndex &index)
{
	ImportanceCounter	*a=ImportanceCounterContainer[index.row()];
	if(a!=NULL){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdSelectResultImportance	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.ImportanceLevels.Add(a->ImportanceLevel);
			RCmd.Send(NULL,globalPage,0);
		}
	}
}

void PropertyResultImportanceForm::on_tableWidgetAreaList_clicked(const QModelIndex &index)
{
	ResultImportanceList *L=PointerList[index.row()];

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
	}
}

void PropertyResultImportanceForm::on_tableWidgetAreaList_doubleClicked(const QModelIndex &index)
{
	ResultImportanceList *L=PointerList[index.row()];
	EditImportanceForm	D(GetLayersBase(),this);
	D.SetImportanceLevel(L->ImportanceLevel);
	if(D.exec()==true){
		GUICmdChangeResultImportanceLevel	RCmd(GetLayersBase(),sRoot,sName,L->Page);
		RCmd.ImportanceLevel=D.ImportanceLevel;
		RCmd.ItemID=L->ItemID;
		RCmd.Send(NULL,L->Page,0);
		ShowAreaGrid();
	}
}

void PropertyResultImportanceForm::on_pushButtonSelectLines_clicked()
{
	IntList Rows;
	::GetSelectedRows(ui->tableWidgetImportanceList ,Rows);
		
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSelectResultImportance	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		for(IntClass *k=Rows.GetFirst();k!=NULL;k=k->GetNext()){
			ImportanceCounter	*a=ImportanceCounterContainer[k->GetValue()];
			if(a!=NULL){
				RCmd.ImportanceLevels.Add(a->ImportanceLevel);
			}
		}
		RCmd.Send(NULL,globalPage,0);
	}
}

void PropertyResultImportanceForm::tbImportanceColorClicked()
{
	//QColorDialog
	QColor C=QColorDialog::getColor(ResultImportanceColor);
	if(C.isValid()){
		//StyleSheet?A?F?d?\?|
		SetBackgroundColor(ui->tbImportanceColor,C);
		ResultImportanceColor=C;

		//PixelInspection?E???‹?e
		SetResultImportanceColor(C);

		//GUI?p?????[?^?E?U?÷
		GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
	}
}

void PropertyResultImportanceForm::SetBackgroundColor(QToolButton *Button,QColor C)
{
	//StyleSheet?A?F?d?\?|
	QString strStyleSheet=/**/"QToolButton { background-color: " + C.name() + /**/" }";
	Button->setStyleSheet(strStyleSheet);
}

void PropertyResultImportanceForm::SetResultImportanceColor(QColor C)
{
	//PixelInspection?E???‹?e
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PixelInspection");
	if(LBase!=NULL){
		CmdResultImportanceColor CmdPacket(GetLayersBase());
		CmdPacket.ResultImportanceColor=C;
		LBase->TransmitDirectly(&CmdPacket);
	}
}
