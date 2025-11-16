#if	!defined(XDISPLAYIMAGEHOOK_H)
#define	XDISPLAYIMAGEHOOK_H

#include "NList.h"

class	GUIFormBase;
class	DisplayImageHooked;
class	DisplayImage;


class	FunctionServerClass
{
	class	DisplayImagePointerList : public NPList<DisplayImagePointerList>
	{
	public:
		GUIFormBase	*Pointer;

		DisplayImagePointerList(GUIFormBase *_Pointer){	Pointer=_Pointer;	}
	};
	NPListPack<DisplayImagePointerList>	PointerList;
public:
	FunctionServerClass(void){}
	virtual	~FunctionServerClass(void);

	void	SetHookedDisplayImage(GUIFormBase *t);
	void	DeleteTarget(GUIFormBase *f);
};

class	DisplayImageHooked
{
	GUIFormBase *DisplayImageInst;

protected:
	class	HookedFunctionBase
	{
	protected:
		FunctionServerClass *Obj;
	public:
		HookedFunctionBase(FunctionServerClass *obj):Obj(obj){}
		int	CompareBase(HookedFunctionBase &src);
	};

	class	HookedFunctionListPaintFirst : public HookedFunctionBase,public NPList<HookedFunctionListPaintFirst>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListPaintFirst(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,QPainter &pnt ,QImage &PntImage);
		virtual	int	Compare(HookedFunctionListPaintFirst &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListPaintLast : public HookedFunctionBase,public NPList<HookedFunctionListPaintLast>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListPaintLast(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,QPainter &pnt ,QImage &PntImage);
		virtual	int	Compare(HookedFunctionListPaintLast &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListMouseMove : public HookedFunctionBase,public NPList<HookedFunctionListMouseMove>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListMouseMove(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListMouseMove &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListLClick : public HookedFunctionBase,public NPList<HookedFunctionListLClick>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListLClick(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListLClick &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListLClickOnFree : public HookedFunctionBase,public NPList<HookedFunctionListLClickOnFree>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListLClickOnFree(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListLClickOnFree &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListLClickWithShift : public HookedFunctionBase,public NPList<HookedFunctionListLClickWithShift>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListLClickWithShift(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListLClickWithShift &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListLDoubleClick : public HookedFunctionBase,public NPList<HookedFunctionListLDoubleClick>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListLDoubleClick(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListLDoubleClick &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListRClick : public HookedFunctionBase,public NPList<HookedFunctionListRClick>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListRClick(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListRClick &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListRClickOnFree : public HookedFunctionBase,public NPList<HookedFunctionListRClickOnFree>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListRClickOnFree(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListRClickOnFree &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListRClickWithShift : public HookedFunctionBase,public NPList<HookedFunctionListRClickWithShift>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListRClickWithShift(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *,int GlobalPosX,int GlobalPosY);
		virtual	int	Compare(HookedFunctionListRClickWithShift &src)	override	{	return CompareBase(src);	}
	};
	class	HookedFunctionListDrawEnd : public HookedFunctionBase,public NPList<HookedFunctionListDrawEnd>
	{
		friend	class	DisplayImageHooked;
	public:
		HookedFunctionListDrawEnd(FunctionServerClass *obj);
		bool (*Function)(FunctionServerClass *Obj,GUIFormBase *);
		virtual	int	Compare(HookedFunctionListDrawEnd &src)	override	{	return CompareBase(src);	}
	};

	NPListPack<HookedFunctionListPaintFirst>		HookedFunctionListPaintFirstPack;
	NPListPack<HookedFunctionListPaintLast>			HookedFunctionListPaintLastPack;
	NPListPack<HookedFunctionListMouseMove>			HookedFunctionListMouseMovePack;
	NPListPack<HookedFunctionListLClick>			HookedFunctionListLClickPack;
	NPListPack<HookedFunctionListLClickOnFree>		HookedFunctionListLClickPackOnFree;
	NPListPack<HookedFunctionListLClickWithShift>	HookedFunctionListLClickWithShiftPack;
	NPListPack<HookedFunctionListLDoubleClick>		HookedFunctionListLDoubleClickPack;
	NPListPack<HookedFunctionListRClick>			HookedFunctionListRClickPack;
	NPListPack<HookedFunctionListRClickOnFree>		HookedFunctionListRClickPackOnFree;
	NPListPack<HookedFunctionListRClickWithShift>	HookedFunctionListRClickWithShiftPack;
	NPListPack<HookedFunctionListDrawEnd>			HookedFunctionListDrawEndPack;
	bool	HookResult;
public:
	DisplayImageHooked(GUIFormBase *_DisplayImageInst){	DisplayImageInst=_DisplayImageInst;	HookResult=true;	}
	~DisplayImageHooked(void);

	void	SetDisplayImageInst(DisplayImage *p);
	DisplayImage *GetDisplayImageInst(void)		;

	virtual	void	ReleaseHook(FunctionServerClass *f);

	virtual	void	SetHookInPaintFirst(FunctionServerClass *Obj			,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool HighestPriority=false);
	virtual	void	SetHookInPaintLast(FunctionServerClass *Obj				,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool HighestPriority=false);
	virtual	void	SetHookInMouseMove(FunctionServerClass *Obj				,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseLClick(FunctionServerClass *Obj			,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseLClickOnFree(FunctionServerClass *Obj		,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseLClickWithShift(FunctionServerClass *Obj	,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseLDoubleClick(FunctionServerClass *Obj		,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseRClick(FunctionServerClass *Obj			,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseRClickOnFree(FunctionServerClass *Obj		,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInMouseRClickWithShift(FunctionServerClass *Obj	,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY),bool HiggestPriority=false);
	virtual	void	SetHookInDrawEnd(FunctionServerClass *Obj				,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm),bool HighestPriority=false);

	virtual	void	RemoveHook(FunctionServerClass *Obj);
	bool	GetLastHookResult(void)	{	return HookResult;	}

	virtual	bool	HookedExecutePaintFirst		(QPainter &pnt ,QImage &PntImage);
	virtual	bool	HookedExecutePaintLast		(QPainter &pnt ,QImage &PntImage);
	virtual	bool	HookedExecuteMouseMove		(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteLClick			(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteLClickOnFree	(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteLClickWithShift(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteLDoubleClick	(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteRClick			(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteRClickOnFree	(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteRClickWithShift(int GlobalPosX,int GlobalPosY);
	virtual	bool	HookedExecuteDrawEnd(void);
};

inline	DisplayImageHooked::HookedFunctionListPaintFirst::HookedFunctionListPaintFirst(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListPaintLast::HookedFunctionListPaintLast(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListMouseMove::HookedFunctionListMouseMove(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListLClick::HookedFunctionListLClick(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListLClickOnFree::HookedFunctionListLClickOnFree(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListLClickWithShift::HookedFunctionListLClickWithShift(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListLDoubleClick::HookedFunctionListLDoubleClick(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListRClick::HookedFunctionListRClick(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListRClickOnFree::HookedFunctionListRClickOnFree(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListRClickWithShift::HookedFunctionListRClickWithShift(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

inline	DisplayImageHooked::HookedFunctionListDrawEnd::HookedFunctionListDrawEnd(FunctionServerClass *obj)
:HookedFunctionBase(obj),Function(NULL)
{}

#endif