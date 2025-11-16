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

#include <QtGui>
#include <QtOpenGL>

#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>

#include "GLWidget.h"

inline	double	Clip255(double d)
{
	if(d>255)
		return 255;
	if(d<0)
		return 0;
	return d;
}

inline	void	GetRGBValue(BYTE P,BYTE S,BYTE R,double Coefficient,double &Red,double &Green,double &Blue)
{
	double temp=R*Coefficient*cos((M_PI/2.0)*(P/255.0));
	Red		=Clip255(temp*sin((M_PI/2.0)*(S/255.0)));
	Green	=Clip255(R*Coefficient*sin((M_PI/2.0)*(P/255.0)));
	Blue	=Clip255(temp*cos((M_PI/2.0)*(S/255.0)));
}

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    object = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
//	Scale = 1.0;
	Scale = 0.002465;
	side = 0;
	dx = 0;
	dy = 0;
//	Red = Green = Blue = 0;
	P = S = R = 0;
	PL = PH = SL = SH = RL = RH = 0;
	Coefficient=sqrt((double)(255*255+255*255+255*255))/255.0;

	BackgroundColor = QColor(Qt::white);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(object, 1);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::initializeGL()
{
    qglClearColor(BackgroundColor);	//glClearColor バッファを初期化するカラー情報
    object = makeObject();
    glShadeModel(GL_FLAT);			//フラットシェーディングの設定で、同じ面の明るさは一定になります
    glEnable(GL_DEPTH_TEST);		//デプステストを有効にします 多角形に影を付けるには、各多角形の前後関係を決定する必要がある
//    glEnable(GL_CULL_FACE);			//片面表示を有効にします ポリゴンのおもて面のみを描き、裏を描かないようにする

	glDisable(GL_CULL_FACE);		//両面を描く

	glEnable(GL_BLEND);				//ブレンドを有効化
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //混合の設定
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//指定したバッファを特定の色で消去
			//GL_COLOR_BUFFER_BIT カラー バッファ 
			//GL_DEPTH_BUFFER_BIT デプス バッファ 
			//GL_ACCUM_BUFFER_BIT アキュムレーション バッファ 
			//GL_STENCIL_BUFFER_BIT ステンシル バッファ 
    glLoadIdentity();						//現在選択されている行列に単位行列をロードする
    glTranslated(0.0, 0.0, -10.0);			//変換行列に平行移動の行列を乗じます
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);	//変換行列に回転の行列を乗じます
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
//    glTranslated((double)(dx)/side, (double)(dy)/side, 0.0);			//変換行列に平行移動の行列を乗じます
	glScaled (Scale,Scale,Scale);
    glCallList(object);						//保存されたコマンドを呼び出す（リスト内容を描画します）

	//テキストの表示
	QFont f=QFont("Helvetica",14);
	f.setBold(true);
	qglColor(QColor(255,0,0,200));
	renderText(-127,128,-127,"Red",f);
	qglColor(QColor(0,255,0,200));
	renderText(-127,-127,128,"Green",f);
	qglColor(QColor(0,0,255,200));
	renderText(128,128,128,"Blue",f);
	qglColor(QColor(0,0,0,200));
	renderText(-127,142,128,"(0,0,0)",f);
}

void GLWidget::resizeGL(int width, int height)
{
    side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);	//ビューポートの設定 左下隅 width と height

    glMatrixMode(GL_PROJECTION);	//行列演算に関係するコマンドを利用する
				//GL_MODELVIEW モデルビュー行列 
				//GL_PROJECTION 射影行列 
				//GL_TEXTURE テクスチャ行列 
    glLoadIdentity();							//現在の行列を単位行列にする
    glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);	//正射影の視体積を作成する
    glMatrixMode(GL_MODELVIEW);		//行列演算に関係するコマンドを利用する
				//GL_MODELVIEW モデルビュー行列 
				//GL_PROJECTION 射影行列 
				//GL_TEXTURE テクスチャ行列 
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	int	D  = event->delta();
    dx = event->position().x() - lastPos.x();
    dy = event->position().y() - lastPos.y();

	//x、y、z には、それぞれスケーリング係数を指定します
	//1 以上であればオブジェクトが拡大され、1 より小さければ縮小されます
	//また、-1 にすれば線対称変換されます
	D > 0 ? Scale += Scale*0.1 : Scale -= Scale*0.1;
	updateGL();
}

