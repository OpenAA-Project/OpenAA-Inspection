#ifndef PROPERTYREALTIMEGRAPHFORM_H
#define PROPERTYREALTIMEGRAPHFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyRealtimeGraphForm.h"

class PropertyRealtimeGraphForm : public GUIFormBase
{
	Q_OBJECT

	int	CamNumb;
public:
	QStringList	RelatedRealtimeGraph;

	PropertyRealtimeGraphForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyRealtimeGraphForm();

	virtual void	AfterStartSequence(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	Ui::PropertyRealtimeGraphFormClass ui;

private slots:
};

#endif // PROPERTYREALTIMEGRAPHFORM_H
