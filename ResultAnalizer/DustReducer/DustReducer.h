#ifndef DUSTREDUCER_H
#define DUSTREDUCER_H

#include "dustreducer_global.h"
#include "XResultAnalizer.h"

class	ImageBuffer;

struct	DustReducerResult
{
	int	Phase;
	int	Page;
	int	Layer;
	int	ItemID;
	int	PosNo;
	int	Dots;
	int	Length;
	double	S;
	bool	Dust;
};

class  DustReducer : public ResultAnalizerItemBase
{
	BYTE	**NGMap;
	int		XLen;
	int		XByte;
	int		YLen;
public:
	struct	DustReducerResult	*Dim;
	int		AllocatedCount;
	int		WPoint;
public:
	int		VLayer;
	int		BrightnessL;
	int		BrightnessH;
	int		MaxAreaDots;
	int		MaxLength;
	double	MaxV;

	explicit	DustReducer(LayersBase *Base);
	~DustReducer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	ShowSettingDialogFunc(void) override;

	void		Allocate(void);

	void		ExecuteStartByInspection(void);
	ExeResult	Execute(ResultInItemRoot *Res);
private:
	bool	IsDust(int Phase ,int Page ,int Layer ,int ItemID, int PosNo,int X,int Y,ImageBuffer &TBuff);
};

#endif // DUSTREDUCER_H
