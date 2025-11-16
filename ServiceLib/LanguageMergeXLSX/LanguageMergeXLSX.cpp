#include "LanguageMergeXLSX.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>

LanguageMergeXLSX::LanguageMergeXLSX(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.tableWidgetBindedFiles->setColumnWidth(0,200);
	ui.tableWidgetBindedFiles->setColumnWidth(1,200);
	ui.tableWidgetBindedFiles->setColumnWidth(2,60);

	LanguageData.LoadDefault();
	ShowLanguageList();
}

LanguageMergeXLSX::~LanguageMergeXLSX()
{

}
void	LanguageMergeXLSX::ShowLanguageList(void)
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
void LanguageMergeXLSX::on_pushButtonDestFolder_clicked()
{
	QString	DestDir=QFileDialog::getExistingDirectory(0, "Destination directory");
	if(DestDir.isEmpty()==false){
		ui.lineEditDestFolder->setText(DestDir);
		QDir	MDir(DestDir);
		QStringList	XLSXFilter;
		XLSXFilter.append("*.XLSX");
		QFileInfoList	tmpDestXLSXFiles=MDir.entryInfoList (XLSXFilter,QDir::Files | QDir::NoDotAndDotDot);
		for(int i=0;i<tmpDestXLSXFiles.count();i++){
			bool	Found=false;
			for(int j=0;j<DestXLSXFiles.count();j++){
				if(DestXLSXFiles[j].fileName()==tmpDestXLSXFiles[i].fileName()){
					Found=true;
					break;
				}
			}
			if(Found==false){
				DestXLSXFiles.append(tmpDestXLSXFiles[i]);
			}
		}

		ui.listWidgetDestFiles->clear();
		for(int i=0;i<DestXLSXFiles.count();i++){
			ui.listWidgetDestFiles->addItem(DestXLSXFiles[i].fileName());
		}
	}
}

void LanguageMergeXLSX::on_pushButtonSourceFolder_clicked()
{
	QString	SourceDir=QFileDialog::getExistingDirectory(0, "Source directory");
	if(SourceDir.isEmpty()==false){
		ui.lineEditSourceFolder->setText(SourceDir);
		QDir	MDir(SourceDir);
		QStringList	XLSXFilter;
		XLSXFilter.append("*.XLSX");
		QFileInfoList	tmpSourceXLSXFiles=MDir.entryInfoList(XLSXFilter,QDir::Files | QDir::NoDotAndDotDot);

		for(int i=0;i<tmpSourceXLSXFiles.count();i++){
			bool	Found=false;
			for(int j=0;j<SourceXLSXFiles.count();j++){
				if(SourceXLSXFiles[j].fileName()==tmpSourceXLSXFiles[i].fileName()){
					Found=true;
					break;
				}
			}
			if(Found==false){
				SourceXLSXFiles.append(tmpSourceXLSXFiles[i]);
			}
		}

		ui.listWidgetSourceFiles->clear();
		for(int i=0;i<SourceXLSXFiles.count();i++){
			ui.listWidgetSourceFiles->addItem(SourceXLSXFiles[i].fileName());
		}
	}
}

void LanguageMergeXLSX::on_listWidgetDestFiles_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetDestFiles->currentRow();
	DestXLSXFiles.removeAt(Row);
	ui.listWidgetDestFiles->clear();
	for(int i=0;i<DestXLSXFiles.count();i++){
		ui.listWidgetDestFiles->addItem(DestXLSXFiles[i].fileName());
	}
}

void LanguageMergeXLSX::on_listWidgetSourceFiles_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetSourceFiles->currentRow();
	SourceXLSXFiles.removeAt(Row);
	ui.listWidgetSourceFiles->clear();
	for(int i=0;i<SourceXLSXFiles.count();i++){
		ui.listWidgetSourceFiles->addItem(SourceXLSXFiles[i].fileName());
	}
}

void LanguageMergeXLSX::on_pushButtonConbine_clicked()
{
	CombinedXLSXContainer.RemoveAll();
	for(int i=0;i<DestXLSXFiles.count();i++){
		QString	Filename=DestXLSXFiles[i].fileName();
		for(int j=0;j<SourceXLSXFiles.count();j++){
			if(Filename==SourceXLSXFiles[j].fileName()){
				CombinedXLSX	*C=new CombinedXLSX(DestXLSXFiles[i],SourceXLSXFiles[j]);
				CombinedXLSXContainer.AppendList(C);
				break;
			}
		}
	}
	ui.tableWidgetBindedFiles->setRowCount(CombinedXLSXContainer.GetCount());
	int	Row=0;
	for(CombinedXLSX *a=CombinedXLSXContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetBindedFiles ,0,Row,a->GetDestFileName());
		::SetDataToTable(ui.tableWidgetBindedFiles ,1,Row,a->GetSourceFileName());
	}
}

void LanguageMergeXLSX::on_pushButtonStartMerge_clicked()
{
	int	RowLanguage=ui.tableWidget->currentRow();
	if(RowLanguage<0){
		QMessageBox::information ( NULL, "Information", "Select language");
		return;
	}
	ui.progressBar->setValue(0);
	ui.progressBar->setMaximum(CombinedXLSXContainer.count());
	for(CombinedXLSX *a=CombinedXLSXContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Load()==false){
			QMessageBox::information ( NULL, "Error", "Load error : XLSX file");
			continue;
		}
		if(a->Merge(RowLanguage)==false){
			QMessageBox::information ( NULL, "Error", "Merge error");
			continue;
		}
		if(a->SaveToDest(LanguageData)==false){
			QMessageBox::information ( NULL, "Error", "Save error");
			continue;
		}
		a->Result=true;
		ui.progressBar->setValue(ui.progressBar->value()+1);
	}
	int	Row=0;
	for(CombinedXLSX *a=CombinedXLSXContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetBindedFiles ,0,Row,a->GetDestFileName());
		::SetDataToTable(ui.tableWidgetBindedFiles ,1,Row,a->GetSourceFileName());
		if(a->Result==true){
			::SetDataToTable(ui.tableWidgetBindedFiles ,2,Row,"OK");
		}
		else{
			::SetDataToTable(ui.tableWidgetBindedFiles ,2,Row,"Error");
		}
	}
}

void LanguageMergeXLSX::on_pushButtonAddDest_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(0, "Add Destination XLSX file"
												,QString()
												, "Excel File (*.xlsx);;all files (*.*)" );
	if(FileName.isEmpty()==false){
		DestXLSXFiles.append(QFileInfo(FileName));
	}
	ui.listWidgetDestFiles->clear();
	for(int i=0;i<DestXLSXFiles.count();i++){
		ui.listWidgetDestFiles->addItem(DestXLSXFiles[i].fileName());
	}
}

void LanguageMergeXLSX::on_pushButtonAddSource_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(0, "Add Source XLSX file"
												,QString()
												, "Excel File (*.xlsx);;all files (*.*)" );
	if(FileName.isEmpty()==false){
		SourceXLSXFiles.append(QFileInfo(FileName));
	}
	ui.listWidgetSourceFiles->clear();
	for(int i=0;i<SourceXLSXFiles.count();i++){
		ui.listWidgetSourceFiles->addItem(SourceXLSXFiles[i].fileName());
	}
}