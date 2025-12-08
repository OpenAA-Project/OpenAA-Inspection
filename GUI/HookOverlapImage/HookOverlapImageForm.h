#ifndef HOOKOVERLAPIMAGEFORM_H
#define HOOKOVERLAPIMAGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"
#include<QImage>
#include<QString>
#include<QPainter>

namespace Ui {
class HookOverlapImageForm;
}

class	GUICmdSendBmp;
class	GUICmdReqBmp;

class HookOverlapImageForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

	QImage			*OverlapImage;
	GUIFormBasePointerContainer	TargetPanels;
	GUICmdSendBmp	**BmpReceiver;
	GUICmdReqBmp	**BmpRequester;
	int				AllocedBmp;
	DisplayImage::DisplayType	DType;
	volatile	int	SlidebarPosition;
	bool			Active;
public:
	QStringList	HookTargetListInst;
	QString	ImageType;
	QString	SliderDirection;
	bool	ShowNGMarkInTarget;

    explicit HookOverlapImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~HookOverlapImageForm();

	virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;
	void	Draw	(DisplayImage	*DImage
						,QPainter &pnt	,QImage &PntImage
						,double ZoomRate,int movx ,int movy
						,int CanvasWidth ,int CanvasHeight);
	void	Draw	(DisplayImage	*DImage
						,QPainter &pnt	,QImage &PntImage
						,double ZoomRate,int movx ,int movy
						,int CanvasWidth ,int CanvasHeight
						,int V);
	virtual	QStringList	GetRelatedForm(void)	override	{	return HookTargetListInst;	}

	void	SetActive(bool b);
	bool	GetActive(void)		{	return Active;	}

	virtual	void	CalledFromDeridedParent(GUIFormBase *Parent, QEvent * event)	override;
	void	GetState(DisplayImage::DisplayType &dType ,bool &Checked,int &Value);
private:
    Ui::HookOverlapImageForm *ui;

	void	AllocInnerBuff(void);
	bool	DrawImage(DisplayImage *DImage ,QPainter &pnt ,QImage &PntImage ,IntList &LayerList, int Alpha);
	bool	DrawImage(QPainter &pnt ,QImage &PntImage
										,IntList &_LayerList , int Alpha
										,int movx ,int movy ,double ZoomRate);
	void	ChangeDxy2Gxy(DisplayImage	*DImage ,int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(DisplayImage	*DImage ,int Gx,int Gy ,int &Dx ,int &Dy);
private slots:
	void	ResizeAction();
    void on_horizontalSlider_valueChanged(int value);

signals:
	void	SignalChanged(int Position);
};

class	CmdGetAlphaMasterToTarget : public GUIDirectMessage
{
public:
	double	Alpha;
	bool	Active;

	CmdGetAlphaMasterToTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlphaMasterToTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetAlphaMasterToTarget : public GUIDirectMessage
{
public:
	double	Alpha;		//0.0-1.0	0:Overlap	1:DisplayImage
	bool	Active;

	CmdSetAlphaMasterToTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAlphaMasterToTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDrawOverlapImage: public GUIDirectMessage
{
public:
	QImage	*PntImage;
	double ZoomRate;
	int		movx ,movy;
	int CanvasWidth;
	int CanvasHeight;

	CmdDrawOverlapImage(LayersBase *base):GUIDirectMessage(base){}
	CmdDrawOverlapImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // HOOKOVERLAPIMAGEFORM_H
