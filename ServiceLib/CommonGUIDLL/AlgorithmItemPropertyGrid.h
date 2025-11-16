/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\AlgorithmItemPropertyGrid.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef ALGORITHMITEMPROPERTYGRID_H
#define ALGORITHMITEMPROPERTYGRID_H

#include <QWidget>
#include "XDataAlgorithm.h"

namespace Ui {
class AlgorithmItemPropertyGrid;
}

class	AlgorithmItemPropertyLine : public NPList<AlgorithmItemPropertyLine>
{
public:
    QString		CategoryName;
    QString		PropertyName;
    QStringList	Values;
};

class AlgorithmItemPropertyGrid : public QWidget
{
    Q_OBJECT
    
public:
    explicit AlgorithmItemPropertyGrid(QWidget *parent = 0);
    ~AlgorithmItemPropertyGrid();

    AlgorithmItemPropertyContainer			AlgorithmItemPropertyData;
    NPListPack<AlgorithmItemPropertyLine>	ItemLines;

    void	ShowGrid(const AlgorithmItemPropertyContainer &_AlgorithmItemPropertyData);
protected:
    virtual void closeEvent ( QCloseEvent * event ) override;
private:
    Ui::AlgorithmItemPropertyGrid *ui;
};

#endif // ALGORITHMITEMPROPERTYGRID_H
