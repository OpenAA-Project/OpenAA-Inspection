#pragma once

#include <QLibrary>
#include "XAuthentication.h"
#include "XServiceForLayers.h"
#include <QDateTime>
#include "XIntClass.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XDLLManager.h"
#include "XHaspLib.h"
#include "XErrorCode.h"

class	HaspInterface : public NPList<HaspInterface> ,public DLLManager ,public ServiceForLayers
{
	QLibrary 	DllLib;
protected:
	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);

	HaspHandleContainer	*(*DLL_Initial)(LayersBase *base,const QString &Parameter);
	bool	(*DLL_Close)(HaspHandleContainer *handle);

	QString		HaspFileName;
	HaspHandleContainer		*Handle;
	QString		Copyright;

public:
	HaspInterface(LayersBase *base);
	virtual	~HaspInterface(void);

	virtual	bool	Initial(const QString &HaspDLLFileName ,const QString &Parameter 
					,int32 &ErrorCode);

	HaspHandleContainer		*GetHandle(void)	{	return Handle;	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

private:
	bool	LoadDLL(const QString &filename ,int32 &ErrorCode);
};

class	AuthenticationInside : public ServiceForLayers
{
	NPListPack<HaspInterface>	HaspContainer;

public:
	AuthenticationInside(LayersBase *base);
	virtual	~AuthenticationInside(void);

	bool	AddInitialHasp(const QString &HaspDLLFileName,const QString &Parameter=QString());
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

	bool	IsAuthenticationPassed(AuthenticationPaper &d
								  ,const QString &_CurrentVersion
								  ,QString &FailMessage
								  ,int &ErrorCode);
	bool	IsAuthenticationPassedByProgram( const QString &_AuthenticationName
											,const QString &_CurrentVersion
											,QString &FailMessage
											,int &ErrorCode);
private:

};
