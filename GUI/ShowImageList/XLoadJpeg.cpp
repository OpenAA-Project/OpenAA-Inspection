#include <stdio.h>
#include <jpeglib.h>
#include "XTypeDef.h"
#include "XMainSchemeMemory.h"
#include <QFileDialog>
#include <QMessageBox>
#include "swap.h"
#include <setjmp.h>

extern	"C"
{
extern	jmp_buf err_jmpbuf;
};

QImage	*read_jpeg_stream(FILE *fp)
{
  uint32 x, y;
  struct jpeg_decompress_struct jpegd;
  struct jpeg_error_mgr myerr;

  JSAMPROW buffer = NULL;
  JSAMPROW row;
  int stride;
  jpegd.err = jpeg_std_error(&myerr);

  jpeg_create_decompress(&jpegd);
  jpeg_stdio_src(&jpegd, fp);
  if (jpeg_read_header(&jpegd, TRUE) != JPEG_HEADER_OK) {
	  jpeg_destroy_decompress(&jpegd);
		return NULL;
	}
	jpeg_start_decompress(&jpegd);
	if (jpegd.out_color_space != JCS_RGB) {
		jpeg_destroy_decompress(&jpegd);
		return NULL;
	}
	stride = sizeof(JSAMPLE) * jpegd.output_width * jpegd.output_components;
	buffer = new BYTE[10*stride];
				
	int	XLen=jpegd.output_width ;
	int	YLen=jpegd.output_height;

	QImage	*Img=new QImage(XLen,YLen,QImage::Format_ARGB32);

	for (y = 0; y < YLen; y++) {
		jpeg_read_scanlines(&jpegd, &buffer, 1);
		row = buffer;

		QRgb	*d=(QRgb *)Img->scanLine(y);
		for (x = 0; x < XLen; x++){
			BYTE	r = *row++;
			BYTE	g = *row++;
			BYTE	b = *row++;
			*d=qRgba(r,g,b,255);
			d++;
		}
	}
	for(;y<jpegd.output_height;y++){
		jpeg_read_scanlines(&jpegd, &buffer, 1);
	}

	//	QMessageBox::information(NULL,"","1");

	jpeg_finish_decompress(&jpegd);
	//	QMessageBox::information(NULL,"","2");

	jpeg_destroy_decompress(&jpegd);
	//	QMessageBox::information(NULL,"","3");

	delete	[]buffer;
	//	QMessageBox::information(NULL,"","4");

	return Img;
}


bool	read_jpeg_stream(FILE *fp,ImageBuffer *Buff[] ,int LayerNumb)
{
  uint32 x, y;
  struct jpeg_decompress_struct jpegd;
  struct jpeg_error_mgr myerr;

  JSAMPROW buffer = NULL;
  JSAMPROW row;
  int stride;
  jpegd.err = jpeg_std_error(&myerr);

  jpeg_create_decompress(&jpegd);
  jpeg_stdio_src(&jpegd, fp);
  if (jpeg_read_header(&jpegd, TRUE) != JPEG_HEADER_OK) {
	  jpeg_destroy_decompress(&jpegd);
		return false;
	}
	jpeg_start_decompress(&jpegd);
	if (jpegd.out_color_space != JCS_RGB) {
		jpeg_destroy_decompress(&jpegd);
		return false;
	}
	stride = sizeof(JSAMPLE) * jpegd.output_width * jpegd.output_components;
	buffer = new BYTE[10*stride];
				
	int	XLen=min((int)jpegd.output_width ,Buff[0]->GetWidth());
	int	YLen=min((int)jpegd.output_height,Buff[0]->GetHeight());
	for (y = 0; y < YLen; y++) {
		jpeg_read_scanlines(&jpegd, &buffer, 1);
		row = buffer;
		if(LayerNumb>=3){
			BYTE	*d0=Buff[0]->GetY(y);
			BYTE	*d1=Buff[1]->GetY(y);
			BYTE	*d2=Buff[2]->GetY(y);
			for (x = 0; x < XLen; x++){
				d0[x] = *row++;
				d1[x] = *row++;
				d2[x] = *row++;
			}
		}
		else if(LayerNumb==2){
			BYTE	*d0=Buff[0]->GetY(y);
			BYTE	*d1=Buff[1]->GetY(y);
			for (x = 0; x < XLen; x++){
				d0[x] = *row++;
				d1[x] = *row++;
				row++;
			}
	    }
		else if(LayerNumb==1){
			BYTE	*d0=Buff[0]->GetY(y);
			for (x = 0; x < XLen; x++){
				d0[x] = *row++;
				row++;
				row++;
			}
		}
	}
	for(;y<jpegd.output_height;y++){
		jpeg_read_scanlines(&jpegd, &buffer, 1);
	}

	//	QMessageBox::information(NULL,"","1");

	jpeg_finish_decompress(&jpegd);
	//	QMessageBox::information(NULL,"","2");

	jpeg_destroy_decompress(&jpegd);
	//	QMessageBox::information(NULL,"","3");

	delete	[]buffer;
	//	QMessageBox::information(NULL,"","4");

	return true;
}