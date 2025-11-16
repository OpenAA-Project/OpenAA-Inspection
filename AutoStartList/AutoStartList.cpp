#include "AutoStartList.h"
#include "XAutoStart.h"
#include "AutoStartParamList.h"
#include "XGeneralFunc.h"

extern	QString		DefaultFileName;

AutoStartList::AutoStartList(bool _EnableClose ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,EnableClose(_EnableClose),AutoStartExeListData(DefaultFileName)
	,LThread(this,this)
{
	ui.setupUi(this);
	AutoStartExeListData.LoadDefault();
	Counting=true;
	Ticking	=true;
	AllFinished=true;
	//setWindowFlags(Qt::WindowTitleHint);

	setWindowTitle(DefaultFileName);
	AutoStartExeListData.SetParent(this);

	minimizeAction	=new QAction(/**/"Minimize",this);
	connect(minimizeAction	,SIGNAL(triggered()),this,SLOT(hide()));
	showAction		=new QAction(DefaultFileName,this);
	connect(showAction		,SIGNAL(triggered()),this,SLOT(showNormal()));
	quitAction		=new QAction(/**/"quit",this);
	connect(quitAction		,SIGNAL(triggered()),qApp,SLOT(quit()));

	TrayIconMenu=new QMenu(this);
	TrayIconMenu->addAction(minimizeAction);
	TrayIconMenu->addAction(showAction);
	TrayIconMenu->addAction(quitAction);

	TrayIcon	=new QSystemTrayIcon(this);
	TrayIcon->setContextMenu(TrayIconMenu);
	TrayIcon->setIcon(QIcon(QPixmap(/**/":Qtres/AutoStartList.png")));
	TrayIcon->show();


	LThread.start();
	
	ui.dialLoop->setMaximum(AutoStartExeListData.LoopCount);
	ui.dialLoop->setValue(0);
	move(0,0);

	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(Timeout()));
	TM.start();
}

AutoStartList::~AutoStartList()
{
	LThread.SetTerminate(true);
	LThread.wait(1000);
}

bool	AutoStartList::IsFinishedAll(void)
{
	return AutoStartExeListData.IsFinishedAll();
}

bool	AutoStartList::ExecuteAll(void)
{
	AutoStartExeListData.ExecuteAll();
	AutoStartExeListData.WaitForStarted();


	AutoStartExeListData.ResizeAlignment();
	return true;
}

void	AutoStartList::Timeout()
{
	if(IsFinishedAll()==true){
		AllFinished=true;
		int	N=ui.dialLoop->value();

		QString	FileName=QString("RapidBoot.tmp");
		if(QFile::exists(FileName)==true){
			N=ui.dialLoop->maximum();
			::GSleep(500);
		}
		if(ui.dialLoop->maximum()<=N){
			if(Counting==false){
				Counting=true;
			}
			else{
				if(AutoStartExeListData.Tasktray==true){
					hide();
				}
				Counting=false;
				ui.dialLoop->setValue(0);
			}
		}
		else{
			if(Ticking==true){
				ui.dialLoop->setValue(N+1);
			}
			if(Counting==false){
				show();
			}
			Counting=true;
		}
	}
	else{
		AllFinished=false;
	}
}

void	AutoStartList::closeEvent(QCloseEvent *ev)
{
	if(EnableClose==false){
		if(TrayIcon->isVisible()==true){
			//hide();
			ev->ignore();
		}
	}
}


void AutoStartList::on_pushButtonStart_clicked()
{
	Ticking=true;
	ui.dialLoop->setValue(ui.dialLoop->maximum());
}

void AutoStartList::on_toolButtonStop_clicked()
{
	if(ui.toolButtonStop->isChecked()==true){
		Ticking=false;
		ui.pushButtonStart->setEnabled(false);
	}
	else{
		Ticking=true;
		ui.pushButtonStart->setEnabled(true);
	}
}

void AutoStartList::on_pushButtonParam_clicked()
{
	Ticking=false;
	AutoStartParamList	D(AutoStartExeListData);
	if(D.exec()==(int)true){
		AutoStartExeListData=D.TmpData;
		AutoStartExeListData.SaveDefault();
		ui.dialLoop->setMaximum(AutoStartExeListData.LoopCount);
	}
	Ticking=true;
}

