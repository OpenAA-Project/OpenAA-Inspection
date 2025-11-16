#ifndef CHILDPANELFORM_H
#define CHILDPANELFORM_H

#include <QWidget>
#include <QTimer>
#include "mtFrameDraw.h"
#include "LiveMightexForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class ChildPanelForm;
}
class	ChildPanelForm;
class	LiveMightexForm;

class	ChildCamPanel : public mtFrameDraw
{
    Q_OBJECT

	ChildPanelForm		*LiveParent;
public:
	ChildCamPanel(QWidget *parent);

	virtual	void	SlotOnPaint(QPainter &pnt);
	virtual	void mousePressEvent ( QMouseEvent * e )	override;

signals:
	void	LSignalOnPaint(QPainter &pnt);
};

class ChildPanelForm : public QWidget , public ServiceForLayers
{
    Q_OBJECT
	ChildCamPanel	ViewerPanel;
	QImage	Pict;
public:
    LiveMightexForm	*ParentForm;

    explicit ChildPanelForm(LayersBase *base ,LiveMightexForm *p,QWidget *parent = 0);
    ~ChildPanelForm();

private slots:
    void on_pushButtonSetting_clicked();
    void on_toolButtonLive_clicked();
	void	SlotDraw();
public slots:
	void	SlotOnPaint(QPainter &pnt);
private:
    Ui::ChildPanelForm *ui;
    
    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // CHILDPANELFORM_H
