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



#ifndef EDITSEQUENCE_H
#define EDITSEQUENCE_H

#include <QMainWindow>
#include "ui_EditSequence.h"
#include "XServiceForLayers.h"

class	SeqControlParam;

class EditSequence : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

public:
	EditSequence(LayersBase *base,SeqControlParam *s ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditSequence();

private:
	Ui::EditSequenceClass ui;

private slots:
	void on_actionShow_triggered();
	void on_actionStart_triggered();
	virtual	void MessageOutFunc(int N);
};

#endif // EDITSEQUENCE_H