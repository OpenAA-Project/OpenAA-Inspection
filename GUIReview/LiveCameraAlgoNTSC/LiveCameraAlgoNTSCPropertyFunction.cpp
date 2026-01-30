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

#include "LiveCameraAlgoNTSCResource.h"
#include "ui_LiveCameraAlgoNTSCPropertyForm.h"
#include "LiveCameraAlgoNTSC.h"
#include "LiveCameraAlgoNTSCProperty.h"

void LiveCameraAlgoNTSC::setProperty(const LiveCameraAlgoNTSCProperty &property)
{
	// �����Ƀp�����[�^�ύX�̑Ή����L�q����
	(*m_property) = property;
}

void LiveCameraAlgoNTSC::setPropertyToUi(const LiveCameraAlgoNTSCProperty &property)
{
	// �����Ƀp�����[�^�̓��e��Ui�ɔ��f�������L�q������
	Ui::LiveCameraAlgoNTSCPropertyClass *ui = getPropertyUi();
}

void LiveCameraAlgoNTSC::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void LiveCameraAlgoNTSC::setPropertyFromUi(LiveCameraAlgoNTSCProperty &property)
{
	// ������Ui�̓��e���p�����[�^�ɔ��f�������L�q���s����
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