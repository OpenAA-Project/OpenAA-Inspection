#if	!defined(XMaskingLibrary_h)
#define	XMaskingLibrary_h

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeMasking		24

class	AlgorithmItemPLI;

class MaskingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	enum	MaskingLibOperation
	{
		 _Masking_Effective				=0
		,_Masking_Ineffective			=1
		,_Masking_LimitedEffective		=2
		,_Masking_LimitedIneffective	=3
	};
	MaskingLibOperation				Operation;				
	AlgorithmLibraryListContainer	LimitedLibraries;

	MaskingLibrary(int LibType,LayersBase *Base);
	virtual	~MaskingLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MaskingLibrary	&operator=(const AlgorithmLibrary &src)	override;
	void	MakeAreaOnly(BYTE **TmpData,int page,int XByte ,int YLen,NPListPack<AlgorithmItemPLI> &ItemList);
};

class	MaskingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MaskingLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~MaskingLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeMasking;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Masking Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MaskingLibrary(GetLibType(),GetLayersBase());	}
};



#endif