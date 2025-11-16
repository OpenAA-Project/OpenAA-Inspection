/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectTabTop.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTTABTOP_H
#define SELECTTABTOP_H

#include <QDialog>
#include <QTabWidget>
#include <QStackedWidget>
#include <QWidgetList>
#include "XServiceForLayers.h"

namespace Ui {
class SelectTabTop;
}

class SelectTabTop : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    QWidgetList	TabList;
public:
    explicit SelectTabTop(LayersBase *lbase ,QWidgetList &list ,QWidget *parent = 0);
    ~SelectTabTop();

    QTabWidget		*SelectedTabSheet;
    QStackedWidget	*SelectedStackedSheet;
    int			SelectedTabPage;
    bool		RetMode;

private slots:
    void on_comboBTabSheet_currentIndexChanged(int index);
    void on_comboBTabPage_currentIndexChanged(int index);
    void on_OKButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::SelectTabTop *ui;
    virtual	void closeEvent ( QCloseEvent * event ) override;
};

#endif // SELECTTABTOP_H
