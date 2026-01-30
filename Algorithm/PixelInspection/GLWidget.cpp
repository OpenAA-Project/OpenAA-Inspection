/*
 * Copyright (C) 2021
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
    qglClearColor(BackgroundColor);	//glClearColor �o�b�t�@�������������J���[����
    object = makeObject();
    glShadeModel(GL_FLAT);			//�t���b�g�V�F�[�f�B���O�̐ݒ��ŁA�����ʂ̖��邳�͈����ɂȂ��܂�
    glEnable(GL_DEPTH_TEST);		//�f�v�X�e�X�g���L���ɂ��܂� ���p�`�ɉe���t�����ɂ́A�e���p�`�̑O���֌W�����肷���K�v������
//    glEnable(GL_CULL_FACE);			//�Жʕ\�����L���ɂ��܂� �|���S���̂����Ėʂ݂̂��`���A�����`���Ȃ��悤�ɂ���

	glDisable(GL_CULL_FACE);		//���ʂ��`��

	glEnable(GL_BLEND);				//�u�����h���L����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //�����̐ݒ�
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//�w�肵���o�b�t�@�������̐F�ŏ���
			//GL_COLOR_BUFFER_BIT �J���[ �o�b�t�@ 
			//GL_DEPTH_BUFFER_BIT �f�v�X �o�b�t�@ 
			//GL_ACCUM_BUFFER_BIT �A�L�������[�V���� �o�b�t�@ 
			//GL_STENCIL_BUFFER_BIT �X�e���V�� �o�b�t�@ 
    glLoadIdentity();						//���ݑI�������Ă����s���ɒP�ʍs�������[�h����
    glTranslated(0.0, 0.0, -10.0);			//�ϊ��s���ɕ��s�ړ��̍s�����悶�܂�
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);	//�ϊ��s���ɉ��]�̍s�����悶�܂�
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
//    glTranslated((double)(dx)/side, (double)(dy)/side, 0.0);			//�ϊ��s���ɕ��s�ړ��̍s�����悶�܂�
	glScaled (Scale,Scale,Scale);
    glCallList(object);						//�ۑ����ꂽ�R�}���h���Ăяo���i���X�g���e���`�悵�܂��j

	//�e�L�X�g�̕\��
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
    glViewport((width - side) / 2, (height - side) / 2, side, side);	//�r���[�|�[�g�̐ݒ� ������ width �� height

    glMatrixMode(GL_PROJECTION);	//�s�񉉎Z�Ɋ֌W�����R�}���h�𗘗p����
				//GL_MODELVIEW ���f���r���[�s�� 
				//GL_PROJECTION �ˉe�s�� 
				//GL_TEXTURE �e�N�X�`���s�� 
    glLoadIdentity();							//���݂̍s�����P�ʍs���ɂ���
    glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);	//���ˉe�̎��̐ς��쐬����
    glMatrixMode(GL_MODELVIEW);		//�s�񉉎Z�Ɋ֌W�����R�}���h�𗘗p����
				//GL_MODELVIEW ���f���r���[�s�� 
				//GL_PROJECTION �ˉe�s�� 
				//GL_TEXTURE �e�N�X�`���s�� 
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

	//x�Ay�Az �ɂ́A���ꂼ���X�P�[�����O�W�����w�肵�܂�
	//1 �ȏ��ł����΃I�u�W�F�N�g���g�傳���A1 ���菬�������Ώk�������܂�
	//�܂��A-1 �ɂ����ΐ��Ώ̕ϊ������܂�
	D > 0 ? Scale += Scale*0.1 : Scale -= Scale*0.1;
	updateGL();
}

void GLWidget::UpdateObject()
{
    glNewList(object, GL_COMPILE);	//glNewList�`glEndList�̊Ԃɕ`���R�}���h���w��

	//���̐����`��
	DrawAxis();

	//�C�ӂ̓_���`��
	DrawPoint();

	//臒l�̗��̂��`��
	DrawThreshold();

    glEndList();
}

GLuint GLWidget::makeObject()
{
    GLuint list = glGenLists(1);	//�V�K�Ƀf�B�X�v���C���X�g���m�ۂ���
    object = list;
	UpdateObject();
/*
    glNewList(list, GL_COMPILE);	//glNewList�`glEndList�̊Ԃɕ`���R�}���h���w��

	//���̐����`��
	DrawAxis();

	//�C�ӂ̓_���`��
	DrawPoint();

	//臒l�̗��̂��`��
	DrawThreshold();
/*
	//���O���̖� �V�A��
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

	//�����̖� ��
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

	//�E���̖� ��
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B11-127,128-G11,128-R11);
	glVertex3d(B21-127,128-G21,128-R21);

	//�����̖� ��
	glColor3d(1.0, 1.0, 0.0);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B13-127,128-G13,128-R13);
	glVertex3d(B23-127,128-G23,128-R23);

	// �㑤�̖� ��
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B23-127,128-G23,128-R23);
	glVertex3d(B13-127,128-G13,128-R13);

	// �����̖� ��
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B21-127,128-G21,128-R21);
	glVertex3d(B11-127,128-G11,128-R11);
*/
/*
	//���O���̖� �V�A��
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

	//�����̖� ��
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

	//�E���̖� ��
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B11-127,128-G11,128-R11);
	glVertex3d(B21-127,128-G21,128-R21);

	//�����̖� ��
	glColor3d(1.0, 1.0, 0.0);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B13-127,128-G13,128-R13);
	glVertex3d(B23-127,128-G23,128-R23);

	// �㑤�̖� ��
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(B12-127,128-G12,128-R12);
	glVertex3d(B22-127,128-G22,128-R22);
	glVertex3d(B23-127,128-G23,128-R23);
	glVertex3d(B13-127,128-G13,128-R13);

	// �����̖� ��
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(B14-127,128-G14,128-R14);
	glVertex3d(B24-127,128-G24,128-R24);
	glVertex3d(B21-127,128-G21,128-R21);
	glVertex3d(B11-127,128-G11,128-R11);
/*
	glBegin(GL_QUADS);
	// �����̖� ��
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

	// ���O���̖� ��
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

	// �E���̖� ��
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

	// �����̖� ��
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

	// �㑤�̖� ��
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

	// �����̖� �V�A��
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
	glEnable(GL_CULL_FACE);			//�Жʕ\�����L���ɂ��܂� �|���S���̂����Ėʂ݂̂��`���A�����`���Ȃ��悤�ɂ���

	//�����ʂ��`��
	glBegin(GL_QUADS);

	//R-G���iZ-Y�������j
	for(int Green=0;Green<255;Green++){
		for(int Red=0;Red<255;Red++){
			qglColor(QColor(Red,Green,0));
			glVertex3d(-127,128-Green,128-Red);
			glVertex3d(-127,128-Green,127-Red);
			glVertex3d(-127,127-Green,127-Red);
			glVertex3d(-127,127-Green,128-Red);
		}
	}

	//B-G���iX-Y�������j
	for(int Green=0;Green<255;Green++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(0,Green,Blue));
			glVertex3d(Blue-127,128-Green,128);
			glVertex3d(Blue-127,127-Green,128);
			glVertex3d(Blue-126,127-Green,128);
			glVertex3d(Blue-126,128-Green,128);
		}
	}

	//B-R���iX-Z�������j
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
	//R-G�����iZ-Y���������j
	for(int Green=0;Green<255;Green++){
		for(int Red=0;Red<255;Red++){
			qglColor(QColor(Red,Green,255));
			glVertex3d(128,127-Green,128-Red);
			glVertex3d(128,127-Green,127-Red);
			glVertex3d(128,128-Green,127-Red);
			glVertex3d(128,128-Green,128-Red);
		}
	}

	//B-G�����iX-Y���������j
	for(int Green=0;Green<255;Green++){
		for(int Blue=0;Blue<255;Blue++){
			qglColor(QColor(255,Green,Blue));
			glVertex3d(Blue-126,128-Green,-127);
			glVertex3d(Blue-126,127-Green,-127);
			glVertex3d(Blue-127,127-Green,-127);
			glVertex3d(Blue-127,128-Green,-127);
		}
	}

	//B-R�����iX-Z���������j
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

	glDisable(GL_CULL_FACE);		//���ʂ��`��

	//�����`��
	glBegin(GL_LINES);

	//R���iZ�������j
	qglColor(QColor(255,0,0));
	glVertex3i(-127,128,128);
	glVertex3i(-127,128,-127);
	glVertex3i(-127,128,-127);
	glVertex3i(-132,128,-117);
	glVertex3i(-127,128,-127);
	glVertex3i(-122,128,-117);

	//G���iY�������j
	qglColor(QColor(0,255,0));
	glVertex3i(-127,128,128);
	glVertex3i(-127,-127,128);
	glVertex3i(-127,-127,128);
	glVertex3i(-130,-117,123);
	glVertex3i(-127,-127,128);
	glVertex3i(-124,-117,133);

	//B���iX�������j
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

	//R���iZ�������j
	glColor3d( 1.0, 0.0, 0.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( -127.0, 127.0, -128.0);

	//G���iY�������j
	glColor3d( 0.0, 1.0, 0.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( -127.0, -128.0, 127.0);

	//B���iX�������j
	glColor3d( 0.0, 0.0, 1.0);
	glVertex3i( -127.0, 127.0, 127.0);
	glVertex3i( 128.0, 127.0, 127.0);

    glEnd();
*/
}

