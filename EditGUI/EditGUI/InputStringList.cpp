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


#include "InputStringList.h"

InputStringList::InputStringList(const QModelIndex &_Index ,PropertyList *_ParentRoot 
                                ,const QStringList &mlist,QWidget *parent)
    : QDialog(parent),Index(_Index),Parent(_ParentRoot)
{
	ui.setupUi(this);

    RGrid.setParent(this);
    RGrid.move(0,0);
    RGrid.SetColumnCount(1);
    MList=mlist;
    SetGrid();
    connect(&RGrid,SIGNAL(Changed()),this,SLOT(Changed()),Qt::QueuedConnection);
}

InputStringList::~InputStringList()
{

}
void	InputStringList::SetGrid(void)
{
    RGrid.SetRowCount(MList.count());
    RGrid.move(0,0);
    RGrid.resize(width(),height()-ui.frame->height());
    for (int r=0;r<MList.count();r++) {
        WMultiGrid::CellData* L=RGrid.GetData(r,0);
        L->Value	=MList.value(r);
        L->CType	=WMultiGrid::_CType_LineEdit;
        L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
    }
    //WMultiGrid::CellData* L=RGrid.GetData(MList.count(),0);
    //L->Value	=MList.value(MList.count());
    //L->CType	=WMultiGrid::_CType_LineEdit;
    //L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
    RGrid.InitialGrid();
}

void InputStringList::resizeEvent (QResizeEvent* event)
{
    RGrid.resize(width(),height()-ui.frame->height());
    ui.frame->setGeometry(0,height()-ui.frame->height(),width(),ui.frame->height());
    RGrid.setColumnWidth(0,width()-72);
}
void	InputStringList::Changed()
{
    SetGrid();
}
void InputStringList::on_pushButtonOK_clicked()
{
    done(true);
}


void InputStringList::on_pushButtonAddLine_clicked()
{
    MList.append(/**/"");
    int N=RGrid.GetRowCount();
    RGrid.AppendRow();
    WMultiGrid::CellData* L=RGrid.GetData(N,0);
    L->Value	=/**/"";
    L->CType	=WMultiGrid::_CType_LineEdit;
    L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
    RGrid.ShowGrid();
}


void InputStringList::on_pushButtonDeleteCurrentLine_clicked()
{
    int row=RGrid.currentIndex().row();
    if (row>=0) {
        MList.removeAt(row);
        RGrid.RemoveLine(row);
        RGrid.ShowGrid();
    }
}
