/*
 * Copyright (C) 2024
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

#include "XTypeDef.h"
#include "XMultiLayerColor.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

MultiLayerColor::MultiLayerColor(void)
{
	LayerCount=0;
	Brightness=NULL;
}
MultiLayerColor::MultiLayerColor(LayersBase *Base)
{
	LayerCount=0;
	Brightness=NULL;
	Allocate(Base->GetMaxLayerNumb());
}
MultiLayerColor::MultiLayerColor(const MultiLayerColor &src)
{
	if(LayerCount!=src.LayerCount){
		Allocate(src.LayerCount);
	}
	for(int i=0;i<LayerCount;i++){
		Brightness[i]=src.Brightness[i];
	}
}

MultiLayerColor::~MultiLayerColor()
{
	if(Brightness!=NULL){
		delete	[]Brightness;
		Brightness=NULL;
	}
	LayerCount=0;
}

void	MultiLayerColor::Allocate(int LayerNumb)
{
	if(LayerCount!=LayerNumb){
		if(Brightness!=NULL){
			delete	[]Brightness;
		}
		LayerCount=LayerNumb;
		Brightness=new uint16[LayerCount];
	}
}
void	MultiLayerColor::Clear(int c)
{
	for(int i=0;i<LayerCount;i++){
		Brightness[i]=c;
	}
}
MultiLayerColor	&MultiLayerColor::operator=(const MultiLayerColor &src)
{
	if(LayerCount!=src.LayerCount){
		Allocate(src.LayerCount);
	}
	for(int i=0;i<LayerCount;i++){
		Brightness[i]=src.Brightness[i];
	}
	return *this;
}

bool	MultiLayerColor::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,LayerCount)==false){
		return false;
	}
	int	N=sizeof(Brightness[0])*LayerCount;
	if(f->write((const char *)Brightness,N)!=N){
		return false;
	}
	return true;
}
bool	MultiLayerColor::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	int32	tLayerCount;
	if(::Load(f,tLayerCount)==false){
		return false;
	}
	if(tLayerCount!=LayerCount){
		Allocate(tLayerCount);
	}
	int	N=sizeof(Brightness[0])*LayerCount;
	if(f->read((char *)Brightness,N)!=N){
		return false;
	}
	return true;
}