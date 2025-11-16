#include "mtImageToolButton.h"

mtImageToolButton::mtImageToolButton(QWidget *parent, bool checked)
	: QToolButton(parent)
{
	nDrawX = 0;
	nDrawY = 0;
	setCheckable(checked);
	setMouseTracking(true);

	connect(this,SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(released()),this,SLOT(SlotReleased()));

	BtnState=Default;
	wImg=&img;
}

mtImageToolButton::mtImageToolButton(const QImage &_img, QWidget *parent, bool checked)
	: QToolButton(parent)
{
	nDrawX = 0;
	nDrawY = 0;
	setCheckable(checked);
	setMouseTracking(true);

	connect(this,SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(released()),this,SLOT(SlotReleased()));

	BtnState=Default;
	wImg=&img;

	setImageBmp(_img);
}

mtImageToolButton::~mtImageToolButton()
{
	disconnect(this,SLOT(SlotClicked(bool)));
	disconnect(this,SLOT(SlotReleased()));

	xyArea.RemoveAll();
	fAreaList.RemoveAll();
}

void mtImageToolButton::setImageBmp(const QImage &_img)
{
	img = _img;
	wImg = &img;
	setImage();
}

void mtImageToolButton::Exec(void)
{
	setChecked(true);
	nDrawX = 3;
	nDrawY = 3;
	wImg=&PressedImg;
	repaint();
	emit SignalClicked(true);
}

void mtImageToolButton::Cancel(void)
{
	BtnState=Default;
	setChecked(false);
	nDrawX = 0;
	nDrawY = 0;
	wImg=&img;
	repaint();
}

void mtImageToolButton::showEvent ( QShowEvent * event )
{
///	setImage();
//	nDrawX = 0;
//	nDrawY = 0;
	if(nDrawX==0 && nDrawY==0){
		wImg=&img;
	}
	else{
		wImg=&PressedImg;
	}
	repaint();
}

void mtImageToolButton::paintEvent(QPaintEvent *evt)
{
	QPainter pnt2(this);
	pnt2.drawImage(nDrawX,nDrawY,*wImg);
}

void mtImageToolButton::mousePressEvent(QMouseEvent *evt)
{
	if(isCheckable()==false){
		QPoint pnt = evt->pos();
		QRgb rgb1 = img.pixel(pnt.x(),pnt.y());
		QColor col = QColor::fromRgba(rgb1);
		if ( col.alpha() == 0 ) { //&& col.red() == 0 && col.green() == 0 && col.blue() == 0 ) {
			return;
		}
		nDrawX = 3;
		nDrawY = 3;
		QToolButton::mousePressEvent(evt);
		wImg=&PressedImg;
		repaint();
		BtnState=Pressed;
	}
	else{
		QToolButton::mousePressEvent(evt);
		if(evt->button()==Qt::LeftButton){
			if(BtnState!=Pressed){
				nDrawX = 3;
				nDrawY = 3;
				wImg=&PressedImg;
				repaint();
				BtnState=Pressed;
				setChecked(true);
				if(autoExclusive ()==true){
					QWidget	*W=parentWidget();
					for(int i=0;i<W->children().count();i++){
						QToolButton	*B=dynamic_cast<QToolButton	*>(W->children()[i]);
						if(B!=NULL){
							if(B!=this && B->isCheckable()==true && B->autoRaise()==true){
								B->setChecked(false);
								mtImageToolButton	*C=dynamic_cast<mtImageToolButton *>(B);
								if(C!=NULL){
									C->OnPressed(false);
								}
							}
						}
					}
				}
			}
			else{
				BtnState=RePressed;
			}
		}
	}
}

void mtImageToolButton::mouseMoveEvent(QMouseEvent *evt)
{
	QToolButton::mouseMoveEvent(evt);

	if(isCheckable()==false){
		QPoint pnt = evt->pos();
		QRgb rgb1 = img.pixel(pnt.x(),pnt.y());
		QColor col = QColor::fromRgba(rgb1);
		if ( col.alpha() == 0 ) { //&& col.red() == 0 && col.green() == 0 && col.blue() == 0 ) {
			if(isChecked()==true){
				BtnState=Released;
				return;
			}
			if(BtnState==Pressed){
				nDrawX = 0;
				nDrawY = 0;
				wImg=&img;
				repaint();
				BtnState=Released;
			}
		}
		else if(BtnState==Released){
			if(isChecked()==true){
				BtnState=Pressed;
				return;
			}
			nDrawX = 3;
			nDrawY = 3;
			wImg=&PressedImg;
			repaint();
			BtnState=Pressed;
		}
	}
}

