#include "CheckDLLForm.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include "XResultDLLManager.h"
#include "XFilterManager.h"
#include "XCameraClass.h"
#include "XPIOButton.h"
#include "XLightClass.h"
#include "XSequence.h"
#include "testsequencedlldialog.h"
#include "SettingParameterDialog.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include "XExecuteVisualizerInterface.h"
#include "Regulus64System.h"

class	CameraClassPack;

extern	CameraClassPack		*CameraPack;
extern	PIOClassPack		*PIOPack;
extern	DLLVarPack			*SeqVarPack;
extern	LightClassPack		*LightPack;


CheckDLLForm::CheckDLLForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	ui.listWidgetAlgorithm->clear();
	for(AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
		ui.listWidgetAlgorithm->addItem(L->GetFileName());
	}

	ui.listWidgetGUI->clear();
	for(GuiDLLItem *G=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetFirst();G!=NULL;G=G->GetNext()){
		ui.listWidgetGUI->addItem(G->FileName);
	}

	ui.listWidgetResultDLL->clear();
	for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
		ui.listWidgetResultDLL->addItem(R->GetFileName());
	}

	ui.listWidgetFilter->clear();
	for(FilterDLLList *F=GetLayersBase()->GetFilterBank()->GetFirst();F!=NULL;F=F->GetNext()){
		ui.listWidgetFilter->addItem(F->GetFilterName());
	}

	ui.listWidgetCamera->clear();
	for(CameraClass *C=CameraPack->GetFirst();C!=NULL;C=C->GetNext()){
		ui.listWidgetCamera->addItem(C->GetFileName());
	}

	ui.listWidgetPIO->clear();
	for(PIOClass *I=PIOPack->GetFirst();I!=NULL;I=I->GetNext()){
		ui.listWidgetPIO->addItem(I->GetFileName());
	}

	ui.listWidgetSequenceDLL->clear();
	for(DLLVarOperand *D=SeqVarPack->GetFirst();D!=NULL;D=D->GetNext()){
		ui.listWidgetSequenceDLL->addItem(D->GetFileName());
	}

	ui.listWidgetLightDLL->clear();
	for(LightAccessList *G=LightPack->GetFirst();G!=NULL;G=G->GetNext()){
		ui.listWidgetLightDLL->addItem(G->GetFileName());
	}

	QDir::setCurrent(GetLayersBase()->GetSystemPath());
	EVMap=new RunnerMap(GetLayersBase(),true,NULL);
	EVMap->LoadDLL("ExecuteVisualizer");
	for(RunnerObjDLL *R=EVMap->GetFirst();R!=NULL;R=R->GetNext()){
		ui.listWidgetExecuteVisualizer->addItem(R->GetFileName());
	}

}

CheckDLLForm::~CheckDLLForm()
{
	delete	EVMap;
	EVMap=NULL;
}


void CheckDLLForm::on_listWidgetGUI_clicked(const QModelIndex &)
{
	int	Row=ui.listWidgetGUI->currentRow();
	if(Row<0)
		return;
	GuiDLLItem *G=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetItem(Row);
	if(G==NULL)
		return;
	ui.lineEditRoot->setText(G->RootName);
	ui.lineEditName->setText(G->Name);
	ui.lineEditOrganization	->setText(/**/"");
	ui.lineEditExplain		->setText(G->Explain);
	ui.lineEditVersion	->setText(QString::number((int)G->GetVersion()));
	ui.lineEditDLLType	->setText(/**/"");
	ui.lineEditCopyright->setText(G->Copyright);
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	G->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);

	QStringList MacroNames;
	G->GetMacroNames(MacroNames);
	int	MaxArgCount=0;
	for(int i=0;i<MacroNames.count();i++){
		ExportFuncForMacro	*e=G->SearchMacroFunc(MacroNames[i]);
		if(e!=NULL && MaxArgCount<e->ArgName.count()){
			MaxArgCount=e->ArgName.count();
		}
	}
	ui.tableWidgetMacro->setRowCount(MacroNames.count());
	ui.tableWidgetMacro->setColumnCount(MaxArgCount+2);

	QStringList	HLabels;
	HLabels.append("Name");
	HLabels.append("Explain");
	for(int n=0;n<MaxArgCount;n++){
		HLabels.append(QString("Arg")+QString::number(n+1));
	}
	ui.tableWidgetMacro->setHorizontalHeaderLabels(HLabels);

	for(int row=0;row<MacroNames.count();row++){
		ExportFuncForMacro	*e=G->SearchMacroFunc(MacroNames[row]);
		if(e!=NULL){
			SetDataToTable(ui.tableWidgetMacro ,0,row,e->FuncName);
			if(e->Explain.count()>0){
				SetDataToTable(ui.tableWidgetMacro ,1,row,e->Explain[0]);
			}
			else{
				SetDataToTable(ui.tableWidgetMacro ,1,row,/**/"");
			}
			for(int n=0;n<e->ArgName.count();n++){
				SetDataToTable(ui.tableWidgetMacro ,2+n,row,e->ArgName[n]);
			}
		}
		else{
			for(int n=0;n<MaxArgCount+2;n++){
				SetDataToTable(ui.tableWidgetMacro ,n,row,/**/"");
			}
		}
	}
	ui.listWidgetRelatedAlgorithm->clear();
	RootNameListContainer	List;
	G->EntryAlgorithm(List);
	for(RootNameList *w=List.GetFirst();w!=NULL;w=w->GetNext()){
		QString	s=w->DLLRoot + QString(" : ")+w->DLLName;
		ui.listWidgetRelatedAlgorithm->addItem(s);
	}
}

