#ifndef SEQRELAYLCUS2_H
#define SEQRELAYLCUS2_H

#include "seqrelaylcus2_global.h"

class	QextSerialPort;

class	SeqRelayLCUS2
{
public:
	QextSerialPort	*port;
	int	ComPort;

	SeqRelayLCUS2()	{	port=NULL;	ComPort=3;	}

	void	Push(char *fp);

private:

};
#endif // SEQRELAYLCUS2_H
