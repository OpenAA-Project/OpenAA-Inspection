/*
 * Copyright (C) 2024
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

#ifndef PQSYSTEMSETTINGFORM_H
#define PQSYSTEMSETTINGFORM_H

#include <QWidget>
#include <QTabWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class PQSystemSettingForm;
}

class PQSystemSettingForm : public PQSystemRunner
{
    Q_OBJECT
    WEditParameterTab		*WTabGeneral;
public:
    explicit PQSystemSettingForm(LayersBase *base ,const QString &root ,const QString &name
                                ,QWidget *parent = 0);
    ~PQSystemSettingForm();
    
    virtual	bool	Initial(void)   override;
    virtual	const QString	GetPath(void)		override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemSetting";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemSetting.dat";  }

private slots:
    void on_ButtonOK_clicked();

private:
    Ui::PQSystemSettingForm *ui;
};

#endif // PQSYSTEMSETTINGFORM_H