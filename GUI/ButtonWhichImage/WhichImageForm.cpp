#include "ButtonWhichImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonWhichImage\WhichImageForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "WhichImageForm.h"
#include "XDisplayImage.h"

WhichImageForm::WhichImageForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

WhichImageForm::~WhichImageForm()
{

}

void	WhichImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

void WhichImageForm::on_radioButtonMaster_toggled(bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->ChangeDisplayType(DisplayImage::__Master);
				m->Repaint();
			}
		}
	}
}

void WhichImageForm::on_radioButtonTarget_toggled(bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->ChangeDisplayType(DisplayImage::__Target);
				m->Repaint();
			}
		}
	}
}

void WhichImageForm::on_radioButtonDark_toggled(bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->Repaint();
			}
		}
	}
}

void WhichImageForm::on_radioButtonLight_toggled(bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->Repaint();
			}
		}
	}
}