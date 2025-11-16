#ifndef RELAYLCUS2_H
#define RELAYLCUS2_H

#include "relaylcus2_global.h"
#include <QSerialPort>

class	RelayLCUS2
{
public:
	QSerialPort		*port;
	int	ComPort;

	RelayLCUS2()	{	port=NULL;	ComPort=3;	}

	void	Push(char *fp);

private:

};

#endif // RELAYLCUS2_H
