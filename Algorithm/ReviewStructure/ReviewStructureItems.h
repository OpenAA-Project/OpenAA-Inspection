/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <QString>
#include "XDateTime.h"
#include <QImage>
#include <QMultiHash>
#include <QPainter>
#include <QPainterPath>
#include <QTransform>

#include "XTypeDef.h"
#include "XReviewCommon.h"
#include "XAlgorithmLibNGType.h"
#include "JDTAnalyzer.h"

class	ReviewPIBase;

// XML�ɋL�q�����Ă���<INSLIB �����n�܂郉�C�u�������������č\������
class InsLibraryItem
{
public:
	InsLibraryItem():Ral(/**/""),LibCode(-1),LibName(/**/""),TypeNameList(){};

public:
	class TypeNameTag{
	public:
		TypeNameTag(){ clear(); };

		void clear(void){
			TypeName = /**/"";
			TCode = -1;
			TName = /**/"";
			NGColor = QColor(Qt::GlobalColor::red);
			NGShape = LibNGTypeItem::NGShapeType::NG_Circle;
			NGBlink = 0;
			NGPriority = 0;
			Wait = 0;
		};

		bool operator==(const TypeNameTag &other) const {
			return (TypeName==other.TypeName && TCode==other.TCode && TName==other.TName && NGColor==other.NGColor &&
				NGShape==other.NGShape && NGBlink==other.NGBlink && NGPriority==other.NGPriority);
		};
	public:
		QString operator()(void) const {
			return value();
		};
		QString operator()(const QString &) const {
			return value();
		};
		QString value() const {
			return QString("TYPENAME=%1,TCODE=%2,TNAME=%3,NGCOLOR=%4,NGSHAPE=%5,NGBLINK=%6,NGPRIORITY=%7,WAIT=%8")
				.arg(TypeName).arg(TCode).arg(TName).arg(NGColor.name()).arg(static_cast<int>(NGShape)).arg(NGBlink).arg(NGPriority).arg(Wait);
		};
	public:
		QString TypeName;//	TYPENAME=
		int TCode;//		TCODE=
		QString TName;//	TNAME=
		QColor NGColor;//	NGCOLOR=
		LibNGTypeItem::NGShapeType NGShape;
		int NGBlink;//		NGBLINK= [0�Ŗ���]
		int NGPriority;//	NGPRIORITY= [���l���Ⴂ�قǗD���x������]
		int Wait;//			WAIT= [����NG�ֈړ������܂ł̑ҋ@����]
	};

public:
	QString Ral;//		RAL=
	int32 LibCode;//	LIBCODE=
	QString LibName;//	LIBNAME=

	QList<TypeNameTag> TypeNameList;

public:
	bool operator==(const InsLibraryItem &other) const {
		if(Ral == other.Ral &&
			LibCode == other.LibCode &&
			LibName == other.LibName &&
			TypeNameList.count() == other.TypeNameList.count()){

				for(int i=0; i<TypeNameList.count(); i++){
					if(other.TypeNameList.contains(TypeNameList[i])==false){
						return false;
					}
				}

				return true;
		}

		return false;
	};
};

typedef QList<InsLibraryItem>	InsLibraryList;
typedef InsLibraryList			*InsLibraryListPtr;
typedef InsLibraryItem			*InsLibraryIndex;
typedef QList<InsLibraryIndex>	InsLibraryIndexList;

// Ral���L�[�Ƃ������C�u�����f�[�^�ւ̃n�b�V��
// NG���񂩂烉�C�u�����f�[�^�̎Q�Ƃ��s�����Ɏg�p����
//
// ReviewPIBase�ɕۑ�������
//
typedef QMultiHash<QString,InsLibraryItem> InsLibraryHash;
typedef InsLibraryHash	*InsLibraryHashPtr;

class InsLibSearchRef{
public:
	InsLibSearchRef(QString Ral=/**/"", int LC=-1, int TC=-1):ral(Ral),lc(LC),tc(TC){};

public:
	bool operator==(const InsLibSearchRef &other) const {
		if(tc==other.tc && lc==other.lc && ral==other.ral){
			return true;
		}else{
			return false;
		}
	};

public:
	QString ral;
	int lc;
	int tc;
};

typedef QMultiHash<int, InsLibSearchRef> InsLibWaitHash;
typedef QHash<QString, QHash<int, QHash<int, InsLibraryItem::TypeNameTag> > > InsLibSearchHash;

class LibNGTypeItemForReview : public LibNGTypeItem
{
public:
	LibNGTypeItemForReview(LayersBase *base):LibNGTypeItem(base){};

public:
	int LibType;
	int LibID;
	XDateTime LastUpdated;
	int DataVersion;

	bool Save(QIODevice *f){ return SaveCommon(f); };
	bool Load(QIODevice *f){ return LoadCommon(f); };

public:
	LibNGTypeItemForReview &operator=(const LibNGTypeItemForReview &other){
		LibType = other.LibType;
		TypeUniqueCode = other.TypeUniqueCode;	//�f�[�^�x�[�X���ŗB���̒l
		TypeCode = other.TypeCode;
		NGColor = other.NGColor;
		Blink = other.Blink;
		NGShape = other.NGShape;
		Priority = other.Priority;
		NextJumpMilisec = other.NextJumpMilisec;
		NGName = other.NGName;
		return *this;
	};
};

class PCEItem
{
public:
	PCEItem(){clear();};

public:
	enum AreaType
	{
		None,//Initial value
		Rect,//R
		Ellipse,//E
		Polygon,//P
		RotateEllipse,//T
		Ring//G
	};

public:
	int pointCount() const { return areaPointList().count(); };

