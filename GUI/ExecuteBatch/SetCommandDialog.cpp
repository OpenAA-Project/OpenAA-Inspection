#include "ExecuteBatchResource.h"
#include "SetCommandDialog.h"
#include "ui_SetCommandDialog.h"
#include "ExecuteBatchForm.h"
#include "XGUI.h"
#include "XGeneralFunc.h"

ComponentLine::ComponentLine(void)
{
	DLLGui		=NULL;
	DLLAlgo		=NULL;
	DLLResult	=NULL;
}
	
QString		ComponentLine::GetDLLRoot(void)
{
	if(DLLAlgo!=NULL){
		return DLLAlgo->GetDLLRoot();
	}
	else if(DLLResult!=NULL){
		return DLLResult->GetDLLRoot();
	}
	else if(DLLGui!=NULL){
		return DLLGui->GetForm()->GetDLLRoot();
	}
	return /**/"";
}

QString		ComponentLine::GetDLLName(void)
{
	if(DLLAlgo!=NULL){
		return DLLAlgo->GetDLLName();
	}
	else if(DLLResult!=NULL){
		return DLLResult->GetDLLName();
	}
	else if(DLLGui!=NULL){
		return DLLGui->GetForm()->GetDLLName();
	}
	return /**/"";
}

int		ComponentLine::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(DLLAlgo!=NULL){
		return DLLAlgo->RegistMacroFunction(Functions,MaxBuffer);
	}
	else if(DLLResult!=NULL){
		return DLLResult->RegistMacroFunction(Functions,MaxBuffer);
	}
	else if(DLLGui!=NULL){
		return DLLGui->GetForm()->RegistMacroFunction(Functions,MaxBuffer);
	}
	return 0;
}

SetCommandDialog::SetCommandDialog(LayersBase *Base ,ExecuteBatchForm *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,Parent(parent)
	,CurrentData(&parent->BatchData)
    ,ui(new Ui::SetCommandDialog)
{
    ui->setupUi(this);

	ui->tableWidgetComponent->setColumnWidth(0,80);
	ui->tableWidgetComponent->setColumnWidth(1,155);

	ui->tableWidgetCommand	->setColumnWidth(0,140);
	ui->tableWidgetCommand	->setColumnWidth(1,270);

		ArgumentStructTable[0].ArgLabel	=ui->labelArg1 ;
	ArgumentStructTable[1].ArgLabel	=ui->labelArg2 ;
	ArgumentStructTable[2].ArgLabel	=ui->labelArg3 ;
	ArgumentStructTable[3].ArgLabel	=ui->labelArg4 ;
	ArgumentStructTable[4].ArgLabel	=ui->labelArg5 ;
	ArgumentStructTable[5].ArgLabel	=ui->labelArg6 ;
	ArgumentStructTable[6].ArgLabel	=ui->labelArg7 ;
	ArgumentStructTable[7].ArgLabel	=ui->labelArg8 ;
	ArgumentStructTable[8].ArgLabel	=ui->labelArg9 ;
	ArgumentStructTable[9].ArgLabel	=ui->labelArg10;
	ArgumentStructTable[0].ArgName	=ui->lineEditArg1 ;
	ArgumentStructTable[1].ArgName	=ui->lineEditArg2 ;
	ArgumentStructTable[2].ArgName	=ui->lineEditArg3 ;
	ArgumentStructTable[3].ArgName	=ui->lineEditArg4 ;
	ArgumentStructTable[4].ArgName	=ui->lineEditArg5 ;
	ArgumentStructTable[5].ArgName	=ui->lineEditArg6 ;
	ArgumentStructTable[6].ArgName	=ui->lineEditArg7 ;
	ArgumentStructTable[7].ArgName	=ui->lineEditArg8 ;
	ArgumentStructTable[8].ArgName	=ui->lineEditArg9 ;
	ArgumentStructTable[9].ArgName	=ui->lineEditArg10;
	ArgumentStructTable[0].ArgValue	=ui->lineEditArg1_Value;
	ArgumentStructTable[1].ArgValue	=ui->lineEditArg2_Value;
	ArgumentStructTable[2].ArgValue	=ui->lineEditArg3_Value;
	ArgumentStructTable[3].ArgValue	=ui->lineEditArg4_Value;
	ArgumentStructTable[4].ArgValue	=ui->lineEditArg5_Value;
	ArgumentStructTable[5].ArgValue	=ui->lineEditArg6_Value;
	ArgumentStructTable[6].ArgValue	=ui->lineEditArg7_Value;
	ArgumentStructTable[7].ArgValue	=ui->lineEditArg8_Value;
	ArgumentStructTable[8].ArgValue	=ui->lineEditArg9_Value;
	ArgumentStructTable[9].ArgValue	=ui->lineEditArg10_Value;

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		QStringList CommandList;
		L->GetMacroNames(CommandList);
		if(CommandList.count()>0){
			ComponentLine	*C=new ComponentLine();
			C->DLLAlgo	=L;
			ComponentContainer.AppendList(C);
		}
	}
	for(GUIItemInstance *G=GetLayersBase()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();G!=NULL;G=G->GetNext()){
		GuiDLLItem	*g=G->DLLAccess;
		if(g==NULL)
			continue;
		QStringList CommandList;
		G->GetForm()->GetMacroNames(CommandList);
		if(CommandList.count()>0){
			ComponentLine	*C=new ComponentLine();
			C->DLLGui	=G;
			ComponentContainer.AppendList(C);
		}
	}
	for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
		QStringList CommandList;
		R->GetMacroNames(CommandList);
		if(CommandList.count()>0){
			ComponentLine	*C=new ComponentLine();
			C->DLLResult	=R;
			ComponentContainer.AppendList(C);
		}
	}
	ShowComponent();

	InstallOperationLog(this);
}

