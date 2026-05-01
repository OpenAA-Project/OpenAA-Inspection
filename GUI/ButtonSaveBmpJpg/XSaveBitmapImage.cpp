/*
 * Copyright (C) 2019
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

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <QIODevice>
#include "XMainSchemeMemory.h"

bool	SaveBitmapImage(QIODevice *f ,ImageBuffer *Buff[] ,int LayerNumb)
{
	BITMAPFILEHEADER	Header;
	BITMAPINFOHEADER	Info;

	if(f->read((char *)&Header,sizeof(Header))!=sizeof(Header))
		return false;
	if(f->read((char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;

	int		N=Header.bfOffBits - sizeof(Header) - sizeof(Info);
	for(int i=0;i<N;i++){
		char	Dummy;
		if(f->read((char *)&Dummy,1)!=1)
			return false;
	}
	int	W=Info.biWidth;
	int	H=Info.biHeight;
	if(Info.biBitCount==32 && Info.biCompression==0){
		RGBQUAD	*ColBuff =new RGBQUAD[W];
		for(int L=0;L<H;L++){
			if(f->read((char *)ColBuff,sizeof(RGBQUAD)*W)!=sizeof(RGBQUAD)*W){
				delete	[]ColBuff;
				return false;
			}
			if(LayerNumb==1 && Buff[0]->GetHeight()>L){
				BYTE	*d=Buff[0]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d[x]=ColBuff[x].rgbRed;
				}
			}
			else if(LayerNumb==2 && Buff[0]->GetHeight()>L){
				BYTE	*d0=Buff[0]->GetY(L);
				BYTE	*d1=Buff[1]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d0[x]=ColBuff[x].rgbRed;
					d1[x]=ColBuff[x].rgbGreen;
				}
			}
			else if(LayerNumb>=3 && Buff[0]->GetHeight()>L){
				BYTE	*d0=Buff[0]->GetY(L);
				BYTE	*d1=Buff[1]->GetY(L);
				BYTE	*d2=Buff[2]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d0[x]=ColBuff[x].rgbRed;
					d1[x]=ColBuff[x].rgbGreen;
					d2[x]=ColBuff[x].rgbBlue;
				}
			}
		}
		delete	[]ColBuff;
	}
	if(Info.biBitCount==24 && Info.biCompression==0){
		RGBTRIPLE	*ColBuff =new RGBTRIPLE[W];
		for(int L=0;L<H;L++){
			if(f->read((char *)ColBuff,sizeof(RGBTRIPLE)*W)!=sizeof(RGBTRIPLE)*W){
				delete	[]ColBuff;
				return false;
			}
			if(LayerNumb==1 && Buff[0]->GetHeight()>L){
				BYTE	*d=Buff[0]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d[x]=ColBuff[x].rgbtRed;
				}
			}
			else if(LayerNumb==2 && Buff[0]->GetHeight()>L){
				BYTE	*d0=Buff[0]->GetY(L);
				BYTE	*d1=Buff[1]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d0[x]=ColBuff[x].rgbtRed;
					d1[x]=ColBuff[x].rgbtGreen;
				}
			}
			else if(LayerNumb>=3 && Buff[0]->GetHeight()>L){
				BYTE	*d0=Buff[0]->GetY(L);
				BYTE	*d1=Buff[1]->GetY(L);
				BYTE	*d2=Buff[2]->GetY(L);
				for(int x=0;x<Buff[0]->GetWidth() && x<W;x++){
					d0[x]=ColBuff[x].rgbtRed;
					d1[x]=ColBuff[x].rgbtGreen;
					d2[x]=ColBuff[x].rgbtBlue;
				}
			}
		}
		delete	[]ColBuff;
	}
	return true;
}