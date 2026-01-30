/*
 * Copyright (C) 2020
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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