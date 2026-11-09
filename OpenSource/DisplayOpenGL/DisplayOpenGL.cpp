#include "DisplayOpenGL.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <QString>
#include <QStringList>
#include "swap.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include "XCrossObj.h"
#include "mtMeter.h"
#include "mtPushButtonWithBalloon.h"


mtFrameDrawOGL::mtFrameDrawOGL(QWidget *parent)
: QOpenGLWidget(parent)
{
	static	bool	Initialized=false;
	resize(400, 400);
	DrawStartEvent			=NULL;

	//Cursor				=crDefault;
	FDrawMode				=fdNone;
	DrawStage				=0;
	FCancelDraw				=false;
	FOnDrawMode				=false;
	FEnableShiftImage		=true;
	//FCrossOnMoving		=false;
	FArrowLength			=30;
	Image					=NULL;
	NowGx=NowGy				=0;
 	ZoomRate				=1.0;
	movx					=0;
	movy					=0;
	LastMouseDownPointX		=0;
	LastMouseDownPointY		=0;
	LastShitX				=0;
	LastShitY				=0;
	ShiftingMode			=false;
	LeftClicked				=false;
	RightClicked			=false;
	DblClickMode			=false;
	NoShiftCanvasMode		=false;
	ImageShiftDelay			= 0;
	FModeCrossLine			=false;
	FCrossLineColor			=Qt::yellow;
	FModeRepaintOnMouseMove	=true;
	CancelClicked			=false;
	LineWidth				=0.0;

	setMouseTracking(true);

	connect(this,SIGNAL(SignalDrawEnd(void))	,this,SLOT(SlotDrawEnd(void)));
	connect(this,SIGNAL(SignalDrawing(DrawingMode,int))	,this,SLOT(SlotDrawing(DrawingMode,int)));
	connect(this,SIGNAL(SignalCancelDraw(void))	,this,SLOT(SlotCancelDraw(void)));
	connect(this,SIGNAL(SignalOnPaint(QPainter &))	,this,SLOT(SlotOnPaint(QPainter &)));
	qRegisterMetaType<DrawingMode>("DrawingMode");
	//grabKeyboard ();

	if(Initialized==false){
		Q_INIT_RESOURCE(mtFrameDrawOGL);
		Initialized=true;
	}

    m_program   = nullptr;
    m_texture   = 0;
    m_pbo       = 0;
    
    m_devicePixelRatio = 1.0;

    m_width     = 1920;
    m_height    = 1080;
    
    // デモ用: オーバーレイで描画するための透過PNG画像を読み込む（なければ作る）
    // 実際はファイルから load("icon.png") などしてください
    //m_spriteImage = QImage(128, 128, QImage::Format_ARGB32_Premultiplied);
    //m_spriteImage.fill(Qt::transparent);
    //QPainter p(&m_spriteImage);
    //p.setRenderHint(QPainter::Antialiasing);
    //p.setBrush(QColor(0, 255, 255, 128));
    //p.drawEllipse(10, 10, 108, 108);
    //p.setPen(Qt::white);
    //p.drawText(m_spriteImage.rect(), Qt::AlignCenter, "Sprite");

    // アニメーションタイマー
    connect(&m_timer, &QTimer::timeout, this, QOverload<>::of(&mtFrameDrawOGL::update));
    m_timer.start(33); 
}

