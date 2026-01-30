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

#include "ShowVRSOperationResource.h"
#include "VRSSettingForm.h"
#include "ReviewStructureVRSSetting.h"

VRSSettingForm::VRSSettingForm(QWidget *parent)
	:QDialog(parent),m_VRSSetting(new VRSSetting())
{
	ui.setupUi(this);

	ui.gbInspectOffset->setVisible(false);

	connect(ui.sbCameraWidth,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbCameraHeight,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbInspectOffsetX,		SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbInspectOffsetY,		SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbInspectResolution,		SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorEscapeX,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorEscapeY,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorEscapeZ,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorMovableAreaSizeH, SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorMovableAreaSizeW, SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorOffsetX,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorOffsetY,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorOriginX,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorOriginY,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorZInitDistance,	SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbVRSResolution,			SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorMovableAreaSizeW,	SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
	connect(ui.sbMotorMovableAreaSizeH,	SIGNAL(valueChanged(int)), this, SLOT(checkValidUi()));
}

VRSSettingForm::~VRSSettingForm()
{
	delete m_VRSSetting;
}

VRSSetting VRSSettingForm::getVRSSetting() const
{
	return *m_VRSSetting;
}

void VRSSettingForm::setVRSSetting(const VRSSetting &setting)
{
	*m_VRSSetting = setting;
	
	const VRSSetting::VRSSideSetting &vrss = setting.getVRSSideSetting();
	const VRSSetting::InspectionSideSetting &inss = setting.getInspectionSizeSetting();

	ui.cbRotation->setCurrentIndex(static_cast<int>(vrss.BoardRotation));
	ui.sbCameraHeight->setValue(vrss.CameraViewRealSize.height());
	ui.sbCameraWidth->setValue(vrss.CameraViewRealSize.width());
	ui.sbInspectOffsetX->setValue(inss.Offset.x());
	ui.sbInspectOffsetY->setValue(inss.Offset.y());
	ui.sbInspectResolution->setValue(inss.Resolution);
	ui.sbMotorEscapeX->setValue(vrss.EscapePosition.x());
	ui.sbMotorEscapeY->setValue(vrss.EscapePosition.y());
	ui.sbMotorEscapeZ->setValue(vrss.EscapePosition.z());
	ui.sbMotorMovableAreaSizeH->setValue(vrss.MotorMovableAreaSize.height());
	ui.sbMotorMovableAreaSizeW->setValue(vrss.MotorMovableAreaSize.width());
	ui.sbMotorOffsetX->setValue(vrss.MotorOffset.x());
	ui.sbMotorOffsetY->setValue(vrss.MotorOffset.y());
	ui.sbMotorOriginX->setValue(vrss.MotorOrigin.x());
	ui.sbMotorOriginY->setValue(vrss.MotorOrigin.y());
	ui.sbMotorZInitDistance->setValue(vrss.ZInitialDistance);
	ui.sbVRSResolution->setValue(vrss.Resolution);

	checkValidUi();
}

VRSSetting VRSSettingForm::result() const
{
	return *m_VRSSetting;
}

void VRSSettingForm::checkValidUi()
{
	m_VRSSetting->getVRSSideSetting().BoardRotation = static_cast<Review::Rotate>(ui.cbRotation->currentIndex());
	m_VRSSetting->getVRSSideSetting().CameraViewRealSize = QSize(ui.sbCameraWidth->value(), ui.sbCameraHeight->value());
	m_VRSSetting->getInspectionSizeSetting().Offset = QPoint(ui.sbInspectOffsetX->value(), ui.sbInspectOffsetY->value());
	m_VRSSetting->getInspectionSizeSetting().Resolution = ui.sbInspectResolution->value();
	m_VRSSetting->getVRSSideSetting().EscapePosition = QVector3D(ui.sbMotorEscapeX->value(), ui.sbMotorEscapeY->value(), ui.sbMotorEscapeZ->value());
	m_VRSSetting->getVRSSideSetting().MotorMovableAreaSize = QSize(ui.sbMotorMovableAreaSizeW->value(), ui.sbMotorMovableAreaSizeH->value());
	m_VRSSetting->getVRSSideSetting().MotorOffset = QPoint(ui.sbMotorOffsetX->value(), ui.sbMotorOffsetY->value());
	m_VRSSetting->getVRSSideSetting().MotorOrigin = QPoint(ui.sbMotorOriginX->value(), ui.sbMotorOriginY->value());
	m_VRSSetting->getVRSSideSetting().ZInitialDistance = ui.sbMotorZInitDistance->value();
	m_VRSSetting->getVRSSideSetting().Resolution = ui.sbVRSResolution->value();

	int value;
	bool ok;

	QPalette orgPalette = palette();
	QPalette errPalette = orgPalette;
	errPalette.setColor(QPalette::ColorRole::WindowText, QColor(Qt::red));
	
	value = ui.sbInspectResolution->value();
	if(value==0){
		ui.lbInsResolution->setPalette(errPalette);
	}else{
		ui.lbInsResolution->setPalette(orgPalette);
	}

	value = ui.sbVRSResolution->value();
	if(value==0){
		ui.lbVRSResolution->setPalette(errPalette);
	}else{
		ui.lbVRSResolution->setPalette(orgPalette);
	}

	ui.lbVRSViewSise->setPalette(orgPalette);

	value = ui.sbCameraWidth->value();
	if(value==0){
		ui.lbVRSViewSise->setPalette(errPalette);
		ui.lbVRSViewSizeW->setPalette(errPalette);
	}else{
		ui.lbVRSViewSizeW->setPalette(orgPalette);
	}
	value = ui.sbCameraHeight->value();
	if(value==0){
		ui.lbVRSViewSise->setPalette(errPalette);
		ui.lbVRSViewSizeH->setPalette(errPalette);
	}else{
		ui.lbVRSViewSizeH->setPalette(orgPalette);
	}

	ui.gbMotorMovableAreaSize->setPalette(orgPalette);

	value = ui.sbMotorMovableAreaSizeW->value();
	if(value==0){
		ui.gbMotorMovableAreaSize->setPalette(errPalette);
		ui.lbMotorMovableAreaSizeW->setPalette(errPalette);
	}else{
		ui.lbMotorMovableAreaSizeW->setPalette(orgPalette);
	}
	value = ui.sbMotorMovableAreaSizeH->value();
	if(value==0){
		ui.gbMotorMovableAreaSize->setPalette(errPalette);
		ui.lbMotorMovableAreaSizeH->setPalette(errPalette);
	}else{
		ui.lbMotorMovableAreaSizeH->setPalette(orgPalette);
	}
}