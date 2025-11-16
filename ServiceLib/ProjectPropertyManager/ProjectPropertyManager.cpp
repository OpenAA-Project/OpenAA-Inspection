#include "ProjectPropertyManager.h"
#include <QFileDialog>
#include "XGeneralFunc.h"



ProjectPropertyManager::ProjectPropertyManager(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	CopiedProperty	=NULL;
	CopiedType		=NULL;

	ui.tableWidgetProjectList->setColumnWidth(0,180);
	ui.tableWidgetProjectList->setColumnWidth(1,300);
	ui.tableWidgetProjectList->setColumnWidth(2,300);

	ui.listWidgetTagFolder	->setCurrentRow(0);

	ui.tableWidgetProperty	->setColumnWidth(0,240);
	ui.tableWidgetProperty	->setColumnWidth(1,400);
}

ProjectPropertyManager::~ProjectPropertyManager()
{

}

void ProjectPropertyManager::on_pushButtonSearchSolutionFile_clicked()
{
	QString FileName=QFileDialog::getOpenFileName (NULL
						, "Solution file"
						, ""
						, QString("Solution(*.sln);;All file(*.*)"));
	if(FileName.isEmpty()==false){
		ui.lineEditSolutionFileName	->setText(FileName);
	}
}

void ProjectPropertyManager::on_pushButtonLoadSolution_clicked()
{
	QString	FileName=ui.lineEditSolutionFileName->text();
	if(FileName.isEmpty()==false){
		SolutionData.LoadSolutionFile(FileName);
		ShowProjectList();
	}
}

void ProjectPropertyManager::ShowProjectList(void)
{
	ui.tableWidgetProjectList	->setRowCount(SolutionData.ProjectPack.GetCount());
	int	Row=0;
	for(ProjectList *c=SolutionData.ProjectPack.GetFirst();c!=NULL;c=c->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetProjectList ,0,Row ,c->Name);
		::SetDataToTable(ui.tableWidgetProjectList ,1,Row ,c->ProjectPath);
		::SetDataToTable(ui.tableWidgetProjectList ,2,Row ,c->ProjectFileName);

		if(c->IsChanged()==true){
			::SetTableColor(ui.tableWidgetProjectList,0,Row ,Qt::magenta);
			::SetTableColor(ui.tableWidgetProjectList,1,Row ,Qt::magenta);
			::SetTableColor(ui.tableWidgetProjectList,2,Row ,Qt::magenta);
		}
	}
}

void ProjectPropertyManager::on_tableWidgetProjectList_clicked(const QModelIndex &index)
{
	ShowTypeList();
	ShowPropertyList();
}
void ProjectPropertyManager::ShowTypeList(void)
{
	int	R=ui.tableWidgetProjectList->currentRow();
	if(R<0)
		return;
	ProjectList *c=SolutionData.ProjectPack[R];
	ui.tableWidgetType	->setRowCount(c->TypePack.GetCount());
	int	Row=0;
	for(CompileTypeList *a=c->TypePack.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetType ,0,Row ,a->Name);
		::SetDataToTable(ui.tableWidgetType ,1,Row ,a->BuildType);
	}
}

void ProjectPropertyManager::on_tableWidgetType_clicked(const QModelIndex &index)
{
	ShowPropertyList();
}
void ProjectPropertyManager::ShowPropertyList(void)
{
	int	ProjIndex=ui.tableWidgetProjectList->currentRow();
	if(ProjIndex<0)
		return;
	int	TypeIndex=ui.tableWidgetType->currentRow();
	if(TypeIndex<0)
		return;
	ProjectList *Proj=SolutionData.ProjectPack[ProjIndex];
	if(Proj==NULL)
		return;
	CompileTypeList *Comp=Proj->TypePack[TypeIndex];
	if(Comp==NULL)
		return;

	QString	TagFolder=ui.listWidgetTagFolder->currentItem()->text();
	int	RowCount=0;
	for(PropertyList *a=Comp->PropertyPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PropertyFolder==TagFolder){
			RowCount++;
		}
	}

	ui.tableWidgetProperty	->setRowCount(RowCount);
	int	Row=0;
	for(PropertyList *a=Comp->PropertyPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PropertyFolder==TagFolder){
			::SetDataToTable(ui.tableWidgetProperty ,0,Row ,a->TagName);
			::SetDataToTable(ui.tableWidgetProperty ,1,Row ,a->Data,Qt::ItemIsEditable);
			Row++;
		}
	}
}

