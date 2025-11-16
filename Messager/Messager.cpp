#include "Messager.h"
#include "XGeneralFunc.h"
#include "PopupWindow.h"
#include <ThreadSequence.h>
//#include "XExecuteInspect.h"
#include "XGUI.h"
#include "MessagerSeq.h"
#include "XMessagerClient.h"
#include <QMessageBox>

ThreadSequence	*Seq;
const	char	*MessagerRegFile="MessagerRegFile.dat";
extern	bool	ExecuteSequence;


extern	QString	LogHeaderFileName;


MStringList::MStringList(void)
{
	EventTime=XDateTime::currentDateTime();
}

Messager::Messager(LayersBase *base,int Port,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,SockServer(this)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	PopDiskReporter=new DiskReporterForm();

	if(LogHeaderFileName.isEmpty()!=NULL){
		QFileInfo	FInfo(LogHeaderFileName);
		QString	Suf		=FInfo.suffix();
		QString	Path	=FInfo.path();
		QString	BaseName=FInfo.completeBaseName();
		XDateTime	Now	=XDateTime::currentDateTime ();
		LogFileName		=Path+BaseName+Now.toString("_yyMMdd-hhmmss")+QString(".")+Suf;
	}

	Seq=new ThreadSequence(GetLayersBase(),this);
	GetLayersBase()->SetSequenceInstance(Seq);

	if(ExecuteSequence==true){
		Seq->SetFunction(SeqMessagerParamData
						,_XSeqLocalInit
						,_SetDataSpecialOperand
						,_GetDataSpecialOperand
						,_SetDataSpecialBitOperand
						,_GetDataSpecialBitOperand
						,_SetDataSpecialStringOperand
						,_GetDataSpecialStringOperand
						,_SetDataSpecialFloatOperand
						,_GetDataSpecialFloatOperand);

		QString	ErrorLine;
		if(GetParamGlobal()->Sequence_FileName.isEmpty()==false){
			QString Something;
			if(Seq->LoadStartSequenceFile(this
						,GetParamGlobal()->Sequence_FileName
						,GetParamGlobal()->IODLL_FileName
						,GetParamGlobal()->IODefine_FileName
						,ErrorLine
						,Something
						,false)==false){
				QString  msg=QString("Sequence Error:Line ")
								+ErrorLine;
				QMessageBox Q( "Error"
								, msg, QMessageBox::Critical
								, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
			}
			Seq->start();
		}
	}

	connect(&SockServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));

	SockServer.listen ( QHostAddress::Any, Port );
	ui.tableWidget->setColumnWidth(0,40);
	ui.tableWidget->setColumnWidth(1,150);
	ui.tableWidget->setColumnWidth(2,200);

	ui.tableWidgetGeneral->setColumnWidth(0,150);
	ui.tableWidgetGeneral->setColumnWidth(1,240);
	PopupW=NULL;
	setWindowState(Qt::WindowMinimized);
}

Messager::~Messager()
{
	if(PopupW!=NULL){
		delete	PopupW;
		PopupW=NULL;
	}
	if(PopDiskReporter!=NULL){
		delete	PopDiskReporter;
		PopDiskReporter=NULL;
	}
}

void	Messager::PutMessage(int GlobalPage,const QString &MessageStr)
{
	int	N=(GlobalPage+1)-MStringData.GetNumber();
	if(N!=0){
		for(int i=0;i<N;i++){
			MStringData.AppendList(new MStringList());
		}
		ui.tableWidget->setRowCount(MStringData.GetNumber());

		MStringData.GetItem(GlobalPage)->Msg=MessageStr;

		int	R=0;
		for(MStringList *L=MStringData.GetFirst();L!=NULL;L=L->GetNext(),R++){
			SetDataToTable(ui.tableWidget,0,R,QString::number(R));
			SetDataToTable(ui.tableWidget,1,R,L->EventTime.toString("yy/MM/dd hh:mm:ss.zzz"));
			SetDataToTable(ui.tableWidget,2,R,L->Msg);
		}
	}
	else{
		MStringList *L=MStringData.GetItem(GlobalPage);
		L->Msg=MessageStr;
		SetDataToTable(ui.tableWidget,1,GlobalPage,L->EventTime.toString("yy/MM/dd hh:mm:ss.zzz"));
		SetDataToTable(ui.tableWidget,2,GlobalPage,L->Msg);
	}
	WriteLog(GlobalPage,MessageStr);
}