	bool isValid() const {
		bool ret = false;
		switch(areaType()){
		case Rect:
			if(pointCount()==2){
				ret = true;
			}
			break;
		case Ellipse:
			if(pointCount()==2){
				ret = true;
			}
			break;
		case Polygon:
			if(pointCount()>=2){
				ret = true;
			}
			break;
		case RotateEllipse:
			if(pointCount()>=2 && rotate()!=INT_MIN){
				ret = true;
			}
		case Ring:
			if(pointCount()==4){
				ret = true;
			}
		default:
			break;
		}
		return ret;
	};
	void clear(){
		setMasterID(-1);
		setPage(-1);
		setPieceID(-1);
		setPieceName(QString());
		setAreaType(AreaType::None);
		setAreaPointList(QList<QPoint>());
		setReserveData(QString());
		setRotate(INT_MIN);
	};

public:
	void setMasterID(int id){ m_MasterID = id; };
	int MasterID() const { return m_MasterID; };
	void setPage(int page){ m_page = page; };
	int page() const { return m_page; };
	void setPieceID(int id){ m_pieceID = id; };
	int pieceID() const { return m_pieceID; };
	void setPieceName(const QString &name){ m_pieceName = name; };
	QString pieceName() const { return m_pieceName; };
	void setAreaType(AreaType type){ m_type = type; };
	AreaType areaType() const { return m_type; };
	void setAreaPointList(const QList<QPoint> &list){ m_AreaPointList = list; };
	QList<QPoint> areaPointList() const { return m_AreaPointList; };
	void setReserveData(const QString &resv){ m_ReserveData = resv; };
	QString reserveData() const { return m_ReserveData; };
	void setRotate(int rotation){ m_rotate = rotation; };
	int rotate() const { return m_rotate; };

public:
	/*
	��������	AREA
	�f�[�^�̋L�q
		�`���L��	R:���`	E:�ȉ~	P:���p�`  T:���]�ȉ~  G:�����O
		���W��		X,Y
		���L����	���p�`�̏ꍇ�͍��W���͍ő��P�O�O�܂łƂ����B
					�P�O�O�𒴂����ꍇ�́A�Ԉ�������
		��
			AREA="R10,20,50,60"				(10,20)-(50,60)�̋��`
			AREA="E60,-100,120,150"			(60,-100)-(120,150)�̋��`�ɓ��ڂ����ȉ~
			AREA="P0,0,10,10,30,10,30,0"	(0,0)-(10,10)-(30,10)-(30,0)�����ԑ��p�`
											�n�_�ƏI�_�����v���Ȃ��Ă��\���Ȃ�
			AREA="T40,500,20,25,60"			���S���W�w�A���S���W�x�A�w�����̔��a�A�x�����̔��a�A���]�p�x�i�x�j
			AREA="G10,100,120,250,30,160,70,200"	(10,100)-(120,250)�̊O���ȉ~��(30,160)-(70,200)�̓����ȉ~�̊Ԃ̗̈�
	*/
	QRect rect() const {
		QRect ret;
		QList<QPoint> pList = areaPointList();

		if(isValid()==false){
			return ret;
		}

		switch(areaType()){
		case Rect:
		case Ellipse:
			ret = QRect(pList[0], pList[0]).united(QRect(pList[1], pList[1]));
			break;
		case Polygon:
			{
				int maxX, minX, maxY, minY;
				maxX = minX = pList.first().x();
				maxY = minY = pList.first().y();
				for(QList<QPoint>::Iterator it=pList.begin()+1; it!=pList.end(); it++){
					if(maxX<it->x()){
						maxX = it->x();
					}else if(minX>it->x()){
						minX = it->x();
					}

					if(maxY<it->y()){
						maxY = it->y();
					}else if(minY>it->y()){
						minY = it->y();
					}
				}

				ret = QRect(minX, minY, qAbs(maxX - minX), qAbs(maxY - minY));
			}
			break;
		case RotateEllipse:// ���]0�x�̑ȉ~�ɂ��ďc���̏��������̃T�C�Y��1�ӂƂ��������`
			{
				int rwidth = pList[1].x();
				int rheight = pList[1].y();

				int rmax = qMin(rwidth, rheight);

				ret = QRect(pList[0] - QPoint(rmax,rmax), pList[0] + QPoint(rmax,rmax));
			}
			break;
		case Ring:// �����O�̏㑤�ƍ����̖ʐς��ȈՓI�ɋ��`�Œ��ׁA�L�����̋��`���I������
			{
				QPoint topLeft = pList[0];
				int twidth = qAbs(pList[0].x() - pList[1].x());
				int theight = qAbs(pList[0].y() - pList[2].y());

				int lwidth = qAbs(pList[0].x() - pList[2].x());
				int lheight = qAbs(pList[0].y() - pList[1].y());

				int width, height;
				if(twidth * theight > lwidth * lheight){
					width = twidth;
					height = theight;
				}else{
					width = lwidth;
					height = lheight;
				}

				ret = QRect(topLeft.x(), topLeft.y(), width, height);
			}
			break;
		}
		
		return ret;
	};

	QPolygon polygon() const {
		QPolygon ret;

		if(areaType()==AreaType::Polygon && isValid()==true){
			QList<QPoint> pList = areaPointList();
			for(int i=0; i<pList.count(); i++){
				ret << pList[i];
			}
			if(pList.first() != pList.last()){
				ret << pList.first();
			}
		}

		return ret;
	};

	QSize size(){

		if(isValid()==false){
			return QSize(0,0);
		}

		switch(areaType()){
		case None:
			{
				return QSize(0,0);
			}
			break;
		case Rect:
		case Ellipse:
			{
				return QSize(qAbs(areaPointList()[0].x() - areaPointList()[1].x()), qAbs(areaPointList()[0].y() - areaPointList()[1].y()));
			}
			break;
		case Polygon:
			{
				QPoint topLeft, bottomRight;
				QList<QPoint> list = areaPointList();
				topLeft = bottomRight = list.first();
				for(int i=1; i<list.count(); i++){
					// X
					if(topLeft.x()>list[i].x()){
						topLeft.setX(list[i].x());
					}else if(bottomRight.x()<list[i].x()){
						bottomRight.setX(list[i].x());
					}

					// Y
					if(topLeft.y()>list[i].y()){
						topLeft.setY(list[i].y());
					}else if(bottomRight.y()<list[i].y()){
						bottomRight.setY(list[i].y());
					}
				}
				return QSize(bottomRight.x()-topLeft.x(), bottomRight.y()-topLeft.y());
			}
			break;
		case RotateEllipse:
			{
				return QSize(2*areaPointList().last().x(), 2*areaPointList().last().y());
			}
			break;
		case Ring:
			{
				return QSize(qAbs(areaPointList()[0].x()-areaPointList()[1].x()), qAbs(areaPointList()[0].y()-areaPointList()[1].y()));
			}
			break;
		default:
			return QSize(0,0);
		}
		return QSize(0,0);
	};

