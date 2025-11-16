#ifndef INTEGRATIONSHOWSAVEDIMAGE_H
#define INTEGRATIONSHOWSAVEDIMAGE_H

#include "integrationshowsavedimage_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"

class	EachMaster;
class	InspectionList;
class	NGPoint;

class	IntegrationShowSavedImage : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QImage	*Img;
	InspectionList	*CurrentInspection;
	NGPoint			*CurrentNG;
public:
	int32	ShownMachineCode;	//-1:Nothing
	int32	ShownPhase;
	bool	ShowMaster;
	bool	EnableToColorizeFor3Layers;

	double	ZoomRate;

	IntegrationShowSavedImage(LayersBase *Base ,QWidget *parent);
	~IntegrationShowSavedImage(void);

	virtual void	Prepare(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	virtual	void paintEvent ( QPaintEvent * event )				override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void PaintInPhase(QPainter &Pnt ,int phase ,EachMaster *m);
	virtual void	StartLot	(void)	override;
private slots:
	void	ResizeAction();
};

#endif // INTEGRATIONSHOWSAVEDIMAGE_H
