#ifndef EASYPROPERTYDXFOPERATIONFORM_H
#define EASYPROPERTYDXFOPERATIONFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XAllocationLibByColor.h"
#include "XDXFOperationCommon.h"

namespace Ui {
class EasyPropertyDXFOperationForm;
}

class	DXFOperationBase;
class	MaskingBase;

class EasyPropertyDXFOperationForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;

    explicit EasyPropertyDXFOperationForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyDXFOperationForm();
    
	virtual void	ReadyParam(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	GenerateAutomatically(void);
	void	MakeAllocation(void);

	virtual void	LeavePage	(void)	override;
signals:
	void	SignalBusy();
	void	SignalIdle();
private slots:
    void on_toolButtonLoadDXF_clicked();
    void on_toolButtonAutoGenerate_clicked();
    void on_toolButtonDeleteAll_clicked();
	void	ResizeAction();
    void on_toolButtonRotate_clicked();
    void on_toolButtonMove_clicked();
    void on_toolButtonExtend_clicked();
    void on_toolButtonYMirror_clicked();
    void on_toolButtonXMirror_clicked();
    void on_toolButtonEnfatLine_clicked();
    void on_toolButtonShrinkY_clicked();
    void on_toolButtonTiltL_clicked();
    void on_toolButtonTiltR_clicked();
    void on_toolButtonDelBlade_clicked();
    void on_toolButtonSlightExtend_clicked();
    void on_toolButtonSlightShrinkY_clicked();
    void on_toolButtonAllocList_clicked();
    void on_toolButtonExtendX_clicked();
    void on_toolButtonShrinkX_clicked();

private:
    Ui::EasyPropertyDXFOperationForm *ui;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	DXFOperationBase	*GetDXFOperationBase(void);
	MaskingBase			*GetMaskingBase(void);
};

class	CmdReqEasyAllocationLibByColor: public GUIDirectMessage
{
public:
	int								ThresholdLevelID;
	AllocationLibByColorContainer	Container;

	CmdReqEasyAllocationLibByColor(LayersBase *base)
		:GUIDirectMessage(base),Container(DXFCommonDataID){		ThresholdLevelID=0;	}
	CmdReqEasyAllocationLibByColor(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase),Container(DXFCommonDataID){	ThresholdLevelID=0;	}
};

class	IntegrationCmdLoadDXF: public IntegrationCmdPacketBase
{
public:
	QString		FileName;
	QByteArray	DXFData;
	int			ActivePage;

	IntegrationCmdLoadDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdRotate: public IntegrationCmdPacketBase
{
public:
	int			ActivePage;
	IntegrationCmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdExtend: public IntegrationCmdPacketBase
{
public:
	double	ZoomX;
	double	ZoomY;
	double	YShear;
	int			ActivePage;

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
	int		ActivePage;

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
	int			ActivePage;
	IntegrationCmdXMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdYMirror: public IntegrationCmdPacketBase
{
public:
	int			ActivePage;
	IntegrationCmdYMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdEnfatLine: public IntegrationCmdPacketBase
{
public:
	double	EnfatLineDot;

	IntegrationCmdEnfatLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
									  
	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdDXFDeleteAllItem: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdDXFDeleteAllItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
									  
	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdTilt: public IntegrationCmdPacketBase
{
public:
	double	Radian;
	int		ActivePage;

	IntegrationCmdTilt(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
									  
	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};
class	IntegrationCmdDelBrade : public IntegrationCmdPacketBase
{
public:
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	BladeAreaX1;
	int32	BladeAreaY1;
	int32	BladeAreaX2;
	int32	BladeAreaY2;

	IntegrationCmdDelBrade(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

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

class	CmdReqCurrentPage: public GUIDirectMessage
{
public:
	int		ActivePage;

	CmdReqCurrentPage(LayersBase *base)
		:GUIDirectMessage(base)	{	}
	CmdReqCurrentPage(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase){	}
};

#endif // EASYPROPERTYDXFOPERATIONFORM_H
