#if	!defined(XPanelShowResultImage_h)
#define	XPanelShowResultImage_h

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XParamCustomized.h"
#include "mtGraphicUnit.h"
#include <QTimer>

class ButtonSettingThresholdForm;
class	EachThresholdCommon;

class	PanelShowResultImage : public mtGraphicUnit,public ServiceForLayers
{
    Q_OBJECT
		
	ButtonSettingThresholdForm	*Parent;
	EachThresholdCommon			*ThCommon;
	int GlobalX ,GlobalY;
	QTimer	TM;
public:
	bool	DrawMode;
	int		DrawGx,DrawGy;
	QColor	DrawColor;

	bool	OverlapNG;

	PanelShowResultImage(ButtonSettingThresholdForm *p ,EachThresholdCommon *wnd);

	void	SetGlobalPoint(int GlobalX ,int GlobalY);

	void	SetClickFunc(void);
	void	ReleaseClickFunc(void);
	void	ShowMarkerPosition(void);
protected:
	virtual	bool	event(QEvent *event)	override;
	
private slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseLDoubleClick(int ,int);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
	void	SlotTimeOut();
};

#endif