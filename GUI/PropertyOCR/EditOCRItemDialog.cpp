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

	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;
	EnsmallDot=0;
	EnlargeDot=0;
	BlockWidth=0;
	BlockHeight=0;
	MinSize=0;
	Mergin=0;
	UseColorLogic=false;
	Rotation	=0;

	ui->checkBoxInspectMatching			->setChecked(ControlRememberer::GetBool(ui->checkBoxInspectMatching			,false));
	ui->checkBoxSaveIntoResult			->setChecked(ControlRememberer::GetBool(ui->checkBoxSaveIntoResult			,false));
	ui->checkBoxOKByFailingRecognition	->setChecked(ControlRememberer::GetBool(ui->checkBoxOKByFailingRecognition	,false));
	ui->spinBoxRegNumber				->setValue	(ControlRememberer::GetInt(ui->spinBoxRegNumber,0));

	ui->ButtonDeleteItem	->setVisible(false);
	ui->ButtonSaveNewItem	->setVisible(true);
	ui->ButtonUpdateItem	->setVisible(false);
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb<3)
		ui->pushButtonPickupColor->setVisible(false);

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
	ui->spinBoxRotation		->setValue(Rotation);
}
void EditOCRItemDialog::FromWindow(void)
{
	ItemName				=ui->lineEditItemName				->text();
	InspectMatching			=ui->checkBoxInspectMatching		->isChecked();
	SaveIntoResult			=ui->checkBoxSaveIntoResult			->isChecked();
	OKByFailingRecognition	=ui->checkBoxOKByFailingRecognition	->isChecked();
	RegNumber				=ui->spinBoxRegNumber				->value	();
	CorrectList				=::GetDataFromListWidget(ui->listWidgetMatchingList);
	Rotation				=ui->spinBoxRotation				->value();
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

void EditOCRItemDialog::on_pushButtonPickupColor_clicked()
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb>=3){
		AddManualItemForm	D(GetLayersBase(),NULL);
		D.AbsLR			=AbsLR;
		D.AbsHR			=AbsHR;
		D.AbsLG			=AbsLG;
		D.AbsHG			=AbsHG;
		D.AbsLB			=AbsLB;
		D.AbsHB			=AbsHB;
		D.EnsmallDot	=EnsmallDot;
		D.EnlargeDot	=EnlargeDot;
		D.BlockWidth	=BlockWidth;
		D.BlockHeight	=BlockHeight;
		D.MinSize		=MinSize;
		D.Mergin		=Mergin;
		D.MaskingColor	=MaskingColor;
		D.Initial();
		if(D.exec()==(int)true){
			AbsLR			=D.AbsLR;
			AbsHR			=D.AbsHR;
			AbsLG			=D.AbsLG;
			AbsHG			=D.AbsHG;
			AbsLB			=D.AbsLB;
			AbsHB			=D.AbsHB;
			EnsmallDot		=D.EnsmallDot;
			EnlargeDot		=D.EnlargeDot;
			BlockWidth		=D.BlockWidth;
			BlockHeight		=D.BlockHeight;
			MinSize			=D.MinSize;
			Mergin			=D.Mergin;
			MaskingColor	=D.MaskingColor;
			UseColorLogic	=true;
		}
	}
	else{
		on_pushButtonPickupBrightness_clicked();
	}
}

void EditOCRItemDialog::on_pushButtonPickupBrightness_clicked()
{
	AddMonoManualItemForm	D(GetLayersBase(),NULL);
	D.AbsLR			=AbsLR;
	D.AbsHR			=AbsHR;
	D.AbsLG			=AbsLG;
	D.AbsHG			=AbsHG;
	D.AbsLB			=AbsLB;
	D.AbsHB			=AbsHB;
	D.EnsmallDot	=EnsmallDot;
	D.EnlargeDot	=EnlargeDot;
	D.BlockWidth	=BlockWidth;
	D.BlockHeight	=BlockHeight;
	D.MinSize		=MinSize;
	D.SetInitial();
	if(D.exec()==(int)true){
		AbsLR			=D.AbsLR;
		AbsHR			=D.AbsHR;
		AbsLG			=D.AbsLG;
		AbsHG			=D.AbsHG;
		AbsLB			=D.AbsLB;
		AbsHB			=D.AbsHB;
		EnsmallDot		=D.EnsmallDot;
		EnlargeDot		=D.EnlargeDot;
		BlockWidth		=D.BlockWidth;
		BlockHeight		=D.BlockHeight;
		MinSize			=D.MinSize;
		UseColorLogic	=false;
	}
}

void EditOCRItemDialog::on_pushButtonRotation0_clicked()
{
	ui->spinBoxRotation	->setValue(0);
}

void EditOCRItemDialog::on_pushButtonRotation90_clicked()
{
	ui->spinBoxRotation	->setValue(90);
}

void EditOCRItemDialog::on_pushButton180_clicked()
{
	ui->spinBoxRotation	->setValue(180);
}

void EditOCRItemDialog::on_pushButton270_clicked()
{
	ui->spinBoxRotation	->setValue(270);
}
