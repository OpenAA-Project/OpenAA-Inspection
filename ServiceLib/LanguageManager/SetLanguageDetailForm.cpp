#include "SetLanguageDetailForm.h"
#include "ui_SetLanguageDetailForm.h"
#include "XLanguageManager.h"
#include <QTextCodec>

SetLanguageDetailForm::SetLanguageDetailForm(LanguageClass *a, QWidget *parent) :
    QDialog(parent)
	,LangData(a)
    ,ui(new Ui::SetLanguageDetailForm)
{
    ui->setupUi(this);

	QTextCodec *currentCodec=QTextCodec::codecForLocale();
	QList<QByteArray>	Q=QTextCodec::availableCodecs ();
	ui->comboBoxQtCodec->clear();
	for(int i=0;i<Q.count();i++){
		QByteArray	q=Q.value(i);
		char	*s=(char *)q.data();
		ui->comboBoxQtCodec->addItem(s);
	}

	if(LangData!=NULL){
		ui->spinBoxColumnNo		->setValue(LangData->ColumnNo);
		ui->comboBoxLanguage	->setEditText(LangData->LanguageName);
		ui->comboBoxExcelFont	->setEditText(LangData->ExcelFont);
		ui->comboBoxQtCodec		->setEditText(LangData->QtCotec);
	}
}

SetLanguageDetailForm::~SetLanguageDetailForm()
{
    delete ui;
}

void SetLanguageDetailForm::on_pushButtonOK_clicked()
{
	if(LangData!=NULL){
		LangData->ColumnNo		=ui->spinBoxColumnNo	->value();
		LangData->LanguageName	=ui->comboBoxLanguage	->currentText();
		LangData->ExcelFont		=ui->comboBoxExcelFont	->currentText();
		LangData->QtCotec		=ui->comboBoxQtCodec	->currentText();
	}
	done(true);
}

void SetLanguageDetailForm::on_pushButtonCancel_clicked()
{
	done(false);
}
