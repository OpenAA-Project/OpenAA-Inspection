#ifndef DISPLAYPOINTINGFORM_H
#define DISPLAYPOINTINGFORM_H

#include "ui_DisplayPointingForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class DisplayPointingForm : public GUIFormBase
{
	Q_OBJECT

public:
	QString	RelatedPanel;

	DisplayPointingForm(LayersBase *Base,QWidget *parent = 0);
	~DisplayPointingForm();

private:
	Ui::DisplayPointingFormClass ui;

	virtual	void	Prepare(void)	override;
	virtual	void	showEvent ( QShowEvent * event ) override;
signals:
	void	SignalDrawFromOutside(QStringList &data);

private slots:
	void	SlotDrawMessage(const QStringList &title ,const QStringList &msg);
	void	ResizeAction();

};

#endif // DISPLAYPOINTINGFORM_H
