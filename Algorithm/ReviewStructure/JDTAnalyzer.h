#pragma once

#include <QCoreApplication>
#include <QString>
#include <QImage>
#include <QThread>
#include <QMutex>
#include <QFile>
#include <QDebug>
#include <QRunnable>

class JDTInfo{
public:
	JDTInfo(){clear();};
	void clear(){
		m_top = -1;
		m_left = -1;
		m_right = -1;
		m_bottom = -1;
		m_phase = -1;
		m_page = -1;
		m_staticID = -1;
		m_version = -1;
	};
public:
	int phase() const { return m_phase; };
	int page() const { return m_page; };
	int staticID() const { return m_staticID; };
	int top() const { return m_top; };
	int left() const { return m_left; };
	int right() const { return m_right; };
	int bottom() const { return m_bottom; };
	int version() const { return m_version; };
	int width() const { return qAbs(m_left-m_right); };
	int height() const { return qAbs(m_top-m_bottom); };
	
	void setPhase(int phase){ m_phase = phase; };
	void setPage(int page){ m_page = page; };
	void setStaticID(int id){ m_staticID = id; };
	void setTop(int top){ m_top = top; };
	void setLeft(int left){ m_left = left; };
	void setRight(int right){ m_right = right; };
	void setBottom(int bottom){ m_bottom = bottom; };
	void setVersion(int ver){ m_version = ver; };

private:
	int m_top;
	int m_left;
	int m_right;
	int m_bottom;
	int m_phase;
	int m_page;
	int m_staticID;
	int m_version;
};

class JDTImage : public JDTInfo
{
public:
	JDTImage(){ JDTInfo::clear();};
	void clear(){
		JDTInfo::clear();
		setImage( QImage() );
		setImageExtention( QString() );
	};
public:
	QImage image() const { return m_pix; };
	QString imageExtention() const { return m_pixExtension; };
	
	void setImage(const QImage &pix){ m_pix = pix; };
	void setImageExtention(const QString &extention){ m_pixExtension = extention; };

private:
	QImage m_pix;
	QString m_pixExtension;
};

/*
// JDTファイルを解析するクラス
class	JDTFile : public QList<JDTImage>
{
public:
	JDTFile(QString &filename, int IDX=-1);
	bool isSuccess(){ return m_ok; };
	bool findImage(int top, int left, JDTImage &jdtDest);
	int getIDX(){ return m_IDX; };
	QString getFilename(){ return m_Filename; };
	bool load();
//public:
//	typedef QList<JDTImage> JDTItems;
private:
	//JDTItems NGImages;
	int m_IDX;
	bool m_ok;
	QString m_Filename;
};
*/


// JDTファイルを解析するクラス
class	JDTFile
{
	QString TransFileHost;
	int		TransFilePort;
public:
	JDTFile(const QString &filename,const QString &TransFileHost	, int TransFilePort=0);
	int count() const { return m_NGImages.count(); }
	int size() const { return count(); };
	bool isSuccess() const { return m_ok; };
	void append(JDTImage &image){
		m_NGImages.append(image);
	};
	QList<JDTImage>::const_iterator constBegin() const { return m_NGImages.constBegin(); };
	QList<JDTImage>::const_iterator constEnd() const { return m_NGImages.constEnd(); };
	bool findImage(int top, int left, JDTImage &jdtDest) const;
	QString getFilename() const { return m_Filename; };
	qint16 getVersion(qint32 verRaw) const {// 4バイトのバージョン値(もしくはLittleEndianのNG画像数下位2バイト)
		qint16 ret;
		if((verRaw & 0x80000000)!=0){// バージョン3以降
			qint16 tmp = (verRaw & 0x7fffffff);
			ret = tmp;
		}else{
			ret = 2;// バージョン2ハイブリッドNG画像フォーマット(PNG or JPG)
		}
		if(ret<0){
			return -1;
		}
		return ret; 
	};
	QList<JDTImage> getJDTItems() const { return m_NGImages; }; 

private:
	int checkVer(const QString &filename) const;// 最初の2バイトを取得してバージョンを認識
	bool analyze(const QString &filename, int version);

	bool analyze_v1(const QString &filename);
	bool analyze_v2(const QString &filename);
	bool analyze_v3(const QString &filename);
	bool analyze_v5(const QString &filename);

	bool analyze_v2(QIODevice &file);
	bool analyze_v3(QIODevice &file);
	bool analyze_v5(QIODevice &file);
	int checkVer(QIODevice &file) const;

private:
	QList<JDTImage> m_NGImages;
	bool m_ok;
	QString m_Filename;
};

