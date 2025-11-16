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
