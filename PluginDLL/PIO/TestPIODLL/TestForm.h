/*
 * Copyright (C) 2018
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

#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QTimer>
#include <QCheckBox>
#include <QToolButton>
#include <QMutex>
#include "XTypeDef.h"
#include "XIODLL.h"

namespace Ui {
    class TestForm;
}

class TestForm : public QWidget,public PIODLLBaseClass
{
    Q_OBJECT

	QTimer	TM;
	int		BitCountIn;
	int		BitCountOut;

	QCheckBox	*OutputBit[128];
	QCheckBox	*InputBit[128];
	QToolButton	*InputEnabled[128];
	bool		InputEnabledMode[128];

	volatile	BYTE		InputedData[128];


	DWORD		LastAccessTime;
public:
	short	BoardID;

public:
    explicit TestForm(short	_BoardID ,QWidget *parent = 0);
    ~TestForm();

	static	QMutex		IOAccess;

	BYTE	GetBufferedInBit(BYTE bitIndex);
	BYTE	GetBufferedInByte(BYTE byteIndex);

	BYTE	PIOGetBit(BYTE bitIndex);
	BYTE	PIOGetByte(BYTE byteIndex);

private slots:
	void	on_toolButtonInputEnabled_clicked();
	void	on_checkBoxInput_clicked();
	
	void	SlotTimeout ();

private:
    Ui::TestForm *ui;

	void	SetupForm(void);
};

#endif // TESTFORM_H