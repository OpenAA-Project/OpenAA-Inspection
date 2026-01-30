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

#ifndef MTIMAGETOOLBUTTON_H
#define MTIMAGETOOLBUTTON_H

#include <QToolButton>
#include <QImage>

#include "mtImageButtonBase.h"

class mtImageToolButton : public QToolButton, public mtImageButtonBase
{
	Q_OBJECT

public:
	explicit	mtImageToolButton(QWidget *parent, bool checked = true);
	explicit	mtImageToolButton(const QImage &_img, QWidget *parent, bool checked = true);
	~mtImageToolButton();

	void setImageBmp(const QImage &_img);

	void Exec(void);
	void Cancel(void);

	void setChecked ( bool );
	bool isChecked ()	const;

protected:
	int nDrawX;
	int nDrawY;

	virtual void paintEvent(QPaintEvent *evt)			override;
	virtual void mousePressEvent(QMouseEvent *evt)		override;
	virtual void mouseMoveEvent(QMouseEvent *evt)		override;
	virtual void mouseReleaseEvent(QMouseEvent *evt)	override;
	virtual void closeEvent(QCloseEvent *evt)			override;
	virtual void showEvent ( QShowEvent * event )		override;

	void OnPressed(bool checked);

public slots:
	virtual	void SlotClicked(bool checked);
	void	click ();

private slots:
	void SlotReleased();

signals:
	void SignalClicked(bool checked=false);

private:
	bool	vChecked;
};

#endif // MTIMAGETOOLBUTTON_H