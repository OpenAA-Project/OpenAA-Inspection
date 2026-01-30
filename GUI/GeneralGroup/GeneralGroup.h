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

#ifndef GENERALPANEL_H
#define GENERALPANEL_H

#include "GeneralGroup_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"

class	GeneralGroup : public GUIFormBase
{
	Q_OBJECT

public:
	GeneralGroup(LayersBase *Base ,QWidget *parent);
	~GeneralGroup(void);

	virtual	void	Prepare(void)	override;

protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
	virtual	void	showEvent(QShowEvent *event)		override;
	virtual	void	paintEvent(QPaintEvent *event)		override;
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual	void	StartPage	(void)	override;

private slots:
	void buttonToggled(bool on);

private:
	void updateButtonText(void);

protected:
	virtual	bool eventFilter(QObject *obj, QEvent *event)	override;

public:
	QString m_text;
	bool m_initState;
	QString m_selfPassword;
	bool	m_passwordLock;

private:
	QPushButton *m_button;
	QRect m_expandGeometry;
};


#endif // GENERALPANEL_H