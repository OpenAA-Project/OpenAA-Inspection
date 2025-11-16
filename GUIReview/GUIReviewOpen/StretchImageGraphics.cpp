#include "GUIReviewOpenResource.h"
#include "StretchImageGraphics.h"

StretchImageGraphics::StretchImageGraphics(QWidget *parent)
	:QGraphicsView(parent),m_image()
{}

StretchImageGraphics::~StretchImageGraphics()
{}

void StretchImageGraphics::setImage(const QImage &img)
{
	m_image = img;
	viewport()->update();
}

void StretchImageGraphics::clearImage()
{
	m_image = QImage();
	viewport()->update();
}

QImage StretchImageGraphics::image(bool scaled, Qt::AspectRatioMode mode) const
{
	if(scaled==false){
		return m_image;
	}

	return m_image.scaled(viewport()->size(), mode);
}

void StretchImageGraphics::paintEvent(QPaintEvent *event)
{
	QGraphicsView::paintEvent(event);
	if(m_image.isNull()==true){
		return;
	}

	QPainter painter(viewport());

	QImage img = m_image.scaled(viewport()->size(), Qt::KeepAspectRatio);

	int x = (viewport()->width() - img.width())/2;
	int y = (viewport()->height() - img.height())/2;

	painter.drawImage(x, y, img);
}
