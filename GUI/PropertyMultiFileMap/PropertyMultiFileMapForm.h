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

#ifndef PROPERTYMULTIFILEMAPFORM_H
#define PROPERTYMULTIFILEMAPFORM_H

#include "XGUIFormBase.h"
#include "XMultiFileMap.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyMultiFileMapForm;
}

class PropertyMultiFileMapForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyMultiFileMapForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMultiFileMapForm();

	MultiFileMapBase	*GetMultiFileMapBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	MultiFileMapLibrary	*TempLib;
	int					LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private:
    Ui::PropertyMultiFileMapForm *ui;
};

#endif // PROPERTYMULTIFILEMAPFORM_H