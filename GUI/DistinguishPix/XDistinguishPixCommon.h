/*
 * Copyright (C) 2019
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

#if	!defined(XDistinguishPixCommon_H)
#define	XDistinguishPixCommon_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	FileListContainer;
class	FileListLeaf;

class	JudgeTargetBroadcaster : public SpecifiedBroadcaster
{
public:
	QString	FolderName;
	QString	FileName;
	int		Judgement;
	QString	JudgeStr;

	JudgeTargetBroadcaster(void){}
};

class	CmdReqFileListContainer: public GUIDirectMessage
{
public:
	FileListContainer	*Container;

	CmdReqFileListContainer(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFileListContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqLoadImageIntoTarget: public GUIDirectMessage
{
public:
	FileListLeaf	*Pointer;
	bool			Success;

	CmdReqLoadImageIntoTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLoadImageIntoTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//--------------------------------------------------------------------------------

class	FileListLeaf : public NPList<FileListLeaf>
{
public:
	QString		UFolderName;
	QString		FileName;
	int32		Judgement;	//0:Undefined	1:OK	2:NG
	QString		JudgeStr;	//This is not saved. This is from Button text

	FileListLeaf(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FileListContainer : public NPListPack<FileListLeaf>
{
public:
	FileListContainer(void){}

	FileListLeaf	*Find(const QString &UFolderName,const QString &FileName);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif