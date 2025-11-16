#include "ListMasterDataAndLoadResource.h"
#include "ui_ListMasterDataAndLoadPropertyForm.h"
#include "ListMasterDataAndLoad.h"
#include "ListMasterDataAndLoadProperty.h"
#include "MultiSelectButtonForm.h"
#include "XDatabaseLoader.h"

void ListMasterDataAndLoad::setProperty(const ListMasterDataAndLoadProperty &property)
{
	// ここにパラメータ変更の対応を記述する
	(*m_property) = property;
	
}

void ListMasterDataAndLoad::setPropertyToUi(const ListMasterDataAndLoadProperty &property)
{
	// ここにパラメータの内容をUiに反映させる記述を書く
	Ui::ListMasterDataAndLoadPropertyClass *ui = getPropertyUi();
}

void ListMasterDataAndLoad::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ListMasterDataAndLoad::setPropertyFromUi(ListMasterDataAndLoadProperty &property)
{
	// ここにUiの内容をパラメータに反映させる記述を行書く
	Ui::ListMasterDataAndLoadPropertyClass *ui = getPropertyUi();
}

void ListMasterDataAndLoad::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ListMasterDataAndLoad::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ListMasterDataAndLoad::showMachineIDFilterDialog()
{
	int MachineIDList[100];

	int mCount = GetLayersBase()->GetDatabaseLoader()->G_EnumMachine( GetLayersBase()->GetDatabase(), MachineIDList, 100);

	QList<QPair<int, QString> > selectList;
	QList<bool> checkFlags;
	for(int i=0; i<mCount; i++){
		QString netID, name, version, remark;
		GetLayersBase()->GetDatabaseLoader()->G_GetMachineInfo( GetLayersBase()->GetDatabase(), MachineIDList[i], netID, name, version, remark);
		selectList << QPair<int, QString>(MachineIDList[i], name);
		checkFlags << getProperty().MachineIDFilter.contains(MachineIDList[i]);
	}

	MultiSelectButtonForm<int> form(getPropertyDialog());
	form.setButtonList(selectList, checkFlags);

	if(form.exec()==QDialog::Accepted){
		getProperty().MachineIDFilter = form.result();
		updateTable();
	}
}

void ListMasterDataAndLoad::initProperty()
{
	setProperty(new ListMasterDataAndLoadProperty);
	setPropertyUi(new Ui::ListMasterDataAndLoadPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	m_ListMasterForm.setMachineIDFilter( getProperty().MachineIDFilter );

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyUi()->pbMachineIDFilter, SIGNAL(clicked()), this, SLOT(showMachineIDFilterDialog()));
}

void ListMasterDataAndLoad::updateTable()
{
	m_ListMasterForm.setMachineIDFilter( getProperty().MachineIDFilter );
}