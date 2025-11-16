#ifndef XREVIEW_COMMON_H_
#define XREVIEW_COMMON_H_

#include <QString>
#include "XDateTime.h"
#include <QPushButton>
#include <QMessageBox>

#include "XAlgorithmLibNGType.h"

namespace Review{

class StaticString
{
private:
	StaticString();

public:
	class InspectionResult{
	private:
		InspectionResult(){};
	public:
		static const QString OK;
		static const QString NG;
		static const QString MaxError;
		static const QString TimeOut;
	};

};

enum SideType{
	Front,
	Back,
	NoSide
};

template<typename T>
inline T switchSide(Review::SideType side, const T &front, const T &back, const T noside){
	switch(side){
	case Review::Front:
		return front;
		break;
	case Review::Back:
		return back;
		break;
	default:
		return noside;
		break;
	}
	return noside;
};

template<typename T>
inline T switchSide(Review::SideType side, const T &front, const T &back){
	return switchSide(side, front, back, T());
};

template<typename T>
inline void switchSideSetValue(Review::SideType side, T &front, T &back, const T &value){
	if(side==Review::Front){
		front = value;
	}else if(side==Review::Back){
		back = value;
	}else{
		// none
	}
};

enum OrganizedSideType{
	FrontOnly,
	BackOnly,
	Both,
	None
};

enum NearPosType{
	PreviousPos,
	CurrentPos,
	NextPos
};

// ソートパラメータ
// HistoryListのソート順指定
enum OrderOfSortHistory{
	_Order_InspectionIDGreater
	,_Order_InspectionIDLesser
	,_Order_InspectionTimeGreater
	,_Order_InspectionTimeLesser
	,_Order_NGCountGreater
	,_Order_NGCountLesser
	,_Order_NGCount_OnlyFrontGreater
	,_Order_NGCount_OnlyFrontLesser
	,_Order_NGCount_OnlyBackGreater
	,_Order_NGCount_OnlyBackLesser
};

// NGのソート順指定(XY座標)
enum OrderOfSortNG{
	_Order_YLesser
	,_Order_YGreater
	,_Order_XLesser
	,_Order_XGreater
	,_Order_LibTypeLesser
	,_Order_LibTypeGreater
	,_Order_NGCauseLesser
	,_Order_NGCauseGreater
	,_Order_Area
};

// 基板の全体画像の表示における基準位置
enum OrginPosition
{
	_Org_TopLeft
	,_Org_BottomLeft
	,_Org_TopRight
	,_Org_BottomRight
};

enum RefType {
	Ref_Index,
	Ref_Instance
};

enum Direction{
	Next,
	Previous
};

enum ListLocate{
	First,// 先頭に設定
	End,// 最後尾に設定
	Manual// 途中に設定
};

enum FKey{
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	NoFKey
};

enum Rotate
{
	Rotate_0=0,
	Rotate_90=1,
	Rotate_180=2,
	Rotate_270=3
};

enum AlignmentNo{
	Alignment_First=0,
	Alignment_Second=1,
	Alignment_Third=2
};
enum AlignmentSide{
	AlignmentSide_Inspection=0,
	AlignmentSide_VRSMachine=1
};

int toIntFromRotate(Rotate rotate);
Review::Rotate toRotateFromInt(int rotate);
Qt::Corner rotatedRectCorner(Qt::Corner originalCorner, Rotate rotation, bool counterclockwise=true);

QPoint corner(const QRect &rect, Qt::Corner c);
QPointF corner(const QRectF &rect, Qt::Corner c);

QRect setCorner(const QRect &rect, const QPoint &pos, Qt::Corner c);
QRectF setCorner(const QRectF &rect, const QPointF &pos, Qt::Corner c);

QRect moveCorner(const QRect &rect, const QPoint &pos, Qt::Corner c);
QRectF moveCorner(const QRectF &rect, const QPointF &pos, Qt::Corner c);

QRect rotateRect(const QRect &r, qreal angle, Qt::Corner keepCorner=Qt::Corner::TopLeftCorner);
QRectF rotateRect(const QRectF &r, qreal angle, Qt::Corner keepCorner=Qt::Corner::TopLeftCorner);
QRect rotateRectRaw(const QRect &r, qreal angle);
QRectF rotateRectRaw(const QRectF &r, qreal angle);
QPoint rotatePoint(const QPoint &p, qreal angle, const QPoint &center=QPoint(0,0));
QPointF rotatePoint(const QPointF &p, qreal angle, const QPoint &center=QPoint(0,0));
QSize rotateSize(const QSize &size, qreal angle);
QSizeF rotateSize(const QSizeF &size, qreal angle);
QImage rotateImage(const QImage &image, qreal angle, const QColor &backFillColor=QColor());

QRect rotateRectOnRect(const QRect &pieceRect, const QPoint &originPoint, qreal angle, Qt::Corner shareCorner=Qt::Corner::TopLeftCorner);
QRect rotateRectRoundCneter(const QRect &r, qreal angle);
QRectF rotateRectRoundCneter(const QRectF &r, qreal angle);

QRect boundRect(const QPoint &p1, const QPoint &p2);
QRectF boundRect(const QPointF &p1, const QPointF &p2);
QRect boundRect(const QList<QPoint> &pList);
QRectF boundRect(const QList<QPointF> &pList);

enum VRSAlignmentType
{
	VRSAlingmentWholeImage,
	VRSAlingmentEachPage
};

typedef enum {
	INDEX_FIRST=0,
	INDEX_SECOND=1,
	INDEX_THIRD=2
} THREE_INDEX;

template<typename T>
class ThreeValue
{
public:
	ThreeValue(){};
	ThreeValue(const T &val){ setValue(val, val, val); };

public:
	inline int count() const { return 3; };
	inline int size() const { return count(); };
	
