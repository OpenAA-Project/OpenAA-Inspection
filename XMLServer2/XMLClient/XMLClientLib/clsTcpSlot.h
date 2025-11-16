/*
 * clsTcpSlot.h
 *
 *  Created on: 2009/10/24
 *      Author: cony
 */

#ifndef CLSTCPSLOT_H_
#define CLSTCPSLOT_H_

#include <QThread>
class clsTcpSlot : public QThread {
	Q_OBJECT
public:
	clsTcpSlot(QObject *par);
	virtual ~clsTcpSlot();

	void run();

	bool bAbort;

public slots:
	void readyRead();
};

#endif /* CLSTCPSLOT_H_ */
