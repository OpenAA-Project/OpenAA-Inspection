#include "EditStatusComment.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QTextCodec>
#include "XGeneralFunc.h"

EditStatusComment::EditStatusComment(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),StatusControl(NULL)
{
	ui.setupUi(this);

	ui.tableWidgetGUIAll->setColumnWidth(0,100);
	ui.tableWidgetGUIAll->setColumnWidth(1,100);
	ui.tableWidgetGUIAll->setColumnWidth(2,100);

	HTMLMode=false;
	HTMLModeToopTip	=false;
}

EditStatusComment::~EditStatusComment()
{

}

void	EditStatusComment::resizeEvent ( QResizeEvent * event )
{
	ui.frameBottom->setGeometry(0,height()-ui.frameBottom->height(),width(),ui.frameBottom->height());
	ui.frameComment->resize(width()-20,ui.frameBottom->geometry().top()-ui.frameComment->geometry().top());
	ui.frameCommentText->setGeometry(0,ui.frameComment->height()-ui.frameCommentText->height(),ui.frameComment->width(),ui.frameCommentText->height());
	ui.textEditCommentNow->resize(ui.frameComment->width()-20,ui.frameCommentText->geometry().top()-ui.textEditCommentNow->geometry().top());
}

void EditStatusComment::on_pushButtonLoad_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, QString("Load Comment file")
												,"CommentDef.dat"
												,/**/"Opinion (*.dat);;All files (*.*)");
	if(FileName.isNull()==false){
		if(StatusControl.LoadDef(FileName)==true){
			ShowOpinions();
		}
	}
}

void EditStatusComment::on_pushButtonSave_clicked()
{
	QString FileName=QFileDialog::getSaveFileName ( 0, QString("Save Comment file")
												,"CommentDef.dat"
												,/**/"Opinion (*.dat);;All files (*.*)");
	if(FileName.isNull()==false){
		StatusControl.SaveDef(FileName);
	}

}

void	EditStatusComment::ShowOpinions(void)
{
	ui.tableWidgetGUIAll->setRowCount(StatusControl.GetCount());
	int	Row=0;
	for(StatusOpinionInGUI *c=StatusControl.GetFirst();c!=NULL;c=c->GetNext()){
		SetDataToTable(ui.tableWidgetGUIAll ,0 ,Row ,c->GetGUIRoot());
		SetDataToTable(ui.tableWidgetGUIAll ,1 ,Row ,c->GetGUIName());
		SetDataToTable(ui.tableWidgetGUIAll ,2 ,Row ,c->GetGUIInst());
		Row++;
	}
	ui.listWidgetCommentOpinionList->clear();
	ui.listWidgetModeAll->clear();
	ui.textEditCommentNow->clear();
	ui.textEditCommentNow->setReadOnly(false);
	ui.textEditToolTip->clear();
	ui.textEditToolTip->setReadOnly(false);
}

void EditStatusComment::on_pushButtonClose_clicked()
{
	close();
}

void EditStatusComment::on_pushButtonRegist_clicked()
{
	QString	Str=ui.textEditCommentNow->toPlainText();
	QStringList	List;
	List.append(Str);

	QString	ToolTipStr=ui.textEditToolTip->toPlainText();
	QStringList	ToolTipList;
	ToolTipList.append(ToolTipStr);

	int	Row=ui.tableWidgetGUIAll->currentRow();
	bool	enableToopTip	=ui.checkBoxEnableToolTip->isChecked();
	if(Row>=0){
		StatusOpinionInGUI	*L=StatusControl.GetItem(Row);
		int	R=ui.listWidgetCommentOpinionList->currentRow();
		if(R>=0){
			CommentOpinion *c=L->NPListPackSaveLoad<CommentOpinion>::GetItem(R);
			if(c!=NULL){
				if(HTMLMode==true){
					c->SetHTMLMode(Str);
				}
				else{
					c->SetComment(List);
				}
				if(HTMLModeToopTip==true){
					c->SetHTMLModeToopTip(ToolTipStr);
				}
				else{
					c->SetToolTip(ToolTipList);
				}
				c->SetEnableToolTip(enableToopTip);
			}
		}
	}
}

void EditStatusComment::on_tableWidgetGUIAll_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetGUIAll->currentRow();
	if(Row>=0){
		StatusOpinionInGUI	*L=StatusControl.GetItem(Row);
		if(L!=NULL){
			ui.listWidgetCommentOpinionList->clear();
			int	R=0;
			for(CommentOpinion *c=L->NPListPackSaveLoad<CommentOpinion>::GetFirst();c!=NULL;c=c->GetNext(),R++){
				ui.listWidgetCommentOpinionList->addItem(QString::number(R));
			}
		}
	}
}

