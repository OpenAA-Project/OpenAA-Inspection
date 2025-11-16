#include "ShowThumbnailResource.h"
#include "ImageWidgetInThumbnail.h"
#include "../XGUIReviewCommon.h"
#include <QPainter>
#include <QDebug>

ImageWidgetInThumbnail::ImageWidgetInThumbnail(QWidget *parent)
	:QWidget(parent),m_pixmap(),m_points(),m_round(10),m_color(Qt::red),m_isDrawNGSingEnable(true)
{}

ImageWidgetInThumbnail::~ImageWidgetInThumbnail()
{
}

void ImageWidgetInThumbnail::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	if(m_pixmap.isNull()==true){
		return;
	}

	QPainter painter;

	// Pixをウィンドウサイズにスケーリング
	QPixmap pix = m_pixmap.scaled(size(), Qt::KeepAspectRatio);

	if(isDrawNGSingEnable()==true){
		// スケーリング結果の伸縮率計算
		double zoomRate = pix.height() / (double)m_pixmap.height();

		painter.begin(&pix);// Pixに描画開始
		QPen pen(m_color);// 指定されている色でNGを描画
		painter.setPen(pen);
		for(QList<ReviewNGPoint>::ConstIterator it=m_points.constBegin(); it!=m_points.constEnd(); it++){

			QPoint center = (QPoint(it->x - TopLeftPos.x(), it->y - TopLeftPos.y())) * zoomRate;

			Review::DrawNGShapeToPainter(&painter, it->Tag.NGColor, it->Tag.NGShape, center, m_round);

																																																							//switch(it->Tag.NGShape){
		//case LibNGTypeItem::NGShapeType::NG_Circle:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawEllipse(center, NGSingSize, NGSingSize);
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_Cross:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawLine(center - QPoint(0, NGSingSize/2), center + QPoint(0, NGSingSize));
		//	painter.drawLine(center - QPoint(NGSingSize, 0), center + QPoint(NGSingSize, 0));
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_FilledCircle:
		//	painter.setBrush(Qt::BrushStyle::SolidPattern);
		//	painter.drawEllipse(center, NGSingSize, NGSingSize);
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_FilledRect:
		//	painter.setBrush(Qt::BrushStyle::SolidPattern);
		//	painter.drawRect(center.x()-NGSingSize, center.y()-NGSingSize, NGSingSize, NGSingSize);
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_FilledStar:
		//	painter.setBrush(Qt::BrushStyle::SolidPattern);
		//	painter.drawText(center.x()-NGSingSize, center.y()-NGSingSize, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"★");
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_Rectangle:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawRect(center.x()-NGSingSize, center.y()-NGSingSize, NGSingSize, NGSingSize);
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_Sharp:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawText(center.x()-NGSingSize, center.y()-NGSingSize, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"#");
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_Star:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawText(center.x()-NGSingSize, center.y()-NGSingSize, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"☆");
		//	break;
		//case LibNGTypeItem::NGShapeType::NG_X:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawLine(center - QPoint(NGSingSize, NGSingSize), center + QPoint(-NGSingSize, -NGSingSize));
		//	painter.drawLine(center - QPoint(-NGSingSize, NGSingSize), center + QPoint(NGSingSize, -NGSingSize));
		//	break;
		//default:
		//	painter.setBrush(Qt::BrushStyle::NoBrush);
		//	painter.drawEllipse(center, NGSingSize, NGSingSize); 
		//	break;
		//}


		//painter.drawEllipse(QPoint(it->x()*zoomRate, it->y()*zoomRate), m_round, m_round);// ○

		//pen.setColor(Qt::white);
		//painter.setPen(pen);
		//painter.drawPoint(it->x()*zoomRate, it->y()*zoomRate);
		//pen.setColor(Qt::GlobalColor::magenta);
		//painter.setPen(pen);
		//painter.drawRect(it->x()*zoomRate - m_round, it->y()*zoomRate - m_round, m_round*2, m_round*2);
		//qDebug() << "ImageSize:" << pix.size();
		//qDebug() << "NGPoint:" << QPoint(it->x()*zoomRate, it->y()*zoomRate);
		}
		painter.end();// Pixに描画終了
	}

	// 描画をだいたい中心になるように描画位置を指定
	int top = (size().height() - pix.height())/2;
	int left = (size().width() - pix.width())/2;

	painter.begin(this);
	painter.drawPixmap(left, top, pix);// Pixを描画
	painter.end();
}