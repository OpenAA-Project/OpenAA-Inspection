#include "mtImageButton.h"

mtImageButton::mtImageButton(const QImage &_img, QWidget *parent)
	: QPushButton(parent),TM(this)
{
	img = _img;
	nDrawX = 0;
	nDrawY = 0;
	setImage();
	//resize(img.width(),img.height());
	connect(this,SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(&TM,SIGNAL(timeout()),this,SLOT(TimeOutOneShot()));
	TM.setSingleShot(true);
	TM.setInterval(250);
}

mtImageButton::~mtImageButton()
{
	disconnect(this,SLOT(SlotClicked(bool)));
	disconnect(this,SLOT(TimeOutOneShot()));
}

void mtImageButton::paintEvent(QPaintEvent *evt)
{
	QPainter pnt2(this);
	pnt2.drawImage(nDrawX,nDrawY,img);
}

void mtImageButton::mousePressEvent(QMouseEvent *evt)
{
	QPoint pnt = evt->pos();
	QRgb rgb1 = img.pixel(pnt.x(),pnt.y());
	QColor col = QColor::fromRgba(rgb1);
	if ( col.alpha() == 0 ) { //&& col.red() == 0 && col.green() == 0 && col.blue() == 0 ) {
		return;
	}
	nDrawX = 3;
	nDrawY = 3;
	repaint();
}

void mtImageButton::mouseReleaseEvent(QMouseEvent *evt)
{
	nDrawX = 0;
	nDrawY = 0;
	repaint();
	emit SignalClicked();
}
void	mtImageButton::click ()
{
	nDrawX = 3;
	nDrawY = 3;
	repaint();
	TM.start();
	emit SignalClicked();
}

void mtImageButton::SlotClicked(bool checked)
{
	click ();
}

void	mtImageButton::TimeOutOneShot()
{
	nDrawX = 0;
	nDrawY = 0;
	repaint();
}
