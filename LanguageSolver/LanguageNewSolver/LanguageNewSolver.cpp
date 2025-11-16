#include "LanguageNewSolver.h"
#include "EditProjectForm.h"
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"

LanguageNewSolver::LanguageNewSolver(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	LanguageData.LoadDefault();

	ui.tableWidget->setColumnWidth(0,40);
	ui.tableWidget->setColumnWidth(1,150);
	ui.tableWidget->setColumnWidth(2,150);
	ui.tableWidget->setColumnWidth(3,150);
	ShowLanguageList();
}

LanguageNewSolver::~LanguageNewSolver()
{

}

void LanguageNewSolver::ShowLanguageList(void)
{
	ui.tableWidget->setRowCount(LanguageData.GetCount());
	int	Row=0;
	for(LanguageClass *a=LanguageData.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui.tableWidget,0,Row,QString::number(a->ColumnNo));
		::SetDataToTable(ui.tableWidget,1,Row,a->LanguageName);
		::SetDataToTable(ui.tableWidget,2,Row,a->ExcelFont);
		::SetDataToTable(ui.tableWidget,3,Row,a->QtCotec);
		Row++;
	}
}

void	LanguageNewSolver::ShowProjectList(void)
{
	ui.listWidgetProject->clear();
	for(LSProjectItem *a=LSProjectData.GetFirst();a!=NULL;a=a->GetNext()){
		ui.listWidgetProject->addItem(a->ProjectItemName);
	}
}

void	LanguageNewSolver::ShowDetail(LSProjectItem *a)
{
	if(a!=NULL){
		ui.EditFolderReference->setText(a->ReferenceFolder);
		ui.listWidgetCPP->clear();
		for(LSSourceFileItem *k=a->SourceFiles.GetFirst();k!=NULL;k=k->GetNext()){
			ui.listWidgetCPP->addItem(k->FileName);
		}
		ui.listWidgetUI->clear();
		for(LSUIFileItem *u=a->UIFiles.GetFirst();u!=NULL;u=u->GetNext()){
			ui.listWidgetUI->addItem(u->FileName);
		}
		ui.lineEditResourceFile	->setText(a->ResourceFileName);
		ui.lineEditXLSXFile		->setText(a->XLSXFileName);
	}
	else{
		ui.EditFolderReference	->setText("");
		ui.listWidgetCPP		->clear();
		ui.listWidgetUI			->clear();
		ui.lineEditResourceFile	->setText("");
		ui.lineEditXLSXFile		->setText("");
	}
}

void LanguageNewSolver::on_actionNew_solution_triggered()
{
	LSProjectData.Clear();
	ShowProjectList();
	ShowDetail(NULL);

	ui.lineEditVarName		->setText(LSProjectData.KeywordForLangSolver);
	ui.lineEditXLSXFolder	->setText("");

}

void LanguageNewSolver::on_actionLoad_solution_triggered()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, "Load Output Solution file", ""
													, "Solution file(*.lsp)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==false){
			return;
		}
		if(LSProjectData.Load(&File)==true){
			LSProjectData.FileName=FileName;
			ShowProjectList();
			ShowDetail(NULL);
			ui.lineEditVarName		->setText(LSProjectData.KeywordForLangSolver);
			ui.lineEditXLSXFolder	->setText(LSProjectData.XLSXFolder);
		}
	}
}

void LanguageNewSolver::on_actionOverwrite_solution_triggered()
{
	if(LSProjectData.FileName.isEmpty()==false){
		QFile	File(LSProjectData.FileName);
		if(File.open(QIODevice::WriteOnly)==false){
			return;
		}
		LSProjectData.KeywordForLangSolver	=ui.lineEditVarName		->text();
		LSProjectData.XLSXFolder			=ui.lineEditXLSXFolder	->text();
		if(LSProjectData.Save(&File)==false){
			return;
		}
	}
	else{
		on_actionSave_solution_triggered();
	}
}

