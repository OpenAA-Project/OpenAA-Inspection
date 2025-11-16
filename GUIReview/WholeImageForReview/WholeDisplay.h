#pragma once

#include "mtGraphicUnit.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include <QHBoxLayout>
#include <QLabel>

class	ReviewPIBase;

class WholeDisplay_impl : public mtGraphicUnit
{
	Q_OBJECT

	ReviewPIBase	*PBase;
public:
	WholeDisplay_impl(ReviewPIBase *p, Review::SideType side=Review::Front, int phase=-1, QWidget *parent=0);
	~WholeDisplay_impl();

public:
	void clearWholeImage(bool redraw=false){ setWholeImage(QImage()); if(redraw)updateImage(); };
	void setWholeImage(const QImage &image, const QSize *orgSize=NULL, bool redraw=false);
	void setNGNailPosList(const HistoryItem &history, bool redraw=false);
	void clearNGNailPosList(bool redraw=false);
	void updateImage();
	bool hasImage() const { return ((m_WholeImage.isNull()==false) ? true : false); };

	QPoint getOutlineOffset(int page){
		QList<QPoint> pList = getOutlineOffsetList();
		if(Review::isIndexEnable(page, pList)==true){
			return pList[page];
		}else{
			return QPoint(0,0);
		}
	};
	void dragStart(void){ setDragActive(true); };
	void dragEnd(void){ setDragActive(false); };
	QRect getDragRect(const QPoint &p) const {
		return Review::boundRect(getDragTopLeftPos(), p);
	};
	QRect getDragOrgRect(const QRect &rect){
		QRect nrrect = getDragNoRotateRect(rect);
		QRect orgRect = nrrect;
		qreal zoom = zoomRate();

		orgRect.moveTopLeft( orgRect.topLeft() / zoom );
		orgRect.setSize( orgRect.size() / zoom );

		return orgRect;
	};
	QSize imageSize(bool rotation=false) const {
		QSize ret;
		if(getWholeImageView().isNull()==true){
			ret = getWholeImage().size();
		}else{
			ret = getWholeImageView().size();
		}
		if(rotation==true){
			ret = Review::rotateSize(ret, rotate());
		}
		return ret;
	};
	QRect getDragNoRotateRect(const QRect &rect){
		Review::Rotate rot = Review::toRotateFromInt(rotate());
		QRect rrect;
		QSize rrsize = Review::rotateRect(rect, rotate()).size();
		qreal zoom = zoomRate();
		QPoint topLeft;

		QSize imgSize = imageSize(true);

		QSize csize = GetCanvasSize();

		switch(rot){
		case Review::Rotate::Rotate_0:
			topLeft = rect.topLeft();
			break;
		case Review::Rotate::Rotate_90:
			topLeft = QPoint(qAbs(imgSize.height() - rect.bottom()), rect.left());
			break;
		case Review::Rotate::Rotate_180:
			topLeft = QPoint(qAbs(imgSize.width() - rect.right()), qAbs(imgSize.height() - rect.bottom()));
			break;
		case Review::Rotate::Rotate_270:
			topLeft = QPoint(rect.top(), qAbs(imgSize.width() - rect.right()));
			break;
		default:
			return QRect();
			break;
		}

		rrect.setTopLeft(topLeft);
		rrect.setSize( rrsize );

		return rrect;
	};
	QPoint rotatePoint(const QPoint &canvasP){
		Review::Rotate rot = Review::toRotateFromInt(rotate());

		QRectF rect(QPointF(0,0), QPointF(canvasP));
		QRectF rrect = Review::rotateRect(rect, rotate());
		rrect.moveTopLeft(QPointF(0,0));

		switch(rot){
		case Review::Rotate::Rotate_0:
			break;
		case Review::Rotate::Rotate_90:
			break;
		case Review::Rotate::Rotate_180:
			break;
		case Review::Rotate::Rotate_270:
			break;
		default:
			break;
		}

		return rrect.bottomRight().toPoint();
	};

	QPoint rotateOrgPoint(const QPoint &canvasP){ return rotatePoint(canvasP) / zoomRate(); };

