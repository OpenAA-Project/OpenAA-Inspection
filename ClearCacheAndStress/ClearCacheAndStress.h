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

#ifndef CLEARCACHEANDSTRESS_H
#define CLEARCACHEANDSTRESS_H

#include <QMainWindow>
#include "ui_ClearCacheAndStress.h"
#include<QThread>
#include "NList.h"
#include "XTypeDef.h"
#include<QTimer>

class	ThreadStress;
class	ThreadDiskStress;

class ClearCacheAndStress : public QMainWindow
{
	Q_OBJECT

	QTimer	TM;
	ThreadStress		*ThreadStressData;
	ThreadDiskStress	*ThreadDiskStressData;
public:
	ClearCacheAndStress(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ClearCacheAndStress();


private:
	Ui::ClearCacheAndStressClass ui;

private slots:
	void SlotTimeOut ();
};

class	MemoryLeaf : public NPList<MemoryLeaf>
{
	int		D;
	int		ID;
	BYTE	*Pointer;
	int		Len;
	int		AccessMode;
public:
	MemoryLeaf(int id,int len);
	~MemoryLeaf(void);

	void	Access(void);
};

class	ThreadStress : public QThread
{
	NPListPack<MemoryLeaf>	MemoryPack;

public:
	ThreadStress(QObject *parent);

	volatile	bool	FinishMode;
	virtual	void	run();
};


class	DiskLeaf : public NPList<DiskLeaf>
{
	int		D;
	int		ID;
	BYTE	*Pointer;
	int		Len;
	int		AccessMode;
public:
	DiskLeaf(int id,int len);
	~DiskLeaf(void);

	void	Access(void);
};

class	ThreadDiskStress : public QThread
{
	NPListPack<DiskLeaf>	DiskPack;

public:
	ThreadDiskStress(QObject *parent);

	volatile	bool	FinishMode;
	virtual	void	run();
};

#endif // CLEARCACHEANDSTRESS_H