//class JDTFileReader
//{
//public:
//	JDTFileReader(QString filename=""):m_Filename(filename),m_Image(){};
//
//public:
//	bool load(int top, int left);
//	void unload(void){ m_Image = QImage(); };
//	bool isLoaded(void){ return !m_Image.isNull(); };
//
//public:
//	void setFilename(QString filename){ if(m_Filename!=filename){m_Filename = filename; m_Image = QImage(); } };
//	QString filename() const { return m_Filename; };
//	QImage image() const { return m_Image; };
//
//public:
//	static QImage load(QString filename, int top, int left);
//
//private:
//	QString m_Filename;
//	QImage m_Image;
//};

//class NGImageReader : public QThread
//{
//public:
//	NGImageReader(QObject *parent=NULL):QThread(parent),m_Filename(/**/""),m_top(-1),m_left(-1),m_image(),m_mutex(){};
//	void clear(){
//		m_Filename = /**/"";
//		m_top = -1;
//		m_left = -1;
//		m_image = QImage();
//	};
//
//protected:
//	void run(){
//		QString Filename;
//		JDTInfo info;
//		int ttop,tleft;
//		{
//		QMutexLocker locker( &m_mutex );
//
//		m_info.clear();
//		Filename = m_Filename;
//		info;
//		ttop = m_top;
//		tleft = m_left;
//		}
//
//		if(Filename.isEmpty()){
//			return;
//		}
//		QFile file(Filename);
//		if(file.open(QIODevice::ReadOnly)==true){
//			// ファイルオープン成功
//			QDataStream stream(&file);
//			int ImageNumb;
//
//			stream.setByteOrder(QDataStream::LittleEndian);
//
//			stream >> ImageNumb;
//
//			if(ImageNumb<=0){
//				// NG画像枚数不明
//				file.close();
//				return;
//			}else{
//				// 画像枚数正常取得
//				for(int NGI=0; NGI<ImageNumb; NGI++){// NG画像分だけループ
//					unsigned char ver[2];
//					int page;
//					int staticID;
//					int x1,x2,y1,y2;
//					int ImageByte;
//
//					stream >> ver[0];
//					stream >> ver[1];
//					
//					// バージョン
//					int version = ((int)ver[1] << 8) + ver[0];
//					if(version < 1){// 初期バージョンは１
//						file.close();
//						return;
//					}else{
//						info.setVersion(version);
//					}
//					
//					stream >> page// ページ番号
//						>> staticID// 通し番号
//						>> x1// 左側
//						>> y1// 上側
//						>> x2// 右側
//						>> y2// 下側
//						>> ImageByte;// 画像のバイト数
//
//					//チェックとデータ格納
//					if(page<0 ||
//						staticID<0 ||
//						x1<0 ||
//						y1<0 ||
//						x2<0 ||
//						ImageByte<0){
//						// データ不一致
//						file.close();
//						return;
//					}else if(x1==ttop && y1==tleft){
//						info.setPage(page);
//						info.setStaticID(staticID);
//						info.setTop(x1);
//						info.setLeft(y1);
//						info.setRight(x2);
//						info.setBottom(y2);
//						QByteArray ary = file.read(ImageByte);
//
//						{
//						QMutexLocker locker( &m_mutex );
//						if(m_image.loadFromData(ary, /**/"PNG")==false){
//							m_image.loadFromData(ary, /**/"JPG");
//						}
//						m_info = info;
//						}
//						file.close();
//						return;
//					}else{
//						stream.skipRawData(ImageByte);
//					}
//				}
//			}
//			file.close();
//			return;
//		}else{
//			// ファイルオープン失敗
//			return;
//		}
//	};
//
//	void localLoad(){
//		QString Filename;
//		JDTInfo info;
//		int ttop,tleft;
//		{
//		QMutexLocker locker( &m_mutex );
//
//		m_info.clear();
//		Filename = m_Filename;
//		info;
//		ttop = m_top;
//		tleft = m_left;
//		}
//
//		if(Filename.isEmpty()){
//			return;
//		}
//		QFile file(Filename);
//		if(file.open(QIODevice::ReadOnly)==true){
//			// ファイルオープン成功
//			QDataStream stream(&file);
//			int ImageNumb;
//
//			stream.setByteOrder(QDataStream::LittleEndian);
//
//			stream >> ImageNumb;
//
//			if(ImageNumb<=0){
//				// NG画像枚数不明
//				file.close();
//				return;
//			}else{
//				// 画像枚数正常取得
//				for(int NGI=0; NGI<ImageNumb; NGI++){// NG画像分だけループ
//					unsigned char ver[2];
//					int page;
//					int staticID;
//					int x1,x2,y1,y2;
//					int ImageByte;
//
//					stream >> ver[0];
//					stream >> ver[1];
//					
//					// バージョン
//					int version = ((int)ver[1] << 8) + ver[0];
//					if(version < 1){// 初期バージョンは１
//						file.close();
//						return;
//					}else{
//						info.setVersion(version);
//					}
//					
//					stream >> page// ページ番号
//						>> staticID// 通し番号
//						>> x1// 左側
//						>> y1// 上側
//						>> x2// 右側
//						>> y2// 下側
//						>> ImageByte;// 画像のバイト数
//
//					//チェックとデータ格納
//					if(page<0 ||
//						staticID<0 ||
//						x1<0 ||
//						y1<0 ||
//						x2<0 ||
//						ImageByte<0){
//						// データ不一致
//						file.close();
//						return;
//					}else if(x1==ttop && y1==tleft){
//						info.setPage(page);
//						info.setStaticID(staticID);
//						info.setTop(x1);
//						info.setLeft(y1);
//						info.setRight(x2);
//						info.setBottom(y2);
//						QByteArray ary = file.read(ImageByte);
//
//						{
//						QMutexLocker locker( &m_mutex );
//						if(m_image.loadFromData(ary, /**/"PNG")==false){
//							m_image.loadFromData(ary, /**/"JPG");
//						}
//						m_info = info;
//						}
//						return;
//					}else{
//						stream.skipRawData(ImageByte);
//					}
//				}
//			}
//			file.close();
//		}else{
//			// ファイルオープン失敗
//			return;
//		}
//	}
//public:
//	QImage image(){
//		// ダミー画像が設定されていれば返す
//		if(m_dummy.isNull()==false){
//			return m_dummy;
//		}
//
//		// 読み込み中のときは待つ
//		if(isRunning()==true){
//			while(!isFinished()){
//				qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);
//			}
//		}
//
//		// 読み込んだ結果を確認
//		bool isNull;
//		{
//			QMutexLocker locker( &m_mutex );
//			isNull = m_image.isNull();
//		}
//
//		//// スレッド生成失敗の場合はスレッドを再生成
//		//if(isFinished()==false && isNull==true){
//		//	start();
//		//	while(!isFinished()){
//		//		qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);
//		//	}
//		//}
//
//		//// スレッドの生成が失敗したか、読み込み失敗しているときローカルスレッドで取得
//		//{
//		//	QMutexLocker locker( &m_mutex );
//		//	isNull = m_image.isNull();
//		//}
//
//		// 読み込み失敗のときはメインスレッドで読み込み
//		if(isNull==true){
//			localLoad();
//		}
//
//		QMutexLocker locker( &m_mutex );
//		return m_image;
//	};
//	QString filename(){ QMutexLocker locker(&m_mutex); return m_Filename; };
//	QPoint pos(){ QMutexLocker locker(&m_mutex); return QPoint(m_top, m_left); };
//	JDTInfo info(){ QMutexLocker locker(&m_mutex); return m_info; };
//	void setDummyImage(QImage img){ m_dummy = img; };
//
//	void setFilename(QString filename_){
//		m_Filename = filename_;
//	};
//	void setPos(int top, int left){
//		m_top = top;
//		m_left = left;
//	};
//	void setPos(QPoint p){
//		setPos(p.x(), p.y());
//	}
//
//private:
//	QString m_Filename;
//	int m_top, m_left;
//	JDTInfo m_info;
//	QImage m_image;
//	QImage m_dummy;
//	QMutex m_mutex;
//};

