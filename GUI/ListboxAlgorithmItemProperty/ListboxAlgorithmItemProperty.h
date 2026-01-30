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


#ifndef LISTBOXALGORITHMITEMPROPERTY_H
#define LISTBOXALGORITHMITEMPROPERTY_H

#include "listboxalgorithmitemproperty_global.h"
#include <QTabWidget>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WMultiGrid.h"

#include "AlgorithmItemPropertyGrid.h"


class	ListboxAlgorithmItemProperty : public GUIFormBase
{
	Q_OBJECT

public:
	AlgorithmItemPropertyGrid	MainList;
	AlgorithmItemPropertyContainer AlgorithmItemPropertyData;

	ListboxAlgorithmItemProperty(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithmItemProperty(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};
#endif // LISTBOXALGORITHMITEMPROPERTY_H