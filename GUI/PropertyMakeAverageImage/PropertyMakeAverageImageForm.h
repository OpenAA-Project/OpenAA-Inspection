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

#ifndef PROPERTYMAKEAVERAGEIMAGEFORM_H
#define PROPERTYMAKEAVERAGEIMAGEFORM_H

#include "XGUIFormBase.h"
#include "XMakeAverageImage.h"

namespace Ui {
class PropertyMakeAverageImageForm;
}

class PropertyMakeAverageImageForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyMakeAverageImageForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMakeAverageImageForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

    void    ResetAverage(void);

private slots:
    void on_toolButtonDrawPartialArea_clicked();
    void on_toolButtonDrawImage_clicked();
    void on_toolButtonDrawDarkImage_clicked();
    void on_toolButtonDrawLightImage_clicked();
    void on_toolButtonDrawAverageImage_clicked();
    void on_pushButtonSetAverageToMaster_clicked();
    void on_toolButtonDrawVariableImage_clicked();
    void on_pushButtonResetAverage_clicked();

    void on_horizontalSliderVariableStrength_valueChanged(int value);

private:
    Ui::PropertyMakeAverageImageForm *ui;

	MakeAverageImageBase	*GetMakeAverageImageBase(void);
};

#endif // PROPERTYMAKEAVERAGEIMAGEFORM_H