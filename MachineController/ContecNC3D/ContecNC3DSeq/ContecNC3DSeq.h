#ifndef CONTECNC3DSEQ_H
#define CONTECNC3DSEQ_H

#include "contecnc3dseq_global.h"
#include "XContecNC3DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>

class	ContecNC3DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC3DController(QObject *parents);
	~ContecNC3DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	void	SendCommand(const QString &Str ,int data);
	bool	WaitForRead(int WTm=100);

	QString		RData;

private slots:
	void	SlotReadyRead();
};

#endif // CONTECNC3DSEQ_H
