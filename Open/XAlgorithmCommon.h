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

#if	!defined(XAlgorithmCommon_h)
#define	XAlgorithmCommon_h

#include <QByteArrayList>
#include "XGUIPacketForDLL.h"

class AlgorithmBase;

enum ReflectionMode
{
	_Reflection_Mask				=0x0001
	,_Reflection_MaskOnlyInLimitMask=0x0101
	,_Reflection_Variety			=0x0002
};


class	CmdReqAlignmentArea : public GUIDirectMessage
{
public:
	FlexArea	Area;

	explicit	CmdReqAlignmentArea(LayersBase *base):GUIDirectMessage(base){}
	explicit	CmdReqAlignmentArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

struct	OriginTypeSelection
{
	bool	_FromUnknown	:1;
	bool	_FromLibrary	:1;
	bool	_FromManual		:1;
	bool	_FromParts		:1;
	bool	_FromMPA		:1;
	bool	_FromCAD		:1;
	AlgorithmBase	*Origin;

	explicit	OriginTypeSelection(AlgorithmBase *ABase)
	:Origin(ABase){
		_FromUnknown	=false;
		_FromLibrary	=false;
		_FromManual		=false;
		_FromParts		=false;
		_FromMPA		=false;
		_FromCAD		=false;
	}
};
	
//============================================================================
#define	ExecuteInitialAfterEdit_ChangedMask			0x0001
#define	ExecuteInitialAfterEdit_ChangedAlignment	0x0002
#define	ExecuteInitialAfterEdit_ChangedAlgorithm	0x0080

class ExecuteInitialAfterEditInfo
{
public:
	DWORD	ExecuteInitialAfterEdit_Changed;
	bool	CalledInLoadMaster;
	bool	CalledInFirst;
	bool	HasChangedOnlyImage;
	QByteArrayList	Something;
	FlexArea	*ApplicableArea;

	ExecuteInitialAfterEditInfo(void);
	ExecuteInitialAfterEditInfo(const ExecuteInitialAfterEditInfo &src);

	ExecuteInitialAfterEditInfo	&operator=(const ExecuteInitialAfterEditInfo &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif