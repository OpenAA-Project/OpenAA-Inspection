/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#if QT_VERSION > 0x040800
#include <GL/GLU.h>
#endif

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    virtual QSize minimumSizeHint() const   override;
    virtual QSize sizeHint() const  override;

    void UpdateObject();

//	void SetRedValue	(BYTE value)	{	Red		=value;	}
//	void SetGreenValue	(BYTE value)	{	Green	=value;	}
//	void SetBlueValue	(BYTE value)	{	Blue	=value;	}
	void SetPValue(BYTE value)	{	P	=value;	}
	void SetSValue(BYTE value)	{	S	=value;	}
	void SetRValue(BYTE value)	{	R	=value;	}

	void SetPLValue(BYTE value)	{	PL=value;	}
	void SetPHValue(BYTE value)	{	PH=value;	}
	void SetSLValue(BYTE value)	{	SL=value;	}
	void SetSHValue(BYTE value)	{	SH=value;	}
	void SetRLValue(BYTE value)	{	RL=value;	}
	void SetRHValue(BYTE value)	{	RH=value;	}

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    virtual void initializeGL() override;
    virtual void paintGL()      override;
    virtual void resizeGL(int width, int height)        override;
    virtual void mousePressEvent(QMouseEvent *event)	override;
    virtual void mouseMoveEvent(QMouseEvent *event)		override;
	virtual void wheelEvent(QWheelEvent *event)			override;

private:
    GLuint makeObject();
    void normalizeAngle(int *angle);

	void DrawAxis();
	void DrawPoint();
	void DrawThreshold();
	void GetRGB(BYTE P,BYTE S,BYTE R,BYTE &Red,BYTE &Green,BYTE &Blue);

    GLuint object;
    int xRot;
    int yRot;
    int zRot;
    double Scale;
	int side;
	int dx;
	int dy;

//	BYTE Red,Green,Blue;
	BYTE P,S,R;
	BYTE PL,PH,SL,SH,RL,RH;
	double Coefficient;

	GLUquadricObj *sphere;	//オブジェクトポインタを準備

    QPoint lastPos;
    QColor BackgroundColor;
};

#endif
