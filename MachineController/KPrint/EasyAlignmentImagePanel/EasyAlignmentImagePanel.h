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

#ifndef EASYALIGNMENTIMAGEPANEL_H
#define EASYALIGNMENTIMAGEPANEL_H

#include "easyalignmentimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyPropertyAlignmentForm;

class	EasyAlignmentImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

	DWORD	LastTimeToMakeImage;
public:
	EasyAlignmentImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyAlignmentImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	SelectItem(int Phase
								,IntList &LayerList
								, FlexArea &Area 
								,SelectedItemsInfoContainer &RetSelectedContainer
								,QByteArray &SomethingData)	override;
	virtual	void	DelSelectedItemsInAlgorithm	(int SlaveNo
												,AlgorithmInPageRoot *APage 
												,IntList &LayerList
												,QByteArray &SomethingData)	override;
	virtual	void	DrawImage(QImage &Image ,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)	override;
	virtual	void	ExecuteMoveItems(const QString &AlgoDLLRoot ,const QString &AlgoDLLName ,int GlobalDx ,int GlobalDy)	override;

	virtual	void	MakeCopyToSlaveInfo(QByteArray &RetInfo)	override;
	virtual	bool	LoadCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot	*Ap,QByteArray &RetData)	override;
	virtual	bool	SaveCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot *Ap,TransformBase	*Param,bool ClearBeforeCopy)		override;

protected:
	virtual	void	CreateCallInfoInSelect	(QByteArray &RetData)	override;
	virtual	void	CreateCallInfoInDelete	(QByteArray &RetData)	override;
	virtual	void	CreateCallInfoInCut		(QByteArray &RetData)	override;

	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm	(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;
	virtual	void	CutItemInAlgorithm	(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &LocalArea ,QByteArray &SomethingData)	override;

private:
	EasyPropertyAlignmentForm	*GetEasyPropertyAlignment(void);

};

#endif // EASYALIGNMENTIMAGEPANEL_H