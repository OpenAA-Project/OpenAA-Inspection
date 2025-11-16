#pragma once

#include "makeshading_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include<QString>
#include<QWidget>
#include<QColor>
#include<QFont>
#include<QPushButton>
#include "XFilterInstance.h"

class MakeShadingProcessForm;
class FlexArea;
class LayersBase;

struct MakeShadingInfoStruct
{
	int		Phase;
	double	FValue[3];
	int		MinX;	//MinXÅ`MaxXÇâÊëúÇ©ÇÁåvéZÇ∑ÇÈÇªÇÃîÕàÕäOÇÕíºãﬂì‡ë§Ç∆ìØÇ∂åvêîÇ…Ç∑ÇÈ
	int		MaxX;
};

class MakeShading : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	MakeShadingProcessForm	*Window;
public:
	QByteArray						*LineShadingData;
	struct MakeShadingInfoStruct	*MakeShadingInfoStructDimInPage;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	MakeShading(LayersBase *Base ,QWidget *parent);
	~MakeShading(void);
	
	virtual void	Prepare(void)		override;
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	void	PushAndClearFilter(void);
	void	PopFilter(void);
	void	RegistShading(int Page,FlexArea &ShadingArea ,double FValue[3]);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdMakeShadingPushAndClearFilter : public GUICmdPacketBase
{
public:
	GUICmdMakeShadingPushAndClearFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdMakeShadingPopFilter : public GUICmdPacketBase
{
public:
	GUICmdMakeShadingPopFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdMakeShadingRegist : public GUICmdPacketBase
{
public:
	FlexArea ShadingArea;
	double	FValue[3];
	int		MinX,MaxX;

	GUICmdMakeShadingRegist(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqMakeShadingInfo : public GUICmdPacketBase
{
public:
	int		Phase;

	GUICmdReqMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMakeShadingInfo : public GUICmdPacketBase
{
public:
	struct MakeShadingInfoStruct	MakeShadingInfoStructData;

	GUICmdAckMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdSetMakeShadingInfo : public GUICmdPacketBase
{
public:
	struct MakeShadingInfoStruct	MakeShadingInfoStructData;

	GUICmdSetMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
