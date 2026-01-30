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

#ifndef COMPRESSIMAGEINDICATORFORM_H
#define COMPRESSIMAGEINDICATORFORM_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class CompressImageIndicatorForm;
}

class CompressImageIndicatorForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit CompressImageIndicatorForm(LayersBase *Base ,QWidget *parent = 0);
    ~CompressImageIndicatorForm();

	virtual	bool OnIdle(void)	override;
private:
    Ui::CompressImageIndicatorForm *ui;
};
//-----------------------------------------------------------------------------------------------------------

class	GUICmdReqCountOfCompressImage : public GUICmdPacketBase
{
public:
	GUICmdReqCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCountOfCompressImage : public GUICmdPacketBase
{
public:
	int32	Count;

	GUICmdSendCountOfCompressImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // COMPRESSIMAGEINDICATORFORM_H