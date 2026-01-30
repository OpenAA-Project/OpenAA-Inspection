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

#ifndef PROPERTYPALLETIZEFORM_H
#define PROPERTYPALLETIZEFORM_H

#include "XGUIFormBase.h"
#include "XPalletize.h"
#include "XStandardPropertyForm.h"
#include <QLocalSocket>

namespace Ui {
class PropertyPalletizeForm;
}

class PalletizeBase;

class PropertyPalletizeForm : public GUIFormBase
{
    Q_OBJECT

    QLocalSocket    Sock;
    IntList         LastIndexMasterPosList;

	MatchingResultContainer LastResult;
public:
    explicit PropertyPalletizeForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyPalletizeForm();

 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
    virtual void	ShowInPlayer		(int64 shownInspectionID=-1)    override;
private slots:
    void on_pushButtonEditLibrary_clicked();
    void on_pushButtonSend_clicked();

private:
    Ui::PropertyPalletizeForm *ui;

    PalletizeBase	*GetPalletizeBase(void);
    void    TransferMotorData(double Dim[5]);
    void    ShowResultGrid(PalletizeItem *Item ,int IndexMasterPos,MatchingResult *MatchingResultList);
};

#endif // PROPERTYPALLETIZEFORM_H