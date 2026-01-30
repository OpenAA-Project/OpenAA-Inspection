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

#ifndef KOREAST8CHGUIFORM_H
#define KOREAST8CHGUIFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class KoreaST8ChGUIForm;
}
class	LightDLLBaseClass;

class KoreaST8ChGUIForm : public GUIFormBase
{
    Q_OBJECT

	LightDLLBaseClass	*LightPointer;

public:
	int					Number;
	int					StepValue;
	
	explicit KoreaST8ChGUIForm(LayersBase *base,QWidget *parent = 0);
    ~KoreaST8ChGUIForm();

	virtual void	Prepare(void)		override;
    virtual	void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

protected:
	virtual	bool eventFilter(QObject *target, QEvent *event)	override;
	virtual	void	keyPressEvent(QKeyEvent *event)	override;

private slots:
    void on_dialLightValue_valueChanged(int value);
    void on_spinBoxLightValue_valueChanged(int arg1);
    void on_pushButtonSet_clicked();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
    void on_toolButtonON_clicked();

private:
    Ui::KoreaST8ChGUIForm *ui;

	QString	GetParamFileName(void);
	bool SaveFile(bool OnOff, int value);
	bool LoadFile(bool &OnOff, int &value);
};

#endif // KOREAST8CHGUIFORM_H