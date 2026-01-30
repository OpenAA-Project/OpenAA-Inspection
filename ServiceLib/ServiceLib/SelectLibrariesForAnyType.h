/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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