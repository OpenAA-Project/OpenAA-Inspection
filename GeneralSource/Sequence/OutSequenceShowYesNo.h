/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShowYesNo.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef OUTSEQUENCESHOWYESNO_H
#define OUTSEQUENCESHOWYESNO_H

#include <QWidget>

namespace Ui {
class OutSequenceShowYesNo;
}
class   ThreadSequence;
class   Sequence;
class	SeqControl;

class OutSequenceShowYesNo : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceShowYesNo(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceShowYesNo();

    void	ShowMessage(QString &msg);
    int                     WRegID;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;
    ThreadSequence  *SeqParent;
private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();

private:
    Ui::OutSequenceShowYesNo *ui;
    virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // OUTSEQUENCESHOWYESNO_H
