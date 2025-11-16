#ifndef DUSTREDUCERAI_H
#define DUSTREDUCERAI_H

#include "dustreducerai_global.h"
#include "XResultAnalizer.h"
#include "XDustReducerAI.h"
#include "XGUIPacketForDLL.h"
#include "XIntClass.h"

class  DustReducerAI : public ResultAnalizerItemBase
{
public:
	DustRegContainer	RegLib;
	bool	ShouldAllocate;

	int32	XLen;
	int32	YLen;
	QString	RegPackFileName;
	double	MinMatchRate;
	IntList	AdaptedLayer;

	BYTE	*CurrentPattern[3];
	int		Page;


	DustReducerAI(LayersBase *Base);
	~DustReducerAI(void);

	void	Allocate(int page);
	virtual	bool	Save(QIODevice *f) override;
	virtual	bool	Load(QIODevice *f) override;
	bool	SaveLib(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	virtual	bool	ShowSettingDialogFunc(void) override;
	virtual	bool	ShowResultDialogFunc(QByteArray &Data)						override;
	virtual	bool	MakeDataForShow(ResultInItemRoot *Res ,QByteArray &RetData)	override;

	ExeResult	Execute(ResultInItemRoot *Res);

	void	Calc(void);
	void	AddToLib(const QString &Comment ,JudgeDust OkNg);
private:
	bool	IsDust(int Phase ,int Page ,int Layer ,int ItemID, int PosNo,int X,int Y,ImageBuffer &TBuff);
	void	MakePattern(int Phase,int Page,int X,int Y);
};

class	CmdShowResultDialog : public GUIDirectMessage
{
public:
	CmdShowResultDialog(LayersBase *base)	:GUIDirectMessage(base){}
};


#endif // DUSTREDUCERAI_H