	T &first(){ return _data[0]; };
	T &second(){ return _data[1]; };
	T &third(){ return _data[2]; };

	const T &first() const { return _data[0]; };
	const T &second() const { return _data[1]; };
	const T &third() const { return _data[2]; };

	void setFirst(T value){ _data[0] = value; };
	void setSecond(T value){ _data[1] = value; };
	void setThird(T value){ _data[2] = value; };

	T value(THREE_INDEX index) const {
		switch(index){
		case INDEX_FIRST:
			return first();
			break;
		case INDEX_SECOND:
			return second();
			break;
		case INDEX_THIRD:
			return third();
			break;
		default:
			Q_ASSERT("Review::ThreeValueIndexASSERT");
			return T();
			break;
		}
	};

	void setValue(THREE_INDEX index, T value){
		switch(index){
		case INDEX_FIRST:
			setFirst(value);
			break;
		case INDEX_SECOND:
			setSecond(value);
			break;
		case INDEX_THIRD:
			setThird(value);
			break;
		default:
			break;
		}
	};
	void setValue(T first_val, T second_val, T third_val){
		setFirst(first_val);
		setSecond(second_val);
		setThird(third_val);
	};

public:
	inline T &operator[](int i){ return _data[i]; };
	inline T operator[](int i) const { return _data[i]; };

private:
	T _data[3];
};

template<typename T1, typename T2, typename T3>
class ThreeMultitypeValue
{
public:
	ThreeMultitypeValue(){};
	ThreeMultitypeValue(const T1 &val1, const T2 &val2, const T3 &val3):_data_1(val1),_data_2(val2),_data_3(val3){};

public:

	T1 &first(){ return _data_1; };
	T2 &second(){ return _data_2; };
	T3 &third(){ return _data_3; };

	const T1 &first() const { return _data_1; };
	const T2 &second() const { return _data_2; };
	const T3 &third() const { return _data_3; };

	void setFirst(T1 value){ _data_1 = value; };
	void setSecond(T2 value){ _data_2 = value; };
	void setThird(T3 value){ _data_3 = value; };

