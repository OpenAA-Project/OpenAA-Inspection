#include "XTypeDef.h"
#include "ui_ExpandedPasteForm.h"
#include "ExpandedPasteForm.h"
#include <QMessageBox>
#include "DisplayImageResource.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XCSV.h"

ExpandedPasteForm::ExpandedPasteForm(DisplayImage *mainPanel,QWidget *parent) :
    QWidget(parent)
	,MainPanel(mainPanel)
    ,ui(new Ui::ExpandedPasteForm)
{
    ui->setupUi(this);
	LangDISolver.SetLanguage(mainPanel->GetLayersBase()->GetLanguagePackageData(),mainPanel->GetLayersBase()->GetLanguageCode());
	LangDISolver.SetUI(this);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	SetWidgetCenter(this);
	MainPanel->GetLayersBase()->InstallOperationLog(this);
}

ExpandedPasteForm::~ExpandedPasteForm()
{
    delete ui;
}

void	ExpandedPasteForm::SetZone(int WDot,int HDot)
{
	ui->spinBoxXDot->setValue(WDot);
	ui->spinBoxYDot->setValue(HDot);
}

void ExpandedPasteForm::showEvent ( QShowEvent * event )
{
	on_ButtonArrange_clicked();
	ShowMatrixList();
	ui->tabWidget->setCurrentIndex(0);
}
	
void ExpandedPasteForm::closeEvent ( QCloseEvent * event )
{
	MainPanel->ExpandedPasteButtonOff();
	event->accept();
}

void ExpandedPasteForm::ShowMatrixList(void)
{
	ui->tableWidgetMatrixList->setRowCount(MainPanel->GetLayersBase()->GetPasteListMatrixContainerBase()->GetCount());
	int	Row=0;
	for(PasteListMatrix *a=MainPanel->GetLayersBase()->GetPasteListMatrixContainerBase()->GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetMatrixList ,0,Row ,QString::number(a->GlobalPage));
		::SetDataToTable(ui->tableWidgetMatrixList ,1,Row ,QString::number(a->XPos));
		::SetDataToTable(ui->tableWidgetMatrixList ,2,Row ,QString::number(a->YPos));
	}
}

void ExpandedPasteForm::on_ButtonPasteSameAlgo_clicked()
{
	MainPanel->SetDrawingMode(DisplayImage::_Normal);
	close();
	emit	ExecuteOkInSameAlgorithm();
}

void ExpandedPasteForm::on_ButtonArrange_clicked()
{
	if(ui->tabWidget->currentIndex()==0){
		int	XNumb=ui->spinBoxXNumb->value();
		int	YNumb=ui->spinBoxYNumb->value();
		int	XDot =ui->spinBoxXDot->value();
		int	YDot =ui->spinBoxYDot->value();
		MainPanel->SetExpandedPaste(XNumb,YNumb,XDot,YDot);
		ui->lineEditTotalNumb->setText(QString::number(XNumb*YNumb));

		//MainPanel->SetDrawingMode(DisplayImage::_Normal);
		//close();
	}
}

void ExpandedPasteForm::on_ButtonCancel_clicked()
{
	MainPanel->SetDrawingMode(DisplayImage::_Normal);
	emit	CancelPaste();
	close();
}

void ExpandedPasteForm::on_tabWidget_currentChanged(int index)
{

}

void ExpandedPasteForm::on_pushButtonLoadMastixList_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, LangDISolver.GetString(ExpandedPasteForm_LS,LID_187)/*"Load Matrix CSV"*/
													, QString()
													, tr(/**/"csv (*.csv);;All File (*.*)"));
	if(FileName.isEmpty()==false){
		QStringListListCSV	CSV;
		if(CSV.LoadFromCSVFile(FileName)==true){
			if(MainPanel->GetLayersBase()->GetPasteListMatrixContainerBase()->Load(CSV)==true){
				ShowMatrixList();
				return;
			}
		}
		ui->tableWidgetMatrixList->setRowCount(0);
	}
}

void ExpandedPasteForm::on_pushButtonSaveMastixList_clicked()
{
	QString FileName=QFileDialog::getSaveFileName ( 0, LangDISolver.GetString(ExpandedPasteForm_LS,LID_188)/*"Save Matrix CSV"*/
													, QString()
													, tr(/**/"csv (*.csv);;All File (*.*)"));
	if(FileName.isEmpty()==false){
		QStringListListCSV	CSV;
		if(MainPanel->GetLayersBase()->GetPasteListMatrixContainerBase()->Save(CSV)==true){
			if(CSV.SaveFromCSVFile(FileName)==false){
				QMessageBox::warning (NULL
									, LangDISolver.GetString(ExpandedPasteForm_LS,LID_189)/*"Warning"*/
									, LangDISolver.GetString(ExpandedPasteForm_LS,LID_190)/*"Not saved Matrix data into CSV file "*/);
			}
		}
	}
}

void ExpandedPasteForm::on_ButtonPasteSameAlgoInMatrixList_clicked()
{
	emit	ExecuteMatrix();
	close();
}

void ExpandedPasteForm::on_tableWidgetMatrixList_clicked(const QModelIndex &index)
{

}
