#if	!defined(XImageExpand_h)
#define	XImageExpand_h

#include "NListComp.h"
#include <QIODevice>
#include "XTypeDef.h"

#pragma	pack(push,1)
struct	ShrinkingActionData
{
	struct MaskInfo{
		char	OffsetX;
		BYTE	MaskCount1;
		BYTE	MaskCount2;		//Continuously more than 1 bytes
		BYTE	MaskCount3;
		BYTE	AndMask1;
		BYTE	AndMask3;

		MaskInfo(void);
		~MaskInfo(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	}*Mask;
	unsigned short	MaskNumb;

	ShrinkingActionData(void);
	~ShrinkingActionData(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
#pragma	pack(pop)

class	ShrinkingPack : public NPListSaveLoad<ShrinkingPack>
{
public:
	int		Len;
	BYTE	BitNumb;
	struct	ShrinkingActionData	*MaskData;

	ShrinkingPack(void);
	~ShrinkingPack(void);
	void	Initial(int len);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ShrinkingPackContainer : public NPListPackSaveLoad<ShrinkingPack>
{
	ShrinkingPack	**Dim;
	int				DimNumb;
public:
	ShrinkingPackContainer(void);
	~ShrinkingPackContainer(void);

	void	Clear(void);
	virtual	ShrinkingPack	*Create(void);
	virtual	void	AppendListItem(ShrinkingPack *additem);

	bool	IsLoaded(int Numb);
	ShrinkingPack	*GetPack(int numb);

	bool    ThinAreaN(BYTE **bmpdata
					,BYTE **bitoperation
					,int xbyte ,int YLenDot 
					,int Numb
					,FlexArea *ForceZone=NULL
					,bool EnableThread=true);
	bool    FatAreaN(BYTE **bmpdata
					,BYTE **bitoperation
					,int xbyte ,int YLenDot 
					,int Numb
					,FlexArea *ForceZone=NULL
					,bool EnableThread=true);

	bool	SaveDefault(const QString &FileName=/**/"ShrinkingTable.dat");
	bool	LoadDefault(const QString &FileName=/**/"ShrinkingTable.dat");
};

//============================================================================

void    ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone=NULL
				,bool EnableThread=true);
void    FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone=NULL
				,bool EnableThread=true);

#endif