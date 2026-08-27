/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

	ui->spinBoxAngleDegree				->setValue	(ControlRememberer::GetInt(ui->spinBoxAngleDegree,0));
	ui->spinBoxLayer					->setValue	(ControlRememberer::GetInt(ui->spinBoxLayer,-1));
	ui->lineEditPatterns				->setText	(ControlRememberer::GetString(ui->lineEditPatterns));
	ui->checkBoxTextOneLine				->setChecked(ControlRememberer::GetBool(ui->checkBoxTextOneLine	,true));
	ui->checkBoxDarker					->setChecked(ControlRememberer::GetBool(ui->checkBoxDarker	,true));
	ui->spinBoxThresholdBrightness		->setValue	(ControlRememberer::GetInt(ui->spinBoxThresholdBrightness,-1));
	ui->spinBoxReducedNoiseSize			->setValue	(ControlRememberer::GetInt(ui->spinBoxReducedNoiseSize,0));
	ui->spinBoxShrinkImage				->setValue	(ControlRememberer::GetInt(ui->spinBoxShrinkImage,0));

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

	ui->spinBoxAngleDegree				->setValue	(AngleDegree		);
	ui->spinBoxLayer					->setValue	(Layer				);
	ui->lineEditPatterns				->setText	(Patterns			);
	ui->checkBoxTextOneLine				->setChecked(TextOneLine		);
	ui->checkBoxDarker					->setChecked(Darker				);
	ui->spinBoxThresholdBrightness		->setValue	(ThresholdBrightness);
	ui->spinBoxReducedNoiseSize			->setValue	(ReducedNoiseSize	);
	ui->spinBoxShrinkImage				->setValue	(ShrinkImage		);
																		
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

	AngleDegree			=ui->spinBoxAngleDegree				->value	();
	Layer				=ui->spinBoxLayer					->value	();
	Patterns			=ui->lineEditPatterns				->text	();
	TextOneLine			=ui->checkBoxTextOneLine			->isChecked();
	Darker				=ui->checkBoxDarker					->isChecked();
	ThresholdBrightness	=ui->spinBoxThresholdBrightness		->value	();
	ReducedNoiseSize	=ui->spinBoxReducedNoiseSize		->value	();
	ShrinkImage			=ui->spinBoxShrinkImage				->value	();
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