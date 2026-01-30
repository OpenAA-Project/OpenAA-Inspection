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


#ifndef SELECTLIBRARYINMASKFORM_H
#define SELECTLIBRARYINMASKFORM_H

#include <QWidget>
#include "ui_SelectLibraryInMaskForm.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class SelectLibrariesForAnyType;

class SelectLibraryInMaskForm : public QWidget ,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectLibraryInMaskForm(bool NewMode ,LayersBase *Base ,QWidget *parent = 0);
	~SelectLibraryInMaskForm();

	SelectLibrariesForAnyType		*Libs;
	bool	RetOK;
	bool	Effective;
	bool	DeleteMode;
	void	SetSelected(AlgorithmLibraryListContainer &selectedList);
	AlgorithmLibraryListContainer		GetSelectedList(void);
private:
	Ui::SelectLibraryInMaskFormClass ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;
signals:
	void	SignalClose(void);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonNotEffective_clicked();
	void on_ButtonEffective_clicked();
    void on_pushButtonDelete_clicked();
};

#endif // SELECTLIBRARYINMASKFORM_H