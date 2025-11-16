/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibraryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBRARYFORM_H
#define SELECTLIBRARYFORM_H

#include <QWidget>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryForm;
}

class   LibFolderForm;

class SelectLibraryForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibraryForm(int libType ,LayersBase *Base,QWidget *parent = 0);
    ~SelectLibraryForm();

    int		SelectedLibID;
    QString	SelectedLibName;

signals:
    void	SignalClose();
private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibraryForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) override;

    LibFolderForm					*pLibFolderForm;
    int								LibFolderID;
    int								LibType;
    AlgorithmLibraryListContainer	LibIDList;

    void	ShowFolder(int LibType);
};

#endif // SELECTLIBRARYFORM_H
