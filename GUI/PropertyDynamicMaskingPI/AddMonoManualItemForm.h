/*
 * Copyright (C) 2023
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

#ifndef ADDMONOMANUALITEMFORM_H
#define ADDMONOMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddMonoManualItemForm.h"
#include "XTypeDef.h"
#include "XDynamicMaskingPI.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include <QToolButton>

class AddMonoManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddMonoManualItemForm(LayersBase *base ,QWidget *parent);
	~AddMonoManualItemForm();

	int32		AbsLR, AbsHR;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	int32		AbsLR2, AbsHR2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	int32		MinSize;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;

	void	SetInitial(void);
	QList<QToolButton *>	LayerPickupButtons;
	IntList		AdaptedPickupLayers;

private:
	Ui::AddMonoManualItemFormClass ui;

private slots:
	void on_pushButtonOKDrawMask_2_clicked();
	void on_pushButtonCancelDrawMask_2_clicked();
	void on_radioButtonDrawMask_2_toggled(bool);
	void on_pushButtonCancelDrawMask_clicked();
	void on_pushButtonOKDrawMask_clicked();
	void on_radioButtonDrawMask_toggled(bool);
	void on_radioButtonPickupMask_toggled(bool);
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
    void on_toolButtonLayer_clicked();
};

#endif // ADDMONOMANUALITEMFORM_H