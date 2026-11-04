#pragma once

#include "capturehikcamerabutton_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	CameraClass;

class	CaptureHIKCameraButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	CameraClass			**Cam;
	int					CountCamera;
	GUIFormBase			*ListSelectPage;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	MasterImage;


	CaptureHIKCameraButton(LayersBase *Base ,QWidget *parent);
	~CaptureHIKCameraButton(void);
	
	virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)						override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

public slots:
	void	SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};
//--------------------------------------------------------------------------
class	CmdPushButton : public GUIDirectMessage
{
public:
	int		Page;
	CmdPushButton(LayersBase *base):GUIDirectMessage(base){}
	CmdPushButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