#ifndef SP
#endif

// NG画像を読み込むスレッド
// ファイルにおいて1対1のスレッドを生成する
// 終了条件などは isFinished() や、実行中かどうかは isRunnning() で認識する
// mutexは使用せず、上記関数で保守する
// ファイル名を指定している場合、そこまで到達することに必要なpageは検索に必要な情報から省略
class NGImageReaderOneFile : public QThread
{
	QString NetDrivePath;
	QString TransFileHost;
	int		TransFilePort;

public:
	NGImageReaderOneFile(const QString &_NetDrivePath 
						,const QString &_TransFileHost
						, int _TransFilePort
						,QObject *parent)
						:QThread(parent)
						,NetDrivePath(_NetDrivePath)
						,TransFileHost(_TransFileHost)
						,TransFilePort(_TransFilePort)
						,m_Filename(/**/"")
						,m_JDTList()
						{};
	void clear(){
		m_Filename = /**/"";
		m_JDTList.clear();
	};

protected:
	void run();

public:
	void localLoad(void){
		QString Filename;
		QList<int> IDXList;
		JDTImage jdtImg;

		Filename = m_Filename;
		IDXList = m_IDXList;

		if(Filename.isEmpty()){
			return;
		}

		for(int i=0; i<IDXList.count(); i++){
			QString repFilename = Filename;
			repFilename.replace(/**/'*', QString::number(IDXList[i]));

			JDTFile file(repFilename,TransFileHost,TransFilePort);

			if(file.isSuccess()){
				m_JDTList.clear();
				for(QList<JDTImage>::ConstIterator cit=file.constBegin(); cit!=file.constEnd(); cit++){
					m_JDTList.append(*cit);
				}
			}


			//QFile file(repFilename);
			//if(file.open(QIODevice::ReadOnly)==true){
			//	// ファイルオープン成功
			//	QDataStream stream(&file);
			//	int ImageNumb;

			//	stream.setByteOrder(QDataStream::LittleEndian);

			//	stream >> ImageNumb;

			//	if(ImageNumb<=0){
			//		// NG画像枚数不明
			//		file.close();
			//		continue;
			//	}else{
			//		// 画像枚数正常取得
			//		for(int NGI=0; NGI<ImageNumb; NGI++){// NG画像分だけループ
			//			unsigned char ver[2];
			//			int page;
			//			int staticID;
			//			int x1,x2,y1,y2;
			//			int ImageByte;

			//			stream >> ver[0];
			//			stream >> ver[1];
			//		
			//			// バージョン
			//			int version = ((int)ver[1] << 8) + ver[0];
			//			if(version < 1){// 初期バージョンは１
			//				file.close();
			//				continue;
			//			}else{
			//				info.setVersion(version);
			//			}
			//		
			//			stream >> page// ページ番号
			//				>> staticID// 通し番号
			//				>> x1// 左側
			//				>> y1// 上側
			//				>> x2// 右側
			//				>> y2// 下側
			//				>> ImageByte;// 画像のバイト数

			//			//チェックとデータ格納
			//			if(page<0 ||
			//				staticID<0 ||
			//				x1<0 ||
			//				y1<0 ||
			//				x2<0 ||
			//				ImageByte<0){
			//				// データ不一致
			//				file.close();
			//				break;
			//			}else{
			//				info.setPage(page);
			//				info.setStaticID(staticID);
			//				info.setTop(x1);
			//				info.setLeft(y1);
			//				info.setRight(x2);
			//				info.setBottom(y2);
			//				QByteArray ary = file.read(ImageByte);

			//				QImage image;
			//				if(image.loadFromData(ary, /**/"PNG")==false){
			//					image.loadFromData(ary, /**/"JPG");
			//				}

			//				{
			//				QMutexLocker locker( &m_mutex );
			//				m_imageList.append(image);
			//				m_infoList.append(info);
			//				}
			//			}
			//		}
			//	}
			//}else{
			//	// ファイルオープン失敗
			//}
		}
	}
	void stop(){ _setStop(true); };
	bool isStop() const { return m_stop; };

public:
	void setDummyImage(QImage img){ m_dummy = img; };
	void setFilename(const QString &Filename)
		{ 
			m_Filename = Filename;
		};
	void setIDXList(const QList<int> &list){ m_IDXList = list; };

