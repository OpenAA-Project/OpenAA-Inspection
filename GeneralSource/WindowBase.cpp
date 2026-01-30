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



#include "WindowBase.h"

WindowBase::WindowBase(const QString &title, QWidget *parent)
	: QDockWidget(title,parent)
{
}

WindowBase::~WindowBase()
{
}

bool WindowBase::Save(QIODevice *file)
{
	int W=width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H=height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H))
		return false;

	return true;
}

bool WindowBase::Load(QIODevice *file)
{
	int W;
	if(file->read((char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H;
	if(file->read((char *)&H,sizeof(H))!=sizeof(H))
		return false;

	setMinimumSize(W,H);
	setMaximumSize(W,H);

	return true;
}