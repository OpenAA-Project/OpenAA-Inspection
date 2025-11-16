/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShow.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef OUTSEQUENCESHOW_H
#define OUTSEQUENCESHOW_H

#include <QWidget>

namespace Ui {
class OutSequenceShow;
}

class   ThreadSequence;
class   Sequence;
class	SeqControl;

class OutSequenceShow : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceShow(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceShow();

    void	ShowMessage(QString &msg);
    int                     WRegID;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;
    ThreadSequence  *SeqParent;

private:
    Ui::OutSequenceShow *ui;
};

#endif // OUTSEQUENCESHOW_H