void GLWidget::UpdateObject()
{
    glNewList(object, GL_COMPILE);	//glNewList～glEndListの間に描画コマンドを指定

	//軸の線を描く
	DrawAxis();

	//任意の点を描く
	DrawPoint();

	//閾値の立体を描く
	DrawThreshold();

    glEndList();
}

GLuint GLWidget::makeObject()
{
    GLuint list = glGenLists(1);	//新規にディスプレイリストを確保する
    object = list;
	UpdateObject();
/*
    glNewList(list, GL_COMPILE);	//glNewList～glEndListの間に描画コマンドを指定

	//軸の線を描く
	DrawAxis();

	//任意の点を描く
	DrawPoint();

	//閾値の立体を描く
	DrawThreshold();
/*
	//手前側の面 シアン
	glColor3d( 0.0, 1.0, 1.0);
	int R11,G11,B11;
	GetRGB(PL,SL,RL,R11,G11,B11);
	int R12,G12,B12;
	GetRGB(PH,SL,RL,R12,G12,B12);
	int R13,G13,B13;
	GetRGB(PH,SH,RL,R13,G13,B13);
	int R14,G14,B14;
	GetRGB(PL,SH,RL,R14,G14,B14);

	glVertex3d(B11-127,128-G11,128-R11);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B13-127,128-G13,128-R13);
	glVertex3d(B14-127,128-G14,128-R14);

	//奥側の面 紫
	glColor3d(1.0, 0.0, 1.0);
	int R24,G24,B24;
	GetRGB(PL,SH,RH,R24,G24,B24);
	int R23,G23,B23;
	GetRGB(PH,SH,RH,R23,G23,B23);
	int R22,G22,B22;
	GetRGB(PH,SL,RH,R22,G22,B22);
	int R21,G21,B21;
	GetRGB(PL,SL,RH,R21,G21,B21);

	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B23-127,128-G23,128-R23);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B21-127,128-G21,128-R21);

	//右側の面 青
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B11-127,128-G11,128-R11);
	glVertex3d(B21-127,128-G21,128-R21);

	//左側の面 黄
	glColor3d(1.0, 1.0, 0.0);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B13-127,128-G13,128-R13);
	glVertex3d(B23-127,128-G23,128-R23);

	// 上側の面 赤
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B23-127,128-G23,128-R23);
	glVertex3d(B13-127,128-G13,128-R13);

	// 下側の面 緑
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B21-127,128-G21,128-R21);
	glVertex3d(B11-127,128-G11,128-R11);
*/
/*
	//手前側の面 シアン
	glColor3d( 0.0, 1.0, 1.0);
	int R11,G11,B11;
	GetRGBValue(PL,SL,RL,Coefficient,R11,G11,B11);
	glVertex3d(B11-127,128-G11,128-R11);

	int R12,G12,B12;
	GetRGBValue(PH,SL,RL,Coefficient,R12,G12,B12);
	glVertex3d(B12-127,128-G12,128-R12);

	int R13,G13,B13;
	GetRGBValue(PH,SH,RL,Coefficient,R13,G13,B13);
	glVertex3d(B13-127,128-G13,128-R13);

	int R14,G14,B14;
	GetRGBValue(PL,SH,RL,Coefficient,R14,G14,B14);
	glVertex3d(B14-127,128-G14,128-R14);

	//奥側の面 紫
	glColor3d(1.0, 0.0, 1.0);
	int R24,G24,B24;
	GetRGBValue(PL,SH,RH,Coefficient,R24,G24,B24);
	glVertex3d(B24-127,128-G24,128-R24);

	int R23,G23,B23;
	GetRGBValue(PH,SH,RH,Coefficient,R23,G23,B23);
	glVertex3d(B23-127,128-G23,128-R23);

	int R22,G22,B22;
	GetRGBValue(PH,SL,RH,Coefficient,R22,G22,B22);
	glVertex3d(B22-127,128-G22,128-R22);

	int R21,G21,B21;
	GetRGBValue(PL,SL,RH,Coefficient,R21,G21,B21);
	glVertex3d(B21-127,128-G21,128-R21);

	//右側の面 青
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B11-127,128-G11,128-R11);
	glVertex3d(B21-127,128-G21,128-R21);

	//左側の面 黄
	glColor3d(1.0, 1.0, 0.0);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B13-127,128-G13,128-R13);
	glVertex3d(B23-127,128-G23,128-R23);

	// 上側の面 赤
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B23-127,128-G23,128-R23);
	glVertex3d(B13-127,128-G13,128-R13);

	// 下側の面 緑
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B21-127,128-G21,128-R21);
	glVertex3d(B11-127,128-G11,128-R11);
/*
	glBegin(GL_QUADS);
	// 奥側の面 赤
//	glColor3d(1.0, 0.0, 0.0);
	glColor4d(1.0, 0.0, 0.0 ,0.5);
//	glVertex3d( 0.0, -0.2, -0.2);
//	glVertex3d( 0.2, -0.2, -0.2);
//	glVertex3d( 0.2,  0.0, -0.2);
//	glVertex3d( 0.0,  0.0, -0.2);

	glVertex3d(-0.1, -0.1,-0.05);
	glVertex3d( 0.1, -0.1,-0.05);
	glVertex3d( 0.1,  0.1,-0.05);
	glVertex3d(-0.1,  0.1,-0.05);

	// 手前側の面 緑
//	glColor3d(0.0, 1.0, 0.0);
	glColor4d(0.0, 1.0, 0.0 ,0.5);
//	glVertex3d( 0.0,  0.0, 0.0);
//	glVertex3d( 0.2,  0.0, 0.0);
//	glVertex3d( 0.2, -0.2, 0.0);
//	glVertex3d( 0.0, -0.2, 0.0);

	glVertex3d(-0.1,  0.1, 0.05);
	glVertex3d( 0.1,  0.1, 0.05);
	glVertex3d( 0.1, -0.1, 0.05);
	glVertex3d(-0.1, -0.1, 0.05);

	// 右側の面 青
//	glColor3d(0.0, 0.0, 1.0);
	glColor4d(0.0, 0.0, 1.0 ,0.5);
//	glVertex3d( 0.2, -0.2, -0.2);
//	glVertex3d( 0.2, -0.2,  0.0);
//	glVertex3d( 0.2,  0.0,  0.0);
//	glVertex3d( 0.2,  0.0, -0.2);

	glVertex3d( 0.1, -0.1,-0.05);
	glVertex3d( 0.1, -0.1, 0.05);
	glVertex3d( 0.1,  0.1, 0.05);
	glVertex3d( 0.1,  0.1,-0.05);

	// 左側の面 黄
//	glColor3d(1.0, 1.0, 0.0);
	glColor4d(1.0, 1.0, 0.0 ,0.5);
//	glVertex3d( 0.0,  0.0, -0.2);
//	glVertex3d( 0.0,  0.0,  0.0);
//	glVertex3d( 0.0, -0.2,  0.0);
//	glVertex3d( 0.0, -0.2, -0.2);

	glVertex3d(-0.1,  0.1,-0.05);
	glVertex3d(-0.1,  0.1, 0.05);
	glVertex3d(-0.1, -0.1, 0.05);
	glVertex3d(-0.1, -0.1,-0.05);

	// 上側の面 紫
//	glColor3d(1.0, 0.0, 1.0);
	glColor4d(1.0, 0.0, 1.0 ,0.5);
//	glVertex3d( 0.0, -0.2,  0.0);
//	glVertex3d( 0.2, -0.2,  0.0);
//	glVertex3d( 0.2, -0.2, -0.2);
//	glVertex3d( 0.0, -0.2, -0.2);

	glVertex3d(-0.1, -0.1, 0.05);
	glVertex3d( 0.1, -0.1, 0.05);
	glVertex3d( 0.1, -0.1,-0.05);
	glVertex3d(-0.1, -0.1,-0.05);

	// 下側の面 シアン
//	glColor3d(0.0, 1.0, 1.0);
	glColor4d(0.0, 1.0, 1.0 ,0.5);
//	glVertex3d( 0.0, 0.0, -0.2);
//	glVertex3d( 0.2, 0.0, -0.2);
//	glVertex3d( 0.2, 0.0,  0.0);
//	glVertex3d( 0.0, 0.0,  0.0);

	glVertex3d(-0.1,  0.1,-0.05);
	glVertex3d( 0.1,  0.1,-0.05);
	glVertex3d( 0.1,  0.1, 0.05);
	glVertex3d(-0.1,  0.1, 0.05);
*/
///////////////////////////////////////////

/*
    glBegin(GL_QUADS);

    GLdouble x1 = +0.06;
    GLdouble y1 = -0.14;
    GLdouble x2 = +0.14;
    GLdouble y2 = -0.06;
    GLdouble x3 = +0.08;
    GLdouble y3 = +0.00;
    GLdouble x4 = +0.30;
    GLdouble y4 = +0.22;

    quad(x1, y1, x2, y2, y2, x2, y1, x1);
    quad(x3, y3, x4, y4, y4, x4, y3, x3);

    extrude(x1, y1, x2, y2);
    extrude(x2, y2, y2, x2);
    extrude(y2, x2, y1, x1);
    extrude(y1, x1, x1, y1);
    extrude(x3, y3, x4, y4);
    extrude(x4, y4, y4, x4);
    extrude(y4, x4, y3, x3);

    const double Pi = 3.14159265358979323846;
    const int NumSectors = 200;

    for (int i = 0; i < NumSectors; ++i) {
        double angle1 = (i * 2 * Pi) / NumSectors;
        GLdouble x5 = 0.30 * sin(angle1);
        GLdouble y5 = 0.30 * cos(angle1);
        GLdouble x6 = 0.20 * sin(angle1);
        GLdouble y6 = 0.20 * cos(angle1);

        double angle2 = ((i + 1) * 2 * Pi) / NumSectors;
        GLdouble x7 = 0.20 * sin(angle2);
        GLdouble y7 = 0.20 * cos(angle2);
        GLdouble x8 = 0.30 * sin(angle2);
        GLdouble y8 = 0.30 * cos(angle2);

        quad(x5, y5, x6, y6, x7, y7, x8, y8);

        extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
    }

    glEnd();

    glEndList();

    object = list;
*/
    return list;
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}

