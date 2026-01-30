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

#ifndef DISPLAYOLDIMAGEPANEL_H
#define DISPLAYOLDIMAGEPANEL_H

#include "displayoldimagepanel_global.h"
#include "XDisplayImage.h"
#include "XDisplayOldImagePanel.h"
#include "XTypeDef.h"

class	NamingNGContainer;
class	NamingNG;

class	DisplayOldImagePanel : public DisplayImage
{
	Q_OBJECT

	NamingInfoContainer	*NamingData;
	NamingNGContainer	*NGNaming;
public:

	DisplayOldImagePanel(LayersBase *Base ,QWidget *parent);
	~DisplayOldImagePanel(void);

	virtual void	Prepare(void)	override;

	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;

	virtual	void	BuildForShow(void)						override;
	virtual	void	ShowInPlayer(int64 shownInspectionID)	override;

	int32		GenerationLevel;	//0:Current 1�`:n older

private:
	NamingNG	*FindNG(NamingInfo *a);

};

#endif // DISPLAYOLDIMAGEPANEL_H