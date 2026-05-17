#ifndef BUTTONTHRESHOLD2_H
#define BUTTONTHRESHOLD2_H

#include "buttonthreshold2_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"

class	ButtonThreshold2 : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;
	QString				PixelLibSettingFileName;

public:
	ButtonThreshold2(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

	int	LanguageCode;
	QString	Password;

	QString	GetPixelLibSettingFileName()	{	return PixelLibSettingFileName;	}

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

#endif // BUTTONTHRESHOLD2_H
