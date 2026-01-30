/*
 * Copyright (C) 2021
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

#include "JDTAnalyzer.h"

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QMutex>
#include <QFileInfo>
#include <QDir>
//#include "XNetworkDrive.h"
#include "XGeneralFunc.h"
#include "XTransFile.h"

//#ifndef BYTE
//#define BYTE unsigned char
//#endif

class	NetworkAccessor
{
	int	Counter;
	QMutex	MutexCounter;
public:
	NetworkAccessor(void){	Counter=0;	}

	void	Inc(void){
		MutexCounter.lock();
		Counter++;
		MutexCounter.unlock();
	}
	int	Dec(void){
		MutexCounter.lock();
		Counter--;
		int	Ret=Counter;
		MutexCounter.unlock();
		return Ret;
	}

};

NetworkAccessor	NetAccessor[26];


JDTFile::JDTFile(const QString &filename,const QString &_TransFileHost, int _TransFilePort)
{
	TransFileHost=_TransFileHost;
	TransFilePort=_TransFilePort;

	m_ok = false;

	if(filename.isEmpty()==true){
		return;
	}

	int ver = checkVer(filename);

	switch(ver){
	case 1:
		m_ok = analyze_v1(filename);// �o�[�W����1�p
		break;
	case 2:
		m_ok = analyze_v2(filename);// �o�[�W����2�p
		break;
	case 3:
	case 4:
		m_ok = analyze_v3(filename);// �o�[�W����3�p
		break;
	case 5:
		m_ok = analyze_v5(filename);// �o�[�W����3�p
		break;
	default:
		return;// �����o�[�W����
	}
}

bool JDTFile::findImage(int top, int left, JDTImage &jdtDest) const
{
	for(QList<JDTImage>::const_iterator it=constBegin(); it!=constEnd(); it++){
		if((it->top()==top) && (it->left()==left)){
			jdtDest = *it;
			return true;
		}
	}
	return false;
}

bool JDTFile::analyze_v1(const QString &filename)
{
	return analyze_v2(filename);
}

bool JDTFile::analyze_v2(const QString &filename)
{
	if(TransFileHost.isEmpty()==true){
		QFile file(filename);
		return analyze_v2(file);
	}
	else{
		TrFile	file(filename,TransFileHost,TransFilePort);
		return analyze_v2(file);
	}
}

bool JDTFile::analyze_v2(QIODevice &file)
{
	if(file.open(QIODevice::ReadOnly)==true){
		// �t�@�C���I�[�v������
		QDataStream stream(&file);
		int ImageNumb;

		stream.setByteOrder(QDataStream::LittleEndian);

		stream >> ImageNumb;

		if(ImageNumb<=0){
			// NG�摜�����s��
			return false;
		}else{
			// �摜���������擾
			//QStringList loadImage;
			for(int NGI=0; NGI<ImageNumb; NGI++){// NG�摜���������[�v
				unsigned char ver[2];
				int page;
				int staticID;
				int x1,x2,y1,y2;
				int ImageByte;

				JDTImage jdtParts;

				stream >> ver[0];
				stream >> ver[1];
					
				// �o�[�W����
				int version = ((int)ver[1] << 8) + ver[0];
				if(version>=1 && version<=2){// �����o�[�W������1�A���݂̃o�[�W������2�܂�
					jdtParts.setVersion(version);
				}else{// �o�[�W�����G���[ 
					return false;
				}
					
				stream >> page// �y�[�W�ԍ�
					>> staticID// �ʂ��ԍ�
					>> x1// ����
					>> y1// �㑤
					>> x2// �E��
					>> y2// ����
					>> ImageByte;// �摜�̃o�C�g��

				//�`�F�b�N�ƃf�[�^�i�[
				if(page<0 ||
					staticID<0 ||
					x1<0 ||
					y1<0 ||
					x2<0 ||
					y2<0 ||
					ImageByte<0){
					// �f�[�^�s���v
					return false;
				}else{
					jdtParts.setPage(page);
					jdtParts.setStaticID(staticID);
					jdtParts.setTop(y1);
					jdtParts.setLeft(x1);
					jdtParts.setRight(x2);
					jdtParts.setBottom(y2);
					QImage pix;
					QByteArray pixData = file.read(ImageByte);
					if(pix.loadFromData(pixData, /**/"PNG")==true){// �o�[�W����2��PNG�摜
						jdtParts.setImageExtention(/**/"PNG");
					}else{
						if(pix.loadFromData(pixData, /**/"JPG")==true){// �o�[�W����1��JPG�摜
							jdtParts.setImageExtention(/**/"JPG");
						}else{
						
						}
					}
					jdtParts.setImage(pix);
					append(jdtParts);
					  
					//loadImage.append(QString("page=%1,top=%2,left=%3,right=%4,bottom=%5").arg(page).arg(x1).arg(y1).arg(x2).arg(y2));
				}
			}
		}
		return true;
	}else{
		// �t�@�C���I�[�v�����s
		return false;
	}

	return false;
}

