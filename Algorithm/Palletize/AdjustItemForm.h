#ifndef ADJUSTITEMFORM_H
#define ADJUSTITEMFORM_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include <QSpinBox>
#include <QString>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XGUIPacketForDLL.h"
#include "XPalletize.h"

namespace Ui {
class AdjustItemForm;
}

class AdjustItemForm;

class	DisplayAdjustPanel : public QWidget,public ServiceForLayers
{
    AdjustItemForm *Parent;
    int     OldGWidth	;
    int     OldGHeight ;
public:
	int		ItemID;
	bool	ModeShowBlock;

	int		MovX,MovY;
	double	ZoomRate;
	int		GlobalPage;
    int     PhaseCode;
    int     GWidth	;
    int     GHeight ;

	QString	AlgoRoot;
	QString	AlgoName;
	QString	GUIRoot;
	QString	GUIName;

	ResultInItemRoot	*Result;
	    
    
    QImage	*NGResultImage;

public:
	DisplayAdjustPanel(LayersBase *base ,AdjustItemForm *p, QWidget *parent = 0);
	virtual	~DisplayAdjustPanel(void);

    void	SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName);
    void	SetResult(ResultInItemRoot *res);
protected:
    virtual	void 	paintEvent ( QPaintEvent * event )		override;
protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )		override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )	override;
	virtual void	wheelEvent ( QWheelEvent * event )		override;
};

class AdjustItemForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    DisplayAdjustPanel  DPanel;

public:
    explicit AdjustItemForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustItemForm();

    void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
    void    GetRotZoomIndex(int &RotIndex ,int &ZoomIndex);
    int     GetItemID(void);
private slots:
    void on_listWidgetZoom_itemSelectionChanged();
    void on_listWidgetAngle_itemSelectionChanged();
    void on_ButtonRelrectOnlyPalletize_clicked();
    void on_ButtonReflectAllPalletize_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void	SlotStartCalc();
    void on_pushButtonMasterPosition_clicked();

private:
    Ui::AdjustItemForm *ui;

	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	AlgorithmBase *InstBase;
	bool	OnChanging;

	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
};

//================================================================

class	GUICmdReqPanelImage: public GUICmdPacketBase
{
public:
    struct PanelStruct
    {
        int     Phase;
        int     ItemID;
    	int     MovX,MovY;
        int     GWidth,GHeight;
        double  ZoomRate;
        int		RotIndex ,ZoomIndex;
    }PanelStructData;

	GUICmdReqPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPanelImage: public GUICmdPacketBase
{
public:
	QImage	*TargetImage;

	GUICmdAckPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
    ~GUICmdAckPanelImage(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqItemInfo: public GUICmdPacketBase
{
public:
    int     Phase;
    int     ItemID;

	GUICmdReqItemInfo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemInfo: public GUICmdPacketBase
{
public:
	DoubleList	ZoomSizeList;
	DoubleList	RotationList;

	GUICmdAckItemInfo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdSendMasterPositions: public GUICmdPacketBase
{
public:
    int     Phase;
    int     ItemID;
	MasterPositionListContainer	MasterPositions;

	GUICmdSendMasterPositions(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // ADJUSTITEMFORM_H
