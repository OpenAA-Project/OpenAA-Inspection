#include "WholeImageForReviewResource.h"
#include "ui_WholeImageForReviewPropertyForm.h"
#include "WholeImageForReview.h"
#include "WholeImageForReviewProperty.h"

void WholeImageForReview::setProperty(const WholeImageForReviewProperty &property)
{
	//// ここにパラメータ変更の対応を記述する
	//// 縦横の並び設定
	//setOrientation(property.viewFrontBackOrientation, property.viewPhaseOrientation);

	//// 現在NGNailの中心で十字表示する設定
	//setNGCrossView(property.viewNGNailCross);

	//// NG箇所を表示する設定
	//setNGPointView(property.viewNGPoint);

	//// 現在NGNailのみ表示する設定
	//setOnlyCurrentNGNailRectView(property.viewOnlyCurrentNail);

	(*m_property) = property;

	setPropertyToDisplay();
}

void WholeImageForReview::setPropertyToUi(const WholeImageForReviewProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::WholeImageForReviewPropertyClass *ui = getPropertyUi();
	bool isHoriaontal = (property.viewFrontBackOrientation==Qt::Horizontal);
	ui->rbFrontBackHoriaontal->setChecked(isHoriaontal);
	ui->rbFrontBackVertical->setChecked(!isHoriaontal);

	isHoriaontal = (property.viewPhaseOrientation==Qt::Horizontal);
	ui->rbPhaseHoriaontal->setChecked(isHoriaontal);
	ui->rbPhaseVertical->setChecked(!isHoriaontal);

	ui->cbNGNailCrossView->setChecked(property.viewNGNailCross);
	ui->cbNGPointView->setChecked(property.viewNGPoint);
	ui->cbOnlyCurrentNailView->setChecked(property.viewOnlyCurrentNail);
	ui->cbFrontRotation->setCurrentIndex(static_cast<int>(property.viewFrontRotation));
	ui->cbBackRotation->setCurrentIndex(static_cast<int>(property.viewBackRotation));
}

void WholeImageForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void WholeImageForReview::setPropertyFromUi(WholeImageForReviewProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::WholeImageForReviewPropertyClass *ui = getPropertyUi();
	property.viewFrontBackOrientation = (ui->rbFrontBackHoriaontal->isChecked() ? Qt::Horizontal : Qt::Vertical);
	property.viewPhaseOrientation = (ui->rbPhaseHoriaontal->isChecked() ? Qt::Horizontal : Qt::Vertical);
	property.viewNGNailCross = ui->cbNGNailCrossView->isChecked();
	property.viewNGPoint = ui->cbNGPointView->isChecked();
	property.viewOnlyCurrentNail = ui->cbOnlyCurrentNailView->isChecked();
	property.viewFrontRotation = static_cast<Review::Rotate>(ui->cbFrontRotation->currentIndex());
	property.viewBackRotation = static_cast<Review::Rotate>(ui->cbBackRotation->currentIndex());
}

void WholeImageForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void WholeImageForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
	updateGUI();
}

void WholeImageForReview::initProperty()
{
	setProperty(new WholeImageForReviewProperty);
	setPropertyUi(new Ui::WholeImageForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyUi()->pbApply, SIGNAL(clicked()), this, SLOT(slot_propertyModified()));
}
