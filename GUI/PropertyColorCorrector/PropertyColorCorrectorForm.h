/*
 * Copyright (C) 2025
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

#ifndef PROPERTYCOLORCORRECTORFORM_H
#define PROPERTYCOLORCORRECTORFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XColorCorrector.h"
#include "XPropertyColorCorrectorPacket.h"

namespace Ui {
class PropertyColorCorrectorForm;
}
class ColorCorrectorBase;

class PropertyColorCorrectorForm : public GUIFormBase
{
    Q_OBJECT

    ColorCorrectorGridListContainer GridList;
public:
    explicit PropertyColorCorrectorForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyColorCorrectorForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void on_pushButtonExecuteTarget_clicked();
    void on_pushButtonAutoGenerate_clicked();

private:
    Ui::PropertyColorCorrectorForm *ui;

    ColorCorrectorBase	*GetColorCorrectorBase(void);
    void    ShowList(void);
};

#endif // PROPERTYCOLORCORRECTORFORM_H