SetCommandDialog::~SetCommandDialog()
{
    delete ui;
}

void	SetCommandDialog::ShowComponent(void)
{
	ui->tableWidgetComponent	->setRowCount(ComponentContainer.GetCount());
	int	Row=0;
	for(ComponentLine *C=ComponentContainer.GetFirst();C!=NULL;C=C->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetComponent ,0,Row ,C->GetDLLRoot());
		::SetDataToTable(ui->tableWidgetComponent ,1,Row ,C->GetDLLName());
	}
}

void	SetCommandDialog::Initial(BatchLine &data)
{
	int	Row=0;
	ComponentLine *C=NULL;
	for(ComponentLine *c=ComponentContainer.GetFirst();c!=NULL;c=c->GetNext(),Row++){
		if(c->GetDLLRoot()==data.DLLRoot && c->GetDLLName()==data.DLLName){
			C=c;
			break;
		}
	}
	if(Row>=ComponentContainer.GetCount())
		return;
	ui->tableWidgetComponent->setCurrentCell(Row,0);
	ui->tableWidgetComponent->setCurrentCell(Row,1);

	ExportFuncForMacro Functions[100];
	if(C!=NULL){
		int	N=C->RegistMacroFunction(Functions,100);
		int	Index=-1;
		ui->tableWidgetCommand->setRowCount(N);
		for(int r=0;r<N;r++){
			::SetDataToTable(ui->tableWidgetCommand ,0,r ,Functions[r].FuncName);
			::SetDataToTable(ui->tableWidgetCommand ,1,r ,Functions[r].Explain);
			if(Functions[r].FuncName==data.CommandStr){
				ui->tableWidgetCommand->setCurrentCell(r,0);
				ui->tableWidgetCommand->setCurrentCell(r,1);
				Index=r;
			}
		}
		if(Index>=0){
			ShowExportFuncForMacro( Functions[Index]);

			for(int i=0;i<Functions[Index].ArgName.count() && i<sizeof(ArgumentStructTable)/sizeof(ArgumentStructTable[0]);i++){
				if(i>=data.ArgValues.count()){
					data.ArgValues.append(/**/"");
				}
				ArgumentStructTable[i].ArgValue->setText(data.ArgValues[i]);
			}
			for(int i=Functions[Index].ArgName.count();i<sizeof(ArgumentStructTable)/sizeof(ArgumentStructTable[0]);i++){
				ArgumentStructTable[i].ArgValue->setText(/**/"");
			}
		}
	}
}

void SetCommandDialog::on_tableWidgetComponent_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetComponent->currentRow();
	if(Row<0)
		return;
	ComponentLine *C=ComponentContainer[Row];
	if(C==NULL)
		return;
	ExportFuncForMacro Functions[100];
	int	N=C->RegistMacroFunction(Functions,100);

	ui->tableWidgetCommand->setRowCount(N);
	for(int r=0;r<N;r++){
		::SetDataToTable(ui->tableWidgetCommand ,0,r ,Functions[r].FuncName);
		::SetDataToTable(ui->tableWidgetCommand ,1,r ,Functions[r].Explain);
	}
}

