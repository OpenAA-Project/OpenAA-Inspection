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
