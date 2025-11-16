#if	!defined(XPrinterDLL_H)
#define	XPrinterDLL_H


#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	PrinterDLLBaseClass;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for PrinterDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Printer DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);


DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string
DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	PrinterDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &PrinterParamStr);
//	Initialize Printer DLL. 
//		This function must create and open handle. 
//	return:		Printer handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	void		_cdecl	DLL_SetLayersBasePointer(PrinterDLLBaseClass *handle ,LayersBase *base);
//	Set LayersBase pointer into PrinterDLL


DEFFUNCEX	bool		_cdecl	DLL_Close(PrinterDLLBaseClass *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(PrinterDLLBaseClass *handle ,QIODevice &str);
//	Load Printer attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Printer attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(PrinterDLLBaseClass *handle ,QIODevice &str);
//	Save Printer attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(PrinterDLLBaseClass *handle, QWidget *parent);
//	This function shows dialog to set Printer(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Printering pattern(Which Printer is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false

};


#endif