bool JDTFile::analyze_v3(const QString &filename)
{
	if(TransFileHost.isEmpty()==true){
		QFile file(filename);
		return analyze_v3(file);
	}
	else{
		bool	ret;
		for(int i=0;i<4;i++){
			TrFile	file(filename,TransFileHost,TransFilePort);
			bool	ret=analyze_v3(file);
			if(ret==true)
				return true;
			GSleep(500);
		}
		return false;
	}
}
bool JDTFile::analyze_v3(QIODevice &file)
{
	if(file.open(QIODevice::ReadOnly)==true){

		// �t�@�C���I�[�v������
		QDataStream stream(&file);
		qint32 ver;
		QStringList loadImage;

		// �o�C�g�ǂݍ��ݏ������t�ɐݒ�
		stream.setByteOrder(QDataStream::LittleEndian);

		// �o�[�W��������
		stream >> ver;// 2 2

		ver = getVersion(ver);
		if(ver<0){
			return false;
		}

		// �t�F�C�Y��
		qint32 phaseNumb;
		stream >> phaseNumb;// 4 6

		if(phaseNumb<=0){
			return false;// �t�F�C�Y���`�F�b�N���s
		}

		// Phase�f�[�^�\��
		for(qint32 phase_cnt=0; phase_cnt<phaseNumb; phase_cnt++){
			// �o�[�W�����擾
			qint32 PhaseVer;
			stream >> PhaseVer;// 2 8
			if(PhaseVer<0){
				return false;
			}

			// �t�F�C�Y�ԍ�
			qint32 phase;
			stream >> phase;// 4 12

			// NG�摜��
			qint32 NGImageNumb;
			stream >> NGImageNumb;// 4 16

			// NG�摜�f�[�^�\��
			for(int NGCnt=0; NGCnt<NGImageNumb; NGCnt++){
				// �o�[�W�����擾
				qint32 NGVer;
				stream >> NGVer;
				if(NGVer<0){
					return false;
				}

				// �y�[�W�ԍ�
				qint32 page;
				stream >> page;

				// �ʂ��ԍ�
				qint32 staID;
				stream >> staID;
				
				// �e���W�擾
				qint32 left,top,right,bottom;
				stream >> left >> top >> right >> bottom;

				if(left<0 || top<0 || right<0 || bottom<0){
					return false;// �����l�`�F�b�N���s
				}

				// NG�摜�̃o�C�g��
				qint32 ImgSize;
				stream >> ImgSize;
						
				// NG�摜�ǂݍ���
				QByteArray NGImage = file.read(ImgSize);
				QImage image;
				if(image.loadFromData(NGImage, "PNG")==false){// PNG�œǂݍ���
					image.loadFromData(NGImage, "JPG");// �o���Ȃ�����JPG�ōēǂݍ���
				}
			
				JDTImage jdtParts;
					
				jdtParts.setImage(image);

				jdtParts.setPhase(phase);
				jdtParts.setPage(page);

				jdtParts.setVersion(NGVer);
				jdtParts.setStaticID(staID);

				jdtParts.setTop(top);
				jdtParts.setLeft(left);
				jdtParts.setRight(right);
				jdtParts.setBottom(bottom);


				append(jdtParts);
				loadImage.append(QString("phase=%1,page=%2,top=%3,left=%4,right=%5,bottom=%6.png")
					.arg(phase).arg(page).arg(left).arg(top).arg(right).arg(bottom));
			}
		}
		return true;
	}
	return false;
}

