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


#ifndef MESSAGEBOXSTRINGLIST_H
#define MESSAGEBOXSTRINGLIST_H

#include <QDialog>
#include <QStringList>
#include "XServiceForLayers.h"

namespace Ui {
class MessageBoxStringList;
}

class MessageBoxStringList : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MessageBoxStringList(LayersBase *lbase ,QStringList &Msg ,QWidget *parent = 0);
    ~MessageBoxStringList();
    
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::MessageBoxStringList *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // MESSAGEBOXSTRINGLIST_H