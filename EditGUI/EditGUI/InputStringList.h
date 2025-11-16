/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\InputStringList.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
