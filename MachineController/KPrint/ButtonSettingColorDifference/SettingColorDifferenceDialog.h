#ifndef SETTINGCOLORDIFFERENCEDIALOG_H
#define SETTINGCOLORDIFFERENCEDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QImage>
#include <QColor>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"
#include "XColorDifference.h"
#include "mtGraphicUnit.h"

namespace Ui {
class SettingColorDifferenceDialog;
}
class	ButtonSettingColorDifferenceForm;
class	SettingColorDifferenceDialog;

class	HSVMap : public QWidget
{
    Q_OBJECT
		
	SettingColorDifferenceDialog	*Parent;
	double	ZoomRate;
	QImage	HSVImageMap;
	QTimer	TM;
	bool	FlapToShowThreshold;
public:
	int	V;

	HSVMap(SettingColorDifferenceDialog *p);

	void	SetV(int v);
private:
	virtual	void 	paintEvent ( QPaintEvent * event ) 			override;
	virtual	void 	mouseReleaseEvent ( QMouseEvent * event )	override;
	virtual	void	resizeEvent ( QResizeEvent * event )		override;

signals:
	void	SignalClickRGB(int R ,int G ,int B);

private slots:
	void	SlotTimeOut();
};

class	ItemInfoList : public NPListSaveLoad<ItemInfoList>
{
public:
	int	Phase;
	int	Page;
	int	ItemID;
	int	MasterCx,MasterCy;
	int	Error;

	ItemInfoList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	ItemInfoListContainer : public NPListPackSaveLoad<ItemInfoList>
{
public:
	ItemInfoListContainer(void){}

	virtual	ItemInfoList	*Create(void)	{	return new ItemInfoList();	}
};


class	PanelShowImage : public mtGraphicUnit,public ServiceForLayers
{
    Q_OBJECT
		
	bool			ModeShowCurrentDraw;
	ItemInfoList	*LastIndex	;
	double			LastZoomRate;
	int				Lastmovx	;
	int				Lastmovy	;
	SettingColorDifferenceDialog	*Parent;
	QTimer	TM;
public:
	QColor	DrawColor	;
	QColor	CurrentColor;
	ItemInfoList	*CurrentIndex;
	QImage	ImageTargetWithItem;

	PanelShowImage(SettingColorDifferenceDialog *p);

protected:
	virtual	bool	event(QEvent *event)	override;
private slots:
	void	SlotOnPaint(QPainter &pnt);
	//void	SlotMouseLDoubleClick(int ,int);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotTimeOut();
private:
	bool	ShouldPaint(void);
};

class SettingColorDifferenceDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ButtonSettingColorDifferenceForm	*Parent;
	HSVMap					PanelHSVMap;
	ItemInfoListContainer	ItemInfos;
	PanelShowImage			ImagePanel;

	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;

	bool		OutputConstantly;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	PreciseColorListConatiner	FlowBrightness;	//After regulation

	PreciseColor	MasterColor;
	PreciseColor	TargetColor;

	PreciseColor	ReferedCurrentColor;
	PreciseColor	FlowCenterColor;

	struct{
		double	HAvr,SAvr,VAvr;
		double	Hvl,Hvh;
		double	Svl,Svh;
		double	Vvl,Vvh;
	}StatisticData;

public:
    explicit SettingColorDifferenceDialog(LayersBase *base ,ButtonSettingColorDifferenceForm *p,QWidget *parent = 0);
    ~SettingColorDifferenceDialog();
    
	bool	IsInsideInThresholdOK(int R,int G,int B);
	bool	IsInsideInThresholdNG(int R,int G,int B);
	bool	IsInsideInCurrentColor(int R,int G,int B);

