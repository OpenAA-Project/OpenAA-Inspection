#pragma once

#include <QWidget>
#include <QPixmap>
#include <QList>
#include "ReviewStructureItems.h"

class ImageWidgetInThumbnail : public QWidget
{
	Q_OBJECT

public:
	ImageWidgetInThumbnail(QWidget *parent=NULL);
	~ImageWidgetInThumbnail();

public:
	void setPixmap(QPixmap pix){ m_pixmap = pix; };
	QPixmap pixmap(void){ return m_pixmap; };

	void setPoints(QList<ReviewNGPoint> points){ m_points = points; };
	void setTopLeftPoint(QPoint pos){ TopLeftPos = pos; };
	QList<ReviewNGPoint> points(void){ return m_points; };

	void setRound(int round){ m_round = round; };
	int round(void){ return m_round; };

	void setRoundColor(QColor color){ m_color = color; };
	QColor roundColor(void){ return m_color; };

	void setDrawNGSingEnable(bool enable){ if(m_isDrawNGSingEnable!=enable){ m_isDrawNGSingEnable = enable; update(); }; };
	bool isDrawNGSingEnable() const { return m_isDrawNGSingEnable; };

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

public:
	QPixmap m_pixmap;
	QList<ReviewNGPoint> m_points;
	QPoint TopLeftPos;
	int m_round;
	QColor m_color;
	bool m_isDrawNGSingEnable;
};