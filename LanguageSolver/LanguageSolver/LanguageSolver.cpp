/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\LanguageSolver.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "LanguageSolver.h"
#include "XLanguageSolver.h"
#include "SelectCodecForm.h"
#include "CodecListSelecterForm.h"
#include <QFileDialog>
#include "XLSProject.h"
#include <QMessageBox>
#include "ViewerUI.h"
#include "ViewerStrings.h"


LanguageStocker	LStocker("LangSolver");
QString	ResourceFileName;
QString	FolderReference;

LanguageSolver::LanguageSolver(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	LStocker.LoadSettingFile();
}

LanguageSolver::~LanguageSolver()
{

}


void LanguageSolver::on_actionLoad_source_CPP_triggered()
{
	QStringList List=QFileDialog::getOpenFileNames( 0, "Scan CPP files", QString(), "CPP(*.cpp *.c)");
	for(int i=0;i<List.count();i++){
		int	ResourceCount;
		LStocker.ScanLoadCPPFile(List.value(i),ResourceCount);
	}
}

void LanguageSolver::on_actionReplace_CPP_triggered()
{
	QStringList List=QFileDialog::getOpenFileNames ( 0, "Scan CPP files", QString(), "CPP(*.cpp *.c)");
	for(int i=0;i<List.count();i++){
		QString	LStr=List.value(i);
		LStocker.ReplaceCPPFile(LStr,LStr,ResourceFileName);
	}
}

void LanguageSolver::on_actionCodec_triggered()
{
	SelectCodecForm	Q(this);
	Q.exec();
}

void LanguageSolver::on_actionSave_resource_files_triggered()
{
	QString FileName=QFileDialog::getSaveFileName( 0, "Save resource file", QString(), "CPP(*.cpp *.c)");
	if(FileName.isEmpty()==false){
		LStocker.SaveResource(FileName);
		ResourceFileName = FileName;
		QFileInfo	FInfo(FileName);
		QString	HeaderFileName=FInfo.path() + QDir::separator() + FInfo.baseName() + QString(".h");
		LStocker.SaveHeaderFile(HeaderFileName);
	}
}

void LanguageSolver::on_actionLoad_resource_file_triggered()
{
	QString FileName=QFileDialog::getOpenFileName( 0, "Load resource file", QString(), "CPP(*.cpp *.c)");
	if(FileName.isEmpty()==false)
		ResourceFileName = FileName;
		LStocker.LoadResource(FileName);
}

void LanguageSolver::on_actionSave_CSV_triggered()
{
	QString FileName=QFileDialog::getSaveFileName( 0, "Save CSV file", QString(), "CSV(*.csv)");
	if(FileName.isEmpty()==false)
		LStocker.SaveCSVFile(FileName);
}

void LanguageSolver::on_actionLoad_CSV_triggered()
{	
	QString FileName=QFileDialog::getOpenFileName( 0, "Load CSV file", QString(), "CSV(*.csv)");
	if(FileName.isEmpty()==false)
		LStocker.LoadCSVFile(FileName);
}

void LanguageSolver::on_actionLoad_UI_ui_triggered()
{
	QStringList List=QFileDialog::getOpenFileNames ( 0, "Load UI files", QString(), "UI(*.ui)");
	for(int i=0;i<List.count();i++){
		QString	LStr=List.value(i);
		LStocker.LoadUIFile(LStr);
	}
}

void LanguageSolver::on_actionCodec_for_Languages_triggered()
{
	CodecListSelecterForm	Q(this);
	Q.exec();
}


void	LanguageSolver::ShowProject()
{
	ui.listWidgetProject->clear();
	for(LSProjectItem *c=LSProjectData.GetFirst();c!=NULL;c=c->GetNext()){
		ui.listWidgetProject->addItem(c->ProjectItemName);
	}
}
void	LanguageSolver::ShowProjectContents(LSProjectItem *CurrentProj)
{
	ui.listWidgetCPP->clear();
	for(LSSourceFileItem *c=CurrentProj->SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		ui.listWidgetCPP->addItem(c->FileName);
	}
	ui.listWidgetUI->clear();
	for(LSUIFileItem *c=CurrentProj->UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
		ui.listWidgetUI->addItem(c->FileName);
	}
	ui.lineEditResourceFile	->setText(CurrentProj->ResourceFileName	);
	ui.lineEditCSVFile		->setText(CurrentProj->CSVFileName		);
	ui.lineEditProjectName	->setText(CurrentProj->ProjectItemName	);
	ui.lineEditXLSXFile		->setText(CurrentProj->XLSXFileName		);
}

