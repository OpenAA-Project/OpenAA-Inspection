#if	!defined(XPQSYSTEMRUNNER_H)
#define	XPQSYSTEMRUNNER_H

#include <QImage>
#include <QStringList>

#include "XPQSystemBaseService.h"
#include "XParamBase.h"

class	PQSystemRunner :public PQSystemBaseService ,public ParamBase
{
public:
	PQSystemRunner(PQSystemBase *Base);
	virtual	~PQSystemRunner(void);

	virtual	void	GetDLLImage(QImage &Img ,QString &Explains)	=0;

	virtual	void	GetParamFromWindow(void)	=0;
	virtual	void	SetParamToWindow(void)		=0;
	virtual	QDialog	*GetDialog(void)			=0;

	virtual	bool	CreateData(void)			=0;

	virtual	bool	WriteExcel(void)			=0;
	virtual	bool	PrintData(void)				=0;
	virtual	bool	ShowResult(void)			=0;	//Graph or list
};

#endif