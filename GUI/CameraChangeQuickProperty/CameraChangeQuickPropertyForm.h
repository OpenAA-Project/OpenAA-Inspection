#ifndef CAMERACHANGEQUICKPROPERTYFORM_H
#define CAMERACHANGEQUICKPROPERTYFORM_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include<QColor>
#include "XColorSpace.h"
#include "NListComp.h"
#include "XYCross.h"
#include<QIODevice>
#include<QPainter>
#include<QScrollArea>
#include<QTableWidget>
#include<QLabel>
#include<QLineEdit>
#include<QSpinBox>
#include "XResult.h"
#include "XCameraCommon.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"

namespace Ui {
class CameraChangeQuickPropertyForm;
}

class CameraChangeQuickPropertyForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT
    FloatRGBColor   RegularColor;
    FlexArea        ReferenceArea;
    QImage          ReferenceImage;
    mtFrameDraw::DrawingMode    SavedDrawingMode;
public:
    QString             TitleName;
    QString             LinkPanelInst;
    CameraQuickProperty Attr;
    int                 VValue;
    QString CameraQuickPropertyStr;

    explicit CameraChangeQuickPropertyForm(LayersBase *Base,QWidget *parent = 0);
    ~CameraChangeQuickPropertyForm();

    virtual	void	ReadyParam(void)	override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	    override;
	virtual void	ShowInPlayer    (int64 shownInspectionID=-1)	override;
    virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)      override;

    void    SetReferenceArea(FlexArea &Area);
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
    void	Draw	(DisplayImage *DImage,QPainter &pnt	,double ZoomRate,int movx ,int movy);

private slots:
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();
    void on_doubleSpinBoxValue_valueChanged(double arg1);
    void on_toolButtonTitle_clicked();

private:
    Ui::CameraChangeQuickPropertyForm *ui;
};
//============================================================================================

class	GUICmdCameraChangeQuickProperty : public GUICmdPacketBase
{
public:
    CameraQuickProperty Attr;
    double              VValue;

	GUICmdCameraChangeQuickProperty(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdCameraChangeQuickProperty : public GUIDirectMessage
{
public:
    CameraQuickProperty Attr;
    int                 VValue;

	CmdCameraChangeQuickProperty(LayersBase *base):GUIDirectMessage(base){}
	CmdCameraChangeQuickProperty(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqCurrentCameraChangeQuickProperty : public GUIDirectMessage
{
public:
    CameraQuickProperty Attr;
    int                 VValue;

	CmdReqCurrentCameraChangeQuickProperty(LayersBase *base):GUIDirectMessage(base){}
	CmdReqCurrentCameraChangeQuickProperty(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCameraAdjustment : public GUIDirectMessage
{
public:
    bool    ON;

	CmdCameraAdjustment(LayersBase *base):GUIDirectMessage(base){}
	CmdCameraAdjustment(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//============================================================================================

class	GUICmdReqBrightness : public GUICmdPacketBase
{
public:
    FlexArea    ReferenceArea;

	GUICmdReqBrightness(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBrightness : public GUICmdPacketBase
{
public:
    FloatRGBColor   CurrentColor;

	GUICmdAckBrightness(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // CAMERACHANGEQUICKPROPERTYFORM_H
