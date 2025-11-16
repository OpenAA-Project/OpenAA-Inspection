#ifndef INTEGRATIONSHOWNGARROW_H
#define INTEGRATIONSHOWNGARROW_H

#include "integrationshowngarrow_global.h"
#include "XGUIFormBase.h"
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

class IntegrationShowNGArrow : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	GUIFormBase	*SourceNG;
	GUIFormBase	*Destination;
	EachMaster	*Master;
	NGPoint		*CurrentNG;
	IntegNGImage	*CurrentImagePoint;
public:
	QString		SourceNGGUIInstName;
	QString		DestinationGUIInstName;
	QColor		ArrowColor;
	bool		ExtendSize;

	IntegrationShowNGArrow(LayersBase *Base ,QWidget *parent = 0);
	~IntegrationShowNGArrow();

	virtual void	ReadyParam(void)	override;
private:
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	paintEvent ( QPaintEvent * event )	override;

private slots:
	void	ResizeAction();
};

#endif // INTEGRATIONSHOWNGARROW_H
