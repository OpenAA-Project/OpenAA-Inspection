#ifndef SHOWMINMAXBUTTON_H
#define SHOWMINMAXBUTTON_H

#include "showminmaxbutton_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"

class	ShowMinMaxButton : public GUIFormBase
{
public:
	bool	ShowButtons;
	bool	CloseButton;
	QString	StartupSize;
	int32	MaxXMainWindow;
	int32	MaxYMainWindow;
	int32	MinXMainWindow;
	int32	MinYMainWindow;

	ShowMinMaxButton(LayersBase *Base ,QWidget *parent);

	virtual	void	ReadyParam(void) override;
private:

};

#endif // SHOWMINMAXBUTTON_H