void GLWidget::DrawPoint()
{
	//�C�ӂ̓_���`��
	double Red,Green,Blue;
	GetRGBValue(P,S,R,Coefficient,Red,Green,Blue);
	qglColor(QColor(Red,Green,Blue));
	glTranslated(Blue-127,128-Green,128-Red);
	sphere = gluNewQuadric();				//�I�u�W�F�N�g�𐶐�
	gluQuadricDrawStyle(sphere, GLU_FILL);	//�I�u�W�F�N�g�̕`���^�C�v���ݒ��i�ȗ��j
	gluSphere(sphere,3,10,10);				//�~�̕`��
	glTranslated(-(Blue-127),-(128-Green),-(128-Red));
	gluDeleteQuadric(sphere);				//����������
/*
	qglColor(QColor(Red,Green,Blue));
	glTranslated(Blue-127,128-Green,128-Red);
	sphere = gluNewQuadric();				//�I�u�W�F�N�g�𐶐�
	gluQuadricDrawStyle(sphere, GLU_FILL);	//�I�u�W�F�N�g�̕`���^�C�v���ݒ��i�ȗ��j
	gluSphere(sphere,3,10,10);				//�~�̕`��
	glTranslated(-(Blue-127),-(128-Green),-(128-Red));
	gluDeleteQuadric(sphere);				//����������
*/
	//�������`��
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

	//���O���̖� �V�A��
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

	//�����̖� ��
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

	//�E���̖� ��
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

	//�����̖� ��
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

	// �㑤�̖� ��
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

	// �����̖� ��
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
	if(A==1.0){		//S==0�Ɠ��ӁH
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