#include "MessageForm.h"
#include <QDesktopWidget>

MessageForm::MessageForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//•\Ž¦ˆÊ’u‚ÌÝ’è
	if(parentWidget()==NULL){
		QDesktopWidget *q=QApplication::desktop();
		QRect R=q->availableGeometry ();
		//setGeometry((R.width ()-width ())/2 ,(R.height()-height())/2,width() ,height());
		move((R.width ()-width ())/2 ,(R.height()-height())/2);
	}
	else{
		QWidget	*s=parentWidget();
		//setGeometry((s->width ()-width ())/2 ,(s->height()-height())/2 ,width() ,height());
		move((s->width ()-width ())/2 ,(s->height()-height())/2);
	}

	//‰æ–Ê‚ÌÝ’è
	palette[0].setColor(QPalette::Window,QColor(Qt::magenta));
	palette[1].setColor(QPalette::Window,QColor(Qt::yellow));
	setPalette(palette[0]);

	//Timer
	Index=0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//	timer->start(500);
}

MessageForm::~MessageForm()
{
	delete timer;
}

void MessageForm::SetBlink()
{
	if(timer->isActive()==false){
		timer->start(500);
	}
}

void MessageForm::update()
{
	Index^=1;
	setPalette(palette[Index]);
}
