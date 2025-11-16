#pragma once

#include <QWidget>
#include <QPainter>

class StretchImageWidget : public QWidget
{
	Q_OBJECT

public:
	StretchImageWidget(QWidget *parent=NULL, const QImage &image=QImage()):QWidget(parent),m_image(image){};

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override{
		QWidget::paintEvent(event);

		QPainter painter(this);
		QImage sImage = image();
		sImage = sImage.scaled(size(), Qt::KeepAspectRatio);
		painter.drawImage(0, 0, sImage);
	};

public:
	void setImage(const QImage &image){ m_image = image; };
	QImage image(void) const { return m_image; };

signals:
	void requireUpdateImage();

public:
	QImage m_image;
};
