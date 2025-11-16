#ifndef SETOUTLINEOFFSET_H
#define SETOUTLINEOFFSET_H

#include "setoutlineoffset_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XOutlineOffset.h"

class	SetOutlineOffset : public GUIFormBase
{
	Q_OBJECT

public:

	SetOutlineOffset(LayersBase *Base ,QWidget *parent);
	~SetOutlineOffset(void);

	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:

};

class	CmdReqOutlineOffset : public GUIDirectMessage
{
public:
	OutlineOffsetInBlob	Data;
	int					MasterCode;
	bool				Result;

	CmdReqOutlineOffset(LayersBase *base):GUIDirectMessage(base),Data(base)							{	Result=false;	}
	CmdReqOutlineOffset(GUICmdPacketBase *base):GUIDirectMessage(base),Data(base->GetLayersBase())	{	Result=false;	}
};

#endif // SETOUTLINEOFFSET_H