void SetCommandDialog::on_tableWidgetCommand_clicked(const QModelIndex &index)
{
	on_tableWidgetCommand_itemSelectionChanged();
}
void SetCommandDialog::on_tableWidgetCommand_itemSelectionChanged()
{
	int	Row=ui->tableWidgetComponent->currentRow();
	if(Row<0)
		return;
	ComponentLine *C=ComponentContainer[Row];
	if(C==NULL)
		return;
	ExportFuncForMacro Functions[100];
	int N=C->RegistMacroFunction(Functions,100);

	int	R=ui->tableWidgetCommand	->currentRow();
	if(R<0)
		return;
	ShowExportFuncForMacro(Functions[R]);
}

void SetCommandDialog::ShowExportFuncForMacro( ExportFuncForMacro &R)
{
	for(int i=0;i<R.ArgName.count() && i<sizeof(ArgumentStructTable)/sizeof(ArgumentStructTable[0]);i++){
		ArgumentStructTable[i].ArgLabel	->setEnabled(true);
		ArgumentStructTable[i].ArgName	->setEnabled(true);
		ArgumentStructTable[i].ArgValue	->setEnabled(true);
		ArgumentStructTable[i].ArgName->setText(R.ArgName[i]);
	}
	for(int i=R.ArgName.count();i<sizeof(ArgumentStructTable)/sizeof(ArgumentStructTable[0]);i++){
		ArgumentStructTable[i].ArgLabel	->setEnabled(false);
		ArgumentStructTable[i].ArgName	->setEnabled(false);
		ArgumentStructTable[i].ArgValue	->setEnabled(false);
		ArgumentStructTable[i].ArgName->setText(/**/"");
	}
	ui->lineEditCommand	->setText(R.FuncName);
}


void SetCommandDialog::on_pushButtonOK_clicked()
{
	int	Row=ui->tableWidgetComponent->currentRow();
	if(Row<0)
		return;
	ComponentLine *C=ComponentContainer[Row];
	if(C==NULL)
		return;
	ExportFuncForMacro Functions[100];
	int	N=C->RegistMacroFunction(Functions,100);

	int	R=ui->tableWidgetCommand	->currentRow();
	if(R<0)
		return;

	CurrentData.DLLRoot		=C->GetDLLRoot();
	CurrentData.DLLName		=C->GetDLLName();
	CurrentData.CommandStr	=Functions[R].FuncName;

	if(Functions[R].ArgName.count()>=1)
		CurrentData.ArgValues.append(ui->lineEditArg1_Value	->text());
	if(Functions[R].ArgName.count()>=2)
		CurrentData.ArgValues.append(ui->lineEditArg2_Value	->text());
	if(Functions[R].ArgName.count()>=3)
		CurrentData.ArgValues.append(ui->lineEditArg3_Value	->text());
	if(Functions[R].ArgName.count()>=4)
		CurrentData.ArgValues.append(ui->lineEditArg4_Value	->text());
	if(Functions[R].ArgName.count()>=5)
		CurrentData.ArgValues.append(ui->lineEditArg5_Value	->text());
	if(Functions[R].ArgName.count()>=6)
		CurrentData.ArgValues.append(ui->lineEditArg6_Value	->text());
	if(Functions[R].ArgName.count()>=7)
		CurrentData.ArgValues.append(ui->lineEditArg7_Value	->text());
	if(Functions[R].ArgName.count()>=8)
		CurrentData.ArgValues.append(ui->lineEditArg8_Value	->text());
	if(Functions[R].ArgName.count()>=9)
		CurrentData.ArgValues.append(ui->lineEditArg9_Value	->text());
	if(Functions[R].ArgName.count()>=10)
		CurrentData.ArgValues.append(ui->lineEditArg10_Value->text());

	if(C->DLLAlgo!=NULL)
		CurrentData.DLLType=BatchLine::_DLL_Algorithm;
	else if(C->DLLResult!=NULL)
		CurrentData.DLLType=BatchLine::_DLL_Result;
	else if(C->DLLGui!=NULL)
		CurrentData.DLLType=BatchLine::_DLL_GUI;

	done(true);
}

void SetCommandDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