	QPainterPath painterPath() const {
		if(isValid()==false){
			return QPainterPath();
		}

		QPainterPath path;
		QTransform transform;
		const QList<QPoint> list = areaPointList();
		
		switch(areaType()){
		case Rect:
			path.addRect(rect());
			break;
		case Ellipse:
			path.addEllipse(rect());
			break;
		case Polygon:
			path.addPolygon(polygon());
			break;
		case RotateEllipse:
			path.addEllipse(areaPointList()[0], areaPointList()[1].x(), areaPointList()[1].y());
			break;
		case Ring:
			// �h���Ԃ��������}�`�͈͓��݂̂Ƃ���
			path.setFillRule(Qt::FillRule::OddEvenFill);
			
			// �O���~
			path.addEllipse(QRect(areaPointList()[0].x(), areaPointList()[0].y(),
				qAbs(areaPointList()[1].x() - areaPointList()[0].x()), qAbs(areaPointList()[1].y() - areaPointList()[0].y())));

			// �����~
			path.addEllipse(QRect(areaPointList()[2].x(), areaPointList()[2].y(),
				qAbs(areaPointList()[3].x() - areaPointList()[2].x()), qAbs(areaPointList()[3].y() - areaPointList()[2].y())));
			break;
		default:
			break;
		}

		return path;
	};

	void drawShape(QPainter &painter, const QTransform &transform = QTransform()) const {

		if(isValid()==false){
			return;
		}

		// ���݃}�g���N�X���擾
		QTransform oldTransform = painter.transform();

		switch(areaType()){
		case Rect:
		case Ellipse:
		case Polygon:
		case Ring:
			{
				// �}�g���N�X���ݒ�
				painter.setTransform(transform);

				// �`��
				painter.drawPath(painterPath());
			}
			break;
		case RotateEllipse:
			{
				QPainterPath path = painterPath();// �ʏ��`���p�X

				QPoint center = areaPointList().first();// ���S

				path.translate(-center);// ���S�����_�Ɉړ�����
				
				// �}�g���N�X���ݒ�
				painter.setTransform(transform);
	
				painter.translate(center);// �`���ʒu���ȉ~�̏ꏊ�Ɉړ�����
				painter.rotate(rotate());// ���]���^����
	
				painter.drawPath(path);// �`��

				painter.rotate(-rotate());// ���]���߂�
				painter.translate(-center);// �`���ʒu���߂�
			}
			break;
		default:
			// �������Ȃ�
			break;
		}
		
		// �}�g���N�X�����ɖ߂�
		painter.setTransform(oldTransform);
	};
	
	void drawText(QPainter &painter, const QTransform &transform = QTransform(), const QTextOption &option = QTextOption()) const
	{
		QTransform oldTransform = painter.transform();
		QFont oldFont = painter.font();
		QFont font = oldFont;

		font.setPointSizeF( font.pointSizeF() / transform.m11() );

		painter.setFont(font);
		painter.setTransform(transform);
		painter.drawText(rect(), pieceName(), option);

		painter.setFont(oldFont);
		painter.setTransform(oldTransform);
	}

private:
	int m_MasterID;
	int m_page;
	int m_pieceID;
	QString m_pieceName;
	AreaType m_type;
	QList<QPoint> m_AreaPointList;
	QString m_ReserveData;
	int m_rotate;
};

typedef QList<PCEItem>	PCEList;

// NG�̂P�P�̏��� : <NGP �`/>�����č\��
class ReviewNGPoint
{
public:
	ReviewNGPoint(void){	clear();	}
	ReviewNGPoint(const ReviewNGPoint &src){
		x			= src.x			;
		y			= src.y			;
		TypeCode	= src.TypeCode	;
		LibCode		= src.LibCode	;
		ItemID		= src.ItemID	;
		SmallPartsID= src.SmallPartsID;
		Ly			= src.Ly		;
		Ral			= src.Ral		;
		result1		= src.result1	;	
		result2		= src.result2	;	
		Error		= src.Error		;
		ItemSearchedX	=src.ItemSearchedX	;
		ItemSearchedY	=src.ItemSearchedY	;
		AlignedX		=src.AlignedX		;
		AlignedY		=src.AlignedY		;
		Ara				=src.Ara			;		

		Tag			=src.Tag		;
		PCEItems	=src.PCEItems	;
	}
	void clear(){
		x = -1;
		y = -1;
		TypeCode = -1;
		LibCode = -1;
		ItemID = -1;
		SmallPartsID = -1;
		Ly = -1;
		Ral = QString();
		result1 = 0;
		result2 = 0;
		Error = -1;
		ItemSearchedX = 0;
		ItemSearchedY = 0;
		AlignedX = 0;
		AlignedY = 0;
		Ara = QString();

		Tag.clear();
		PCEItems.clear();
	};
public:
	int32		x,y;				// X,Y �����摜�����W

	int32		TypeCode;			// TC LibCode�Ŏw�肳���郉�C�u������NG���ނ̃R�[�h
	int32		LibCode;			// LC Ral�Ƃ������O�̃��C�u�����킪���̌������C�u�����R�[�h

	QString		Ral;				// RAL

	short		Error;				//�m�f���x��	�|�P�F�������G���A	�O�F������	�P�F�n�j	�Q�`�m�f
	DWORD		result1;			// RS1 ���ʃf�[�^
	DWORD		result2;			// RS2

