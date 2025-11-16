/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceMessage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef OUTSEQUENCEMESSAGE_H
#define OUTSEQUENCEMESSAGE_H

#include <QWidget>

namespace Ui {
class OutSequenceMessage;
}
class	SeqControl;

class OutSequenceMessage : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceMessage(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceMessage();

    volatile    bool    OnAwake;

    void	ShowMessage(QString &msg);
    virtual void showEvent ( QShowEvent * event )	override;
    virtual void closeEvent ( QCloseEvent * e )		override;

private slots:
    void on_OKButton_clicked();

private:
    Ui::OutSequenceMessage *ui;
};

#endif // OUTSEQUENCEMESSAGE_H