void mtImageToolButton::mouseReleaseEvent(QMouseEvent *evt)
{
	QToolButton::mouseReleaseEvent(evt);

	if(isCheckable()==false){
		if(BtnState==Clicked){
			QPoint pnt = evt->pos();
			QRgb rgb1 = img.pixel(pnt.x(),pnt.y());
			QColor col = QColor::fromRgba(rgb1);
			if ( col.alpha() == 0 ) { //&& col.red() == 0 && col.green() == 0 && col.blue() == 0 ) {
				setChecked(!vChecked);
			}
			else{
				emit SignalClicked(vChecked);
			}
		}
		BtnState=Default;
	}
	//else{
	//	if(BtnState==Pressed){
	//		click();
	//	}
	//}
}

void mtImageToolButton::closeEvent(QCloseEvent *evt)
{
	QToolButton::closeEvent(evt);
}

void mtImageToolButton::OnPressed(bool checked)
{
	if(checked==true){
		nDrawX = 3;
		nDrawY = 3;
		wImg=&PressedImg;
		repaint();
		BtnState=Pressed;
	}
	else{
		nDrawX = 0;
		nDrawY = 0;
		wImg=&img;
		repaint();
		BtnState=Released;
	}
}

void mtImageToolButton::SlotClicked(bool checked)
{
	if(isCheckable()==false){
		if(BtnState==Released){
			BtnState=Clicked;
///			vChecked=checked;
			vChecked=true;
		}
		else{
			//âÊñ à»äOÇ©ÇÁÉ{É^ÉìÇ™âüÇ≥ÇÍÇΩèÍçáÇ…í ÇÈ
///			emit SignalClicked(checked);
			emit SignalClicked(false);
		}
	}
	else{
		if(BtnState==Pressed){
			emit SignalClicked(true);
		}
		else{
			emit SignalClicked(false);
		}
	}
	/*
	else{
		if(checked==true){
			nDrawX = 3;
			nDrawY = 3;
			wImg=&PressedImg;
			repaint();
			BtnState=Pressed;
		}
		else{
			nDrawX = 0;
			nDrawY = 0;
			wImg=&img;
			repaint();
			BtnState=Released;
		}
	}
	*/
}
void	mtImageToolButton::click()
{
/*
	//PressedImgÇÃï€ë∂
	PressedImg.save("PressedImg.bmp","BMP");
*/
	if(isCheckable()==false){
		nDrawX = 3;
		nDrawY = 3;
		wImg=&PressedImg;
		repaint();
		BtnState=Pressed;
	}
	else{
		if(BtnState!=Pressed){
			nDrawX = 3;
			nDrawY = 3;
			wImg=&PressedImg;
			repaint();
			setChecked(true);
			BtnState=Pressed;
			if(autoExclusive ()==true){
				QWidget	*W=parentWidget();
				for(int i=0;i<W->children().count();i++){
					QToolButton	*B=dynamic_cast<QToolButton	*>(W->children()[i]);
					if(B!=NULL){
						if(B!=this && B->isCheckable()==true && B->autoRaise()==true){
							B->setChecked(false);
							mtImageToolButton	*C=dynamic_cast<mtImageToolButton *>(B);
							if(C!=NULL){
								C->OnPressed(false);
							}
						}
					}
				}
			}
			emit	clicked(true);
		}
	}
}

void mtImageToolButton::setChecked ( bool b)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==false){
		ReEntrant=true;
		if(b==true){
			click();
		}
		else{
			if(isCheckable()==false){
			}
			else{
				OnPressed(false);
			}
		}
		ReEntrant=false;
	}
}
bool mtImageToolButton::isChecked() const
{
	if(isCheckable()==false){
		return QToolButton::isChecked();
	}
	else{
		if(BtnState==Pressed){
			return true;
		}
	}
	return false;
}

void mtImageToolButton::SlotReleased()
{
	if(isCheckable()==false){
		if(BtnState==Pressed){
			if(isChecked()==false){
				nDrawX = 0;
				nDrawY = 0;
				wImg=&img;
				repaint();
			}
			BtnState=Released;
		}
	}
	else{
		if(BtnState==RePressed){
			nDrawX = 0;
			nDrawY = 0;
			wImg=&img;
			repaint();
			BtnState=Released;
		}
	}
}
