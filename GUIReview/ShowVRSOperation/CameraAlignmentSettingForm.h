/*
 * Copyright (C) 2022
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

#pragma once

#include <QDialog>

#include "ui_CameraAlignmentSettingForm.h"
#include "VRSControlForm.h"

class AlgorithmBase;

class CameraAlignmentSettingForm : public QDialog
{
	Q_OBJECT

public:
	CameraAlignmentSettingForm(AlgorithmBase *Base, int InitMoveDistance, int InitZDistanceStep, bool reverse_x=false, bool reverse_y=false, QWidget *parent=NULL);

public:
	QLabel *cameraLabel();
	InputRectInConstImageLabel *cameraLabelForm();
	QRectF resultNormalizationRect() const;

public:
	void setImageData(const QList<QImage> &imageList, const QList<QPoint> &outlineList, const QRect &alignment, bool firstExpand=false);

protected:
	virtual	void moveEvent(QMoveEvent *)			override;
	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
    void on_pushButtonMove_clicked();

private:
	Ui::CameraAlignmentSettingClass ui;
	VRSControlForm	m_controlForm;
};
