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
		m_ok = analyze_v1(filename);// バージョン1用
		break;
	case 2:
		m_ok = analyze_v2(filename);// バージョン2用
		break;
	case 3:
	case 4:
		m_ok = analyze_v3(filename);// バージョン3用
		break;
	case 5:
		m_ok = analyze_v5(filename);// バージョン3用
		break;
	default:
		return;// 無効バージョン
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
		// ファイルオープン成功
		QDataStream stream(&file);
		int ImageNumb;

		stream.setByteOrder(QDataStream::LittleEndian);

		stream >> ImageNumb;

		if(ImageNumb<=0){
			// NG画像枚数不明
			return false;
		}else{
			// 画像枚数正常取得
			//QStringList loadImage;
			for(int NGI=0; NGI<ImageNumb; NGI++){// NG画像分だけループ
				unsigned char ver[2];
				int page;
				int staticID;
				int x1,x2,y1,y2;
				int ImageByte;

				JDTImage jdtParts;

				stream >> ver[0];
				stream >> ver[1];
					
				// バージョン
				int version = ((int)ver[1] << 8) + ver[0];
				if(version>=1 && version<=2){// 初期バージョンは1、現在のバージョンは2まで
					jdtParts.setVersion(version);
				}else{// バージョンエラー 
					return false;
				}
					
				stream >> page// ページ番号
					>> staticID// 通し番号
					>> x1// 左側
					>> y1// 上側
					>> x2// 右側
					>> y2// 下側
					>> ImageByte;// 画像のバイト数

				//チェックとデータ格納
				if(page<0 ||
					staticID<0 ||
					x1<0 ||
					y1<0 ||
					x2<0 ||
					y2<0 ||
					ImageByte<0){
					// データ不一致
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
					if(pix.loadFromData(pixData, /**/"PNG")==true){// バージョン2はPNG画像
						jdtParts.setImageExtention(/**/"PNG");
					}else{
						if(pix.loadFromData(pixData, /**/"JPG")==true){// バージョン1はJPG画像
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
		// ファイルオープン失敗
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

		// ファイルオープン成功
		QDataStream stream(&file);
		qint32 ver;
		QStringList loadImage;

		// バイト読み込み順序を逆に設定
		stream.setByteOrder(QDataStream::LittleEndian);

		// バージョン情報
		stream >> ver;// 2 2

		ver = getVersion(ver);
		if(ver<0){
			return false;
		}

		// フェイズ数
		qint32 phaseNumb;
		stream >> phaseNumb;// 4 6

		if(phaseNumb<=0){
			return false;// フェイズ数チェック失敗
		}

		// Phaseデータ構造
		for(qint32 phase_cnt=0; phase_cnt<phaseNumb; phase_cnt++){
			// バージョン取得
			qint32 PhaseVer;
			stream >> PhaseVer;// 2 8
			if(PhaseVer<0){
				return false;
			}

			// フェイズ番号
			qint32 phase;
			stream >> phase;// 4 12

			// NG画像個数
			qint32 NGImageNumb;
			stream >> NGImageNumb;// 4 16

			// NG画像データ構造
			for(int NGCnt=0; NGCnt<NGImageNumb; NGCnt++){
				// バージョン取得
				qint32 NGVer;
				stream >> NGVer;
				if(NGVer<0){
					return false;
				}

				// ページ番号
				qint32 page;
				stream >> page;

				// 通し番号
				qint32 staID;
				stream >> staID;
				
				// 各座標取得
				qint32 left,top,right,bottom;
				stream >> left >> top >> right >> bottom;

				if(left<0 || top<0 || right<0 || bottom<0){
					return false;// 正常値チェック失敗
				}

				// NG画像のバイト数
				qint32 ImgSize;
				stream >> ImgSize;
						
				// NG画像読み込み
				QByteArray NGImage = file.read(ImgSize);
				QImage image;
				if(image.loadFromData(NGImage, "PNG")==false){// PNGで読み込み
					image.loadFromData(NGImage, "JPG");// 出来なければJPGで再読み込み
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

		// ファイルオープン成功
		QDataStream stream(&file);
		qint32 ver;
		QStringList loadImage;

		// バイト読み込み順序を逆に設定
		stream.setByteOrder(QDataStream::LittleEndian);

		// バージョン情報
		stream >> ver;// 2 2

		ver = getVersion(ver);
		if(ver<0){
			return false;
		}

		// フェイズ数
		qint32 phaseNumb;
		stream >> phaseNumb;// 4 6

		if(phaseNumb<=0){
			return false;// フェイズ数チェック失敗
		}

		// Phaseデータ構造
		for(qint32 phase_cnt=0; phase_cnt<phaseNumb; phase_cnt++){
			// バージョン取得
			qint32 PhaseVer;
			stream >> PhaseVer;// 2 8
			if(PhaseVer<0){
				return false;
			}

			// フェイズ番号
			qint32 phase;
			stream >> phase;// 4 12

			int16	SaveMode;
			stream >> SaveMode;

			// NG画像個数
			qint32 NGImageNumb;
			stream >> NGImageNumb;// 4 16

			// NG画像データ構造
			for(int NGCnt=0; NGCnt<NGImageNumb; NGCnt++){
				// バージョン取得
				if(SaveMode==1){
					qint32 NGVer;
					stream >> NGVer;
					if(NGVer<0){
						return false;
					}

					// ページ番号
					qint32 page;
					stream >> page;

					// 通し番号
					qint32 staID;
					stream >> staID;
					
					// 各座標取得
					qint32 left,top,right,bottom;
					stream >> left >> top >> right >> bottom;

					if(left<0 || top<0 || right<0 || bottom<0){
						return false;// 正常値チェック失敗
					}

					// NG画像のバイト数
					qint32 ImgSize;
					stream >> ImgSize;
							
					// NG画像読み込み
					QByteArray NGImage = file.read(ImgSize);
					QImage image;
					if(image.loadFromData(NGImage, "PNG")==false){// PNGで読み込み
						image.loadFromData(NGImage, "JPG");// 出来なければJPGで再読み込み
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

					// ページ番号
					qint32 page;
					stream >> page;

					// 通し番号
					qint32 staID;
					stream >> staID;
					
					// 各座標取得
					qint32 left,top,right,bottom;
					stream >> left >> top >> right >> bottom;

					if(left<0 || top<0 || right<0 || bottom<0){
						return false;// 正常値チェック失敗
					}

					// NG画像のバイト数
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
			// ファイルオープン成功
			QDataStream stream(&file);
			QStringList loadImage;

			// バイト読み込み順序を逆に設定
			stream.setByteOrder(QDataStream::LittleEndian);

			// バージョン情報
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