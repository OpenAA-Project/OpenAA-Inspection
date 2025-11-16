#ifndef AUTOFOCUSWITHCAMERAFORM_H
#define AUTOFOCUSWITHCAMERAFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class AutofocusWithCameraForm;
}

class	SignalOperandBit;
class	SignalOperandInt;

class AutofocusWithCameraForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandBit	*iSetZ;
	SignalOperandInt	*iZPosition;

	int			WaitMilisecForAutoFocus;
public:
	int32		MinZValue;
	int32		MaxZValue;
	int32		SetZSysPort;
	int32		ZPositionSysPort;
	int32		FocusAreaX1;
	int32		FocusAreaY1;
	int32		FocusAreaX2;
	int32		FocusAreaY2;
	QString		CameraDLLRoot;
	QString		CameraDLLName;
	QString		CameraDLLInst;

    explicit AutofocusWithCameraForm(LayersBase *base ,QWidget *parent = 0);
    ~AutofocusWithCameraForm();

	virtual void	Prepare(void)	override;

	bool	MoveZ(int ZPos);
	double	CalcImage(QImage &Image);
	bool	MoveCalc(GUIFormBase *f ,int W ,double &RetValue);
	void	LoopCalc(GUIFormBase *f ,int PosC ,int Distance ,double ML, double MC ,double MH ,int &LoopCount);
	double	CalcRect(QImage &Image,int x1,int y1,int x2,int y2);

	void	SaveDarkLightData(void);
	void	LoadDarkLightData(void);
	QString	GetFileName(void);

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonSettingArea_clicked();
    void on_pushButtonScanNEAR_clicked();

private:
    Ui::AutofocusWithCameraForm *ui;
};

#endif // AUTOFOCUSWITHCAMERAFORM_H
