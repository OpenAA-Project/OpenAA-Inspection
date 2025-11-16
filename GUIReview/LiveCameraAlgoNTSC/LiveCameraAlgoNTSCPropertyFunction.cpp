#include "LiveCameraAlgoNTSCResource.h"
#include "ui_LiveCameraAlgoNTSCPropertyForm.h"
#include "LiveCameraAlgoNTSC.h"
#include "LiveCameraAlgoNTSCProperty.h"

void LiveCameraAlgoNTSC::setProperty(const LiveCameraAlgoNTSCProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void LiveCameraAlgoNTSC::setPropertyToUi(const LiveCameraAlgoNTSCProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::LiveCameraAlgoNTSCPropertyClass *ui = getPropertyUi();
}

void LiveCameraAlgoNTSC::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void LiveCameraAlgoNTSC::setPropertyFromUi(LiveCameraAlgoNTSCProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::LiveCameraAlgoNTSCPropertyClass *ui = getPropertyUi();
}

void LiveCameraAlgoNTSC::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void LiveCameraAlgoNTSC::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void LiveCameraAlgoNTSC::initProperty()
{
	setProperty(new LiveCameraAlgoNTSCProperty);
	setPropertyUi(new Ui::LiveCameraAlgoNTSCPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}
