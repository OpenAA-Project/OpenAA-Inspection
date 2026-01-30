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

#include "XReviewStructure.h"
#include "ui_ReviewStructurePropertyForm.h"

void ReviewPIBase::setProperty(const ReviewStructureProperty &property)
{
	setHistorySortOrder(property.HistoryListSortOrder);
	setNGSortOrder(property.NGNailListSortOrder);
	setPreLoadNGImageLength(property.PreLoadNGImageLength);
	setSaveNGImageFileNameFormat(property.SaveNGImageFileNameFormat);
	setXMLServerState(property.XMLServerIPAddress, property.XMLServerPortNo);

	setPropertyToUi(property);

	m_property = property;
}

void ReviewPIBase::setPropertyToUi(const ReviewStructureProperty &property)
{
	getPropertyUi()->cbHistorySortOrder				->setCurrentIndex(static_cast<int>(property.HistoryListSortOrder));
	getPropertyUi()->cbNGNailSortOrder				->setCurrentIndex(static_cast<int>(property.NGNailListSortOrder));
	getPropertyUi()->sbPreNGImageLoadLength			->setValue(property.PreLoadNGImageLength);
	getPropertyUi()->leSaveNGImageFileFormat		->setText(property.SaveNGImageFileNameFormat);
	getPropertyUi()->leXMLServerIPAddress			->setText(property.XMLServerIPAddress);
	getPropertyUi()->leXMLServerPortNo				->setText(QString::number(property.XMLServerPortNo));
	getPropertyUi()->leNGImagePath					->setText(property.NGImagePath);
	getPropertyUi()->cbMasterImageQuality			->setCurrentIndex(property.SkipMasterImageRate);
	getPropertyUi()->cbVRSOperationEnable			->setChecked(property.VRSOperationEnable);
	getPropertyUi()->leDirectoryToSaveCSV			->setText(property.DirectoryToSaveCSV);
	getPropertyUi()->checkBoxCSVUnitMM				->setChecked(property.CSVUnitMM);
	getPropertyUi()->spinBoxCSVOffsetX				->setValue(property.CSVOffsetX);
	getPropertyUi()->spinBoxCSVOffsetY				->setValue(property.CSVOffsetY);
	getPropertyUi()->checkBoxCSVReverseX			->setChecked(property.CSVReverseX);
	getPropertyUi()->checkBoxCSVReverseY			->setChecked(property.CSVReverseY);
	getPropertyUi()->doubleSpinBoxCSVMagnificationX	->setValue(property.CSVMagnificationX);
	getPropertyUi()->doubleSpinBoxCSVMagnificationY	->setValue(property.CSVMagnificationY);
}

void ReviewPIBase::getPropertyFromUi(ReviewStructureProperty &property)
{
	property.HistoryListSortOrder = static_cast<Review::OrderOfSortHistory>(getPropertyUi()->cbHistorySortOrder->currentIndex());
	property.NGNailListSortOrder = static_cast<Review::OrderOfSortNG>(getPropertyUi()->cbNGNailSortOrder->currentIndex());
	property.PreLoadNGImageLength = getPropertyUi()->sbPreNGImageLoadLength->value();
	
	QString filePath = getPropertyUi()->leSaveNGImageFileFormat->text();

	for(int i=0; i<filePath.count(); i++){
		if(filePath[i].cell()==QChar('\\').cell()){
			filePath[i] = QChar('/');
		}
	}
	//while(true){
	//	QString searchStr = /**/"//";
	//	int index = filePath.indexOf(searchStr);
	//	if(index==-1)break;

	//	filePath.replace(index, searchStr.length(), "/Empty/");
	//}

	property.SaveNGImageFileNameFormat = filePath;
	property.XMLServerIPAddress = getPropertyUi()->leXMLServerIPAddress->text();
	property.XMLServerPortNo = getPropertyUi()->leXMLServerPortNo->text().toInt();
	if(property.XMLServerPortNo<0){
		property.XMLServerPortNo = 12345;
	}
	property.NGImagePath		= getPropertyUi()->leNGImagePath		->text();
	property.SkipMasterImageRate= getPropertyUi()->cbMasterImageQuality	->currentIndex();
	property.VRSOperationEnable = getPropertyUi()->cbVRSOperationEnable	->isChecked();
	property.DirectoryToSaveCSV = getPropertyUi()->leDirectoryToSaveCSV	->text();
	property.CSVUnitMM			= getPropertyUi()->checkBoxCSVUnitMM	->isChecked();
	property.CSVOffsetX			= getPropertyUi()->spinBoxCSVOffsetX	->value();
	property.CSVOffsetY			= getPropertyUi()->spinBoxCSVOffsetY	->value();
	property.CSVReverseX		= getPropertyUi()->checkBoxCSVReverseX	->isChecked();
	property.CSVReverseY		= getPropertyUi()->checkBoxCSVReverseY	->isChecked();
	property.CSVMagnificationX	= getPropertyUi()->doubleSpinBoxCSVMagnificationX	->value();
	property.CSVMagnificationY	= getPropertyUi()->doubleSpinBoxCSVMagnificationY	->value();
}

void ReviewPIBase::updateProperty(void)
{
	setProperty(getProperty());
}

void ReviewPIBase::initProperty(void)
{
	setPropertyUi(new Ui::ReviewStructureClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	updateProperty();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));

	SettingFileReader reader;
	reader.load(VRSSetting::filePath());

	VRSSetting setting = getVRSSetting();

	setting.fromSectionBufferList( reader.sectionList() );

	setVRSSetting(setting);
}

void ReviewPIBase::setVRSSetting(const VRSSetting &setting)
{
	m_VRSSetting = setting;

	SettingFileReader reader;
	reader.setFilename(setting.filePath());

	reader.setSectionList(setting.sectionBufferList());

	reader.save();
}

void ReviewPIBase::saveVRSSetting() const
{
	SettingFileReader reader;
	reader.setFilename(getVRSSetting().filePath());
	reader.setSectionList(getVRSSetting().sectionBufferList());
	reader.save();
	reader.clear();

	const VRSAlignment &falign = getVRSAlignment(Review::Front);
	if(falign.machineID()!=-1){
		reader.setFilename(falign.filename());
		reader.setSectionList(falign.toBufferList());
		reader.save();
		reader.clear();
	}

	const VRSAlignment &balign = getVRSAlignment(Review::Back);
	if(balign.machineID()!=-1){
		reader.setFilename(balign.filename());
		reader.setSectionList(balign.toBufferList());
		reader.save();
		reader.clear();
	}
}