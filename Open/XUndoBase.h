#if	!defined(XUNDOBASE_H)
#define	XUNDOBASE_H

#include "XTypeDef.h"
#include "NList.h"
#include "XServiceForLayers.h"
#include <QIODevice>
#include <QBuffer>
#include"XQuickBuffer.h"

class	AlgorithmParentFromItem;
class	AlgorithmItemRoot;
class	AlgorithmInLayerRoot;
class	AlgorithmInPageRoot;
class	DataInLayer;
class	DataInPage;
class	UndoTopic;
class	GUIFormBase;


class	UndoChainObject : public NPList<UndoChainObject> ,public ServiceForLayers
{
	friend	class	UndoTopic;

	QuickBuffer		Buff;
public:
	explicit	UndoChainObject(LayersBase *base);
	virtual ~UndoChainObject(void){}

	virtual	bool UndoExecute(QIODevice *f){	return true;	}
	virtual	bool RedoExecute(QIODevice *f){	return true;	}
	QIODevice	*GetWritePointer(void)	{	return &Buff;	}
};

//--------------------------------------------------------------------------------
class UndoAlgorithmItemRoot : public UndoChainObject
{
private:
    typedef void (AlgorithmItemRoot::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
	AlgorithmParentFromItem	*Parent;
	int32					ItemID;
	int32					ItemClassType;
	FPFUNC					m_Undofunc;

public:
    explicit	UndoAlgorithmItemRoot(AlgorithmItemRoot *Item,AlgorithmParentFromItem *parent ,FPFUNC fpfunc);

	virtual	bool UndoExecute(QIODevice *f)	override;
};

//--------------------------------------------------------------------------------
class UndoAlgorithmLayer : public UndoChainObject
{
private:
    typedef void (AlgorithmInLayerRoot::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
	AlgorithmInLayerRoot	*ThisInst;
	FPFUNC					m_Undofunc;

public:
    explicit	UndoAlgorithmLayer(AlgorithmInLayerRoot *_ThisInst ,FPFUNC fpfunc);

	virtual	bool UndoExecute(QIODevice *f)	override;
};

//--------------------------------------------------------------------------------
class UndoAlgorithmPage : public UndoChainObject
{
private:
    typedef void (AlgorithmInPageRoot::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
	AlgorithmInPageRoot	*ThisInst;
	FPFUNC					m_Undofunc;

public:
    explicit	UndoAlgorithmPage(AlgorithmInPageRoot *_ThisInst ,FPFUNC fpfunc);

	virtual	bool UndoExecute(QIODevice *f)	override;
};
//--------------------------------------------------------------------------------
class UndoDataInLayer : public UndoChainObject
{
private:
    typedef void (DataInLayer::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
	DataInLayer				*ThisInst;
	FPFUNC					m_Undofunc;

public:
	explicit	 UndoDataInLayer(DataInLayer *_ThisInst ,FPFUNC fpfunc);

	virtual	bool UndoExecute(QIODevice *f)	override;
};

//--------------------------------------------------------------------------------
class UndoDataInPage : public UndoChainObject
{
private:
    typedef void (DataInPage::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
	DataInPage				*ThisInst;
	FPFUNC					m_Undofunc;

public:
    explicit	UndoDataInPage(DataInPage *_ThisInst ,FPFUNC fpfunc);

	virtual	bool UndoExecute(QIODevice *f)	override;
};

//--------------------------------------------------------------------------------

template <typename t_Undo>
class UndoElement : public UndoChainObject
{
private:
    typedef void (t_Undo::*FPFUNC)(QIODevice *f);  // èàóùä÷êîÇÃå^

private:
    t_Undo* m_pHandleParent;         // ëÄçÏëŒè€
	FPFUNC	m_Undofunc;
	FPFUNC	m_Redofunc;
public:
    explicit	UndoElement(t_Undo* rHandleParent ,FPFUNC fpUndoFunc ,FPFUNC fpRedoFunc)
        : UndoChainObject(rHandleParent->GetLayersBase()),m_pHandleParent(rHandleParent),m_Undofunc(fpUndoFunc),m_Redofunc(fpRedoFunc){}
    explicit	UndoElement(t_Undo* rHandleParent ,FPFUNC fpUndoFunc)
        : UndoChainObject(rHandleParent->GetLayersBase()),m_pHandleParent(rHandleParent),m_Undofunc(fpUndoFunc),m_Redofunc(NULL){}

public:
	virtual	bool UndoExecute(QIODevice *f)	override
	{
		if(m_pHandleParent!=NULL){
		    (m_pHandleParent->*m_Undofunc)(f);
			return true;
		}
		return false;
	}
	virtual	bool RedoExecute(QIODevice *f)	override
	{
		if(m_pHandleParent!=NULL){
		    (m_pHandleParent->*m_Redofunc)(f);
			return true;
		}
		return false;
	}
};


#endif