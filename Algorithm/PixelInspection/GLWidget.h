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

	GLUquadricObj *sphere;	//�I�u�W�F�N�g�|�C���^������

    QPoint lastPos;
    QColor BackgroundColor;
};

#endif