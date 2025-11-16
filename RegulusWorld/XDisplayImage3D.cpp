#include "XDisplayImage3D.h"
#include <QSurfaceFormat>
#include "XRegulusWorld.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XRegulusWorld.h"

XDisplayFixedView::XDisplayFixedView(QWidget *parent
                ,XDisplayImage3D5Panels *p
                ,EnumDisplay3DType d
				,bool	EnableMeasure
				,bool	EnableToolArea
				,bool	EnableVScroller
				,bool	EnableHScroller
				,bool	EnableZoom
				,bool	EnableMove
				,bool	EnableFitZoom)
	:mtGraphicUnit(parent,EnableMeasure
						 ,EnableToolArea
						 ,EnableVScroller
						 ,EnableHScroller
						 ,EnableZoom
						 ,EnableMove
						 ,EnableFitZoom)
    ,Display3DType(d)
    ,Parent(p)
{
    connect(this,SIGNAL(SignalOnPaint(QPainter &))          ,this,SLOT(SlotOnPaint(QPainter &)));
    connect(this,SIGNAL(SignalMouseMove(int ,int))          ,this,SLOT(SlotMouseMove(int ,int)));
    connect(this,SIGNAL(SignalMouseLDownWithShift(int ,int)),this,SLOT(SlotMouseLDownWithShift(int ,int)));
    connect(this,SIGNAL(SignalMouseLUp(int ,int))           ,this,SLOT(SlotMouseLUp(int ,int)));
    connect(this,SIGNAL(SignalMouseRUp(int ,int))           ,this,SLOT(SlotMouseRUp(int ,int)));

    RW3DInPageRoot  *Ap=(RW3DInPageRoot *)Parent->AlgoBase->GetPageData(Parent->Page);
    Point3D MinPoint,MaxPoint;
    if(Ap->GetArea(MinPoint,MaxPoint)==true){
        Point3D Center=(MinPoint+MaxPoint)/2;
        switch(Display3DType){
	    case DT_Top     :
            CamView.Point   =Center+Vector3D(0,0,(MaxPoint.GetZ()-MinPoint.GetZ())*3);
            CamView.Radian.Set(0,M_PI/2,0);
            CamView.Length  =(MaxPoint.GetZ()-MinPoint.GetZ());
            break;
	    case DT_Bottom  :
            CamView.Point   =Center+Vector3D(0,0,-(MaxPoint.GetZ()-MinPoint.GetZ())*3);
            CamView.Radian.Set(0,-M_PI/2,0);
            CamView.Length  =(MaxPoint.GetZ()-MinPoint.GetZ());
            break;
        case DT_Left    :
            CamView.Point   =Center+Vector3D(-(MaxPoint.GetX()-MinPoint.GetX())*3,0,0);
            CamView.Radian.Set(0,0,M_PI);
            CamView.Length  =(MaxPoint.GetX()-MinPoint.GetX());
            break;
        case DT_Right   :
            CamView.Point   =Center+Vector3D((MaxPoint.GetX()-MinPoint.GetX())*3,0,0);
            CamView.Radian.Set(0,0,0);
            CamView.Length  =(MaxPoint.GetX()-MinPoint.GetX());
            break;
	    case DT_3D      :
            CamView.Point   =Center+Vector3D((MaxPoint.GetX()-MinPoint.GetX())*3,(MaxPoint.GetX()-MinPoint.GetX())*3,0);
            CamView.Radian.Set(0,0,0);
            CamView.Length  =(MaxPoint.GetX()-MinPoint.GetX());
            break;
        }
    }
}

void	XDisplayFixedView::SlotOnPaint(QPainter &pnt)
{
    RW3DInPageRoot  *Ap=(RW3DInPageRoot *)Parent->AlgoBase->GetPageData(Parent->Page);
    Ap->Draw(DCanvas,CamView,NULL);
}
void	XDisplayFixedView::SlotMouseMove(int x,int y)
{
}
void	XDisplayFixedView::SlotMouseLDownWithShift(int x,int y)
{
}
void	XDisplayFixedView::SlotMouseLUp(int x,int y)
{
}
void	XDisplayFixedView::SlotMouseRUp(int x,int y)
{
}

void	XDisplayFixedView::resizeEvent ( QResizeEvent * event )
{
    DCanvas=QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
}

//============================================================================

XDisplayView3D::XDisplayView3D(QWidget *parent
                ,XDisplayImage3D5Panels *p
                ,EnumDisplay3DType d
				,bool	EnableMeasure
				,bool	EnableToolArea
				,bool	EnableVScroller
				,bool	EnableHScroller
				,bool	EnableZoom
				,bool	EnableMove
				,bool	EnableFitZoom)
	:mtGraphicUnit(parent,EnableMeasure
						 ,EnableToolArea
						 ,EnableVScroller
						 ,EnableHScroller
						 ,EnableZoom
						 ,EnableMove
						 ,EnableFitZoom)
    ,Display3DType(d)
    ,Parent(p)
{
    connect(this,SIGNAL(SignalOnPaint(QPainter &))          ,this,SLOT(SlotOnPaint(QPainter &)));
    connect(this,SIGNAL(SignalMouseMove(int ,int))          ,this,SLOT(SlotMouseMove(int ,int)));
    connect(this,SIGNAL(SignalMouseLDownWithShift(int ,int)),this,SLOT(SlotMouseLDownWithShift(int ,int)));
    connect(this,SIGNAL(SignalMouseLUp(int ,int))           ,this,SLOT(SlotMouseLUp(int ,int)));
    connect(this,SIGNAL(SignalMouseRUp(int ,int))           ,this,SLOT(SlotMouseRUp(int ,int)));
}

