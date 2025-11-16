#include "AllCheckedForm.h"
#include <QDesktopWidget>

AllCheckedForm::AllCheckedForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//表示位置の設定
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

	//画面の設定
	palette[0].setColor(QPalette::Window,QColor(Qt::red));
	palette[1].setColor(QPalette::Window,QColor(Qt::gray));
	setPalette(palette[0]);

	//メッセージラベルの表示設定
	ui.lbMessage2_1->setVisible(false);
	ui.lbMessage2_2->setVisible(false);
	ui.lbMessage3_1->setVisible(false);
	ui.lbMessage3_2->setVisible(false);

	//Timer
	Index=0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

AllCheckedForm::~AllCheckedForm()
{
	delete timer;
}

void AllCheckedForm::SetShowPickupEnable(QString &KibanNo)
{
	//メッセージラベルの表示設定
	ui.lbMessage1_1->move(50,40);
	ui.lbMessage1_2->move(30,110);
	QString MessageText;
	MessageText	="LOT数";
	MessageText+=QString::number(KibanNo.toInt());
	ui.lbMessage3_1->setText(MessageText);
	ui.lbMessage3_1->setVisible(true);
	ui.lbMessage2_1->setVisible(true);
	ui.lbMessage2_2->setVisible(true);

	//画面の設定
	timer->start(500);
}

void AllCheckedForm::SetShowMaxOverEnable(QString &KibanNo)
{
	//メッセージラベルの表示設定
	ui.lbMessage1_1->move(50,40);
	ui.lbMessage1_2->move(30,110);
	QString MessageText;
	MessageText	="LOT数";
	MessageText+=QString::number(KibanNo.toInt());
	ui.lbMessage3_1->setText(MessageText);
	ui.lbMessage3_1->setVisible(true);
	ui.lbMessage3_2->setVisible(true);
	ui.lbMessage2_2->setVisible(true);

	//色の設定
	QPalette P;
	P.setColor(QPalette::WindowText,QColor(Qt::white));
	ui.lbMessage1_1->setPalette(P);
	ui.lbMessage1_2->setPalette(P);
	ui.lbMessage3_1->setPalette(P);
	ui.lbMessage2_2->setPalette(P);
	P.setColor(QPalette::WindowText,QColor(Qt::red));
	ui.lbMessage3_2->setPalette(P);
	palette[0].setColor(QPalette::Window,QColor(Qt::black));
	setPalette(palette[0]);

//	//画面の設定
//	timer->start(500);
}

void AllCheckedForm::update()
{
	Index^=1;
	setPalette(palette[Index]);
}