void GLWidget::DrawAxis()
{
	glEnable(GL_CULL_FACE);			//片面表示を有効にします ポリゴンのおもて面のみを描き、裏を描かないようにする

	//軸平面を描く
	glBegin(GL_QUADS);

	//R-G軸（Z-Y軸方向）
	for(int Green=0;Green<255;Green++){
		for(int Red=0;Red<255;Red++){
			qglColor(QColor(Red,Green,0));
			glVertex3d(-127,128-Green,128-Red);
			glVertex3d(-127,128-Green,127-Red);
			glVertex3d(-127,127-Green,127-Red);
			glVertex3d(-127,127-Green,128-Red);
		}
	}

	//B-G軸（X-Y軸方向）
	for(int Green=0;Green<255;Green++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(0,Green,Blue));
			glVertex3d(Blue-127,128-Green,128);
			glVertex3d(Blue-127,127-Green,128);
			glVertex3d(Blue-126,127-Green,128);
			glVertex3d(Blue-126,128-Green,128);
		}
	}

	//B-R軸（X-Z軸方向）
	for(int Red=0;Red<255;Red++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(Red,0,Blue));
			glVertex3d(Blue-127,128,128-Red);
			glVertex3d(Blue-126,128,128-Red);
			glVertex3d(Blue-126,128,127-Red);
			glVertex3d(Blue-127,128,127-Red);
		}
	}
