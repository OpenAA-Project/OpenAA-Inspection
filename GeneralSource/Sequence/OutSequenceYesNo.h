/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceYesNo.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef OUTSEQUENCEYESNO_H
#define OUTSEQUENCEYESNO_H

#include <QWidget>

namespace Ui {
class OutSequenceYesNo;
}

class	SeqControl;
class	ThreadSequence;

class OutSequenceYesNo : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceYesNo(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceYesNo();

    volatile    bool    OnAwake;
    bool        OKMode;
    void	ShowMessage(QString &msg);
    virtual void showEvent ( QShowEvent * event )	override;
    virtual void closeEvent ( QCloseEvent * e )		override;
    ThreadSequence  *SeqParent;

private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();

private:
    Ui::OutSequenceYesNo *ui;
};

#endif // OUTSEQUENCEYESNO_H
