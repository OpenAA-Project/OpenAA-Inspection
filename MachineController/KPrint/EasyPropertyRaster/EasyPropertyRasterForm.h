#ifndef EASYPROPERTYRASTERFORM_H
#define EASYPROPERTYRASTERFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XGUIRasterPacket.h"

namespace Ui {
class EasyPropertyRasterForm;
}

class RasterBase;
class MaskingBase;

class EasyPropertyRasterForm : public GUIFormBase
{
    Q_OBJECT

	RasterElementListContainer		Elements;
	PageElementIDClassContainer		ElementIDList;
public:
	int32	SlaveNo;

    explicit EasyPropertyRasterForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyRasterForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	GenerateAutomatically(void);
	void	MakeAllocation(void);
	virtual void	LeavePage	(void)	override;
	virtual	void	StartInitial(void)	override;
signals:
	void	SignalBusy();
	void	SignalIdle();   

private slots:
    void on_toolButtonLoadPDF_clicked();
    void on_toolButtonDeleteAll_clicked();
    void on_toolButtonRotate_clicked();
    void on_toolButtonYMirror_clicked();
    void on_toolButtonXMirror_clicked();
    void on_toolButtonExtend_clicked();
    void on_toolButtonShrinkY_clicked();
    void on_toolButtonTiltL_clicked();
    void on_toolButtonTiltR_clicked();
    void on_toolButtonSlightExtend_clicked();
    void on_toolButtonSlightShrinkY_clicked();
    void on_toolButtonMove_clicked();
	void	ResizeAction();
    void on_toolButtonAutoGenerate_clicked();

    void on_toolButtonExtendX_clicked();
    void on_toolButtonShrinkX_clicked();
    void on_toolButtonSlightExtend_2_clicked();
    void on_toolButtonSlightShrinkY_2_clicked();
    void on_toolButtonAdjustPosition_clicked();
    void on_tableWidgetAreaList_itemSelectionChanged();
    void on_toolButtonRegColor_clicked();
    void on_toolButtonRegArea_clicked();
    void on_toolButtonGenerateAlgorithm_clicked();
    void on_tableWidgetAreaList_doubleClicked(const QModelIndex &index);

private:
    Ui::EasyPropertyRasterForm *ui;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	RasterBase	*GetRasterBase(void);
	MaskingBase	*GetMaskingBase(void);

	void	ShowAlignmentList(void);
};

class	IntegrationCmdLoadRaster: public IntegrationCmdPacketBase
{
public:
	QString		FileName;
	QByteArray	RasterData;

	IntegrationCmdLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdRotate: public IntegrationCmdPacketBase
{
public:

	IntegrationCmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdExtend: public IntegrationCmdPacketBase
{
public:
	double	ZoomX;
	double	ZoomY;
	double	YShear;

	IntegrationCmdExtend(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdMoveXY: public IntegrationCmdPacketBase
{
public:
	double	MovX;
	double	MovY;

	IntegrationCmdMoveXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAutoGenerate: public IntegrationCmdPacketBase
{
public:
	IntList	ColorCode;
	QColor	Color;
	int	GenLibType;
	int	GenLibID;

	IntegrationCmdAutoGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdExecuteInitialMask: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdExecuteInitialMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};
class	IntegrationCmdXMirror: public IntegrationCmdPacketBase
{
public:

	IntegrationCmdXMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdYMirror: public IntegrationCmdPacketBase
{
public:

	IntegrationCmdYMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdRasterDeleteAllItem: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRasterDeleteAllItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
									  
	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdTilt: public IntegrationCmdPacketBase
{
public:
	double	Radian;

	IntegrationCmdTilt(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
									  
	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdReqMoveMode : public GUIDirectMessage
{
public:
	bool	MoveMode;

	IntegrationCmdReqMoveMode(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCmdReqMoveMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	IntegrationCmdSetMoveMode : public GUIDirectMessage
{
public:
	bool	MoveMode;

	IntegrationCmdSetMoveMode(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCmdSetMoveMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdDelMaskByCAD : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};


class	IntegrationCmdReqAddArea : public GUIDirectMessage
{
public:
	FlexArea	AddedArea;

	IntegrationCmdReqAddArea(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCmdReqAddArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdAddRegArea: public IntegrationCmdPacketBase
{
public:
	FlexArea	AddedArea;

	IntegrationCmdAddRegArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationCmdAddRegColorArea: public IntegrationCmdPacketBase
{
public:
	FlexArea	PickupArea;
	int			LibID;

	IntegrationCmdAddRegColorArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=====================================================================================================
class	IntegrationCmdReqElementInfo: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqElementInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationCmdAckElementInfo: public IntegrationCmdPacketBase
{
public:
	RasterElementListContainer		Elements;
	PageElementIDClassContainer		ElementIDList;

	IntegrationCmdAckElementInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetCurrentElementID: public IntegrationCmdPacketBase
{
public:
	int	CurrentElementID;

	IntegrationCmdSetCurrentElementID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdSetRegColor: public IntegrationCmdPacketBase
{
public:
	bool	ModeRegArea;
	bool	ModeRegColor;

	IntegrationCmdSetRegColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdReqRegColorElementID : public GUIDirectMessage
{
public:
	bool	ModeRegColor;
	int		CurrentElementID;

	IntegrationCmdReqRegColorElementID(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCmdReqRegColorElementID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdGeneraeRasterAlgorithm: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdGeneraeRasterAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdDeleteRegColor: public IntegrationCmdPacketBase
{
public:
	int	Page		;
	int	ElementID	;

	IntegrationCmdDeleteRegColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // EASYPROPERTYRASTERFORM_H
