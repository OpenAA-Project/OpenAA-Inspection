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

#pragma once

#include "NListComp.h"
#include <QString>
#include <QDateTime>
#include <QTextStream>
#include "XTypeDef.h"

#define		TmpFolderNameToUpdate	"_UpdatedFiles"

class UpdatedFileList : public NPListSaveLoad<UpdatedFileList>
{
public:
	enum Operation
	{
		_Update
		,_ForceUpdate
		,_Delete
	};
	Operation	FileOperation;
	QString		RelativeFileName;
	QDateTime	FileStamp;

	UpdatedFileList(void);
	~UpdatedFileList(void);

	virtual	bool	Save(QIODevice* f)	override;
	virtual	bool	Load(QIODevice* f)	override;
private:
};

class UpdatedFileListContainer : public NPListPackSaveLoad<UpdatedFileList>
{
public:
	QString		Version;

	UpdatedFileListContainer(void) {}
	~UpdatedFileListContainer(void) {}

	virtual	UpdatedFileList* Create(void)	override;

	bool	LoadFromFileList(const QString& AbsPath, QTextStream &Txt);
	bool	SaveFileList(const QString& AbsPath, QTextStream& Txt);

	UpdatedFileListContainer	&operator=(const UpdatedFileListContainer &src);

	virtual	bool	Save(QIODevice* f)	override;
	virtual	bool	Load(QIODevice* f)	override; 

private:

};