	int32		ItemID;				//Number;
    int32		SmallPartsID;		//��ID

	short		ItemSearchedX;		//Hx
    short		ItemSearchedY;		//Hy	�ʒT���␳��
	short		AlignedX;			//Mx
    short		AlignedY;			//My	�A���C�������g�␳��

	int32		Ly;					//LY
	QString		Ara;				//ARA	�Ж��̃��X�g(�J���}�L��)

public:
	QPoint getNGPos() const { return QPoint(x, y); };
	QPoint getMasterPos() const { return QPoint(x - ItemSearchedX - AlignedX, y - ItemSearchedY - AlignedY); };

	ReviewNGPoint& operator=(const ReviewNGPoint &src) {
		if (this == &src) return *this;
		
		x            = src.x;
		y            = src.y;
		TypeCode     = src.TypeCode;
		LibCode      = src.LibCode;
		ItemID       = src.ItemID;
		SmallPartsID = src.SmallPartsID;
		Ly           = src.Ly;
		Ral          = src.Ral;
		result1      = src.result1;    
		result2      = src.result2;    
		Error        = src.Error;
		ItemSearchedX= src.ItemSearchedX;
		ItemSearchedY= src.ItemSearchedY;
		AlignedX     = src.AlignedX;
		AlignedY     = src.AlignedY;
		Ara          = src.Ara;        
		Tag          = src.Tag;
		PCEItems     = src.PCEItems;
		
		return *this;
	}
public:
	InsLibraryItem::TypeNameTag Tag;
	PCEList						PCEItems;

	QStringList	AraList() const { return Ara.split(','); };			//ARA	�Ж��̃��X�g(�J���}���؂蕪����)
	bool	operator==(const ReviewNGPoint &src);
public:

	bool    Load(QIODevice *f);
    bool    Save(QIODevice *f);
};

typedef QList<ReviewNGPoint>		ReviewNGPointList;
typedef ReviewNGPointList			*ReviewNGPointListPtr;
typedef ReviewNGPoint				*ReviewNGPointIndex;
typedef QList<ReviewNGPointIndex>	ReviewNGPointIndexList;



class HistoryItem;

class NGNailItemRef
{
public:
	NGNailItemRef(){		
		TargetPosX = -1;
		TargetPosY = -1;
		MasterPosX = -1;
		MasterPosY = -1;
		phase = -1;
		page = -1;
		IDX = -1;
		FKey = Review::NoFKey;
		OutlineOffsetX	=0;
		OutlineOffsetY	=0;
	}
	NGNailItemRef(const NGNailItemRef &src){
		TargetPosX = src.TargetPosX ;
		TargetPosY = src.TargetPosY ;
		MasterPosX = src.MasterPosX ;
		MasterPosY = src.MasterPosY ;
		phase	= src.phase	;
		page	= src.page	;
		IDX		= src.IDX	;
		FKey	= src.FKey	;
		OutlineOffsetX	=src.OutlineOffsetX;
		OutlineOffsetY	=src.OutlineOffsetY;
	}
	virtual void clear(){
		TargetPosX = -1;
		TargetPosY = -1;
		MasterPosX = -1;
		MasterPosY = -1;
		phase = -1;
		page = -1;
		IDX = -1;
		FKey = Review::NoFKey;
		OutlineOffsetX	=0;
		OutlineOffsetY	=0;

	}
public:
	int		TargetPosX;
	int		TargetPosY;
	int		MasterPosX;
	int		MasterPosY;

	int		OutlineOffsetX;
	int		OutlineOffsetY;
public:
	int		page;
	int		phase;
	Review::FKey FKey;

public:
	int		IDX;

public:
	bool operator==(const NGNailItemRef &other) const {
		return (TargetPosX == other.TargetPosX) &&
			(TargetPosY == other.TargetPosY) &&
			(MasterPosX == other.MasterPosX) &&
			(MasterPosY == other.MasterPosY) &&
			(page == other.page) &&
			(phase == other.phase) &&
			(IDX == other.IDX);
	}
	NGNailItemRef &operator=(const NGNailItemRef &src)
	{
		TargetPosX = src.TargetPosX ;
		TargetPosY = src.TargetPosY ;
		MasterPosX = src.MasterPosX ;
		MasterPosY = src.MasterPosY ;
		phase	= src.phase	;
		page	= src.page	;
		IDX		= src.IDX	;
		FKey	= src.FKey	;
		OutlineOffsetX	=src.OutlineOffsetX;
		OutlineOffsetY	=src.OutlineOffsetY;
		return *this;
	}
};

class NGNailItem : public NGNailItemRef
{
public:
	NGNailItem()/*:NGImage(NULL)*/{	clear();	}
	NGNailItem(const NGNailItem &src):NGNailItemRef(src){ 
		NGReader		= src.NGReader;
		NGImageWidth	= src.NGImageWidth ;
		NGImageHeight	= src.NGImageHeight ;
		isChecked		= src.isChecked ;
		NGPointList		=src.NGPointList;
		InspectID		= src.InspectID ;
	}

	virtual	~NGNailItem(){};
	virtual void clear()
	{
		NGNailItemRef::clear();

		NGReader		= NULL;
		NGImageWidth	= -1;
		NGImageHeight	= -1;
		isChecked		= false;
		NGPointList.clear();
		InspectID = -1;
	};

public:

	int		NGImageWidth	;
	int		NGImageHeight	;
	bool	isChecked		;		
	mutable QImage  Image	;
	QImage	DummyImage		;

