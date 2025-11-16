/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DynamicClassifyImagePanel\DynamicClassifyImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
