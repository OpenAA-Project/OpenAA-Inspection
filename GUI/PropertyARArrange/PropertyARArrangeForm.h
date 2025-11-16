#ifndef PROPERTYARARRANGEFORM_H
#define PROPERTYARARRANGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "ui_PropertyARArrangeForm.h"
#include "XPropertyARArrangePacket.h"

class PropertyARArrangeForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyARArrangeForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyARArrangeForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private:
	Ui::PropertyARArrangeFormClass ui;

	LearningImagePointerList	*CurrentLearning;
	LearningImagePointerContainer	LContainer;
	ARItemListContainer				CurrentARItemContainer;

	void	ShowLearningList(void);
	void	ShowArrangeList(void);
	void	ShowLearningImage(LearningImagePointerList	*p);

private slots:
	void on_tableWidgetRegistration_doubleClicked(QModelIndex);
	void on_tableWidgetArrange_doubleClicked(QModelIndex);
	void on_pushButtonUpdate_clicked();
	void on_tableWidgetArrange_clicked(const QModelIndex &);
	void on_tableWidgetRegistration_clicked(const QModelIndex &);
};

#endif // PROPERTYARARRANGEFORM_H