	void setValue(T1 first_val, T2 second_val, T3 third_val){
		setFirst(first_val);
		setSecond(second_val);
		setThird(third_val);
	};

private:
	T1 _data_1;
	T2 _data_2;
	T3 _data_3;
};

template<typename T>
class DeleteAtEnd{
public:
	DeleteAtEnd(T *ptr):m_ptr(ptr){};
	~DeleteAtEnd(){ delete m_ptr; };
private:
	T *m_ptr;
};

template<class T>
bool isBetween(const T &min, const T &value, const T &max){
	if(min<=value && value<=max){
		return true;
	}else{
		return false;
	}
};

template<class T>
bool isIndexEnableList(int index, const QList<T> &list){
	return Review::isBetween(0, index, list.count()-1);
};

template<class T>
bool isIndexEnableVector(int index, const QVector<T> &vect){
	return Review::isBetween(0, index, vect.count()-1);
};

template<class T>
void increase(int max, QList<T> &list){
	while(list.count()<max){
		list << T();
	}
};

template<class T>
void increase(int root_max, int child_max, QList<QList<T> > &list, bool increase_all_child=true)
{
	increase(root_max, list);
	if(increase_all_child==true){
		for(int i=0; i<list.count(); i++){
			increase(child_max, list[i]);
		}
	}else{
		for(int i=0; i<root_max; i++){
			increase(child_max, list[i]);
		}
	}
};

template<class T>
void resize(int size, QList<T> &list){
	QList<T> buf;
	int count = 0;
	for(; count<size && count<list.count(); count++){
		buf << list[count];
	}
	list = buf;
	for(; count<size; count++){
		list << T();
	}
};

template<class T>
QList<T> toList(const T &item){
	QList<T> list;
	list.append(item);
	return list;
};

template<class T>
QList<QList<T> > createList(quint32 first_dim, quint32 second_dim){
	QList<QList<T> > list = QVector<QList<T> >(first_dim).toList();
	for(int i=0; i<list.count(); i++){
		list[i] = QVector<T>(second_dim).toList();
	}
	return list;
};

QString makeMasterImageName(int MasterCode, int MachineID, int phase, int page, const QString &path);

class MasterImageFileData{
public:
	QString fileName;
	int MasterCode;
	int MachineID;
	int phase;
	int page;

public:
	bool operator<(const MasterImageFileData &other) const {
		do{
			if(MasterCode<other.MachineID)break;
			if(phase<other.phase)break;
			if(page<other.page)break;

			return false;

		}while(false);
		return true;
	};
	bool operator>(const MasterImageFileData &other) const {
		return !(*this<other);
	};
};

bool isFront(Review::SideType side);
bool isBack(Review::SideType side);

QString toString(Review::SideType side);

bool isArrowKey(int key);

// デフォルトのFキーカラー
QColor getDefaultFKeyColor(Review::FKey key);

// デフォルトFカラーリスト
QList<QColor> getDefaultFKeyColorList();

bool isFKey(Qt::Key key);

Review::FKey convertFKeyQtToReview(Qt::Key key);

// Review::FKeyをint型に変換する。F1==0, F2==1, ... , F12==11, Fキーなし==12, その他==-1が返る
int FKeyToInt(Review::FKey key);

// int型をReview::FKeyへ変換する。数値0～12がF1～F12,NoFKeyの同順となる。範囲から外れた場合はNoFKeyが返る
Review::FKey IntToFKey(int ref);

// マスターコード、マシンID、XMLのファイル名からXMLサーバーの検索ディレクトリからのファイルパスを作成する
QString makeLotFileName(int MasterCode, int MachineID, QString FileName);

// XMLファイルに記述されている日時フォーマットのQStringからXDateTimeオブジェクトを再構成する
XDateTime makeLotISTDateTime(QString format);

Review::SideType ShowMessageFrontOrBack(QWidget *parent=NULL);

QList<QPair<QString, QString> > getSaveNGImageFormatMacroList();

void DrawNGShapeToPainter(QPainter *painter, QColor color, LibNGTypeItem::NGShapeType shape, QPoint center, int round);

// all input QImage is Format_Indexed8, return is Format_RGB32
QImage toRGBImage(const QImage &rImage, const QImage &gImage=QImage(), const QImage &bImage=QImage(), bool monoFlag=false);

template<typename T1, typename T2>
bool compPairFirstLesser(const QPair<T1, T2> &item1, const QPair<T1, T2> &item2){
	return item1.first < item2.first;
};

template<typename T1, typename T2>
bool compPairFirstGreater(const QPair<T1, T2> &item1, const QPair<T1, T2> &item2){
	return !compPairFirstLesser(item1, item2);
};

template<typename T>
QList<T> sortByPriority(const QList<int> &priorityList, const QList<T> &itemList)
{
	QList<QPair<int, T> > list;
	for(int i=0; i<priorityList.count() && i<itemList.count(); i++){
		list << QPair<int, T>(priorityList[i], itemList[i]);
	}

	qStableSort(list.begin(), list.end(), compPairFirstLesser<int, T>);

	QList<T> retList;
	for(int i=0; i<list.count(); i++){
		retList << list.at(i).second;
	}

	return retList;
};

}

#endif