	QSize getImageViewSize(void){ return getWholeImage().size(); };

public:
	void setNGSingDefaultColor(QColor color, bool redraw=false){ m_NGSingDefaultColor = color; if(redraw)updateImage(); };
	void setNGImageSize(QSize size){ m_NGImageSize = size; };
	void setNGSingCurrentColor(QColor color, bool redraw=false){ m_NGSingCurrentColor = color; if(redraw)updateImage(); };
	HistoryItem getHistory() const { return m_History; };
	QColor getNGSingDefaultColor() const { return m_NGSingDefaultColor; };
	QColor getNGSingCurrentColor() const { return m_NGSingCurrentColor; };
	QSize getNGImageSize(){ return m_NGImageSize; };
	void setPCEArea(PCEList list, bool redraw=false){ m_PCEList = list; if(redraw)updateImage(); };
	PCEList getPCEList() const { return m_PCEList; };
	void setCurrentIndex(int index, bool redraw=false)
	{ 
			m_currentIndex = index;
			if(m_currentIndex<0){ 
				m_currentIndex=-1; 
			} 
			if(redraw)
				updateImage();
	}
	void removeCurrentIndex(bool redraw=false){ m_currentIndex = -1; if(redraw)updateImage(); };
	void setCurrentNGRectVisible(bool visible, bool redraw=false){ m_currentNGRectVisible = visible; if(redraw)updateImage(); };
	void setNGNailSelectIndex(int index){ m_NGNailSelectIndex = index; };
	int getNGNailSelectIndex() const { return m_NGNailSelectIndex; };
	bool isNGNailSelected() const { return (m_NGNailSelectIndex!=-1); };
	void clearNGNailSelected(){ m_NGNailSelectIndex = -1; };
	QSize getWholeImageOrgSize() const { return m_WholeImageOrgSize; };
	void setWholeImageOrgSize(const QSize &size){ m_WholeImageOrgSize = size; };
	void setCurrentNGCrossView(bool view, bool redraw=false){ if(m_currentNGCrossView != view){m_currentNGCrossView = view; if(redraw)updateImage(); } };
	void setNGPointView(bool view, bool redraw=false){ if(m_NGPointView != view){m_NGPointView = view; if(redraw)updateImage(); } };
	void setCurrentNGRectOnlyView(bool view, bool redraw=false){ if(m_currentNGRectOnlyView != view){ m_currentNGRectOnlyView = view; if(redraw)updateImage(); } };
	bool getCurrentNGCrossView() const { return m_currentNGCrossView; };
	bool getNGPointView() const { return m_NGPointView; };
	bool getCurrentNGNailOnlyView() const { return m_currentNGRectOnlyView; };
	void setOutlineOffset(const QList<QPoint> &outlines){ m_OutlineOffset = outlines; };
	QList<QPoint> getOutlineOffsetList() const { return m_OutlineOffset; };
	void setDragActive(bool flag){ m_DragIsActive = flag; };
	bool isDragActive(void) const { return m_DragIsActive; };
	void setDragTopLeftPos(const QPoint &p){ m_DragTopLeftPos = p; };
	QPoint getDragTopLeftPos(void) const { return m_DragTopLeftPos; };
	void setDragCurrentMousePos(const QPoint &p){ m_DragCurrentMousePos = p; };
	QPoint getDragCurrentMousePos(void) const { return m_DragCurrentMousePos; };
	bool isCurrentNGViewEnable(void) const { return m_currentNGRectVisible; };
	void setCurrentNGViewEnable(bool enable){ m_currentNGRectVisible = enable; };
	void setHistory(const HistoryItem &history){ m_History = history; };
	HistoryItem &getHistory(void){ return m_History; };
	void setPhase(int phase){ m_phase = phase; };
	int getPhase(void) const { return m_phase; };
	int getCurrentIndex(void) const { return m_currentIndex; };
	void setSide(Review::SideType side){ m_side = side; };
	Review::SideType getSide(void) const { return m_side; };
	qreal zoomRate(){
		qreal ret;
		if(getCurrentViewRect().isEmpty()==true){
			// 全体画像
			QSize size = getWholeImageOrgSize();
			QRect rect(QPoint(0,0), size);// 全体画像の矩形化
			QRect rrect = Review::rotateRect(rect, rotate());// 回転
			QSize rsize = rrect.size();
			rsize.scale(GetCanvas()->size(), Qt::KeepAspectRatio);// 回転したサイズでキャンバスサイズへ調整
			QRect srrect = QRect(QPoint(0,0), rsize);
			QSize ssrsize = Review::rotateRect(srrect, -rotate()).size();// 逆回転して回転なしの状態に戻す

			ret = ssrsize.width() / (qreal)getWholeImageOrgSize().width();
		}else{
			QSize size = getCurrentViewRect().size();
			QRect rect(QPoint(0,0), size);// 全体画像の矩形化
			QRect rrect = Review::rotateRect(rect, rotate());// 回転
			QSize rsize = rrect.size();
			rsize.scale(GetCanvas()->size(), Qt::KeepAspectRatio);// 回転したサイズでキャンバスサイズへ調整
			QRect srrect = QRect(QPoint(0,0), rsize);
			QSize ssrsize = Review::rotateRect(srrect, -rotate()).size();// 逆回転して回転なしの状態に戻す

			ret = ssrsize.width() / (qreal)getCurrentViewRect().width();
		}
		return ret;
	};

protected:
	virtual	void mousePressEvent(QMouseEvent *event)	override;
	virtual	void mouseMoveEvent(QMouseEvent *event)		override;
	virtual	void mouseReleaseEvent(QMouseEvent *event)	override;
	virtual	void resizeEvent(QResizeEvent *event)		override;

public slots:
	void SlotMouseRDown(int x, int y);
	void SlotMouseMove(int x, int y);
	void SlotMouseLDown(int x, int y);

signals:
	void SignalSelectNG(int phase, int index);
	void SignalResize();
	void SignalReqWholePicPiece(Review::SideType side, int phase, const QRect &rect);
	void SignalReqWholePicOrg(Review::SideType side, int phase);

public:
	QImage getWholeImage(void) const { return m_WholeImage; };
	QImage getWholeImageView(void) const { return m_WholeImageView; };
	bool hasWholeImage() const { return !m_WholeImageView.isNull(); };
	bool hasWholeImageView() const { return !m_WholeImageView.isNull(); };
	QRect getCurrentViewRect(void) const { return m_currentViewRect; };
	void setWholeImageView(const QImage &image){ m_WholeImageView = image; };
	void setCurrentViewRectTopLeft(const QPoint &p){ setCurrentViewRect( QRect(p.x(), p.y(), getCurrentViewRect().width(), getCurrentViewRect().height() ) ); };
	void setCurrentViewRect(const QRect &rect){ m_currentViewRect = rect; };
	void setPCENameViewThreshold(double rate){ m_PCENameViewThreshold = rate; };
	double getPCENameViewThreshold() const { return m_PCENameViewThreshold; };
	void setRotate(int rotate){ m_Rotate = rotate; };
	int rotate() const { return m_Rotate; };

private:
	bool			m_DragIsActive;
	QPoint			m_DragTopLeftPos;
	QPoint			m_DragCurrentMousePos;
	HistoryItem		m_History;// 履歴データ
	QList<QPoint>	m_OutlineOffset;// アウトライン情報
	int				m_NGNailSelectIndex;// 現在選択されているNGNailインデックス
	QColor			m_NGSingDefaultColor;// NG表示のデフォルトカラー
	QColor			m_NGSingCurrentColor;// 選択NG表示のカラー
	QImage			m_WholeImage;// 全体画像
	QImage			m_WholeImageView;// 全体画像の表示部分
	QSize			m_NGImageSize;// NG画像のサイズ
	int				m_currentIndex;// 現在選択中のNGのインデックス
	bool			m_currentNGRectVisible;// 現在選択中のNGの矩形描画フラグ
	bool			m_currentNGCrossView;// 現在選択中のNGを中心とした十字を表示するフラグ
	bool			m_NGPointView;// NGを点で表示するフラグ
	bool			m_currentNGRectOnlyView;// 現在選択中のNGのみ矩形描画フラグ
	QSize			m_WholeImageOrgSize;// 元画像の全体サイズ
	int				m_phase;// フェイズ番号
	Review::SideType m_side;// サイド
	QRect			m_currentViewRect;// 全体サイズのうち、現在表示しているサイズ
	PCEList			m_PCEList;
	double			m_PCENameViewThreshold;
	int				m_Rotate;// 画像の描画回転度(deg)
};

