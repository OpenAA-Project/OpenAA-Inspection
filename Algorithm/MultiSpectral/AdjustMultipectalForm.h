#ifndef ADJUSTMULTIPECTALFORM_H
#define ADJUSTMULTIPECTALFORM_H

#include <QWidget>
#include <QToolButton>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XGUIComponent.h"

namespace Ui {
class AdjustMultipectalForm;
}

class AdjustMultipectalForm;

class	DisplayAdjustPanel : public QWidget,public ServiceForLayers
{
    AdjustMultipectalForm *Parent;
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
	DisplayAdjustPanel(LayersBase *base ,AdjustMultipectalForm *p, QWidget *parent = 0);
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

class	DisplayComparedPanel : public QWidget,public ServiceForLayers
{
    AdjustMultipectalForm   *Parent;
    DisplayComparedPanel    *Linked;
    int     OldGWidth	;
    int     OldGHeight ;
public:
	int		ItemID;
	bool	ModeShowBlock;

	int		GlobalPage;
    int     PhaseCode;

	QString	AlgoRoot;
	QString	AlgoName;
	QString	GUIRoot;
	QString	GUIName;

	ResultInItemRoot	*Result;

	int		MovX,MovY;
	double	ZoomRate;
    int     GWidth	;
    int     GHeight ;
    bool    Mastered;
    int     CurrentLayer;
    QImage	*ImageByLayer;

public:
	DisplayComparedPanel(LayersBase *base 
                        ,AdjustMultipectalForm *p
                        ,DisplayComparedPanel *LinkedPanel
                        ,QWidget *parent = 0);
	virtual	~DisplayComparedPanel(void);

    void	SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName);
    void	SetResult(ResultInItemRoot *res);
protected:
    virtual	void 	paintEvent ( QPaintEvent * event )		override;
protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )		override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )	override;
	virtual void	wheelEvent ( QWheelEvent * event )		override;
private:
    void    SetZoomPos(int MovX,int MovY,double ZoomRate);
};

//-----------------------------------------------------------------------

class AdjustMultipectalForm : public AlgorithmComponentWindow
							,public ServiceForLayers 
							,public PasswordInQWodget
{
    Q_OBJECT

    DisplayAdjustPanel      DPanel;
    DisplayComparedPanel    MasterPanel;
    DisplayComparedPanel    TargetPanel;
public:
    explicit AdjustMultipectalForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustMultipectalForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
    bool    GetSimShowNGMark(void);
    int     GetCurrentLayer(void);
private slots:
    void on_ButtonRelrectOnlyDotColorMatching_clicked();
    void on_ButtonReflectAllDotColorMatchings_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_horizontalSliderLayer_valueChanged(int value);
    void on_spinBoxCurrentLayer_valueChanged(int arg1);
    void    SlotStartCalc();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxThresholdLength_valueChanged(double arg1);
    void on_spinBoxOKDot_valueChanged(int arg1);

private:
    Ui::AdjustMultipectalForm *ui;

    AlgorithmLibraryListContainer	LibIDList;
    AlgorithmItemIndependentPack	*IData;
    AlgorithmBase *InstBase;
    bool	OnChanging;

	void	GetDataFromWindow(void);
	void	ShowLibrary(void);

	int		OldLibID;
	int		NewLibID;
};

//=====================================================================
class	GUICmdReqPanelImage: public GUICmdPacketBase
{
public:
    struct PanelStruct
    {
        int     Phase;
    	int     Mx1,My1;
        int     GWidth,GHeight;
        double  ZoomRate;
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

//=====================================================================
class	GUICmdReqComparedPanelImage: public GUICmdPacketBase
{
public:
    struct PanelStruct
    {
        int     Phase;
    	int     Mx1,My1;
        int     GWidth,GHeight;
        double  ZoomRate;
        int     CurrentLayer;
        bool    Mastered;
    }PanelStructData;

	GUICmdReqComparedPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckComparedPanelImage: public GUICmdPacketBase
{
public:
    QImage	*ImageByLayer;

	GUICmdAckComparedPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
    ~GUICmdAckComparedPanelImage(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // ADJUSTMULTIPECTALFORM_H
