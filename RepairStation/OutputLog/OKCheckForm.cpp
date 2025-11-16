#include "OKCheckForm.h"
#include <QDesktopWidget>

OKCheckForm::OKCheckForm(QWidget *parent)
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

	//色の設定（ウィンドウを赤く表示）
	QPalette palette;
	palette.setColor(QPalette::Window,QColor(Qt::cyan));
	setPalette(palette);}

OKCheckForm::~OKCheckForm()
{
}
