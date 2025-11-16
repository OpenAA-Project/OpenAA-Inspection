/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\itemlistwindow.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