mtFrameDrawOGL::~mtFrameDrawOGL()
{
	if (!isValid()) {
        return; 
    }
    makeCurrent();
    if (m_pbo){ 
        glDeleteBuffers(1, &m_pbo);
        m_pbo=0;
    }
    if (m_texture){
        glDeleteTextures(1, &m_texture);
        m_texture=0;
    }
    doneCurrent();

	disconnect(this,SLOT(SlotDrawEnd(void)));
	disconnect(this,SLOT(SlotDrawing(DrawingMode,int)));
	disconnect(this,SLOT(SlotCancelDraw(void)));
	disconnect(this,SLOT(SlotOnPaint(QPainter &)));

    DelImage();
}
void	mtFrameDrawOGL::closeEvent(QCloseEvent *event)
{
// 1. タイマーを止める
    if (m_timer.isActive()) {
        m_timer.stop();
    }

    // 親クラスの処理
    QWidget::closeEvent(event);
}
void mtFrameDrawOGL::initializeGL()
{
    initializeOpenGLFunctions();

    // --- 背景描画用のOpenGL初期化 (前回と同じ) ---
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, R"(
        attribute vec4 position;
        attribute vec2 texCoord;
        varying vec2 vTexCoord;
        void main() {
            gl_Position = position;
            vTexCoord = texCoord;
        }
    )");
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, R"(
        #ifdef GL_ES
        precision mediump float;
        #endif
        uniform sampler2D textureSampler;
        varying vec2 vTexCoord;
        void main() {
            gl_FragColor = texture2D(textureSampler, vTexCoord);
        }
    )");
    m_program->link();

    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 0.0f
    };
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenBuffers(1, &m_pbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * 4, nullptr, GL_STREAM_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void mtFrameDrawOGL::resizeGL(int w, int h)
{
    // デバイスのピクセル比率を考慮
    //m_devicePixelRatio = QOpenGLWindow::devicePixelRatio();
	m_devicePixelRatio = QOpenGLWidget::devicePixelRatio();
    glViewport(0, 0, w * m_devicePixelRatio, h * m_devicePixelRatio);
}

void mtFrameDrawOGL::resizeEvent ( QResizeEvent * event )
{
    //QOpenGLWindow::resizeEvent(event);
	QOpenGLWidget::resizeEvent(event);
    // GUIFormBaseのリサイズ処理も呼び出す
    QSize newSize = event->size();

	m_width = newSize.width()*m_devicePixelRatio;
    m_height = newSize.height()*m_devicePixelRatio;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBufferData(GL_PIXEL_UNPACK_BUFFER, m_width * m_height * 4, nullptr, GL_STREAM_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}
void	mtFrameDrawOGL::SlotDrawEnd(void)
{
//	setCursor(QCursor(Qt::ArrowCursor));
}
void	mtFrameDrawOGL::SlotDrawing(DrawingMode,int)
{
}
void	mtFrameDrawOGL::SlotCancelDraw(void)
{
}
void	mtFrameDrawOGL::SlotOnPaint(QPainter &pnt)
{
}
void	mtFrameDrawOGL::DrawFromOutside(QStringList &data)
{
}
void	mtFrameDrawOGL::paintEvent(QPaintEvent *event)
{
	paintGL();
}
void mtFrameDrawOGL::paintGL()
{
    // =========================================================
    // Step 1: 背景の高速描画 (Pure OpenGL + PBO)
    // =========================================================
    
    // PBOへのデータ転送 (CPU -> GPUメモリ)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);
    void* ptr = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_width * m_height * 4, 
                                 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    if (ptr) {
		emit	SignalDrawBackground(static_cast<GPUPixel*>(ptr) ,m_width,m_height); 

		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    }

    // テクスチャ更新 (DMA転送)
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // 背景描画実行
    glClear(GL_COLOR_BUFFER_BIT);
    m_program->bind();
    m_vbo.bind();
    int posLoc = m_program->attributeLocation("position");
    int texLoc = m_program->attributeLocation("texCoord");
    m_program->enableAttributeArray(posLoc);
    m_program->enableAttributeArray(texLoc);
    m_program->setAttributeBuffer(posLoc, GL_FLOAT, 0, 2, 4 * sizeof(float));
    m_program->setAttributeBuffer(texLoc, GL_FLOAT, 2 * sizeof(float), 2, 4 * sizeof(float));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 【重要】OpenGLのステートをクリーンにする
    // QPainterと混ぜる場合、バインドを解除しておかないとQPainterが誤動作することがある
    m_program->release();
    m_vbo.release();
    glBindTexture(GL_TEXTURE_2D, 0);


    // =========================================================
    // Step 2: プリミティブの高速描画 (QPainter with OpenGL Engine)
    // =========================================================
    
    QPainter painter(this); // ここでOpenGLペイントエンジンが起動
//    painter.setRenderHint(QPainter::Antialiasing); // アンチエイリアス有効
//
//    // 1. 線分の高速描画
//    QPen pen(Qt::yellow, 5);
//    painter.setPen(pen);
//    painter.drawLine(50, 50, 200 + anim, 300);
//
//    // 2. 矩形の高速描画 (半透明)
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor(255, 0, 0, 128)); // 赤 半透明
//    painter.drawRect(50, 350, 200, 100);
//
//    // 3. 楕円の高速描画
//    painter.setBrush(QColor(0, 255, 0, 180)); // 緑 半透明
//    painter.drawEllipse(300, 350, 150, 100);
//
//    // 4. QImageの高速描画 (アルファチャンネル付き)
//    // (x, y) = (500, 100) の位置に描画
//    //painter.drawImage(500, 100, m_spriteImage);
//
//    // 5. 文字列の高速描画
//    QFont font("Arial", 24, QFont::Bold);
//    painter.setFont(font);
//    painter.setPen(Qt::white);
//    // 影をつけて視認性を上げる
//    painter.setPen(Qt::black);
//    painter.drawText(52, 52, "High Performance Text");
//    painter.setPen(Qt::cyan);
//    painter.drawText(50, 50, "High Performance Text");

	InPaint(painter);

    painter.end(); // 描画終了 (OpenGLコマンドのフラッシュ)
}

//void mtFrameDrawOGL::DrawBackground(uint32_t* buffer)
//{
//    // 背景データの生成（前回と同じ、少し暗くしてオーバーレイを見やすく）
//    static int offset = 0;
//    offset++;
//    int total = m_width * m_height;
//    uint32_t color = (offset & 0xFF) << 16; 
//    for(int i=0; i<total; ++i) {
//        // 背景は少し暗く (Alpha=255)
//        buffer[i] = 0xFF000000 | (color / 2) | ((i & 0xFF) / 2); 
//    }
//}


void	mtFrameDrawOGL::SetImage(QImage *img)
{
	if(Image!=NULL){
		delete	Image;
	}
	Image=img;
	RepaintAll();
}
void	mtFrameDrawOGL::DelImage(void)
{
	if(Image!=NULL){
		delete	Image;
		Image=NULL;
	}
}

void	mtFrameDrawOGL::SetCrossLineMode(bool mode ,const QColor &Col)
{
	FModeCrossLine	=mode;
	FCrossLineColor	=Col;
}
void	mtFrameDrawOGL::SetMode(DrawingMode Value)
{
	if(FDrawMode==fdLine){
		SData.UData.LineData.x=0;
		SData.UData.LineData.y=0;
		SData.UData.LineData.s=0;
	}
	else if(FDrawMode==fdHalfLine){
		SData.UData.HalfLineData.x=0;
		SData.UData.HalfLineData.y=0;
		SData.UData.HalfLineData.s=0;
	}
	else if(FDrawMode==fdChoppedLine){
		SData.UData.ChoppedLineData.x1=0;
		SData.UData.ChoppedLineData.y1=0;
		SData.UData.ChoppedLineData.x2=0;
		SData.UData.ChoppedLineData.y2=0;
	}
	else if(FDrawMode==fdRectangle){
		SData.UData.RectangleData.x1=0;
		SData.UData.RectangleData.y1=0;
		SData.UData.RectangleData.x2=0;
		SData.UData.RectangleData.y2=0;
	}
	else if(FDrawMode==fdRotRectangle){
		SData.UData.RotRectangleData.cx=0;
		SData.UData.RotRectangleData.cy=0;
		SData.UData.RotRectangleData.rx=0;
		SData.UData.RotRectangleData.ry=0;
		SData.UData.RotRectangleData.s =0;
	}
	else if(FDrawMode==fdCircle){
		SData.UData.CircleData.cx=0;
		SData.UData.CircleData.cy=0;
		SData.UData.CircleData.r=0;
	}
	else if(FDrawMode==fdEllipse || FDrawMode==fdEllipse4){
		SData.UData.EllipseData.cx=0;
		SData.UData.EllipseData.cy=0;
		SData.UData.EllipseData.rx=0;
		SData.UData.EllipseData.ry=0;
	}
	else if(FDrawMode==fdRotEllipse){
		SData.UData.RotEllipseData.cx=0;
		SData.UData.RotEllipseData.cy=0;
		SData.UData.RotEllipseData.rx=0;
		SData.UData.RotEllipseData.ry=0;
		SData.UData.RotEllipseData.s =0;
	}
	else if(FDrawMode==fdArc){
		SData.UData.ArcData.cx=0;
		SData.UData.ArcData.cy=0;
		SData.UData.ArcData.r=0;
		SData.UData.ArcData.s1=0;
		SData.UData.ArcData.s2=0;
	}
	else if(FDrawMode==fdRing){
		SData.UData.ERingData.cx =0;
		SData.UData.ERingData.cy =0;
		SData.UData.ERingData.rx1=0;
		SData.UData.ERingData.ry1=0;
		SData.UData.ERingData.rx2=0;
		SData.UData.ERingData.ry2=0;
	}
	else if(FDrawMode==fdSingleArrow){
		SData.UData.SingleArrowLineData.x1=0;
		SData.UData.SingleArrowLineData.y1=0;
		SData.UData.SingleArrowLineData.x2=0;
		SData.UData.SingleArrowLineData.y2=0;
	}
	else if(FDrawMode==fdDualArrow){
		SData.UData.DualArrowLineData.x1=0;
		SData.UData.DualArrowLineData.y1=0;
		SData.UData.DualArrowLineData.x2=0;
		SData.UData.DualArrowLineData.y2=0;
	}
	else if(FDrawMode==fdFree){
		if(SData.UData.FreeData.points!=NULL){
			SData.UData.FreeData.points->RemoveAll();
			delete SData.UData.FreeData.points;
			}
		SData.UData.FreeData.points=NULL;
		}
	else if(FDrawMode==fdPoly){
		if(SData.UData.PolyData.points!=NULL){
			SData.UData.PolyData.points->RemoveAll();
			delete SData.UData.PolyData.points;
			}
		SData.UData.PolyData.points=NULL;
		}
	else if(FDrawMode==fdMove){
		if(SData.UData.MoveData.points!=NULL){
			SData.UData.MoveData.points->RemoveAll();
			delete SData.UData.MoveData.points;
			}
		SData.UData.MoveData.points=NULL;
		}
	else if(FDrawMode==fdRingArc1 || FDrawMode==fdRingArc4){
		SData.UData.RingArcData.cx=0;
		SData.UData.RingArcData.cy=0;
		SData.UData.RingArcData.rx1=0;
		SData.UData.RingArcData.ry1=0;
		SData.UData.RingArcData.rx2=0;
		SData.UData.RingArcData.ry2=0;
		SData.UData.RingArcData.s1=0;
		SData.UData.RingArcData.s2=0;
	}
	SData.LineWidth	=LineWidth;
	DrawStage=0;
	ChangeMode(Value);

//	  FDrawMode=Value;
	if(FDrawMode==fdLine
	|| FDrawMode==fdChoppedLine
	|| FDrawMode==fdHChoppedLine
	|| FDrawMode==fdVChoppedLine
	|| FDrawMode==fdSingleArrow
	|| FDrawMode==fdDualArrow
	|| FDrawMode==fdArc
	|| FDrawMode==fdArc3
	|| FDrawMode==fdRingArc1
	|| FDrawMode==fdRingArc4)
		FClosedArea=false;
	else if(   FDrawMode==fdRectangle
			|| FDrawMode==fdRotRectangle
			|| FDrawMode==fdCircle
			|| FDrawMode==fdCircle3
			|| FDrawMode==fdEllipse
			|| FDrawMode==fdEllipse4
			|| FDrawMode==fdRotEllipse
			|| FDrawMode==fdRing){
		FClosedArea=true;
	}

	if(FDrawMode==fdFree){
		SData.UData.FreeData.points = new NPListPack<ShapePoint>();
		}
	else if(FDrawMode==fdPoly){
		SData.UData.PolyData.points = new NPListPack<ShapePoint>();
		}
	else if(FDrawMode==fdMove){
		SData.UData.MoveData.points=new NPListPack<ShapePoint>();
		}
	SetStartCursor();
	SData.dtype=Value;
	FOnDrawMode=false;
}

void	mtFrameDrawOGL::InPaint(QPainter &Pnt)
{
	if(Image!=NULL && Image->isNull()==false){
		PaintMutex.lock();
		Pnt.drawImage(movx*ZoomRate, movy*ZoomRate, *Image);
		PaintMutex.unlock();
	}
	emit SignalOnPaint(Pnt);

	if(DrawStage>0){
		PaintMutex.lock();

		Pnt.setPen(FColor);
		Pnt.setBrush(FColor);

		int		x1,y1,x2,y2,x3,y3,x4,y4;
		int		mx1,my1,mx2,my2;
		int		nx1,ny1,nx2,ny2;
		double	s,s1,s2;
		double	s11,s12;
		double	s21,s22;

		int		MinDataGx=-movx;
		int		MinDataGy=-movy;
		int		MaxDataGx=width()/ZoomRate-movx;
		int		MaxDataGy=height()/ZoomRate-movy;


		switch(FDrawMode){
			case fdPoint	:
				DrawLineZoom(Pnt
							,SData.UData.PointData.x+movx,SData.UData.PointData.y+movy
							,SData.UData.PointData.x+movx,SData.UData.PointData.y+movy
							,ZoomRate);
				break;
			case fdLine:
				if(1.75*M_PI<=SData.UData.LineData.s || SData.UData.LineData.s<=0.25*M_PI){
					DrawLineZoom(Pnt
								,MinDataGx+movx	,-tan(SData.UData.LineData.s)*SData.UData.LineData.x			+SData.UData.LineData.y+movy
								,MaxDataGx+movx ,tan(SData.UData.LineData.s)*(MaxDataGx-SData.UData.LineData.x)+SData.UData.LineData.y+movy
								,ZoomRate);
				}
				else if(0.75*M_PI>=SData.UData.LineData.s){
					DrawLineZoom(Pnt
								,(-cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*SData.UData.LineData.y				+SData.UData.LineData.x+movx)	,(MinDataGy+movy)
								,(cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*(MaxDataGy-SData.UData.LineData.y)	+SData.UData.LineData.x+movx)	,(MaxDataGy+movy)
								,ZoomRate);
				}
				else if(1.25*M_PI>=SData.UData.LineData.s){
					DrawLineZoom(Pnt
								,MinDataGx+movx	,(-tan(SData.UData.LineData.s)*SData.UData.LineData.x			+SData.UData.LineData.y+movy)
								,MaxDataGx+movx	,(tan(SData.UData.LineData.s)*(MaxDataGx-SData.UData.LineData.x)+SData.UData.LineData.y+movy)
								,ZoomRate);
				}
				else{
					DrawLineZoom(Pnt
								,(-cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*SData.UData.LineData.y				+SData.UData.LineData.x+movx),(MinDataGy+movy)
								,( cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*(MaxDataGy-SData.UData.LineData.y)	+SData.UData.LineData.x+movx),(MaxDataGy+movy)
								,ZoomRate);
				}
				break;

			case fdHalfLine	:
				if(1.75*M_PI<=SData.UData.HalfLineData.s || SData.UData.HalfLineData.s<=0.25*M_PI){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx,SData.UData.HalfLineData.y+movy
								,MaxDataGx+movx					,tan(SData.UData.HalfLineData.s)*(MaxDataGx-SData.UData.HalfLineData.x)	+SData.UData.HalfLineData.y+movy
								,ZoomRate);
				}
				else if(0.75*M_PI>=SData.UData.HalfLineData.s){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx																										,SData.UData.HalfLineData.y+movy
								,cos(SData.UData.HalfLineData.s)/sin(SData.UData.HalfLineData.s)*(MaxDataGy-SData.UData.HalfLineData.y)	+SData.UData.HalfLineData.x+movx,MaxDataGy+movy
								,ZoomRate);
				}
				else if(1.25*M_PI>=SData.UData.HalfLineData.s){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx,SData.UData.HalfLineData.y+movy
								,MinDataGx+movx					,-tan(SData.UData.HalfLineData.s)*SData.UData.HalfLineData.x	+SData.UData.HalfLineData.y+movy
								,ZoomRate);
				}
				else{
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx																								,SData.UData.HalfLineData.y+movy
								,-cos(SData.UData.HalfLineData.s)/sin(SData.UData.HalfLineData.s)*SData.UData.HalfLineData.y +SData.UData.HalfLineData.x+movx	,MinDataGy+movy
								,ZoomRate);
				}
				break;

			case fdChoppedLine:
			case fdHChoppedLine:
			case fdVChoppedLine:
				DrawLineZoom(Pnt
							,SData.UData.ChoppedLineData.x1+movx	,SData.UData.ChoppedLineData.y1+movy
							,SData.UData.ChoppedLineData.x2+movx	,SData.UData.ChoppedLineData.y2+movy
							,ZoomRate);
				break;

			case fdRectangle:
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y1+movy
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y1+movy
							,ZoomRate);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y1+movy
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y2+movy
							,ZoomRate);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y2+movy
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y2+movy
							,ZoomRate);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y2+movy
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y1+movy
							,ZoomRate);
				break;
			case fdRotRectangle:
				x1=(SData.UData.RotRectangleData.cx-SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y1=(SData.UData.RotRectangleData.cy+SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x2=(SData.UData.RotRectangleData.cx+SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y2=(SData.UData.RotRectangleData.cy-SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x3=(SData.UData.RotRectangleData.cx+SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y3=(SData.UData.RotRectangleData.cy-SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x4=(SData.UData.RotRectangleData.cx-SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y4=(SData.UData.RotRectangleData.cy+SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				DrawLineZoom(Pnt,x1,y1 ,x2,y2	,ZoomRate);
				DrawLineZoom(Pnt,x2,y2 ,x3,y3	,ZoomRate);
				DrawLineZoom(Pnt,x3,y3 ,x4,y4	,ZoomRate);
				DrawLineZoom(Pnt,x4,y4 ,x1,y1	,ZoomRate);
				break;
			case fdCircle:
				Pnt.drawArc( (SData.UData.CircleData.cx-SData.UData.CircleData.r+movx)*ZoomRate	,(SData.UData.CircleData.cy-SData.UData.CircleData.r+movy)*ZoomRate
							,2*SData.UData.CircleData.r*ZoomRate,2*SData.UData.CircleData.r*ZoomRate
							,0,5760);
				break;
			case fdCircle3:
				Pnt.drawArc( (SData.UData.CircleData.cx-SData.UData.CircleData.r+movx)*ZoomRate	,(SData.UData.CircleData.cy-SData.UData.CircleData.r+movy)*ZoomRate
							,2*SData.UData.CircleData.r*ZoomRate,2*SData.UData.CircleData.r*ZoomRate
							,0,5760);
				if(DrawStage==1){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRate-2	,(TmpPoint[0][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==2){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRate-2	,(TmpPoint[0][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRate-2	,(TmpPoint[1][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==3){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRate-2	,(TmpPoint[0][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRate-2	,(TmpPoint[1][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[2][0]+movx)*ZoomRate-2	,(TmpPoint[2][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
				}
				break;
			case fdEllipse:
			case fdEllipse4:
				Pnt.drawArc( (SData.UData.EllipseData.cx-SData.UData.EllipseData.rx+movx)*ZoomRate,(SData.UData.EllipseData.cy-SData.UData.EllipseData.ry+movy)*ZoomRate
							,2*SData.UData.EllipseData.rx*ZoomRate,2*SData.UData.EllipseData.ry*ZoomRate
							,0,5760);
				break;
			case fdRotEllipse:
				DrawRotEllipse(Pnt);
				break;
			case fdArc:
				s=SData.UData.ArcData.s2-SData.UData.ArcData.s1;
				while(s<0){
					s+=2.0*M_PI;
				}

				Pnt.drawArc( (SData.UData.ArcData.cx-SData.UData.ArcData.r+movx)*ZoomRate	,(SData.UData.ArcData.cy-SData.UData.ArcData.r+movy)*ZoomRate
							,2*SData.UData.ArcData.r*ZoomRate,2*SData.UData.ArcData.r*ZoomRate
							//,5760*SData.UData.ArcData.s1/(2*M_PI),5760*SData.UData.ArcData.s2/(2*M_PI));
							,5760*(1.0-SData.UData.ArcData.s2/(2*M_PI))
							,5760*s/(2*M_PI));
				break;
			case fdArc3:
				if(DrawStage==1){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRate-2	,(TmpPoint[0][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==2){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRate-2	,(TmpPoint[0][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRate-2	,(TmpPoint[1][1]+movy)*ZoomRate-2
								,5,5
								,0,5760);
					
					s=SData.UData.ArcData.s2-SData.UData.ArcData.s1;
					while(s<0){
						s+=2.0*M_PI;
					}

					Pnt.drawArc( (SData.UData.ArcData.cx-SData.UData.ArcData.r+movx)*ZoomRate	,(SData.UData.ArcData.cy-SData.UData.ArcData.r+movy)*ZoomRate
								,2*SData.UData.ArcData.r*ZoomRate,2*SData.UData.ArcData.r*ZoomRate
								//,5760*SData.UData.ArcData.s1/(2*M_PI),5760*SData.UData.ArcData.s2/(2*M_PI));
								,5760*(1.0-SData.UData.ArcData.s2/(2*M_PI))
								,5760*s/(2*M_PI));
				}
				break;
			case fdFree:
				for(ShapePoint	*p=SData.UData.FreeData.points->GetFirst();p!=NULL;p=p->GetNext()){
					ShapePoint	*q=p->GetNext();
					if(q==NULL){
						break;
					}
					DrawLineZoom(Pnt
								,p->x+movx	,p->y+movy
								,q->x+movx	,q->y+movy
								,ZoomRate);
				}
				break;
			case fdPoly:
				for(ShapePoint	*p=SData.UData.PolyData.points->GetFirst();p!=NULL;p=p->GetNext()){
					ShapePoint	*q=p->GetNext();
					if(q==NULL){
						DrawLineZoom(Pnt
							,p->x+movx	,p->y+movy
							,rotx+movx	,roty+movy
							,ZoomRate);
						break;
					}
					DrawLineZoom(Pnt
								,p->x+movx	,p->y+movy
								,q->x+movx	,q->y+movy
								,ZoomRate);
				}
				break;
			case fdSingleArrow:
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRate
							 ,(SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate);
				s=GetSita(SData.UData.SingleArrowLineData.x1-SData.UData.SingleArrowLineData.x2
						, SData.UData.SingleArrowLineData.y1-SData.UData.SingleArrowLineData.y2);
				s1=s+M_PI/6;
				s2=s-M_PI/6;
				mx1=SData.UData.SingleArrowLineData.x2+16*cos(s1);
				my1=SData.UData.SingleArrowLineData.y2+16*sin(s1);
				mx2=SData.UData.SingleArrowLineData.x2+16*cos(s2);
				my2=SData.UData.SingleArrowLineData.y2+16*sin(s2);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate
						 	 ,(mx1+movx)*ZoomRate	,(my1+movy)*ZoomRate);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate
							,(mx2+movx)*ZoomRate	,(my2+movy)*ZoomRate);
				break;
			case fdDualArrow:
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRate
							 ,(SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate);
				s1=GetSita(SData.UData.SingleArrowLineData.x1-SData.UData.SingleArrowLineData.x2
						 , SData.UData.SingleArrowLineData.y1-SData.UData.SingleArrowLineData.y2);
				s11=s1+M_PI/6;
				s12=s1-M_PI/6;
				mx1=SData.UData.SingleArrowLineData.x2+16*cos(s11);
				my1=SData.UData.SingleArrowLineData.y2+16*sin(s11);
				mx2=SData.UData.SingleArrowLineData.x2+16*cos(s12);
				my2=SData.UData.SingleArrowLineData.y2+16*sin(s12);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate
							,(mx1+movx)*ZoomRate	,(my1+movy)*ZoomRate);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRate
							,(mx2+movx)*ZoomRate	,(my2+movy)*ZoomRate);
				s2=GetSita(SData.UData.SingleArrowLineData.x2-SData.UData.SingleArrowLineData.x1
						 , SData.UData.SingleArrowLineData.y2-SData.UData.SingleArrowLineData.y1);
				s21=s2+M_PI/6;
				s22=s2-M_PI/6;
				nx1=SData.UData.SingleArrowLineData.x1+16*cos(s21);
				ny1=SData.UData.SingleArrowLineData.y1+16*sin(s21);
				nx2=SData.UData.SingleArrowLineData.x1+16*cos(s22);
				ny2=SData.UData.SingleArrowLineData.y1+16*sin(s22);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRate
							 ,(nx1+movx)*ZoomRate	,(ny1+movy)*ZoomRate);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRate	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRate
							 ,(nx2+movx)*ZoomRate	,(ny2+movy)*ZoomRate);
				break;
			case fdRing:
				DrawRing(Pnt);
				break;
			case fdLongCircle:
				DrawLongCircle(Pnt);
				break;

			case fdRingArc1:
				DrawRingArc(Pnt);
				break;
			case fdRingArc4:
				DrawRingArc(Pnt);
				break;
		}
		PaintMutex.unlock();
	}
	if(FModeCrossLine==true){
		//QPainter	Pnt(this);
		PaintMutex.lock();
		Pnt.setPen(FCrossLineColor);
		Pnt.drawLine(0,NowGy,width(),NowGy);
		Pnt.drawLine(NowGx,0,NowGx,height());
		PaintMutex.unlock();
	}
}

static	void	DrawPixelZoom(QPainter &Pnt ,int x1, int y1 ,double ZoomRate)
{
	int	ix1=x1*ZoomRate;
	int	iy1=y1*ZoomRate;
	int	ix2=(x1+1)*ZoomRate-1;
	int	iy2=(y1+1)*ZoomRate;

	for(int i=iy1;i<iy2;i++){
		Pnt.drawLine(ix1,i,ix2,i);
	}
}

void	mtFrameDrawOGL::DrawLineZoom(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRate)
{
	double	R=GetLineWidth()/2.0;
	if(ZoomRate<2.0){
		if(R*ZoomRate<=0.00001){
			Pnt.drawLine(x1*ZoomRate ,y1*ZoomRate, x2*ZoomRate,y2*ZoomRate);
		}
		else{
			double	dx=x2-x1;
			double	dy=y2-y1;
			double	Len=hypot(dx,dy);
			if(Len>0){
				dx /=Len;
				dy /=Len;
				double	Vx=-dy;
				double	Vy= dx;

				Pnt.drawLine((x1+Vx*R)*ZoomRate ,(y1+Vy*R)*ZoomRate, (x2+Vx*R)*ZoomRate,(y2+Vy*R)*ZoomRate);
				Pnt.drawLine((x1-Vx*R)*ZoomRate ,(y1-Vy*R)*ZoomRate, (x2-Vx*R)*ZoomRate,(y2-Vy*R)*ZoomRate);
				double	s1=-GetSita(Vx,Vy);
				double	s2=RegulateAngle(s1-M_PI);
				double	sc=-GetSita(-dx,-dy);

				double	sp=-RegulateAngle(s1-M_PI/2);
				Pnt.drawArc((x1-R)*ZoomRate, (y1-R)*ZoomRate, R*2*ZoomRate, R*2*ZoomRate, 5760*s2/(2*M_PI), 180*16);
				Pnt.drawArc((x2-R)*ZoomRate, (y2-R)*ZoomRate, R*2*ZoomRate, R*2*ZoomRate, 5760*s1/(2*M_PI), 180*16);
			}
		}
	}
	else{
		if(R*ZoomRate<=0.00001){
			DrawLineZoomInner(Pnt ,x1, y1 ,x2, y2 ,ZoomRate);
		}
		else{
			double	dx=x2-x1;
			double	dy=y2-y1;
			double	Len=hypot(dx,dy);
			if(Len>0){
				dx /=Len;
				dy /=Len;
				double	Vx=-dy;
				double	Vy= dx;
				DrawLineZoomInner(Pnt ,x1+Vx*R, y1+Vy*R ,x2+Vx*R, y2+Vy*R ,ZoomRate);
				DrawLineZoomInner(Pnt ,x1-Vx*R, y1-Vy*R ,x2-Vx*R, y2-Vy*R ,ZoomRate);

				double	s1=-GetSita(Vx,Vy);
				double	s2=RegulateAngle(s1-M_PI);
				double	sc=-GetSita(-dx,-dy);

				double	sp=-RegulateAngle(s1-M_PI/2);
				Pnt.drawArc((x1-R)*ZoomRate, (y1-R)*ZoomRate, R*2*ZoomRate, R*2*ZoomRate, 5760*s2/(2*M_PI), 180*16);
				Pnt.drawArc((x2-R)*ZoomRate, (y2-R)*ZoomRate, R*2*ZoomRate, R*2*ZoomRate, 5760*s1/(2*M_PI), 180*16);
			}
		}
	}

}

void	mtFrameDrawOGL::DrawLineZoomInner(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRate)
{
	int lastx=99999999 ,lasty=99999999;
	int x,y;		
	int dx=x2-x1;
	int dy=y2-y1;
	if(abs(dx)>abs(dy)){
	    if(dx>0){
	        for(x=0;x<dx;x++){
	            y=x*dy/dx+y1;
	            if(lastx!=x1+x || lasty!=y){
	                lastx=x1+x;
	                lasty=y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRate);
				}
			}
		}
	    else{
	        for(x=0;x>dx;x--){
	            y=x*dy/dx+y1;
	            if(lastx!=x1+x || lasty!=y){
	                lastx=x1+x;
	                lasty=y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRate);
				}
			}
		}
	}
	else{
	    if(dy>0){
	        for(y=0;y<dy;y++){
	            x=y*dx/dy+x1;
	            if(lastx!=x || lasty!=y1+y){
	                lastx=x;
	                lasty=y1+y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRate);
				}
			}
		}
	    else if(dy!=0){
	        for(y=0;y>dy;y--){
	            x=y*dx/dy+x1;
	            if(lastx!=x || lasty!=y1+y){
	                lastx=x;
	                lasty=y1+y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRate);
				}
			}
		}
	    else if(lastx!=x1 || lasty!=y1){
			DrawPixelZoom(Pnt ,x1,y1 ,ZoomRate);
	        lastx=x1;
	        lasty=y1;
		}
	}
}


static	bool	GetRotEllipseXY(double Cx,double Cy,double rx,double ry
									,double c,double s
									,double a,double b
									,double &X1,double &Y1,double &X2,double &Y2)
{
	double	Rx2=rx*rx;
	double	Ry2=ry*ry;
	double	D=(b*c+a*s)*(b*c+a*s)*Rx2 + (a*c-b*s)*(a*c-b*s)*Ry2;
	if(D<=0){
		return false;
	}
	D=sqrt(D);
	X1=-a*rx*ry/D +Cx;
	Y1=-b*rx*ry/D +Cy;
	X2= a*rx*ry/D +Cx;
	Y2= b*rx*ry/D +Cy;

	return true;
}

void	mtFrameDrawOGL::DrawRotEllipse(QPainter &Pnt)
{
	int	N=1000;
	double	LastX1,LastY1;
	double	LastX2,LastY2;
	double	Cx=(SData.UData.RotEllipseData.cx+movx)*ZoomRate;
	double	Cy=(SData.UData.RotEllipseData.cy+movy)*ZoomRate;
	double	Rx=SData.UData.RotEllipseData.rx*ZoomRate;
	double	Ry=SData.UData.RotEllipseData.ry*ZoomRate;
	if(N>2*Rx){
		N=2*Rx+1;
	}
	if(N>2*Ry){
		N=2*Ry+1;
	}
	if(N<10){
		N=10;
	}
	double	s=sin(-SData.UData.RotEllipseData.s);
	double	c=cos(-SData.UData.RotEllipseData.s);

	GetRotEllipseXY(Cx,Cy,Rx+1,Ry+1,c,s,1,0,LastX1,LastY1,LastX2,LastY2);
//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=1;i<N;i++){
			double	l=i*M_PI/N;
			double	X1,Y1;
			double	X2,Y2;
			if(GetRotEllipseXY(Cx,Cy,Rx,Ry,c,s,cos(l),sin(l),X1,Y1,X2,Y2)==true){
				double	L1=hypot(LastX1-X1,LastY1-Y1);
				double	L2=hypot(LastX1-X2,LastY1-Y2);
				if(L2<L1){
					swap(X1,X2);
					swap(Y1,Y2);
				}
				Pnt.drawLine(LastX1,LastY1,X1,Y1);
				Pnt.drawLine(LastX2,LastY2,X2,Y2);
				LastX1=X1;
				LastY1=Y1;
				LastX2=X2;
				LastY2=Y2;
			}
		}
//	}
}

void	mtFrameDrawOGL::DrawRing(QPainter &Pnt)
{
	double	Cx=(SData.UData.ERingData.cx+movx)*ZoomRate;
	double	Cy=(SData.UData.ERingData.cy+movy)*ZoomRate;
	double	Rx1=SData.UData.ERingData.rx1*ZoomRate;
	double	Ry1=SData.UData.ERingData.ry1*ZoomRate;
	double	Rx2=SData.UData.ERingData.rx2*ZoomRate;
	double	Ry2=SData.UData.ERingData.ry2*ZoomRate;

	if(Ry2<Ry1){
		swap(Rx1,Rx2);
		swap(Ry1,Ry2);
	}
	double	Ry22=Ry2*Ry2;
	double	Ry11=Ry1*Ry1;
	double	Rx22=Rx2*Rx2;
	double	Rx11=Rx1*Rx1;

	int	ILen=Ry2*2+1;
//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=0;i<ILen;i++){
			int	y=i-Ry2;
		//for(int y=-Ry2;y<=Ry2;y++){
			if(y<=-Ry1 || Ry1<=y){

#if 1 // 20100210
				double D;

				if (0.0 == Ry22)
					D = Rx22;
				else
					D = Rx22 - Rx22 * y * y / Ry22;
#else
				double	D=Rx22-Rx22*y*y/Ry22;
#endif

				if(D>=0){
					D=sqrt(D);
					double	X1=Cx-D;
					double	X2=Cx+D;
					Pnt.drawLine(X1,Cy+y,X2,Cy+y);
				}
			}
			else{

#if 1 // 20100210
				double D2;

				if (0.0 == Ry22)
					D2 = Rx22;
				else
					D2 = Rx22 - Rx22 * y * y / Ry22;
#else
				double	D2=Rx22-Rx22*y*y/Ry22;
#endif

				if(D2>=0){
					D2=sqrt(D2);
					double	X21=Cx-D2;
					double	X22=Cx+D2;

#if 1 // 20100210
					double D1;

					if (0.0 == Ry11)
						D1 = Rx11;
					else
						D1 = Rx11 - Rx11 * y * y / Ry11;
#else
					double	D1=Rx11-Rx11*y*y/Ry11;
#endif

					if(D1>=0){
						D1=sqrt(D1);
						double	X11=Cx-D1;
						double	X12=Cx+D1;
						Pnt.drawLine(X11,Cy+y,X21,Cy+y);
						Pnt.drawLine(X12,Cy+y,X22,Cy+y);
					}
				}
			}
		}
//	}
}

void	mtFrameDrawOGL::DrawLongCircle(QPainter &Pnt)
{
	double	Cx1=(SData.UData.LongCircleData.cx1+movx)*ZoomRate;
	double	Cy1=(SData.UData.LongCircleData.cy1+movy)*ZoomRate;
	double	Cx2=(SData.UData.LongCircleData.cx2+movx)*ZoomRate;
	double	Cy2=(SData.UData.LongCircleData.cy2+movy)*ZoomRate;
	double	dx=SData.UData.LongCircleData.cx2-SData.UData.LongCircleData.cx1;
	double	dy=SData.UData.LongCircleData.cy2-SData.UData.LongCircleData.cy1;
	double	R=SData.UData.LongCircleData.r;
	double	r=SData.UData.LongCircleData.r*ZoomRate;;
	double	L=hypot(dx,dy);
	if(L>0.00001){
		double	hx=-dy*R/L;
		double	hy= dx*R/L;
		double	Rx11=(SData.UData.LongCircleData.cx1+hx+movx)*ZoomRate;
		double	Ry11=(SData.UData.LongCircleData.cy1+hy+movy)*ZoomRate;
		double	Rx12=(SData.UData.LongCircleData.cx2+hx+movx)*ZoomRate;
		double	Ry12=(SData.UData.LongCircleData.cy2+hy+movy)*ZoomRate;
		double	Rx21=(SData.UData.LongCircleData.cx1-hx+movx)*ZoomRate;
		double	Ry21=(SData.UData.LongCircleData.cy1-hy+movy)*ZoomRate;
		double	Rx22=(SData.UData.LongCircleData.cx2-hx+movx)*ZoomRate;
		double	Ry22=(SData.UData.LongCircleData.cy2-hy+movy)*ZoomRate;

		double	Ky11=(SData.UData.LongCircleData.cy1-SData.UData.LongCircleData.r+movy)*ZoomRate;
		double	Ky12=(SData.UData.LongCircleData.cy1+SData.UData.LongCircleData.r+movy)*ZoomRate;
		double	Ky21=(SData.UData.LongCircleData.cy2-SData.UData.LongCircleData.r+movy)*ZoomRate;
		double	Ky22=(SData.UData.LongCircleData.cy2+SData.UData.LongCircleData.r+movy)*ZoomRate;

		int	YMin=min(Ky11,Ky21);
		int	YMax=max(Ky12,Ky22);

		for(int y=YMin;y<=YMax;y++){
			int	gminx=99999999,gmaxx=-99999999;
			if(-r<=(y-Cy1) && (y-Cy1)<=r){
				double	x=sqrt(r*r-(y-Cy1)*(y-Cy1));
				gminx=Cx1-x;
				gmaxx=Cx1+x;
			}
			long	X;
			if(GetCrossHalfInnerPoint(Rx11,Ry11,Rx12,Ry12,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(GetCrossHalfInnerPoint(Rx21,Ry21,Rx22,Ry22,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(-r<=(y-Cy2) && (y-Cy2)<=r){
				double	x=sqrt(r*r-(y-Cy2)*(y-Cy2));
				if(Cx2-x<gminx){
					gminx=Cx2-x;
				}
				if(Cx2+x>gmaxx){
					gmaxx=Cx2+x;
				}
			}
			if(gminx<=gmaxx){
				Pnt.drawLine(gminx,y,gmaxx,y);
			}
		}
	}
	else{
		Pnt.drawArc( (SData.UData.LongCircleData.cx1-SData.UData.LongCircleData.r+movx)*ZoomRate	
					,(SData.UData.LongCircleData.cy1-SData.UData.LongCircleData.r+movy)*ZoomRate
					,2*SData.UData.LongCircleData.r*ZoomRate,2*SData.UData.LongCircleData.r*ZoomRate
					,0,5760);
	}
}

static	int	CutLineByAngle(int X1,int X2,int Y
					,int Cx,int Cy ,double s1,double s2 ,double CosS1 ,double SinS1,double CosS2 ,double SinS2
					,int P[2][4])
{
	/*
		constraint s1	:	SinS1*(x-cx)-CosS1(y-cy)=0;
		constraint s2	:	SinS2*(x-cx)-CosS2(y-cy)=0;
	*/
	if(X1>X2)	swap(X1,X2);

	double	ts1=GetSita(X1-Cx,Y-Cy);
	double	ts2=GetSita(X2-Cx,Y-Cy);
	bool	b1=IsInsideAngle(ts1,s1,s2);
	bool	b2=IsInsideAngle(ts2,s1,s2);
	if(b1==true && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				P[1][0]=hX2;
				P[1][1]=Y;
				P[1][2]=X2;
				P[1][3]=Y;
				return 2;
			}
		}
		P[0][0]=X1;
		P[0][1]=Y;
		P[0][2]=X2;
		P[0][3]=Y;
		return 1;
	}
	if(b1==true && b2==false){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX1;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	if(b1==false && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=hX2;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	else{
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
			}
		}
	}
	return 0;
}


void	mtFrameDrawOGL::DrawRingArc(QPainter &Pnt)
{
	double	Cx=(SData.UData.RingArcData.cx+movx)*ZoomRate;
	double	Cy=(SData.UData.RingArcData.cy+movy)*ZoomRate;
	double	Rx1=SData.UData.RingArcData.rx1*ZoomRate;
	double	Ry1=SData.UData.RingArcData.ry1*ZoomRate;
	double	Rx2=SData.UData.RingArcData.rx2*ZoomRate;
	double	Ry2=SData.UData.RingArcData.ry2*ZoomRate;
	double	S1 =SData.UData.RingArcData.s1;
	double	S2 =SData.UData.RingArcData.s2;

	double	CosS1=cos(S1);
	double	SinS1=sin(S1);
	double	CosS2=cos(S2);
	double	SinS2=sin(S2);

	if(Ry2<Ry1){
		swap(Rx1,Rx2);
		swap(Ry1,Ry2);
	}
	double	Ry22=Ry2*Ry2;
	double	Ry11=Ry1*Ry1;
	double	Rx22=Rx2*Rx2;
	double	Rx11=Rx1*Rx1;

	int	ILen=Ry2*2+1;
	for(int i=0;i<ILen;i++){
		int	y=i-Ry2;
		if(y<=-Ry1 || Ry1<=y){
			double D;

			if (0.0 == Ry22)
				D = Rx22;
			else
				D = Rx22 - Rx22 * y * y / Ry22;

			if(D>=0){
				D=sqrt(D);
				double	X1=Cx-D;
				double	X2=Cx+D;

				int	P[2][4];
				int	N=CutLineByAngle(X1,X2,Cy+y
									,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
									,P);
				for(int k=0;k<N;k++){
					Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
				}
			}
		}
		else{
			double D2;

			if (0.0 == Ry22)
				D2 = Rx22;
			else
				D2 = Rx22 - Rx22 * y * y / Ry22;

			if(D2>=0){
				D2=sqrt(D2);
				double	X21=Cx-D2;
				double	X22=Cx+D2;

				double D1;

				if (0.0 == Ry11)
					D1 = Rx11;
				else
					D1 = Rx11 - Rx11 * y * y / Ry11;

				if(D1>=0){
					D1=sqrt(D1);
					double	X11=Cx-D1;
					double	X12=Cx+D1;
					int	P[2][4];
					int	N;
					N=CutLineByAngle(X11,X21,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
					}
					N=CutLineByAngle(X12,X22,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
					}
				}
			}
		}
	}
}

void mtFrameDrawOGL::SetClosedArea(bool Value)
{
	if(FDrawMode==fdFree
	|| FDrawMode==fdPoly){
		FClosedArea=Value;
	}

	else
	if(FDrawMode==fdRectangle
	|| FDrawMode==fdRotRectangle
	|| FDrawMode==fdCircle
	|| FDrawMode==fdCircle3
	|| FDrawMode==fdEllipse
	|| FDrawMode==fdEllipse4
	|| FDrawMode==fdRotEllipse){
		FClosedArea=true;
	}
	else{
		FClosedArea=false;
	}
}



bool	mtFrameDrawOGL::Save(QIODevice *file)
{
	if(SData.Save(file)==false)
		return(false);
	if(file->write((const char *)&DrawStage,sizeof(DrawStage))!=sizeof(DrawStage))
		return(false);
	int32	r=FColor.red();
	if(file->write((const char *)&r,sizeof(r))!=sizeof(r))
		return(false);
	int32	g=FColor.green();
	if(file->write((const char *)&g,sizeof(g))!=sizeof(g))
		return(false);
	int32	b=FColor.blue();
	if(file->write((const char *)&b,sizeof(b))!=sizeof(b))
		return(false);
	int32	a=FColor.alpha();
	if(file->write((const char *)&a,sizeof(a))!=sizeof(a))
		return(false);
	if(file->write((const char *)&FDrawMode,sizeof(FDrawMode))!=sizeof(FDrawMode))
		return(false);
	if(file->write((const char *)&FClosedArea,sizeof(FClosedArea))!=sizeof(FClosedArea))
		return(false);
	if(file->write((const char *)&FCancelDraw,sizeof(FCancelDraw))!=sizeof(FCancelDraw))
		return(false);
	if(file->write((const char *)&FOnDrawMode,sizeof(FOnDrawMode))!=sizeof(FOnDrawMode))
		return(false);
	if(file->write((const char *)&rotx,sizeof(rotx))!=sizeof(rotx))
		return(false);
	if(file->write((const char *)&roty,sizeof(roty))!=sizeof(roty))
		return(false);

	return(true);
}
bool	mtFrameDrawOGL::Load(QIODevice *file)
{
	if(SData.Load(file)==false)
		return(false);
	if(file->read((char *)&DrawStage,sizeof(DrawStage))!=sizeof(DrawStage))
		return(false);
	int32	r,g,b,a;
	if(file->read((char *)&r,sizeof(r))!=sizeof(r))
		return(false);
	if(file->read((char *)&g,sizeof(g))!=sizeof(g))
		return(false);
	if(file->read((char *)&b,sizeof(b))!=sizeof(b))
		return(false);
	if(file->read((char *)&a,sizeof(a))!=sizeof(a))
		return(false);
	FColor.setRgb(r,g,b,a);
	if(file->read((char *)&FDrawMode,sizeof(FDrawMode))!=sizeof(FDrawMode))
		return(false);
	if(file->read((char *)&FClosedArea,sizeof(FClosedArea))!=sizeof(FClosedArea))
		return(false);
	if(file->read((char *)&FCancelDraw,sizeof(FCancelDraw))!=sizeof(FCancelDraw))
		return(false);
	if(file->read((char *)&FOnDrawMode,sizeof(FOnDrawMode))!=sizeof(FOnDrawMode))
		return(false);
	if(file->read((char *)&rotx,sizeof(rotx))!=sizeof(rotx))
		return(false);
	if(file->read((char *)&roty,sizeof(roty))!=sizeof(roty))
		return(false);

	return(true);
}


bool mtFrameDrawOGL::IsPixelEffective(int x ,int y)
{
	return(true);
}

bool	mtFrameDrawOGL::Drawing(void)
{
	if(DrawStage==0)
		return(false);
	return(true);
}

void	mtFrameDrawOGL::PutPixelOnly(int x ,int y ,QColor &col)
{
	QPainter	Pnt(this);

	QPen	mPen(FColor);
	Pnt.setPen(mPen);
	Pnt.drawPoint(x,y);
}

void	mtFrameDrawOGL::GetCanvasToUniverse(int gx, int gy ,int &ux, int &uy)	const
{
	ux=gx/ZoomRate-movx;
	uy=gy/ZoomRate-movy;
}

void mtFrameDrawOGL::mousePressEvent ( QMouseEvent *Ev )
{
	DblClickMode=false;
	CancelClicked=false;
	bool ShiftKey;

	int	X=Ev->x();
	int	Y=Ev->y();
	NowGx=X;
	NowGx=Y;
	MousePressX=X;
	MousePressY=Y;
	ClickedTime=GetComputerMiliSec();

	// �t���O���擾(���E�N���b�N�A�V�t�g�L�[)
	LeftClicked		= ((Ev->buttons() & Qt::LeftButton)!=0) ? true : false;
	RightClicked	= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
	ShiftKey		= ((Ev->modifiers() & Qt::ShiftModifier)!=0) ? true : false;

	if(LeftClicked){
		bool	mvalid=true;
		mtMousePoint(Ev,X,Y,mvalid);
		if(mvalid==false){
			return;
		}
	}

	if((ShiftKey==true) && (LeftClicked==true)){
		if(GetMode()!=fdNone
		&& GetMode()!=fdPoint){
			mtMouseLDown(Ev,X,Y);
		}
		return;
	}

	int uX, uY;
	GetCanvasToUniverse(X, Y ,uX, uY);
	if(LeftClicked){
		LastMouseDownPointX=uX;
		LastMouseDownPointY=uY;
		LastShitX=X;
		LastShitY=Y;
		ShiftingMode=false;
		emit	SignalJustMouseLPress(uX,uY);
	}
	else
	if((ShiftKey==true) && (RightClicked==true)){
		//mtMouseRDown(Ev, X,Y);
		return;
	}
	else
	if(RightClicked==true){
		emit	SignalJustMouseRPress(uX,uY);
		return;
	}
}

void	mtFrameDrawOGL::SetEnableShiftImage(bool b)
{
	FEnableShiftImage=b;
}
bool	mtFrameDrawOGL::GetEnableShiftImage(void)	const
{
	return FEnableShiftImage;
}

void	mtFrameDrawOGL::mouseDoubleClickEvent ( QMouseEvent * Ev )
{
	DblClickMode=true;
	int	X=Ev->x();
	int	Y=Ev->y();
	MousePressX=X;
	MousePressY=Y;

	LeftClicked = ((Ev->buttons() & Qt::LeftButton)!=0) ? true : false;
	RightClicked= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
}
void	mtFrameDrawOGL::mouseMoveEvent ( QMouseEvent * Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
	NowGx=X;
	NowGy=Y;
	double	A,B,C;
	DrawingMode	CurrentMode=FDrawMode;

	if(CancelClicked==true){
		return;
	}

	bool	mvalid=true;
	mtMousePoint(Ev,X,Y,mvalid);
	if(mvalid==false){
		return;
		}
	mtMouseMove(Ev, X, Y);

	int uX, uY;
	GetCanvasToUniverse(X, Y ,uX, uY);

	if((Ev->buttons()&Qt::LeftButton)!=0){
		if(abs(uX-LastMouseDownPointX)*ZoomRate>10 || abs(uY-LastMouseDownPointY)*ZoomRate>10 || ShiftingMode==true){
			if(GetComputerMiliSec()-ClickedTime>ImageShiftDelay){
				if(FEnableShiftImage==true){
					int	Dx=X-LastShitX;
					int	Dy=Y-LastShitY;
					ShiftingMode=true;
					emit	SignalShiftCanvas(Dx,Dy);
					LastShitX=X;
					LastShitY=Y;
					return;
				}
			}
		}
		RepaintAll();
	}

	if(DrawStage==1){
		switch(CurrentMode){
			case fdLine:
				SData.UData.LineData.s=GetSita(uX-SData.UData.LineData.x,uY-SData.UData.LineData.y);
				emit	SignalDrawMessage(QStringList("Angle")
										 ,QStringList(QString::number(SData.UData.LineData.s*180.0/M_PI,'f',3)));
				break;
			case fdHalfLine:
				SData.UData.HalfLineData.s=GetSita(uX-SData.UData.HalfLineData.x,uY-SData.UData.HalfLineData.y);
				emit	SignalDrawMessage(QStringList("Length")<<QString("Angle")
					,QStringList( QString::number(hypot(uX-SData.UData.HalfLineData.x,uY-SData.UData.HalfLineData.y),'f',2))
								<<QString::number(SData.UData.HalfLineData.s*180.0/M_PI,'f',3));
				break;
			case fdChoppedLine:
				SData.UData.ChoppedLineData.x2=uX;
				SData.UData.ChoppedLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdHChoppedLine:
				SData.UData.ChoppedLineData.x2=uX;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdVChoppedLine:
				SData.UData.ChoppedLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdSingleArrow:
				SData.UData.SingleArrowLineData.x2=uX;
				SData.UData.SingleArrowLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.SingleArrowLineData.x2-SData.UData.SingleArrowLineData.x1))
							   <<QString::number(SData.UData.SingleArrowLineData.y2-SData.UData.SingleArrowLineData.y1));
				break;
			case fdDualArrow:
				SData.UData.DualArrowLineData.x2=uX;
				SData.UData.DualArrowLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.DualArrowLineData.x2-SData.UData.DualArrowLineData.x1,'f',1))
							   <<QString::number(SData.UData.DualArrowLineData.y2-SData.UData.DualArrowLineData.y1,'f',1));
				break;
			case fdRectangle:
				SData.UData.RectangleData.x2=uX;
				SData.UData.RectangleData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList( QString::number(SData.UData.RectangleData.x2-SData.UData.RectangleData.x1))
								<<QString::number(SData.UData.RectangleData.y2-SData.UData.RectangleData.y1));
				break;
			case fdRotRectangle:
				SData.UData.RotRectangleData.rx=fabs(uX-SData.UData.RotRectangleData.cx);
				SData.UData.RotRectangleData.ry=fabs(uY-SData.UData.RotRectangleData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotRectangleData.rx,'f',2))
							   <<QString::number(SData.UData.RotRectangleData.ry,'f',2)
							   <<QString("0"));
				break;
			case fdCircle:
				SData.UData.CircleData.r=hypot(uX-SData.UData.CircleData.cx
											 , uY-SData.UData.CircleData.cy);
				emit	SignalDrawMessage(QStringList("Radius")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdCircle3:
				SData.UData.CircleData.cx=(uX+TmpPoint[0][0])/2;
				SData.UData.CircleData.cy=(uY+TmpPoint[0][1])/2;
				SData.UData.CircleData.r=hypot(uX-SData.UData.CircleData.cx
											 , uY-SData.UData.CircleData.cy);
				emit	SignalDrawMessage(QStringList("Second Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdEllipse:
				SData.UData.EllipseData.rx=fabs(uX-SData.UData.EllipseData.cx);
				SData.UData.EllipseData.ry=fabs(uY-SData.UData.EllipseData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")
					,QStringList(QString::number(SData.UData.EllipseData.rx,'f',2))
							   <<QString::number(SData.UData.EllipseData.ry,'f',2));
				break;
			case fdEllipse4:
				SData.UData.EllipseData.cx=TmpPoint[0][0];
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+uY)/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-uY)/2.0;
				emit	SignalDrawMessage(QStringList("Top-Y")<<QString("Bottom-Y")
							,QStringList(QString::number(uY,'f',2))
							   <<QString::number(uY,'f',2));
				break;
			case fdRotEllipse:
				SData.UData.RotEllipseData.rx=fabs(uX-SData.UData.RotEllipseData.cx);
				SData.UData.RotEllipseData.ry=fabs(uY-SData.UData.RotEllipseData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotEllipseData.rx,'f',2))
							   <<QString::number(SData.UData.RotEllipseData.ry,'f',2)
							   <<QString("0"));
				break;
			case fdArc:
				SData.UData.ArcData.r=hypot(uX-SData.UData.ArcData.cx
										  , uY-SData.UData.ArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList(QString::number(SData.UData.ArcData.r,'f',2))
								<<QString("0")
								<<QString("360"));
				break;
			case fdArc3:
				emit	SignalDrawMessage(QStringList("Second Point-X")<<QString("Second Point-Y")
					,QStringList(QString::number(uX,'f',2))
								<<QString::number(uY,'f',2));
				break;
			case fdFree:
				if(SData.UData.FreeData.points!=NULL){
					ShapePoint	*q=SData.UData.FreeData.points->GetLast();
					if(q!=NULL && (q->x!=uX || q->y!=uY)){
						SData.UData.FreeData.points->AppendList(new ShapePoint(uX,uY));
						emit	SignalDrawMessage(QStringList("Dx")<<QString("Dy")
								,QStringList( QString::number(uX-SData.UData.FreeData.points->GetFirst()->x))
											<<QString::number(uY-SData.UData.FreeData.points->GetFirst()->y));
					}
				}
				rotx=uX;
				roty=uY;
				break;
			case fdPoly:
				if(SData.UData.PolyData.points!=NULL){
					ShapePoint	*q=SData.UData.PolyData.points->GetLast();
					if(q!=NULL){
						emit	SignalDrawMessage(QStringList("Dx")<<QString("Dy")
								,QStringList( QString::number(uX-q->x))
											<<QString::number(uY-q->y));
					}
				}
				rotx=uX;
				roty=uY;
				break;
			/*
			case fdMove:
				MovePoints(X-rotx ,Y-roty);
				rotx=X;
				roty=Y;
				break;
			*/
			case fdRing:
				SData.UData.ERingData.rx1=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry1=fabs(uY-SData.UData.ERingData.cy);
				SData.UData.ERingData.rx2=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry2=fabs(uY-SData.UData.ERingData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")
					,QStringList( QString::number(SData.UData.ERingData.rx1,'f',2))
								<<QString::number(SData.UData.ERingData.ry1,'f',2)
								<<QString::number(SData.UData.ERingData.rx2,'f',2)
								<<QString::number(SData.UData.ERingData.ry2,'f',2));
				break;
			case fdLongCircle:
				SData.UData.LongCircleData.cx1=(uX+TmpPoint[0][0])/2;
				SData.UData.LongCircleData.cy1=(uY+TmpPoint[0][1])/2;
				SData.UData.LongCircleData.cx2=SData.UData.LongCircleData.cx1;
				SData.UData.LongCircleData.cy2=SData.UData.LongCircleData.cy1;
				SData.UData.LongCircleData.r  =hypot(uX-SData.UData.LongCircleData.cx1
													,uY-SData.UData.LongCircleData.cy1);
				emit	SignalDrawMessage(QStringList("Second Point")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.rx1=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry1=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")
					,QStringList(QString::number(SData.UData.RingArcData.rx1,'f',2))
							   <<QString::number(SData.UData.RingArcData.ry1,'f',2));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=TmpPoint[0][0];
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+uY)/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-uY)/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;
				emit	SignalDrawMessage(QStringList("Top-Y")<<QString("Bottom-Y")
										,QStringList(QString::number(uY,'f',2))
										<<QString::number(uY,'f',2));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==2){
		switch(CurrentMode){
			case fdCircle3:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.CircleData.cx,SData.UData.CircleData.cy,SData.UData.CircleData.r);
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdEllipse4:
				SData.UData.EllipseData.cx=(uX+TmpPoint[0][0])/2.0;
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.rx=abs(uX-TmpPoint[0][0])/2.0;

				emit	SignalDrawMessage(QStringList("Left-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
			case fdRotRectangle:
				SData.UData.RotRectangleData.s=GetSita(uX -SData.UData.RotRectangleData.cx	,uY -SData.UData.RotRectangleData.cy)
													-GetSita(rotx-SData.UData.RotRectangleData.cx,roty-SData.UData.RotRectangleData.cy);
				SData.UData.RotRectangleData.s=RegulateAngle(SData.UData.RotRectangleData.s);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotRectangleData.rx,'f',2))
							   <<QString::number(SData.UData.RotRectangleData.ry,'f',2)
							   <<QString::number(SData.UData.RotRectangleData.s*180.0/M_PI,'f',3));
				break;
			case fdRotEllipse:
				SData.UData.RotEllipseData.s=GetSita(uX -SData.UData.RotEllipseData.cx	,uY -SData.UData.RotEllipseData.cy)
													-GetSita(rotx-SData.UData.RotEllipseData.cx,roty-SData.UData.RotEllipseData.cy);
				SData.UData.RotEllipseData.s=RegulateAngle(SData.UData.RotEllipseData.s);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotEllipseData.rx,'f',2))
							   <<QString::number(SData.UData.RotEllipseData.ry,'f',2)
							   <<QString::number(SData.UData.RotEllipseData.s*180.0/M_PI,'f',3));
				break;
			case fdArc:
				SData.UData.ArcData.s1=GetSita(uX -SData.UData.ArcData.cx	,uY -SData.UData.ArcData.cy)
											-GetSita(rotx-SData.UData.ArcData.cx,roty-SData.UData.ArcData.cy);
				SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.ArcData.r,'f',2))
								<<QString::number(SData.UData.ArcData.s1*180.0/M_PI,'f',3)
								<<QString("360"));
				break;
			case fdArc3:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.ArcData.cx,SData.UData.ArcData.cy,SData.UData.ArcData.r);
				A=TmpPoint[1][1]-TmpPoint[0][1];
				B=-(TmpPoint[1][0]-TmpPoint[0][0]);
				C=-TmpPoint[0][0]*TmpPoint[1][1]+TmpPoint[1][0]*TmpPoint[0][1];
				if(A*uX+B*uY+C>=0){
					SData.UData.ArcData.s1=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
					SData.UData.ArcData.s2=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
				}
				else{
					SData.UData.ArcData.s2=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
					SData.UData.ArcData.s1=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
				}
				SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
				SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdRing:
				SData.UData.ERingData.rx2=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry2=fabs(uY-SData.UData.ERingData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")
					,QStringList( QString::number(SData.UData.ERingData.rx1,'f',2))
								<<QString::number(SData.UData.ERingData.ry1,'f',2)
								<<QString::number(SData.UData.ERingData.rx2,'f',2)
								<<QString::number(SData.UData.ERingData.ry2,'f',2));
				break;
			case fdLongCircle:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.LongCircleData.cx1,SData.UData.LongCircleData.cy1,SData.UData.LongCircleData.r);
				SData.UData.LongCircleData.cx2=SData.UData.LongCircleData.cx1;
				SData.UData.LongCircleData.cy2=SData.UData.LongCircleData.cy1;
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.s1=GetSita(uX  -SData.UData.RingArcData.cx	,uY -SData.UData.RingArcData.cy)
										  -GetSita(rotx-SData.UData.RingArcData.cx ,roty-SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s1=RegulateAngle(SData.UData.RingArcData.s1);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString("360"));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=(uX+TmpPoint[0][0])/2.0;
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.rx1=abs(uX-TmpPoint[0][0])/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;

				emit	SignalDrawMessage(QStringList("Left-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==3){
		switch(CurrentMode){
			case fdEllipse4:
				SData.UData.EllipseData.cx=(TmpPoint[2][0]+uX)/2.0;
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.rx=abs(TmpPoint[2][0]-uX)/2.0;
				emit	SignalDrawMessage(QStringList("Right-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
			case fdArc:
				SData.UData.ArcData.s2=GetSita(uX	-SData.UData.ArcData.cx,uY	 -SData.UData.ArcData.cy)
								-GetSita(rotx-SData.UData.ArcData.cx,roty-SData.UData.ArcData.cy);
				SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.ArcData.r,'f',2))
								<<QString::number(SData.UData.ArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.ArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdLongCircle:
				SData.UData.LongCircleData.cx2=uX;
				SData.UData.LongCircleData.cy2=uY;
				emit	SignalDrawMessage(QStringList("Other circle")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.s2=GetSita(uX	-SData.UData.RingArcData.cx,uY	 -SData.UData.RingArcData.cy)
										  -GetSita(rotx -SData.UData.RingArcData.cx,roty -SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s2=RegulateAngle(SData.UData.RingArcData.s2);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=(TmpPoint[2][0]+uX)/2.0;
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.rx1=abs(TmpPoint[2][0]-uX)/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;
				emit	SignalDrawMessage(QStringList("Right-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==4){
		switch(CurrentMode){
			case fdRingArc1:
				SData.UData.RingArcData.rx2=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry2=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.rx2,'f',2)
								<<QString::number(SData.UData.RingArcData.ry2,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.s1=GetSita(uX  -SData.UData.RingArcData.cx	,uY -SData.UData.RingArcData.cy)
										  -GetSita(rotx-SData.UData.RingArcData.cx ,roty-SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s1=RegulateAngle(SData.UData.RingArcData.s1);
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
										,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
											<<QString::number(SData.UData.RingArcData.ry1,'f',2)
											<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
											<<QString("360"));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==5){
		switch(CurrentMode){
			case fdRingArc1:
				SData.UData.RingArcData.rx2=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry2=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.rx2,'f',2)
								<<QString::number(SData.UData.RingArcData.ry2,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.s2=GetSita(uX	-SData.UData.RingArcData.cx,uY	 -SData.UData.RingArcData.cy)
										  -GetSita(rotx -SData.UData.RingArcData.cx,roty -SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s2=RegulateAngle(SData.UData.RingArcData.s2);
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==6){
		switch(CurrentMode){
			case fdRingArc4:
				SData.UData.RingArcData.ry2=abs(SData.UData.RingArcData.cy-uY);
				SData.UData.RingArcData.rx2=SData.UData.RingArcData.ry2;
				emit	SignalDrawMessage(QStringList("Top-Y2")<<QString("Bottom-Y2")
										,QStringList(QString::number(uY,'f',2))
										<<QString::number(uY,'f',2));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==7){
		switch(CurrentMode){
			case fdRingArc4:
				SData.UData.RingArcData.rx2=abs(SData.UData.RingArcData.cx-uX);
				emit	SignalDrawMessage(QStringList("Right-X2")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else{
		if(FModeRepaintOnMouseMove==true){
			update();
		}
	}
}
void	mtFrameDrawOGL::RepaintAll(void)
{
	update();
}

void	mtFrameDrawOGL::wheelEvent ( QWheelEvent * event )
{
	emit	SignalWheel(event);
}


void mtFrameDrawOGL::PutCrossLine(QPainter &Pnt ,int x,int y )
{
	Pnt.drawLine(0,y,width(),y);
	Pnt.drawLine(x,0,x,height());
}

void mtFrameDrawOGL::mouseReleaseEvent ( QMouseEvent * Ev )
{
	//int	X=Ev->x();
	//int	Y=Ev->y();
	//bool	mvalid=true;
	//mtMousePoint(Ev,X,Y,mvalid);
	if(CancelClicked==true){
		return;
	}

	if(DblClickMode==false){
		if(ShiftingMode==true){
			ShiftingMode=false;
			return;
		}

		ShapePoint	*c;
		ShapePoint	*d;
		ShapePoint	*q;
		int	X=Ev->x();
		int	Y=Ev->y();
		double	A,B,C;

		DrawingMode	CurrentMode=FDrawMode;
		ShiftingMode=false;

		bool	mvalid=true;
		mtMousePoint(Ev,X,Y,mvalid);
		if(mvalid==false){
			return;
		}

		FCancelDraw=false;

		int uX, uY;
		GetCanvasToUniverse(MousePressX, MousePressY ,uX, uY);
		if(LeftClicked==true){
			LastMouseDownPointX=uX;
			LastMouseDownPointY=uY;
			emit	SignalJustMouseLRelease(uX,uY);

			if(CancelClicked==true){
				return;
			}
			if(GetMode()==fdNone 
			|| GetMode()==fdPoint){
				mtMouseLDown(Ev,X,Y);
			}
			if(CurrentMode==fdNone){
				RepaintAll();
				return;
			}
			if(FCancelDraw==true){
				RepaintAll();
				return;
			}
			if((Ev->modifiers() & Qt::ShiftModifier)!=0){
				RepaintAll();
				return;
			}

			if(DrawStage==0){
				SData.dtype=CurrentMode;
				if(DrawStartEvent!=NULL)
					DrawStartEvent(this,X,Y);
				switch(CurrentMode){
					case fdPoint:
						SData.UData.PointData.x=uX;
						SData.UData.PointData.y=uY;
						DrawStage++;
						SData.LineWidth=LineWidth;
						DrawingOn();
						emit SignalDrawing(fdPoint,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor(Qt::ArrowCursor);
						break;
					case fdLine:
						FOnDrawMode=true;
						SData.UData.LineData.x=uX;
						SData.UData.LineData.y=uY;
						SData.UData.LineData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLine,DrawStage);
						//setCursor=(TCursor)crLine2;
						break;
					case fdHalfLine:
						FOnDrawMode=true;
						SData.UData.HalfLineData.x=uX;
						SData.UData.HalfLineData.y=uY;
						SData.UData.HalfLineData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHalfLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdHChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdVChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdVChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdSingleArrow:
						FOnDrawMode=true;
						SData.UData.SingleArrowLineData.x1=uX;
						SData.UData.SingleArrowLineData.y1=uY;
						SData.UData.SingleArrowLineData.x2=uX;
						SData.UData.SingleArrowLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdSingleArrow,DrawStage);
						//setCursor=(TCursor)crArrowLine2;
						break;
					case fdDualArrow:
						FOnDrawMode=true;
						SData.UData.DualArrowLineData.x1=uX;
						SData.UData.DualArrowLineData.y1=uY;
						SData.UData.DualArrowLineData.x2=uX;
						SData.UData.DualArrowLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdDualArrow,DrawStage);
						//setCursor=(TCursor)crArrowLine2;
						break;
					case fdRectangle:
						FOnDrawMode=true;
						SData.UData.RectangleData.x1=uX;
						SData.UData.RectangleData.y1=uY;
						SData.UData.RectangleData.x2=uX;
						SData.UData.RectangleData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRectangle,DrawStage);
						//setCursor=(TCursor)crRect2;
						break;
					case fdRotRectangle:
						FOnDrawMode=true;
						SData.UData.RotRectangleData.cx=uX;
						SData.UData.RotRectangleData.cy=uY;
						SData.UData.RotRectangleData.rx=0;
						SData.UData.RotRectangleData.ry=0;
						SData.UData.RotRectangleData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						//setCursor=(TCursor)crRotRect2;
						break;
					case fdCircle:
						FOnDrawMode=true;
						SData.UData.CircleData.cx=uX;
						SData.UData.CircleData.cy=uY;
						SData.UData.CircleData.r=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdCircle3:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdEllipse:
						FOnDrawMode=true;
						SData.UData.EllipseData.cx=uX;
						SData.UData.EllipseData.cy=uY;
						SData.UData.EllipseData.rx=0;
						SData.UData.EllipseData.ry=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						TmpPoint[3][0]=TmpPoint[2][0]=TmpPoint[1][0]=TmpPoint[0][0]=uX;
						TmpPoint[3][1]=TmpPoint[2][1]=TmpPoint[1][1]=TmpPoint[0][1]=uY;
						SData.UData.EllipseData.rx=10;
						SData.UData.EllipseData.ry=10;
						SData.UData.EllipseData.cx=uX;
						SData.UData.EllipseData.cy=uY+SData.UData.EllipseData.rx;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotEllipse:
						FOnDrawMode=true;
						SData.UData.RotEllipseData.cx=uX;
						SData.UData.RotEllipseData.cy=uY;
						SData.UData.RotEllipseData.rx=0;
						SData.UData.RotEllipseData.ry=0;
						SData.UData.RotEllipseData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdArc:
						FOnDrawMode=true;
						SData.UData.ArcData.cx=uX;
						SData.UData.ArcData.cy=uY;
						SData.UData.ArcData.r=0;
						SData.UData.ArcData.s1=0;
						SData.UData.ArcData.s2=2*M_PI;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc2;
						break;
					case fdArc3:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdFree:
						FOnDrawMode=true;
						if(SData.UData.FreeData.points==NULL){
							SData.UData.FreeData.points = new NPListPack<ShapePoint>();
							}
						SData.UData.FreeData.points->AppendList(new ShapePoint(uX,uY));
						rotx=uX;
						roty=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdFree,DrawStage);
						//setCursor=(TCursor)crFree2;
						break;
					case fdPoly:
						FOnDrawMode=true;
						if(SData.UData.PolyData.points==NULL){
							SData.UData.PolyData.points = new NPListPack<ShapePoint>();
							}
						SData.UData.PolyData.points->AppendList(new ShapePoint(uX,uY));
						rotx=uX;
						roty=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdPoly,DrawStage);
						//setCursor=(TCursor)crPoly2;
						break;
					/*
					case fdMove:
						FOnDrawMode=true;
						DrawStage++;
						if(SData.UData.MoveData.points==NULL){
							SData.UData.MoveData.points = new NPListPack<ShapePoint>();
							}
						DrawingOn();
						emit SignalDrawing(fdMove,DrawStage);
						//setCursor=(TCursor)crMove2;
						break;
					*/
					case fdRing:
						FOnDrawMode=true;
						PutPixelOnly(X,Y,FColor);
						SData.UData.ERingData.cx=uX;
						SData.UData.ERingData.cy=uY;
						SData.UData.ERingData.rx1=0;
						SData.UData.ERingData.ry1=0;
						SData.UData.ERingData.rx2=0;
						SData.UData.ERingData.ry2=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						//setCursor=(TCursor)crRing2;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdRingArc1:
						FOnDrawMode=true;
						SData.UData.RingArcData.cx=uX;
						SData.UData.RingArcData.cy=uY;
						SData.UData.RingArcData.rx1=0;
						SData.UData.RingArcData.ry1=0;
						SData.UData.RingArcData.rx2=0;
						SData.UData.RingArcData.ry2=0;
						SData.UData.RingArcData.s1=0;
						SData.UData.RingArcData.s2=2*M_PI;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc2;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						TmpPoint[3][0]=TmpPoint[2][0]=TmpPoint[1][0]=TmpPoint[0][0]=uX;
						TmpPoint[3][1]=TmpPoint[2][1]=TmpPoint[1][1]=TmpPoint[0][1]=uY;
						SData.UData.RingArcData.rx1=10;
						SData.UData.RingArcData.ry1=10;
						SData.UData.RingArcData.cx=uX;
						SData.UData.RingArcData.cy=uY+SData.UData.EllipseData.rx;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					}
				}
			else if(DrawStage==1){
				switch(CurrentMode){
					case fdLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crLine1;
						break;
					case fdHalfLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHalfLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdChoppedLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdHChoppedLine:
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdVChoppedLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdVChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdSingleArrow:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdSingleArrow,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArrowLine1;
						break;
					case fdDualArrow:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdDualArrow,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArrowLine1;
						break;
					case fdRectangle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						if(SData.UData.RectangleData.x1>SData.UData.RectangleData.x2)
							swap(SData.UData.RectangleData.x1,SData.UData.RectangleData.x2);
						if(SData.UData.RectangleData.y1>SData.UData.RectangleData.y2)
							swap(SData.UData.RectangleData.y1,SData.UData.RectangleData.y2);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRectangle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRect1;
						break;
					case fdRotRectangle:
						FOnDrawMode=true;
						rotx=uX;
						roty=uY;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						//setCursor=(TCursor)crRotRect3;
						break;
					case fdCircle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crCircle1;
						break;
					case fdCircle3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdEllipse:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotEllipse:
						FOnDrawMode=true;
						rotx=uX;
						roty=uY;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						//setCursor=(TCursor)crRotEllipse3;
						break;
					case fdArc:
						FOnDrawMode=true;
						rotx=SData.UData.ArcData.cx+(int)((double)SData.UData.ArcData.r*cos(SData.UData.ArcData.s1));
						roty=SData.UData.ArcData.cy+(int)((double)SData.UData.ArcData.r*sin(SData.UData.ArcData.s1));
						mtMouseMove(Ev, X, Y);
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc3;
						break;
					case fdArc3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdFree:
						mtMouseMove(Ev, X, Y);
						c=SData.UData.FreeData.points->GetFirst();
						d=SData.UData.FreeData.points->GetLast();
						SData.LineWidth=LineWidth;
						if(FClosedArea==true){
							if(c->x!=d->x || c->y!=d->y){
								SData.UData.FreeData.points->AppendList(new ShapePoint(c->x,c->y));
							}
						}
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdFree,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crFree1;
						break;
					case fdPoly:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						if(SData.UData.PolyData.points==NULL){
							SData.UData.PolyData.points = new NPListPack<ShapePoint>();
						}
						q=SData.UData.PolyData.points->GetLast();
						if((q!=NULL && (q->x!=uX || q->y!=uY)) || (q==NULL)){
							SData.UData.PolyData.points->AppendList(new ShapePoint(uX,uY));
						}

						rotx=uX;
						roty=uY;
						DrawingOn();
						emit SignalDrawing(fdPoly,DrawStage);
						//setCursor=(TCursor)crPoly2;
						break;
					/*
					case fdMove:
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdMove,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crMove1;
						break;
					*/
					case fdRing:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						//setCursor=(TCursor)crRing2;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;	
					case fdRingArc1:
						FOnDrawMode=true;
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s1));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s1));
						mtMouseMove(Ev, X, Y);
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc3;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
						}
				}
			else if(DrawStage==2){
				switch(CurrentMode){
					case fdCircle3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.CircleData.cx,SData.UData.CircleData.cy,SData.UData.CircleData.r);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle3,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotRectangle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRotEllipse:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdArc:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.ArcData.cx+(int)((double)SData.UData.ArcData.r*cos(SData.UData.ArcData.s2));
						roty=SData.UData.ArcData.cy+(int)((double)SData.UData.ArcData.r*sin(SData.UData.ArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					case fdArc3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.ArcData.cx,SData.UData.ArcData.cy,SData.UData.ArcData.r);
						A=TmpPoint[1][1]-TmpPoint[0][1];
						B=-(TmpPoint[1][0]-TmpPoint[0][0]);
						C=-TmpPoint[0][0]*TmpPoint[1][1]+TmpPoint[1][0]*TmpPoint[0][1];
						if(A*uX+B*uY+C>=0){
							SData.UData.ArcData.s1=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
							SData.UData.ArcData.s2=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
						}
						else{
							SData.UData.ArcData.s2=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
							SData.UData.ArcData.s1=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
						}
						SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
						SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRing:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRing1;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.LongCircleData.cx1,SData.UData.LongCircleData.cy1,SData.UData.LongCircleData.r);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						FOnDrawMode=false;
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRingArc1:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s2));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					}
				}
			else if(DrawStage==3){
				switch(CurrentMode){
					case fdEllipse4:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[3][0]=uX;
						TmpPoint[3][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						break;
					case fdArc:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArc1;
						break;
					case fdLongCircle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					//case fdFree:
					case fdRingArc1:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s1));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s1));
						TmpPoint[3][0]=uX;
						TmpPoint[3][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						break;
					}
				}
			else if(DrawStage==4){
				switch(CurrentMode){
					case fdRingArc1:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s2));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					}
				}
			else if(DrawStage==5){
				switch(CurrentMode){
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;				}
			}
			else if(DrawStage==6){
				switch(CurrentMode){
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						break;
				}
			}
			else if(DrawStage==7){
				switch(CurrentMode){
					case fdRingArc4:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						break;
				}
			}

			ChangeCursor(CurrentMode ,DrawStage);
		}
		else
		if((Ev->buttons()&Qt::SHIFT)!=0
		&& RightClicked==true){
			RepaintAll();
			return;
			}
		else
		if(RightClicked==true){
			LastMouseDownPointX=uX;
			LastMouseDownPointY=uY;
			emit	SignalJustMouseRRelease(uX,uY);

			mtMouseRDown(Ev, X,Y);
			if((Ev->modifiers() & Qt::ShiftModifier)!=0){
				RepaintAll();
				return;
			}
			if(CurrentMode==fdPoly){
				if(SData.UData.PolyData.points!=NULL){
					ShapePoint	*p=SData.UData.PolyData.points->GetLast();
					if(p!=NULL){
						SData.UData.PolyData.points->RemoveList(p);
						delete	p;
						if(SData.UData.PolyData.points->GetFirst()==NULL){
							DrawStage=0;
							FOnDrawMode=false;
							CancelDraw();
							emit SignalCancelDraw();
						}
					}
				}
			}
			else{
				if(CurrentMode==fdFree
				&& SData.UData.FreeData.points!=NULL){
					delete	SData.UData.FreeData.points;
					SData.UData.FreeData.points=NULL;
					}
	
				if(DrawStage>0)
					DrawStage--;
				if(CurrentMode==fdRotRectangle){
					SData.UData.RotRectangleData.s=0;
				}
				FOnDrawMode=false;
				CancelDraw();
				emit SignalCancelDraw();
			}
			ChangeCursor(CurrentMode ,DrawStage);
		}
	}
	else{	//When double click occurs
		int	X=Ev->x();
		int	Y=Ev->y();
		DrawingMode	CurrentMode=FDrawMode;

		if(LeftClicked==true){
			if(CurrentMode==fdPoly){
				SData.LineWidth=LineWidth;
				if(SData.UData.PolyData.points==NULL){
					SData.UData.PolyData.points = new NPListPack<ShapePoint>();
				}
				ShapePoint	*c=SData.UData.PolyData.points->GetFirst();
				ShapePoint	*d=SData.UData.PolyData.points->GetLast();
				if(FClosedArea==true && c!=NULL && d!=NULL){
					if(c->x!=d->x || c->y!=d->y){
						SData.UData.PolyData.points->AppendList(new ShapePoint(c->x,c->y));
						}
					}
				DrawStage++;
				DrawingOn();
				emit SignalDrawing(fdPoly,DrawStage);

				FOnDrawMode=false;
				DrawEnd();
				emit SignalDrawEnd();
				//setCursor=(TCursor)crPoly1;
				RepaintAll();
				return;
			}
			else{
				QMouseEvent	PushedEvent(Ev->type(),Ev->pos(),Qt::LeftButton,Ev->buttons() | Qt::LeftButton,Ev->modifiers());
				emit	SignalDoubleClick(&PushedEvent);
			}
		}
		else
		if(RightClicked==true && CurrentMode==fdPoly){
			mtMouseRDown(Ev, X,Y);
			FOnDrawMode=false;
			CancelDraw();
			emit SignalCancelDraw();
		}
		else{
			if(RightClicked==true){
				QMouseEvent	PushedEvent(Ev->type(),Ev->pos(),Qt::RightButton,Ev->buttons(),Ev->modifiers());
				emit	SignalDoubleClick(Ev);
			}
		}
		ChangeCursor(CurrentMode ,DrawStage);
	}
	RepaintAll();
}