	ReviewNGPointList	NGPointList; // NG�摜�Ɋ܂܂���NG�̏W�܂�
	int InspectID;// �ڑ�����HistoryItem�Őݒ肳����
	mutable QMutex imageMutex;

public:
	void setNGReader(NGImageReaderOneFile *Reader){ NGReader = Reader; };
	inline const NGImageReaderOneFile *getNGReader(void) const { return NGReader; };
	inline NGImageReaderOneFile *getNGReader(void) { return NGReader; };
	bool hasNGReader(void) const { return (getNGReader()!=NULL); };
	void setDummyImage(const QImage &image){ DummyImage = image; };
	QImage image(void) const {
		QMutexLocker locker(&imageMutex);
		QImage ret;

		if(DummyImage.isNull()==false){
			ret = DummyImage;
		}else if(Image.isNull()==false){
			ret = Image;
		}else{
			if(hasNGReader()){
				if(getNGReader()->isFinished()==false){
					if(getNGReader()->isRunning()==false){
						NGReader->start();
					}
					while(getNGReader()->isFinished()==false)
						;
				}
				ret = NGReader->getImage(getNGNailItemRef().TargetPosX, getNGNailItemRef().TargetPosY, getNGNailItemRef().phase);
				Image = ret;
			}
		}

		return ret;
	};
	NGNailItem	&operator=(const NGNailItem &src){
		NGNailItemRef::operator=(src);
		NGReader		= src.NGReader;
		NGImageWidth	= src.NGImageWidth ;
		NGImageHeight	= src.NGImageHeight ;
		isChecked		= src.isChecked ;
		NGPointList		=src.NGPointList;
		InspectID		= src.InspectID ;
		return *this;
	}

private:
	mutable NGImageReaderOneFile *NGReader;

public:
	NGNailItemRef getNGNailItemRef() const {
		NGNailItemRef ret = *this;
		return ret;
	};
	QString getLibraryRal(void) const {
		if(NGPointList.count()==0){
			return QString(/**/"");
		}else{
			return NGPointList.first().Ral;
		}
	};
	int		getLibraryCode(void) const {
		if(NGPointList.count()==0){
			return -1;
		}else{
			return NGPointList.first().LibCode;
		}
	};
	QString	getArea(void)const{
		if(NGPointList.count()==0){
			return /**/"";
		}else{
			return NGPointList.first().Ara;
		}
	}

	void	unloadImage(){
		Image = QImage();
		//QString filename = /**/"";
		//QPoint pos(0,0);
		//if(NGImage!=NULL){
		//	filename = NGImage->filename();
		//	pos = NGImage->pos();
		//	deleteReader();
		//}
		//NGImage = new NGImageReader;
		//NGImage->setFilename(filename);
		//NGImage->setPos(pos);
	};
	//bool	isLoaded() const {
	//	if(NGReader==NULL){
	//		return false;
	//	}else{
	//		return NGReader->isFinished();
	//	}
	//	//if(NGImage==NULL){
	//	//	return false;
	//	//}else{
	//	//	return NGImage->isFinished();
	//	//}
	//};
};

typedef QList<NGNailItem>	NGNailList;
typedef NGNailList			*NGNailListPtr;
typedef NGNailItem			*NGNailIndex;
typedef QList<NGNailIndex>	NGNailIndexList;

//�m�f�������� : ShowHistoryListForReview�̃��X�g1����(XML��IST�^�O1��)
//
// ReviewPIBase�ɕۑ�������
//
class HistoryItem
{
public:
	int			InspectedMachine;
	QString		XMLSearchFormat;
	XDateTime	InspectedTime;	// ��������
	int			_InspectID;		// ����ID
	int			NGCount;		// NG��
	QStringList Result;			// ���ʏ��� : 
								//	TimeOver	�^�C���I�[�o�[
								//	MaxOver		NG�������I�[�o�[
								//	OK			OK�֐U�蕪��
								//	NG			NG�֐U�蕪��
	Review::SideType Side;

public:
	void setInspectID(int id){ _InspectID = id; };
	int InspectID() const { return _InspectID; };

private:
	NGNailList	m_NGNails;		// NG���� : NG�摜�P�ʂ̗v�f�����R���e�i
	NGImageReaderOneFile *m_NGReader;
	QString m_Filename;
	QList<int> m_IDXList;
	ReviewPIBase	*PBase;
public:
	void setNGNails(const NGNailList &Nails){
		m_NGNails = Nails;
		for(int i=0; i<m_NGNails.count(); i++){
			m_NGNails[i].setNGReader(m_NGReader);
			m_NGNails[i].InspectID = InspectID();
		}
	};
	inline const NGNailList &getNGNails(void) const { return m_NGNails; };
	inline NGNailList &getNGNails(void) { return m_NGNails; };

public:
	HistoryItem(ReviewPIBase *pBase);

	//HistoryItem(const HistoryItem &other){
	//	*this = other;
	//	m_autoDelete = false;
	//};

	~HistoryItem(){};

public:
	void setJDTFilename(const QString &Filename){
		if(m_NGReader!=NULL){
			m_NGReader->setFilename(Filename);
		}
		m_Filename = Filename;
	};

	void setJDTFileIDXList(const QList<int> &list){
		if(m_NGReader!=NULL){
			m_NGReader->setIDXList(list);
		}
		m_IDXList = list;
	};

	void createReader(void);

	void deleteReader(void){
		if(m_NGReader!=NULL){
        if(m_NGReader->isRunning()){
            m_NGReader->requestInterruption(); // または quit()
            m_NGReader->wait(); // スレッドの安全な停止を待つ
        }
        m_NGReader->deleteLater();;
        m_NGReader = NULL;
    }
	};