/*
	//R-G軸奥（Z-Y軸奥方向）
	for(int Green=0;Green<255;Green++){
		for(int Red=0;Red<255;Red++){
			qglColor(QColor(Red,Green,255));
			glVertex3d(128,127-Green,128-Red);
			glVertex3d(128,127-Green,127-Red);
			glVertex3d(128,128-Green,127-Red);
			glVertex3d(128,128-Green,128-Red);
		}
	}

	//B-G軸奥（X-Y軸奥方向）
	for(int Green=0;Green<255;Green++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(255,Green,Blue));
			glVertex3d(Blue-126,128-Green,-127);
			glVertex3d(Blue-126,127-Green,-127);
			glVertex3d(Blue-127,127-Green,-127);
			glVertex3d(Blue-127,128-Green,-127);
		}
	}

	//B-R軸奥（X-Z軸奥方向）
	for(int Red=0;Red<255;Red++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(Red,255,Blue));
			glVertex3d(Blue-127,-127,127-Red);
			glVertex3d(Blue-126,-127,127-Red);
			glVertex3d(Blue-126,-127,128-Red);
			glVertex3d(Blue-127,-127,128-Red);
		}
	}
*/
    glEnd();

	glDisable(GL_CULL_FACE);		//両面を描く

	//軸を描く
	glBegin(GL_LINES);

	//R軸（Z軸方向）
	qglColor(QColor(255,0,0));
	glVertex3i(-127,128,128);
	glVertex3i(-127,128,-127);
	glVertex3i(-127,128,-127);
	glVertex3i(-132,128,-117);
	glVertex3i(-127,128,-127);
	glVertex3i(-122,128,-117);

	//G軸（Y軸方向）
	qglColor(QColor(0,255,0));
	glVertex3i(-127,128,128);
	glVertex3i(-127,-127,128);
	glVertex3i(-127,-127,128);
	glVertex3i(-130,-117,123);
	glVertex3i(-127,-127,128);
	glVertex3i(-124,-117,133);

	//B軸（X軸方向）
	qglColor(QColor(0,0,255));
	glVertex3i(-127,128,128);
	glVertex3i(128,128,128);
	glVertex3i(128,128,128);
	glVertex3i(118,128,123);
	glVertex3i(128,128,128);
	glVertex3i(118,128,133);

    glEnd();
