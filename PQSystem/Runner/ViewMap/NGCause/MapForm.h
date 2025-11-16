#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include "mtGraphicUnit.h"

namespace Ui {
class MapForm;
}

class NGCauseForm;
const	int		DivX=16;
const	int		DivY=16;


class MapGraphic : public mtGraphicUnit
{
public:
	MapGraphic(QWidget *parent = 0
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);
	~MapGraphic();
};

class MapForm : public QWidget
{
    Q_OBJECT

    NGCauseForm	*Parent;
	MapGraphic	MapPanel;

	int		MapDim[DivX][DivY];
	int		LastMovX;
	int		LastMovY;
	double	LastZoomRate;
	int		LastMaster;
	QImage	MasterImage;
	QImage	MapMask;   
public:
    explicit MapForm(NGCauseForm *p,QWidget *parent = 0);
    ~MapForm();
    
private slots:
    void on_comboBoxMachine_currentIndexChanged(int index);
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseLDown(int ,int);
	void	SlotMouseRDown(int ,int);
	void	SlotMouseWheel(int delta ,int x,int y);
protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
private:
    Ui::MapForm *ui;

	void	MakeMapDim(void);
};

#endif // MAPFORM_H
