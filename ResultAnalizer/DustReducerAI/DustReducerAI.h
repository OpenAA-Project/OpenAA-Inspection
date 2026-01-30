/*
 * Copyright (C) 2024
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

#ifndef DUSTREDUCERAI_H
#define DUSTREDUCERAI_H

#include "dustreducerai_global.h"
#include "XResultAnalizer.h"
#include "XDustReducerAI.h"
#include "XGUIPacketForDLL.h"
#include "XIntClass.h"

class  DustReducerAI : public ResultAnalizerItemBase
{
public:
	DustRegContainer	RegLib;
	bool	ShouldAllocate;

	int32	XLen;
	int32	YLen;
	QString	RegPackFileName;
	double	MinMatchRate;
	IntList	AdaptedLayer;

	BYTE	*CurrentPattern[3];
	int		Page;


	DustReducerAI(LayersBase *Base);
	~DustReducerAI(void);

	void	Allocate(int page);
	virtual	bool	Save(QIODevice *f) override;
	virtual	bool	Load(QIODevice *f) override;
	bool	SaveLib(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	virtual	bool	ShowSettingDialogFunc(void) override;
	virtual	bool	ShowResultDialogFunc(QByteArray &Data)						override;
	virtual	bool	MakeDataForShow(ResultInItemRoot *Res ,QByteArray &RetData)	override;

	ExeResult	Execute(ResultInItemRoot *Res);

	void	Calc(void);
	void	AddToLib(const QString &Comment ,JudgeDust OkNg);
private:
	bool	IsDust(int Phase ,int Page ,int Layer ,int ItemID, int PosNo,int X,int Y,ImageBuffer &TBuff);
	void	MakePattern(int Phase,int Page,int X,int Y);
};

class	CmdShowResultDialog : public GUIDirectMessage
{
public:
	CmdShowResultDialog(LayersBase *base)	:GUIDirectMessage(base){}
};


#endif // DUSTREDUCERAI_H