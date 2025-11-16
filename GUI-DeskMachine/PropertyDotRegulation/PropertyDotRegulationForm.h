#ifndef PROPERTYDOTREGULATIONFORM_H
#define PROPERTYDOTREGULATIONFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyDotRegulationForm.h"

class	LayersBase;

class PropertyDotRegulationForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyDotRegulationForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyDotRegulationForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	
private slots:
    void on_pushButtonPickup_clicked();
    void on_pushButtonXPosList_clicked();
    void on_pushButtonYPosList_clicked();
    void on_pushButtonBrightness_clicked();

private:
	Ui::PropertyDotRegulationFormClass ui;
};

#endif // PROPERTYDOTREGULATIONFORM_H
