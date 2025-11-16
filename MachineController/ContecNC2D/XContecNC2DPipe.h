#if	!defined(ContecNC2DPipe_h)
#define	ContecNC2DPipe_h
#include <QLocalSocket>
#include <QLocalServer>


class	ContecNC2DPipe;
class	ContecNC2D;

class	ContecNC2DPipeInstance : public QObject
{
	Q_OBJECT

	ContecNC2DPipe	*Parent;
	QLocalSocket	*Socket;
public:
	ContecNC2DPipeInstance(ContecNC2DPipe *parent ,QLocalSocket *s);

private slots:
	void	SlotReadyRead();
};

class	ContecNC2DPipe : public QLocalServer
{
	Q_OBJECT

	ContecNC2D	*Parent;
public:
	ContecNC2DPipe ( ContecNC2D * parent = 0 );

	void	Start(void);

	void	ExeStart();
	void	ExeStep();
	bool	IsEnd();
	bool	IsStartButton();
private slots:
	void	SlotNewConnection ();

};
#endif