void LanguageNewSolver::on_actionSave_solution_triggered()
{
	QString FileName=QFileDialog::getSaveFileName ( 0, "Save Output Solution file", ""
													, "Solution file(*.lsp)");
	if(FileName.isEmpty()==false){
		LSProjectData.FileName=FileName;
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==false){
			return;
		}
		LSProjectData.KeywordForLangSolver	=ui.lineEditVarName		->text();
		LSProjectData.XLSXFolder			=ui.lineEditXLSXFolder	->text();
		if(LSProjectData.Save(&File)==true){
			ShowProjectList();
			ShowDetail(NULL);
		}
	}

}

void LanguageNewSolver::on_actionClose_triggered()
{
	close();
}

void LanguageNewSolver::on_pushButtonAddProject_clicked()
{
	LSProjectItem	*a=new LSProjectItem(&LSProjectData);
	EditProjectForm	D(a);
	int	ret=D.exec();
	if((bool)ret==true){
		int	Row=LSProjectData.SearchRow(a->ProjectItemName);
		if(Row<0){
			LSProjectData.AppendList(a);
			ShowProjectList();
			Row=LSProjectData.GetCount();
			ui.listWidgetProject->setCurrentRow(Row-1);
			ShowDetail(a);
		}
		else{
			ui.listWidgetProject->setCurrentRow(Row);
		}
	}
	else{
		delete	a;
	}
}

void LanguageNewSolver::on_listWidgetProject_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row<0)
		return;
	LSProjectItem	*a=LSProjectData.GetItem(Row);

	ShowDetail(a);
}

void LanguageNewSolver::on_listWidgetProject_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row<0)
		return;
	LSProjectItem	*a=LSProjectData.GetItem(Row);

	EditProjectForm	D(a);
	int	ret=D.exec();
	if(ret==1000){
		LSProjectData.RemoveList(a);
		delete	a;
	}
	ShowProjectList();
}

void LanguageNewSolver::on_pushButtonFolderReference_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row<0)
		return;
	LSProjectItem	*a=LSProjectData.GetItem(Row);

	QString dir = QFileDialog::getExistingDirectory(this, tr("Directory"));
	if(dir.isEmpty()==false){
		QDir	Dir(QDir::currentPath ());
		QFileInfo	Info(dir);
		ui.EditFolderReference->setText(dir);
		a->ReferenceFolder			=Dir.relativeFilePath(dir);
	}
}

void LanguageNewSolver::on_pushButtonAddCPPFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QDir	Dir(QDir::currentPath ());
			QStringList List=QFileDialog::getOpenFileNames( 0, "CPP files", CurrentProject->ReferenceFolder, "CPP(*.cpp *.c)");
			for(int i=0;i<List.count();i++){
				QString	FileName=Dir.relativeFilePath(List.value(i));
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
			ShowDetail(CurrentProject);
		}
	}
}

void LanguageNewSolver::on_pushButtonDeleteCPPFiles_clicked()
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
			ShowDetail(CurrentProject);
		}
	}
}

void LanguageNewSolver::on_pushButtonAddUIFiles_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QDir	Dir(QDir::currentPath ());
			QStringList List=QFileDialog::getOpenFileNames( 0, "UI files", CurrentProject->ReferenceFolder, "UI(*.ui)");
			for(int i=0;i<List.count();i++){
				QString	FileName=Dir.relativeFilePath(List.value(i));
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
			ShowDetail(CurrentProject);
		}
	}
}

void LanguageNewSolver::on_pushButtonDeleteUIFiles_clicked()
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
			ShowDetail(CurrentProject);
		}
	}
}

void LanguageNewSolver::on_pushButtonAutoResourceNaming_clicked()
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
				QString RFileName=RDir+::GetSeparator()+RBase+QString("Resource.")+RSuffix;
				ui.lineEditResourceFile->setText(RFileName);
				CurrentProject->ResourceFileName=RFileName;
			}
		}
	}
}

void LanguageNewSolver::on_pushButtonSetResourceFile_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QDir	Dir(QDir::currentPath ());
			QString FileName=QFileDialog::getOpenFileName( 0, "Save resource file", CurrentProject->ReferenceFolder, "CPP(*.cpp *.c)");
			if(FileName.isEmpty()==false){
				CurrentProject->ResourceFileName=Dir.relativeFilePath(FileName);
				ShowDetail(CurrentProject);
			}
		}
	}
}

