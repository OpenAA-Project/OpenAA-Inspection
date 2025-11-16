#pragma once

#include "NListComp.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class ListAutoGenerator : public NPListSaveLoad<ListAutoGenerator>
{
public:
	QString	Code			;
	QString	Name			;
	QString	DXFFileName		;
	QString	PDFFileName		;
	QString	AlignFileName	;
	QString	SpecialFileName	;

	ListAutoGenerator(void);
	ListAutoGenerator(const ListAutoGenerator &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	ListAutoGenerator	&operator=(const ListAutoGenerator &src);

};
class ListAutoGeneratorContainer : public NPListPackSaveLoad<ListAutoGenerator>
{
public:
	ListAutoGeneratorContainer(void);
	ListAutoGeneratorContainer(const ListAutoGeneratorContainer &src);

	virtual	ListAutoGenerator	*Create(void)	override;

	ListAutoGeneratorContainer	&operator=(const ListAutoGeneratorContainer &src);
};

//==================================================================================

class	IntegrationCmdExecuteAutoGenerator : public IntegrationCmdPacketBase
{
public:
	QByteArray	DXFData		;
	QByteArray	PDFData		;
	QByteArray	AlignData	;
	QByteArray	SpecialData	;

	IntegrationCmdExecuteAutoGenerator(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};
