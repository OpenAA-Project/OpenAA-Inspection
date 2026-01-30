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

#ifndef DYNAMICCLASSIFYIMAGEPANEL_H
#define DYNAMICCLASSIFYIMAGEPANEL_H

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDynamicClassify.h"
#include "XDisplayImage.h"
#include "SelectAreaDialog.h"


class	DynamicClassifyImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	DynamicClassifyImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)override;
	virtual void	StartPage(void)	override;

	virtual	void	RequireHooks(GUIFormBase *mother)			override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	void	ButtonExecuteCopySelected(bool EnableDup)	override;

private slots:
};

class	GUICmdSetCopyAttr : public GUICmdPacketBase
{
public:
	SelectAreaMode	Mode;

	GUICmdSetCopyAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSetCopyAttr(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // DYNAMICCLASSIFYIMAGEPANEL_H