void LanguageSolver::on_actionLoad_Project_triggered()
{
	ProjectFileName=QFileDialog::getOpenFileName( 0, "Load Project file", QString(), "LSP(*.lsp)");
	if(ProjectFileName.isEmpty()==false){
		QFile	file(ProjectFileName);
		if(file.open(QIODevice::ReadOnly)==false)
			return;
		if(LSProjectData.Load(file)==true){
			ShowProject();
			ui.lineEditVarName		->setText(LSProjectData.KeywordForLangSolver);
			ui.lineEditXLSXFolder	->setText(LSProjectData.XLSXFolder);
		}
	}
}

void LanguageSolver::on_actionSaveProject_triggered()
{
	ProjectFileName=QFileDialog::getSaveFileName( 0, "Save Project file", QString(), "LSP(*.lsp)");
	if(ProjectFileName.isEmpty()==false){
		QFile	file(ProjectFileName);
		if(file.open(QIODevice::WriteOnly)==false)
			return;
		LSProjectData.Save(file);
	}
}

void LanguageSolver::on_listWidgetProject_clicked(const QModelIndex &)
{
	int	Row=ui.listWidgetProject->currentRow();
	LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
	if(CurrentProject!=NULL){
		ShowProjectContents(CurrentProject);
	}
}

void LanguageSolver::on_pushButtonAddProject_clicked()
{
	LSProjectItem *Proj=new LSProjectItem(&LSProjectData,LSProjectData.KeywordForLangSolver);
	Proj->ProjectItemName=ui.lineEditProjectName->text();
	LSProjectData.AppendList(Proj);

	int	Row=LSProjectData.GetNumber()-1;
	ShowProject();
	ui.listWidgetProject->setCurrentRow(Row);

	LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
	if(CurrentProject!=NULL){
		ShowProjectContents(CurrentProject);
	}
}

void LanguageSolver::on_pushButtonUpdateProject_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->ProjectItemName=ui.lineEditProjectName->text();

			ShowProject();
			ui.listWidgetProject->setCurrentRow(Row);
			ShowProjectContents(CurrentProject);
		}
	}
			
}

void LanguageSolver::on_pushButtonDeleteProject_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			LSProjectData.RemoveList(CurrentProject);
			ShowProject();
		}
	}
}

void LanguageSolver::on_pushButtonAddCPPFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QStringList List=QFileDialog::getOpenFileNames( 0, "CPP files", FolderReference, "CPP(*.cpp *.c)");
			for(int i=0;i<List.count();i++){
				QString	FileName=List.value(i);
				LSSourceFileItem *c;
				for(c=CurrentProject->SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->FileName==FileName)
						break;
				}
				if(c==NULL){
					c=new LSSourceFileItem();
					c->FileName=FileName;
					CurrentProject->SourceFiles.AppendList(c);
				}
			}
			ShowProjectContents(CurrentProject);
		}
	}
}

void LanguageSolver::on_pushButtonDeleteCPPFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QList<QListWidgetItem *> Q=ui.listWidgetCPP->selectedItems();
			LSSourceFileItem *Dim[10000];
			for(int i=0;i<Q.count();i++){
				QListWidgetItem *W=Q.value(i);
				for(LSSourceFileItem *c=CurrentProject->SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->FileName==W->text()){
						Dim[i]=c;
						break;
					}
				}
			}
			for(int i=0;i<Q.count();i++){
				CurrentProject->SourceFiles.RemoveList(Dim[i]);
			}
			ShowProjectContents(CurrentProject);
		}
	}
}




void LanguageSolver::on_pushButtonAddUIFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QStringList List=QFileDialog::getOpenFileNames( 0, "UI files", FolderReference, "UI(*.ui)");
			for(int i=0;i<List.count();i++){
				QString	FileName=List.value(i);
				LSUIFileItem *c;
				for(c=CurrentProject->UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->FileName==FileName)
						break;
				}
				if(c==NULL){
					c=new LSUIFileItem();
					c->FileName=FileName;
					CurrentProject->UIFiles.AppendList(c);
				}
			}
			ShowProjectContents(CurrentProject);
		}
	}
}

void LanguageSolver::on_pushButtonDeleteUIFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QList<QListWidgetItem *> Q=ui.listWidgetUI->selectedItems();
			LSUIFileItem *Dim[10000];
			for(int i=0;i<Q.count();i++){
				QListWidgetItem *W=Q.value(i);
				for(LSUIFileItem *c=CurrentProject->UIFiles.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->FileName==W->text()){
						Dim[i]=c;
						break;
					}
				}
			}
			for(int i=0;i<Q.count();i++){
				CurrentProject->UIFiles.RemoveList(Dim[i]);
			}
			ShowProjectContents(CurrentProject);
		}
	}
}

void LanguageSolver::on_pushButtonSetResourceFile_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QString FileName=QFileDialog::getSaveFileName( 0, "Save resource file", FolderReference, "CPP(*.cpp *.c)");
			if(FileName.isEmpty()==false){
				CurrentProject->ResourceFileName=FileName;
				ShowProjectContents(CurrentProject);
			}
		}
	}
}