void LanguageNewSolver::on_pushButtonAutoXLSXNaming_clicked()
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

void LanguageNewSolver::on_pushButtonSetXLSXFile_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			QString FileName=QFileDialog::getOpenFileName( 0, "Save XLSX file", CurrentProject->ReferenceFolder, "XLSX(*.xlsx)");
			if(FileName.isEmpty()==false){
				QFileInfo	FInfo(FileName);
				CurrentProject->XLSXFileName=FInfo.fileName();
				ShowDetail(CurrentProject);
			}
		}
	}
}

void LanguageNewSolver::on_pushButtonExecuteOne_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectData.KeywordForLangSolver	=ui.lineEditVarName->text();
		LSProjectData.XLSXFolder			=ui.lineEditXLSXFolder->text();
		LSProjectItem *CurrentProject		=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			LSProjectData.IDName			=CurrentProject->ProjectItemName;
			QString ErrMsg;
			LSProjectData.ClearStocker();
			LanguageData.AllocCodec();
			if(CurrentProject->Execute(LSProjectData,LanguageData,ErrMsg)==false){
				QMessageBox::critical ( NULL, "Error", ErrMsg);
				return;
			}
			QMessageBox::information( NULL, "Success", "Success execute");
		}
	}
}

void LanguageNewSolver::on_pushButtonExecute_clicked()
{
	LSProjectData.KeywordForLangSolver	=ui.lineEditVarName->text();
	LSProjectData.XLSXFolder			=ui.lineEditXLSXFolder->text();
	
	for(LSProjectItem *CurrentProject=LSProjectData.GetFirst();CurrentProject!=NULL;CurrentProject=CurrentProject->GetNext()){
		QString ErrMsg;
		LSProjectData.IDName			=CurrentProject->ProjectItemName;
		LSProjectData.ClearStocker();
		if(CurrentProject->Execute(LSProjectData,LanguageData,ErrMsg)==false){
			QMessageBox::critical ( NULL, "Error", ErrMsg);
			return;
		}
	}
	QMessageBox::information( NULL, "Success", "Success execute");
}

void LanguageNewSolver::on_actionLoad_Codec_file_triggered()
{
	QString FileName=QFileDialog::getOpenFileName( 0, "Load Language codec files", "", "dat(*.dat)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==false){
			return;
		}
		if(LanguageData.Load(&File)==true){
			ShowLanguageList();
		}
	}
}

void LanguageNewSolver::on_EditFolderReference_textChanged(const QString &arg1)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject		=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->ReferenceFolder	=ui.EditFolderReference->text();
		}
	}
}

void LanguageNewSolver::on_lineEditResourceFile_textChanged(const QString &arg1)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject		=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->ResourceFileName=ui.lineEditResourceFile->text();
		}
	}
}

void LanguageNewSolver::on_lineEditXLSXFile_textChanged(const QString &arg1)
{
	int	Row=ui.listWidgetProject->currentRow();
	if(Row>=0){
		LSProjectItem *CurrentProject		=LSProjectData.GetItem(Row);
		if(CurrentProject!=NULL){
			CurrentProject->XLSXFileName	=ui.lineEditXLSXFile	->text();
		}
	}
}

void LanguageNewSolver::on_pushButtonDeleteProject_clicked()
{
	int	Row=ui.listWidgetProject->currentRow();
	LSProjectItem *CurrentProject		=LSProjectData.GetItem(Row);
	if(CurrentProject!=NULL){
		LSProjectData.RemoveList(CurrentProject);
		delete	CurrentProject;
		ShowProjectList();
	}
}

void LanguageNewSolver::on_pushButtonSort_clicked()
{
	LSProjectData.Sort();
	ShowProjectList();
	if(LSProjectData.GetCount()>0){
		ui.listWidgetProject->setCurrentRow(0);
		LSProjectItem	*a=LSProjectData.GetItem(0);
		if(a!=NULL){
			ShowDetail(a);
		}
	}
}
