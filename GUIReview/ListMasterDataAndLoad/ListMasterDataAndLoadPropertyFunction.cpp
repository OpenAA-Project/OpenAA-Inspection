/*
 * Copyright (C) 2017
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ListMasterDataAndLoadResource.h"
#include "ui_ListMasterDataAndLoadPropertyForm.h"
#include "ListMasterDataAndLoad.h"
#include "ListMasterDataAndLoadProperty.h"
#include "MultiSelectButtonForm.h"
#include "XDatabaseLoader.h"

void ListMasterDataAndLoad::setProperty(const ListMasterDataAndLoadProperty &property)
{
	// �����Ƀp�����[�^�ύX�̑Ή����L�q����
	(*m_property) = property;
	
}

void ListMasterDataAndLoad::setPropertyToUi(const ListMasterDataAndLoadProperty &property)
{
	// �����Ƀp�����[�^�̓��e��Ui�ɔ��f�������L�q������
	Ui::ListMasterDataAndLoadPropertyClass *ui = getPropertyUi();
}

void ListMasterDataAndLoad::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ListMasterDataAndLoad::setPropertyFromUi(ListMasterDataAndLoadProperty &property)
{
	// ������Ui�̓��e���p�����[�^�ɔ��f�������L�q���s����
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