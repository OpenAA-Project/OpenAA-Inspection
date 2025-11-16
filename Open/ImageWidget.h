#pragma once

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>

class ImageWidget : public QWidget
{
public:
	ImageWidget(QWidget *parent=NULL, Qt::WindowFlags f=0)
		:QWidget(parent, f),m_aspectRatioMode(Qt::IgnoreAspectRatio),m_isExpandMode(false),m_pix(),m_topLeft(0,0){};

protected:
	virtual void paintEvent(QPaintEvent *event)	override
	{
		QWidget::paintEvent(event);

		if(pixmap().isNull()==false){
			QPainter painter(this);
			if(isExpandMode()==false){
				painter.drawPixmap(topLeft(), pixmap());
			}else{
				QPixmap pix = pixmap().scaled(size(), aspectRatioMode());
				painter.drawPixmap(topLeft(), pix);
			}
		}
	};

public:
	void setExpandMode(bool expand){ m_isExpandMode = expand; };
	bool isExpandMode() const { return m_isExpandMode; };

	void setAspectRatioMode(Qt::AspectRatioMode mode){ m_aspectRatioMode = mode; };
	Qt::AspectRatioMode aspectRatioMode() const { return m_aspectRatioMode; };

	void setImage(const QPixmap &pix, bool redraw=true){ m_pix = pix; if(redraw){ update(); } };
	void setImage(const QImage &image, bool redraw=true){ setImage(QPixmap::fromImage(image), redraw); };
	QPixmap pixmap() const { return m_pix; };
	
	void setTopLeft(const QPoint &pos){ m_topLeft = pos; };
	void setTopLeft(int x, int y){ setTopLeft(QPoint(x,y)); };
	QPoint topLeft() const { return m_topLeft; };

private:
	bool m_isExpandMode;
	Qt::AspectRatioMode m_aspectRatioMode;
	QPixmap m_pix;
	QPoint m_topLeft;
};
