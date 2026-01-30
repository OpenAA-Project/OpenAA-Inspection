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

#ifndef DISPLACEMENTMETERFORM_H
#define DISPLACEMENTMETERFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class DisplacementMeterForm;
}
class	QextSerialPort;

class SignalOperandInt;

class DisplacementMeterForm : public GUIFormBase
{
    Q_OBJECT
    
	QextSerialPort		*sio;
	int					SysMeasuredNo;
	SignalOperandInt	*oMeasured;
public:
	int				CommPort;

	explicit DisplacementMeterForm(LayersBase *base ,QWidget *parent = 0);
    ~DisplacementMeterForm();
    
	virtual	void	Prepare(void)	override;

	bool	OpenPort(int port);
	bool	ClosePort(void);
private slots:
    void on_pushButtonZero_clicked();
    void on_pushButtonMeasure_clicked();

private:
    Ui::DisplacementMeterForm *ui;
private:
	int		GetChar(void);
	void	SendChar(unsigned char d);

	bool	SendStr(char *s);
	bool	GetStr(char buff[] ,int maxlen);
};

#endif // DISPLACEMENTMETERFORM_H