struct	TmpPoint
{
	short x,y;
};

void mtFrameDrawOGL::Clear(void)
{
	if(FDrawMode==fdFree){
		if(SData.UData.FreeData.points!=NULL){
			SData.UData.FreeData.points->RemoveAll();
			//delete	SData.UData.FreeData.points;
			}
		//SData.UData.FreeData.points=NULL;
		}
	else if(FDrawMode==fdPoly){
		if(SData.UData.PolyData.points!=NULL){
			SData.UData.PolyData.points->RemoveAll();
			//delete	SData.UData.PolyData.points;
			}
		//SData.UData.PolyData.points=NULL;
		}
	else if(FDrawMode==fdMove){
		if(SData.UData.MoveData.points!=NULL){
			SData.UData.MoveData.points->RemoveAll();
			//delete	SData.UData.MoveData.points;
			}
		//SData.UData.MoveData.points=NULL;
		}

	DrawStage=0;
	FOnDrawMode=false;
	SetStartCursor();
}

void mtFrameDrawOGL::GetEffectiveArea(int &minx,int &miny,int &maxx ,int &maxy)
{
	minx=0;
	miny=0;
	maxx=width();
	maxy=height();
}

void	mtFrameDrawOGL::keyPressEvent ( QKeyEvent * event )
{
	if(event->isAccepted ()==true){
		return;
	}
	QPoint	P=GetCursorPos();
	if(0<=P.x() && P.x()<width() && 0<=P.y() && P.y()<height()){
		bool Accept=false;
		emit SignalKeyPress(event->key() ,P,Accept);
		if(Accept==true){
			event->accept();
		}
		if(Accept==false){
			if(event->key()==Qt::Key_Left){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x()-1, P.y());
				}
				else{
					SetMouseCursorPos(P.x()-10, P.y());
				}
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Right){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x()+1, P.y());
				}
				else{
					SetMouseCursorPos(P.x()+10, P.y());
				}
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter){
				QMouseEvent	LMouse(QEvent::MouseButtonPress
								,P
								,Qt::LeftButton
								,Qt::LeftButton
								,Qt::NoModifier);
				mousePressEvent(&LMouse);
				mouseReleaseEvent(&LMouse);
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Escape){
				QMouseEvent	LMouse(QEvent::MouseButtonPress
								,P
								,Qt::RightButton
								,Qt::RightButton
								,Qt::NoModifier);
				mousePressEvent(&LMouse);
				mouseReleaseEvent(&LMouse);
				event->accept();
			}
		}
	}
}

