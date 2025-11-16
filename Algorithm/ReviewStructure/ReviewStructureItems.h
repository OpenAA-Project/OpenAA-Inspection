#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ReviewPIBaseで使用するデータ定義
//
//  通常では以下のようなセットで定義される
//    class ClassItem{...};
//    typedef QList<ClassItem>	ClassList;
//    typedef ClassList			*ClassListPtr;
//    typedef ClassItem			*ClassIndex;
//    typedef QList<ClassIndex>	ClassIndexList;
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

// XMLに記述されている<INSLIB から始まるライブラリ情報より再構成する
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
		int NGBlink;//		NGBLINK= [0で無効]
		int NGPriority;//	NGPRIORITY= [数値が低いほど優先度が高い]
		int Wait;//			WAIT= [次のNGへ移動するまでの待機時間]
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

// Ralをキーとしたライブラリデータへのハッシュ
// NG情報からライブラリデータの参照を行う時に使用する
//
// ReviewPIBaseに保存される
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
		TypeUniqueCode = other.TypeUniqueCode;	//データベース内で唯一の値
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
	属性名称	AREA
	データの記述
		形状記号	R:矩形	E:楕円	P:多角形  T:回転楕円  G:リング
		座標列		X,Y
		特記事項	多角形の場合は座標数は最大１００までとする。
					１００を超える場合は、間引かれる
		例
			AREA="R10,20,50,60"				(10,20)-(50,60)の矩形
			AREA="E60,-100,120,150"			(60,-100)-(120,150)の矩形に内接する楕円
			AREA="P0,0,10,10,30,10,30,0"	(0,0)-(10,10)-(30,10)-(30,0)を結ぶ多角形
											始点と終点が一致しなくても構わない
			AREA="T40,500,20,25,60"			中心座標Ｘ、中心座標Ｙ、Ｘ方向の半径、Ｙ方向の半径、回転角度（度）
			AREA="G10,100,120,250,30,160,70,200"	(10,100)-(120,250)の外側楕円と(30,160)-(70,200)の内側楕円の間の領域
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
		case RotateEllipse:// 回転0度の楕円について縦横の小さい方のサイズを1辺とした正方形
			{
				int rwidth = pList[1].x();
				int rheight = pList[1].y();

				int rmax = qMin(rwidth, rheight);

				ret = QRect(pList[0] - QPoint(rmax,rmax), pList[0] + QPoint(rmax,rmax));
			}
			break;
		case Ring:// リングの上側と左側の面積を簡易的に矩形で調べ、広い方の矩形を選択する
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
			// 塗りつぶし条件を図形範囲内のみとする
			path.setFillRule(Qt::FillRule::OddEvenFill);
			
			// 外側円
			path.addEllipse(QRect(areaPointList()[0].x(), areaPointList()[0].y(),
				qAbs(areaPointList()[1].x() - areaPointList()[0].x()), qAbs(areaPointList()[1].y() - areaPointList()[0].y())));

			// 内側円
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

		// 現在マトリクスを取得
		QTransform oldTransform = painter.transform();

		switch(areaType()){
		case Rect:
		case Ellipse:
		case Polygon:
		case Ring:
			{
				// マトリクスを設定
				painter.setTransform(transform);

				// 描画
				painter.drawPath(painterPath());
			}
			break;
		case RotateEllipse:
			{
				QPainterPath path = painterPath();// 通常描画パス

				QPoint center = areaPointList().first();// 中心

				path.translate(-center);// 中心を原点に移動する
				
				// マトリクスを設定
				painter.setTransform(transform);
	
				painter.translate(center);// 描画位置を楕円の場所に移動する
				painter.rotate(rotate());// 回転を与える
	
				painter.drawPath(path);// 描画

				painter.rotate(-rotate());// 回転を戻す
				painter.translate(-center);// 描画位置を戻す
			}
			break;
		default:
			// 何もしない
			break;
		}
		
		// マトリクスを元に戻す
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

// NGの１個１個の情報 : <NGP ～/>から再構成
class ReviewNGPoint
{
public:
	ReviewNGPoint(void){clear();};
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
	int32		x,y;				// X,Y 検査画像上座標

	int32		TypeCode;			// TC LibCodeで指定されるライブラリのNG種類のコード
	int32		LibCode;			// LC Ralという名前のライブラリ種がもつの検査ライブラリコード

	QString		Ral;				// RAL

	short		Error;				//ＮＧレベル	－１：未検査エリア	０：未判定	１：ＯＫ	２～ＮＧ
	DWORD		result1;			// RS1 結果データ
	DWORD		result2;			// RS2

