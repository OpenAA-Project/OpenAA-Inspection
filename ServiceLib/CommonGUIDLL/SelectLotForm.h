/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\SelectLotForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLOTFORM_H
#define SELECTLOTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "commonguidll_global.h"

namespace Ui {
class SelectLotForm;
}
class	GUIFormBase;

class SelectLotForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    GUIFormBase	*ParentGUI;
public:
    explicit SelectLotForm(LayersBase *pbase ,QWidget *parent, QWidget *parentGUI ,int MaxLines);
    ~SelectLotForm();

    bool	RetMode;

    int			SelectedLotAutoCount;
    QString		SelectedLotID;
    QString		SelectedLotName;
    XDateTime	SelectedLastUpdated;
    QString		SelectedRemark;

    bool	RxSync(QByteArray &f);
    bool	RxSync(QIODevice &Buff);

    virtual	void	TxSync(QBuffer &f);

    void	CreateNewLot(const QString &LotID ,const QString &LotName ,bool Synchronized=true);


signals:
    void	SignalClose();

private slots:
    void on_tableWidgetLot_clicked(const QModelIndex &index);
    void on_tableWidgetLot_doubleClicked(const QModelIndex &index);
    void on_ButtonCreate_clicked();
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectLotForm *ui;
    IntList	LotAutoCounts;

    bool SelectLotAction(void);
    bool ExecuteCreateNew(void);

    virtual	void	closeEvent ( QCloseEvent * event )	override;
};

#endif // SELECTLOTFORM_H
