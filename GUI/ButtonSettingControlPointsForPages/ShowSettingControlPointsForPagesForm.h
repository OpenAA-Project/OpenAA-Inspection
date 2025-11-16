#ifndef SHOWSETTINGCONTROLPOINTSFORPAGESFORM_H
#define SHOWSETTINGCONTROLPOINTSFORPAGESFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XDisplayImage.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"

namespace Ui {
class ShowSettingControlPointsForPagesForm;
}

class ShowSettingControlPointsForPagesForm : public QWidget
                                            ,public ServiceForLayers
                                            ,public FunctionServerClass
{
    Q_OBJECT
    
    DisplayImage    ImagePanel;
    FlexArea        ControlPointArea;
    XYPointContainerWithName	*ControlPointsForPages;
public:
    explicit ShowSettingControlPointsForPagesForm(LayersBase *Base ,DisplayImage::DisplayType dtype,QWidget *parent = 0);
    ~ShowSettingControlPointsForPagesForm();
    

	void	Draw	(QPainter &pnt	,QImage &PntImage
					,double ZoomRate,int movx ,int movy 
					,int CanvasWidth , int CanvasHeight);
private slots:
    void on_comboBoxPage_currentIndexChanged(int index);
    void	SlotMouseLDoubleClick(int globalX,int globalY);
    void on_pushButtonSave_clicked();
    void on_pushButtonClose_clicked();
    void on_listWidgetPoints_itemSelectionChanged();
    void on_pushButtonDelete_clicked();

private:
    Ui::ShowSettingControlPointsForPagesForm *ui;

    void    resizeEvent(QResizeEvent *event)  override;
    void    ShowPointList(void);
};


//==================================================================

class	GUICmdReqControlPoints: public GUICmdPacketBase
{
public:
	GUICmdReqControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)  {   return true;    }
	virtual	bool	Save(QIODevice *f)  {   return true;    }

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckControlPoints: public GUICmdPacketBase
{
public:
    XYPointContainerWithName	ControlPointsForPages;
	GUICmdAckControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetControlPoints: public GUICmdPacketBase
{
public:
    XYPointContainerWithName	ControlPointsForPages;
	GUICmdSetControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWSETTINGCONTROLPOINTSFORPAGESFORM_H
