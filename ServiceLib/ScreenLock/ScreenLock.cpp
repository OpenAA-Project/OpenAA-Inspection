#include "ScreenLock.h"
#include <QSizePolicy>
#include <QGuiApplication>
#include <QScreen>

extern	bool	CloseAfterPassword;

ScreenLock::ScreenLock(const QString &_Password , const QString &title 
						,int _BreakTime
						,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),Password(_Password),BreakTime(_BreakTime)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	move(0,0);

	ui.LabelTitle->move(0,0);
	ui.LabelTitle->setText(title);

	TM.setInterval(BreakTime*1000);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.setSingleShot(true);
}

ScreenLock::~ScreenLock()
{

}

void ScreenLock::showEvent ( QShowEvent * event )
{
	QScreen	*Scr=qGuiApp->screens()[0];
	setFixedSize(Scr->geometry().width(),Scr->geometry().height());
	ui.LabelTitle->resize(width(),30);

	int	Lx=(Scr->geometry().width() -ui.frame->width())/2;
	int	Ly=(Scr->geometry().height()-ui.frame->height())/2;

	ui.frame->move(Lx,Ly);
}

void ScreenLock::on_pushButtonOK_clicked()
{
	QString	Str=ui.lineEditPassword->text();
	if(Password==Str){
		TM.start();
		setFixedSize(100,50);
		resize(100,50);
		if(CloseAfterPassword==true){
			close();
		}
	}
}

void	ScreenLock::SlotTimeOut()
{
	QScreen	*Scr=qGuiApp->screens()[0];
	setFixedSize(Scr->geometry().width(),Scr->geometry().height());
	resize(Scr->geometry().width(),Scr->geometry().height());
	ui.lineEditPassword->setText(/**/"");
}