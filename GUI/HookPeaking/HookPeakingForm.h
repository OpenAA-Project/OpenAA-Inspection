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
#include <QThread>
#include <QImage>
#include <QPainter>
#include "XServiceForLayers.h"

namespace Ui {
class HookPeakingForm;
}

class	ThreadPeaking;

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

signals:
	void	SignalChanged(int Position);
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
