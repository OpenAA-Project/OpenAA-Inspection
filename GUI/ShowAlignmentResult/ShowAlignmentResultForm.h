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

#ifndef SHOWALIGNMENTRESULTFORM_H
#define SHOWALIGNMENTRESULTFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class ShowAlignmentResultForm;
}
class	SignalOperandInt;
class	SignalOperandBit;

class	GUICmdReqAlignmentResult;
class	GUICmdAckAlignmentResult;

class ShowAlignmentResultForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	*iRegDx;
	SignalOperandInt	*iRegDy;
	SignalOperandInt	*iRegTheta;

	int			AlignmentPage;
	int			AlignmentLocalPx;
	int			AlignmentLocalPy;

	int	AllocatedPageNumb;
	GUICmdReqAlignmentResult	**ResultCmd;
	GUICmdAckAlignmentResult	**ResultACmd;

public:
	int			RegDxNo;
	int			RegDyNo;
	int			RegThetaNo;

    explicit ShowAlignmentResultForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowAlignmentResultForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:


private:
    Ui::ShowAlignmentResultForm *ui;
};

//=============================================================================================
class	GUICmdReqAlignmentResult : public GUICmdPacketBase
{
public:
	int			AlignmentLocalPx;
	int			AlignmentLocalPy;

	GUICmdReqAlignmentResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqAlignmentResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentResult : public GUICmdPacketBase
{
public:
	int	ResultDx;
	int	ResultDy;
	double	ResultTheta;

	GUICmdAckAlignmentResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckAlignmentResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//=============================================================================================
class	GUICmdReqAllAlignmentArea : public GUICmdPacketBase
{
public:

	GUICmdReqAllAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqAllAlignmentArea(void);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAllAlignmentArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdAckAllAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckAllAlignmentArea(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // SHOWALIGNMENTRESULTFORM_H