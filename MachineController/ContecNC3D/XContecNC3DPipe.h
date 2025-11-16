#if	!defined(ContecNC3DPipe_h)
#define	ContecNC3DPipe_h
#include <QLocalSocket>
#include <QLocalServer>


class	ContecNC3DPipe;
class	ContecNC3D;

class	ContecNC3DPipeInstance : public QObject
{
	Q_OBJECT

	ContecNC3DPipe	*Parent;
	QLocalSocket	*Socket;
public:
	ContecNC3DPipeInstance(ContecNC3DPipe *parent ,QLocalSocket *s);

private slots:
	void	SlotReadyRead();
};

class	ContecNC3DPipe : public QLocalServer
{
	Q_OBJECT

	ContecNC3D	*Parent;
public:
	ContecNC3DPipe ( ContecNC3D * parent = 0 );

	void	Start(void);
	void	ExeOrigin(void);
	void	ExeStartXY();
	void	ExeStepXY();
	bool	IsEndXY();
	void	ExeStartZ(int ZMicron);
	bool	IsEndZ();
	bool	IsStartButton();

	void	SetLightGreen(bool b);
	void	SetBlink(bool b);
	void	GoMoveZ(int ZMicron);
	void	SetVacuum(bool b);

private slots:
	void	SlotNewConnection ();

};
#endif