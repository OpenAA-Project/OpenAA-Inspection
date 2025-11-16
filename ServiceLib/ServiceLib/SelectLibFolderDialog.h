/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibFolderDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBFOLDERDIALOG_H
#define SELECTLIBFOLDERDIALOG_H

#include <QDialog>


namespace Ui {
class SelectLibFolderDialog;
}
class	LayersBase;
class   LibFolderForm;

class SelectLibFolderDialog : public QDialog
{
    Q_OBJECT
    LibFolderForm	*pLibFolderForm;

public:
    explicit SelectLibFolderDialog(int LibType ,LayersBase * base, QWidget *parent = 0);
    ~SelectLibFolderDialog();

    int		SelectedLibFolderID;
    QString SelectedFolderName;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::SelectLibFolderDialog *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // SELECTLIBFOLDERDIALOG_H
