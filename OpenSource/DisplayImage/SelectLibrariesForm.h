/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectLibrariesForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBRARIESFORM_H
#define SELECTLIBRARIESFORM_H

#include <QWidget>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibrariesForm;
}

class SelectLibrariesForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibrariesForm(int libType ,LayersBase *Base,QWidget *parent = 0);
    ~SelectLibrariesForm();

    AlgorithmLibraryListContainer	SelectedList;
    void	SetSelected(const AlgorithmLibraryListContainer &selectedList);

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index);
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::SelectLibrariesForm *ui;

    LibFolderForm					*pLibFolderForm;
    int								LibFolderID;
    int								LibType;
    AlgorithmLibraryListContainer	LibIDList;

    void	ShowFolder(int LibType);
    void	ShowSelectedList(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTLIBRARIESFORM_H
