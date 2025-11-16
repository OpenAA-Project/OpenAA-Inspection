#pragma once

#include <QtGui>
#include <QGraphicsView>

class StretchImageGraphics : public QGraphicsView
{
	Q_OBJECT

public:
	StretchImageGraphics( QWidget *parent=0);
	~StretchImageGraphics();

public:
	void setImage(const QImage &img);
	void clearImage();
	QImage image(bool scaled=false, Qt::AspectRatioMode mode=Qt::IgnoreAspectRatio) const;

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;

private:
	QImage m_image;
};