QPoint	mtFrameDrawOGL::GetCursorPos( void)
{
	const	QCursor	C=cursor ();
	return mapFromGlobal (C.pos());
}

void	mtFrameDrawOGL::SetMouseCursorPos(int XonG, int YonG)
{
	const	QCursor	C=cursor ();
	const QPoint pos(XonG,YonG);
	QPoint P=mapToGlobal (pos);
	C.setPos(P);
}

void	mtFrameDrawOGL::ExecuteMouseMove(int XonG, int YonG)
{
	QPoint position(XonG, YonG);
	QMouseEvent Ev( QEvent::MouseMove
					, position
					, Qt::NoButton
					, Qt::NoButton
					, Qt::NoModifier);
	mouseMoveEvent(&Ev); 
}

QString	mtFrameDrawOGL::ToString(DrawingMode mode)
{
	QString	Ret;
	switch(FDrawMode){
		case fdArc:
			Ret=/**/"fdArc";
			break;
		case fdArc3:
			Ret=/**/"fdArc3";
			break;
		case fdChoppedLine:
			Ret=/**/"fdChoppedLine";
			break;
		case fdHChoppedLine:
			Ret=/**/"fdHChoppedLine";
			break;
		case fdVChoppedLine:
			Ret=/**/"fdVChoppedLine";
			break;
		case fdCircle:
			Ret=/**/"fdCircle";
			break;
		case fdCircle3:
			Ret=/**/"fdCircle3";
			break;
		case fdDualArrow:
			Ret=/**/"fdDualArrow";
			break;
		case fdEllipse:
			Ret=/**/"fdEllipse";
			break;
		case fdEllipse4:
			Ret=/**/"fdEllipse4";
			break;
		case fdFree:
			Ret=/**/"fdFree";
			break;
		case fdHalfLine:
			Ret=/**/"fdHalfLine";
			break;
		case fdLine:
			Ret=/**/"fdLine";
			break;
		case fdMove:
			Ret=/**/"fdMove";
			break;
		case fdNone:
			Ret=/**/"fdNone";
			break;
		case fdPoint:
			Ret=/**/"fdPoint";
			break;
		case fdPoly:
			Ret=/**/"fdPoly";
			break;
		case fdRectangle:
			Ret=/**/"fdRectangle";
			break;
		case fdRing:
			Ret=/**/"fdRing";
			break;
		case fdRotEllipse:
			Ret=/**/"fdRotEllipse";
			break;
		case fdRotRectangle:
			Ret=/**/"fdRotRectangle";
			break;
		case fdSingleArrow:
			Ret=/**/"fdSingleArrow";
			break;
		case fdSpoint:
			Ret=/**/"fdSpoint";
			break;
		case fdRingArc1:
			Ret=/**/"fdRingArc1";
			break;
		case fdRingArc4:
			Ret=/**/"fdRingArc4";
			break;
	}
	return Ret;
}

