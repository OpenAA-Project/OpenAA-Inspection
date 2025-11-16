#include "XReviewCommon.h"

#include <QPen>
#include <QPainter>
#include <QStaticText>
#include <QDir>
#include <QDebug>
#include "XGeneralFuncCore.h"

namespace Review{

const QString StaticString::InspectionResult::OK = "OK";
const QString StaticString::InspectionResult::NG = "NG";
const QString StaticString::InspectionResult::MaxError = "MaxError";
const QString StaticString::InspectionResult::TimeOut = "TimeOut";
	
QString makeMasterImageName(int MasterCode, int MachineID, int phase, int page, const QString &path)
{
	QString Sep=/**/"";
	QString s = path.right(1);
	if(s!=::GetSeparator() && s!=QString(/**/"\\")){
		Sep= QDir::separator();
	}
	QString	Ret;
	if(phase==0){
		Ret =path+Sep
			+QString(/**/"Image")+QString::number(MasterCode)+QString(/**/"-")
			+QString(/**/"Page")+QString::number(page)+QString(/**/"-")
			+QString(/**/"Mac")+QString::number(MachineID)
			+QString(/**/".img");
	}
	else{
		Ret =path+Sep
			+QString(/**/"Image")+QString::number(MasterCode)+QString(/**/"-")
			+QString(/**/"Phase")+QString::number(phase)+QString(/**/"-")
			+QString(/**/"Page")+QString::number(page)+QString(/**/"-")
			+QString(/**/"Mac")+QString::number(MachineID)
			+QString(/**/".img");
	}
	return Ret;
}

bool isFront(Review::SideType side){ return (side==Review::Front); }
bool isBack(Review::SideType side){ return !isFront(side); };

QString toString(Review::SideType side){
	if(isFront(side)){
		return "Front";
	}else{
		return "Back";
	}
}

bool isArrowKey(int key){
	switch(key){
	case Qt::Key_Up:
	case Qt::Key_Down:
	case Qt::Key_Right:
	case Qt::Key_Left:
		return true;
		break;
	default:
		return false;
		break;
	}
}

int toIntFromRotate(Rotate rotate){
	switch(rotate){
	case Rotate_0:
		return 0;
		break;
	case Rotate_90:
		return 90;
		break;
	case Rotate_180:
		return 180;
		break;
	case Rotate_270:
		return 270;
		break;
	default:
		return 0;
		break;
	}
	return 0;
};

Review::Rotate toRotateFromInt(int rotate)
{
	switch(rotate){
	case 0:
		return Rotate::Rotate_0;
		break;
	case 90:
		return Rotate::Rotate_90;
		break;
	case 180:
		return Rotate::Rotate_180;
		break;
	case 270:
		return Rotate::Rotate_270;
		break;
	default:
		break;
	}

	int angle_fix = rotate % 360;
	angle_fix = (angle_fix + 360) % 360;

	if(isBetween(0+45, angle_fix, 90+45-1)==true){
		return Rotate::Rotate_90;
	}else if(isBetween(180-45, angle_fix, 180-45-1)==true){
		return Rotate::Rotate_180;
	}else if(isBetween(270-45, angle_fix, 270-45-1)==true){
		return Rotate::Rotate_270;
	}else{
		return Rotate::Rotate_0;
	}
}

Qt::Corner rotatedRectCorner(Qt::Corner originalCorner, Rotate rotation, bool counterclockwise)
{
	switch(originalCorner){
	case Qt::Corner::TopLeftCorner:
		switch(rotation){
		case Rotate::Rotate_0:
			return Qt::Corner::TopLeftCorner;
			break;
		case Rotate::Rotate_90:
			return (counterclockwise==true ? Qt::Corner::TopRightCorner : Qt::Corner::BottomLeftCorner);
			break;
		case Rotate::Rotate_180:
			return Qt::Corner::BottomRightCorner;
			break;
		case Rotate::Rotate_270:
			return (counterclockwise==true ? Qt::Corner::BottomLeftCorner : Qt::Corner::TopRightCorner);
			break;
		default:
			break;
		}
		break;
	case Qt::Corner::TopRightCorner:
		switch(rotation){
		case Rotate::Rotate_0:
			return Qt::Corner::TopRightCorner;
			break;
		case Rotate::Rotate_90:
			return (counterclockwise==true ? Qt::Corner::BottomRightCorner : Qt::Corner::TopLeftCorner);
			break;
		case Rotate::Rotate_180:
			return Qt::Corner::BottomLeftCorner;
			break;
		case Rotate::Rotate_270:
			return (counterclockwise==true ? Qt::Corner::TopLeftCorner : Qt::Corner::BottomRightCorner);
			break;
		default:
			break;
		}
		break;
	case Qt::Corner::BottomLeftCorner:
		switch(rotation){
		case Rotate::Rotate_0:
			return Qt::Corner::BottomLeftCorner;
			break;
		case Rotate::Rotate_90:
			return (counterclockwise==true ? Qt::Corner::TopLeftCorner : Qt::Corner::BottomRightCorner);
			break;
		case Rotate::Rotate_180:
			return Qt::Corner::TopRightCorner;
			break;
		case Rotate::Rotate_270:
			return (counterclockwise==true ? Qt::Corner::BottomRightCorner : Qt::Corner::TopLeftCorner);
			break;
		default:
			break;
		}
		break;
	case Qt::Corner::BottomRightCorner:
		switch(rotation){
		case Rotate::Rotate_0:
			return Qt::Corner::BottomRightCorner;
			break;
		case Rotate::Rotate_90:
			return (counterclockwise==true ? Qt::Corner::BottomLeftCorner : Qt::Corner::TopRightCorner);
			break;
		case Rotate::Rotate_180:
			return Qt::Corner::TopLeftCorner;
			break;
		case Rotate::Rotate_270:
			return (counterclockwise==true ? Qt::Corner::TopRightCorner : Qt::Corner::BottomLeftCorner);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return Qt::Corner::TopLeftCorner;
}

QPoint corner(const QRect &rect, Qt::Corner c)
{
	return corner(QRectF(rect), c).toPoint();
}

QPointF corner(const QRectF &rect, Qt::Corner c)
{
	switch(c){
	case Qt::Corner::TopLeftCorner:
		return rect.topLeft();
		break;
	case Qt::Corner::TopRightCorner:
		return rect.topRight();
		break;
	case Qt::Corner::BottomLeftCorner:
		return rect.bottomLeft();
		break;
	case Qt::Corner::BottomRightCorner:
		return rect.bottomRight();
		break;
	default:
		return rect.topLeft();
		break;
	}
	return rect.topLeft();
}

QRect setCorner(const QRect &rect, const QPoint &pos, Qt::Corner c)
{
	return setCorner(QRectF(rect), QPointF(pos), c).toRect();
}

QRectF setCorner(const QRectF &rect, const QPointF &pos, Qt::Corner c)
{
	QRectF ret = rect;
	switch(c){
	case Qt::Corner::TopLeftCorner:
		ret.setTopLeft(pos);
		break;
	case Qt::Corner::TopRightCorner:
		ret.setTopRight(pos);
		break;
	case Qt::Corner::BottomLeftCorner:
		ret.setBottomLeft(pos);
		break;
	case Qt::Corner::BottomRightCorner:
		ret.setBottomRight(pos);
		break;
	default:
		ret.setTopLeft(pos);
		break;
	}
	return ret;
}

QRect moveCorner(const QRect &rect, const QPoint &pos, Qt::Corner c)
{
	return moveCorner(QRectF(rect), QPointF(pos), c).toRect();
}

QRectF moveCorner(const QRectF &rect, const QPointF &pos, Qt::Corner c)
{
	QRectF ret = rect;
	switch(c){
	case Qt::Corner::TopLeftCorner:
		ret.moveTopLeft(pos);
		break;
	case Qt::Corner::TopRightCorner:
		ret.moveTopRight(pos);
		break;
	case Qt::Corner::BottomLeftCorner:
		ret.moveBottomLeft(pos);
		break;
	case Qt::Corner::BottomRightCorner:
		ret.moveBottomRight(pos);
		break;
	default:
		ret.moveTopLeft(pos);
		break;
	}
	return ret;
}

QRect rotateRect(const QRect &r, qreal angle, Qt::Corner keepCorner)
{
	return rotateRect(QRectF(r), angle, keepCorner).toRect();
}

QRectF rotateRect(const QRectF &r, qreal angle, Qt::Corner keepCorner)
{
	return moveCorner(rotateRectRaw(r, angle), corner(r, keepCorner), keepCorner);
}

QRect rotateRectRaw(const QRect &r, qreal angle)
{
	return rotateRectRaw(QRectF(r), angle).toRect();
}

QRectF rotateRectRaw(const QRectF &r, qreal angle)
{
	QTransform transform;
	return transform.rotate(angle).mapRect(r);
}

QPoint rotatePoint(const QPoint &p, qreal angle, const QPoint &center)
{
	return rotatePoint(QPointF(p), angle, center).toPoint();
}

QPointF rotatePoint(const QPointF &p, qreal angle, const QPoint &center)
{
	QTransform transform;
	QPointF moveCenterPoint = p - center;
	return transform.rotate(angle).map(moveCenterPoint) + center;
}

QSize rotateSize(const QSize &size, qreal angle)
{
	QRect rect(QPoint(0,0), size);
	return rotateRect(rect, angle).size();
}

QSizeF rotateSize(const QSizeF &size, qreal angle)
{
	QRectF rect(QPointF(0,0), size);
	return rotateRect(rect, angle).size();
}

QImage rotateImage(const QImage &image, qreal angle, const QColor &backFillColor)
{
	QImage ret;
	if(image.isNull()==false){
		
		QTransform trans;
		trans.rotate(angle);

		ret = image.transformed(trans);
	}
	return ret;
}

QRect rotateRectOnRect(const QRect &pieceRect, const QPoint &originPoint, qreal angle, Qt::Corner shareCorner)
{
	QTransform transform;
	transform.translate(-originPoint.x(), -originPoint.y());
	transform.rotate(angle);
	QRect ret = transform.mapRect(pieceRect);
	ret.moveTopLeft( QPoint(transform.dx(), transform.dy()) );
	return ret;
}

QRect rotateRectRoundCneter(const QRect &r, qreal angle)
{
	return rotateRectRoundCneter(QRectF(r), angle).toRect();
}

QRectF rotateRectRoundCneter(const QRectF &r, qreal angle)
{
	QRectF crect = r;
	crect.moveCenter(QPointF(0,0));
	QRectF res = QTransform().rotate(angle).mapRect(r);
	res.moveTopLeft(r.topLeft());
	return res;
}

QRect boundRect(const QPoint &p1, const QPoint &p2)
{
	return QRect(p1, p1).united(QRect(p2, p2));
}

QRectF boundRect(const QPointF &p1, const QPointF &p2)
{
	return QRectF(p1, p1).united(QRectF(p2, p2));
}

QRect boundRect(const QList<QPoint> &pList)
{
	QRect rect;
	for(QList<QPoint>::ConstIterator it=pList.constBegin(); it!=pList.constEnd(); it++){
		rect = rect.united(QRect(*it, *it));
	}
	return rect;
}

QRectF boundRect(const QList<QPointF> &pList)
{
	QRectF rect;
	for(QList<QPointF>::ConstIterator it=pList.constBegin(); it!=pList.constEnd(); it++){
		rect = rect.united(QRectF(*it, *it));
	}
	return rect;
}

// デフォルトのFキーカラー
QColor getDefaultFKeyColor(Review::FKey key){
	switch(key){
	case F1:
		return QColor(Qt::green);
	case F2:
		return QColor(Qt::blue);
	case F3:
		return QColor(Qt::yellow);
	case F4:
		return QColor(Qt::lightGray);
	case F5:
		return QColor(Qt::cyan);
	case F6:
		return QColor(Qt::magenta);
	case F7:
		return QColor(Qt::darkRed);
	case F8:
		return QColor(Qt::darkGreen);
	case F9:
		return QColor(Qt::darkBlue);
	case F10:
		return QColor(Qt::darkCyan);
	case F11:
		return QColor(Qt::darkMagenta);
	case F12:
		return QColor(Qt::darkYellow);
	case NoFKey:
		return QColor(Qt::red);
	default:
		return QColor(Qt::white);
	}
}

// デフォルトFカラーリスト
QList<QColor> getDefaultFKeyColorList()
{
	QList<QColor> ret;
	ret.append( getDefaultFKeyColor(Review::F1) );
	ret.append( getDefaultFKeyColor(Review::F2) );
	ret.append( getDefaultFKeyColor(Review::F3) );
	ret.append( getDefaultFKeyColor(Review::F4) );
	ret.append( getDefaultFKeyColor(Review::F5) );
	ret.append( getDefaultFKeyColor(Review::F6) );
	ret.append( getDefaultFKeyColor(Review::F7) );
	ret.append( getDefaultFKeyColor(Review::F8) );
	ret.append( getDefaultFKeyColor(Review::F9) );
	ret.append( getDefaultFKeyColor(Review::F10) );
	ret.append( getDefaultFKeyColor(Review::F11) );
	ret.append( getDefaultFKeyColor(Review::F12) );
	ret.append( getDefaultFKeyColor(Review::NoFKey) );

	return ret;
}

bool isFKey(Qt::Key key){
	if(Qt::Key_F1 <= key && key <= Qt::Key_F12){
		return true;
	}else{
		return false;
	}
}

Review::FKey convertFKeyQtToReview(Qt::Key key){
	int iFKey = key - Qt::Key_F1;
	if(iFKey<0 || Review::F12<iFKey){
		return Review::NoFKey;
	}else{
		return (Review::FKey)iFKey;
	}
}

// Review::FKeyをint型に変換する。F1==0, F2==1, ... , F12==11, Fキーなし==12, その他==-1が返る
int FKeyToInt(Review::FKey key){
	switch(key){
	case F1:
		return 0;
		break;
	case F2:
		return 1;
		break;
	case F3:
		return 2;
		break;
	case F4:
		return 3;
		break;
	case F5:
		return 4;
		break;
	case F6:
		return 5;
		break;
	case F7:
		return 6;
		break;
	case F8:
		return 7;
		break;
	case F9:
		return 8;
		break;
	case F10:
		return 9;
		break;
	case F11:
		return 10;
		break;
	case F12:
		return 11;
		break;
	case NoFKey:
		return 12;
		break;
	default:
		return -1;
		break;
	}
}

// int型をReview::FKeyへ変換する。数値0～12がF1～F12,NoFKeyの同順となる。範囲から外れた場合はNoFKeyが返る
Review::FKey IntToFKey(int ref){
	if(ref < 0 || 12 < ref){
		return NoFKey;
	}else{
		return (Review::FKey)ref;
	}
}

// マスターコード、マシンID、XMLのファイル名からXMLサーバーの検索ディレクトリからのファイルパスを作成する
QString makeLotFileName(int MasterCode, int MachineID, QString FileName){
	return QString(/**/"%1-%2/%3").arg(MachineID).arg(MasterCode).arg(FileName);
}

// XMLファイルに記述されている日時フォーマットのQStringからXDateTimeオブジェクトを再構成する
XDateTime makeLotISTDateTime(QString format){
	return XDateTime::fromString(format, /**/"yyMMddhhmmss");
}

Review::SideType ShowMessageFrontOrBack(QWidget *parent){
	QMessageBox msg(parent);
	msg.setText("Which side is this ?");

	QAbstractButton *btnFront	= msg.addButton("Front", QMessageBox::NoRole);
	QAbstractButton *btnBack	= msg.addButton("Back", QMessageBox::NoRole);

	msg.exec();

	if(btnFront == msg.clickedButton()){
		return Review::Front;
	}else if(btnBack == msg.clickedButton()){
		return Review::Back;
	}else{
		return Review::SideType::Front;
	}
}

// NG画像保存のマクロリスト
QList<QPair<QString, QString> > Review::getSaveNGImageFormatMacroList()
{
	QList<QPair<QString, QString> > macroSimbolInfoPairList;
	
	macroSimbolInfoPairList
		<< QPair<QString, QString>("%m", "MasterID")
		<< QPair<QString, QString>("%M", "MasterName")
		<< QPair<QString, QString>("%l", "LotName")
		<< QPair<QString, QString>("%i", "InspectionID")
		<< QPair<QString, QString>("%S", "NGSide; \"Front\" or \"Back\"")
		<< QPair<QString, QString>("%n", "NG Number(same as row)")
		<< QPair<QString, QString>("%N", "NG Number(index on side)")
		<< QPair<QString, QString>("/", "Directory Separator");

	return macroSimbolInfoPairList;
}

QString AlgorithmRoot = /**/"Review";
QString AlgorithmName = /**/"ReviewStructure";

void DrawNGShapeToPainter(QPainter *painter, QColor color, LibNGTypeItem::NGShapeType shape, QPoint center, int round)
{
	QPen pen(color);
	QBrush brush(color);
	int tmp;
	qreal tmp_reql;
	QRect rect;
	QFont old_font = painter->font();
	QFont font = old_font;
	QStaticText stext;

	painter->setPen(pen);

	switch(shape){
	case LibNGTypeItem::NGShapeType::NG_Circle:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		painter->drawEllipse(center, round, round);
		break;
	case LibNGTypeItem::NGShapeType::NG_Cross:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		painter->drawLine(center - QPoint(0, round), center + QPoint(0, round));
		painter->drawLine(center - QPoint(round, 0), center + QPoint(round, 0));
		break;
	case LibNGTypeItem::NGShapeType::NG_FilledCircle:
		//painter->setBrush(Qt::BrushStyle::SolidPattern);
		brush.setStyle(Qt::BrushStyle::SolidPattern);
		painter->setBrush(brush);
		painter->drawEllipse(center, round, round);
		break;
	case LibNGTypeItem::NGShapeType::NG_FilledRect:
		brush.setStyle(Qt::BrushStyle::SolidPattern);
		painter->setBrush(brush);
		painter->drawRect(center.x()-round, center.y()-round, round*2, round*2);
		break;
	case LibNGTypeItem::NGShapeType::NG_FilledStar:
		brush.setStyle(Qt::BrushStyle::SolidPattern);
		painter->setBrush(brush);
		round = 15;
		painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::TextJustificationForced, /**/"★");
		break;
	case LibNGTypeItem::NGShapeType::NG_Rectangle:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		painter->drawRect(center.x()-round, center.y()-round, round*2, round*2);
		break;
	case LibNGTypeItem::NGShapeType::NG_Sharp:
		painter->setBrush(Qt::BrushStyle::NoBrush);

		tmp = (int)((round * 2.0) / 3.0 + 0.5);
		painter->drawLine(center.x() - round + tmp + 1, center.y() - round, center.x() - round + tmp - 1, center.y() + round);// |
		painter->drawLine(center.x() - round + 2*tmp + 1, center.y() - round, center.x() - round + 2*tmp - 1, center.y() + round);// ||
		painter->drawLine(center.x() - round, center.y() - round + tmp + 1, center.x() + round, center.y() - round + tmp - 1);// -
		painter->drawLine(center.x() - round, center.y() - round + 2*tmp + 1, center.x() + round, center.y() - round + 2*tmp - 1);// =
		
		//painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::AlignJustify, /**/"#");
		break;
	case LibNGTypeItem::NGShapeType::NG_Star:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		round = 15;
		painter->drawText(center.x()-round, center.y()-round, round*2, round*2, Qt::AlignCenter | Qt::AlignJustify, /**/"☆");
		break;
	case LibNGTypeItem::NGShapeType::NG_X:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		painter->drawLine(center.x() - round, center.y() - round, center.x() + round, center.y() + round);
		painter->drawLine(center.x() + round, center.y() - round, center.x() - round, center.y() + round);
		break;
	default:
		painter->setBrush(Qt::BrushStyle::NoBrush);
		painter->drawEllipse(center, round, round); 
		break;
	}
}

QImage toRGBImage(const QImage &rImage, const QImage &gImage, const QImage &bImage, bool monoFlag)
{
	QImage ret;
	if((rImage.isNull()==false && rImage.format()!=QImage::Format_Indexed8) || (gImage.isNull()==false && gImage.format()!=QImage::Format_Indexed8) || (bImage.isNull()==false && bImage.format()!=QImage::Format_Indexed8)){
		return ret;
	}

	QSize size;
	size = size.expandedTo(rImage.size());
	size = size.expandedTo(gImage.size());
	size = size.expandedTo(bImage.size());

	if(rImage.isNull()==false){
		size = size.boundedTo(rImage.size());
	}
	if(gImage.isNull()==false){
		size = size.boundedTo(gImage.size());
	}
	if(bImage.isNull()==false){
		size = size.boundedTo(bImage.size());
	}
	
	ret = QImage(size, QImage::Format_RGB32);

	qDebug() << "R is " << rImage.isNull();
	qDebug() << "G is " << gImage.isNull();
	qDebug() << "B is " << bImage.isNull();

	int	YLen=ret.height();
	int	XLen=ret.width();
	if(rImage.isNull()==true){
		if(gImage.isNull()==true){
			if(bImage.isNull()==true){
				// null
			}else{
				if(monoFlag==false){
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcBData = (qint8 *)bImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(0, 0, srcBData[x]);
						}
					}
				}else{
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcBData = (qint8 *)bImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(srcBData[x], srcBData[x], srcBData[x]);
						}
					}
				}
			}
		}else{
			if(bImage.isNull()==true){
				if(monoFlag==false){
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcGData = (qint8 *)gImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(0, srcGData[x], 0);
						}
					}
				}else{
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcGData = (qint8 *)gImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(srcGData[x], srcGData[x], srcGData[x]);
						}
					}
				}
			}else{
				#pragma omp for
				for(int y=0; y<YLen; y++){
					QRgb *destRgb = (QRgb*)ret.scanLine(y);
					qint8 *srcGData = (qint8 *)gImage.scanLine(y);
					qint8 *srcBData = (qint8 *)bImage.scanLine(y);
					for(int x=0; x<XLen; x++){
						destRgb[x] = qRgb(0, srcGData[x], srcBData[x]);
					}
				}
			}
		}
	}else{
		if(gImage.isNull()==true){
			if(bImage.isNull()==true){
				if(monoFlag==false){
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcData = (qint8 *)rImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(srcData[x], 0, 0);
						}
					}
				}else{
					#pragma omp for
					for(int y=0; y<YLen; y++){
						QRgb *destRgb = (QRgb*)ret.scanLine(y);
						qint8 *srcData = (qint8 *)rImage.scanLine(y);
						for(int x=0; x<XLen; x++){
							destRgb[x] = qRgb(srcData[x], srcData[x], srcData[x]);
						}
					}
				}
			}else{
				#pragma omp for
				for(int y=0; y<YLen; y++){
					QRgb *destRgb = (QRgb*)ret.scanLine(y);
					qint8 *srcRData = (qint8 *)rImage.scanLine(y);
					qint8 *srcBData = (qint8 *)bImage.scanLine(y);
					for(int x=0; x<XLen; x++){
						destRgb[x] = qRgb(srcRData[x], 0, srcBData[x]);
					}
				}
			}
		}else{
			if(bImage.isNull()==true){
				#pragma omp for
				for(int y=0; y<YLen; y++){
					QRgb *destRgb = (QRgb*)ret.scanLine(y);
					qint8 *srcRData = (qint8 *)rImage.scanLine(y);
					qint8 *srcGData = (qint8 *)gImage.scanLine(y);
					for(int x=0; x<XLen; x++){
						destRgb[x] = qRgb(srcRData[x], srcGData[x], 0);
					}
				}
			}else{
				#pragma omp for
				for(int y=0; y<YLen; y++){
					QRgb *destRgb = (QRgb*)ret.scanLine(y);
					qint8 *srcRData = (qint8 *)rImage.scanLine(y);
					qint8 *srcGData = (qint8 *)gImage.scanLine(y);
					qint8 *srcBData = (qint8 *)bImage.scanLine(y);
					for(int x=0; x<XLen; x++){
						destRgb[x] = qRgb(srcRData[x], srcGData[x], srcBData[x]);
					}
				}
			}
		}
	}
	return ret;
}

}
