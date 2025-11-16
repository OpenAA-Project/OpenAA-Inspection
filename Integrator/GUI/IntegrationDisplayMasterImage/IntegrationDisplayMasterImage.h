#ifndef INTEGRATIONDISPLAYMASTERIMAGE_H
#define INTEGRATIONDISPLAYMASTERIMAGE_H

#include "integrationdisplaymasterimage_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationLib.h"

class	InspectionList;
class	EachMaster;
class	IntegNGImage;
class	NGPoint;

class	IntegrationDisplayMasterImage: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QImage	**Image;
	int		PhaseNumb;
	InspectionList	*CurrentInspection;
	double	ZoomRate;
	NGPoint			*CurrentNGPoint;
	IntegNGImage	*CurrentImagePoint;
public:
	int	MachineCode;
	int	CurrentPhase;
	bool	ShowNGPoint;

	IntegrationDisplayMasterImage(LayersBase *Base ,QWidget *parent);
	~IntegrationDisplayMasterImage();

private:
	virtual void paintEvent ( QPaintEvent * ) override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	MakeImage(EachMaster *f);
	virtual void	StartLot	(void) override;
private slots:
	void	ResizeAction();
};

#endif // INTEGRATIONDISPLAYMASTERIMAGE_H