	QImage getImage(int left, int top, int phase){
		// ダミー画像が設定されていれば返す
		if(m_dummy.isNull()==false){
			return m_dummy;
		}

		// 読み込み中のときは待つ
		if(isRunning()==true){
			while(!isFinished()){
				qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);
			}
		}

		// 読み込み失敗のときはメインスレッドで読み込み
		if(m_JDTList.isEmpty()==true){
			localLoad();
		}

		QImage ret;

		for(int i=0; i<m_JDTList.count(); i++){
			if(m_JDTList[i].top()==top && m_JDTList[i].left()==left){
				if(m_JDTList[i].phase()!=-1 && m_JDTList[i].phase()!=phase){
					continue;
				}else{
					ret = m_JDTList[i].image();
					break;
				}
			}
		}
		return ret;
	};
	QString filename() const { return m_Filename; };
	QList<int> IDXList() const { return m_IDXList; };
	QList<JDTImage> jdtList() const { return m_JDTList; };

private:
	void _setStop(bool flag){ m_stop = flag; };
	void _safetyTerminate(){
		if(isRunning()==true){
			terminate();
			while(isRunning()==true)
				msleep(1);
		}
	};
	void _safetyStop(){
		if(isRunning()==true){
			stop();
			while(isFinished()==false)
				msleep(1);
		}
	};

private:
	QString m_Filename;
	QList<int> m_IDXList;
	QList<JDTImage> m_JDTList;
	QImage m_dummy;
	volatile bool m_stop;
};