bool JDTFile::analyze_v5(const QString &filename)
{
	if(TransFileHost.isEmpty()==true){
		QFile file(filename);
		return analyze_v5(file);
	}
	else{
		bool	ret;
		for(int i=0;i<4;i++){
			TrFile	file(filename,TransFileHost,TransFilePort);
			bool	ret=analyze_v5(file);
			if(ret==true)
				return true;
			GSleep(500);
		}
		return false;
	}
}
bool JDTFile::analyze_v5(QIODevice &file)
{
	if(file.open(QIODevice::ReadOnly)==true){

		// �t�@�C���I�[�v������
		QDataStream stream(&file);
		qint32 ver;
		QStringList loadImage;

		// �o�C�g�ǂݍ��ݏ������t�ɐݒ�
		stream.setByteOrder(QDataStream::LittleEndian);

		// �o�[�W��������
		stream >> ver;// 2 2

		ver = getVersion(ver);
		if(ver<0){
			return false;
		}

		// �t�F�C�Y��
		qint32 phaseNumb;
		stream >> phaseNumb;// 4 6

		if(phaseNumb<=0){
			return false;// �t�F�C�Y���`�F�b�N���s
		}

		// Phase�f�[�^�\��
		for(qint32 phase_cnt=0; phase_cnt<phaseNumb; phase_cnt++){
			// �o�[�W�����擾
			qint32 PhaseVer;
			stream >> PhaseVer;// 2 8
			if(PhaseVer<0){
				return false;
			}

			// �t�F�C�Y�ԍ�
			qint32 phase;
			stream >> phase;// 4 12

			int16	SaveMode;
			stream >> SaveMode;

			// NG�摜��
			qint32 NGImageNumb;
			stream >> NGImageNumb;// 4 16

			// NG�摜�f�[�^�\��
			for(int NGCnt=0; NGCnt<NGImageNumb; NGCnt++){
				// �o�[�W�����擾
				if(SaveMode==1){
					qint32 NGVer;
					stream >> NGVer;
					if(NGVer<0){
						return false;
					}

					// �y�[�W�ԍ�
					qint32 page;
					stream >> page;

					// �ʂ��ԍ�
					qint32 staID;
					stream >> staID;
					
					// �e���W�擾
					qint32 left,top,right,bottom;
					stream >> left >> top >> right >> bottom;

					if(left<0 || top<0 || right<0 || bottom<0){
						return false;// �����l�`�F�b�N���s
					}

					// NG�摜�̃o�C�g��
					qint32 ImgSize;
					stream >> ImgSize;
							
					// NG�摜�ǂݍ���
					QByteArray NGImage = file.read(ImgSize);
					QImage image;
					if(image.loadFromData(NGImage, "PNG")==false){// PNG�œǂݍ���
						image.loadFromData(NGImage, "JPG");// �o���Ȃ�����JPG�ōēǂݍ���
					}
					JDTImage jdtParts;
						
					jdtParts.setImage(image);

					jdtParts.setPhase(phase);
					jdtParts.setPage(page);

					jdtParts.setVersion(NGVer);
					jdtParts.setStaticID(staID);

					jdtParts.setTop(top);
					jdtParts.setLeft(left);
					jdtParts.setRight(right);
					jdtParts.setBottom(bottom);


					append(jdtParts);
					loadImage.append(QString("phase=%1,page=%2,top=%3,left=%4,right=%5,bottom=%6.png")
						.arg(phase).arg(page).arg(left).arg(top).arg(right).arg(bottom));
				}
				else if(SaveMode==0){
					qint32 NGVer;
					stream >> NGVer;
					if(NGVer<0){
						return false;
					}

					// �y�[�W�ԍ�
					qint32 page;
					stream >> page;

					// �ʂ��ԍ�
					qint32 staID;
					stream >> staID;
					
					// �e���W�擾
					qint32 left,top,right,bottom;
					stream >> left >> top >> right >> bottom;

					if(left<0 || top<0 || right<0 || bottom<0){
						return false;// �����l�`�F�b�N���s
					}

					// NG�摜�̃o�C�g��
					qint32 SrcImageXLen,SrcImageYLen;
					stream >> SrcImageXLen >> SrcImageYLen;
						
					QImage image(SrcImageXLen ,SrcImageYLen ,QImage::Format_RGB32);
					QByteArray NGImageR = file.read(SrcImageXLen*SrcImageYLen);
					QByteArray NGImageG = file.read(SrcImageXLen*SrcImageYLen);
					QByteArray NGImageB = file.read(SrcImageXLen*SrcImageYLen);
					for(int y=0;y<SrcImageYLen;y++){
						QRgb	*d=(QRgb *)image.scanLine(y);
						BYTE	*R=(BYTE *)&NGImageR.data()[y*SrcImageXLen];
						BYTE	*G=(BYTE *)&NGImageG.data()[y*SrcImageXLen];
						BYTE	*B=(BYTE *)&NGImageB.data()[y*SrcImageXLen];
						for(int x=0;x<SrcImageXLen;x++){
							*d=qRgb(*R,*G,*B);
							R++;
							G++;
							B++;
							d++;
						}
					}
					JDTImage jdtParts;
						
					jdtParts.setImage(image);

					jdtParts.setPhase(phase);
					jdtParts.setPage(page);

					jdtParts.setVersion(NGVer);
					jdtParts.setStaticID(staID);

					jdtParts.setTop(top);
					jdtParts.setLeft(left);
					jdtParts.setRight(right);
					jdtParts.setBottom(bottom);


					append(jdtParts);
					loadImage.append(QString("phase=%1,page=%2,top=%3,left=%4,right=%5,bottom=%6.png")
						.arg(phase).arg(page).arg(left).arg(top).arg(right).arg(bottom));
				}
			}
		}
		return true;
	}
	return false;
}

