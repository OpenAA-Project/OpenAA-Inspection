/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterNothing\FilterNothing.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterImageShading.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>

#include "Setting.h"


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ImageShading";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make Shading data from Image";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterImageShading(base);
}

bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	SettingDialog dlg(handle->GetLayersBase(),parent);

	FilterImageShading *ptr = dynamic_cast<FilterImageShading*>(handle);
	if(ptr==NULL){
		return false;
	}

	dlg.setImagePath( ptr->imagePath(0), ptr->imagePath(1), ptr->imagePath(2) );
	dlg.setTarget( ptr->target(0), ptr->target(1), ptr->target(2) );
	dlg.setPreOffset( ptr->preOffset(0), ptr->preOffset(1), ptr->preOffset(2) );
	dlg.setAftOffset( ptr->aftOffset(0), ptr->aftOffset(1), ptr->aftOffset(2) );
	dlg.updateInf();

	if(dlg.exec()==QDialog::Accepted){
		ptr->setTarget( dlg.target(0), dlg.target(1), dlg.target(2) );
		ptr->setPreOffset( dlg.preOffset(0), dlg.preOffset(1), dlg.preOffset(2) );
		ptr->setAftOffset( dlg.aftOffset(0), dlg.aftOffset(1), dlg.aftOffset(2) );

		ptr->setImagePath( dlg.imagePath(0), dlg.imagePath(1), dlg.imagePath(2) );
	}

	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterImageShading::FilterImageShading(LayersBase *base)
:FilterClassBase(base)
{
	m_arrayLength = 0;

	m_multiplyListR = NULL;
	m_multiplyListG = NULL;
	m_multiplyListB = NULL;

	m_targetValueR = 190;
	m_targetValueG = 190;
	m_targetValueB = 190;

	m_preOffsetValueR = 0;
	m_preOffsetValueG = 0;
	m_preOffsetValueB = 0;

	m_aftOffsetValueR = 0;
	m_aftOffsetValueG = 0;
	m_aftOffsetValueB = 0;

	for(int i=0;i<256;i++){
		m_TableListR[i]=NULL;
		m_TableListG[i]=NULL;
		m_TableListB[i]=NULL;
	}

}
FilterImageShading::~FilterImageShading(void)
{
	if(m_multiplyListR!=NULL)
		delete	[]m_multiplyListR;
	if(m_multiplyListG!=NULL)
		delete	[]m_multiplyListG;
	if(m_multiplyListB!=NULL)
		delete	[]m_multiplyListB;

	m_multiplyListR = NULL;
	m_multiplyListG = NULL;
	m_multiplyListB = NULL;

	for(int i=0;i<256;i++){
		if(m_TableListR[i]!=NULL){
			delete	[]m_TableListR[i];
			m_TableListR[i]=NULL;
		}
		if(m_TableListG[i]!=NULL){
			delete	[]m_TableListG[i];
			m_TableListG[i]=NULL;
		}
		if(m_TableListB[i]!=NULL){
			delete	[]m_TableListB[i];
			m_TableListB[i]=NULL;
		}
	}
}

bool FilterImageShading::Save(QIODevice *f)
{
	if(f==NULL){
		return false;
	}

	QDataStream stream(f);

	stream << m_imagePathLayerR;
	stream << m_imagePathLayerG;
	stream << m_imagePathLayerB;
		
	stream << m_targetValueR;
	stream << m_targetValueG;
	stream << m_targetValueB;

	stream << m_preOffsetValueR;
	stream << m_preOffsetValueG;
	stream << m_preOffsetValueB;

	stream << m_aftOffsetValueR;
	stream << m_aftOffsetValueG;
	stream << m_aftOffsetValueB;

	stream << m_arrayLength;
	if(m_multiplyListR==NULL){
		stream << false;
	}else{
		stream << true;
		for(int i=0; i<m_arrayLength; i++){
			stream << m_multiplyListR[i];
		}
	}
	if(m_multiplyListG==NULL){
		stream << false;
	}else{
		stream << true;
		for(int i=0; i<m_arrayLength; i++){
			stream << m_multiplyListG[i];
		}
	}
	if(m_multiplyListB==NULL){
		stream << false;
	}else{
		stream << true;
		for(int i=0; i<m_arrayLength; i++){
			stream << m_multiplyListB[i];
		}
	}
	
	stream << m_imageStatusLayerR;
	stream << m_imageStatusLayerG;
	stream << m_imageStatusLayerB;

	return true;
}

