#ifndef CONTECNC4DSEQ_H
#define CONTECNC4DSEQ_H

#include "contecnc4dseq_global.h"
#include "XContecNC4DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>

class	ContecNC4DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC4DController(QObject *parents);
	~ContecNC4DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	void	SendCommand(const QString &Str ,int data);
	void	SendCommand(const QString &Str ,int data1,int data2);
	bool	WaitForRead(int WTm=100);

	QString		RData;

private slots:
	void	SlotReadyRead();
};


#endif // CONTECNC4DSEQ_H
