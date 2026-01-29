#include "EditOCRItemDialog.h"
#include "ui_EditOCRItemDialog.h"
#include "XRememberer.h"
#include<QInputDialog>
#include<QMessageBox>
#include "XGeneralFunc.h"
#include "AddMonoManualItemForm.h"
#include "AddManualItemForm.h"

EditOCRItemDialog::EditOCRItemDialog(LayersBase *Base, QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditOCRItemDialog)
{
    ui->setupUi(this);

	RegNumber	=0;
	InspectMatching	=false;
	SaveIntoResult	=false;
	OKByFailingRecognition=false;

	Mergin=0;

	ui->checkBoxInspectMatching			->setChecked(ControlRememberer::GetBool(ui->checkBoxInspectMatching			,false));
	ui->checkBoxSaveIntoResult			->setChecked(ControlRememberer::GetBool(ui->checkBoxSaveIntoResult			,false));
	ui->checkBoxOKByFailingRecognition	->setChecked(ControlRememberer::GetBool(ui->checkBoxOKByFailingRecognition	,false));
	ui->spinBoxRegNumber				->setValue	(ControlRememberer::GetInt(ui->spinBoxRegNumber,0));

	ui->ButtonDeleteItem	->setVisible(false);
	ui->ButtonSaveNewItem	->setVisible(true);
	ui->ButtonUpdateItem	->setVisible(false);

	InstallOperationLog(this);
}

EditOCRItemDialog::~EditOCRItemDialog()
{
    delete ui;
}

void EditOCRItemDialog::ReflectToWindow(void)
{
	ui->lineEditItemName				->setText(ItemName);
	ui->checkBoxInspectMatching			->setChecked(InspectMatching);
	ui->checkBoxSaveIntoResult			->setChecked(SaveIntoResult);
	ui->checkBoxOKByFailingRecognition	->setChecked(OKByFailingRecognition);
	ui->spinBoxRegNumber				->setValue	(RegNumber);
	ui->listWidgetMatchingList			->addItems(CorrectList);

	ui->ButtonDeleteItem	->setVisible(true);
	ui->ButtonSaveNewItem	->setVisible(true);
	ui->ButtonUpdateItem	->setVisible(true);
}
void EditOCRItemDialog::FromWindow(void)
{
	ItemName				=ui->lineEditItemName				->text();
	InspectMatching			=ui->checkBoxInspectMatching		->isChecked();
	SaveIntoResult			=ui->checkBoxSaveIntoResult			->isChecked();
	OKByFailingRecognition	=ui->checkBoxOKByFailingRecognition	->isChecked();
	RegNumber				=ui->spinBoxRegNumber				->value	();
	CorrectList				=::GetDataFromListWidget(ui->listWidgetMatchingList);
}

void EditOCRItemDialog::on_listWidgetMatchingList_doubleClicked(const QModelIndex &index)
{
	int	R=ui->listWidgetMatchingList->currentRow();
	if(R<0)
		return;
	QListWidgetItem	*w=ui->listWidgetMatchingList->item(R);
	if(w!=NULL){
		QString	s=QInputDialog::getText ( NULL, "Edit matching string (Regular expression)"
										, "OK condition"
										, QLineEdit::Normal
										, w->text()
										, 0);
		if(s.isEmpty()==false){
			w->setText(s);
		}
	}
}

void EditOCRItemDialog::on_pushButtonAddMatchingList_clicked()
{
	QString	s=QInputDialog::getText ( NULL, "Add matching string (Regular expression)"
									, "OK condition"
									, QLineEdit::Normal
									, QString()
									, 0);
	if(s.isEmpty()==false){
		ui->listWidgetMatchingList->addItem(s);
	}
}

void EditOCRItemDialog::on_pushButtonSubMatchingList_clicked()
{
	int	R=ui->listWidgetMatchingList->currentRow();
	if(R<0)
		return;
	if(QMessageBox::question (NULL,"Delete?"
							, "Delete this line?"
							, QMessageBox::Yes |  QMessageBox::No)==QMessageBox::Yes){
		QStringList	tCorrectList	=::GetDataFromListWidget(ui->listWidgetMatchingList);
		tCorrectList.removeAt(R);
		ui->listWidgetMatchingList->clear();
		ui->listWidgetMatchingList->addItems(tCorrectList);
	}
}

void EditOCRItemDialog::on_ButtonSaveNewItem_clicked()
{
	FromWindow();
	done(1);
}

void EditOCRItemDialog::on_ButtonUpdateItem_clicked()
{
	FromWindow();
	done(2);
}

void EditOCRItemDialog::on_pushButtonClose_clicked()
{
	done(-1);
}

void EditOCRItemDialog::on_ButtonDeleteItem_clicked()
{
	done(3);
}