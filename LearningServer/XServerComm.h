#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "XServerLayerBase.h"
#include "NList.h"

class	LearningServer;

class LearningServerSocket : public QObject
							,public NPList<LearningServerSocket>
							,public ServiceForLayers
{
	Q_OBJECT

	LearningServer	*Parent;
	QTcpSocket		*sv;
	int				Error;
public:
	LearningServerSocket(QTcpSocket *s ,LearningServer *obj);

	QTcpSocket	*GetSocket(void)	const{	return sv;	}
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};
