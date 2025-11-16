#include "ListStatisticNGResource.h"
#include "ui_ListStatisticNGPropertyForm.h"
#include "ListStatisticNG.h"
#include "ListStatisticNGProperty.h"
#include "XReviewCommon.h"

void ListStatisticNG::setProperty(const ListStatisticNGProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
}

void ListStatisticNG::setPropertyToUi(const ListStatisticNGProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::ListStatisticNGPropertyClass *ui = getPropertyUi();
	ui->listFKeyPriority->clear();

	QStringList fkeyStrList = getFKeyDefinedNames(true);

	for(int i=0; i<fkeyStrList.count(); i++){
		fkeyStrList[i] = QString(/**/"[F%1]:").arg(i+1, 2, 10, QChar('0')) + fkeyStrList[i];
	}

	QStringList list = Review::sortByPriority(property.PriorityList, fkeyStrList);
	ui->listFKeyPriority->addItems(list);
}

void ListStatisticNG::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ListStatisticNG::setPropertyFromUi(ListStatisticNGProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::ListStatisticNGPropertyClass *ui = getPropertyUi();

	property.PriorityList.clear();

	QList<int> list;
	QStringList strList = getFKeyDefinedNames(true);
}

void ListStatisticNG::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ListStatisticNG::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ListStatisticNG::initProperty()
{
	setProperty(new ListStatisticNGProperty);
	setPropertyUi(new Ui::ListStatisticNGPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}
