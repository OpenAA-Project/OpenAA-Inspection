#pragma once

#include <QtGui>

#include "ui_TotalNGMapForm.h"
#include "XReviewStructure.h"

// ロット全体の基板に関してNGのXY座標をマスター画像に表示したものを表示する
class TotalNGMap : public QDialog
{
	Q_OBJECT

public:
	TotalNGMap(LayersBase *Base, ReviewPIBase *RBase, QWidget *parent);
	~TotalNGMap();

private:
	typedef QList<QList<int> > _vautMap;

public:
	// 表示形式(標準はCircle(○))
	enum NGDrawShapeType {
		Circle,
		Fill_Circle,
		Triangle,
		Fill_Triangle,
		Rectangle,
		Fill_Rectangle
	};

public:
	class VautNGListItem{
	public:
		VautNGListItem(const int NGCnt=-1, const QRect r=QRect()):m_NGCount(NGCnt),m_rect(r){};
		void setNGCount(int num){ m_NGCount = num; };
		void setRect(const QRect r){ m_rect = r; };

		int NGCount() const { return m_NGCount; };
		QRect rect() const { return m_rect; };

	public:
		bool operator<(const VautNGListItem &other) const { return NGCount()<other.NGCount(); };
		static bool DescendingOrder(const VautNGListItem &item1, const VautNGListItem &item2){ return (item2<item1); };

	private:
		int	m_NGCount;
		QRect m_rect;
	};
	class TableWidgetIntItem : public QTableWidgetItem{
	public:
		TableWidgetIntItem(int i, int type=0):QTableWidgetItem(QString::number(i), type){};
	public:
		virtual bool operator<( const QTableWidgetItem & other ) const{
			int n = text().toInt();
			int o = other.text().toInt();
			return n<o;
		};
	};

public:
	void setNGPoints(const OrganizedHistoryListPtr OrgHistoryListPtr);// 履歴情報を受け取って、NGPosListを更新する.
	void setWholeImage(QList<QImage> &FrontPix, QList<QImage> &BackPix);// 全体画像の更新
	bool isShowEnable() const;
	static bool compair(const QPoint &p1, const QPoint &p2){
		if(p1.x() < p2.x()){
			return true;
		}else if(p1.x() == p2.x() && p1.y() < p2.y()){
			return true;
		}else{
			return false;
		}
	};
	void uniqQPointList(QList<QPoint> &list);

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;// 画像の描画イベント。１：全体画像の表示　２：NG位置の表示
	void drawNGPoints(QPainter &painter, QList<QPoint> &posList, double zoomRate=1.0);

public slots:
	void on_pbClose_clicked(void);

public:
	void setSplitX(int n){ m_splitX = n; };
	int splitX() const { return m_splitX; };

	void setSplitY(int n){ m_splitY = n; };
	int splitY() const { return m_splitY; };

	void setNGDrawColor(const QColor &color){ m_NGDrawColor = color; };
	QColor NGDrawColor(void) const { return m_NGDrawColor; };

	void setNGDrawShape(NGDrawShapeType type){ m_NGDrawShape = type; };
	NGDrawShapeType NGDrawShape(void) const { return m_NGDrawShape; };

	void setNGDrawSize(int size){ m_NGDrawSize = size; };
	int NGDrawSize(void) const { return m_NGDrawSize; };

	void setIgnoreErrorInspect(bool enable){ m_isIgnoreErrorInspect = enable; };
	bool isIgnoreErrorInspect() const { return m_isIgnoreErrorInspect; };

	void setLayersBase(LayersBase *Base){ m_LBase = Base; };
	LayersBase *layersBase(void) const { return m_LBase; };

	void setReviewPIBase(ReviewPIBase *RBase){ m_RBase = RBase; };
	ReviewPIBase *reviewPIBase() const { return m_RBase; };

	inline const QList<QImage> &image(Review::SideType side) const { return ((isFront(side) ? m_FrontImageList : m_BackImageList)); };
	inline QList<QImage> &image(Review::SideType side){ return ((isFront(side) ? m_FrontImageList : m_BackImageList)); };

	inline const QImage &image(Review::SideType side, int phase) const{ return image(side)[phase]; };
	inline QImage &image(Review::SideType side, int phase){ return image(side)[phase]; };

	void setImage(Review::SideType side, const QList<QImage> &images){
		Review::isFront(side) ? m_FrontImageList = images : m_BackImageList = images;
	};
	void setImage(Review::SideType side, int phase, const QImage &image){
		Review::isFront(side) ? m_FrontImageList[phase] = image : m_BackImageList[phase] = image;
	};
	void setImage(const QList<QImage> &FrontImages, const QList<QImage> &BackImages){
		setImage(Review::Front, FrontImages);
		setImage(Review::Back, BackImages);
	};
	
	void clearImage(Review::SideType side){
		((isFront(side) ? m_FrontImageList.clear() : m_BackImageList.clear()));
	};
	void clearImage(){
		m_FrontImageList.clear(); m_BackImageList.clear();
	};
	void clearImage(Review::SideType side, int phase){
		((isFront(side) ? m_FrontImageList[phase] = QImage() : m_BackImageList[phase] = QImage()));
	};
	void clearImage(int phase){
		m_FrontImageList[phase] = QImage(); m_BackImageList[phase] = QImage();
	};

