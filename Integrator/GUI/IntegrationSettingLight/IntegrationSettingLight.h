#pragma once

#include "integrationsettinglight_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	IntegrationSettingLight : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

	bool	Once;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int		LightNumber;

	IntegrationSettingLight(LayersBase *Base ,QWidget *parent);
	~IntegrationSettingLight(void);
	
	virtual void	Prepare(void)	override;
	virtual void	BuildForShow(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
};