	int32		ItemID;				//Number;
    int32		SmallPartsID;		//個片ID

	short		ItemSearchedX;		//Hx
    short		ItemSearchedY;		//Hy	個別探索補正量
	short		AlignedX;			//Mx
    short		AlignedY;			//My	アラインメント補正量

	int32		Ly;					//LY
	QString		Ara;				//ARA	個片名称リスト(カンマ有り)

public:
	QPoint getNGPos() const { return QPoint(x, y); };
	QPoint getMasterPos() const { return QPoint(x - ItemSearchedX - AlignedX, y - ItemSearchedY - AlignedY); };

public:
	InsLibraryItem::TypeNameTag Tag;
	PCEList						PCEItems;

	QStringList	AraList() const { return Ara.split(','); };			//ARA	個片名称リスト(カンマ区切り分割後)
	bool	operator==(const ReviewNGPoint &src);
public:

	bool    Load(QIODevice *f);
    bool    Save(QIODevice *f);
};

typedef QList<ReviewNGPoint>		ReviewNGPointList;
typedef ReviewNGPointList			*ReviewNGPointListPtr;
typedef ReviewNGPoint				*ReviewNGPointIndex;
typedef QList<ReviewNGPointIndex>	ReviewNGPointIndexList;

//ＮＧ箇所の情報 : NGImageListForReview で表示されるリストひとつ分のデータ
//XMLのNGデータから再構成する : NG画像1枚単位でのまとまり. <NGI ～/>とReviewNGPoint、および<IST NGJ=～>から再構成
//
//  ReviewPIBaseに保存される
//

// NGNailItemの比較用クラス
// 保持しているデータを用いて同じデータかどうかをチェックすることに使用する
// 継承先でも == は使用できる

class HistoryItem;

class NGNailItemRef
{
public:
	NGNailItemRef(){clear();};
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

	};
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
	Review::FKey FKey;// Fキー情報

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
	};
};

class NGNailItem : public NGNailItemRef
{
public:
	NGNailItem()/*:NGImage(NULL)*/{clear();};
	~NGNailItem(){};
	virtual void clear()
	{
		NGNailItemRef::clear();

		//NGImage = QImage();
		//deleteReader();
		//NGImage = new NGImageReader;
		NGReader = NULL;
		NGImageWidth = -1;
		NGImageHeight = -1;
		isChecked = false;
		NGPointList = ReviewNGPointList();
		InspectID = -1;
		//NGImageFilename = /**/"";
	};
	//void setReader(NGImageReader *reader){
	//	deleteReader();
	//	NGImage = reader;
	//};

	//void deleteReader(){
	//	if(NGImage!=NULL){
	//		if(NGImage->isRunning()){
	//			NGImage->terminate();
	//			while(!NGImage->isFinished()){}
	//		}
	//		delete NGImage;
	//	}
	//	NGImage = NULL;
	//};
public:
	//QBitmap	NGImage		// QBitmapでPNGを引き出すと画像が劣化するので、QImageへ変更。QPixmapでも代用可能のよう。実際に利用する段階で、利用しやすい方に決定する。
	//QImage	NGImage;		// NG画像
	//NGImageReader *NGImage;
	int		NGImageWidth;
	int		NGImageHeight;
	bool	isChecked;		// 確認済みフラグ 確認フラグがtrueならばFKeyは有効
	//QString NGImageFilename;
	mutable QImage  Image;
	QImage	DummyImage;

