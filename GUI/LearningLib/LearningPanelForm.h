#ifndef LEARNINGPANELFORM_H
#define LEARNINGPANELFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "mtGraphicUnit.h"
#include "XFlexArea.h"

namespace Ui {
class LearningPanelForm;
}

class AlgorithmItemRoot;
class LearningPanelForm;

class	RImagePanelS	: public mtGraphicUnit,public ServiceForLayers
{
    Q_OBJECT
	LearningPanelForm	*Parent;
public:
	RImagePanelS(LearningPanelForm *p,LayersBase *base);
	~RImagePanelS(void);

	void	Initial(void);
private slots:
	void	SlotOnPaint(QPainter &pnt);
    void	SlotMouseLDown(int ,int);
	void	SlotMouseRDown(int ,int);
    void	SlotMouseWheel(int delta ,int globalX,int globalY);
private:
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
    void	ChangeDxy2Gxy(double Dx,double Dy ,double &Gx ,double &Gy);
};

class LearningPanelForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	QString EmitterRoot ,EmitterName;
	int GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2;
	int GlobalCx ,GlobalCy;

	RImagePanelS	ImagePanel;
	FlexArea		PointArea;		//Global matrix
	bool			OkMode;
    int             LibType;
    int             LibID;
    AlgorithmItemRoot   *Item;
public:
    explicit LearningPanelForm(int GlobalCx ,int GlobalCy
					            , bool _OkMode
                                ,int LibType ,int LibID
					            , const QString &EmitterRoot ,const QString &EmitterName
					            , LayersBase *base 
                                , QWidget *parent = 0);
     explicit LearningPanelForm(int GlobalCx ,int GlobalCy
					            , bool _OkMode
                                ,AlgorithmItemRoot *Item
					            , const QString &EmitterRoot ,const QString &EmitterName
					            , LayersBase *base 
                                , QWidget *parent = 0);
     ~LearningPanelForm();
    
private slots:
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);
    void on_toolButtonRectangleDraw_clicked();
    void on_toolButtonPointDraw_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();

public slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotDrawEnd(void);
private:
    Ui::LearningPanelForm *ui;
};

#endif // LEARNINGPANELFORM_H
