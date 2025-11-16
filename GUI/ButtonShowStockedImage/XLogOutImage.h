#if	!defined(XLogOutImage_h)
#define	XLogOutImage_h

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"

class	CmdPushImage : public GUIDirectMessage
{
public:
	int		Phase;
	int		Page;
	int		Layer;
	bool	Mastered;

	CmdPushImage(LayersBase *base):GUIDirectMessage(base)		{	Phase=-1;	Page=-1;	Layer=-1;	Mastered=false;	}
	CmdPushImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//==================================================================================================

inline	void	LogOutImageHPL	(LayersBase *Base ,int phase ,int page ,int layer ,bool Mastered=false)
{
	CmdPushImage	RCmd(Base);
	RCmd.Phase		=phase;
	RCmd.Page		=page;
	RCmd.Layer		=layer;
	RCmd.Mastered	=Mastered;

	GUIFormBase	*f=Base->FindByName(/**/"Button",/**/"ShowStockedImage",/**/"");
	if(f!=NULL){
		if(f->GetParamGlobal()->OutputLogMode==true){
			f->TransmitDirectly(&RCmd);
		}
	}
}
inline	void	LogOutImagePL	(LayersBase *Base ,int page ,int layer ,bool Mastered=false)
{
	CmdPushImage	RCmd(Base);
	RCmd.Page		=page;
	RCmd.Layer		=layer;
	RCmd.Mastered	=Mastered;

	GUIFormBase	*f=Base->FindByName(/**/"Button",/**/"ShowStockedImage",/**/"");
	if(f!=NULL){
		if(f->GetParamGlobal()->OutputLogMode==true){
			f->TransmitDirectly(&RCmd);
		}
	}
}
inline	void	LogOutImageHP	(LayersBase *Base ,int phase ,int page ,bool Mastered=false)
{
	CmdPushImage	RCmd(Base);
	RCmd.Phase		=phase;
	RCmd.Page		=page;
	RCmd.Mastered	=Mastered;

	GUIFormBase	*f=Base->FindByName(/**/"Button",/**/"ShowStockedImage",/**/"");
	if(f!=NULL){
		if(f->GetParamGlobal()->OutputLogMode==true){
			f->TransmitDirectly(&RCmd);
		}
	}
}
inline	void	LogOutImageH	(LayersBase *Base ,int phase ,bool Mastered=false)
{
	CmdPushImage	RCmd(Base);
	RCmd.Phase	=phase;

	GUIFormBase	*f=Base->FindByName(/**/"Button",/**/"ShowStockedImage",/**/"");
	if(f!=NULL){
		if(f->GetParamGlobal()->OutputLogMode==true){
			f->TransmitDirectly(&RCmd);
		}
	}
}

#endif