	ReviewNGPointList	NGPointList; // NG画像に含まれるNGの集まり
	int InspectID;// 接続先のHistoryItemで設定される

public:
	void setNGReader(NGImageReaderOneFile *Reader){ NGReader = Reader; };
	inline const NGImageReaderOneFile *getNGReader(void) const { return NGReader; };
	inline NGImageReaderOneFile *getNGReader(void) { return NGReader; };
	bool hasNGReader(void) const { return (getNGReader()!=NULL); };
	void setDummyImage(const QImage &image){ DummyImage = image; };
	QImage image(void) const {
		QImage ret;

		if(DummyImage.isNull()==false){// ダミー優先
			ret = DummyImage;
		}else if(Image.isNull()==false){// すでに読み込み済み
			ret = Image;
		}else{// 未読み込みの場合は読み込み
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

private:
	mutable NGImageReaderOneFile *NGReader;

public:
	NGNailItemRef getNGNailItemRef() const {
		NGNailItemRef ret = *this;
		//ret.TargetPosX = TargetPosX;
		//ret.TargetPosY = TargetPosY;
		//ret.MasterPosX = MasterPosX;
		//ret.MasterPosY = MasterPosY;
		//ret.page = page;
		//ret.phase = phase;
		//ret.FKey = FKey;

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
	//void	loadImage(){
	//	if(NGReader!=NULL && NGReader->isRunning()==true){
	//		while(NGReader->isFinished()==false){
	//			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	//		}
	//	}
	//	if(NGReader!=NULL){
	//		 Image = NGReader->getImage(getNGNailItemRef().TargetPosX, getNGNailItemRef().TargetPosY);
	//	}
	//};
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

//ＮＧ履歴情報 : ShowHistoryListForReviewのリスト1列分(XMLのISTタグ1個分)
//
// ReviewPIBaseに保存される
//
class HistoryItem
{
public:
	int			InspectedMachine;
	QString		XMLSearchFormat;
	XDateTime	InspectedTime;	// 検査時間
	int			_InspectID;		// 検査ID
	int			NGCount;		// NG個数
	QStringList Result;			// 結果情報 : 
								//	TimeOver	タイムオーバー
								//	MaxOver		NG個数上限オーバー
								//	OK			OKへ振り分け
								//	NG			NGへ振り分け
	Review::SideType Side;

public:
	void setInspectID(int id){ _InspectID = id; };
	int InspectID() const { return _InspectID; };

private:
	NGNailList	m_NGNails;		// NG情報 : NG画像単位の要素をもつコンテナ
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
			delete m_NGReader;
			m_NGReader = NULL;
		}
	};

	void loadNGImage(void){
		if(m_NGReader->isFinished()==false && m_NGReader->isRunning()==false){// 終わってなくて実行されてもいない場合はスタート
			m_NGReader->start();
		}
	};

public:
	Review::FKey getFKeyInfo(QList<int> &perNail, QList<int> &perNG) const {
		if(m_NGNails.count()==0){
			return Review::NoFKey;
		}

		// 入れ物の初期化
		perNail	= QVector<int>(13, 0).toList();
		perNG	= QVector<int>(13, 0).toList();

		// Fキー情報を計上
		for(NGNailList::ConstIterator item=m_NGNails.constBegin(); item!=m_NGNails.constEnd(); item++){
			perNail[Review::FKeyToInt(item->FKey)] += 1;// Fキーに対応した配列をインクリメント
			perNG[Review::FKeyToInt(item->FKey)] += item->NGPointList.count();// 重複分を含む
		}

		// 最大Fキーカウント数のFキーを取得
		// 同数の場合、F[i]のiが小さい方が優先的に選ばれる
		int maxIndex = 0;
		int maxCount = perNail[maxIndex];
		for(int i=1; i<perNail.count()-1; i++){
			if(perNail[i] > maxCount){
				maxCount = perNail[i];
				maxIndex = i;
			}
		}
		// Fキーが１つも付いていない場合はFキーなし
		// いずれかのFキーが１つでも付いていれば、そのFキー属性にする
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

// 表裏の履歴をまとめたデータ
// 同一検査コード(XMLデータのISTの要素EIDの値)の表と裏の履歴情報を保持する
// ロットが更新されると同時に更新される
// 保持する履歴情報はポインタで、実態は別にある
// 
// ReviewPIBaseに保存される
//
class OrganizedHistoryItem
{
public:
	OrganizedHistoryItem(){
		clear();
	};
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
			for(NGNailList::Iterator it=FrontItem->getNGNails().begin(); it!=FrontItem->getNGNails().end(); it++){
				FrontBackNGNailList.append(it);
			}
		}
		if(BackItem!=NULL){
			for(NGNailList::Iterator it=BackItem->getNGNails().begin(); it!=BackItem->getNGNails().end(); it++){
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
	QList<NGNailList::Iterator> FrontBackNGNailList;// イテレータが表→裏の順番で並んでいるリスト
	Review::OrganizedSideType Type;// 表裏所属
	Qt::Key FKey;// Fキー情報
};

typedef QList<OrganizedHistoryItem>		OrganizedHistoryList;
typedef OrganizedHistoryList			*OrganizedHistoryListPtr;
typedef OrganizedHistoryItem			*OrganizedHistoryIndex;
typedef QList<OrganizedHistoryIndex>	OrganizedHistoryIndexList;

// JDTファイルの画像データひとつ分の情報を保持するクラス
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

// 表と裏の読み込んだマスターデータのバッファ
// 便宜上アルゴリズムに保存しておく
// 将来的に複数の表裏構造を使用するため保存できるようにしておく
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