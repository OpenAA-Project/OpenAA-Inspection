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



#ifndef INPUTSTRINGLIST_H
#define INPUTSTRINGLIST_H

#include <QDialog>
#include "ui_InputStringList.h"
#include "propertylist.h"

class InputStringList : public QDialog
{
    Q_OBJECT
        
    StringListDialogList	RGrid;
public:
    const QModelIndex       Index;
    PropertyList            *Parent;
    QStringList	MList;

    InputStringList(const QModelIndex &_Index ,PropertyList *_ParentRoot 
                    ,const QStringList &mlist,QWidget *parent=nullptr);
    ~InputStringList();

public:
    void	SetGrid(void);
private slots:
    void	Changed();
protected:
    virtual	void resizeEvent (QResizeEvent* event)	override;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDeleteCurrentLine_clicked();

private:
    Ui::InputStringListClass ui;
};

#endif // INPUTSTRINGLIST_H