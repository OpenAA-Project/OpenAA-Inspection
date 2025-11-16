#ifndef EACHTHRESHOLDWHOLEFORM_H
#define EACHTHRESHOLDWHOLEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XEachThresholdCommon.h"
#include "XIntegrationPacketComm.h"
#include "XPasswordQWidget.h"
#include "mtGraphicUnit.h"
#include "XAlgorithmLibrary.h"
#include <QTimer>

namespace Ui {
class EachThresholdWholeForm;
}
class ButtonSettingThresholdForm;
class ThresholdWholeHistoryList;

class EachThresholdWholeForm : public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
    bool	OnChanging;
	mtGraphicUnit	ImagePanel;
	bool	ReEntrant;
	AlgorithmLibraryList	SelectedLib;
	FlexArea	SelectedArea;
	QTimer		TM;
	bool		DrawModeSelectedArea;
	QImage		ImageSelectedArea;

public:
    explicit EachThresholdWholeForm(LayersBase *base ,ButtonSettingThresholdForm *p ,QWidget *parent = 0);
    ~EachThresholdWholeForm();
    
private slots:
    void on_doubleSpinBoxSizeBMM_valueChanged(double arg1);
    void on_spinBoxSizeB_valueChanged(int arg1);
    void on_doubleSpinBoxLengthBMM_valueChanged(double arg1);
    void on_spinBoxLengthB_valueChanged(int arg1);
    void on_horizontalSliderSizeB_valueChanged(int value);
    void on_horizontalSliderLengthB_valueChanged(int value);
 
    void on_doubleSpinBoxSizeNMM_valueChanged(double arg1);
    void on_spinBoxSizeN_valueChanged(int arg1);
    void on_doubleSpinBoxLengthNMM_valueChanged(double arg1);
    void on_spinBoxLengthN_valueChanged(int arg1);
    void on_horizontalSliderSizeN_valueChanged(int value);
    void on_horizontalSliderLengthN_valueChanged(int value);
 
    void on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1);
    void on_spinBoxRedOKDot_valueChanged(int arg1);
    void on_doubleSpinBoxMultiSizeMM_valueChanged(double arg1);
    void on_spinBoxMultiSize_valueChanged(int arg1);
    void on_spinBoxMultiNGCount_valueChanged(int arg1);
    void on_doubleSpinBoxOozingMM_valueChanged(double arg1);
    void on_spinBoxOozing_valueChanged(int arg1);
    void on_toolButtonBrightnessDarkStrictLoose_clicked();
    void on_toolButtonBrightnessLightLoose_clicked();
    void on_toolButtonShiftLoose_clicked();
    void on_toolButtonBrightnessDarkStrict_clicked();
    void on_toolButtonBrightnessLightStrict_clicked();
    void on_toolButtonShiftStrict_clicked();
    void on_toolButtonOKSize_clicked();
    void on_toolButtonClose_clicked();

	void on_horizontalSliderRedOKDot_valueChanged(int value);
    void on_horizontalSliderSIze_valueChanged(int value);
    void on_horizontalSliderNGCount_valueChanged(int value);
    void on_horizontalSliderOozing_valueChanged(int value);
    void on_spinBoxBrightnessDark_valueChanged(int arg1);
    void on_spinBoxBrightnessLight_valueChanged(int arg1);
    void on_spinBoxShift_valueChanged(int arg1);
    void on_doubleSpinBoxSearchAreaXMM_valueChanged(double arg1);
    void on_spinBoxSearchAreaX_valueChanged(int arg1);
    void on_listWidgetOperationHistory_currentRowChanged(int currentRow);
    void on_horizontalSliderSearchAreaX_valueChanged(int value);
    void on_doubleSpinBoxSearchAreaYMM_valueChanged(double arg1);
    void on_spinBoxSearchAreaY_valueChanged(int arg1);
    void on_horizontalSliderSearchAreaY_valueChanged(int value);
	void on_toolButtonEnable_clicked();

	void	CanvasSlotDrawEnd(void);
	void	CanvasSlotOnPaint(QPainter &);
	void	SlotMouseWheel(int,int,int);
	void	SlotTimeOut();

    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_clicked();

private:
    Ui::EachThresholdWholeForm *ui;

    void	ShowDataAfterMarker(void);

	double	GetZoomRate(void)			;
	mtGraphicUnit	*GetCanvas(void)	;
	int		GetMovx(void)				;
	int		GetMovy(void)				;
	int		GetCanvasWidth(void)		;
	int		GetCanvasHeight(void)		;
	void	SetMovXY(int mx,int my)		;
	double	GetZoomRateForWhole(void)	;
	double	GetZoomRateForFit(void)		;
	void	SetZoomRate(double ZoomRate);
	double	GetMaxZoomValue(void)		;
	double	GetMinZoomValue(void)		;
	void	SetMaxZoomValue(double d)	;
	void	SetMinZoomValue(double d)	;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);

	void	GetHistoryListFromWindow(ThresholdWholeHistoryList *Data);
	void	RestoreHistoryListToWindow(ThresholdWholeHistoryList *Data);
	void	ShowHistoryList(void);
};

//===============================================================================

class	IntegrationReqThresholdPanelImage: public IntegrationCmdPacketBase
{
	friend	class ButtonSettingThresholdForm;
public:
	double	ZoomRate;
	int		movx,movy;
	int		ImageW,ImageH;
	int		Phase;

	IntegrationReqThresholdPanelImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);

private:

};

class	IntegrationAckThresholdPanelImage: public IntegrationCmdPacketBase
{
	friend	class ButtonSettingThresholdForm;
public:
	//QImage	*TargetImageWithNG;
	//int32	SlaveNo;

	IntegrationAckThresholdPanelImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);
	virtual	~IntegrationAckThresholdPanelImage(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};


//===============================================================================

class	IntegrationReqThresholdLibID: public IntegrationCmdPacketBase
{
public:
	int			FilterLibType;
	FlexArea	Area;
	int			Phase;

	IntegrationReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);

private:

};
class	IntegrationAckThresholdLibID: public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryListContainer	Libs;

	IntegrationAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	GUICmdReqThresholdLibID: public GUICmdPacketBase
{
public:
	int			FilterLibType;
	FlexArea	Area;
	int			Phase;

	GUICmdReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckThresholdLibID: public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	Libs;

	GUICmdAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

#endif // EACHTHRESHOLDWHOLEFORM_H
