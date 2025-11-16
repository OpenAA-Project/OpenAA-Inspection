/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\EditOutlineOffset.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