	QList<QList<QPoint> > getPointList(Review::SideType side){
		return (isFront(side) ? m_FrontNGPosList : m_BackNGPosList); 
	};
	QList<QPoint> getPointList(Review::SideType side, int phase){
		return (isFront(side) ? m_FrontNGPosList[phase] : m_BackNGPosList[phase]);
	};
	void setPointList(Review::SideType side, QList<QList<QPoint> > points){
		isFront(side) ? m_FrontNGPosList = points : m_BackNGPosList = points;
	};
	void setPointList(Review::SideType side, int phase, QList<QPoint> points){
		isFront(side) ? m_FrontNGPosList[phase] = points : m_BackNGPosList[phase] = points;
	};

	void clearPointList(){
		m_FrontNGPosList.clear(); m_BackNGPosList.clear();
	};
	void clearPointList(Review::SideType side){
		isFront(side) ? m_FrontNGPosList.clear() : m_BackNGPosList.clear();
	};
	void clearPointList(Review::SideType side, int phase){
		isFront(side) ? m_FrontNGPosList[phase].clear() : m_BackNGPosList[phase].clear();
	};

	Review::SideType currentSide() const { return (ui.cbSide->currentIndex()==0 ? Review::Front : Review::Back); };
	int phaseCount(Review::SideType side) const { return image(side).count(); };
	int currentPhase() const { return ui.cbPhase->currentIndex(); };
	const _vautMap &currentVautMap() const {
		Review::SideType side = currentSide();
		int phase = currentPhase();

		if(side==Review::Front){
			return m_FrontVautMapList[phase];
		}else{
			return m_BackVautMapList[phase];
		}
	};
	
	_vautMap &currentVautMap(){
		Review::SideType side = currentSide();
		int phase = currentPhase();

		if(side==Review::Front){
			return m_FrontVautMapList[phase];
		}else{
			return m_BackVautMapList[phase];
		}
	};

	QSize viewAreaSize() const { return ui.gvImageView->viewport()->size(); };

	Ui::TotalNGMapClass *getUi(){ return &ui; };

	void updateData();
	void updateVautMapList();
	void updateVautTable();
	void createVautMap(int phaseNumb, int XCount, int YCount){
		m_FrontVautMapList = QVector<QList<QList<int> > >(phaseNumb, QVector<QList<int> >(YCount, QVector<int>(XCount, 0).toList()).toList()).toList();
		m_BackVautMapList = m_FrontVautMapList;
	};
	void updateImage();
	QImage addNGPoint(Review::SideType side, int phase, const QImage &image, const QList<QPoint> &pointList) const;

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void showEvent(QShowEvent *event)		override;
	virtual	void closeEvent(QCloseEvent *event)		override;

signals:
	void resized(QSize newSize, QSize oldSize);

public slots:
	void setCurrentPhase(int phase){ ui.cbPhase->setCurrentIndex(phase); };

private slots:
	void on_cbPhase_currentIndexChanged(int index);
	void on_cbSide_currentIndexChanged(int index);
	void on_twVautTable_cellClicked(int row, int column);

//private:
//	void _setStretchImageWidgetList(Review::SideType side, const QList<StretchImageWidget *> list){
//		isFront(side) ? m_FrontImageWidgetList = list : m_BackImageWidgetList = list;
//	};
//	void _setStretchImageWidget(Review::SideType side, int phase, StretchImageWidget * widget){
//		isFront(side) ? m_FrontImageWidgetList[phase] = widget : m_BackImageWidgetList[phase] = widget;
//	};
//
//	const QList<StretchImageWidget *> _stretchImageWidgetList(Review::SideType side) const {
//		return isFront(side) ? m_FrontImageWidgetList : m_BackImageWidgetList;
//	};
//	const StretchImageWidget *_stretchImageWidget(Review::SideType side, int phase) const {
//		return isFront(side) ? m_FrontImageWidgetList[phase] : m_BackImageWidgetList[phase];
//	};
//
//	int _widgetCount(Review::SideType side) const {
//		return isFront(side) ? m_FrontImageWidgetList.count() : m_BackImageWidgetList.count();
//	}

private:
	Ui::TotalNGMapClass ui;// この中のQFrameのインスタンスMainCanvasに下のQPixmapを張り付けて画像を表示し、保持しているNGPosListがもつNG座標を描き込んで表示する
	
	QList<QImage> m_FrontImageList;	// 表の全体画像
	QList<QImage> m_BackImageList;	// 裏の全体画像

	//QList<StretchImageWidget *> m_FrontImageWidgetList;
	//QList<StretchImageWidget *> m_BackImageWidgetList;

	QList<QList<QPoint> > m_FrontNGPosList;// NGの位置のリスト(順番は無関係)
	QList<QList<QPoint> > m_BackNGPosList;

	QList<_vautMap> m_FrontVautMapList;
	QList<_vautMap> m_BackVautMapList;
	
	int m_splitX;	// X分割数
	int m_splitY;	// Y分割数
	QColor m_NGDrawColor;		// 表示するNGの色
	NGDrawShapeType m_NGDrawShape;	// NGの表示形式
	int m_NGDrawSize;
	QList<QList<int> > m_vautCountList;
	bool m_isIgnoreErrorInspect;
	QPoint m_targetPoint;

	LayersBase *m_LBase;
	ReviewPIBase *m_RBase;
	QGraphicsScene *m_viewScene;
	QGraphicsPixmapItem *m_viewItem;
};