bool FilterImageShading::Load(QIODevice *f)
{
	if(f==NULL){
		return false;
	}
		
	QDataStream stream(f);
		
	stream >> m_imagePathLayerR;
	stream >> m_imagePathLayerG;
	stream >> m_imagePathLayerB;
		
	stream >> m_targetValueR;
	stream >> m_targetValueG;
	stream >> m_targetValueB;

	stream >> m_preOffsetValueR;
	stream >> m_preOffsetValueG;
	stream >> m_preOffsetValueB;

	stream >> m_aftOffsetValueR;
	stream >> m_aftOffsetValueG;
	stream >> m_aftOffsetValueB;

	stream >> m_arrayLength;

	if(m_multiplyListR!=NULL){
		delete m_multiplyListR;
		m_multiplyListR = NULL;
	}
	if(m_multiplyListG!=NULL){
		delete m_multiplyListG;
		m_multiplyListG = NULL;
	}
	if(m_multiplyListB!=NULL){
		delete m_multiplyListB;
		m_multiplyListB = NULL;
	}

	if(m_arrayLength!=0){
		bool exist;

		stream >> exist;
		if(exist==true){
			m_multiplyListR = new qreal[m_arrayLength];
			for(int i=0; i<m_arrayLength; i++){
				stream >> m_multiplyListR[i];
			}
		}
		
		stream >> exist;
		if(exist==true){
			m_multiplyListG = new qreal[m_arrayLength];
			for(int i=0; i<m_arrayLength; i++){
				stream >> m_multiplyListG[i];
			}
		}
		
		stream >> exist;
		if(exist==true){
			m_multiplyListB = new qreal[m_arrayLength];
			for(int i=0; i<m_arrayLength; i++){
				stream >> m_multiplyListB[i];
			}
		}
	}
	
	stream >> m_imageStatusLayerR;
	stream >> m_imageStatusLayerG;
	stream >> m_imageStatusLayerB;

	if(m_arrayLength!=GetDotPerLine() || m_imageStatusLayerR!=ImageStatus(m_imagePathLayerR)){
		_updateArrayLength(GetDotPerLine());
		_makeShadingData(0);
	}
	if(m_arrayLength!=GetDotPerLine() || m_imageStatusLayerG!=ImageStatus(m_imagePathLayerG)){
		_updateArrayLength(GetDotPerLine());
		_makeShadingData(1);
	}
	if(m_arrayLength!=GetDotPerLine() || m_imageStatusLayerB!=ImageStatus(m_imagePathLayerB)){
		_updateArrayLength(GetDotPerLine());
		_makeShadingData(2);
	}
	
	const int	N = GetMaxLines();
	if(m_multiplyListR!=NULL){
		BuildTable(m_TableListR, m_multiplyListR, m_preOffsetValueR, m_aftOffsetValueR, N, m_arrayLength);
	}
	if(m_multiplyListG!=NULL){
		BuildTable(m_TableListG, m_multiplyListG, m_preOffsetValueG, m_aftOffsetValueG, N, m_arrayLength);
	}
	if(m_multiplyListB!=NULL){
		BuildTable(m_TableListB, m_multiplyListB, m_preOffsetValueB, m_aftOffsetValueB, N, m_arrayLength);
	}
	return true;
}

