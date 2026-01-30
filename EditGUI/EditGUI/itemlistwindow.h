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

#ifndef ITEMLISTWINDOW_H
#define ITEMLISTWINDOW_H

#include <QWidget>
#include "XGUI.h"
#include "XGUIFormBase.h"
#include <QToolButton>
#include <QStatusBar>
#include <QScrollArea>
#include <QMouseEvent>
#include <QLabel>
#include <QResizeEvent>

namespace Ui {
class ItemListWindow;
}


class	ItemButtonList;
class	ItemListWindow;

class	ItemButton : public QToolButton
{
    Q_OBJECT
public:
    ItemButtonList	*ItemPoint;
    ItemListWindow	*RootParent;

    ItemButton(QWidget *parent);

    void mouseMoveEvent ( QMouseEvent * event );
public slots:
    virtual	void	SlotClick(void);
};

class	TabScrollArea : public QScrollArea
{
public:
    QWidget	*W;
    TabScrollArea( QWidget * parent = 0 ):QScrollArea(parent){	W=NULL;	}
};

class	ItemButtonList : public NPList<ItemButtonList>
{
public:
    GuiDLLItem	*DLLPoint;
    ItemButton	*Button;
    QWidget		*Parent;
    QLabel		*LabelName;
    QLabel		*LabelExplain;
    QWidget		*TabBase;
    int			Page;

    ItemButtonList(void);
    ~ItemButtonList(void);

    void		setUnchecked();

    virtual	int	Compare(ItemButtonList &src)	override;
};


class ItemListWindow : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit ItemListWindow(LayersBase *Base,QWidget *parent = 0);
    ~ItemListWindow();

    void	Initial(void);
    void	ShowItems(void);

    NPListPack<ItemButtonList>	Item[1000];
    QStatusBar	SBar;

    ItemButtonList	*GetActiveButton(void);
    void	SelectGUI(GUINameClassified *v);

protected:
    virtual	void resizeEvent ( QResizeEvent * event )	override;
private:
    Ui::ItemListWindow *ui;
};

#endif // ITEMLISTWINDOW_H