/*
 * Copyright (C) 2021
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

#ifndef COPYLIBRARYFORM_H
#define COPYLIBRARYFORM_H

#include <QDialog>
#include "ui_CopyLibraryForm.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CopyLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CopyLibraryForm(const QString &AlgoRoot , const QString &AlgoName 
					, LayersBase *base ,QWidget *parent = 0);
	~CopyLibraryForm();

	QString AlgoRoot;
	QString AlgoName;
	AlgorithmBase	*ABase;

	int		LibType;
	GeneralLibFolderForm	*pLibFolderFormSrc;
	int		LibFolderIDSrc;
	void	ShowLibrarySrc(AlgorithmLibrary &data);

	GeneralLibFolderForm	*pLibFolderFormDst;
	int		LibFolderIDDst;
	void	ShowLibraryDst(AlgorithmLibrary &data);

private:
	Ui::CopyLibraryFormClass ui;

	AlgorithmLibraryListContainer	LibIDListSrc;
	AlgorithmLibraryListContainer	LibIDListDst;

private slots:
	void on_pushButtonAll_clicked();
	void on_pushButtonClose_clicked();
	void on_pushButtonCopy_clicked();
	void	SlotSelectLibFolderSrc(int LibFolderID ,QString FolderName);
	void	SlotSelectLibFolderDst(int LibFolderID ,QString FolderName);
};

#endif // COPYLIBRARYFORM_H