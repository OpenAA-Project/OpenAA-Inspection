#pragma once

#include <QWidget>
#include <QSplitter>
#include "mtGraphicUnit.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector>
#include "XRegulusWorldObject.h"

class	RegulusWorld;
class	XDisplayImage3D5Panels;
class	RW3DBaseRoot;
class	RW3DInPageRoot;
class	PointVector3D;


//==========================================================================================

enum EnumDisplay3DType
{
	 DT_Top
	,DT_Bottom
	,DT_Left
	,DT_Right
	,DT_3D
};

class XDisplayFixedView : public mtGraphicUnit
{
	Q_OBJECT

	friend	class XDisplayImage3D5Panels;
	EnumDisplay3DType	Display3DType;
	XDisplayImage3D5Panels	*Parent;
	CameraView CamView;
	QImage	DCanvas;
public:
	XDisplayFixedView(QWidget *parent
				,XDisplayImage3D5Panels *p
				,EnumDisplay3DType d
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);

public slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseMove(int ,int);
	void	SlotMouseLDownWithShift(int ,int);
	void	SlotMouseLUp(int ,int);
	void	SlotMouseRUp(int ,int);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

class XDisplayView3D : public mtGraphicUnit
{
	Q_OBJECT

	friend	class XDisplayImage3D5Panels;
	EnumDisplay3DType	Display3DType;
	XDisplayImage3D5Panels	*Parent;
	CameraView CamView;

public:
	XDisplayView3D(QWidget *parent
				,XDisplayImage3D5Panels *p
				,EnumDisplay3DType d
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);
public slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseMove(int ,int);
	//void	SlotMouseLDoubleClick(int ,int);
	void	SlotMouseLDownWithShift(int ,int);
	void	SlotMouseLUp(int ,int);
	void	SlotMouseRUp(int ,int);
};


class XDisplayImage3D5Panels : public QWidget
{
	Q_OBJECT

	friend	class XDisplayFixedView;
	friend	class XDisplayView3D;

	RegulusWorld		*WBase;
	RW3DBaseRoot		*AlgoBase;

	QSplitter			*SplitterH;
	QSplitter			*SplitterV;

	XDisplayFixedView	*ViewTop;
	XDisplayFixedView	*ViewBottom;
	XDisplayFixedView	*ViewLeft;
	XDisplayFixedView	*ViewRight;
	XDisplayView3D		*View3D;

	int	Page;

public:

	XDisplayImage3D5Panels(RegulusWorld *wbase
							,const QString AlgoDLLRoot ,const QString AlgoDLLName
							,QWidget *p=nullptr);

private:
	virtual	void resizeEvent(QResizeEvent *event)	override;

public slots:

};

//===================================================================
class XDisplayImage3D : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

	RegulusWorld	*WBase;
public:
	XDisplayImage3D(RegulusWorld *wbase,QWidget *p=nullptr);
	~XDisplayImage3D(void);

//private slots:
//	void	CanvasSlotOnPaint(QPainter &Pnt);

private:
    void initializeGL()		override;
    void paintGL()	        override;
    void resizeGL(int width, int height)    override;

private:
    //QOpenGLShaderProgram *program;
    //int vertexLocation_;
    //int colorLocation_;

    void mousePressEvent(QMouseEvent *event)	override;
    void mouseMoveEvent(QMouseEvent *event)		override;
    void wheelEvent(QWheelEvent *event)			override;

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:


    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    QMatrix4x4 pMatrix;
    QOpenGLShaderProgram *program;
	int vertexLocation_;
	int colorLocation_;

    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

};