/*
	glBegin(GL_LINES);

	//R軸（Z軸方向）
	glColor3d( 1.0, 0.0, 0.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( -127.0, 127.0, -128.0);

	//G軸（Y軸方向）
	glColor3d( 0.0, 1.0, 0.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( -127.0, -128.0, 127.0);

	//B軸（X軸方向）
	glColor3d( 0.0, 0.0, 1.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( 128.0, 127.0, 127.0);

    glEnd();
*/
}

void GLWidget::DrawPoint()
{
	//任意の点を描く
	double Red,Green,Blue;
	GetRGBValue(P,S,R,Coefficient,Red,Green,Blue);
	qglColor(QColor(Red,Green,Blue));
	glTranslated(Blue-127,128-Green,128-Red);
	sphere = gluNewQuadric();				//オブジェクトを生成
	gluQuadricDrawStyle(sphere, GLU_FILL);	//オブジェクトの描画タイプを設定（省略可）
	gluSphere(sphere,3,10,10);				//円の描画
	glTranslated(-(Blue-127),-(128-Green),-(128-Red));
	gluDeleteQuadric(sphere);				//メモリ解放
/*
	qglColor(QColor(Red,Green,Blue));
	glTranslated(Blue-127,128-Green,128-Red);
	sphere = gluNewQuadric();				//オブジェクトを生成
	gluQuadricDrawStyle(sphere, GLU_FILL);	//オブジェクトの描画タイプを設定（省略可）
	gluSphere(sphere,3,10,10);				//円の描画
	glTranslated(-(Blue-127),-(128-Green),-(128-Red));
	gluDeleteQuadric(sphere);				//メモリ解放
*/
	//矢印を描く
//	glLineWidth(10);
	glBegin(GL_LINES);

	qglColor(QColor(0,0,0));
	glVertex3i(Blue-127,128-Green,128-Red);
	glVertex3i(Blue-100,120-Green,120-Red);
	glVertex3i(Blue-127,128-Green,128-Red);
	glVertex3i(Blue-118,126-Green,120-Red);
	glVertex3i(Blue-127,128-Green,128-Red);
	glVertex3i(Blue-117,126-Green,130-Red);

    glEnd();
}

