#ifndef EASYPROPERTYMASKINGFORM_H
#define EASYPROPERTYMASKINGFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
#include <QModelIndex>
#include <QTableWidgetItem>
#include <QTimer>
#include "XMasking.h"

namespace Ui {
class EasyPropertyMaskingForm;
}

class EasyPropertyMaskingForm : public GUIFormBase
{
    Q_OBJECT
    AlgorithmLibraryListContainer	LimitedLib;
	QTimer	TM;
	bool	ReEntrant;
public:
	int32	SlaveNo;

    explicit EasyPropertyMaskingForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyMaskingForm();
    
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	GenerateAutomatically(void);
	void	DeleteAutomaticItems(void);
	void	DeleteOriginCAD(void);
	virtual	void	StartInitial(void)	override;
signals:
	void	SignalBusy();
	void	SignalIdle();
private slots:
    void on_toolButtonEffective_clicked();
    void on_toolButtonAutoPickup_clicked();
    void SlotTableRightClicked(QTableWidgetItem *item);
	void	ResizeAction();
	void	SlotTimeOut();
    void on_horizontalSlider_valueChanged(int value);
    void on_toolButtonMakeEffectiveFromCAD_clicked();
    void on_spinBoxShrinkDotForCAD_valueChanged(int arg1);
    void on_doubleSpinBoxShrinkDotForCADMM_valueChanged(double arg1);
	void	SlotDrawEndAfterOperation(FlexArea &ResultArea);
    void on_toolButtonMakeOutlineArea_clicked();
    void on_toolButtonMakePatternEdge_clicked();
    void on_tableWidgetLimited_clicked(const QModelIndex &index);
	void SlotUpdateItemList();
    void on_toolButtonShowOnlyLibID_clicked();

private:
    Ui::EasyPropertyMaskingForm *ui;

	void	ShowLimitTable(void);
	virtual void	StartPage	(void)	override;
};

class	IntegrationCmdAutoPickup : public IntegrationCmdPacketBase
{
public:
	int32	MaskAutoPickupRL;
	int32	MaskAutoPickupRH;
	int32	MaskAutoPickupGL;
	int32	MaskAutoPickupGH;
	int32	MaskAutoPickupBL;
	int32	MaskAutoPickupBH;
	int32	MaskAutoLayer;
	int32	MaskAutoMinPickupSize;
	int32	MaskAutoMaxPickupSize;
	int32	MaskAutoMinPickupDots;
	int32	MaskAutoMaxPickupDots;
	int32	MaskAutoErosion;
	int32	LocalX,LocalY;
	int32	MaskAutoExcludeLeftX ;
	int32	MaskAutoExcludeRightX;
	int32	MaskNoisePinhole ;
	int32	MaskNoiseSmallDot;

	int32	Mask2AutoPickupRL;
	int32	Mask2AutoPickupRH;
	int32	Mask2AutoPickupGL;
	int32	Mask2AutoPickupGH;
	int32	Mask2AutoPickupBL;
	int32	Mask2AutoPickupBH;
	int32	Mask2AutoMinPickupSize;
	int32	Mask2AutoMaxPickupSize;
	int32	Mask2AutoMinPickupDots;
	int32	Mask2AutoMaxPickupDots;
	int32	Mask2AutoErosion;
	int32	Mask2AutoOutsideXPos;
	int32	Mask2AutoOutsideYPos;
	int32	Mask2NoisePinhole ;
	int32	Mask2NoiseSmallDot;

	int32	Mask3AutoPickupRL;
	int32	Mask3AutoPickupRH;
	int32	Mask3AutoPickupGL;
	int32	Mask3AutoPickupGH;
	int32	Mask3AutoPickupBL;
	int32	Mask3AutoPickupBH;
	int32	Mask3AutoMinPickupSize;
	int32	Mask3AutoMaxPickupSize;
	int32	Mask3AutoMinPickupDots;
	int32	Mask3AutoMaxPickupDots;
	int32	Mask3AutoErosion;
	int32	Mask3AutoOutsideXPos;
	int32	Mask3AutoOutsideYPos;
	int32	Mask3NoisePinhole ;
	int32	Mask3NoiseSmallDot;

	int32	Mask4AutoPickupRL;
	int32	Mask4AutoPickupRH;
	int32	Mask4AutoPickupGL;
	int32	Mask4AutoPickupGH;
	int32	Mask4AutoPickupBL;
	int32	Mask4AutoPickupBH;
	int32	Mask4AutoMinPickupSize;
	int32	Mask4AutoMaxPickupSize;
	int32	Mask4AutoMinPickupDots;
	int32	Mask4AutoMaxPickupDots;
	int32	Mask4AutoErosion;
	int32	Mask4AutoOutsideXPos;
	int32	Mask4AutoOutsideYPos;
	int32	Mask4NoisePinhole ;
	int32	Mask4NoiseSmallDot;

	AlgorithmLibraryListContainer	LimitedLib;
	int32	BladeHoleMinArea	;
	int32	BladeHoleErosionDot	;
	int		OmitX1,OmitY1,OmitX2,OmitY2;
	int		BladeAreaX1,BladeAreaY1,BladeAreaX2,BladeAreaY2;

	IntegrationCmdAutoPickup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdReqLibrary : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckLibrary : public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryListContainer	LibContainer;

	IntegrationCmdAckLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};
class	IntegrationDeleteAllMask : public IntegrationCmdPacketBase
{
public:
	bool	DeleteManualItems	;
	bool	DeleteCADItems		;

	IntegrationDeleteAllMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	IntegrationDeleteOnlyCADMask : public IntegrationCmdPacketBase
{
public:

	IntegrationDeleteOnlyCADMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdReqMaskCount: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckMaskCount: public IntegrationCmdPacketBase
{
public:
	UsedLimitedMaskContainer	MaskContainer;

	IntegrationCmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationMakeEffectiveFromCAD: public IntegrationCmdPacketBase
{
public:
	int	ShrinkDot;
	IntegrationMakeEffectiveFromCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationGenerateOutlineArea: public IntegrationCmdPacketBase
{
public:
    int     Expansion ;
    int     InsideDot ;
    int     OutsideDot;
	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationGenerateOutlineArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCreatePatternEdge: public IntegrationCmdPacketBase
{
public:
    int     BoundaryDiff ;
    int     WidthDot ;

	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationCreatePatternEdge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	IntegrationSetItemSelection: public IntegrationCmdPacketBase
{
public:
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	IntegrationSetItemSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // EASYPROPERTYMASKINGFORM_H
