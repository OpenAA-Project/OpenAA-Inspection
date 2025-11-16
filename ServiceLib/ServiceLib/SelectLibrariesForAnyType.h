/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibrariesForAnyType.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBRARIESFORANYTYPE_H
#define SELECTLIBRARIESFORANYTYPE_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectLibrariesForAnyType;
}

class   LibFolderForm;

class SelectLibrariesForAnyType : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibrariesForAnyType(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibrariesForAnyType();

    AlgorithmLibraryListContainer	SelectedList;
    void	SetSelected(AlgorithmLibraryListContainer &selectedList);

    void	SetLibTypeInComboBox(void);
    void	ShowFolder(int LibType);
    void	ShowSelectedList(void);

    bool	Save(QIODevice *f);
    bool	Load(QIODevice *f);

    void	setFocusComboBForMaskingForm( void );	// 2010/04/21 MW_I マスク画面変更対応
    void	resizeForMaskingForm( void );			// 2010/04/21 MW_I マスク画面変更対応

private slots:
    void on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_comboBLibType_currentIndexChanged(int index);
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);



private:
    Ui::SelectLibrariesForAnyType *ui;

    bool                            InitialMode;
    LibFolderForm					*pLibFolderForm;
    int								LibFolderID;
    int								LibType;
    AlgorithmLibraryListContainer	LibIDList;

    virtual	void closeEvent (QCloseEvent * event)   override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    virtual void showEvent(QShowEvent *e)   override;
};

#endif // SELECTLIBRARIESFORANYTYPE_H
