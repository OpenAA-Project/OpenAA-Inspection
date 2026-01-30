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

#ifndef PROJECTEDINSPECTIONIMAGEPANEL_H
#define PROJECTEDINSPECTIONIMAGEPANEL_H

#include "projectedinspectionimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XProjectedInspection.h"
#include "XDisplayImage.h"


class	ProjectedInspectionImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	ProjectedInspectionImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)		override;

	virtual	void	DrawEndAfterOperation(FlexArea &area)					override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

private slots:
};

#endif // PROJECTEDINSPECTIONIMAGEPANEL_H