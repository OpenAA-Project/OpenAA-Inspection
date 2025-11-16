#ifndef DISPLAYOLDIMAGEPANEL_H
#define DISPLAYOLDIMAGEPANEL_H

#include "displayoldimagepanel_global.h"
#include "XDisplayImage.h"
#include "XDisplayOldImagePanel.h"
#include "XTypeDef.h"

class	NamingNGContainer;
class	NamingNG;

class	DisplayOldImagePanel : public DisplayImage
{
	Q_OBJECT

	NamingInfoContainer	*NamingData;
	NamingNGContainer	*NGNaming;
public:

	DisplayOldImagePanel(LayersBase *Base ,QWidget *parent);
	~DisplayOldImagePanel(void);

	virtual void	Prepare(void)	override;

	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;

	virtual	void	BuildForShow(void)						override;
	virtual	void	ShowInPlayer(int64 shownInspectionID)	override;

	int32		GenerationLevel;	//0:Current 1Å`:n older

private:
	NamingNG	*FindNG(NamingInfo *a);

};

#endif // DISPLAYOLDIMAGEPANEL_H