void GLWidget::DrawThreshold()
{
	glBegin(GL_QUADS);

	//手前側の面 シアン
	for(BYTE P=PL;P<PH;P++){
		for(BYTE S=SL;S<SH;S++){
			double Red,Green,Blue;
			GetRGBValue(P,S,RL,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,S,RL,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,S+1,RL,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P,S+1,RL,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

	//奥側の面 紫
	for(BYTE P=PL;P<PH;P++){
		for(BYTE S=SL;S<SH;S++){
			double Red,Green,Blue;
			GetRGBValue(P,S+1,RH,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,S+1,RH,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,S,RH,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P,S,RH,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

	//右側の面 青
	for(BYTE P=PL;P<PH;P++){
		for(BYTE R=RL;R<RH;R++){
			double Red,Green,Blue;
			GetRGBValue(P,SL,R,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P,SL,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,SL,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,SL,R,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

	//左側の面 黄
	for(BYTE P=PL;P<PH;P++){
		for(BYTE R=RL;R<RH;R++){
			double Red,Green,Blue;
			GetRGBValue(P+1,SH,R,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P+1,SH,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P,SH,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(P,SH,R,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

	// 上側の面 赤
	for(BYTE R=RL;R<RH;R++){
		for(BYTE S=SL;S<SH;S++){
			double Red,Green,Blue;
			GetRGBValue(PH,S,R,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PH,S,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PH,S+1,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PH,S+1,R,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

	// 下側の面 緑
	for(BYTE R=RL;R<RH;R++){
		for(BYTE S=SL;S<SH;S++){
			double Red,Green,Blue;
			GetRGBValue(PL,S+1,R,Coefficient,Red,Green,Blue);
			qglColor(QColor(Red,Green,Blue,200));
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PL,S+1,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PL,S,R+1,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
			GetRGBValue(PL,S,R,Coefficient,Red,Green,Blue);
			glVertex3d(Blue-127,128-Green,128-Red);
		}
	}

    glEnd();
}

void GLWidget::GetRGB(BYTE P,BYTE S,BYTE R,BYTE &Red,BYTE &Green,BYTE &Blue)
{
	double A	=cos((double)S*M_PI/510.0);
	double A2	=A*A;
	double B	=tan((double)P*M_PI/510.0);

	double r=sqrt(3.0*R*R*(1.0-A2)/(B*B+1));
	double temp,temp1;
	if(A==1.0){		//S==0と同意？
		temp=R*sin((P/255.0)*(M_PI/2.0))*(sqrt((double)(255*255+255*255+255*255))/255.0);;
	}
	else{
		if((temp1=3.0*R*R-r*r/(1.0-A2))<0){
			temp=0;
		}
		else{
			temp=sqrt(temp1);
		}
	}
	double g=temp;
	if((temp1=3.0*R*R-r*r-g*g)<0){
		temp=0;
	}
	else{
		temp=sqrt(temp1);
	}
	double b=temp;

	Red		=Clip255(r+0.5);
	Green	=Clip255(g+0.5);
	Blue	=Clip255(b+0.5);
}
