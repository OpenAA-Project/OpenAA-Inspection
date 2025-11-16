#include <Windows.h>
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