void ProjectPropertyManager::on_listWidgetTagFolder_clicked(const QModelIndex &index)
{
    ShowPropertyList();
}

void ProjectPropertyManager::on_pushButtonCopyToAll_clicked()
{
	int	ProjIndex=ui.tableWidgetProjectList->currentRow();
	if(ProjIndex<0)
		return;
	int	TypeIndex=ui.tableWidgetType->currentRow();
	if(TypeIndex<0)
		return;
	ProjectList *Proj=SolutionData.ProjectPack[ProjIndex];
	if(Proj==NULL)
		return;
	CompileTypeList *Comp=Proj->TypePack[TypeIndex];
	if(Comp==NULL)
		return;

	QString	TagFolder=ui.listWidgetTagFolder->currentItem()->text();
	int	Row=0;
	int	RowIndex=ui.tableWidgetProperty->currentRow();
	for(PropertyList *a=Comp->PropertyPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PropertyFolder==TagFolder){
			if(RowIndex==Row){
				for(ProjectList *p=SolutionData.ProjectPack.GetFirst();p!=NULL;p=p->GetNext()){
					PropertyList *t=p->SearchProperty(Comp->Name,Comp->BuildType ,TagFolder ,a->TagName);
					if(t!=NULL){
						//_heapchk();
						t->Data		=a->Data;
						t->Changed	=true;
					}
				}
				break;
			}
			Row++;
		}
	}
	ShowProjectList();
	ShowPropertyList();
}

void ProjectPropertyManager::on_pushButtonUpdateProject_clicked()
{
	SolutionData.UpdateToFile();
}

void ProjectPropertyManager::on_pushButtonCopy1_clicked()
{
	int	ProjIndex=ui.tableWidgetProjectList->currentRow();
	if(ProjIndex<0)
		return;
	int	TypeIndex=ui.tableWidgetType->currentRow();
	if(TypeIndex<0)
		return;
	ProjectList *Proj=SolutionData.ProjectPack[ProjIndex];
	if(Proj==NULL)
		return;
	CompileTypeList *Comp=Proj->TypePack[TypeIndex];
	if(Comp==NULL)
		return;

	QString	TagFolder=ui.listWidgetTagFolder->currentItem()->text();
	int	Row=0;
	int	RowIndex=ui.tableWidgetProperty->currentRow();
	for(PropertyList *a=Comp->PropertyPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PropertyFolder==TagFolder){
			if(RowIndex==Row){
				CopiedProperty	=a;
				CopiedType		=Comp;
				break;
			}
			Row++;
		}
	}
}

void ProjectPropertyManager::on_pushButtonPaste1_clicked()
{
	if(CopiedProperty==NULL || CopiedType==NULL)
		return;
	int	ProjIndex=ui.tableWidgetProjectList->currentRow();
	if(ProjIndex<0)
		return;
	ProjectList *Proj=SolutionData.ProjectPack[ProjIndex];
	if(Proj==NULL)
		return;
	PropertyList *t=Proj->SearchProperty(CopiedType->Name,CopiedType->BuildType ,CopiedProperty->PropertyFolder ,CopiedProperty->TagName);
	if(t!=NULL){
		t->Data=CopiedProperty->Data;
		t->Changed=true;
	}
	ShowProjectList();
	ShowPropertyList();
}
