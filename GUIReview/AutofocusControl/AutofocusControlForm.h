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

#ifndef AUTOFOCUSCONTROLFORM_H
#define AUTOFOCUSCONTROLFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"
#include "XAutofocusControl.h"

namespace Ui {
class AutofocusControlForm;
}

class AutofocusControlForm : public GUIFormBase
{
    Q_OBJECT
    XYClassContainer	XYPosData;
public:
    explicit AutofocusControlForm(LayersBase *base ,QWidget *parent = 0);
    ~AutofocusControlForm();
    
	virtual void	Prepare(void)				override;
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	int32		CommPort;	//1:Comm1 2:Comm2
	int32		SearchAreaDot;
	int32		ZScrewPitch;	//	Micron
	int32		ZPulsePerRotation;	

	AFControl	AFComm;

	int		CurrentZ;
	int		SurroundZ;
	int32	StabilizedMilisec;
	int32	CountOfPosition;

	int		MicroscopeDx;
	int		MicroscopeDy;

	int		PosXOnCameraMode;
	int		PosYOnCameraMode;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	SetMeasurePoint(void);

private slots:
    void on_pushButtonMeasureNow_clicked();
    void on_pushButton8Points_clicked();
    void on_pushButtonAutofocusNow_clicked();
    void on_pushButtonAuto_clicked();
    void on_toolButtonGoMicroscope_clicked();

private:
    Ui::AutofocusControlForm *ui;

	void	FromWindow(void);
	void	ToWindow(void);
	void	MovePos(int dX ,int dY);
	void	GetCurrentXYPos(int &X ,int &Y);
	void	ShowDepth(void);
};

#endif // AUTOFOCUSCONTROLFORM_H