void mtFrameDrawOGL::ChangeMode(DrawingMode newmode)
{
	FDrawMode=newmode;
	ChangeCursor(newmode ,DrawStage);
}

void	mtFrameDrawOGL::SetCursor(DrawingMode mode)
{
	ChangeCursor(mode ,0);
}

void mtFrameDrawOGL::ChangeCursor(DrawingMode newmode ,int CurrentDrawStage)
{
	switch(newmode){
			case fdArc:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdArc3:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdHChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdVChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdCircle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				break;
			case fdCircle3:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/EllipseTop.PNG"),8,1));
				break;
			case fdDualArrow:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdEllipse:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				break;
			case fdEllipse4:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/EllipseTop.PNG"),8,1));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				break;
			case fdFree:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(QPixmap(":/Icon/Free1.PNG"),11,0));
				break;
			case fdHalfLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdMove:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(QPixmap(":/Icon/MoveItem1.PNG"),7,7));
				break;
			case fdNone:
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdPoint:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdPoly:
				setCursor(QCursor(QPixmap(":/Icon/Polygon1.PNG"),9,9));
				break;
			case fdRectangle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle1.PNG"),4,4));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle2.PNG"),12,12));
				//setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRing:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRotEllipse:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==3)
					setCursor(QCursor(QPixmap(":/Icon/RotEllipse1.PNG"),12,14));
				//setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRotRectangle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle1.PNG"),4,4));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle2.PNG"),12,12));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/RotRectangle1.PNG"),12,14));
				break;
			case fdSingleArrow:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdSpoint:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRingArc1:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRingArc4:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			default:
				setCursor(QCursor(Qt::ArrowCursor));
	}
}


