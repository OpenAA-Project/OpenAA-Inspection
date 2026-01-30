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

#pragma once
#include <QColor>
#include <QString>
#include<QCheckBox>

class RasterFileLayerLine
{
	QCheckBox	*ShownBox;
public:
	int	FileLayerID;
	QString	FileName;
	QColor	Color;

	RasterFileLayerLine(void);
	RasterFileLayerLine(const RasterFileLayerLine &src);

	QColor	GetColor(void)		{	return Color;	}
	void	SetShown(bool b);
	bool	GetShown(void);

	void	StoreFromWindow(void);
	void	ReflectToWindow(void);
	bool	SaveContent(QIODevice *f);
	bool	LoadContent(QIODevice *f);
};
