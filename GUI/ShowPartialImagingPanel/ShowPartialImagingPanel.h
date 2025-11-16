#ifndef SHOWPARTIALIMAGINGPANEL_H
#define SHOWPARTIALIMAGINGPANEL_H

#include "showpartialimagingpanel_global.h"
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPartialImaging.h"

class ShowPartialImagingPanel : public GUIFormBase
{
	Q_OBJECT

	WriteBufferInItem	*PointData;

public:
	ShowPartialImagingPanel(LayersBase *Base ,QWidget *parent);
	~ShowPartialImagingPanel(void);

	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	
	PartialImagingBase	*GetPartialImagingBase(void);
	void	MakeImage(QImage &Img,WriteBufferInItem *Pointer);

private slots:
	void	ResizeAction();
};
#endif // SHOWPARTIALIMAGINGPANEL_H
