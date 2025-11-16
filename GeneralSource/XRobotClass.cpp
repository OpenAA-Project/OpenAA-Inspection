#include "XRobotClass.h"

RobotFigure::RobotFigure(void)
{
}
RobotFigure::RobotFigure(const RobotFigure &src)
{
	Position=src.Position	;
	Angle	=src.Angle		;
}

RobotFigure	&RobotFigure::operator=(const RobotFigure &src)
{
	Position=src.Position	;
	Angle	=src.Angle		;
	return *this;
}

bool	RobotFigure::Save(QIODevice *f)
{
	if(Position.Save(f)	==false)	return false;
	if(Angle.Save(f)	==false)	return false;
	return true;
}

bool	RobotFigure::Load(QIODevice *f)
{
	if(Position.Load(f)	==false)	return false;
	if(Angle.Load(f)	==false)	return false;
	return true;
}

