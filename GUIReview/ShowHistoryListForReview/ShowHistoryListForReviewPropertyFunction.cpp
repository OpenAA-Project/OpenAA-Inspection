#include "ShowHistoryListForReviewResource.h"
#include "ui_ShowHistoryListForReviewPropertyForm.h"
#include "ShowHistoryListForReview.h"
#include "ShowHistoryListForReviewProperty.h"

void ShowHistoryListForReview::setProperty(const ShowHistoryListForReviewProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void ShowHistoryListForReview::setPropertyToUi(const ShowHistoryListForReviewProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::ShowHistoryListForReviewPropertyClass *ui = getPropertyUi();
}

void ShowHistoryListForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ShowHistoryListForReview::setPropertyFromUi(ShowHistoryListForReviewProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::ShowHistoryListForReviewPropertyClass *ui = getPropertyUi();
}

void ShowHistoryListForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ShowHistoryListForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ShowHistoryListForReview::initProperty()
{
	setProperty(new ShowHistoryListForReviewProperty);
	setPropertyUi(new Ui::ShowHistoryListForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}
