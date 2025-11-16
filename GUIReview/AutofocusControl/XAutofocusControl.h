#if	!defined(XAUTOFOCUSCONTROL_H)
#define	XAUTOFOCUSCONTROL_H

#include "XGUIPacketForDLL.h"

class	QextSerialPort;

class	AFControl
{
public:
	int				CommPort;
	QextSerialPort    *sio;

	AFControl(void);

	bool	OpenPort(int port);
	bool	ClosePort(void);
	bool	IsOpened(void);

	bool	GoAutofocus(void);
	int		GetCurrentZ(void);
	bool	ChangeNumber(char number);

private:
	int		GetChar(void);
	void	SendChar(unsigned char d);

	bool	SendStr(char *s);
	bool	GetStr(char buff[] ,int maxlen);
};

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

class	CmdSetLensRange : public GUIDirectMessage
{
public:
	int		Number;

	CmdSetLensRange(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqLensRange : public GUIDirectMessage
{
public:
	int		Number;
	int		ZoomRate;

	CmdReqLensRange(LayersBase *base)
		:GUIDirectMessage(base){	Number=1;	}
};

class	CmdMovePosition : public GUIDirectMessage
{
public:
	CmdMovePosition(LayersBase *base)
		:GUIDirectMessage(base){}
};


#endif