int JDTFile::checkVer(const QString &filename) const
{
	if(TransFileHost.isEmpty()==true){
		QFile file(filename);
		return checkVer(file);
	}
	else{
		TrFile	file(filename,TransFileHost,TransFilePort);
		return checkVer(file);
	}
}
int JDTFile::checkVer(QIODevice &file) const
{
	qint32 ver = -1;
	for(int h=0;h<2;h++){
		if(file.open(QIODevice::ReadOnly)==true){
			// �t�@�C���I�[�v������
			QDataStream stream(&file);
			QStringList loadImage;

			// �o�C�g�ǂݍ��ݏ������t�ɐݒ�
			stream.setByteOrder(QDataStream::LittleEndian);

			// �o�[�W��������
			stream >> ver;
			ver = getVersion(ver);
			if(ver<1){
				return -1;
			}
			return ver;
		}
		GSleep(1000);
	}
	return -1;
}

	
void NGImageReaderOneFile::run()
{
		QString Filename;
		QList<int> IDXList;

		_setStop(false);

		Filename = m_Filename;
		IDXList = m_IDXList;

		if(Filename.isEmpty()){
			return;
		}

		if(isStop()){
			return;
		}

		m_JDTList.clear();

		for(int i=0; i<IDXList.count(); i++){
			QString repFilename = Filename;
			repFilename.replace(/**/'*', QString::number(IDXList[i]));

			if(isStop()){
				return;
			}
			if(NetDrivePath.isNull()==true || repFilename.at(0).isLetter()==false){
				JDTFile file(repFilename,TransFileHost,TransFilePort);
				m_JDTList = m_JDTList + file.getJDTItems();
			}
			/*
			else{
				QFileInfo	FInfo(repFilename);
				QString		FilePath=FInfo.absoluteFilePath().toUpper();
				QChar	drv=FilePath.at(0);
				int	DriveCode=drv.cell()-'A';
				CreateNetworkDrive(true
							,DriveCode
							,NetDrivePath	//"\\\\192.168.0.18\\Data2"
							,""
							,"");
				NetAccessor[DriveCode].Inc();

				JDTFile file(repFilename,TransFileHost,TransFilePort);
				m_JDTList = m_JDTList + file.getJDTItems();
					
				if(NetAccessor[DriveCode].Dec()==0){
					DisconnectNetworkDrive(DriveCode);
				}
			}
			*/
		}
}