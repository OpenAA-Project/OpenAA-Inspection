#ifndef CONTECNC2DSEQ_H
#define CONTECNC2DSEQ_H

#include "contecnc2dseq_global.h"
#include "XContecNC2DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QWidget>

class	ContecNC2DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC2DController(QObject *parents);
	~ContecNC2DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	bool	WaitForRead(void);

	QString		RData;

private slots:
	void	SlotReadyRead();
};

#endif // CONTECNC2DSEQ_H
