/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\SelectWorkerForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTWORKERFORM_H
#define SELECTWORKERFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include <QSqlTableModel>
#include "XServiceForLayers.h"

namespace Ui {
class SelectWorkerForm;
}

class	QSqlWorkerListModel : public QSqlTableModel
{
public:
    QSqlWorkerListModel(QObject * parent, QSqlDatabase db);
    QString selectStatement () const;
};

class SelectWorkerForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectWorkerForm(LayersBase *pbase ,QWidget *parent = 0);
    ~SelectWorkerForm();

    int		SelectWorkerID;
    QString	SelectWorkerName;

signals:
    void	SignalClose();
private slots:
    void on_ButtonSelect_clicked();
    void	SlotClicked(const QModelIndex &Index);
    void	SlotDoubleClicked(const QModelIndex &Index);
private:
    Ui::SelectWorkerForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // SELECTWORKERFORM_H
