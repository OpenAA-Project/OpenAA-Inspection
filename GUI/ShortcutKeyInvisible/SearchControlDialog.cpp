#include "SearchControlDialog.h"
#include "ui_SearchControlDialog.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include<QTextStream>
#include<QFileInfo>
#include <QTabWidget>
#include <QToolButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>


static	void	AddPath(QStringList &List,QWidget *Control,QWidget *Root)
{
	if(Control==Root)
		return;
	List.append(Control->objectName());
	AddPath(List,Control->parentWidget(),Root);
}

void	ChildControl::SetPath(QWidget *Root)
{
	QStringList	List;
	AddPath(List,Control,Root);
	Path=/**/"";
	for(int i=List.count()-1;i>=0;i--){
		Path =Path+List[i];
		if(i!=0){
			Path = Path+QString('\\');
		}
	}
}

SearchControlDialog::SearchControlDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SearchControlDialog)
{
    ui->setupUi(this);
	ui->tableWidgetComponent->setColumnWidth(0,250);
	ui->tableWidgetComponent->setColumnWidth(1,300);
	ui->tableWidgetComponent->setColumnWidth(2,300);

	ui->tableWidgetControl->setColumnWidth(0,200);
	ui->tableWidgetControl->setColumnWidth(1,250);
	ui->tableWidgetControl->setColumnWidth(2,450);

	for(GUIItemInstance *c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->DLLAccess!=NULL){
			GUIItemInstancePointerList	*t=new GUIItemInstancePointerList(c);
			ItemListContainer.AppendList(t);
		}
	}
	ShowComponentList();
}

SearchControlDialog::~SearchControlDialog()
{
    delete ui;
}
void SearchControlDialog::ShowComponentList(void)
{
	int	N=ItemListContainer.GetCount();
	ui->tableWidgetComponent->setRowCount(N);
	int	Row=0;

	for(GUIItemInstancePointerList *p=ItemListContainer.GetFirst();p!=NULL;p=p->GetNext(),Row++){
		if(p->Point->DLLAccess!=NULL){
			SetDataToTable(ui->tableWidgetComponent,0,Row,p->Point->GetForm()->GetDLLRoot());
			SetDataToTable(ui->tableWidgetComponent,1,Row,p->Point->GetForm()->GetDLLName());
			SetDataToTable(ui->tableWidgetComponent,2,Row,p->Point->GetForm()->GetName());
		}
	}
}

void	SearchAddChild(NPListPack<ChildControl> &Children ,QWidget *Obj)
{
	if(dynamic_cast<QPushButton *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QPushButton"));
	}
	else if(dynamic_cast<QToolButton *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QToolButton"));
	}
	else if(dynamic_cast<QCheckBox *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QCheckBox"));
	}
	else if(dynamic_cast<QRadioButton *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QRadioButton"));
	}
	else if(dynamic_cast<QLineEdit *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QLineEdit"));
	}
	else if(dynamic_cast<QSpinBox *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QSpinBox"));
	}
	else if(dynamic_cast<QDoubleSpinBox *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QDoubleSpinBox"));
	}
	else if(dynamic_cast<QTextEdit *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QTextEdit"));
	}
	else if(dynamic_cast<QComboBox *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QComboBox"));
	}
	else if(dynamic_cast<QListWidget *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QListWidget"));
	}
	else if(dynamic_cast<QListView *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QListView"));
	}
	else if(dynamic_cast<QTreeWidget *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QTreeWidget"));
	}
	else if(dynamic_cast<QTreeView *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QTreeView"));
	}
	else if(dynamic_cast<QTableWidget *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QTableWidget"));
	}
	else if(dynamic_cast<QTableView *>(Obj)!=NULL){
		Children.AppendList(new ChildControl(Obj,/**/"QTableView"));
	}
	QObjectList	List=Obj->children();
	for(int i=0;i<List.count();i++){
		QObject	*o=List[i];
		QWidget	*w=dynamic_cast<QWidget *>(o);
		if(w!=NULL){
			SearchAddChild(Children ,w);
		}
	}
}

void SearchControlDialog::on_tableWidgetComponent_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetComponent->currentRow();
	GUIItemInstancePointerList *p=ItemListContainer[Row];
	if(p!=NULL){
		ControlChildren.RemoveAll();
		SearchAddChild(ControlChildren ,p->Point->Handle);
		for(ChildControl *s=ControlChildren.GetFirst();s!=NULL;s=s->GetNext()){
			s->SetPath(p->Point->Handle);
		}
		ShowControlList();
	}
}
void SearchControlDialog::ShowControlList(void)
{
	int	N=ControlChildren.GetCount();
	ui->tableWidgetControl->setRowCount(N);
	int	Row=0;

	for(ChildControl *p=ControlChildren.GetFirst();p!=NULL;p=p->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetControl,0,Row,p->ClassName);
		::SetDataToTable(ui->tableWidgetControl,1,Row,p->Control->objectName());
		::SetDataToTable(ui->tableWidgetControl,2,Row,p->Path);
	}
}
void SearchControlDialog::on_tableWidgetControl_doubleClicked(const QModelIndex &index)
{
	on_pushButton_clicked();
}

void SearchControlDialog::on_pushButton_clicked()
{
	int	Row=ui->tableWidgetComponent->currentRow();
	GUIItemInstancePointerList *p=ItemListContainer[Row];
	int	CRow=ui->tableWidgetControl->currentRow();
	ChildControl *q=ControlChildren[CRow];
	if(p!=NULL && q!=NULL){
		DLLRoot	=p->Point->GetForm()->GetDLLRoot();
		DLLName	=p->Point->GetForm()->GetDLLName();
		DLLInst	=p->Point->GetForm()->GetName();
		ObjPath	=q->Path;
		ObjName	=q->Control->objectName();
		done(true);
	}
}

void SearchControlDialog::on_pushButton_2_clicked()
{
	done(false);
}
