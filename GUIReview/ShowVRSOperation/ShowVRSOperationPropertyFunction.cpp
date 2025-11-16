#include "ShowVRSOperationResource.h"
#include "ui_ShowVRSOperationPropertyForm.h"
#include "ShowVRSOperation.h"
#include "ShowVRSOperationProperty.h"

void ShowVRSOperation::setProperty(const ShowVRSOperationProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void ShowVRSOperation::setPropertyToUi(const ShowVRSOperationProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::ShowVRSOperationPropertyClass *pui = getPropertyUi();

	pui->sbInitialMoveLength->setValue(property.moveLength);
	pui->sbZDistanceStep->setValue(property.ZDistanceStep);
	ui.sbMoveLength->setValue(property.moveLength);
	ui.cbXReverse->setChecked(property.ReverseX);
	ui.cbYReverse->setChecked(property.ReverseY);
}

void ShowVRSOperation::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ShowVRSOperation::setPropertyFromUi(ShowVRSOperationProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::ShowVRSOperationPropertyClass *pui = getPropertyUi();

	property.moveLength = ui.sbMoveLength->value();
	property.ZDistanceStep = pui->sbZDistanceStep->value();
	property.ReverseX = ui.cbXReverse->isChecked();
	property.ReverseY = ui.cbYReverse->isChecked();
}

void ShowVRSOperation::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ShowVRSOperation::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ShowVRSOperation::initProperty()
{
	setProperty(new ShowVRSOperationProperty);
	setPropertyUi(new Ui::ShowVRSOperationPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}

void ShowVRSOperation::updateMoveLength(int value)
{
	ShowVRSOperationProperty pro;
	pro = getProperty();
	pro.moveLength = value;
	setProperty(pro);
	pro.save();
}

void ShowVRSOperation::updateZDistanceStep(int value)
{
	ShowVRSOperationProperty pro;
	pro = getProperty();
	pro.ZDistanceStep = value;
	setProperty(pro);
	pro.save();
}
