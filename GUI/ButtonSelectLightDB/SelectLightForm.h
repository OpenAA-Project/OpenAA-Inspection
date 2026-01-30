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

#ifndef SELECTLIGHTFORM_H
#define SELECTLIGHTFORM_H

#include <QWidget>
#include <QByteArray>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NList.h"

namespace Ui {
class SelectLightForm;
}

class SelectLightForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

    class	LightPacket : public NPList<LightPacket>
    {
    public:
        int		MachineID;
        int		LightID;
    };
    NPListPack<LightPacket>	LightLines;
public:
    explicit SelectLightForm(LayersBase *pbase ,bool ShowSelectButtons ,bool EditPanel, int SelectMachineCode=-1 ,QWidget *parent = 0);
    ~SelectLightForm();

    int		SelectedMachineID;
    int		SelectedLightID;
    QByteArray	SelectedLight;

signals:
    void	SignalClose();
private slots:
    void on_tableWidgetLight_clicked(const QModelIndex &index);
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectLightForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;

    void	ShowList(void);
    void	SelectOne(void);
};

#endif // SELECTLIGHTFORM_H