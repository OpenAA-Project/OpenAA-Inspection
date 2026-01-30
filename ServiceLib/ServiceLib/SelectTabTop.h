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

#ifndef SELECTTABTOP_H
#define SELECTTABTOP_H

#include <QDialog>
#include <QTabWidget>
#include <QStackedWidget>
#include <QWidgetList>
#include "XServiceForLayers.h"

namespace Ui {
class SelectTabTop;
}

class SelectTabTop : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    QWidgetList	TabList;
public:
    explicit SelectTabTop(LayersBase *lbase ,QWidgetList &list ,QWidget *parent = 0);
    ~SelectTabTop();

    QTabWidget		*SelectedTabSheet;
    QStackedWidget	*SelectedStackedSheet;
    int			SelectedTabPage;
    bool		RetMode;

private slots:
    void on_comboBTabSheet_currentIndexChanged(int index);
    void on_comboBTabPage_currentIndexChanged(int index);
    void on_OKButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::SelectTabTop *ui;
    virtual	void closeEvent ( QCloseEvent * event ) override;
};

#endif // SELECTTABTOP_H