	int		GetSlaveNo(void);
private slots:
    void on_tableWidgetItemList_pressed(const QModelIndex &index);
    void on_verticalSliderY_valueChanged(int value);
    void on_spinBoxK_valueChanged(int arg1);
    void on_listWidgetOKBrightness_pressed(const QModelIndex &index);
    void on_listWidgetNGBrightness_pressed(const QModelIndex &index);
    void on_toolButtonDelOKColor_clicked();
    void on_toolButtonDelNGColor_clicked();
    void on_toolButtonCurrentColor_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();
    void on_doubleSpinBoxAdoptedRate_valueChanged(double arg1);
    void on_comboBoxJudgeMethod_currentIndexChanged(int index);
    void on_doubleSpinBoxTHDeltaE_valueChanged(double arg1);
    void on_doubleSpinBoxdH_valueChanged(double arg1);
    void on_doubleSpinBoxdSL_valueChanged(double arg1);
    void on_doubleSpinBoxdSH_valueChanged(double arg1);
    void on_doubleSpinBoxdVL_valueChanged(double arg1);
    void on_doubleSpinBoxdVH_valueChanged(double arg1);
	void	SlotClickRGB(int R ,int G ,int B);
private:
    Ui::SettingColorDifferenceDialog *ui;

	void	ShowItemList(void);
	void	ShowRGB(int R, int G ,int B);
	void	ShowOKColorList(void);
	void	ShowNGColorList(void);
	void	Calc(void);
};

//-------------------------------------------------------------------------------------------

class	IntegrationCmdReqItemInfos : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqItemInfos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckItemInfos : public IntegrationCmdPacketBase
{
public:
	ItemInfoListContainer	ItemInfos;

	IntegrationCmdAckItemInfos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//-------------------------------------------------------------------------------------------

class	IntegrationCmdReqItemData : public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	IntegrationCmdReqItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckItemData : public IntegrationCmdPacketBase
{
public:
	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;

	bool		OutputConstantly;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	PreciseColorListConatiner	FlowBrightness;	//After regulation

	PreciseColor	MasterColor;
	PreciseColor	TargetColor;

	PreciseColor	ReferedCurrentColor;
	PreciseColor	FlowCenterColor;

	struct{
		double	HAvr,SAvr,VAvr;
		double	Hvl,Hvh;
		double	Svl,Svh;
		double	Vvl,Vvh;
	}StatisticData;

	IntegrationCmdAckItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdReqTryItem : public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;

	bool		OutputConstantly;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	PreciseColorListConatiner	FlowBrightness;	//After regulation

	PreciseColor	MasterColor;
	PreciseColor	TargetColor;

	PreciseColor	ReferedCurrentColor;
	PreciseColor	FlowCenterColor;

	struct{
		double	HAvr,SAvr,VAvr;
		double	Hvl,Hvh;
		double	Svl,Svh;
		double	Vvl,Vvh;
	}StatisticData;


	IntegrationCmdReqTryItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	IntegrationCmdAckTryItem : public IntegrationCmdPacketBase
{
public:
	int	Error;
	double	DeltaE;
	double	LenOK;
	double	LenNG;
	PreciseColor	ReferenceColor1;
	PreciseColor	ReferenceColor2;
	PreciseColor	MasterColor	;
	PreciseColor	TargetColor	;
	struct{
		double		MasterH,MasterS,MasterV;
		double		TargetH,TargetS,TargetV;
		double		SigmaH,SigmaS,SigmaV;
	}StatisticData;

	IntegrationCmdAckTryItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationCmdReqSetItemOnly : public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;

	bool		OutputConstantly;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	PreciseColorListConatiner	FlowBrightness;	//After regulation


	IntegrationCmdReqSetItemOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	IntegrationCmdReqSetItemAll : public IntegrationCmdPacketBase
{
public:
	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;


	IntegrationCmdReqSetItemAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationReqImageColorDifference : public IntegrationCmdPacketBase
{
public:
	struct{
		int		ItemPhase	;
		int		ItemPage	;
		int		ItemID		;
		int		CurrentPhase;
		double	ZoomRate	;
		int		movx		;
		int		movy		;
		int		ImageW		;
		int		ImageH		;
	}Info;
	QColor	DrawColor	;
	QColor	CurrentColor;

	IntegrationReqImageColorDifference(LayersBase *base
										,const QString &EmitterRoot ,const QString &EmitterName 
										,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo
							,int32 cmd 
							,QString &EmitterRoot,QString &EmitterName);
};


class	IntegrationAckImageColorDifference : public IntegrationCmdPacketBase
{
public:
	QImage	Image;

	IntegrationAckImageColorDifference(LayersBase *base
										,const QString &EmitterRoot ,const QString &EmitterName
										,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo
							,int32 cmd
							,QString &EmitterRoot,QString &EmitterName){}
};


#endif // SETTINGCOLORDIFFERENCEDIALOG_H
