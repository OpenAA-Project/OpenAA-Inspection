#ifndef PROPERTYSPOTREDUCERFORM_H
#define PROPERTYSPOTREDUCERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertySpotReducerForm.h"
#include "XGUIPacketForDLL.h"

class	SpotReducerBase;

class PropertySpotReducerForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertySpotReducerForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertySpotReducerForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	SpotReducerBase	*GetSpotReducerBase(void);

private:
	Ui::PropertySpotReducerFormClass ui;
};

#endif // PROPERTYSPOTREDUCERFORM_H