bool FilterImageShading::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	/*
	const int	N = GetMaxLines();
	if(BufferDimCounts>=1 && m_multiplyListR!=NULL){
		_calcMultiply(Buff[0], m_multiplyListR, m_preOffsetValueR, m_aftOffsetValueR, N, m_arrayLength);
	}
	if(BufferDimCounts>=2 && m_multiplyListG!=NULL){
		_calcMultiply(Buff[1], m_multiplyListG, m_preOffsetValueG, m_aftOffsetValueG, N, m_arrayLength);
	}
	if(BufferDimCounts>=3 && m_multiplyListB!=NULL){
		_calcMultiply(Buff[2], m_multiplyListB, m_preOffsetValueB, m_aftOffsetValueB, N, m_arrayLength);
	}
	*/
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	#pragma omp parallel
	{
		#pragma omp for		
		for(int y=0; y<MaxLines; y++){
			if(BufferDimCounts>=1 && m_multiplyListR!=NULL){
				BYTE	*d = Buff[0]->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					*d=(m_TableListR[*d])[x];
					d++;
				}
			}
			if(BufferDimCounts>=2 && m_multiplyListG!=NULL){
				BYTE	*d = Buff[1]->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					*d=(m_TableListG[*d])[x];
					d++;
				}
			}
			if(BufferDimCounts>=3 && m_multiplyListB!=NULL){
				BYTE	*d = Buff[2]->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					*d=(m_TableListB[*d])[x];
					d++;
				}
			}
		}
	}
	

	return true;
}

bool FilterImageShading::Initial(void)
{
	if(_isImageModified(0)==true){
		_makeShadingData(0);
	}
	if(_isImageModified(1)==true){
		_makeShadingData(1);
	}
	if(_isImageModified(2)==true){
		_makeShadingData(2);
	}
	return true;
}

bool FilterImageShading::Release(void)
{
	if(m_multiplyListR!=NULL){
		delete []m_multiplyListR;
		m_multiplyListR = NULL;
	}
	if(m_multiplyListG!=NULL){
		delete []m_multiplyListG;
		m_multiplyListG = NULL;
	}
	if(m_multiplyListB!=NULL){
		delete []m_multiplyListB;
		m_multiplyListB = NULL;
	}

	return true;
}

QString	FilterImageShading::GetDataText(void)
{
	return "ImageShading";
}

QString FilterImageShading::GetDefaultFileName(void)
{
	return "FilterImageShading.dat";
}

QString FilterImageShading::imagePath(int number) const
{
	switch(number){
	case 0:
		return m_imagePathLayerR;
		break;
	case 1:
		return m_imagePathLayerG;
		break;
	case 2:
		return m_imagePathLayerB;
		break;
	default:
		return QString();
		break;
	}

	return QString();
}

void FilterImageShading::BuildTable(BYTE *Table[256],const qreal * const data, qreal preOffset, qreal aftOffset, const int MaxLines, const int DotPerLine)
{
	for(int i=0;i<256;i++){
		if(Table[i]!=NULL){
			delete	[]Table[i];
		}
		Table[i]=new BYTE[DotPerLine];
	}

	if(preOffset==0 && aftOffset==0){
		for(int Col=0;Col<256;Col++){
			for(int x=0; x<DotPerLine; x++){
				qreal v = Col;
				v = v * data[x];	// main
				(Table[Col])[x] = (BYTE)qBound(0.0, v, 255.0);
			}
		}
	}else if(preOffset!=0 && aftOffset==0){
		for(int Col=0;Col<256;Col++){
			for(int x=0; x<DotPerLine; x++){
				qreal v = Col;

				v += preOffset;
				v = qBound(0.0, v, 255.0);

				v = v * data[x];	// main

				(Table[Col])[x] = (BYTE)qBound(0.0, v, 255.0);
			}
		}
	}else if(preOffset==0 && aftOffset!=0){
		for(int Col=0;Col<256;Col++){
			for(int x=0; x<DotPerLine; x++){
				qreal v = Col;

					//v += preOffset;
					//v = qBound(0.0, v, 255.1);

				v = v * data[x];	// main

				v += aftOffset;
				v = qBound(0.0, v, 255.0);

				(Table[Col])[x] = (BYTE)qBound(0.0, v, 255.0);
			}
		}
	}else{
		for(int Col=0;Col<256;Col++){
			for(int x=0; x<DotPerLine; x++){
				qreal v = Col;

				v += preOffset;
				v = qBound(0.0, v, 255.0);

				v = v * data[x];	// main

				v += aftOffset;
				v = qBound(0.0, v, 255.0);

				(Table[Col])[x] = (BYTE)qBound(0.0, v, 255.0);
			}
		}
	}
}


