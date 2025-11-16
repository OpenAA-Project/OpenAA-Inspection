#if	!defined(XIOLogThread_H)
#define	XIOLogThread_H

#include <QThread>
#include "XDateTime.h"
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "XSequence.h"

class	RegList : public NPList<RegList>
{
public:
	Operand *Ope;
	bool	LastDataB;
	int		LastDataN;
	double	LastDataD;
	QString	LastDataS;
	bool	Changed;
	char	StrName[20];

	RegList(SeqControl *seq,const QString &RegStr);

	bool	GetAndCompare(void);
	void	MakeStr(char Buff[]);
	void	I2Str(char *s,int n);
	void	B2Str(char *s,bool n);
};

class ThreadIOLogger : public QThread
{
	Q_OBJECT

public:
	char		FileName[256];
	SeqControl	*Seq;
	NPListPack<RegList>	RegDatas;

	BYTE	LastInByte[100];
	BYTE	LastOutByte[100];
	int		PIOBoardNumber;
	int		IBitCount;
	int		OBitCount;
	QStringList		PushedMesssages;
	QMutex			MutexMessage;

	ThreadIOLogger(SeqControl *seq);

	void run();

	void	AddReg(const QString &RegStr);
	void	AddMessage(const QString &Str);
};

#endif