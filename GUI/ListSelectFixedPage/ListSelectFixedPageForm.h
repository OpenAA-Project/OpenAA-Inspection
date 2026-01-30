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

#ifndef LISTSELECTFIXEDPAGEFORM_H
#define LISTSELECTFIXEDPAGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>


namespace Ui {
class ListSelectFixedPageForm;
}

class ListSelectFixedPageForm : public GUIFormBase
{
    Q_OBJECT

public:
    QStringList DisplayImageInst;

    explicit ListSelectFixedPageForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ListSelectFixedPageForm();

    virtual void	BuildForShow(void);
    virtual bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)    override;
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_listWidgetPage_itemSelectionChanged();
    void on_listWidgetPage_clicked(const QModelIndex &index);

private:
    Ui::ListSelectFixedPageForm *ui;

    void    ShowPageList(void);
private slots:
	void	ResizeAction();
};

#endif // LISTSELECTFIXEDPAGEFORM_H