class WholeDisplay : public QWidget
{
	Q_OBJECT

public:
	WholeDisplay(ReviewPIBase *p ,Review::SideType side, int phase, QWidget *parent=NULL)
		:QWidget(parent),m_mainLayout(new QVBoxLayout),m_infoLabel(new QLabel),m_display(new WholeDisplay_impl(p,side, phase, this))
	{
		// 自動レイアウトにおける伸縮設定
		m_infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		m_display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		// 枠の表示設定
		m_infoLabel->setFrameShape(QFrame::Shape::Box);
		m_infoLabel->setFrameShadow(QFrame::Shadow::Plain);

		// 文字列表示アライメント設定
		m_infoLabel->setAlignment(Qt::AlignCenter);

		// レイアウトに追加
		m_mainLayout->addWidget(m_infoLabel);
		m_mainLayout->addWidget(m_display);
		
		setLayout(m_mainLayout);

		//connect(m_display, SIGNAL(SignalSelectNG(int)), this, SIGNAL(SignalSelectNG(int)));
	};

public:
	void setInfoString(QString str){ m_infoLabel->setText(str); };
	WholeDisplay_impl *getDisplay(){ return m_display; };

signals:
	void SignalSelectNG(int index);

private:
	QVBoxLayout *m_mainLayout;
	QLabel *m_infoLabel;
	WholeDisplay_impl *m_display;
};