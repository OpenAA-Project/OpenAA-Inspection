#include "NGImageForReviewResource.h"
#include "PieceDisplay.h"
#include "../XGUIReviewCommon.h"
#include <QPainter>
#include <QDebug>

PieceDisplay::PieceDisplay(QWidget *parent)
	:mtGraphicUnit(parent),Image(),TopLeftPos(0, 0),zoomStage(0)
{
	connect(this, SIGNAL(SignalMouseWheel(int,int,int)), SLOT(SlotWheel(int, int, int)));
	connect(this, SIGNAL(SignalMouseRDown(int,int)), SLOT(SlotMouseRDown(int, int)));
	connect(this, SIGNAL(SignalShiftAll()), SLOT(SlotShiftedImage()));
}

void PieceDisplay::setImage(QImage image ,int RotateAngle)
{
	Image = image;
	ImageOrg = image;
	zoomStage = 0;
	GetCanvas()->movx = 0;
	GetCanvas()->movy = 0;
	updateImage(RotateAngle);
}

void	PieceDisplay::Clear(int RotateAngle)
{
	Image.fill(0);
	ImageOrg.fill(0);
	zoomStage = 0;
	GetCanvas()->movx = 0;
	GetCanvas()->movy = 0;
	updateImage(RotateAngle);
}

void PieceDisplay::SlotWheel(int delta, int x, int y)
{
	if(Image.isNull()==true)return;

	if(delta>0){
		if(zoomStage>2)return;
		Image = ImageOrg.scaled(Image.size()*2, Qt::KeepAspectRatio);
		zoomStage++;
		updateImage();
		ZoomDraw(GetCanvas()->movx - (GetCanvas()->movx+x)/2, GetCanvas()->movy - (GetCanvas()->movy+y)/2, pow(2.0, zoomStage));
	}else{
		if(zoomStage<-2)return;
		Image = ImageOrg.scaled(Image.size()/2, Qt::KeepAspectRatio);
		zoomStage--;
		updateImage();
		ZoomDraw(GetCanvas()->movx + (GetCanvas()->movx+x), GetCanvas()->movy + (GetCanvas()->movy+y), pow(2.0, zoomStage));
	}
	emit SignalImageStateChanged(zoomStage, GetCanvas()->movx, GetCanvas()->movy);
}

void PieceDisplay::SlotSetImageState(int zoomStage, int movx, int movy)
{
	if(this->zoomStage!=zoomStage){
		this->zoomStage = zoomStage;
		Image = ImageOrg.scaled(ImageOrg.size()*pow(2.0, zoomStage), Qt::KeepAspectRatio);
		updateImage();
	}
	if(GetCanvas()->movx!=movx || GetCanvas()->movy!=movy){
		ZoomDraw(movx, movy, pow(2.0, zoomStage));
	}
}

void PieceDisplay::SlotShiftedImage()
{
	emit SignalImageStateChanged(zoomStage, GetCanvas()->movx, GetCanvas()->movy);
}

void PieceDisplay::SlotMouseRDown(int,int)
{
	zoomStage = 0;
	Image = ImageOrg;
	updateImage();
	ZoomDraw(0, 0, 1.0);
	emit SignalImageStateChanged(zoomStage, GetCanvas()->movx, GetCanvas()->movy);
}

void PieceDisplay::updateImage(int RotateAngle)
{
	if(Image.isNull()){
		GetCanvas()->SetImage(NULL);
		return;
	}
	QSize size = Image.size();
	QSize tag_size = GetCanvas()->size();

	if(zoomStage<0){
		for(int i=0; i<-zoomStage; i++){
			tag_size /= 2;
		}
	}else if(zoomStage>0){
		for(int i=0; i<zoomStage; i++){
			tag_size *= 2;
		}
	}
	size.scale(tag_size, Qt::KeepAspectRatio);

	QImage *image = new QImage(Image.scaled(size));

	GetCanvas()->SetImage(image);
}