void LanguageSolver::on_pushButtonSetCSVFile_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QString FileName=QFileDialog::getSaveFileName( 0, "Save CSV file", FolderReference, "CSV(*.csv)");
			if(FileName.isEmpty()==false){
				CurrentProject->CSVFileName=FileName;
				ShowProjectContents(CurrentProject);
			}
		}
	}
}

void LanguageSolver::on_pushButtonExecute_clicked()
{
	int	N=0;
	for(LSProjectItem *c=LSProjectData.GetFirst();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetProject->setCurrentRow(N);
		ShowProjectContents(c);
		QString	ErrMsg;
		if(c->Execute(ErrMsg)==false){
			QMessageBox::critical ( NULL, "Error", ErrMsg);
			return;
		}
	}
	 QMessageBox::information( NULL, "Finished", "Successful");
}

void LanguageSolver::on_pushButtonFolderReference_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Directory"));
	if(dir.isEmpty()==false){
		QFileInfo	Info(dir);
		ui.lineEditProjectName->setText(Info.baseName());
		FolderReference=dir;
		ui.EditFolderReference->setText(dir);
	}
}

void LanguageSolver::on_lineEditResourceFile_textChanged(const QString &)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->ResourceFileName=ui.lineEditResourceFile->text();
		}
	}
}

void LanguageSolver::on_lineEditCSVFile_textChanged(const QString &)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->CSVFileName=ui.lineEditCSVFile->text();
		}
	}
}

void LanguageSolver::on_pushButtonAutoResourceNaming_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			LSSourceFileItem *c=CurrentProject->SourceFiles.GetFirst();
			if(c!=NULL){
				QString	RDir	=QFileInfo(c->FileName).path();
				QString	RBase	=QFileInfo(c->FileName).baseName();
				QString RSuffix	=QFileInfo(c->FileName).completeSuffix();
				QString RFileName=RDir+QDir::separator()+RBase+QString("Resource.")+RSuffix;
				ui.lineEditResourceFile->setText(RFileName);
				CurrentProject->ResourceFileName=RFileName;
			}
		}
	}
}

void LanguageSolver::on_pushButtonAutoCSVNaming_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			LSSourceFileItem *c=CurrentProject->SourceFiles.GetFirst();
			if(c!=NULL){
				QString	RDir	=QFileInfo(c->FileName).path();
				QString	RBase	=QFileInfo(c->FileName).baseName();
				QString RFileName=RDir+QDir::separator()+RBase+QString(".csv");
				ui.lineEditCSVFile->setText(RFileName);
				CurrentProject->CSVFileName=RFileName;
			}
		}
	}
}

void LanguageSolver::on_lineEditVarName_textChanged(const QString &)
{
	LSProjectData.SetKeyword(ui.lineEditVarName->text());
}


void LanguageSolver::on_pushButtonExecuteOne_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QString	ErrMsg;
			if(CurrentProject->Execute(ErrMsg)==false){
				QMessageBox::critical ( NULL, "Error", ErrMsg);
				return;
			}
		}
	}
}

void LanguageSolver::on_pushButtonViewString_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			ViewerStrings	D(CurrentProject->Stocker,NULL);
			D.exec();
			return;
		}
	}
	ViewerUI	D(LStocker,NULL);
	D.exec();
}

void LanguageSolver::on_pushButtonViewUI_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			ViewerUI	D(CurrentProject->Stocker,NULL);
			D.exec();
			return;
		}
	}
	ViewerUI	D(LStocker,NULL);
	D.exec();
}

void LanguageSolver::on_lineEditXLSXFolder_textChanged(const QString &)
{
	LSProjectData.XLSXFolder=ui.lineEditXLSXFolder->text();
}

void LanguageSolver::on_actionOverwrite_Project_triggered()
{
	if(ProjectFileName.isEmpty()==false){
		QFile	file(ProjectFileName);
		if(file.open(QIODevice::WriteOnly)==false)
			return;
		LSProjectData.Save(file);
	}
}

void LanguageSolver::on_pushButtonAutoXLSXNaming_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			LSSourceFileItem *c=CurrentProject->SourceFiles.GetFirst();
			if(c!=NULL){
				QString	RBase	=QFileInfo(c->FileName).baseName();
				QString RFileName=RBase+QString(".xlsx");
				ui.lineEditXLSXFile->setText(RFileName);
				CurrentProject->XLSXFileName=RFileName;
			}
		}
	}
}

void LanguageSolver::on_pushButtonSetXLSXFile_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QString FileName=QFileDialog::getSaveFileName( 0, "Save XLSX file", FolderReference, "XLSX(*.xlsx)");
			if(FileName.isEmpty()==false){
				QFileInfo	FInfo(FileName);
				CurrentProject->XLSXFileName=FInfo.fileName();
				ShowProjectContents(CurrentProject);
			}
		}
	}
}