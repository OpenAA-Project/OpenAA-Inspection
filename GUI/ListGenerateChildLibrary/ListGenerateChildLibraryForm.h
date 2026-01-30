/*
 * Copyright (C) 2022
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

#ifndef LISTGENERATECHILDLIBRARYFORM_H
#define LISTGENERATECHILDLIBRARYFORM_H

#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "LibFolderForm.h"

namespace Ui {
class ListGenerateChildLibraryForm;
}

class	GeneralLibFolderForm;
class	ListGenerateChildLibraryForm;

class	LibFolderTreeForm : public LibFolderForm
{
	ListGenerateChildLibraryForm	*Parent;
public:
	LibFolderTreeForm(ListGenerateChildLibraryForm *p ,int libType ,LayersBase *lbase ,QWidget *parent = 0);

protected:
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event );
};

class ListGenerateChildLibraryForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit ListGenerateChildLibraryForm(LayersBase *Base,QWidget *parent = 0);
    ~ListGenerateChildLibraryForm();

	virtual	void	BuildForShow(void)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual	void	RxSync(QByteArray &f)	override;


private slots:
    void on_pushButtonGenerate_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	ResizeAction();
public slots:
    void on_pushButtonSelect_clicked();

private:
    Ui::ListGenerateChildLibraryForm *ui;

	LibFolderTreeForm	*pLibFolderForm;
	int		LibFolderID;
};

#endif // LISTGENERATECHILDLIBRARYFORM_H