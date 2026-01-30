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

#include "robotfairinodll_global.h"
#include "XRobotClass.h"
#include <QTimer>
#include <QString>

class FRRobot;

class RobotFairInoDLL : public RobotDLLBaseClass
{
public:
	FRRobot *robot;

	QString	IPAddress;
    float	velPercentage        ;
    float	accPercentage        ;
    float	max_disPercentage    ;

    RobotFairInoDLL(QWidget *parent ,LayersBase *base);

	virtual	bool	Initial(void)	override;
	virtual	bool	Close(void)		override;

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
	virtual	bool	ShowSettingDialog(void)	override;

	virtual	bool	MotionMove(RobotFigure &target ,float Speed)	override;
	virtual	bool	MotionMove(RobotFigure target[],int PointCount ,float Speed)	override;
	virtual	bool	GetFigure(RobotFigure &CurrentFigure)			override;
	virtual	bool	GetButtonState(bool Buttons[])					override;
	virtual	bool	SetDragMode(bool EnableDrag)					override;

	virtual	bool	TrajectoryStart(const QString &FileName)		override;
	virtual	bool	TrajectoryEnd(void)								override;
	virtual	bool	StartTrajectory(const QString &FileName)		override;

};