	void loadNGImage(void){
		if(m_NGReader->isFinished()==false && m_NGReader->isRunning()==false){// �I�����ĂȂ��Ď��s�����Ă����Ȃ��ꍇ�̓X�^�[�g
			m_NGReader->start();
		}
	};

public:
	Review::FKey getFKeyInfo(QList<int> &perNail, QList<int> &perNG) const {
		if(m_NGNails.count()==0){
			return Review::NoFKey;
		}

		// ���ꕨ�̏�����
		perNail	= QVector<int>(13, 0).toList();
		perNG	= QVector<int>(13, 0).toList();

		// F�L�[�������v��
		for(NGNailList::ConstIterator item=m_NGNails.constBegin(); item!=m_NGNails.constEnd(); item++){
			perNail[Review::FKeyToInt(item->FKey)] += 1;// F�L�[�ɑΉ������z�����C���N�������g
			perNG[Review::FKeyToInt(item->FKey)] += item->NGPointList.count();// �d�������܂�
		}

		// �ő�F�L�[�J�E���g����F�L�[���擾
		// �����̏ꍇ�AF[i]��i�������������D���I�ɑI�΂���
		int maxIndex = 0;
		int maxCount = perNail[maxIndex];
		for(int i=1; i<perNail.count()-1; i++){
			if(perNail[i] > maxCount){
				maxCount = perNail[i];
				maxIndex = i;
			}
		}
		// F�L�[���P���t���Ă��Ȃ��ꍇ��F�L�[�Ȃ�
		// �����ꂩ��F�L�[���P�ł��t���Ă����΁A����F�L�[�����ɂ���
		if(maxCount==0){
			return Review::NoFKey;
		}else{
			return Review::IntToFKey(maxIndex);
		}
	};
	bool isOK() const {
		return m_NGNails.isEmpty();
	};
	bool isErrorResult() const {
		for(int i=0; i<Result.count(); i++){
			if(Result[i]!=/**/"OK" && Result[i]!=/**/"NG"){
				return true;
			}
		}
		return false;
	};
	bool isHalt() const {
		for(int i=0; i<Result.count(); i++){
			if(Result[i]==/**/"TimeOver" || Result[i]==/**/"MaxOver"){
				return true;
			}
		}
		return false;
	};
public:
	HistoryItem &operator=(const HistoryItem &other){
		InspectedTime = other.InspectedTime;
		setInspectID(other.InspectID());
		NGCount = other.NGCount;
		m_NGNails = other.m_NGNails;
		Side = other.Side;

		return *this;
	}
public:
	bool operator<(const HistoryItem &other) const { return (this->InspectID() < other.InspectID()); };
};

typedef QList<HistoryItem>	HistoryList;
typedef HistoryList			*HistoryListPtr;
typedef HistoryItem			*HistoryIndex;
typedef QList<HistoryIndex>	HistoryIndexList;

class OrganizedHistoryItem
{
public:
	OrganizedHistoryItem(){
		clear();
	};
	OrganizedHistoryItem(const OrganizedHistoryItem &other){
		FrontItem = other.getFront();
		BackItem = other.getBack();
		updateIteratorList();
		Type = other.getSideType();
		FKey = other.getFKey();
	}
public:


	void clear(){
		FrontItem = NULL;
		BackItem = NULL;
		Type = Review::None;
	};
	void setHistoryItem(HistoryItem *item, Review::SideType side){
		if(side==Review::Front){
			FrontItem = item;
			updateIteratorList();
		}else if(side==Review::Back){
			BackItem = item;
			updateIteratorList();
		}else{
			// do nothing
		}
	};
	void updateIteratorList(){
		FrontBackNGNailList.clear();

		if(FrontItem!=NULL){
			NGNailList	&tNGNail=FrontItem->getNGNails();
			for(NGNailList::Iterator it=tNGNail.begin(); it!=tNGNail.end(); it++){
				FrontBackNGNailList.append(it);
			}
		}
		if(BackItem!=NULL){
			NGNailList	&tNGNail=BackItem->getNGNails();
			for(NGNailList::Iterator it=tNGNail.begin(); it!=tNGNail.end(); it++){
				FrontBackNGNailList.append(it);
			}
		}
	}
	NGNailList::Iterator getNGNailItemIterator(int GlobalIndex) const {
		if(GlobalIndex<0 || FrontBackNGNailList.size() <= GlobalIndex){
			return NGNailList::Iterator();
		}else{
			return FrontBackNGNailList[GlobalIndex];
		}
	};
	int indexOf(NGNailItemRef ref) const {
		for(int i=0; i<FrontBackNGNailList.size(); i++){
			if(ref==FrontBackNGNailList[i]->getNGNailItemRef()){
				return i;
			}
		}
		return -1;
	};
	Review::SideType getWhitchSide(int GlobalIndex) const {
		if(FrontItem==NULL && BackItem==NULL){
			return Review::NoSide;
		}
		if(FrontItem!=NULL && GlobalIndex < FrontItem->getNGNails().count()){
			return Review::Front;
		}else{
			return Review::Back;
		}
	};

	void setSide(Review::OrganizedSideType type){ Type = type; };
	void setFKey(Qt::Key key){ FKey = key; };
	XDateTime getInspectedTime() const {
		if(FrontItem!=NULL)return FrontItem->InspectedTime;
		if(BackItem!=NULL)return BackItem->InspectedTime;
		return XDateTime();
	};
	int getInspectID() const {
		if(FrontItem!=NULL){
			return FrontItem->InspectID();
		}else if(BackItem!=NULL){
			return BackItem->InspectID();
		}else{
			return -1;
		}
	};
	int getNGCount() const {
		int ret = 0;

		if(FrontItem!=NULL){
			ret += FrontItem->NGCount;
		}
		if(BackItem!=NULL){
			ret += BackItem->NGCount;
		}

		return ret;
	};
	int getNGNailCount() const {
		int ret=0;

		if(FrontItem!=NULL){
			ret += FrontItem->getNGNails().count();
		}
		if(BackItem!=NULL){
			ret += BackItem->getNGNails().count();
		}

		return ret;
	};
	bool	IsHalt(void) const{
		if(FrontItem!=NULL){
			if(FrontItem->isHalt()==true)
				return true;
		}
		if(BackItem!=NULL){
			if(BackItem->isHalt()==true)
				return true;
		}
		return false;
	}