void EditStatusComment::on_listWidgetCommentOpinionList_clicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetGUIAll->currentRow();
	if(Row>=0){
		StatusOpinionInGUI	*L=StatusControl.GetItem(Row);
		int	R=ui.listWidgetCommentOpinionList->currentRow();
		if(R>=0){
			CommentOpinion *c=L->NPListPackSaveLoad<CommentOpinion>::GetItem(R);
			if(c!=NULL){
				ui.listWidgetModeAll->clear();
				ui.listWidgetModeAll->addItems(c->GetObjectPath());
				
				if(c->IsHTML()==true){
					ui.textEditCommentNow->setHtml(c->GetCommentString());
					HTMLMode=true;
					ui.textEditCommentNow->setReadOnly(true);
				}
				else{
					ui.textEditCommentNow->setPlainText(c->GetCommentString());
					HTMLMode=false;
					ui.textEditCommentNow->setReadOnly(false);
				}
				if(c->IsHTMLToopTip()==true){
					ui.textEditToolTip->setHtml(c->GetToolTipString());
					HTMLModeToopTip=true;
					ui.textEditToolTip->setReadOnly(true);
				}
				else{
					ui.textEditToolTip->setPlainText(c->GetToolTipString());
					HTMLModeToopTip=false;
					ui.textEditToolTip->setReadOnly(false);
				}
				ui.checkBoxEnableToolTip->setChecked(c->IsEnableToolTop());
				on_checkBoxEnableToolTip_clicked();
			}
		}
	}
}

void EditStatusComment::on_pushButtonLoadHTML_clicked()
{
	QString s=QFileDialog::getOpenFileName ( NULL, "Load HTML"
											, QString()
											, /**/"HTML(*.html);;HTML(*.htm);;All files(*.*)");
	if(s.isEmpty()==false){
		QFile	File(s);
		if(File.open(QIODevice::ReadOnly)==true){
			QList<QByteArray> CodeList=QTextCodec::availableCodecs ();
			QTextCodec *codec=QTextCodec::codecForName ( /**/"UTF-8" );
			QTextCodec *CurrentCodec=QTextCodec::codecForLocale();
			QTextCodec::setCodecForLocale(codec);

			QTextStream	TextStr(&File);
			QString	Str=TextStr.readAll();
			ui.textEditCommentNow->setHtml(Str);
			ui.textEditCommentNow->setReadOnly(true);
			HTMLMode=true;
			QTextCodec::setCodecForLocale(CurrentCodec);
		}
	}
}

void EditStatusComment::on_pushButtonClear_clicked()
{
    ui.textEditCommentNow->clear();
    ui.textEditCommentNow->setReadOnly(false);
    HTMLMode=false;
}

void EditStatusComment::on_pushButtonFont_clicked()
{
	bool ok;
	QFont	InitFont=ui.textEditCommentNow->font();
	QFont F=QFontDialog::getFont ( &ok,InitFont, NULL
								,"Comment font");
	if(ok==true){
		ui.textEditCommentNow->setFont(F);
	}
}

void EditStatusComment::on_pushButtonLoadHTMLToolTip_clicked()
{
	QString s=QFileDialog::getOpenFileName ( NULL, "Load HTML"
											, QString()
											, /**/"HTML(*.html);;HTML(*.htm);;All files(*.*)");
	if(s.isEmpty()==false){
		QFile	File(s);
		if(File.open(QIODevice::ReadOnly)==true){
			QList<QByteArray> CodeList=QTextCodec::availableCodecs ();
			QTextCodec *codec=QTextCodec::codecForName ( /**/"UTF-8" );
			QTextCodec *CurrentCodec=QTextCodec::codecForLocale();
			QTextCodec::setCodecForLocale(codec);

			QTextStream	TextStr(&File);
			QString	Str=TextStr.readAll();
			ui.textEditToolTip->setHtml(Str);
			ui.textEditToolTip->setReadOnly(true);
			HTMLModeToopTip=true;
			QTextCodec::setCodecForLocale(CurrentCodec);
		}
	}
}

void EditStatusComment::on_pushButtonFontToolTip_clicked()
{
	bool ok;
	QFont	InitFont=ui.textEditCommentNow->font();
	QFont F=QFontDialog::getFont ( &ok,InitFont, NULL
								,"ToolTip font");
	if(ok==true){
		ui.textEditToolTip->setFont(F);
	}
}

void EditStatusComment::on_pushButtonClearToolTip_clicked()
{
    ui.textEditToolTip->clear();
    ui.textEditToolTip->setReadOnly(false);
    HTMLModeToopTip=false;
}

void EditStatusComment::on_checkBoxEnableToolTip_clicked()
{
	QPalette	P=ui.textEditToolTip->palette();
	if(ui.checkBoxEnableToolTip->isChecked()==true){
		P.setColor(QPalette::Base,Qt::white);
	}
	else{
		P.setColor(QPalette::Base,Qt::cyan);
	}
	ui.textEditToolTip->setPalette(P);
}