void FilterImageShading::_calcMultiply(ImageBuffer *buff, const qreal * const data, qreal preOffset, qreal aftOffset, const int MaxLines, const int DotPerLine)
{
	if(preOffset==0 && aftOffset==0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0; y<MaxLines; y++){
				BYTE	*d = buff->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					qreal v = d[x];

					//v += preOffset;
					//v = qBound(0.0, v, 255.0);

					v = v * data[x];	// main

					//v += aftOffset;
					//v = qBound(0.0, v, 255.0);

					d[x] = (BYTE)qBound(0.0, v, 255.0);
				}
			}
		}
	}else if(preOffset!=0 && aftOffset==0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0; y<MaxLines; y++){
				BYTE	*d = buff->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					qreal v = d[x];

					v += preOffset;
					v = qBound(0.0, v, 255.0);

					v = v * data[x];	// main

					//v += aftOffset;
					//v = qBound(0.0, v, 255.0);

					d[x] = (BYTE)qBound(0.0, v, 255.0);
				}
			}
		}
	}else if(preOffset==0 && aftOffset!=0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0; y<MaxLines; y++){
				BYTE	*d = buff->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					qreal v = d[x];

					//v += preOffset;
					//v = qBound(0.0, v, 255.1);

					v = v * data[x];	// main

					v += aftOffset;
					v = qBound(0.0, v, 255.0);

					d[x] = (BYTE)qBound(0.0, v, 255.0);
				}
			}
		}
	}else{
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0; y<MaxLines; y++){
				BYTE	*d = buff->GetY(y);
				for(int x=0; x<DotPerLine; x++){
					qreal v = d[x];

					v += preOffset;
					v = qBound(0.0, v, 255.0);

					v = v * data[x];	// main

					v += aftOffset;
					v = qBound(0.0, v, 255.0);

					d[x] = (BYTE)qBound(0.0, v, 255.0);
				}
			}
		}
	}
}

void FilterImageShading::_makeShadingData()
{
	m_arrayLength = GetDotPerLine();

	if(m_multiplyListR!=NULL){
		delete	[]m_multiplyListR;
		m_multiplyListR = NULL;
	}
	if(m_multiplyListG!=NULL){
		delete	[]m_multiplyListG;
		m_multiplyListG = NULL;
	}
	if(m_multiplyListB!=NULL){
		delete	[]m_multiplyListB;
		m_multiplyListB = NULL;
	}

	qreal *buff = NULL;

	QImage img;

	img = QImage(m_imagePathLayerR);
	
	if(img.isNull()==false){
		if(buff==NULL){
			buff = new qreal[m_arrayLength];
		}
		_makeAverageData(img, 0, buff, m_arrayLength);
		m_multiplyListR = new qreal[m_arrayLength];
		_makeShadingData(buff, m_arrayLength, m_multiplyListR, m_targetValueR, m_preOffsetValueR);
	}

	img = QImage(m_imagePathLayerG);

	if(img.isNull()==false){
		if(buff==NULL){
			buff = new qreal[m_arrayLength];
		}
		_makeAverageData(img, 1, buff, m_arrayLength);
		m_multiplyListG = new qreal[m_arrayLength];
		_makeShadingData(buff, m_arrayLength, m_multiplyListG, m_targetValueG, m_preOffsetValueG);
	}

	img = QImage(m_imagePathLayerB);

	if(img.isNull()==false){
		if(buff==NULL){
			buff = new qreal[m_arrayLength];
		}
		_makeAverageData(img, 2, buff, m_arrayLength);
		m_multiplyListB = new qreal[m_arrayLength];
		_makeShadingData(buff, m_arrayLength, m_multiplyListB, m_targetValueB, m_preOffsetValueB);
	}

	if(buff!=NULL){
		delete []buff;
	}
}

