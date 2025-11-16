#include "mtImageButtonColored.h"
#include "XGeneralFunc.h"

#define BLEND_ALPHA 0.5

mtImageButtonColored::mtImageButtonColored(const QImage &_img, const QColor &_col, QWidget *parent)
	: mtImageButton(_img,parent)
{
	Col = _col;
	nBlend_Alfa = BLEND_ALPHA;
	img2 = img;
}

mtImageButtonColored::mtImageButtonColored(const QImage &_img, QWidget *parent)
	: mtImageButton(_img,parent)
{
	QPalette P=palette();
	Col = P.color(QPalette::Button);
	nBlend_Alfa = BLEND_ALPHA;
	img2 = img;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}

mtImageButtonColored::~mtImageButtonColored()
{
	disconnect(this,SLOT(SlotClicked()));
}

QColor mtImageButtonColored::color()	const
{
	return Col;
}

void mtImageButtonColored::setColor(const QColor &col)
{
	Col = col;
	setImageCombine();
	//img.save("D:/Tmp/ppp.png","PNG");
	//img2.save("D:/Tmp/ppp_org.png","PNG");
	img.save("E:/Tmp/ppp.png","PNG");
	img2.save("E:/Tmp/ppp_org.png","PNG");
	repaint();
}

void mtImageButtonColored::setColor(const QString &ColString)
{
	QColor col=QString2QColor(ColString);
	setColor(col);
}

void mtImageButtonColored::setImageCombine() {
	QRgb rgb0, rgb1, rgb2=Col.rgb();
	for( int i=0; i<img2.width(); i++ ) {
		QColor cl;
		for( int j=0; j<img2.height(); j++ ) {
			rgb1 = img2.pixel(i,j);
			if ( qAlpha(rgb1) != 0 ) {
				int r = qRed(rgb1);
				int g = qGreen(rgb1);
				int b = qBlue(rgb1);
				r = (int)(nBlend_Alfa*r+(1-nBlend_Alfa)*qRed(rgb2));
				g = (int)(nBlend_Alfa*g+(1-nBlend_Alfa)*qGreen(rgb2));
				b = (int)(nBlend_Alfa*b+(1-nBlend_Alfa)*qBlue(rgb2));
				cl = QColor(r,g,b);
				rgb0 = cl.rgb();
				img.setPixel(i,j,rgb0);
			} else {
				img.setPixel(i,j,rgb1);
			}
		}
	}
}