void NGNailDisplay::updateImage(int RotateAngle)
{
	if(Image.isNull()){
		GetCanvas()->SetImage(NULL);
		return;
	}
	QSize size = Image.size();
	QSize tag_size = GetCanvas()->size();

	if(zoomStage<0){
		for(int i=0; i<-zoomStage; i++){
			tag_size /= 2;
		}
	}else if(zoomStage>0){
		for(int i=0; i<zoomStage; i++){
			tag_size *= 2;
		}
	}
	size.scale(tag_size, Qt::KeepAspectRatio);

	double zoomRate = size.width() / (double)Image.size().width();

	QImage *image = new QImage(Image.scaled(size));

	QPen pen;
	pen.setWidth(1);
	if(NGVisible==true){

		QPainter painter(image);
		for(int i=0; i<NGPoints.count(); i++){
			if(NGPSelect[i]==false){
				//pen.setColor(NGSingColor);
				pen.setColor(NGPoints[i].Tag.NGColor);
			}else{
				pen.setColor(NGSelectColor);
			}
			painter.setPen(pen);
			
			QPoint center =(QPoint(NGPoints[i].x - TopLeftPos.x(), NGPoints[i].y - TopLeftPos.y())) * zoomRate * pow(2.0, zoomStage);
			switch(RotateAngle){
				case 0:
					center = (QPoint(NGPoints[i].x - TopLeftPos.x(), NGPoints[i].y - TopLeftPos.y())) * zoomRate * pow(2.0, zoomStage);
					break;
				case 90:
					center = (QPoint(NGPoints[i].y - TopLeftPos.y(),NGPoints[i].x - TopLeftPos.x())) * zoomRate * pow(2.0, zoomStage);
					center.setX(image->width()-center.x());
					break;
			}

			if(NGSingColorForce==true){
				Review::DrawNGShapeToPainter(&painter, NGSingColor, NGPoints[i].Tag.NGShape, center, NGSingSize/2);
			}else{
				Review::DrawNGShapeToPainter(&painter, NGPoints[i].Tag.NGColor, NGPoints[i].Tag.NGShape, center, NGSingSize/2);
			}

			//switch(NGPoints[i].Tag.NGShape){
			//case LibNGTypeItem::NGShapeType::NG_Circle:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2); 
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_Cross:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawLine(center - QPoint(0, NGSingSize/2), center + QPoint(0, NGSingSize/2));
			//	painter.drawLine(center - QPoint(NGSingSize/2, 0), center + QPoint(NGSingSize/2, 0));
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_FilledCircle:
			//	painter.setBrush(Qt::BrushStyle::SolidPattern);
			//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2);
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_FilledRect:
			//	painter.setBrush(Qt::BrushStyle::SolidPattern);
			//	painter.drawRect(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize);
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_FilledStar:
			//	painter.setBrush(Qt::BrushStyle::SolidPattern);
			//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"š");
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_Rectangle:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawRect(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize);
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_Sharp:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"#");
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_Star:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"™");
			//	break;
			//case LibNGTypeItem::NGShapeType::NG_X:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawLine(center - QPoint(NGSingSize/2, NGSingSize/2), center + QPoint(-NGSingSize/2, -NGSingSize/2));
			//	painter.drawLine(center - QPoint(-NGSingSize/2, NGSingSize/2), center + QPoint(NGSingSize/2, -NGSingSize/2));
			//	break;
			//default:
			//	painter.setBrush(Qt::BrushStyle::NoBrush);
			//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2); 
			//	break;
			//}
		}

	}

	GetCanvas()->SetImage(image);
}

void NGNailDisplay::setNGPoints(QList<ReviewNGPoint> list)
{
	//NGPSelect.clear();
	NGPoints = list;
	NGPSelect = QVector<bool>(list.count(), false).toList();
	updateImage();
}


void NGNailDisplay::SlotMouseMove(int x, int y)
{
	//QSize size = Image.size();
	//QSize tag_size = GetCanvas()->size();

	//if(zoomStage<0){
	//	for(int i=0; i<-zoomStage; i++){
	//		tag_size /= 2;
	//	}
	//}else if(zoomStage>0){
	//	for(int i=0; i<zoomStage; i++){
	//		tag_size *= 2;
	//	}
	//}
	//size.scale(tag_size, Qt::KeepAspectRatio);

	//double zoomRate = size.width() / (double)Image.size().width();

	//bool reflesh = false;

	//for(int i=0; i<NGPoints.count(); i++){
	//	QPoint p = (NGPoints[i]-TopLeftPos) * zoomRate;
	//	if(qAbs(p.x()-x)<NGSingSize/2*pow(2.0, -zoomStage) && qAbs(p.y()-y)<NGSingSize/2*pow(2.0, -zoomStage)){
	//		if(NGPSelect[i]==false){
	//			reflesh = true;
	//		}
	//		NGPSelect[i] = true;
	//	}else{
	//		if(NGPSelect[i]==true){
	//			reflesh = true;
	//		}
	//		NGPSelect[i] = false;
	//	}
	//}
	//if(reflesh==true){
	//	updateImage();
	//}
}