void FilterImageShading::_makeShadingData(int layer)
{
	QImage img;

	QString imagePath;
	qreal **destMultiplyList = NULL;
	qreal targetValue;
	qreal preOffsetValue;

	switch(layer){
	case 0:
		imagePath = m_imagePathLayerR;
		destMultiplyList = &m_multiplyListR;
		targetValue = m_targetValueR;
		preOffsetValue = m_preOffsetValueR;
		break;
	case 1:
		imagePath = m_imagePathLayerG;
		destMultiplyList = &m_multiplyListG;
		targetValue = m_targetValueG;
		preOffsetValue = m_preOffsetValueG;
		break;
	case 2:
		imagePath = m_imagePathLayerB;
		destMultiplyList = &m_multiplyListB;
		targetValue = m_targetValueB;
		preOffsetValue = m_preOffsetValueB;
		break;
	default:
		return;
	}

	if(*destMultiplyList!=NULL){
		delete	[](*destMultiplyList);
		*destMultiplyList = NULL;
	}

	img = QImage(imagePath);
		
	if(img.isNull()==false){
		qreal *buff = new qreal[m_arrayLength];
		_makeAverageData(img, layer, buff, m_arrayLength);
		*destMultiplyList = new qreal[m_arrayLength];
		_makeShadingData(buff, m_arrayLength, *destMultiplyList, targetValue, preOffsetValue);
		delete []buff;
	}

	//switch(layer){
	//case 0:
	//	if(m_multiplyListR!=NULL){
	//		delete	[]m_multiplyListR;
	//		m_multiplyListR = NULL;
	//	}

	//	img = QImage(m_imagePathLayerR);
	//	
	//	if(img.isNull()==false){
	//		if(buff==NULL){
	//			buff = new qreal[m_arrayLength];
	//		}
	//		_makeAverageData(img, 0, buff, m_arrayLength);
	//		m_multiplyListR = new qreal[m_arrayLength];
	//		_makeShadingData(buff, m_arrayLength, m_multiplyListR, m_targetValueR, m_preOffsetValueR);
	//	}

	//	break;
	//case 1:
	//	if(m_multiplyListG!=NULL){
	//		delete	[]m_multiplyListG;
	//		m_multiplyListG = NULL;
	//	}

	//	img = QImage(m_imagePathLayerG);
	//	
	//	if(img.isNull()==false){
	//		if(buff==NULL){
	//			buff = new qreal[m_arrayLength];
	//		}
	//		_makeAverageData(img, 0, buff, m_arrayLength);
	//		m_multiplyListG = new qreal[m_arrayLength];
	//		_makeShadingData(buff, m_arrayLength, m_multiplyListG, m_targetValueG, m_preOffsetValueG);
	//	}
	//	break;
	//case 2:
	//	if(m_multiplyListB!=NULL){
	//		delete	[]m_multiplyListB;
	//		m_multiplyListB = NULL;
	//	}

	//	img = QImage(m_imagePathLayerB);
	//	
	//	if(img.isNull()==false){
	//		if(buff==NULL){
	//			buff = new qreal[m_arrayLength];
	//		}
	//		_makeAverageData(img, 0, buff, m_arrayLength);
	//		m_multiplyListB = new qreal[m_arrayLength];
	//		_makeShadingData(buff, m_arrayLength, m_multiplyListB, m_targetValueB, m_preOffsetValueB);
	//	}
	//	break;
	//default:
	//	break;
	//}

}

void FilterImageShading::_makeAverageData(const QImage &image, int layer, qreal *buffer, int bufferLen)
{
	if(buffer==NULL || bufferLen<=0){
		return;
	}

	if(image.isNull()==true){
		#pragma omp for
		for(int i=0; i<bufferLen; i++){
			buffer[i] = 1.0;
		}
		return;
	}

	qreal *buff = new qreal[image.width()];

	if(layer==0){
		#pragma omp for
		for(int x=0; x<image.width(); x++){
			qreal sum = 0.0;
			for(int y=0; y<image.height(); y++){
				sum += qRed( image.pixel(x, y) );
			}
			sum /= image.height();

			buff[x] = sum;
		}
	}else if(layer==1){
		#pragma omp for
		for(int x=0; x<image.width(); x++){
			qreal sum = 0.0;
			for(int y=0; y<image.height(); y++){
				sum += qGreen( image.pixel(x, y) );
			}
			sum /= image.height();

			buff[x] = sum;
		}
	}else if(layer==2){
		#pragma omp for
		for(int x=0; x<image.width(); x++){
			qreal sum = 0.0;
			for(int y=0; y<image.height(); y++){
				sum += qBlue( image.pixel(x, y) );
			}
			sum /= image.height();

			buff[x] = sum;
		}
	}else{
		delete	[]buff;
		return;
	}

	const qreal multi_val = image.width() / (qreal)bufferLen;
		
	#pragma omp for
	for(int i=0; i<bufferLen; i++){
		buffer[i] = buff[(int)(i*multi_val)];
	}

	delete []buff;
}

