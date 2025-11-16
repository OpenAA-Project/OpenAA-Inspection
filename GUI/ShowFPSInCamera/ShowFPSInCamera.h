#pragma once

#include "showfpsincamera_global.h"
#include <QLabel>
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ShowFPSInCamera : public GUIFormBase
{
	Q_OBJECT

	QLabel	Button;

	class	CapturedInfoInCam
	{
	public:
		DWORD	TimeDim[100];
		int		Pointer;
		int		StockedCount;

		CapturedInfoInCam(void);
		double	GetFPS(void);
	};
	CapturedInfoInCam	*CamDim;
	int					AllocatedCamCount;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxFPS;
	int32	Precision;
	double	FPS;

	ShowFPSInCamera(LayersBase *Base ,QWidget *parent);
	~ShowFPSInCamera(void);

	virtual void	ReadyParam(void)	override;
	virtual void	Prepare(void)		override;

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	ResizeAction();
	void	SlotCapturedInCamera0();
	void	SlotCapturedInCamera1();
	void	SlotCapturedInCamera2();
	void	SlotCapturedInCamera3();
	void	SlotCapturedInCamera4();
	void	SlotCapturedInCamera5();
	void	SlotCapturedInCamera6();
	void	SlotCapturedInCamera7();
	void	SlotCapturedInCamera8();
	void	SlotCapturedInCamera9();
	void	SlotCapturedInCamera10();
	void	SlotCapturedInCamera11();
	void	SlotCapturedInCamera12();
	void	SlotCapturedInCamera13();
	void	SlotCapturedInCamera14();
	void	SlotCapturedInCamera15();
signals:
	void	SignalCycleTime(double FPS);

private:
	void	CapturedInCameraFromSlot(int CamNo);
};

class	CmdReqFPSInCamera: public GUIDirectMessage
{
public:
	int		CamNo;
	double	FPS;

	CmdReqFPSInCamera(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFPSInCamera(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
