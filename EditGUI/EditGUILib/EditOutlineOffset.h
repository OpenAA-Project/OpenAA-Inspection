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


#ifndef EDITOUTLINEOFFSET_H
#define EDITOUTLINEOFFSET_H

#include <QWidget>
#include"XParamGlobal.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditOutlineOffset;
}

class	EditOutlineOffset;

class	OutlineOffsetGrid : public WMultiGrid
{
    EditOutlineOffset	*EParent;

public:
    OutlineOffsetGrid(EditOutlineOffset *eParent ,QWidget * parent=0):WMultiGrid(parent),EParent(eParent){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};

class EditOutlineOffset : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    OutlineOffsetGrid	aGrid;
    int ParentWindowHeight;
public:
    explicit EditOutlineOffset(LayersBase *Base,int ParentWindowHeight=-1,QWidget *parent=NULL);
    ~EditOutlineOffset();

    void	SetGrid(void);

signals:
    void	ChangedValue();
public slots:
    void	ChangeValue();
private slots:
    void on_pushButton_clicked();
    void SlotClickedXYButton( int row ,int col);
private:
    Ui::EditOutlineOffset *ui;
};

#endif // EDITOUTLINEOFFSET_H