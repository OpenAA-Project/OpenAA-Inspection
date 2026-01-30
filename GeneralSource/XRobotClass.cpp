/*
 * Copyright (C) 2025
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

#include "XRobotClass.h"

RobotFigure::RobotFigure(void)
{
}
RobotFigure::RobotFigure(const RobotFigure &src)
{
	Position=src.Position	;
	Angle	=src.Angle		;
}

RobotFigure	&RobotFigure::operator=(const RobotFigure &src)
{
	Position=src.Position	;
	Angle	=src.Angle		;
	return *this;
}

bool	RobotFigure::Save(QIODevice *f)
{
	if(Position.Save(f)	==false)	return false;
	if(Angle.Save(f)	==false)	return false;
	return true;
}

bool	RobotFigure::Load(QIODevice *f)
{
	if(Position.Load(f)	==false)	return false;
	if(Angle.Load(f)	==false)	return false;
	return true;
}
