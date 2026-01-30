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
#include "CameraAlignmentSettingForm.h"
#include <QDebug>
#include <QMoveEvent>
#include <QDesktopWidget>

CameraAlignmentSettingForm::CameraAlignmentSettingForm(AlgorithmBase *Base, int InitMoveDistance, int InitZDistanceStep, bool reverse_x, bool reverse_y, QWidget *parent)
	:QDialog(parent),m_controlForm(Base, InitMoveDistance, InitZDistanceStep,reverse_x, reverse_y, this)
{
	ui.setupUi(this);

	ui.widWholeImageAlignment->setMouseDragMode(InputRectInMultiImageWidget::MouseDragMode::ModeShiftImage);
}

QLabel *CameraAlignmentSettingForm::cameraLabel()
{
	return ui.lbCameraAlignment;
}

InputRectInConstImageLabel *CameraAlignmentSettingForm::cameraLabelForm()
{
	return ui.lbCameraAlignment;
}

QRectF CameraAlignmentSettingForm::resultNormalizationRect() const
{
	return ui.lbCameraAlignment->resultNormalizationRect();
}

void CameraAlignmentSettingForm::setImageData(const QList<QImage> &imageList, const QList<QPoint> &outlineList, const QRect &alignment, bool firstExpand)
{
	ui.widWholeImageAlignment->setImageList(imageList, outlineList);
	ui.widWholeImageAlignment->setResultRect(alignment);
	ui.widWholeImageAlignment->setResultZoom(1.0);
	ui.widWholeImageAlignment->setFirstExpand(firstExpand);
}

void CameraAlignmentSettingForm::moveEvent(QMoveEvent *event)
{
	QDialog::moveEvent(event);

	m_controlForm.move(frameGeometry().topRight());
}

void CameraAlignmentSettingForm::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);
	m_controlForm.show();

	QRect newGeometory = frameGeometry();
	
	int topBarHeight = qAbs( geometry().top() - frameGeometry().top() );
	int frameLineWidth = qAbs( geometry().left() - frameGeometry().left() );

	// show window on center
	if(frameGeometry().width() + m_controlForm.frameGeometry().width() > qApp->desktop()->width()){
		newGeometory.moveLeft(frameLineWidth);
	}else{
		newGeometory.moveLeft( (qApp->desktop()->width() - frameGeometry().width() - m_controlForm.frameGeometry().width() ) / 2 );
	}
	if(frameGeometry().height() > qApp->desktop()->height()){
		newGeometory.moveTop(topBarHeight);
	}else{
		newGeometory.moveTop( (qApp->desktop()->height() - frameGeometry().height() ) / 2 );
	}

	newGeometory.setTop( newGeometory.top() + topBarHeight );
	newGeometory.setBottom( newGeometory.bottom() - frameLineWidth );
	newGeometory.setLeft( newGeometory.left() + frameLineWidth );
	newGeometory.setRight( newGeometory.right() - frameLineWidth );

	setGeometry( newGeometory );

	// control
	m_controlForm.move(frameGeometry().topRight());
}
void CameraAlignmentSettingForm::on_pushButtonMove_clicked()
{

}