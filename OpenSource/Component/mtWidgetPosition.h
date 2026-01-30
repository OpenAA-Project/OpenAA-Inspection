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


#ifndef MTWIDGETPOSITION_H
#define MTWIDGETPOSITION_H

#include <QWidget>

class	mtWidgetPosition : public QWidget
{
	Q_OBJECT
	Q_ENUMS(AlighmentOfWidget)
	Q_PROPERTY(AlighmentOfWidget AlignOfWidget READ GetAOW WRITE SetAOW)

public:
	enum	AlighmentOfWidget{
			_None
			,_Client
			,_Left
			,_Right
			,_Top
			,_Bottom
	};
private:
	AlighmentOfWidget	AOWData;

public:
	explicit	mtWidgetPosition(QWidget * parent = 0);

	AlighmentOfWidget	GetAOW(void)	const	{	return(AOWData);	}
	void				SetAOW(AlighmentOfWidget data);

protected:
	virtual void resizeEvent ( QResizeEvent * event )	override;
	void	SetWindowPos(void);
	virtual void enterEvent ( QEnterEvent * event )			override;
	virtual void leaveEvent ( QEvent * event )			override;
signals:
	void	SignalEnter();
	void	SignalLeave();
private slots:
	void	On_geometryChanged();
};

#endif