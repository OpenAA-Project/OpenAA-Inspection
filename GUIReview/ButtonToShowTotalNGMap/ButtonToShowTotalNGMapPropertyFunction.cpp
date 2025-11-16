#include "ButtonToShowTotalNGMapResource.h"
#include "ui_ButtonToShowTotalNGMapPropertyForm.h"
#include "ButtonToShowTotalNGMap.h"
#include "ButtonToShowTotalNGMapProperty.h"
#include <QColorDialog>

void ButtonToShowTotalNGMap::setProperty(const ButtonToShowTotalNGMapProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void ButtonToShowTotalNGMap::setPropertyToUi(const ButtonToShowTotalNGMapProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::ButtonToShowTotalNGMapPropertyClass *ui = getPropertyUi();

	ui->sbSplitCountX->setValue(property.SplitCountX);
	ui->sbSplitCountY->setValue(property.SplitCountY);
	QPalette pale = ui->tbNGColor->palette();
	pale.setColor(QPalette::ColorRole::Button, property.NGDrawColor);
	ui->lbNGColorSample->setText(property.NGDrawColor.name());
	ui->lbNGColorSample->setBackgroundRole(QPalette::Button);
	ui->lbNGColorSample->setAutoFillBackground(true);
	ui->tbNGColor->setPalette(pale);
	ui->sbNGDrawSize->setValue(property.NGDrawSize);
	ui->cbDrawShape->setCurrentIndex(property.NGDrawShape);
	ui->cbIgnoreResultError->setChecked(property.IgnoreErrorBoard);
}

void ButtonToShowTotalNGMap::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ButtonToShowTotalNGMap::setPropertyFromUi(ButtonToShowTotalNGMapProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::ButtonToShowTotalNGMapPropertyClass *ui = getPropertyUi();

	property.SplitCountX = ui->sbSplitCountX->value();
	property.SplitCountY = ui->sbSplitCountY->value();
	property.NGDrawColor = ui->tbNGColor->palette().color(QPalette::ColorRole::Button);
	property.NGDrawSize = ui->sbNGDrawSize->value();
	int index = ui->cbDrawShape->currentIndex();
	if(index!=-1){
		property.NGDrawShape = (TotalNGMap::NGDrawShapeType)index;
	}else{
		property.NGDrawShape = TotalNGMap::NGDrawShapeType::Fill_Rectangle;
	}
	property.IgnoreErrorBoard = ui->cbIgnoreResultError->isChecked();
}

void ButtonToShowTotalNGMap::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ButtonToShowTotalNGMap::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ButtonToShowTotalNGMap::slot_propertyRejected()
{
	setPropertyToUi();
}

void ButtonToShowTotalNGMap::slot_tbNGColor_clicked()
{
	QColor color = QColorDialog::getColor(getProperty().NGDrawColor, this, LangSolver.GetString(ButtonToShowTotalNGMapPropertyFunction_LS,LID_0)/*"Select NG Color"*/);
	if(color.isValid()==true){
		QPalette pale = getPropertyUi()->tbNGColor->palette();
		pale.setColor(QPalette::ColorRole::Button, color);
		getPropertyUi()->tbNGColor->setBackgroundRole(QPalette::Button);
		getPropertyUi()->tbNGColor->setPalette(pale);
		getPropertyUi()->lbNGColorSample->setText(pale.color(QPalette::Button).name());
	}
}

void ButtonToShowTotalNGMap::initProperty()
{
	setProperty(new ButtonToShowTotalNGMapProperty);
	setPropertyUi(new Ui::ButtonToShowTotalNGMapPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyDialog(), SIGNAL(rejected()), this, SLOT(slot_propertyRejected()));
	connect(getPropertyUi()->tbNGColor, SIGNAL(clicked()), this, SLOT(slot_tbNGColor_clicked()));
}


 
void ButtonToShowTotalNGMap::clicked()
{
	m_map.setSplitX(getProperty().SplitCountX);
	m_map.setSplitY(getProperty().SplitCountY);
	m_map.setNGDrawColor(getProperty().NGDrawColor);
	m_map.setNGDrawSize(getProperty().NGDrawSize);
	m_map.setNGDrawShape((TotalNGMap::NGDrawShapeType)getProperty().NGDrawShape);
	m_map.setIgnoreErrorInspect(getProperty().IgnoreErrorBoard);

	m_map.setModal(false);
	
	m_map.exec();
}