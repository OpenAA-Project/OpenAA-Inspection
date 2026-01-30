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

#ifndef SHOWSIZEPANELSEQFORM_H
#define SHOWSIZEPANELSEQFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;


namespace Ui {
class ShowSizePanelSeqForm;
}

class ShowSizePanelSeqForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	*iRegLengthSize;		//Unit:um
	SignalOperandInt	*iRegWidthSize;		
	SignalOperandInt	*iRegHeightSize;
public:
	int32		LimitMaxLength;				//Unit:um
	int32		LimitMaxWidth;
	int32		LimitMaxHeight;
	int32		SizeLength;					//Unit:um
	int32		SizeWidth;
	int32		SizeHeight;
	int32		SysRegisterNoLength;
	int32		SysRegisterNoWidth;
	int32		SysRegisterNoHeight;
	
	explicit ShowSizePanelSeqForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowSizePanelSeqForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
    void on_pushButtonChange_clicked();

private:
    Ui::ShowSizePanelSeqForm *ui;
};

#endif // SHOWSIZEPANELSEQFORM_H