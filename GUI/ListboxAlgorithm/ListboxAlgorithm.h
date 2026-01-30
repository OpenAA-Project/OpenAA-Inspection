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


#ifndef LISTBOXALGORITHM_H
#define LISTBOXALGORITHM_H

#include "listboxalgorithm_global.h"

#include <QTabWidget>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

class	AlgorithmList : public WMultiGrid ,public ServiceForLayers
{
    Q_OBJECT
public:
	AlgorithmList(LayersBase *Base,QWidget *parent = 0);
	
	virtual	void	ChangeValue(int row ,int col,const QVariant &value)	override;
	virtual	void	GetValue(int row ,int col,QVariant &value)			override;

	void	ShowGrid(void);
};

class	ListboxAlgorithm : public GUIFormBase
{
	Q_OBJECT

	AlgorithmList	MainList;
public:
	bool	IsShowOrganization;
	bool	IsShowPath;
	bool	IsShowRoot;
	bool	IsShowName;

	ListboxAlgorithm(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithm(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};
#endif // LISTBOXALGORITHM_H