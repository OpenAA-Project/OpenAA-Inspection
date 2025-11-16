#include "LanguageManager.h"
#include "XGeneralFunc.h"
#include "SetLanguageForm.h"
#include "NewProjectForm.h"
#include "XIntClass.h"
#include <QMessageBox>
#include <QFileDialog>

LanguageManager::LanguageManager(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.tableWidgetProject->setColumnWidth(0,130);
	ui.tableWidgetProject->setColumnWidth(1,120);

	ui.tableWidgetExcelFiles->setColumnWidth(0,200);
	ui.tableWidgetExcelFiles->setColumnWidth(1,280);

	SolutionFileName	=LSolution.GetDefaultFileName();
	LSolution.LoadDefault();
	LanguageData.LoadDefault();

	ShowProjectList();
}

LanguageManager::~LanguageManager()
{

}

void	LanguageManager::ShowProjectList()
{
	ui.tableWidgetProject->setRowCount(LSolution.GetCount());
	int	Row=0;
	for(ProjectLanguage *a=LSolution.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui.tableWidgetProject,0,Row,a->ProjectName);
		::SetDataToTable(ui.tableWidgetProject,1,Row,a->GetLngFileName());
		Row++;
	}
}

void	LanguageManager::ShowDetail(ProjectLanguage *a)
{
	if(a!=NULL){
		ui.tableWidgetExcelFiles->setRowCount(a->ExcelFiles.count());
		int	Row=0;
		for(int i=0;i<a->ExcelFiles.count();i++){
			QFileInfo	Info(a->ExcelFiles[i]);
			::SetDataToTable(ui.tableWidgetExcelFiles,0,Row,Info.fileName());
			::SetDataToTable(ui.tableWidgetExcelFiles,1,Row,Info.path());
			Row++;
		}
		ui.lineEditLNGFile->setText(a->OutputLNGFile);
	}
	else{
		ui.tableWidgetExcelFiles->setRowCount(0);
		ui.lineEditLNGFile->setText("");
	}
}

void LanguageManager::on_tableWidgetProject_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);

	NewProjectForm	D(a->ProjectName);
	int	ret=D.exec();
	if(ret==1000){
		LSolution.RemoveList(a);
		delete	a;
		ShowProjectList();
	}
	else if((bool)ret==true){
		a->ProjectName=D.ProjectName;
		ShowProjectList();
	}
}

void LanguageManager::on_tableWidgetProject_clicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);
	ShowDetail(a);
}

void LanguageManager::on_tableWidgetExcelFiles_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);
	if(QMessageBox::warning(NULL,"Select","Delete Excel file?",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		a->ExcelFiles.removeAt(Row);
		ShowDetail(a);
	}
}

void LanguageManager::on_pushButtonLoadExcel_clicked()
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);

	QDir	HomeDir(QDir::currentPath ());
	QStringList FileNames=QFileDialog::getOpenFileNames ( 0, "Excel File", ""
														, "Excel file (*.xlsx *.xls)");
	for(int i=0;i<FileNames.count();i++){
		QString	LFileName=FileNames[i];
		QString	RelFileName	=	HomeDir.relativeFilePath(LFileName);
		QFileInfo	DInfo(RelFileName);
		QString		Dest=DInfo.fileName();
		bool	Found=false;
		for(int j=0;j<a->ExcelFiles.count();j++){
			QFileInfo	Info(a->ExcelFiles[j]);
			if(Info.fileName()==Dest){
				Found=true;
				break;
			}
		}
		if(Found==false){
			a->ExcelFiles.append(RelFileName);
		}
	}
	ShowDetail(a);
}

void LanguageManager::on_pushButtonDeleteExcel_clicked()
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);

	IntList Rows;
	::GetSelectedRows(ui.tableWidgetExcelFiles ,Rows);
	QStringList	StrList;
	for(int i=0;i<a->ExcelFiles.count();i++){
		if(Rows.IsInclude(i)==false){
			StrList.append(a->ExcelFiles[i]);
		}
	}
	a->ExcelFiles=StrList;
	ShowDetail(a);
}

void LanguageManager::on_pushButtonLNGFile_clicked()
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);

	QString FileName=QFileDialog::getSaveFileName ( 0, "Output LNG file", ""
												, "Language fle(*.lng)");
	if(FileName.isEmpty()==false){
		a->OutputLNGFile=FileName;
		ShowDetail(a);
	}
}

void LanguageManager::on_pushButtonCompile_clicked()
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);
	QString ErrorMsg;
	if(a->Execute(LanguageData,ui.progressBarCompile,ErrorMsg)==false){
		QMessageBox::critical(NULL,"Error",ErrorMsg);
	}
}

void LanguageManager::on_pushButtonBuildAll_clicked()
{
	for(ProjectLanguage *a=LSolution.GetFirst();a!=NULL;a=a->GetNext()){
		QString ErrorMsg;
		if(a->Execute(LanguageData,ui.progressBarCompile,ErrorMsg)==false){
			QMessageBox::critical(NULL,"Error",ErrorMsg);
			return;
		}
	}
}

void LanguageManager::on_actionLoad_solution_triggered()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, "Load Output Solution file", ""
													, "Solution file(*.lsn)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==false){
			return;
		}
		if(LSolution.Load(&File)==true){
			SolutionFileName=FileName;
			ShowProjectList();
			ShowDetail(NULL);
		}
	}
}

void LanguageManager::on_actionLanguage_triggered()
{
	SetLanguageForm	D(LanguageData);
	D.exec();
}

void LanguageManager::on_actionDefault_triggered()
{

}

void LanguageManager::on_actionNew_Project_triggered()
{
	NewProjectForm	D("");
	if(D.exec()==(int)true){
		int	Row=LSolution.Search(D.ProjectName);
		if(Row<0){
			ProjectLanguage	*a=new ProjectLanguage();
			a->ProjectName	=D.ProjectName;
			LSolution.AppendList(a);
			ShowProjectList();
		}
		else{
			ui.tableWidgetProject->selectRow(Row);
		}
	}
}


void LanguageManager::on_actionSave_solution_triggered()
{
	QString FileName=QFileDialog::getSaveFileName ( 0, "Save Output Solution file", ""
													, "Solution file(*.lsn)");
	if(FileName.isEmpty()==false){
		SolutionFileName=FileName;
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==false){
			return;
		}
		if(LSolution.Save(&File)==true){
			ShowProjectList();
			ShowDetail(NULL);
		}
	}

}

void LanguageManager::on_actionNew_solution_triggered()
{
	SolutionFileName=/**/"";
	LSolution.Clear();
	ShowProjectList();
	ShowDetail(NULL);
}

void LanguageManager::on_actionClose_triggered()
{
	close();
}

void LanguageManager::on_actionOverwrite_solution_triggered()
{
	if(SolutionFileName.isEmpty()==false){
		QFile	File(SolutionFileName);
		if(File.open(QIODevice::WriteOnly)==false){
			return;
		}
		if(LSolution.Save(&File)==false){
			return;
		}
	}
	else{
		on_actionSave_solution_triggered();
	}
}

void LanguageManager::on_lineEditLNGFile_textChanged(const QString &arg1)
{
	int	Row=ui.tableWidgetProject->currentRow();
	if(Row<0)
		return;
	ProjectLanguage *a=LSolution.GetItem(Row);
	if(a!=NULL){
		a->OutputLNGFile=ui.lineEditLNGFile->text();
	}
}

void LanguageManager::on_pushButtonAddNewProject_clicked()
{
	on_actionNew_Project_triggered();
}
