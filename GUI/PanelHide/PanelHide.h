#ifndef PANELHIDE_H
#define PANELHIDE_H

#include "panelhide_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class PanelHide :public GUIFormBase
{
	Q_OBJECT

public:
	bool	HideMode;

	PanelHide(LayersBase *Base ,QWidget *parent = 0);

	virtual void	ReadyParam(void)							override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};

class	CmdShowPanel : public GUIDirectMessage
{
public:
	bool	ModeShow;
	CmdShowPanel(LayersBase *base):GUIDirectMessage(base){}
};

#endif // PANELHIDE_H