void mtFrameDrawOGL::Loaded(void)
{
	/*
	TCustomControl::Loaded();

	if(LoadedMode==false){
		LoadedMode=true;
		Screen->Cursors[crLine1 	 ] = LoadCursor(HInstance, "LINE1");
		Screen->Cursors[crLine2 	 ] = LoadCursor(HInstance, "LINE2");
		Screen->Cursors[crMove1 	 ] = LoadCursor(HInstance, "MOVE1");
		Screen->Cursors[crMove2 	 ] = LoadCursor(HInstance, "MOVE2");
		Screen->Cursors[crRing1 	 ] = LoadCursor(HInstance, "RING1");
		Screen->Cursors[crRing2 	 ] = LoadCursor(HInstance, "RING2");
		Screen->Cursors[crPoly1 	 ] = LoadCursor(HInstance, "POLY1");
		Screen->Cursors[crPoly2 	 ] = LoadCursor(HInstance, "POLY2");
		Screen->Cursors[crFree1 	 ] = LoadCursor(HInstance, "FREE1");
		Screen->Cursors[crFree2 	 ] = LoadCursor(HInstance, "FREE2");
		Screen->Cursors[crRotRect1	 ] = LoadCursor(HInstance, "ROTRECT1");
		Screen->Cursors[crRotRect2	 ] = LoadCursor(HInstance, "ROTRECT2");
		Screen->Cursors[crRotRect3	 ] = LoadCursor(HInstance, "ROTRECT3");
		Screen->Cursors[crEllipse1	 ] = LoadCursor(HInstance, "ELLIPSE1");
		Screen->Cursors[crEllipse2	 ] = LoadCursor(HInstance, "ELLIPSE2");
		Screen->Cursors[crRotEllipse3] = LoadCursor(HInstance, "ROTELLIPSE3");
		Screen->Cursors[crRect1 	 ] = LoadCursor(HInstance, "RECT1");
		Screen->Cursors[crRect2 	 ] = LoadCursor(HInstance, "RECT2");
		Screen->Cursors[crHalfLine1  ] = LoadCursor(HInstance, "HALFLINE1");
		Screen->Cursors[crHalfLine2  ] = LoadCursor(HInstance, "HALFLINE2");
		Screen->Cursors[crCircle1	 ] = LoadCursor(HInstance, "CIRCLE1");
		Screen->Cursors[crCircle2	 ] = LoadCursor(HInstance, "CIRCLE2");
		Screen->Cursors[crArc1		 ] = LoadCursor(HInstance, "ARC1");
		Screen->Cursors[crArc2		 ] = LoadCursor(HInstance, "ARC2");
		Screen->Cursors[crArc3		 ] = LoadCursor(HInstance, "ARC3");
		Screen->Cursors[crArc4		 ] = LoadCursor(HInstance, "ARC4");
		Screen->Cursors[crArrowLine1 ] = LoadCursor(HInstance, "ARROWLINE1");
		Screen->Cursors[crArrowLine2 ] = LoadCursor(HInstance, "ARROWLINE2");
		Screen->Cursors[crSpoint	 ] = LoadCursor(HInstance, "SPOINT");
		Screen->Cursors[crSmallCross ] = LoadCursor(HInstance, "SMALLCROSS");
		}
	*/
}

void mtFrameDrawOGL::SetStartCursor(void)
{
	/*
	switch(FDrawMode){
		case fdPoint:
			Cursor=(TCursor)crSmallCross;
			break;
		case fdLine:
			Cursor=(TCursor)crLine1;
			break;
		case fdHalfLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdHChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdVChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdRectangle:
			Cursor=(TCursor)crRect1;
			break;
		case fdRotRectangle:
			Cursor=(TCursor)crRotRect1;
			break;
		case fdCircle:
			Cursor=(TCursor)crCircle1;
			break;
		case fdCircle3:
			Cursor=(TCursor)crCircle1;
			break;
		case fdEllipse:
			Cursor=(TCursor)crEllipse1;
			break;
		case fdEllipse4:
			Cursor=(TCursor)crEllipse4;
			break;
		case fdRotEllipse:
			Cursor=(TCursor)crEllipse1;
			break;
		case fdArc:
			Cursor=(TCursor)crArc1;
			break;
		case fdArc3:
			Cursor=(TCursor)crArc1;
			break;
		case fdFree:
			Cursor=(TCursor)crFree1;
			break;
		case fdPoly:
			Cursor=(TCursor)crPoly1;
			break;
		case fdMove:
			Cursor=(TCursor)crMove1;
			break;
		case fdRing:
			Cursor=(TCursor)crRing1;
			break;
		case fdSingleArrow:
			Cursor=(TCursor)crArrowLine1;
			break;
		case fdDualArrow:
			Cursor=(TCursor)crArrowLine1;
			break;
		case fdSpoint:
			Cursor=(TCursor)crSpoint;
			break;
		case fdRingArc1:
			Cursor=(TCursor)crRingArc1;
			break;
		case fdRingArc4:
			Cursor=(TCursor)crRingArc4;
			break;
		case fdNone:
			Cursor=(TCursor)crDefault;
			break;
		}
	*/
}

//=============================================



mtQFrameDrawInGUnitOG::mtQFrameDrawInGUnitOG(mtGraphicUnitOG *mparent ,QWidget *parent)
:mtFrameDrawOGL(parent)
{
	Parent	=mparent;
	SetZoomRate(1.0);
	SetMovXY(0,0);
	AreaSizeX=100;
	AreaSizeY=100;
}

void	mtQFrameDrawInGUnitOG::mousePressEvent ( QMouseEvent *Ev )
{	
	mtFrameDrawOGL::mousePressEvent(Ev); 
	Parent->LaunchSignalMousePressEvent(Ev);
}

