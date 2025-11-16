/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShowOK.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef OUTSEQUENCESHOWOK_H
#define OUTSEQUENCESHOWOK_H

#include <QWidget>

namespace Ui {
class OutSequenceShowOK;
}

class   ThreadSequence;
class   Sequence;
class	SeqControl;

class OutSequenceShowOK : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceShowOK(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceShowOK();

    void	ShowMessage(QString &msg);
    int                     WRegID;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;
    ThreadSequence  *SeqParent;

private slots:
    void on_OKButton_clicked();

private:
    Ui::OutSequenceShowOK *ui;
    virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // OUTSEQUENCESHOWOK_H
