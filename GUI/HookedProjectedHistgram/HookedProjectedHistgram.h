#ifndef HOOKEDPROJECTEDHISTGRAM_H
#define HOOKEDPROJECTEDHISTGRAM_H

#include "hookedprojectedhistgram_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	HookedProjectedHistgram : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	int32	SenderPort;
	QString	IPAddress;
	QString	ImagePanelNameToHook;

	HookedProjectedHistgram(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // HOOKEDPROJECTEDHISTGRAM_H
