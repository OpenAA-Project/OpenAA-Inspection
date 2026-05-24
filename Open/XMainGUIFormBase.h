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

#pragma once

#include "NList.h"
#include <QString>
#include <QStringList>
#include <QIODevice>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include <QtGui>
#include <QVariant>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XMacroFunction.h"
#include "XGUIFormBase.h"
#include "XSingleExecuteBySocket.h"
#include "XDataComponent.h"
#include "XEntryPoint.h"
#include "XGUI.h"


class	MainGUIFormBase : public GUIFormBase
{
    Q_OBJECT

	friend	class	SocketForMainGUI;

	CheckSingleExecution	*Execution;
	QLocalServer			IdentificationServer;
	NPListPack<SocketForMainGUI>	IdentificationSocket;
	QSize					BaseSize;
	bool					ScaleFirst;	
	double					ScaleX;
	double					ScaleY;
	bool					ReEntrant;
public:
	bool	CloseCompletely;
	GUIInstancePack::_FormPosition	FormPosition;

	explicit	MainGUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent=NULL);

	virtual	void closeEvent ( QCloseEvent * event )	override;
	void	OutputPosition(void);
	virtual	void	ReflectAlignment(void)	override;

	void	SetSingleExecution(const QString &IdentifiedName);
	bool	CheckDoubleBoot(void);
	bool	RequirePrebootedSoftwareToTerminate(void);
	void	StartIdentificationServer(const QString &IdentificationName);
	virtual	void	GetGUIScale(double &XScale ,double &YScale)	override;
	virtual	void	SetGUIScale(double  XScale ,double  YScale)	override;

protected:
	virtual	void	moveEvent ( QMoveEvent * event )	override;
	virtual	void	resizeEvent ( QResizeEvent * event )override;
private:
	QString	GetPositionFileName(void);
signals:
	void	QuitFromMenu();
	void	QuitUnconditionally();
	void	SignalMoveWindow(int PosX ,int PosY);
	void	SignalCloseEvent();
private slots:
	void	SlotTerminateFromOther();
	void	SlotNewConnection ();
};

inline	void	MainGUIFormBase::SetGUIScale(double  XScale ,double  YScale)
{
	ScaleX=XScale;
	ScaleY=YScale;
}