void	XDisplayView3D::SlotOnPaint(QPainter &pnt)
{
}
void	XDisplayView3D::SlotMouseMove(int x,int y)
{
}
void	XDisplayView3D::SlotMouseLDownWithShift(int x,int y)
{
}
void	XDisplayView3D::SlotMouseLUp(int x,int y)
{
}
void	XDisplayView3D::SlotMouseRUp(int x,int y)
{
}

//============================================================================

XDisplayImage3D5Panels::XDisplayImage3D5Panels(RegulusWorld *wbase
                                                ,const QString AlgoDLLRoot ,const QString AlgoDLLName
                                                ,QWidget *p)
	:QWidget(p),WBase(wbase)
{	
    AlgoBase=WBase->GetRW3DBaseRoot(AlgoDLLRoot,AlgoDLLName);
	Page    =0;
    SplitterH	=new QSplitter(this);
	SplitterH	->setOrientation(Qt::Horizontal);
	SplitterH	->addWidget((ViewLeft=new XDisplayFixedView (this,this,DT_Left ,true,true,true,true,true,true,false)));
	SplitterH	->addWidget((View3D	=new XDisplayView3D     (this,this,DT_3D   ,true,true,true,true,true,true,false)));
	SplitterH	->addWidget((ViewRight=new XDisplayFixedView(this,this,DT_Right,true,true,true,true,true,true,false)));
	SplitterH	->setGeometry(0,0,width(),height());
    QList<int> HSize;
    HSize<<width()/5;
    HSize<<3*width()/5;
    HSize<<width()/5;
    SplitterH	->setSizes(HSize);

	SplitterV	=new QSplitter(this);
	SplitterV	->setOrientation(Qt::Vertical);
	SplitterV	->addWidget((ViewTop=new XDisplayFixedView   (this,this,DT_Top,true,true,true,true,true,true,false)));
	SplitterV	->addWidget(SplitterH);                   
	SplitterV	->addWidget((ViewBottom=new XDisplayFixedView(this,this,DT_Bottom,true,true,true,true,true,true,false)));
	SplitterV	->setGeometry(0,0,width(),height());
    QList<int> VSize;
    VSize<<height()/4;
    VSize<<2*height()/4;
    VSize<<height()/4;
    SplitterV	->setSizes(VSize);   
}

void XDisplayImage3D5Panels::resizeEvent(QResizeEvent *event)
{
	SplitterV	->setGeometry(0,0,width(),height());
	SplitterV->show();

    QList<int> HSize=SplitterH->sizes();
    QList<int> VSize=SplitterV->sizes();
}

//============================================================================

XDisplayImage3D::XDisplayImage3D(RegulusWorld *wbase,QWidget *p)
:QOpenGLWidget(p)
{
	bool	ErrorOccurs=false;
	if(!connect(this ,SIGNAL(SignalOnPaint(QPainter &)) ,this,SLOT(CanvasSlotOnPaint(QPainter &)))){
		ErrorOccurs=true;
	}
    program=nullptr;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    alpha = 25;
    beta = -25;
    distance = 2.5;
}

XDisplayImage3D::~XDisplayImage3D(void)
{
}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void XDisplayImage3D::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void XDisplayImage3D::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void XDisplayImage3D::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

static const char *vertexShaderSource =
"#version 130\n"
"uniform mat4 mvpMatrix;\n"
"in vec4 vertex;\n"
"in vec4 color;\n"
"out vec4 varyingColor;\n"
"void main(void)\n"
"{\n"
"    varyingColor = color;\n"
"    gl_Position = mvpMatrix * vertex;\n"
"}";

static const char *fragmentShaderSource =
        "#version 130\n"
        "in vec4 varyingColor;\n"
        "out vec4 fragColor;\n"
        "void main(void)\n"
        "{\n"
        "    fragColor = varyingColor;\n"
        "}\n";

QByteArray versionedShaderCode(const char *src)
{
    QByteArray versionedSrc;

    if (QOpenGLContext::currentContext()->isOpenGLES())
        versionedSrc.append(QByteArrayLiteral("#version 300 es\n"));
    else
        versionedSrc.append(QByteArrayLiteral("#version 330\n"));

    versionedSrc.append(src);
    return versionedSrc;
}

void XDisplayImage3D::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f); // [7]

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
    vertexLocation_ = program->attributeLocation("vertex");
    colorLocation_  = program->attributeLocation("color");
}

void XDisplayImage3D::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void XDisplayImage3D::paintGL()
{
    vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
             << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
             << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Back
             << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
             << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
             << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Right
             << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5)
             << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) // Top
             << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5,  0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) // Bottom
             << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5, -0.5);
    //! [1]
    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Front
           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Back
           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Top
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);


    program->bind();
    program->setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    program->enableAttributeArray(vertexLocation_);
    program->enableAttributeArray(colorLocation_);
    program->setAttributeArray(vertexLocation_, vertices.constData());
    program->setAttributeArray(colorLocation_,  colors.constData());

    //glDrawArrays(GL_POLYGON, 0, 4);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    program->disableAttributeArray(vertexLocation_);
    program->disableAttributeArray(colorLocation_);
    program->release();
}

void XDisplayImage3D::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void XDisplayImage3D::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }

        update();
    }

    lastMousePosition = event->pos();

    event->accept();
}

void XDisplayImage3D::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        update();
    }

    event->accept();
}