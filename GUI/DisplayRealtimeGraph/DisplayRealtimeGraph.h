#ifndef DISPLAYREALTIMEGRAPH_H
#define DISPLAYREALTIMEGRAPH_H

#include "displayrealtimegraph_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class DisplayRealtimeGraphBrightness;
class DisplayRealtimeGraphFocus;
class DisplayImage;

class	DisplayRealtimeGraph :public GUIFormBase
{
    Q_OBJECT

public:
	DisplayRealtimeGraphBrightness	*PanelBrightness;
	DisplayRealtimeGraphFocus		*PanelFocus;

	GUIFormBase		*PropertyRealtimeGraphPointer;
	DisplayImage	*RealtimeImagePanelPointer	;

	DisplayRealtimeGraph(LayersBase *Base ,QWidget *parent);
	~DisplayRealtimeGraph();

	virtual void	AfterStartSequence(void)	override;

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:

private slots:
	void	ResizeAction();
};

#endif // DISPLAYREALTIMEGRAPH_H
