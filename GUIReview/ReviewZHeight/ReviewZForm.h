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

#ifndef REVIEWZFORM_H
#define REVIEWZFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ReviewZForm;
}
class SignalOperandInt;
class SignalOperandBit;

class ReviewZForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandInt	*oValueZ;
	SignalOperandBit	*oSetZ;	
	GUIFormBase			*VRSOpe;

	int32		ZScrewPitch;	//	Micron
	int32		ZPulsePerRotation;
	int32		ZOffsetPulse;
	int32		ZMultiply;
public:
    explicit ReviewZForm(LayersBase *base ,QWidget *parent = 0);
    ~ReviewZForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	int32		SysValueZ;
	int32		SysSetZ;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButton10Up_clicked();
    void on_pushButton10Dn_clicked();
    void on_pushButton100Up_clicked();
    void on_pushButton100Dn_clicked();

    void on_spinBox_valueChanged(int arg1);
	void	OperandChanged();
private:
    Ui::ReviewZForm *ui;
};

#endif // REVIEWZFORM_H