void FilterImageShading::_makeShadingData(qreal *averageArray, int arrayLen,
	qreal *resultArray, qreal target, qreal preOffset)
{
	int block = 2;
	if(averageArray==NULL || arrayLen<=0 || resultArray==NULL)return;

	if(block*2 + 1 > arrayLen){
		for(int i=1; i<arrayLen-1; i++){
			resultArray[i] = (target+preOffset) / (averageArray[i]+preOffset);
		}
		return;
	}

	for(int i=0; i<block; i++){
		resultArray[i] = (target+preOffset) / (averageArray[i]+preOffset);
	}

	for(int i=block; i<arrayLen-block; i++){
		qreal sum = 0.0;
		int cnt = 0;
		for(int j=-block; j<=block; j++){
			sum += (target+preOffset) / (averageArray[i+j]+preOffset);
			cnt++;
		}
		sum /= cnt;
		resultArray[i] = sum;
	}

	for(int i=arrayLen-block; i<arrayLen; i++){
		resultArray[i] = (target+preOffset) / (averageArray[i]+preOffset);
	}
}

bool FilterImageShading::_isImageModified(int layer) const {
	if(layer==0){
		if(m_imageStatusLayerR!=ImageStatus(m_imagePathLayerR)){
			return true;
		}else{
			return false;
		}
	}else if(layer==1){
		if(m_imageStatusLayerG!=ImageStatus(m_imagePathLayerG)){
			return true;
		}else{
			return false;
		}
	}else if(layer==2){
		if(m_imageStatusLayerB!=ImageStatus(m_imagePathLayerB)){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

void FilterImageShading::_updateArrayLength(int length){
	if(m_arrayLength==length){
		return;
	}

	if(m_arrayLength!=0){
		qreal mult = m_arrayLength / (qreal)length;
			
		if(m_multiplyListR!=NULL){
			qreal *buff = new qreal[length];

			for(int i=0; i<length; i++){
				buff[i] = m_multiplyListR[(int)(i*mult)];
			}
			delete []m_multiplyListR;
			m_multiplyListR = buff;
		}
			
		if(m_multiplyListG!=NULL){
			qreal *buff = new qreal[length];

			for(int i=0; i<length; i++){
				buff[i] = m_multiplyListG[(int)(i*mult)];
			}
			delete []m_multiplyListG;
			m_multiplyListG = buff;
		}
			
		if(m_multiplyListB!=NULL){
			qreal *buff = new qreal[length];

			for(int i=0; i<length; i++){
				buff[i] = m_multiplyListB[(int)(i*mult)];
			}
			delete []m_multiplyListB;
			m_multiplyListB = buff;
		}
	}

	m_arrayLength = length;
}

bool qp2compare(const QPair<int, int> &a, const QPair<int, int> &b){
	return (a.second < b.second);
}

template<typename T>
class _sortItem{
public:
	_sortItem():distance(0.0){};

public:
	T data;
	qreal distance;
public:
	bool operator<(const _sortItem &other) const {
		return distance < other.distance;
	};
};

QList<QPair<int, int> > sortByNearValue(int value, const QList<QPair<int, int> > &list){
	if(list.isEmpty()==true){
		return QList<QPair<int, int> >();
	}

	QList<_sortItem<QPair<int,int> > > itemList;
	int currentVautCount = list.first().second;
	QList<QPair<int, int> > destList;

	for(int i=0; i<list.count(); i++){
		const QPair<int, int> &data = list.at(i);

		if(currentVautCount!=data.second){
			currentVautCount = data.second;
			std::sort(itemList.begin(), itemList.end());
			for(int i=0; i<itemList.count(); i++){
				destList << itemList.at(i).data;
			}
			itemList.clear();
		}

		_sortItem<QPair<int, int> > item;
		item.data = data;
		item.distance = qAbs(value - data.first);
		itemList << item;
	}

	return destList;
}

QList<QPair<int/* light level */, int/* vote count */> > FilterImageShading::_noiseCutting(const QImage &image, int x, int layer, qreal cutLevel)
{
	if(layer<0 || 2<layer || cutLevel<0 || qFuzzyIsNull(cutLevel)==true){
		return QList<QPair<int, int> >();
	}


	QList<QPair<int/* light level */, int/* vote count */> > list;
	for(int i=0; i<256; i++){
		list << QPair<int, int>(i, 0);
	}

	const int shiftVal = 8 * (2-layer);

	qreal average = 0.0;
	for(int y=0; y<image.height(); y++){
		int val = (image.pixel(x, y) >> shiftVal) & 0xff;
		list[val].second++;
		average += val;
	}
	average /= image.height();

	std::sort(list.begin(), list.end(), qp2compare);
	list = sortByNearValue(average, list);

	int count = 0;
	const qreal maxCount = (100.0 - cutLevel)/100.0 * image.height();
	QList<QPair<int, int> > retList;

	for(int i=0; i<list.count(); i++){
		const QPair<int, int> &p = list.at(i);
		count += p.second;

		retList << p;

		if(count>=maxCount){
			break;
		}
	}

	return retList;
}

void FilterImageShading::setImagePath(const QString &imgPathR, const QString &imgPathG, const QString &imgPathB)
{
	_updateArrayLength(GetDotPerLine());

	if(m_imagePathLayerR!=imgPathR || m_imageStatusLayerR!=ImageStatus(imgPathR)){
		m_imagePathLayerR = imgPathR;
		m_imageStatusLayerR = ImageStatus(imgPathR);

		_makeShadingData(0);
	}
	
	if(m_imagePathLayerG!=imgPathG || m_imageStatusLayerG!=ImageStatus(imgPathG)){
		m_imagePathLayerG = imgPathG;
		m_imageStatusLayerG = ImageStatus(imgPathG);

		_makeShadingData(1);
	}

	if(m_imagePathLayerB!=imgPathB || m_imageStatusLayerB!=ImageStatus(imgPathB)){
		m_imagePathLayerB = imgPathB;
		m_imageStatusLayerB = ImageStatus(imgPathB);

		_makeShadingData(2);
	}
}

void FilterImageShading::setTarget(qreal targetR, qreal targetG, qreal targetB)
{
	m_targetValueR = targetR;
	m_targetValueG = targetG;
	m_targetValueB = targetB;
}

void FilterImageShading::setPreOffset(qreal offsetR, qreal offsetG, qreal offsetB)
{
	m_preOffsetValueR = offsetR;
	m_preOffsetValueG = offsetG;
	m_preOffsetValueB = offsetB;
}

void FilterImageShading::setAftOffset(qreal offsetR, qreal offsetG, qreal offsetB)
{
	m_aftOffsetValueR = offsetR;
	m_aftOffsetValueG = offsetG;
	m_aftOffsetValueB = offsetB;
}

qreal FilterImageShading::target(int layer)
{
	switch(layer){
	case 0:
		return m_targetValueR;
	case 1:
		return m_targetValueG;
	case 2:
		return m_targetValueB;
	default:
		return -1;
	}
}

qreal FilterImageShading::preOffset(int layer)
{
	switch(layer){
	case 0:
		return m_preOffsetValueR;
	case 1:
		return m_preOffsetValueG;
	case 2:
		return m_preOffsetValueB;
	default:
		return -1;
	}
}

qreal FilterImageShading::aftOffset(int layer)
{
	switch(layer){
	case 0:
		return m_aftOffsetValueR;
	case 1:
		return m_aftOffsetValueG;
	case 2:
		return m_aftOffsetValueB;
	default:
		return -1;
	}
}
