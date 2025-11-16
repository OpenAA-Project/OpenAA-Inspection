#ifndef LIVEMIGHTEXFORM_H
#define LIVEMIGHTEXFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "mtFrameDraw.h"
#include <QLabel>

namespace Ui {
class LiveMightexForm;
}

class	LiveMightexForm;
class	ChildPanelForm;
class	SignalOperandBit;

class	CamPanel : public mtFrameDraw
{
    Q_OBJECT

	LiveMightexForm		*LiveParent;
public:
	CamPanel(QWidget *parent);

	virtual	void	SlotOnPaint(QPainter &pnt);
protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )	override;

signals:
	void	LSignalOnPaint(QPainter &pnt);
};

class LiveMightexForm : public GUIFormBase
{
    Q_OBJECT
    CamPanel		ViewerPanel;
	QImage	Pict;
	SignalOperandBit	*iLiveMode;
public:
	bool	ReverseX;
	bool	ReverseY;
	bool	ShowSettingButton;
	bool	ShowLiveButton;
	int		PulsePer100Pixels;
	double	MainCameraZoomRate;
	int32	SysRegLiveMode;

    explicit LiveMightexForm(LayersBase *base ,QWidget *parent = 0);
    ~LiveMightexForm();
    
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	Prepare(void)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
	virtual	void	Terminated(void)			override;

	bool	SaveCameraSetting(void);
	bool	LoadCameraSetting(void);

private slots:
    void on_pushButtonSetting_clicked();
    void on_toolButtonLive_clicked();
	void	SlotDraw();
    void on_pushButtonCapture_clicked();

public slots:
	void ResizeAction(void);
	void	SlotOnPaint(QPainter &pnt);
private:
    Ui::LiveMightexForm *ui;
	QLabel *previewLabel;
};

#endif // LIVEMIGHTEXFORM_H
