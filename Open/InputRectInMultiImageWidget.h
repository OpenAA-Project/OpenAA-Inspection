#pragma once

#include <QWidget>

class InputRectInMultiImageWidget : public QWidget
{
	Q_OBJECT

public:
	InputRectInMultiImageWidget(QWidget *parent=NULL);

public:
	typedef enum {
		ModeDefault,// This mode do not anything
		ModeShiftImage,// Image can shift moving by drag.
		ModeMakeRect// User can create rect on image by two left-click of mouse.
	} MouseDragMode;

	typedef enum {
		DragIsNone,
		DragIsNow,
		DragIsEnd
	} DragState;

protected:
	virtual	void paintEvent ( QPaintEvent * event )		override;
	virtual	void mousePressEvent(QMouseEvent *)			override;
	virtual	void mouseReleaseEvent(QMouseEvent *)		override;
	virtual	void mouseMoveEvent(QMouseEvent *)			override;
	virtual	void mouseDoubleClickEvent(QMouseEvent *)	override;
	virtual	void wheelEvent(QWheelEvent *)				override;

private:
	void paintEvent_ModeDefault(QPaintEvent *, QPainter &);
	void paintEvent_ModeMakeRect(QPaintEvent *, QPainter &);
	void paintEvent_ModeShiftImage(QPaintEvent *, QPainter &);

	void mousePressEvent_ModeDefault(QMouseEvent *);
	void mousePressEvent_ModeMakeRect(QMouseEvent *);
	void mousePressEvent_ModeShiftImage(QMouseEvent *);
	
	void mouseReleaseEvent_ModeDefault(QMouseEvent *);
	void mouseReleaseEvent_ModeMakeRect(QMouseEvent *);
	void mouseReleaseEvent_ModeShiftImage(QMouseEvent *);
	
	void mouseMoveEvent_ModeDefault(QMouseEvent *);
	void mouseMoveEvent_ModeMakeRect(QMouseEvent *);
	void mouseMoveEvent_ModeShiftImage(QMouseEvent *);
	
	void mouseDoubleClickEvent_ModeDefault(QMouseEvent *);
	void mouseDoubleClickEvent_ModeMakeRect(QMouseEvent *);
	void mouseDoubleClickEvent_ModeShiftImage(QMouseEvent *);
	
	void wheelEvent_ModeDefault(QWheelEvent *);
	void wheelEvent_ModeMakeRect(QWheelEvent *);
	void wheelEvent_ModeShiftImage(QWheelEvent *);

public:
	void setImageList(const QList<QImage> &images, const QList<QPoint> &outlines);
	void setTopLeft(const QPoint &topLeft);
	bool setZoomStep(qint32 step);
	void setZoomStepLimit(quint32 stepLimit);
	void setZoomStepDefault(qint32 step){ m_zoomStepDefault = step; };
	void setMouseDragMode(MouseDragMode mode);
	void setDragState(DragState nowDrag);
	void setDragStartPosition(const QPoint &position);
	void setDragCurrentPosition(const QPoint &position);
	void calcResultRect();// active under the mode is DragIsEnd and at soon.
	void clearResultRect();
	bool zoomStepIn();
	bool zoomStepOut();
	void setFirstExpand(bool enable){ m_firstExpand = enable; };

	const QList<QImage> &imageList() const { return m_imageList; };
	int imageCount() const { return m_imageList.count(); };
	const QImage &image(int i) const { return imageList()[i]; };
	QList<QPoint> outlineList() const { return m_outlineList; };
	QPoint outline(int i) const { return m_outlineList[i]; };
	QPoint topLeft() const { return m_topLeft; };
	qint32 zoomStep() const { return m_zoomStep; };
	quint32 zoomStepLimit() const { return m_zoomStepLimit; };
	qint32 zoomStepDefault() const { return m_zoomStepDefault; };
	MouseDragMode mouseDragMode() const { return m_mouseDragMode; };
	DragState dragState() const { return m_dragging; };
	QPoint dragStartPosition() const { return m_dragStartPosision; };
	QPoint dragCurrentPosition() const { return m_dragCurrentPosition; };
	QRect resultRect() const { return m_resultRect; };
	bool isRectEnable() const { return resultRect().isValid(); };
	qreal resultZoomRate() const { return m_resultZoomRate; };
	
	QPoint topLeftReal() const { return topLeft()/zoomRate(); };
	QPoint dragStartPositionReal() const { return dragStartPosition()/zoomRate(); };
	QPoint dragCurrentPositionReal() const { return dragCurrentPosition()/zoomRate(); };
	QRect resultRectReal() const {
		QRect ret = resultRect();
		ret.moveTopLeft( ret.topLeft()*resultZoomRate() );
		ret.setWidth( ret.width()*resultZoomRate() );
		ret.setHeight( ret.height()*resultZoomRate() );
		return ret;
	};

	void setTopPage(quint32 page){ if(m_topPage!=page){ m_topPage = page; update(); }; };
	quint32 topPage() const { return m_topPage; };
	bool isTopPageEnable() { return (topPage()>=0 && topPage()<imageList().count()); };

public:
	void setResultRect(const QRect &rect);
	void setResultZoom(qreal zoom);

private:
	void paintImage(QPainter &painter, const QPoint &imageZoomedTopLeft);

signals:
	void rectCreated(QRect rect);

public:
	qreal zoomRate() const;
	QRect createRect(const QPoint &cooner1, const QPoint &cooner2);
	qreal stepRate() const { return 2.0; };

private:
	QList<QImage> m_imageList;// image and outline
	QList<QPoint> m_outlineList;

	QPoint m_topLeft;
	qint32 m_zoomStep;
	quint32 m_zoomStepLimit;
	qint32 m_zoomStepDefault;
	MouseDragMode m_mouseDragMode;
	DragState m_dragging;
	QPoint m_dragStartPosision;
	QPoint m_dragCurrentPosition;
	QRect m_resultRect;
	qreal m_resultZoomRate;
	bool m_firstExpand;
	quint8 m_rectAlpha;
	qint32 m_topPage;
};

