#if	!defined(ContecNC4DPipe_h)
#define	ContecNC4DPipe_h
#include <QLocalSocket>
#include <QLocalServer>


class	ContecNC4DPipe;
class	ContecNC4D;

class	ContecNC4DPipeInstance : public QObject
{
	Q_OBJECT

	ContecNC4DPipe	*Parent;
	QLocalSocket	*Socket;
public:
	ContecNC4DPipeInstance(ContecNC4DPipe *parent ,QLocalSocket *s);

private slots:
	void	SlotReadyRead();
};

class	ContecNC4DPipe : public QLocalServer
{
	Q_OBJECT

	ContecNC4D	*Parent;
public:
	ContecNC4DPipe ( ContecNC4D * parent = 0 );

	void	Start(void);
	void	ExeOrigin(void);
	void	ExeStartXY();
	void	ExeStepXY();
	bool	IsEndXY();
	void	ExeStartZ(int ZMicron);
	bool	IsEndZ();
	bool	IsStartButton();
	bool	IsAreaSensorON();

	void	SetLightGreen(bool b);
	void	SetBlink(bool b);
	void	GoMoveZ(int ZMicron);
	void	SetVacuum(bool b);
	void	SetLaserPointer(bool b);
	void	MoveVRS(int XPos,int YPos);

private slots:
	void	SlotNewConnection ();

};
#endif