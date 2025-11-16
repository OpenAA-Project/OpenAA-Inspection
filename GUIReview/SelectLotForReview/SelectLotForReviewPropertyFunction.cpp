#include "SelectLotForReviewResource.h"
#include "ui_SelectLotForReviewPropertyForm.h"
#include "SelectLotForReview.h"
#include "SelectLotForReviewProperty.h"

void SelectLotForReview::setProperty(const SelectLotForReviewProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void SelectLotForReview::setPropertyToUi(const SelectLotForReviewProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::SelectLotForReviewPropertyClass *ui = getPropertyUi();
	ui->gbAutoShowResultLotLoadForm->setChecked(property.autoShowResultLoadLotForm);
	ui->cbShowOnlyError->setChecked(property.showOnlyHasError);
}

void SelectLotForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void SelectLotForReview::setPropertyFromUi(SelectLotForReviewProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::SelectLotForReviewPropertyClass *ui = getPropertyUi();
	property.autoShowResultLoadLotForm = ui->gbAutoShowResultLotLoadForm->isChecked();
	property.showOnlyHasError = ui->cbShowOnlyError->isChecked();
}

void SelectLotForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void SelectLotForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void SelectLotForReview::slot_propertyRejected()
{
	setPropertyToUi();
}

void SelectLotForReview::initProperty()
{
	setProperty(new SelectLotForReviewProperty);
	setPropertyUi(new Ui::SelectLotForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyDialog(), SIGNAL(rejected()), this, SLOT(slot_propertyRejected()));
}
