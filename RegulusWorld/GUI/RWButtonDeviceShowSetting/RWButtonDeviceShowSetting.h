#pragma once

#include "rwbuttondeviceshowsetting_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	RWButtonDeviceShowSetting : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int		DeviceID;

	RWButtonDeviceShowSetting(LayersBase *Base ,QWidget *parent);
	~RWButtonDeviceShowSetting(void);
	
	virtual void	Prepare(void)	override;
				  
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