void	mtQFrameDrawInGUnitOG::SlotDrawEnd(void)
{
	Parent->LaunchSignalDrawEnd();
}
void	mtQFrameDrawInGUnitOG::SlotDrawing(DrawingMode mode,int stage)
{
	Parent->LaunchSignalDrawing(mode,stage);
}
void	mtQFrameDrawInGUnitOG::SlotCancelDraw(void)
{
	Parent->LaunchSignalCancelDraw();
}
void	mtQFrameDrawInGUnitOG::SlotOnPaint(QPainter &pnt)
{
	Parent->LaunchSignalOnPaint(pnt);
}

void	mtQFrameDrawInGUnitOG::wheelEvent ( QWheelEvent * event )
{
	emit	SignalWheel(event);
}
void	mtQFrameDrawInGUnitOG::mtMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid)
{
	mtFrameDrawOGL::mtMousePoint(Ev ,x ,y ,valid);
	Parent->LaunchSignalMousePoint(Ev ,x ,y ,valid);
}
void	mtQFrameDrawInGUnitOG::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDrawOGL::mtMouseLDown(Ev ,x ,y);
	Parent->LaunchSignalMouseLDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnitOG::mtMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDrawOGL::mtMouseRDown(Ev ,x ,y);
	Parent->LaunchSignalMouseRDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnitOG::mtMouseMove(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDrawOGL::mtMouseMove(Ev ,x ,y);
	Parent->LaunchSignalMouseMove(Ev ,x ,y);
}
void	mtQFrameDrawInGUnitOG::mtMouseLUp(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDrawOGL::mtMouseLDown(Ev ,x ,y);
	emit	SignalMouseLUp(x/GetZoomRate()-GetMovX(),y/GetZoomRate()-GetMovY());
	Parent->LaunchSignalMouseLUp(Ev ,x ,y);
}
void	mtQFrameDrawInGUnitOG::mtMouseRUp(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDrawOGL::mtMouseRDown(Ev ,x ,y);
	Parent->LaunchSignalMouseRUp(Ev ,x ,y);
}
void	mtQFrameDrawInGUnitOG::ShiftPressed(int gx ,int gy)
{
	Parent->LaunchSignalShiftPressed(gx ,gy);
}

//-----------------------------------------------------

void	mtGraphicUnitOG::LaunchSignalDrawEnd(void)
{
	emit	SignalDrawEnd();
}
void	mtGraphicUnitOG::LaunchSignalDrawing(DrawingMode mode,int stage)
{
	emit	SignalDrawing(mode,stage);
}
void	mtGraphicUnitOG::LaunchSignalCancelDraw(void)
{
	emit	SignalCancelDraw();
}
void	mtGraphicUnitOG::LaunchSignalOnPaint(QPainter &pnt)
{
	emit	SignalOnPaint(pnt);
}


mtScrollBarOG::mtScrollBarOG( mtGraphicUnitOG *mparent ,Qt::Orientation orientation,QWidget *parent)
:QScrollBar(orientation,parent)
{
	Parent	=mparent;
}

void mtScrollBarOG::sliderChange ( SliderChange change )
{
	if(Parent->IsInnerFuncMode()==true){
		return;
	}
	if(orientation ()==Qt::Horizontal){
		Parent->GetCanvas()->SetMovX(-Parent->GetHScroll()->value());
		Parent->GetHScroll()->repaint(0,0,Parent->GetHScroll()->width(),Parent->GetHScroll()->height());
	}
	else{
		Parent->GetCanvas()->SetMovY(-Parent->GetVScroll()->value());
		Parent->GetVScroll()->repaint(0,0,Parent->GetVScroll()->width()
										 ,Parent->GetVScroll()->height());
	}
	Parent->SetMeter();
	Parent->GetCanvas()->RepaintAll();
	Parent->LaunchSignalScrollDraw();
}

void mtScrollBarOG::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtScrollBarOG::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}

