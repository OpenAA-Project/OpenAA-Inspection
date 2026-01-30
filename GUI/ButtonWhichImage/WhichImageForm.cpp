/*
 * Copyright (C) 2023
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

#include "ButtonWhichImageResource.h"

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