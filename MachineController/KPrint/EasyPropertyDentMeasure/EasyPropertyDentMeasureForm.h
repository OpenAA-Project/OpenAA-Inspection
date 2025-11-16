#ifndef EASYPROPERTYDENTMEASUREFORM_H
#define EASYPROPERTYDENTMEASUREFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XMeasureCommon.h"
#include <QPushButton>
#include <QModelIndex>
#include <QStringList>

namespace Ui {
class EasyPropertyDentMeasureForm;
}

class	DentMeasurePointButton : public QPushButton
{
	Q_OBJECT
public:
	int	EndNo;	//0:�E�n�E�_	1:�E�I�E�_
	int	MeasureNo;

	DentMeasurePointButton(void);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int EndNo , int MeasureNo);
};

class EasyPropertyDentMeasureForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;
	int32	SlaveNo;

	int		Row2GUITable[12];
	int		GUI2RowTable[12];

	bool	GenerateFilmBlock;
	int		InspectionIDNoFilmUpper	;
	int		InspectionIDNeedFilmUpper;
	int		InspectionIDNoFilmLower	;
	int		InspectionIDNeedFilmLower;
	int		FilmNeededOffsetY;
	int		FilmNoNeedOffsetY;
	bool	BladeUpsideDown;
	bool	GenerateFilmInLoadingMaster;
	int		GenerateFilmInLoadingMasterSlaveNo;

    explicit EasyPropertyDentMeasureForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyDentMeasureForm();
    
	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	GenerateAutomatically(void);
signals:
	void	SignalBusy();
	void	SignalIdle();
private slots:
    void on_toolButtonAutoGenerate_clicked();
    void on_PushButtonAddLine_clicked();
    void on_PushButtonRemoveLine_clicked();
    void on_PushButtonSaveBladePos_clicked();
    void on_PushButtonLoadBladePos_clicked();
	void	ResizeAction();
	void	SlotBladeListIndexChanged ( int index );
	void	SlotFilmListIndexChanged ( int index );
    void on_toolButtonGetCorrentValues_clicked();
    void on_toolButtonSetCorrentValues_clicked();
    void on_toolButtonGetCorrentValuesTarget_clicked();
    void on_PushButtonManualCreateArea_clicked();
    void on_tableWidgetBladePos_clicked(const QModelIndex &index);
    void on_tableWidgetBladePos_doubleClicked(const QModelIndex &index);
	void	SlotEndPointClicked(int EndNo,int MeasureNo);
	void	SlotFilmEndPointClicked(int EndNo,int MeasureNo);
    void on_toolButtonSetName_clicked();
    void on_toolButtonGenFilmUpper_clicked();
    void on_toolButtonGenFilmLower_clicked();
    void on_pushButtonSetUpper_clicked();
    void on_pushButtonSetLower_clicked();

    void on_toolButtonBlade_clicked();
    void on_toolButtonFilm_clicked();

    void on_PushButtonGenerateFilmPos_clicked();

private:
    Ui::EasyPropertyDentMeasureForm *ui;

	void	ShowList(void);
	void	ShowFilmList(void);
	void	ShwListInner(int row, int Index );
	void	ShwFilmListInner(int grow, int Index );
	void	GetDataFromList(void);
	void	GenerateAutomaticallyPure(bool OnlyGenerateFilmLen=false);
	void	SetColumn0(QStringList	&List ,struct MeasureHVInfo	&p ,int row,int ComboIndex);
	void	SetFilmColumn0(QStringList	&List ,struct MeasureHVInfo	&p ,int grow,int ComboIndex);
	void	SetOnlyBladeThreshold(void);
	void	WriteDefault(void);
};

class	IntegrationCmdGenerateDentAndMeasure : public IntegrationCmdPacketBase
{
public:
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	BladeLeft ;
	int32	BladeRight;
	IntList	ItemLibIDs;
	int32	LineLib;
	int32	RxLineLib;
	int32	DistanceLib;
	int32	MaskLib;
	int32	BladeHoleMinArea	;
	int32	BladeHoleErosionDot	;
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;
	bool			OnlyGenerateFilmLen;

	IntegrationCmdGenerateDentAndMeasure(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};


class	IntegrationCmdReqCorrectValues : public IntegrationCmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	bool			Mastered;

	IntegrationCmdReqCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAckCorrectValues : public IntegrationCmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;

	IntegrationCmdAckCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	IntegrationCmdSetCorrectValues : public IntegrationCmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	int32	LineLib;
	int32	RxLineLib;
	int32	DistanceLib;
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	MaskLib;

	IntegrationCmdSetCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdSetOnlyBladeThreshold : public IntegrationCmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;

	IntegrationCmdSetOnlyBladeThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};
class	IntegrationCmdSetMeasureEndPoint : public IntegrationCmdPacketBase
{
public:
	int		EndNo;
	int		MeasureNo;
	int		GlobalX;
	int		GlobalY;

	IntegrationCmdSetMeasureEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdUpdateBladeList : public GUIDirectMessage
{
public:

	IntegrationCmdUpdateBladeList(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCmdUpdateBladeList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationReqBladeList : public GUIDirectMessage
{
public:

	IntegrationReqBladeList(LayersBase *base):GUIDirectMessage(base){}
	IntegrationReqBladeList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	IntegrationCmdFilm : public IntegrationCmdPacketBase
{
public:
	bool	GenerateMode;
	bool	UpperMode;
	int		UniversalDx;
	int		UniversalDy;

	IntegrationCmdFilm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationReqMeasurePosition : public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		Page;
	int		DistanceItemID;

	IntegrationReqMeasurePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckMeasurePosition : public IntegrationCmdPacketBase
{
public:
	int		Point1X,Point1Y;
	int		Point2X,Point2Y;

	IntegrationAckMeasurePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


#endif // EASYPROPERTYDENTMEASUREFORM_H
