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

#ifndef PROPERTYCHECKEVERYDAYFORM_H
#define PROPERTYCHECKEVERYDAYFORM_H

#include <QDialog>
#include "XCheckEveryday.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XCheckEverydayGUIPacket.h"
#include "XCheckEverydayCommon.h"

namespace Ui {
class PropertyCheckEverydayForm;
}

class PropertyCheckEverydayForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyCheckEverydayForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyCheckEverydayForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//virtual void	StartPage	(void)	override;

	CheckEverydayLightInfoContainer	InfoLight;
	CheckEverydayFocusInfoContainer	InfoFocus;
    
	virtual	void showEvent ( QShowEvent * event )	override;
	virtual void	BuildForShow(void)	override;
	CheckEverydayBase	*GetCheckEverydayBase(void);
	void ShowGrid(void);

private slots:
    void on_toolButtonLight_clicked();
    void on_toolButtonFocus_clicked();
    void on_pushButtonSave_clicked();

    void on_tableWidgetLight_clicked(const QModelIndex &index);
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);
    void on_tableWidgetFocus_clicked(const QModelIndex &index);
    void on_tableWidgetFocus_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyCheckEverydayForm *ui;
};

#endif // PROPERTYCHECKEVERYDAYFORM_H