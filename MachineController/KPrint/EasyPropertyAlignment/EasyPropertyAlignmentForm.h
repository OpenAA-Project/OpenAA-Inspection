#ifndef EASYPROPERTYALIGNMENTFORM_H
#define EASYPROPERTYALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XAlignmentLarge.h"
#include "PropertyAlignmentLargePacket.h"
#include "XIntClass.h"

namespace Ui {
class EasyPropertyAlignmentForm;
}
class SelectAlignmentAreaForm;

class EasyPropertyAlignmentForm : public GUIFormBase
{
    Q_OBJECT
    
	SelectAlignmentAreaForm		*SelectAlignmentAreaFormInst;
	AlignmentLargePointListPack	Marks;

	ListPhasePageLayerItemPack		AreaIDList;
	AlgorithmLibraryListContainer	LimitedLib;
public:
	int32	SlaveNo;

    explicit EasyPropertyAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyAlignmentForm();
    
	virtual	void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	StartInitial(void)	override;
	void	GenerateAutomatically(void);

	IntList	GetCurrentAreaPriority(void);
	void	ShowByAreaID(int AreaID);
	void	SetByAreaID(int AreaID);
signals:
	void	SignalBusy();
	void	SignalIdle();

private slots:
    void on_toolButtonAutoGenerate_clicked();
    void on_toolButtonAreaMode_clicked();
    void on_toolButtonDeleteAll_clicked();
    void on_toolButtonAreaPriority_clicked();
	void	ResizeAction();
    void on_tableWidgetMarkList_itemSelectionChanged();
    void on_tableWidgetMarkList_itemDoubleClicked(QTableWidgetItem *item);
	void	SlotChangedItems();
    void on_tableWidgetLimitedLib_doubleClicked(const QModelIndex &index);
    void on_toolButtonPriority_clicked();
    void on_pushButtonAddLimitedLib_clicked();

    void on_toolButtonAreaFromMask_clicked();

    void on_toolButtonAreaFromCAD_clicked();

private:
    Ui::EasyPropertyAlignmentForm *ui;

	void	ShowAreaName(void);
	void	ReqAreaID(void);
	void	ShowLimitedLib(void);
	void	ShowPointList(void);
};

class	IntegrationCmdGenerateAreaAndItem : public IntegrationCmdPacketBase
{
public:
	bool	GeneratePartialAlignment;
	IntList	ItemLibIDs;
	int32	AlignmntAreaErosion;
	int32	AlignmntPointSize;
	int32	AlignmntSearchAreaDot;
	int32	AlignmntSearchAreaDot2;
	int32	AlignmntSearchAreaDotMiddle;
	int32	AlignmntSearchAreaDotY;
	int32	AlignmntSearchAreaDot2Y;
	int32	AlignmntSearchAreaDotMiddleY;
	int32	AlignmntGeneratedLayer;
	bool	AlignmntJudgeWithBrDif;

	IntegrationCmdGenerateAreaAndItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdSetAreaMode : public IntegrationCmdPacketBase
{
public:
	bool	AreaMode;
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	IntegrationCmdSetAreaMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdClearAll : public IntegrationCmdPacketBase
{
public:
	bool	AreaMode;
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	IntegrationCmdClearAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	CmdEasyAlignmentDrawModePacket : public GUIDirectMessage
{
public:
	ListPhasePageLayerItemPack		AreaIDList;
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	CmdEasyAlignmentDrawModePacket(LayersBase *base):GUIDirectMessage(base){	AreaPriority.Add(XAlignmentLargeArea::_PriorityNone);	}
	CmdEasyAlignmentDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
	
class	CmdReqAreaMode : public GUIDirectMessage
{
public:
	bool	AreaMode;
	ListPhasePageLayerItemPack		AreaIDList;
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority
	bool	CharacterMode;

	CmdReqAreaMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAreaMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdReqAlignmentMark : public IntegrationCmdPacketBase
{
public:
	int32		Phase;
	IntList		AreaPriority;	//XAlignmentLargeArea::_EnumPriority
	ListPhasePageLayerItemPack		AreaIDList;

	IntegrationCmdReqAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationCmdAckAlignmentMark : public IntegrationCmdPacketBase
{
public:
	AlignmentLargePointListPack	Marks;

	IntegrationCmdAckAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetAlignmentMark : public IntegrationCmdPacketBase
{
public:
	int32		Phase;
	AlignmentLargePointList	Mark;

	IntegrationCmdSetAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};



class	IntegrationCmdReqAlignmentAreaID : public IntegrationCmdPacketBase
{
public:
	int32		Phase;
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	IntegrationCmdReqAlignmentAreaID(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckAlignmentAreaID : public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack		AreaID;

	IntegrationCmdAckAlignmentAreaID(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationCmdReqAlignmentLimitedLib : public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack		AreaID;

	IntegrationCmdReqAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckAlignmentLimitedLib : public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationCmdAckAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdAddAlignmentLimitedLib : public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack		AreaID;
	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationCmdAddAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdDelAlignmentLimitedLib : public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack		AreaID;
	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationCmdDelAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAutoGenerateMark: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack		AreaIDList;

	IntegrationAutoGenerateMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};




class	IntegrationCmdReqMakeAreaFromMask : public IntegrationCmdPacketBase
{
public:
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	IntegrationCmdReqMakeAreaFromMask(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdReqMakeAreaFromCAD : public IntegrationCmdPacketBase
{
public:
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	IntegrationCmdReqMakeAreaFromCAD(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // EASYPROPERTYALIGNMENTFORM_H