mtGraphicUnitOG::mtGraphicUnitOG(QWidget *parent				
							,bool	_EnableMeasure
							,bool	_EnableToolArea
							,bool	_EnableVScroller
							,bool	_EnableHScroller
							,bool	_EnableZoom
							,bool	_EnableMove
							,bool	_EnableFitZoom)
    : mtWidgetPosition(parent)
{
	FirstTime	=true;

	EnableMeasure	=_EnableMeasure		;
	EnableToolArea	=_EnableToolArea	;
	EnableVScroller	=_EnableVScroller	;
	EnableHScroller	=_EnableHScroller	;
	EnableZoom		=_EnableZoom		;
	EnableMove		=_EnableMove		;
	EnableFitZoom	=_EnableFitZoom		;
	FVerticalMerginRate		=0.1;
	FHorizontalMerginRate	=0.1;
	UseLongPush		=false;
	LongPushMilisec	=1000;

	InsideFunc	=0;
	if(EnableMeasure==true){
		MeterTop	=new mtMeter(this);
		MeterTop->SetDrawMode(mtMeter::mtHorizLower);
		MeterLeft	=new mtMeter(this);
		MeterLeft->SetDrawMode(mtMeter::mtVertRight);
	}
	else{
		MeterTop=NULL;
		MeterLeft=NULL;
	}

	ScrollerWidth=16;
	if(EnableHScroller==true){
		HScroll	=new mtScrollBarOG(this,Qt::Horizontal,this);
		LeftPageBtn	=new mtPushButtonWithBalloon(this);
		RightPageBtn=new mtPushButtonWithBalloon(this);
	}
	else{
		HScroll		=NULL;
		LeftPageBtn	=NULL;
		RightPageBtn=NULL;
	}
	if(EnableVScroller==true){
		VScroll	=new mtScrollBarOG(this,Qt::Vertical,this);
		UpPageBtn	=new mtPushButtonWithBalloon(this);
		DownPageBtn	=new mtPushButtonWithBalloon(this);
	}
	else{
		VScroll		=NULL;
		UpPageBtn	=NULL;
		DownPageBtn	=NULL;
	}
	if(EnableFitZoom==true){
		FitZoomBtn	=new mtPushButtonWithBalloon(this);
	}
	else{
		FitZoomBtn=NULL;
	}

	FrDraw =new mtQFrameDrawInGUnitOG(this,this);
	FZoomRateMin=0.001;
	FZoomRateMax=100;
	resize(400, 400);


	connect(FrDraw,SIGNAL(SignalDrawEnd(void))		,this,SLOT(SlotDrawEnd(void)));
	connect(FrDraw,SIGNAL(SignalDrawing(DrawingMode,int))		,this,SLOT(SlotDrawing(DrawingMode,int)));
	connect(FrDraw,SIGNAL(SignalCancelDraw(void))	,this,SLOT(SlotCancelDraw(void)));
	connect(FrDraw,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(FrDraw,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
	connect(FrDraw,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
	connect(FrDraw,SIGNAL(SignalKeyPress(int,QPoint,bool &)),this,SLOT(SlotKeyPress(int,QPoint,bool &)));
	connect(FrDraw,SIGNAL(SignalDoubleClick(QMouseEvent *)),this,SLOT(SlotDoubleClick(QMouseEvent *)));
	connect(FrDraw,SIGNAL(SignalWheel(QWheelEvent*)),this,SLOT(SlotWheel(QWheelEvent*)));
	connect(FrDraw,SIGNAL(SignalShiftCanvas(int,int)),this,SLOT(SlotShiftCanvas(int,int)));
	connect(FrDraw,SIGNAL(SignalDrawMessage(const QStringList &,const QStringList &))	,this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
	connect(FrDraw,SIGNAL(SignalJustMouseLPress	(int,int))	,this,SLOT(SlotJustMouseLPress	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseRPress	(int,int))	,this,SLOT(SlotJustMouseRPress	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseLRelease(int,int))	,this,SLOT(SlotJustMouseLRelease	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseRRelease(int,int))	,this,SLOT(SlotJustMouseRRelease	(int,int)));

	bool	ModeEnterLeave=false;
	if(VScroll!=NULL){
		connect(VScroll,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(VScroll,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(HScroll!=NULL && ModeEnterLeave==false){
		connect(HScroll,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(HScroll,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(MeterTop!=NULL && ModeEnterLeave==false){
		connect(MeterTop,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(MeterTop,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(MeterLeft!=NULL && ModeEnterLeave==false){
		connect(MeterLeft,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(MeterLeft,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(UpPageBtn!=NULL){
		connect(UpPageBtn,SIGNAL(clicked())		,this,SLOT(SlotUpPageButtonDown		()));
	}
	if(DownPageBtn!=NULL){
		connect(DownPageBtn,SIGNAL(clicked())	,this,SLOT(SlotDownPageButtonDown	()));
	}
	if(LeftPageBtn!=NULL){
		connect(LeftPageBtn,SIGNAL(clicked())	,this,SLOT(SlotLeftPageButtonDown	()));
	}
	if(RightPageBtn!=NULL){
		connect(RightPageBtn,SIGNAL(clicked())	,this,SLOT(SlotRightPageButtonDown	()));
	}
	if(FitZoomBtn!=NULL){
		connect(FitZoomBtn,SIGNAL(clicked())	,this,SLOT(SlotFitZoomBtnDown	()));
	}
}


mtGraphicUnitOG::~mtGraphicUnitOG(void)
{
	disconnect(this,SLOT(SlotDrawEnd(void)));
	disconnect(this,SLOT(SlotDrawing(DrawingMode,int)));
	disconnect(this,SLOT(SlotCancelDraw(void)));
	disconnect(this,SLOT(SlotOnPaint(QPainter &)));
	disconnect(this,SLOT(SlotEnter()));
	disconnect(this,SLOT(SlotLeave()));
	disconnect(this,SLOT(SlotKeyPress(int,QPoint,bool &)));
	disconnect(this,SLOT(SlotDoubleClick(QMouseEvent *)));
	disconnect(this,SLOT(SlotWheel(QWheelEvent*)));
	disconnect(this,SLOT(SlotShiftCanvas(int,int)));
	disconnect(this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
	disconnect(this,SLOT(SlotJustMouseLPress	(int,int)));
	disconnect(this,SLOT(SlotJustMouseRPress	(int,int)));
	disconnect(this,SLOT(SlotJustMouseLRelease	(int,int)));
	disconnect(this,SLOT(SlotJustMouseRRelease	(int,int)));
	disconnect(this,SLOT(SlotUpPageButtonDown		()));
	disconnect(this,SLOT(SlotDownPageButtonDown	()));
	disconnect(this,SLOT(SlotLeftPageButtonDown	()));
	disconnect(this,SLOT(SlotRightPageButtonDown	()));
	disconnect(this,SLOT(SlotFitZoomBtnDown	()));

	delete	MeterTop;
	delete	MeterLeft;
	delete	VScroll;
	delete	HScroll;
	delete	FrDraw;
	delete	FitZoomBtn;
	delete	UpPageBtn;
	delete	DownPageBtn;
	delete	LeftPageBtn;
	delete	RightPageBtn;

	MeterTop	=NULL;
	MeterLeft	=NULL;
	VScroll		=NULL;
	HScroll		=NULL;
	FrDraw		=NULL;
	FitZoomBtn	=NULL;
	UpPageBtn	=NULL;
	DownPageBtn	=NULL;
	LeftPageBtn	=NULL;
	RightPageBtn=NULL;
}


void mtGraphicUnitOG::resizeEvent ( QResizeEvent *event)
{
	int	x1=0;
	int	y1=0;
	int	W=width();
	int	H=height();
	int	CWidth=W;
	int	CHeight=H;

	if(MeterTop!=NULL){
		if(MeterLeft!=NULL){
			MeterTop ->setGeometry ( 16, 0, CWidth -32, 16 );
		}
		else{
			MeterTop ->setGeometry ( 0, 0, CWidth -16, 16 );
		}
		y1=16;
		H-=16;
	}
	if(MeterLeft!=NULL){
		if(MeterTop!=NULL){
			MeterLeft->setGeometry ( 0 , 16,16, CHeight -32 );
		}
		else{
			MeterLeft->setGeometry ( 0 , 0,16, CHeight-16 );
		}
		x1=16;
		W-=16;
	}
	int	VScrollWidth=ScrollerWidth;
	if(VScroll!=NULL){
		if(MeterTop!=NULL){
			VScroll	->setGeometry (CWidth -1-VScrollWidth, 16, VScrollWidth, CHeight -32 -16);
		}
		else{
			VScroll	->setGeometry (CWidth -1-VScrollWidth, 0, VScrollWidth, CHeight -32);
		}
		W-=VScrollWidth;
	}
	int	HScrollHeight=ScrollerWidth;
	if(HScroll!=NULL){
		if(MeterLeft!=NULL){
			HScroll	->setGeometry ( 16 , CHeight -1-HScrollHeight, CWidth -32-16, HScrollHeight);
		}
		else{
			HScroll	->setGeometry ( 0 , CHeight -1-HScrollHeight, CWidth -32, HScrollHeight);
		}
		H-=HScrollHeight;
	}
	FrDraw->setGeometry (x1,y1,W,H);

	if(UpPageBtn!=NULL){
		UpPageBtn	->setGeometry (CWidth -1-VScrollWidth,0,16,16);
	}
	if(DownPageBtn!=NULL){
		DownPageBtn	->setGeometry (CWidth -1-VScrollWidth, CHeight -32,16,16);
	}
	if(LeftPageBtn!=NULL){
		LeftPageBtn	->setGeometry (0, CHeight -1-HScrollHeight,16,16);
	}
	if(RightPageBtn!=NULL){
		RightPageBtn->setGeometry (CWidth -32, CHeight -1-HScrollHeight,16,16);
	}
	if(FitZoomBtn!=NULL){
		FitZoomBtn->setGeometry (0,0,16,16);
	}
	//QWidget::resizeEvent ( event );
	SetWindowPos();

	if(FirstTime==true && GetCanvasWidth()>0){
		ZoomDrawWhole();
		FirstTime=false;
	}
	update();
	if(event!=NULL){
		QWidget::resizeEvent(event);
		event->accept();
	}
}

mtQFrameDrawInGUnitOG	*mtGraphicUnitOG::GetCanvas(void)	const
{
	return(FrDraw);
}
void	mtGraphicUnitOG::ZoomDraw( int movx, int movy, double ZoomRate)
{
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	ZoomDrawFree(movx, movy, ZoomRate);
}
void	mtGraphicUnitOG::ZoomDrawFree(int movx, int movy, double zoomrate)
{
	FrDraw->SetMovXY(movx,movy);
	FrDraw->SetZoomRate(zoomrate);
	
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}

bool	mtGraphicUnitOG::ZoomIn(int XonG, int YonG)
{
	double	ZoomRate=GetZoomRate()*2;
	if(ZoomRate<FZoomRateMin){
		return false;
	}
	if(FZoomRateMax<ZoomRate){
		return false;
	}

    int LX=(int)((double)XonG/ZoomRate);
    int LY=(int)((double)YonG/ZoomRate);
	ZoomDrawFree(GetMovx()-LX, GetMovy()-LY,ZoomRate);
	return true;
}

bool	mtGraphicUnitOG::ZoomOut(int XonG, int YonG)
{
	double	OldZoomRate=GetZoomRate();
	double	tZoomRate=GetZoomRate()/2.0;
	if(tZoomRate<FZoomRateMin){
		return false;
	}
	double	Z=OldZoomRate/tZoomRate;
	int LX=(int)((double)XonG/(tZoomRate*Z));
	int LY=(int)((double)YonG/(tZoomRate*Z));
	ZoomDrawFree(GetMovx()+LX, GetMovy()+LY, tZoomRate);
	return true;
}

bool	mtGraphicUnitOG::SetZoom(int XonG, int YonG , double _ZoomRate)
{
	if(FZoomRateMin<=_ZoomRate && _ZoomRate<=FZoomRateMax){
	    int LX=(int)((double)XonG/GetZoomRate());
		int LY=(int)((double)YonG/GetZoomRate());
	    int LXNew=(int)((double)XonG/_ZoomRate);
		int LYNew=(int)((double)YonG/_ZoomRate);
		ZoomDraw(GetMovx()-LX+LXNew, GetMovy()-LY+LYNew, _ZoomRate);
		return true;
	}
	return false;
}

bool    mtGraphicUnitOG::ZoomRectG(int Gx1 ,int Gy1 ,int Gx2 ,int Gy2)
{
    int cx=(Gx2+Gx1)/2;
    int cy=(Gy2+Gy1)/2;
    int Ux=abs(Gx2-Gx1);
    int Uy=abs(Gy2-Gy1);

    cx=cx/GetZoomRate()-GetMovx();
    cy=cy/GetZoomRate()-GetMovy();
    Ux=Ux/GetZoomRate();
    Uy=Uy/GetZoomRate();

    double  ZX,ZY;
	if(Ux>0){
        ZX=(double)(double)GetCanvas()->width()/Ux;
	}
	else{
        ZX=FZoomRateMax;
	}
	if(Uy>0){
        ZY=(double)(double)GetCanvas()->height()/Uy;
	}
	else{
        ZY=FZoomRateMax;
	}
    double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(FZoomRateMin<=ZoomRate && ZoomRate<=FZoomRateMax){
	    int	movx=GetCanvas()->width()/2/ZoomRate - cx;
		int	movy=GetCanvas()->height()/2/ZoomRate- cy;
		ZoomDraw(movx, movy, ZoomRate);
		return true;
	}
	return false;
}

bool    mtGraphicUnitOG::ZoomRectU(int Ux1 ,int Uy1 ,int Ux2 ,int Uy2)
{
    int cx=(Ux2+Ux1)/2;
    int cy=(Uy2+Uy1)/2;
    int Ux=abs(Ux2-Ux1);
    int Uy=abs(Uy2-Uy1);

    double  ZX,ZY;
	if(Ux>0){
        ZX=(double)(double)GetCanvas()->width()/Ux;
	}
	else{
        ZX=FZoomRateMax;
	}
	if(Uy>0){
        ZY=(double)(double)GetCanvas()->height()/Uy;
	}
	else{
        ZY=FZoomRateMax;
	}
	double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(FZoomRateMin<=ZoomRate && ZoomRate<=FZoomRateMax){
		int	movx=GetCanvas()->width()/2/ZoomRate - cx;
		int	movy=GetCanvas()->height()/2/ZoomRate- cy;
		ZoomDraw(movx, movy, ZoomRate);
		return true;
	}
	return false;
}

double	mtGraphicUnitOG::GetZoomRateForWhole(void)	const
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZX=((double)vW)/((double)GetCanvas()->AreaSizeX);
    double	ZY=((double)vH)/((double)GetCanvas()->AreaSizeY);
    double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	return ZoomRate;
}

void	mtGraphicUnitOG::ZoomDrawWhole(void)
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZoomRate=GetZoomRateForWhole();
	int	GW=GetCanvas()->AreaSizeX*ZoomRate;
	int	GH=GetCanvas()->AreaSizeY*ZoomRate;
	int	XSpare=(vW-GW)/2;
	int	YSpare=(vH-GH)/2;

	ZoomDraw(XSpare/ZoomRate, YSpare/ZoomRate, ZoomRate);
}

double	mtGraphicUnitOG::GetZoomRateForFit(void)	const
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZX=((double)vW)/((double)GetCanvas()->AreaSizeX);
    double	ZY=((double)vH)/((double)GetCanvas()->AreaSizeY);
    double	ZoomRate=(ZX<ZY)?ZY:ZX;
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	return ZoomRate;
}
void	mtGraphicUnitOG::ZoomDrawFit(void)
{
	double	ZoomRate=GetZoomRateForFit();
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	int	GW=GetCanvas()->AreaSizeX*ZoomRate;
	int	GH=GetCanvas()->AreaSizeY*ZoomRate;
	int	XSpare=(vW-GW)/2;
	int	YSpare=(vH-GH)/2;

	ZoomDraw(XSpare/ZoomRate, YSpare/ZoomRate, ZoomRate);
}
void	mtGraphicUnitOG::SetScrollerWidth(int w)
{	
	ScrollerWidth=w;
}
void	mtGraphicUnitOG::SetFModeRepaintOnMouseMove(bool b)
{
	GetCanvas()->SetFModeRepaintOnMouseMove(b);
}
bool	mtGraphicUnitOG::GetFModeRepaintOnMouseMove(void)
{
	return GetCanvas()->GetFModeRepaintOnMouseMove();
}
void	mtGraphicUnitOG::Repaint(void)
{
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnitOG::SetAreaSize(int xlen ,int ylen)
{
	if(xlen>0)
		FrDraw->AreaSizeX=xlen;
	if(ylen>0)
		FrDraw->AreaSizeY=ylen;
}

class	MMQWidget : public QWidget
{
public:
	void KeyPressEvent ( QKeyEvent * event )	{	keyPressEvent(event);	}
	void KeyReleaseEvent ( QKeyEvent * event )	{	keyReleaseEvent(event);	}
};


void	mtGraphicUnitOG::keyPressEvent(QKeyEvent * event )
{
	((MMQWidget *)FrDraw)->KeyPressEvent(event);
}
void	mtGraphicUnitOG::SetMerginRate(double Hr,double Vr)
{
	FVerticalMerginRate		=Hr;
	FHorizontalMerginRate	=Vr;
}
void	mtGraphicUnitOG::SetSlider(void)
{
	InsideFunc++;

	if(HScroll!=NULL){
		int	MinV=FrDraw->AreaSizeX*(-FHorizontalMerginRate)/GetZoomRate();
		int	MaxV=FrDraw->AreaSizeX*(1.0+FHorizontalMerginRate)/GetZoomRate();
		int	Range=FrDraw->width()/GetZoomRate();
		HScroll->setMinimum (MinV);
		HScroll->setMaximum (MaxV-Range);
		HScroll->setPageStep(Range);
		int	XPos=-GetMovx();
		HScroll->setValue(XPos);
		HScroll->repaint();

	}

	if(VScroll!=NULL){
		int	MinV=FrDraw->AreaSizeY*(-FVerticalMerginRate)/GetZoomRate();
		int	MaxV=FrDraw->AreaSizeY*(1.0+FVerticalMerginRate)/GetZoomRate();
		int	Range=FrDraw->height()/GetZoomRate();
		VScroll->setMinimum (MinV);
		VScroll->setMaximum (MaxV-Range);
		VScroll->setPageStep(Range);
		int	YPos=-GetMovy();
		VScroll->setValue(YPos);
		VScroll->repaint();
	}

	InsideFunc--;

}
void	mtGraphicUnitOG::DrawAdd(int UOffx, int UOffy)
{
	InsideFunc++;

	FrDraw->SetMovXY(FrDraw->GetMovX()+UOffx,FrDraw->GetMovY()+UOffy);

	if(HScroll!=NULL){
		int	NowH=HScroll->sliderPosition();
		NowH-=UOffx;
		HScroll->setSliderPosition(NowH);
		HScroll->repaint();
		HScroll->setValue(-GetMovx());
	}

	if(VScroll!=NULL){
		int	NowV=VScroll->sliderPosition();
		NowV-=UOffy;
		VScroll->setSliderPosition(NowV);
		VScroll->repaint();
		VScroll->setValue(-GetMovy());
	}

	SetMeter();
	GetCanvas()->RepaintAll();

	InsideFunc--;
}

void	mtGraphicUnitOG::SetDrawOffset(int UMovx ,int UMovy)
{
	InsideFunc++;

	FrDraw->SetMovXY(UMovx,UMovy);

	if(HScroll!=NULL){
		int	NowH=-UMovx;
		HScroll->setSliderPosition(NowH);
		HScroll->repaint();
		HScroll->setValue(-GetMovx());
	}
	if(VScroll!=NULL){
		int	NowV=-UMovx;
		VScroll->setSliderPosition(NowV);
		VScroll->repaint();
		VScroll->setValue(-GetMovy());
	}
	SetMeter();
	GetCanvas()->RepaintAll();

	InsideFunc--;
}


void	mtGraphicUnitOG::SetMeter(void)
{
	if(MeterTop!=NULL){
		MeterTop	->SetZoomRate	 (GetZoomRate());
		MeterTop	->SetLeftPosition(-GetMovx());
	}
	if(MeterLeft!=NULL){
		MeterLeft	->SetZoomRate(GetZoomRate());
		MeterLeft	->SetLeftPosition(-GetMovy());
	}
}

void	mtGraphicUnitOG::Clear(void)
{
	if(FrDraw!=NULL){
		FrDraw->Clear();
	}
}

void	mtGraphicUnitOG::SetCancelDraw(void)
{
	if(FrDraw!=NULL){
		FrDraw->SetCancelDraw();
	}
}
void	mtGraphicUnitOG::SetCursor(DrawingMode mode)
{
	FrDraw->SetCursor(mode);
}
void	mtGraphicUnitOG::LaunchSignalMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid)
{
}
void	mtGraphicUnitOG::LaunchSignalMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	if((Ev->modifiers() & Qt::ShiftModifier)==0){
		emit	SignalMouseLDown(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->modifiers() & Qt::ShiftModifier)!=0){
		emit	SignalMouseLDownWithShift(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}
void	mtGraphicUnitOG::LaunchSignalMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	if((Ev->modifiers() & Qt::ShiftModifier)==0){
		emit	SignalMouseRDown(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->modifiers() & Qt::ShiftModifier)!=0){
		emit	SignalMouseRDownWithShift(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}
void	mtGraphicUnitOG::LaunchSignalMouseMove(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseMove(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}
void	mtGraphicUnitOG::LaunchSignalMouseLUp(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseLUp(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}
void	mtGraphicUnitOG::LaunchSignalMouseRUp(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseRUp(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}

void	mtGraphicUnitOG::SlotWheel(QWheelEvent * e)
{
	QPoint numDegrees = e->angleDelta();
	//int	D=e->delta();
	int	D=numDegrees.y();
	int	X=e->position().x()/FrDraw->GetZoomRate()-FrDraw->GetMovX();
	int	Y=e->position().y()/FrDraw->GetZoomRate()-FrDraw->GetMovY();
	emit	SignalMouseWheel(D,X,Y);
}

void	mtGraphicUnitOG::LaunchSignalShiftPressed(int gx ,int gy)
{
	emit	SignalShiftPressed(gx ,gy);
}

void	mtGraphicUnitOG::LaunchSignalMousePressEvent(QMouseEvent *Ev)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMousePressEvent(Ev);
}

void	mtGraphicUnitOG::SlotDrawEnd(void)
{
}
void	mtGraphicUnitOG::SlotDrawing(DrawingMode mode,int stage)
{
}
void	mtGraphicUnitOG::SlotCancelDraw(void)
{
}
void	mtGraphicUnitOG::SlotOnPaint(QPainter &pnt)
{
}
void	mtGraphicUnitOG::SlotMouseMove(int globalX,int globalY)
{
}
void	mtGraphicUnitOG::SlotMouseLDown(int globalX,int globalY)
{
}
void	mtGraphicUnitOG::SlotMouseLUp(int globalX,int globalY)
{
}
void	mtGraphicUnitOG::SlotMouseRDown(int globalX,int globalY)
{
}
void	mtGraphicUnitOG::SlotMouseRUp(int globalX,int globalY)
{
}
void mtGraphicUnitOG::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtGraphicUnitOG::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}

void	mtGraphicUnitOG::SlotEnter()
{
	emit	SignalEnter();
}
void	mtGraphicUnitOG::SlotLeave()
{
	emit	SignalLeave();
}

void	mtGraphicUnitOG::SlotKeyPress(int key ,QPoint RawPos,bool &Accept)
{
	emit	SignalKeyPress(key,RawPos.x(),RawPos.y() ,Accept);
}

bool	mtGraphicUnitOG::IsIncludeInCanvas(QPoint &P)	const
{
	if(0<=P.x() && P.x()<GetCanvas()->width() && 0<=P.y() && P.y()<GetCanvas()->height()){
		return true;
	}
	return false;
}

void	mtGraphicUnitOG::SetMouseCursorPos(int XonG, int YonG)
{
	GetCanvas()->SetMouseCursorPos(XonG, YonG);
}

void	mtGraphicUnitOG::ExecuteMouseMove(int XonG, int YonG)
{
	GetCanvas()->ExecuteMouseMove(XonG, YonG);
}

void	mtGraphicUnitOG::LaunchSignalScrollDraw(void)
{
	emit	SignalScrollDraw();
}
void	mtGraphicUnitOG::SlotDoubleClick(QMouseEvent *Ev)
{
	int	x=Ev->x();
	int	y=Ev->y();
	StateMouseButtons=Ev->buttons();

	if((Ev->buttons()&Qt::LeftButton)!=0){
		emit	SignalMouseLDoubleClick(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->buttons()&Qt::RightButton)!=0){
		emit	SignalMouseRDoubleClick(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}

void	mtGraphicUnitOG::SlotUpPageButtonDown()
{
    int	movy=GetCanvas()->height()/2/GetZoomRate();
	FrDraw->SetMovY(FrDraw->GetMovY()+movy);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnitOG::SlotDownPageButtonDown()
{
    int	movy=GetCanvas()->height()/2/GetZoomRate();
	FrDraw->SetMovY(FrDraw->GetMovY()-movy);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnitOG::SlotLeftPageButtonDown()
{
    int	movx=GetCanvas()->width()/2/GetZoomRate();
	FrDraw->SetMovX(FrDraw->GetMovX()+movx);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnitOG::SlotRightPageButtonDown()
{
    int	movx=GetCanvas()->width()/2/GetZoomRate();
	FrDraw->SetMovX(FrDraw->GetMovX()-movx);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnitOG::SlotFitZoomBtnDown()
{
    ZoomDrawWhole();
	GetCanvas()->RepaintAll();
	emit	SignalFitZoom();
}
void	mtGraphicUnitOG::SlotShiftCanvas(int UniversalDx,int UniversalDy)
{
	if(EnableMove==true){
		FrDraw->SetMovX(FrDraw->GetMovX()+UniversalDx/GetZoomRate());
		FrDraw->SetMovY(FrDraw->GetMovY()+UniversalDy/GetZoomRate());
		SetSlider();
		SetMeter();
		GetCanvas()->RepaintAll();
		emit	SignalShiftAll();
	}
}
void	mtGraphicUnitOG::SlotDrawMessage(const QStringList &title ,const QStringList &msg)
{
	emit	SignalDrawMessage(title ,msg);

}

void	mtGraphicUnitOG::SetEnableShiftImage(bool b)
{
	FrDraw->SetEnableShiftImage(b);
}
bool	mtGraphicUnitOG::GetEnableShiftImage(void)	const
{
	return FrDraw->GetEnableShiftImage();
}

void	mtGraphicUnitOG::SetCrossLineMode(bool mode ,const QColor &Col)
{
	FrDraw->SetCrossLineMode(mode ,Col);
}

void	mtGraphicUnitOG::SetMeterOffset(int OffsetX ,int OffsetY)
{
	if(MeterTop!=NULL){
		MeterTop->SetOffsetValue(OffsetX);
	}
	if(MeterLeft!=NULL){
		MeterLeft->SetOffsetValue(OffsetY);
	}
}

void	mtGraphicUnitOG::GetMeterOffset(int &OffsetX ,int &OffsetY)
{
	if(MeterTop!=NULL){
		OffsetX	=MeterTop->GetOffsetValue();
	}
	else{
		OffsetX=0;
	}
	if(MeterLeft!=NULL){
		OffsetY	=MeterLeft->GetOffsetValue();
	}
	else{
		OffsetY	=0;
	}
}
void	mtGraphicUnitOG::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
	PushedTimeer.start();
	emit	SignalJustMouseLPress  (UniversalDx,UniversalDy);
}
void	mtGraphicUnitOG::SlotJustMouseLRelease(int UniversalDx,int UniversalDy)
{
	if(UseLongPush==false || PushedTimeer.hasExpired(LongPushMilisec)==false){
		emit	SignalJustMouseLRelease(UniversalDx,UniversalDy);
	}
	else{
		emit	SignalJustMouseLLongPress(UniversalDx,UniversalDy);
	}
}
void	mtGraphicUnitOG::SlotJustMouseRPress  (int UniversalDx,int UniversalDy)
{
	PushedTimeer.start();
	emit	SignalJustMouseRPress  (UniversalDx,UniversalDy);
}
void	mtGraphicUnitOG::SlotJustMouseRRelease(int UniversalDx,int UniversalDy)
{
	if(UseLongPush==false || PushedTimeer.hasExpired(LongPushMilisec)==false){
		emit	SignalJustMouseRRelease(UniversalDx,UniversalDy);
	}
	else{
		emit	SignalJustMouseRLongPress(UniversalDx,UniversalDy);
	}
}