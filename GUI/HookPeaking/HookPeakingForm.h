#ifndef HOOKPEAKINGFORM_H
#define HOOKPEAKINGFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "mtPushButtonColored.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"
#include "fftw3.h"
#include <QThread>
#include <QImage>
#include <QPainter>
#include "XServiceForLayers.h"

namespace Ui {
class HookPeakingForm;
}
class HookPeakingForm;

class	ThreadPeaking : public QThread,public ServiceForLayers
{
    Q_OBJECT
	friend	class HookPeakingForm;

	int	DotPerLine	;
	int	MaxLines	;
	int	ynumb;
	int	xnumb;
	fftw_complex *in[5000];
	fftw_complex *out[5000];
	fftw_plan	p[5000];
	ImageBuffer			**PeakBuff;
	QMutex				PeakMutex;
	int					AllocatedCount;
	HookPeakingForm		*Parent;
	int	Isolation;
	int	Turn;
public:
	int					*CRadius;
	volatile	bool	Terminated;

	ThreadPeaking(LayersBase *base ,HookPeakingForm *parent);
	~ThreadPeaking(void);

	virtual	void	run();

signals:
	void	SignalShowPeaking();
private:
	void	Realloc(void);
	void	MakePeakData(int localPage);
	int		GetPage(void);
	
	int		MakePeakData(int SIZEX,int SIZEY,fftw_plan p,fftw_complex *in,fftw_complex *out
						,ImageBuffer &Src, ImageBuffer &Image,int x1,int y1,int x2,int y2);
	void	CopyToParent(int localPage);
};


class HookPeakingForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

	friend	class	ThreadPeaking;

	GUIFormBasePointerContainer		TargetPanels;
	mtPushButtonColored	*ButtonColor;
	//ImageBuffer			**PeakBuff;
	int					AllocatedCount;

	int		LastAlpha;
	BYTE	RTable[256][256];
	BYTE	GTable[256][256];
	BYTE	BTable[256][256];

	ThreadPeaking	*Thread;
	DWORD			LastPaintTime;
	QColor			LastColor;
	int				DrawTurn;
public:
	QStringList			HookTargetListInst;
	int					CRadius;
	volatile	bool	Calclating;
	bool				ModeShowModeButton;
	bool				ModeShowColorButton;
	QString				MemoryType;
	int32				InitialValue;
	
    explicit HookPeakingForm(LayersBase *Base ,QWidget *parent = 0);
    ~HookPeakingForm();

	virtual void	Prepare(void)		override;
			void	Release(void);
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;
	void	Draw	(QPainter &pnt	,QImage &PntImage
					,double ZoomRate,int movx ,int movy 
					,int CanvasWidth , int CanvasHeight);
	bool	DrawInPage	(QImage &PntImage,int page 
						,double ZoomRate,int movx ,int movy 
						,int CanvasWidth , int CanvasHeight
						,int tDrawTurn);
	virtual	QStringList	GetRelatedForm(void)	override	{	return HookTargetListInst;	}
	void	SetCalclating(bool b);
private slots:
    void on_toolButtonMode_clicked();
    void on_toolButtonColor_clicked();
	void	SlotShowPeaking();
private:
    Ui::HookPeakingForm *ui;
    
private slots:
	void	ResizeAction();
    void on_horizontalSliderTransparentRate_valueChanged(int value);
};

class	GUICmdMakePeakData: public GUICmdPacketBase
{
public:
	bool	Calclating;
	QString	InstName;

	GUICmdMakePeakData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


#endif // HOOKPEAKINGFORM_H
