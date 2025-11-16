#ifndef SHOWMEMORYFORM_H
#define SHOWMEMORYFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


namespace Ui {
class ShowMemoryForm;
}


struct	__ShowMemoryStruct
{
	unsigned long		dwLength;
	unsigned long		dwMemoryLoad;
	unsigned long long	ullTotalPhys;
	unsigned long long	ullAvailPhys;
	unsigned long long	ullTotalPageFile;
	unsigned long long	ullAvailPageFile;
	unsigned long long	ullTotalVirtual;
	unsigned long long	ullAvailVirtual;
	unsigned long long	ullAvailExtendedVirtual;
};

class ShowMemoryForm : public GUIFormBase
{
    Q_OBJECT
    QTimer	TM;
public:
	QFont	CFont;
	struct	__ShowMemoryStruct	ShowMemoryStruct;
	struct	__ShowMemoryStruct	*ShowMemoryStructInSlave;
	int		SlavePageNumb;

    explicit ShowMemoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowMemoryForm();
	virtual void	Prepare(void)	override;
private:
    Ui::ShowMemoryForm *ui;
	
private slots:
	void	SlotTimeout();
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqShowMemory : public GUICmdPacketBase
{
public:
	GUICmdReqShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckShowMemory : public GUICmdPacketBase
{
public:
	struct	__ShowMemoryStruct	ShowMemoryStruct;

	GUICmdAckShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//============================================================================================

bool	GetMemoryInfo(
	 unsigned long		&dwMemoryLoad
	,unsigned long long	&ullTotalPhys
	,unsigned long long	&ullAvailPhys
	,unsigned long long	&ullTotalPageFile
	,unsigned long long	&ullAvailPageFile
	,unsigned long long	&ullTotalVirtual
	,unsigned long long	&ullAvailVirtual
	,unsigned long long	&ullAvailExtendedVirtual
	);

#endif // SHOWMEMORYFORM_H
