#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "EditStatusDialog.h"
#include "ui_EditStatusDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XStatusController.h"
#include <QTextCodec>

EditStatusDialog::EditStatusDialog(LayersBase *base ,QWidget *Ctrl,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Control(Ctrl)
    ,ui(new Ui::EditStatusDialog)
{
    ui->setupUi(this);
	LangLibSolver.SetUI(this);

	HTMLMode=false;
	HTMLModeToopTip=false;
}

EditStatusDialog::~EditStatusDialog()
{
    delete ui;
}

void EditStatusDialog::resizeEvent ( QResizeEvent * event )
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->plainTextEditComment->resize(width()-20,ui->frame->geometry().top()-ui->plainTextEditComment->geometry().top());
}

void EditStatusDialog::showEvent ( QShowEvent * event )
{
	ui->tableWidgetGUI->setColumnWidth(0,(ui->tableWidgetGUI->width()-30)/3);
	ui->tableWidgetGUI->setColumnWidth(1,(ui->tableWidgetGUI->width()-30)/3);
	ui->tableWidgetGUI->setColumnWidth(2,(ui->tableWidgetGUI->width()-30)/3);

	ui->tableWidgetGUI->setRowCount(1);
	::SetDataToTable(ui->tableWidgetGUI ,0,0,GUIRoot);
	::SetDataToTable(ui->tableWidgetGUI ,1,0,GUIName);
	::SetDataToTable(ui->tableWidgetGUI ,2,0,GUIInst);

	ui->listWidgetMode->clear();
	ui->listWidgetMode->addItems(ObjectPath);

	CommentOpinion	*s=GetLayersBase()->GetStatusController()->FindComment(GUIRoot
																			,GUIName
																			,GUIInst
																			,ObjectPath);
	if(s!=NULL){
		QString	Str=s->GetCommentString();
		if(s->IsHTML()==true){
			HTMLMode=true;
			ui->plainTextEditComment->setHtml(Str);
			ui->plainTextEditComment->setReadOnly(true);
		}
		else{
			HTMLMode=false;
			ui->plainTextEditComment->setText (Str);
			ui->plainTextEditComment->setReadOnly(false);
		}
		if(Control!=NULL){
			if(s->GetToolTipString().isEmpty()){
				s->SetHTMLModeToopTip(Control->toolTip());
			}
		}
		QString	ToolTipStr=s->GetToolTipString();
		if(s->IsHTMLToopTip()==true){
			HTMLModeToopTip=true;
			ui->textEditToolTip->setHtml(ToolTipStr);
			ui->textEditToolTip->setReadOnly(true);
		}
		else{
			HTMLModeToopTip=false;
			ui->textEditToolTip->setText (ToolTipStr);
			ui->textEditToolTip->setReadOnly(false);
		}
		//ui->lineEditToolTip->setText(s->GetToolTip());

		ui->checkBoxEnableToolTip->setChecked(s->IsEnableToolTop());
		on_checkBoxEnableToolTip_clicked();
	}
	else{
		ui->plainTextEditComment->setReadOnly(false);
	}
}

void EditStatusDialog::on_pushButtonUpdate_clicked()
{
	QStringList	Comment;
	QStringList	ToolTip;

	if(HTMLMode==true){
		QString	LStr=ui->plainTextEditComment->toHtml();
		Comment.append(LStr);
	}
	else{
		QString	LStr=ui->plainTextEditComment->toPlainText();
		Comment.append(LStr);
	}

	if(HTMLModeToopTip==true){
		QString	ToolTipStr=ui->textEditToolTip->toHtml();
		ToolTip.append(ToolTipStr);
	}
	else{
		QString	ToolTipStr=ui->textEditToolTip->toPlainText();
		ToolTip.append(ToolTipStr);
	}
	bool	enableToopTip	=ui->checkBoxEnableToolTip->isChecked();
	GetLayersBase()->GetStatusController()->SetHtml(GUIRoot
													,GUIName
													,GUIInst
													,ObjectPath
													,Comment
													,ToolTip
													,enableToopTip);
	done(true);
}

void EditStatusDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditStatusDialog::on_pushButtonLoadHTML_clicked()
{
	QString s=QFileDialog::getOpenFileName ( NULL, LangLibSolver.GetString(EditStatusDialog_LS,LID_152)/*"Load HTML"*/
											, QString()
											, /**/"HTML(*.html);;HTML(*.htm);;All files(*.*)");
	if(s.isEmpty()==false){
		QFile	File(s);
		if(File.open(QIODevice::ReadOnly)==true){
			QTextCodec *codec=QTextCodec::codecForName ( /**/"UTF-8" );
			QTextStream	TextStr(&File);
			//TextStr.setCodec ( codec );
			QTextCodec	*CurrentCodec=QTextCodec::codecForLocale();
			QTextCodec::setCodecForLocale(codec);
			QString	Str=TextStr.readAll();
			ui->plainTextEditComment->setHtml(Str);
			HTMLMode=true;
			ui->plainTextEditComment->setReadOnly(true);
			QTextCodec::setCodecForLocale(CurrentCodec);
		}
	}
}

void EditStatusDialog::on_pushButtonClear_clicked()
{
    ui->plainTextEditComment->clear();
    ui->plainTextEditComment->setReadOnly(false);
    HTMLMode=false;
}

void EditStatusDialog::on_pushButtonLoadToolTipHTML_clicked()
{
	QString s=QFileDialog::getOpenFileName ( NULL, LangLibSolver.GetString(EditStatusDialog_LS,LID_153)/*"Load HTML"*/
											, QString()
											, /**/"HTML(*.html);;HTML(*.htm);;All files(*.*)");
	if(s.isEmpty()==false){
		QFile	File(s);
		if(File.open(QIODevice::ReadOnly)==true){
			QTextCodec *codec=QTextCodec::codecForName ( /**/"UTF-8" );
			QTextStream	TextStr(&File);
			//TextStr.setCodec ( codec );
			QTextCodec	*CurrentCodec=QTextCodec::codecForLocale();
			QTextCodec::setCodecForLocale(codec);
			QString	Str=TextStr.readAll();
			ui->textEditToolTip->setHtml(Str);
			HTMLModeToopTip=true;
			ui->textEditToolTip->setReadOnly(true);
			QTextCodec::setCodecForLocale(CurrentCodec);
		}
	}

}

void EditStatusDialog::on_pushButtonToolTipClear_clicked()
{
    ui->textEditToolTip->clear();
    ui->textEditToolTip->setReadOnly(false);
    HTMLMode=false;
}

void EditStatusDialog::on_checkBoxEnableToolTip_clicked()
{
	QPalette	P=ui->textEditToolTip->palette();
	if(ui->checkBoxEnableToolTip->isChecked()==true){
		P.setColor(QPalette::Base,Qt::white);
	}
	else{
		P.setColor(QPalette::Base,Qt::cyan);
	}
	ui->textEditToolTip->setPalette(P);
}
