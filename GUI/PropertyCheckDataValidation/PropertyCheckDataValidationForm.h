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

#ifndef PROPERTYCHECKDATAVALIDATIONFORM_H
#define PROPERTYCHECKDATAVALIDATIONFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XCheckDataValidation.h"
#include "XPropertyCheckDataValidationPacket.h"

namespace Ui {
class PropertyCheckDataValidationForm;
}

class ShowNGMessageForm;

class PropertyCheckDataValidationForm : public GUIFormBase
{
    Q_OBJECT

    CheckDataValidationGridListContainer    GridList;
    bool    ModeShowNGMessage;
public:
    explicit PropertyCheckDataValidationForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyCheckDataValidationForm();

    virtual void	ReadyParam(void)    override;
 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
    void on_toolButtonExistItemArea_clicked();
    void on_toolButtonExistItemVector_clicked();
    void on_toolButtonMinMax_clicked();
    void on_toolButtonProhibiteItem_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void    SlotShowNGMessage(int phase ,int page);
private:
    Ui::PropertyCheckDataValidationForm *ui;
    ShowNGMessageForm   *NGMessageWindow;

    CheckDataValidationBase	*GetCheckDataValidationBase(void);

    void ShowList(void);
    void ReDrawImage(void);
};

#endif // PROPERTYCHECKDATAVALIDATIONFORM_H