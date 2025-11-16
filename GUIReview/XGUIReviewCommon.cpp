#include "XGUIReviewCommon.h"
#include <QStaticText>
//
//void GUIReview::DrawNGShapeToPainter(QPainter *painter, QColor color, LibNGTypeItem::NGShapeType shape, QPoint center, int round)
//{
//	QPen pen(color);
//	QBrush brush(color);
//	int tmp;
//	qreal tmp_reql;
//	QRect rect;
//	QFont old_font = painter->font();
//	QFont font = old_font;
//	QStaticText stext;
//
//	painter->setPen(pen);
//
//	switch(shape){
//	case LibNGTypeItem::NGShapeType::NG_Circle:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		painter->drawEllipse(center, round, round);
//		break;
//	case LibNGTypeItem::NGShapeType::NG_Cross:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		painter->drawLine(center - QPoint(0, round), center + QPoint(0, round));
//		painter->drawLine(center - QPoint(round, 0), center + QPoint(round, 0));
//		break;
//	case LibNGTypeItem::NGShapeType::NG_FilledCircle:
//		//painter->setBrush(Qt::BrushStyle::SolidPattern);
//		brush.setStyle(Qt::BrushStyle::SolidPattern);
//		painter->setBrush(brush);
//		painter->drawEllipse(center, round, round);
//		break;
//	case LibNGTypeItem::NGShapeType::NG_FilledRect:
//		brush.setStyle(Qt::BrushStyle::SolidPattern);
//		painter->setBrush(brush);
//		painter->drawRect(center.x()-round, center.y()-round, round*2, round*2);
//		break;
//	case LibNGTypeItem::NGShapeType::NG_FilledStar:
//		brush.setStyle(Qt::BrushStyle::SolidPattern);
//		painter->setBrush(brush);
//		round = 15;
//		painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::TextJustificationForced, /**/"š");
//		break;
//	case LibNGTypeItem::NGShapeType::NG_Rectangle:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		painter->drawRect(center.x()-round, center.y()-round, round*2, round*2);
//		break;
//	case LibNGTypeItem::NGShapeType::NG_Sharp:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//
//		tmp = (int)((round * 2.0) / 3.0 + 0.5);
//		painter->drawLine(center.x() - round + tmp + 1, center.y() - round, center.x() - round + tmp - 1, center.y() + round);// |
//		painter->drawLine(center.x() - round + 2*tmp + 1, center.y() - round, center.x() - round + 2*tmp - 1, center.y() + round);// ||
//		painter->drawLine(center.x() - round, center.y() - round + tmp + 1, center.x() + round, center.y() - round + tmp - 1);// -
//		painter->drawLine(center.x() - round, center.y() - round + 2*tmp + 1, center.x() + round, center.y() - round + 2*tmp - 1);// =
//		
//		//painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::AlignJustify, /**/"#");
//		break;
//	case LibNGTypeItem::NGShapeType::NG_Star:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		round = 15;
//		painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::AlignJustify, /**/"™");
//		break;
//	case LibNGTypeItem::NGShapeType::NG_X:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		painter->drawLine(center.x() - round, center.y() - round, center.x() + round, center.y() + round);
//		painter->drawLine(center.x() + round, center.y() - round, center.x() - round, center.y() + round);
//		break;
//	default:
//		painter->setBrush(Qt::BrushStyle::NoBrush);
//		painter->drawEllipse(center, round, round); 
//		break;
//	}
//}