void	Messager::PutMessage(int TypeValue,int GlobalPage,const QString &MessageStr)
{
	if(TypeValue==1){
		MStringList	*L=new MStringList();
		L->Msg=MessageStr;
		MStringDataGeneral.AppendList(L);

		ui.tableWidgetGeneral->insertRow(0);
		SetDataToTable(ui.tableWidgetGeneral,0,0,L->EventTime.toString("yy/MM/dd hh:mm:ss.zzz"));
		SetDataToTable(ui.tableWidgetGeneral,1,0,L->Msg);
	}
	else if(TypeValue==2){
		if(PopupW==NULL){
			PopupW=new PopupWindow(MessageStr);
		}
		PopupW->ShowMessage(MessageStr);

		PopupW->show();
	}
	else if(TypeValue==3){
		if(PopupW!=NULL){
			PopupW->hide();
		}
	}
	else if(TypeValue==4){
		PopDiskReporter->show();
		PopDiskReporter->SetList(MessageStr);
	}
	WriteLog(TypeValue,GlobalPage,MessageStr);
}

void	Messager::WriteLog(int GlobalPage,const QString &MessageStr)
{
	if(LogFileName.isEmpty()==false){
		QFile	FL(LogFileName);
		if(FL.open(QIODevice::Append | QIODevice::Text)==true){
			QString	s=XDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss.zzz")
				+ QString(" Page=")+QString::number(GlobalPage)
				+ QString(" Msg=")+MessageStr;
			WriteLog(FL,s);
		}
	}
}

void	Messager::WriteLog(int TypeValue,int GlobalPage,const QString &MessageStr)
{
	if(LogFileName.isEmpty()==false){
		QFile	FL(LogFileName);
		if(FL.open(QIODevice::Append | QIODevice::Text)==true){
			QString	s=XDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss.zzz")
				+ QString(" Type=")+QString::number(TypeValue)
				+ QString(" Page=")+QString::number(GlobalPage)
				+ QString(" Msg=")+MessageStr;
			WriteLog(FL,s);
		}
	}
}
void	Messager::WriteLog(QFile &FL,const QString &MessageStr)
{
	QTextStream	Stream(&FL);
	Stream<<MessageStr<<"\n";
}

void Messager::SlotNewConnection()
{
	MessagePopper	*s=new MessagePopper(this);
	s->Sv=SockServer.nextPendingConnection();
	connect(s->Sv,SIGNAL(readyRead())	,s,SLOT(SlotReadyRead()));
	connect(s->Sv,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	s->Sv->setTextModeEnabled(true);
}

void	MessagePopper::SlotReadyRead()
{
	int32	Len;
	if(Sv->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return;
	}
	QByteArray	ByteArray=Sv->readAll();

	QBuffer	RBuff(&ByteArray);
	MessageList		R;
	if(RBuff.open(QIODevice::ReadOnly)==false)
		return;
	if(::Load(&RBuff,R.MType)==false)
		return;
	if(::Load(&RBuff,R.GlobalPage)==false)
		return;
	if(::Load(&RBuff,R.Message)==false)
		return;
	if(::Load(&RBuff,R.ArrayData)==false)
		return;

	Parent->PutMessage(R.MType,R.GlobalPage,R.Message);
}

void	MessagePopper::SlotDisconnected()
{
	deleteLater();
}



void Messager::on_pushButtonSequence_clicked()
{
	Seq->ShowSimulateSequence(this);
}

void Messager::on_pushButtonClose_clicked()
{
	QCoreApplication::quit ();
}