void CheckDLLForm::on_listWidgetAlgorithm_clicked(const QModelIndex &)
{
	int	Row=ui.listWidgetAlgorithm->currentRow();
	if(Row<0)
		return;
	AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetItem(Row);
	if(L==NULL)
		return;
	ui.lineEditRoot->setText(L->GetDLLRoot());
	ui.lineEditName->setText(L->GetDLLName());
	QString str;
	if(L->GetOrganization(str)==true){
		ui.lineEditOrganization->setText(str);
	}
	ui.lineEditVersion	->setText(QString::number(L->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number((qulonglong)L->GetDLLType(),16));
	ui.lineEditExplain	->setText(/**/"");
	ui.lineEditCopyright->setText(/**/"");
	AlgorithmLibraryContainer	*Lib=L->NewLibrary(GetLayersBase());
	if(Lib!=NULL){
		ui.lineEditLibType	->setText(QString::number(Lib->GetLibType()));
		delete	Lib;
	}
	else{
		ui.lineEditLibType	->setText(/**/"");
	}

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	L->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}


void CheckDLLForm::on_pushButtonOK_clicked()
{
	emit	SignalClose();
	close();
}
void CheckDLLForm::on_listWidgetResultDLL_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetResultDLL->currentRow();
	if(Row<0)
		return;
	ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetItem(Row);
	if(R==NULL)
		return;

	ui.lineEditRoot->setText(R->GetDLLRoot());
	ui.lineEditName->setText(R->GetDLLName());
	QString str=R->GetOrganization();
	ui.lineEditOrganization->setText(str);
	
	ui.lineEditVersion	->setText(QString::number(R->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number(R->GetDLLType()));
	ui.lineEditExplain	->setText(R->GetExplain());
	ui.lineEditCopyright->setText(R->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	R->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_listWidgetFilter_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetFilter->currentRow();
	if(Row<0)
		return;
	FilterDLLList *F=GetLayersBase()->GetFilterBank()->GetItem(Row);
	if(F==NULL)
		return;

	ui.lineEditRoot->setText(/**/"");
	ui.lineEditName->setText(F->GetFilterName());
	ui.lineEditOrganization->setText(/**/"");
	
	ui.lineEditVersion	->setText(QString::number(F->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number(F->GetDLLType()));
	ui.lineEditExplain	->setText(F->GetExplain());
	ui.lineEditCopyright->setText(F->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	F->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_listWidgetCamera_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetCamera->currentRow();
	if(Row<0)
		return;
	CameraClass *C=CameraPack->GetItem(Row);
	if(C==NULL)
		return;
	ui.lineEditRoot->setText(/**/"");
	ui.lineEditName->setText(C->GetName());
	ui.lineEditOrganization->setText(/**/"");

	ui.lineEditVersion	->setText(QString::number(C->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number((qulonglong)C->GetDLLType(),16));
	ui.lineEditExplain	->setText(C->GetExplain());
	ui.lineEditCopyright->setText(C->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	C->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_listWidgetPIO_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetPIO->currentRow();
	if(Row<0)
		return;
	PIOClass *I=PIOPack->GetItem(Row);
	if(I==NULL)
		return;
	ui.lineEditRoot->setText(/**/"");
	ui.lineEditName->setText(I->GetName());
	ui.lineEditOrganization->setText(/**/"");

	ui.lineEditVersion	->setText(QString::number(I->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number((qulonglong)I->GetDLLType(),16));
	ui.lineEditExplain	->setText(I->GetExplain());
	ui.lineEditCopyright->setText(I->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	I->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_listWidgetSequenceDLL_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetSequenceDLL->currentRow();
	if(Row<0)
		return;
	DLLVarOperand *D=SeqVarPack->GetItem(Row);
	if(D==NULL)
		return;
	ui.lineEditRoot->setText(/**/"");
	ui.lineEditName->setText(D->GetDLLVarName());
	ui.lineEditOrganization->setText(/**/"");

	ui.lineEditVersion	->setText(QString::number(D->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number((qulonglong)D->GetDLLType(),16));
	ui.lineEditExplain	->setText(D->GetExplain());
	ui.lineEditCopyright->setText(D->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	D->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_listWidgetLightDLL_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetLightDLL->currentRow();
	if(Row<0)
		return;
	LightAccessList *G=LightPack->GetItem(Row);
	if(G==NULL)
		return;
	ui.lineEditRoot->setText(/**/"");
	ui.lineEditName->setText(G->GetName());
	ui.lineEditOrganization->setText(/**/"");

	ui.lineEditVersion	->setText(QString::number(G->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number((qulonglong)G->GetDLLType(),16));
	ui.lineEditExplain	->setText(G->GetExplain());
	ui.lineEditCopyright->setText(G->GetCopyright());
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	G->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}

void CheckDLLForm::on_pushButtonSetting_clicked()
{
	QWidget * w=ui.toolBox->currentWidget ();
	if(w->objectName()==QString(/**/"GUI")){
		ParamGUI		*p=GetLayersBase()->GetParamGUI();
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		p->LoadDefault(GetLayersBase()->GetUserPath());
		SettingParameterDialog	D(GetLayersBase(),p);
		D.exec();
	}
	else if(w->objectName()==QString(/**/"Algorithm")){
		int	Row=ui.listWidgetAlgorithm->currentRow();
		if(Row<0)
			return;
		AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetItem(Row);
		if(L==NULL)
			return;
		AlgorithmBase	*p=L->InitialAlloc(GetLayersBase());
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		p->LoadDefault(GetLayersBase()->GetUserPath());
		SettingParameterDialog	D(GetLayersBase(),p);
		D.exec();
		delete	p;
	}
	else if(w->objectName()==QString(/**/"ResultDLL")){
		int	Row=ui.listWidgetResultDLL->currentRow();
		if(Row<0)
			return;
		ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetItem(Row);
		if(R==NULL)
			return;
		ResultDLLBaseRoot	*p=R->GetDLLPoint();
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		p->LoadDefault(GetLayersBase()->GetUserPath());
		SettingParameterDialog	D(GetLayersBase(),p);
		D.exec();
	}
	else if(w->objectName()==QString(/**/"Filter")){
		int	Row=ui.listWidgetFilter->currentRow();
		if(Row<0)
			return;
		FilterDLLList *F=GetLayersBase()->GetFilterBank()->GetItem(Row);
		if(F==NULL)
			return;
	}
	else if(w->objectName()==QString(/**/"Camera")){
		int	Row=ui.listWidgetCamera->currentRow();
		if(Row<0)
			return;
		CameraClass *C=CameraPack->GetItem(Row);
		if(C==NULL)
			return;
	}
	else if(w->objectName()==QString(/**/"PIO")){
	}
	else if(w->objectName()==QString(/**/"SequenceDLL")){
	}
	else if(w->objectName()==QString(/**/"LightDLL")){
		int	Row=ui.listWidgetLightDLL->currentRow();
		if(Row<0)
			return;
		LightAccessList *G=LightPack->GetItem(Row);
		if(G==NULL)
			return;
	}
}

void CheckDLLForm::on_pushButtonTest_clicked()
{
	QWidget * w=ui.toolBox->currentWidget ();
	if(w->objectName()==/**/QString("SequenceDLL")){
		int	Row=ui.listWidgetSequenceDLL->currentRow();
		if(Row<0)
			return;
		DLLVarOperand *D=SeqVarPack->GetItem(Row);
		if(D==NULL)
			return;
		TestSequenceDLLDialog	TestDialog(D);
		TestDialog.exec();
	}
}

void CheckDLLForm::on_listWidgetExecuteVisualizer_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetExecuteVisualizer->currentRow();
	if(Row<0)
		return;
	RunnerObjDLL *R=EVMap->GetItem(Row);
	if(R==NULL)
		return;
	QString DLLRoot, DLLName;
	R->GetRootName(DLLRoot, DLLName);
	ui.lineEditRoot->setText(DLLRoot);
	ui.lineEditName->setText(DLLName);
	ui.lineEditOrganization->setText(/**/"");

	ui.lineEditVersion	->setText(QString::number(R->GetVersion()));
	ui.lineEditDLLType	->setText(QString::number(0));
	ui.lineEditExplain	->setText(R->GetExplain());
	ui.lineEditCopyright->setText(/**/"");
	ui.lineEditLibType	->setText(/**/"");

	ui.listWidgetExportFunc->clear();
	QStringList Str;
	R->GetExportFunctions(Str);
	ui.listWidgetExportFunc->addItems(Str);
	ui.listWidgetRelatedAlgorithm->clear();
}
