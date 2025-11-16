#if	!defined(XLINEINBLOCK_H)
#define	XLINEINBLOCK_H

#include <QImage>
#include "XTypeDef.h"
#include <QColor>

class	BlockItem;
class	BlockBase;
class	ImageBuffer;
class	FlexArea;
class	BlockThreshold;
class	BlockInLayer;
class	BlockInLayerForItemBitImage;
class	AlgorithmItemPointerListContainerContainer;
class	ExecuteInitialAfterEditInfo;

class	LineInBlockBase
{
protected:
	BlockItem	*Parent;
	bool	Effective;	
public:
	LineInBlockBase(BlockItem *parent);
	virtual	~LineInBlockBase(void);

	virtual	void	ExecuteInitialAfterEdit(bool n, int N,int FollowLinelength,ExecuteInitialAfterEditInfo &EInfo)	=0;
	virtual	void	Release(void)					=0;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col)	=0;

	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy)=0;
	bool	IsEffective(void){		return Effective;	}
	void	SetEffective(bool b)	{	Effective=b;	}
	virtual	double	GetSelfCoef(void)	=0;
	virtual	bool	CheckOverlapArea(FlexArea &area)	=0;
	FlexArea		&GetParentArea(void);
	const	BlockThreshold	*GetThresholdR(void);
	BlockThreshold			*GetThresholdW(void);
	virtual	void	MoveTo(int offsetx ,int offsety)		=0;

protected:
	virtual	ImageBuffer		&GetMasterImage(void);
	virtual	ImageBuffer		&GetTargetImage(void);
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2);
	int				GetDotPerLine(void);
	int				GetMaxLines(void);
	double			GetVarLow(void);
	virtual	BlockBase	*GetParentBase(void);
	virtual	BlockInLayerForItemBitImage	*GetBlockInLayerForItemBitImage(void);
	virtual	bool	GetModeUseMasterImage(void);
	virtual	int	GetSpaceToOutline(void);
};

class	HLineInBlock : public LineInBlockBase
{
	int		HLineX1,HLineX2,HLineY;
	BYTE	*HDot;
	int		AddedS;
	int		AddedSS;

public:
	HLineInBlock(BlockItem *parent);
	~HLineInBlock(void);

	virtual	void	ExecuteInitialAfterEdit(bool LeftMode ,int N ,int FollowLinelength,ExecuteInitialAfterEditInfo &EInfo);
	virtual	void	Release(void);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col);
	HLineInBlock	&operator=(const HLineInBlock &src);
	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy);
	double	GetSelfCoef(void);
	virtual	bool	CheckOverlapArea(FlexArea &area);
	virtual	void	MoveTo(int offsetx ,int offsety);
protected:
	bool	ExecuteInitialAfterEditInner(bool Left ,int N ,int gW,int StartPos,ExecuteInitialAfterEditInfo &EInfo);
	double			GetVar(int Lx1,int Lx2 ,int Ly ,ImageBuffer &Buff);
};

class	VLineInBlock : public LineInBlockBase
{
	int		VLineX,VLineY1,VLineY2;
	BYTE	*VDot;
	int		AddedS;
	int		AddedSS;

public:
	VLineInBlock(BlockItem *parent);
	~VLineInBlock(void);

	virtual	void	ExecuteInitialAfterEdit(bool TopMode ,int N ,int FollowLinelength,ExecuteInitialAfterEditInfo &EInfo);
	
	virtual	void	Release(void);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col);
	VLineInBlock	&operator=(const VLineInBlock &src);
	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy);
	double	GetSelfCoef(void);
	virtual	bool	CheckOverlapArea(FlexArea &area);
	virtual	void	MoveTo(int offsetx ,int offsety);
protected:
	bool	ExecuteInitialAfterEditInner(bool Left ,int N ,int gH ,int StartPos,ExecuteInitialAfterEditInfo &EInfo);
	double			GetVar(int Lx,int Ly1 ,int Ly2 ,ImageBuffer &Buff);
};


//==================================================================

class	LineInBlockClusterBase
{
protected:
	BlockInLayer *ParentLayer;
	AlgorithmItemPointerListContainerContainer	*ParentPointer;
	int			LibID;
	bool		Effective;	
public:
	LineInBlockClusterBase(BlockInLayer *ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int LibID);
	virtual	~LineInBlockClusterBase(void);

	virtual	void	ExecuteInitialAfterEdit(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite,ExecuteInitialAfterEditInfo &EInfo)	=0;
	virtual	void	Release(void)					=0;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col)	=0;

	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy ,double &AvrCol)=0;
	bool	IsEffective(void){		return Effective;	}
	void	SetEffective(bool b)	{	Effective=b;	}
	virtual	double	GetSelfCoef(void)	=0;
	virtual	bool	CheckOverlapArea(FlexArea &area)	=0;
	FlexArea		&GetParentArea(void);
	virtual	void	MoveTo(int offsetx ,int offsety)		=0;

protected:
	virtual	ImageBuffer		&GetMasterImage(void);
	virtual	ImageBuffer		&GetTargetImage(void);
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2);
	int				GetDotPerLine(void);
	int				GetMaxLines(void);
	double			GetVarLow(void);
	virtual	BlockBase	*GetParentBase(void);
	virtual	BlockInLayerForItemBitImage	*GetBlockInLayerForItemBitImage(void);
};

class	HLineInBlockCluster : public LineInBlockClusterBase
{
	int		HLineX1,HLineX2,HLineY;
	BYTE	*HDot;
	int		AddedS;
	int		AddedSS;

public:
	HLineInBlockCluster(BlockInLayer *_ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int _LibID);
	~HLineInBlockCluster(void);

	virtual	void	ExecuteInitialAfterEdit(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite,ExecuteInitialAfterEditInfo &EInfo);
	virtual	void	Release(void);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col);
	HLineInBlockCluster	&operator=(const HLineInBlockCluster &src);
	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy,double &AvrCol);
	double	GetSelfCoef(void);
	virtual	bool	CheckOverlapArea(FlexArea &area);
	virtual	void	MoveTo(int offsetx ,int offsety);
protected:
	bool	ExecuteInitialAfterEditInner(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite,ExecuteInitialAfterEditInfo &EInfo);
	double			GetVar(int Lx1,int Lx2 ,int Ly ,ImageBuffer &Buff);
};

class	VLineInBlockCluster : public LineInBlockClusterBase
{
	int		VLineX,VLineY1,VLineY2;
	BYTE	*VDot;
	int		AddedS;
	int		AddedSS;

public:
	VLineInBlockCluster(BlockInLayer *_ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int _LibID);
	~VLineInBlockCluster(void);

	virtual	void	ExecuteInitialAfterEdit(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite,ExecuteInitialAfterEditInfo &EInfo);
	
	virtual	void	Release(void);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col);
	VLineInBlockCluster	&operator=(const VLineInBlockCluster &src);
	virtual	double	Match(ImageBuffer &IBuff ,int dx ,int dy,double &AvrCol);
	double	GetSelfCoef(void);
	virtual	bool	CheckOverlapArea(FlexArea &area);
	virtual	void	MoveTo(int offsetx ,int offsety);
protected:
	bool	ExecuteInitialAfterEditInner(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite,ExecuteInitialAfterEditInfo &EInfo);
	double			GetVar(int Lx,int Ly1 ,int Ly2 ,ImageBuffer &Buff);
};

#endif