	HistoryItem *getFront() const {
		if(FrontItem!=NULL){
			return FrontItem;
		}else{
			return NULL;
		}
	};
	bool hasFront() const { return (FrontItem!=NULL); };
	HistoryItem *getBack() const {
		if(BackItem!=NULL){
			return BackItem;
		}else{
			return NULL;
		}
	};
	bool hasBack() const { return (BackItem!=NULL); };
	Review::OrganizedSideType getSideType() const {
		return Type;
	};
	bool hasSide(Review::SideType side) const {
		if(isFront(side)==true){
			return hasFront();
		}else{
			return hasBack();
		}
	};
	HistoryItem *getSide(Review::SideType side) const {
		if(isFront(side)==true){
			return getFront();
		}else{
			return getBack();
		}
	};
	bool isErrorBoard() const {
		if(hasFront() && getFront()->isErrorResult()){
			return true;
		}
		if(hasBack() && getBack()->isErrorResult()){
			return true;
		}
		return false;
	};
	Qt::Key getFKey() const { return FKey; };
	int error() const {return -1;};
	Review::SideType getWhitchSide(NGNailItemRef ref) const {
		if(FrontItem!=NULL){
			for(NGNailList::ConstIterator item=FrontItem->getNGNails().constBegin(); item!=FrontItem->getNGNails().constEnd(); item++){
				if(ref==(*item)){
					return Review::Front;
				}
			}
		}
		if(BackItem!=NULL){
			for(NGNailList::ConstIterator item=BackItem->getNGNails().constBegin(); item!=BackItem->getNGNails().constEnd(); item++){
				if(ref==(*item)){
					return Review::Back;
				}
			}
		}
		return Review::NoSide;
	};
	OrganizedHistoryItem &operator=( const OrganizedHistoryItem &other){
		FrontItem = other.getFront();
		BackItem = other.getBack();
		updateIteratorList();
		Type = other.getSideType();
		FKey = other.getFKey();

		return *this;
	};
	bool isEmergencyResult(QString &text) const {
		bool res = false;
		QStringList retTextList;
		if(hasFront()==true){
			QStringList resList = getFront()->Result;
			if(resList.isEmpty()==true){
				retTextList << QString("HistoryNo.%1 [Front]:No Result infomation.").arg(getInspectID());
				res = true;
			}
			if(resList.contains(/**/"OK", Qt::CaseInsensitive)==true){
				if(resList.contains(/**/"NG", Qt::CaseInsensitive)==true || resList.contains(/**/"TimeOver", Qt::CaseInsensitive)==true || resList.contains(/**/"MaxError", Qt::CaseInsensitive)==true){
					retTextList << QString("HistoryNo.%1 [Front]:Result has OK and NG code both.").arg(getInspectID());
					res = true;
				}
			}
		}
		if(hasBack()==true){
			QStringList resList = getBack()->Result;
			if(resList.isEmpty()==true){
				retTextList << QString("HistoryNo.%1 [Back]:No Result infomation.").arg(getInspectID());
				res = true;
			}
			if(resList.contains(/**/"OK", Qt::CaseInsensitive)==true){
				if(resList.contains(/**/"NG", Qt::CaseInsensitive)==true || resList.contains(/**/"TimeOver", Qt::CaseInsensitive)==true || resList.contains(/**/"MaxError", Qt::CaseInsensitive)==true){
					retTextList << QString("HistoryNo.%1 [Back]:Result has OK and NG code both.").arg(getInspectID());
					res = true;
				}
			}
		}
		if(res==true){
			text = retTextList.join(/**/"\n");
		}
		return res;
	};
	bool isOK() const {
		if(hasFront()==true){
			if(getFront()->getNGNails().isEmpty()==false){
				for(int i=0; i<getFront()->getNGNails().count(); i++){
					if(getFront()->getNGNails()[i].NGPointList.isEmpty()==false){
						return false;
					}
				}
			}
		}
		if(hasBack()==true){
			if(getBack()->getNGNails().isEmpty()==false){
				for(int i=0; i<getBack()->getNGNails().count(); i++){
					if(getBack()->getNGNails()[i].NGPointList.isEmpty()==false){
						return false;
					}
				}
			}
		}
		return true;
	};
	bool isCheckedAll() const {
		if(hasFront()==true){
			for(NGNailList::ConstIterator it=FrontItem->getNGNails().constBegin(); it!=FrontItem->getNGNails().constEnd(); it++){
				if(it->isChecked==false){
					return false;
				}
			}
		}
		if(hasBack()==true){
			for(NGNailList::ConstIterator it=BackItem->getNGNails().constBegin(); it!=BackItem->getNGNails().constEnd(); it++){
				if(it->isChecked==false){
					return false;
				}
			}
		}
		return true;
	}

public:
	bool operator==(const OrganizedHistoryItem &other) const {
		if( FrontItem==other.getFront() && BackItem==other.getBack() ){
			return true;
		}
		return false;
	};
private:
	HistoryIndex FrontItem;
	HistoryIndex BackItem;
	QList<NGNailList::Iterator> FrontBackNGNailList;
	Review::OrganizedSideType Type;
	Qt::Key FKey;
};

typedef QList<OrganizedHistoryItem>		OrganizedHistoryList;
typedef OrganizedHistoryList			*OrganizedHistoryListPtr;
typedef OrganizedHistoryItem			*OrganizedHistoryIndex;
typedef QList<OrganizedHistoryIndex>	OrganizedHistoryIndexList;

// JDT�t�@�C���̉摜�f�[�^�ЂƂ��̏������ێ������N���X
class JDTItem
{
public:
	JDTItem(int version=-1, int page=-1, int staticID=-1, int top=-1, int left=-1, int bottom=-1, int right=-1, const QImage &img=QImage())
		:_Ver(version),_Page(page),_StaticID(staticID),_Top(top),_Left(left),_Bottom(bottom),_Right(right),_Image(img){};
public:
	int version() const { return _Ver; };
	int page() const { return _Ver; };
	int staticID() const { return _StaticID; };
	int top() const { return _Top; };
	int left() const { return _Left; };
	int bottom() const { return _Bottom; };
	int right() const { return _Right; };
	QImage image() const { return _Image; };

