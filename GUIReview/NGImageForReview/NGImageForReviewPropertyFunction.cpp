#include "NGImageForReviewResource.h"
#include "ui_NGImageForReviewPropertyForm.h"
#include "NGImageForReview.h"
#include "NGImageForReviewProperty.h"

void NGImageForReview::setProperty(const NGImageForReviewProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void NGImageForReview::setPropertyToUi(const NGImageForReviewProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::NGImageForReviewPropertyClass *m_ui = getPropertyUi();
	m_ui->cbRotate->setCurrentIndex(static_cast<int>(property.rotate));
	m_ui->checkBoxBlankImageOnCopyMaster	->setChecked(property.BlankImageOnCopyMaster);
}

void NGImageForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void NGImageForReview::setPropertyFromUi(NGImageForReviewProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::NGImageForReviewPropertyClass *m_ui = getPropertyUi();
	property.rotate					= static_cast<Review::Rotate>(m_ui->cbRotate->currentIndex());
	property.BlankImageOnCopyMaster	=m_ui->checkBoxBlankImageOnCopyMaster->isChecked();
}

void NGImageForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void NGImageForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void NGImageForReview::initProperty()
{
	setProperty(new NGImageForReviewProperty);
	setPropertyUi(new Ui::NGImageForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	connect(getPropertyUi()->cbRotate, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_propertyModified()));

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}
