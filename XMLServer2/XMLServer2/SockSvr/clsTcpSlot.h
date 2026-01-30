/*
 * Copyright (C) 2012
 * Author : cony
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
	bool bEndFlg;

public slots:
	void readyRead();
	void endThread();

private:
	QObject *par;
};

#endif /* CLSTCPSLOT_H_ */