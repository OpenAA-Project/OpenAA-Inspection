#include <stdio.h>
#include <jpeglib.h>
#include "XTypeDef.h"
#include "XMainSchemeMemory.h"
#include <QFileDialog>
#include <QMessageBox>
#include "swap.h"
#include <setjmp.h>

//extern	"C"
//{
//extern	jmp_buf err_jmpbuf;
//};

bool	read_jpeg_stream(FILE *fp,ImageBuffer *Buff[] ,int LayerNumb);

bool	LoadJpeg(const QString &PFileName ,ImageBuffer *Buff[] ,int LayerNumb)
{
	//int c = setjmp(err_jmpbuf);
	//if (c == 0) {
		QFile	File(PFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			FILE *file=fdopen(File.handle() ,/**/"rb");
			if(file!=NULL){
				bool ret=read_jpeg_stream(file,Buff ,LayerNumb);
				fclose(file);
				return ret;
			}
		}
	//}
	return false;
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
QImage	read_jpeg_stream(FILE *fp);

QImage	LoadJpeg(const QString &PFileName)
{
	//int c = setjmp(err_jmpbuf);
	//if (c == 0) {
		QFile	File(PFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			FILE *file=fdopen(File.handle() ,/**/"rb");
			if(file!=NULL){
				QImage	r=read_jpeg_stream(file);
				fclose(file);
				return r;
			}
		}
	//}
	return QImage();
}

QImage	read_jpeg_stream(FILE *fp)
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
		return QImage();
	}
	jpeg_start_decompress(&jpegd);
	if (jpegd.out_color_space != JCS_RGB) {
		jpeg_destroy_decompress(&jpegd);
		return QImage();
	}
	stride = sizeof(JSAMPLE) * jpegd.output_width * jpegd.output_components;
	buffer = new BYTE[10*stride];
	int	XLen=jpegd.output_width;
	int	YLen=jpegd.output_height;
	QImage	Img(XLen,YLen,QImage::Format_RGB32);
	for (y = 0; y < YLen; y++) {
		jpeg_read_scanlines(&jpegd, &buffer, 1);
		row = buffer;
		QRgb	*d=(QRgb *)Img.scanLine(y);
		for (x = 0; x < XLen; x++){
			*d=qRgb(*row,*(row+1),*(row+2));
			row+=3;
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