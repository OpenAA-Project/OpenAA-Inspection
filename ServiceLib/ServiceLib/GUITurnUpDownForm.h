/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\GUITurnUpDownForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GUITURNUPDOWNFORM_H
#define GUITURNUPDOWNFORM_H

#include <QDialog>
#include <QTabWidget>
#include <QStackedWidget>

namespace Ui {
class GUITurnUpDownForm;
}
class	GUIFormBase;

class GUITurnUpDownForm : public QDialog
{
    Q_OBJECT

    QWidgetList	TabList;
    QTabWidget		*SelectedTabSheet;
    QStackedWidget	*SelectedStackedSheet;
    GUIFormBase		*Form;

public:
    explicit GUITurnUpDownForm(const QWidgetList &list,GUIFormBase *Form ,QWidget *parent = 0);
    ~GUITurnUpDownForm();

    void	ShowList(void);

private slots:
    void on_comboBTabSheet_currentIndexChanged(int index);
    void on_pushButtonOK_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();

private:
    Ui::GUITurnUpDownForm *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // GUITURNUPDOWNFORM_H