	void setVersion(int version){ _Ver = version; };
	void setPage(int page){ _Page = page; };
	void setStaticID(int id){ _StaticID = id; };
	void setTop(int top){ _Top = top; };
	void setLeft(int left){ _Left = left; };
	void setBottom(int bottom){ _Bottom = bottom; };
	void setRight(int right){ _Right = right; };
	void setImage(QImage &image){ _Image = image; };

	bool isEnable() const {
		return (_Ver!=1) && (_Page!=-1) && (_StaticID!=-1) && (_Top!=-1) && (_Left!=-1) && (_Bottom!=-1) && (_Right!=-1) && (_Image.isNull()==false);
	};
private:
	int _Ver;
	int _Page;
	int _StaticID;
	int _Top;
	int _Left;
	int _Bottom;
	int _Right;
	QImage _Image;
};

typedef QList<JDTItem>	JDTList;
typedef JDTList			*JDTListPtr;
typedef JDTItem			*JDTIndex;
typedef QList<JDTIndex>	JDTIndexList;

// �\�Ɨ��̓ǂݍ��񂾃}�X�^�[�f�[�^�̃o�b�t�@
// �֋X���A���S���Y���ɕۑ����Ă���
// �����I�ɕ����̕\���\�����g�p���邽�ߕۑ��ł����悤�ɂ��Ă���
class MasterDataInfo
{
public:
	MasterDataInfo(){ clear(); };

public:
	void clear()
	{
		Side = Review::SideType::Front;

		MasterCode = -1;
		MachineID = -1;
		PageNumb = 0;
		PhaseNumb = 0;
		RegTime = XDateTime::currentDateTime();
		MasterName = /**/"";
		Remark = /**/"";
		Version = -1;
		LastEditTime = XDateTime::currentDateTime();
		CategoryID	= -1;
		MasterType	= -1;
		DotPerLine	= 0;
		MaxLines	= 0;
		LayerNumb	= 0;
		LibFolderID	=-1;
		ThresholdLevelID	=0;
		ThresholdLevelParentID=0;
	};

	bool isEmpty() const {
		return (MasterCode==-1);
	};

public:
	Review::SideType Side;

	int MasterCode;
	int MachineID;
	XDateTime	RegTime;
	QString		MasterName;
	QString		Remark;
	int32		Version;
	XDateTime	LastEditTime;
	int32		CategoryID;
	int16		MasterType;
	int	DotPerLine;
	int	MaxLines;
	int	LayerNumb;
	int	PageNumb;
	int PhaseNumb;
	int	LibFolderID;
	int	ThresholdLevelID;
	int	ThresholdLevelParentID;
};

class LotInfoItem
{
public:
	LotInfoItem(){
		clear();
	};

	void clear(){
		MasterCode = -1;
		MachineCode = -1;
		TableName = QString();
		LotName = QString();
		Remark = QString();
	};

	bool isEmpty() const {
		return (MasterCode	== -1 ||
				MachineCode	== -1 ||
				TableName	== QString());
	};
public:
	int MasterCode;
	int MachineCode;
	QString TableName;
	QString LotName;
	QString Remark;

public:
	QString Filename() const {
		int index = TableName.lastIndexOf(/**/"/");
		if(index==-1){
			return TableName;
		}else{
			return TableName.mid(index+1);
		}
	}
};

typedef QList<LotInfoItem> LotInfoList;

//----------------------------------------------------------------------------------

class	ForSaveNGPoint : public NPList<ForSaveNGPoint>
{
public:
	XDateTime	Entering;
	XDateTime	Leaving;
	int			FnKeyNumber;	//-2: Not viewed , -1:viewed  0:F1 1:F2 ...
	QPoint		Position;
	QString		Cause;
	int			Side;
	int			LineNumber;
	bool		Top;

	ForSaveNGPoint(int lineNumber);

	ForSaveNGPoint	&operator=(ForSaveNGPoint &src);
	bool	SaveCSV(QTextStream &Str);

	int	GetTopNGCount(void)		{	return (Top==true)?1:0;		}
	int	GetBottomNGCount(void)	{	return (Top==true)?0:1;		}
};

class	ForSaveOneInspection : public NPList<ForSaveOneInspection>
{
public:
	XDateTime	Entering;
	int			LineNumber;
	int			InspectionID;
	XDateTime	InspectionTime;
	int			Halt;		//1:NG	2:TimeOver	3:MaxError

	NPListPack<ForSaveNGPoint>	NGList;

	ForSaveOneInspection(void);

	ForSaveNGPoint	*FindByLineNumber(int LNumber);

	bool	SaveCSV(QTextStream &Str);

	int	GetTopNGCount(void);
	int	GetBottomNGCount(void);
};


inline	ForSaveOneInspection::ForSaveOneInspection(void)
{
	LineNumber	=-1;
	InspectionID=-1;
	Halt		=-1;
}

inline	ForSaveNGPoint::ForSaveNGPoint(int lineNumber)
{
	FnKeyNumber	=-2;
	Side		=-1;
	LineNumber	=lineNumber;
}

inline	ForSaveNGPoint	&ForSaveNGPoint::operator=(ForSaveNGPoint &src)
{
	Entering	=src.Entering;
	Leaving		=src.Leaving;
	FnKeyNumber	=src.FnKeyNumber;
	Position	=src.Position;
	Cause		=src.Cause;
	Side		=src.Side;
	LineNumber	=src.LineNumber;
	return *this;
}

inline	ForSaveNGPoint	*ForSaveOneInspection::FindByLineNumber(int LNumber)
{
	for(ForSaveNGPoint *a=NGList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LineNumber==LNumber){
			return a;
		}
	}
	return NULL;
}

inline	int	ForSaveOneInspection::GetTopNGCount(void)
{
	int	NGCount=0;
	for(ForSaveNGPoint *a=NGList.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetTopNGCount();
	}
	return NGCount;
}
inline	int	ForSaveOneInspection::GetBottomNGCount(void)
{
	int	NGCount=0;
	for(ForSaveNGPoint *a=NGList.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetBottomNGCount();
	}
	return NGCount;
}