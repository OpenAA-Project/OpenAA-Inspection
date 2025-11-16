#include "NGImageListForReviewResource.h"
#include "ui_NGImageListForReviewPropertyForm.h"
#include "NGImageListForReview.h"
#include "NGImageListForReviewProperty.h"

void NGImageListForReview::setProperty(const NGImageListForReviewProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void NGImageListForReview::setPropertyToUi(const NGImageListForReviewProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::NGImageListForReviewPropertyClass *ui = getPropertyUi();

	ui->gbMoveHistoryOnLeftRightKey			->setChecked(property.isMoveHistoryOnLeftRightKey);
	ui->gbMoveHistoryOnEnterKey				->setChecked(property.isMoveHistoryOnEnterKey);
	ui->cbAllCheckOnMoveHistoryByLeftRightKey->setChecked(property.isAllCheckOnMoveHistoryByLeftRightKey);
	ui->cbAllCheckOnMoveHistoryByEnterKey	->setChecked(property.isAllCheckOnMoveHistoryByEnterKey);
	ui->cbIgnoreResultError					->setChecked(property.isIgnoreResultError);
	ui->cbAlwaysOperationPreviousEnable		->setChecked(property.isAlwaysPreviousOperationEnable);
}

void NGImageListForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void NGImageListForReview::setPropertyFromUi(NGImageListForReviewProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::NGImageListForReviewPropertyClass *ui = getPropertyUi();

	property.isMoveHistoryOnLeftRightKey			= ui->gbMoveHistoryOnLeftRightKey->isChecked();
	property.isMoveHistoryOnEnterKey				= ui->gbMoveHistoryOnEnterKey->isChecked();
	property.isAllCheckOnMoveHistoryByLeftRightKey	= ui->cbAllCheckOnMoveHistoryByLeftRightKey->isChecked();
	property.isAllCheckOnMoveHistoryByEnterKey		= ui->cbAllCheckOnMoveHistoryByEnterKey->isChecked();
	property.isIgnoreResultError					= ui->cbIgnoreResultError->isChecked();
	property.isAlwaysPreviousOperationEnable		= ui->cbAlwaysOperationPreviousEnable->isChecked();
}

void NGImageListForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void NGImageListForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void NGImageListForReview::initProperty()
{
	setProperty(new NGImageListForReviewProperty);
	setPropertyUi(new Ui::NGImageListForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}
