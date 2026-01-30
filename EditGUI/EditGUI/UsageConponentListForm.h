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

#ifndef USAGECONPONENTLISTFORM_H
#define USAGECONPONENTLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NList.h"

namespace Ui {
class UsageConponentListForm;
}

class	GUIItemInstance;
class	EditGUI;

class UsageConponentListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    EditGUI	*Parent;

public:
    class	GUIItemInstancePointerList : public NPList<GUIItemInstancePointerList>
    {
    public:
        GUIItemInstance	*Point;

        GUIItemInstancePointerList(GUIItemInstance *p):Point(p){}
    };

    NPListPack<GUIItemInstancePointerList>	ItemListContainer;

public:
    explicit UsageConponentListForm(EditGUI *p,LayersBase *base,QWidget *parent = 0);
    ~UsageConponentListForm();
    
private slots:
    void MListSectionClicked (int);
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonMakeCopyBAT_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonExcludedListOut_clicked();

private:
    Ui::UsageConponentListForm *ui;
    virtual	void	resizeEvent ( QResizeEvent * event ) override;
	void ShowList(void);
};

#endif // USAGECONPONENTLISTFORM_H