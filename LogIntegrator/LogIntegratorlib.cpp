#include "LogIntegratorlib.h"
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>

void clsLogIntegratorLib::setPath1(QString src) {
	if ( src != "" ) Path1 = src;
}
void clsLogIntegratorLib::setPath2(QString src) {
	if ( src != "" ) Path2 = src;
}

void clsLogIntegratorLib::setOutPath(QString src) {
	if ( src != "" ) OutPath = src;
}

void clsLogIntegratorLib::setLotNo(QString src) {
	if ( src != "" ) LotNo = src;
}

void clsLogIntegratorLib::setBaseNo(QString src) {
	if ( src != "" ) BaseNo = src;
}

bool clsLogIntegratorLib::makeLogIntegrate()
{
	if ( Path1 == "" || Path2 == "" )
		return false;
	if ( OutPath == "" )
		return false;
	if( searchSaveDate() == false )
		return false;

	LogList.RemoveAll();
	QString fPath;

	//処理中プログレスバーを更新
	emit UpdateSignal(40);

	for( int i=0; i<SaveDateListPath1.size(); i++ ){
		if ( readBase(Path1+"/"+SaveDateListPath1.at(i)+"/"+LotNo) == false ){
			return false;
		}
	}

	//処理中プログレスバーを更新
	emit UpdateSignal(60);

	for( int i=0; i<SaveDateListPath2.size(); i++ ){
		if ( readBase(Path2+"/"+SaveDateListPath2.at(i)+"/"+LotNo) == false ){
			return false;
		}
	}

	//処理中プログレスバーを更新
	emit UpdateSignal(80);

	for( clsLogItem *rec=LogList.GetFirst(); rec!=NULL; rec=rec->GetNext() ){
		if( rec->AnotherItem == NULL ){
			continue;
		}
		rec->calcNgCnt();
		rec->AnotherItem->calcNgCnt();
		rec->IntegrateProperty(rec->AnotherItem);
	}

	//処理中プログレスバーを更新
	emit UpdateSignal(100);

	return true;
}

bool clsLogIntegratorLib::searchSaveDate(void)
{
	if ( Path1 == "" )
		return false;
	QStringList DateList;
	if ( (DateList = searchLot( Path1 )).size() == 0 ){
		QMessageBox::warning( NULL, QString("エラー"), QString("上面HDにロット番号「")+LotNo+QString("」のフォルダが見つかりませんでした。ロット番号やファイルなどを確認してください。処理を中止します。") );
		return false;
	}else{
		SaveDateListPath1 = DateList;
	}

	if ( Path2 == "" )
		return false;
	if ( (DateList = searchLot( Path2 )).size() == 0 ){
		QMessageBox::warning( NULL, QString("エラー"), QString("下面HDにロット番号「")+LotNo+QString("」のフォルダが見つかりませんでした。ロット番号やファイルなどを確認してください。処理を中止します。") );
		return false;
	}else{
		SaveDateListPath2 = DateList;
	}

	return true;
}

QStringList clsLogIntegratorLib::searchLot(QString fPath)
{
	QStringList Result;
	QDir rootdir(fPath);
	if ( rootdir.exists() == false )
		return Result;
	QStringList filters;
	filters << "????????";	//yyyyMMdd
	rootdir.setNameFilters(filters);
	QFileInfoList subdirs = rootdir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Reversed | QDir::Name );
	for( int i=0; i<subdirs.size(); i++ ) {
		QFileInfo fInfo = subdirs.at(i);
		if( QDir(fInfo.filePath()).cd(LotNo) == true )
			Result << fInfo.fileName();
	}
	return Result;
}

bool clsLogIntegratorLib::outLog() {
	OutTime = QDateTime::currentDateTime().toString("HHmmss");
	if ( writeLogLoop(OutPath) == false )
		return false;
	return true;
}

bool clsLogIntegratorLib::errChk() {
	if ( ErrList.GetNumber() > 0 ) {
		dialog.setError(ErrList);
		return false;
	}
	return true;
}

void clsLogIntegratorLib::showErrDialog() {
	dialog.setSuccess(SuccList);
	dialog.show();
	dialog.activateWindow();
}

void clsLogIntegratorLib::ClearErrDialogLogs(void)
{
	LogList.RemoveHead(LogList.GetNumber());
	ErrList.RemoveAll();
	SuccList.RemoveAll();
	dialog.ClearLogs();
	dialog.setSuccess(SuccList);
	dialog.setError(ErrList);
}

//ErrDialogにエラーの発生したログがあればデータを退避する
void clsLogIntegratorLib::makeErrLog() {
	if(dialog.IsErrLog()==true){
		AllErrList+=ErrList;
	}
}

//ErrDialogにエラーの発生したログを表示する
void clsLogIntegratorLib::showErrLog() {
	dialog.setError(AllErrList);
	dialog.show();
	dialog.activateWindow();
}

//ErrDialogにエラーの発生したログを表示する
bool clsLogIntegratorLib::IsErrLog() {
	if(AllErrList.GetNumber()>0){
		return true;
	}
	return false;
}

void clsLogIntegratorLib::ClearErrLog()
{
	AllErrList.RemoveAll();
}

bool clsLogIntegratorLib::outErrLog(QString Date) {
	OutTime = QDateTime::currentDateTime().toString("HHmmss");
	if ( writeErrLogLoop(OutPath,Date) == false )
		return false;
	return true;
}

//パスの入った文字列fPath内の一階層目のディレクトリ一覧を取得し、一つ一つメンバ変数LotNoに入れ、readBaseにパスを渡す
//常にtrueが返ってくる
bool clsLogIntegratorLib::readLot(QString fPath) {
	QDir dir(fPath);
	QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for( int i=0; i<list.size(); i++ ) {
		QFileInfo fInfo = list.at(i);
		LotNo = fInfo.fileName();
		if ( readBase(fInfo.filePath()) == false ) {
			continue;
		}
	}
	return true;
}

//パスの入った文字列fPath内の一階層目のディレクトリ一覧を取得し、一つ一つメンバ変数BaseNoに入れ、readBaseにパスを渡す
//常にtrueが返ってくる
bool clsLogIntegratorLib::readBase(QString fPath) {
	QDir dir(fPath);
	QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	int ListSize=list.size();
//	double ProcessTimeCalc=100.0/ListSize;
	for( int i=0; i<ListSize; i++ ) {
//		//処理中プログレスバーを更新
//		emit UpdateSignal(i*ProcessTimeCalc);

		QFileInfo fInfo = list.at(i);
		BaseNo = fInfo.fileName();
		if ( readLog(fInfo.filePath()) == false ) {
			continue;
		}
	}
	return true;
}

bool clsLogIntegratorLib::readLog(QString fPath) {
	QDir dir(fPath);
	QStringList filter;
	filter << "??????????*_?_????_??????.csv";	//ロット番号（10桁orそれ以上）
	dir.setNameFilters(filter);
	QFileInfoList list = dir.entryInfoList();
	for( int i=0; i<list.size(); i++ ) {
		QFileInfo fInfo = list.at(i);
		QString fnam = fInfo.filePath();
		QFile file(fnam);
		if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
			return false;
		}
		QTextStream in(&file);
		clsLogItem *item = new clsLogItem();
		item->SetPropertiesFromFileName(fInfo.fileName());
		while( !in.atEnd() ) {
			QString buf = in.readLine();
			item->SetProperty(buf);
		}
		file.close();

		bool addFlg = true;
		clsLogItem *src = LogList.GetFirst();
		for( int j=0; j<LogList.GetNumber(); j++ ) {
			if( src->chkOutSame(*item) == true ) {
				src->SetAnotherItem(item);
				addFlg = false;
				break;
			}
			src = src->GetNext();
		}
		if ( addFlg == true ) {
			LogList.AppendList(item);
		} else {
			delete(item);
		}
	}

	return true;
}

//書き込みしているところの本体
bool clsLogIntegratorLib::writeLogLoop(QString fPath) {
	if ( fPath == "" ) {
		return false;
	}
	clsLogItem *cur = new clsLogItem();
	*cur = *LogList.GetFirst();
	//SaveDate = cur->SaveDate;
	LotNo    = cur->LotNo;
	BaseNo   = cur->BaseNo;

	QString filePath = makeOutLogFileName(fPath);
	if ( filePath == "" ) {
		return false;
	}
	file.setFileName(filePath);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) {
		QMessageBox::critical(NULL, QString("エラー"), QString("以下のファイルの出力に失敗しました。他のアプリケーションで使用されていないかどうかなどを確認してください。処理を中止します。\n") + filePath );
		return false;
	}
	QString fnam = file.fileName();
	writeLogHeader();
	LogList.sort();		//BaseNoでLogListをソート
	for( clsLogItem *rec=LogList.GetFirst(); rec != NULL; rec=rec->GetNext() ) {
		if ( cur->chkOutSame(*rec) != true ) {
			*cur = *rec;
			LotNo    = cur->LotNo;
			BaseNo   = cur->BaseNo;
		}
		if ( rec->AnotherItem == NULL ) {
			addErrList(rec);
		} else {
			writeLog(rec);
			addSuccList(rec);
		}
	}
	file.close();
	return true;
}

void clsLogIntegratorLib::addErrList(clsLogItem *src) {
	clsLogItem *rec = new clsLogItem();
	*rec = *src;
	ErrList.AppendList(rec);
}

void clsLogIntegratorLib::addSuccList(clsLogItem *src) {
	clsLogItem *rec = new clsLogItem();
	*rec = *src;
	SuccList.AppendList(rec);
}

//書き込みしているところの本体（エラーログ）
bool clsLogIntegratorLib::writeErrLogLoop(QString fPath,QString Date) {
	if ( fPath == "" ) {
		return false;
	}

	QString filePath = makeOutErrLogFileName(fPath,Date);
	if ( filePath == "" ) {
		return false;
	}
	file.setFileName(filePath);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) {
		QMessageBox::critical(NULL, QString("エラー"), QString("以下のファイルの出力に失敗しました。他のアプリケーションで使用されていないかどうかなどを確認してください。処理を中止します。\n") + filePath );
		return false;
	}
	QString fnam = file.fileName();
	writeErrLogHeader();
	for( clsLogItem *rec=AllErrList.GetFirst(); rec != NULL; rec=rec->GetNext() ) {
		writeErrLog(rec);
	}
	file.close();
	return true;
}

bool clsLogIntegratorLib::writeLog(clsLogItem *rec) {
	QTextStream out(&file);

	QString buf;
	buf  = "\""+rec->Hinsyu+"\",";
	buf += rec->LotNo+",";
	buf += rec->BaseNo+",";
	buf += rec->SaveDate+",";
	buf += rec->SaveTime+",";
	buf += "\""+rec->HDName+"\",";
	buf += QString::number(rec->cntNg());
	int cnt = rec->NgLst.GetNumber();
	clsLogResult *ngrec = rec->NgLst.GetFirst();
	for( int j=0; j<cnt; j++ ) {
		buf += ","+ngrec->NgResult;
		ngrec = ngrec->GetNext();
	}
	buf += "\n";
	out << buf;
	rec = rec->GetNext();

	return true;
}

bool clsLogIntegratorLib::writeErrLog(clsLogItem *rec) {
	QTextStream out(&file);

	QString buf;
	buf  = "\""+rec->Hinsyu+"\",";
	buf += rec->LotNo+",";
	buf += rec->BaseNo+",";
	buf += rec->SaveDate+",";
	buf += rec->SaveTime+",";
	buf += "\""+rec->HDName+"\",";
	buf += "\n";
	out << buf;
//	rec = rec->GetNext();

	return true;
}

bool clsLogIntegratorLib::writeLogHeader() {
	QString fnam = file.fileName();
	QTextStream out(&file);
	QString buf = QString("品種,ロット番号,基板番号,保存年月日,保存時刻,HD名称,NG個片数");
	for( int i=1; i<=MAX_KOHENNO; i++ ) {
		buf += QString(",個片結果")+QString::number(i);
	}
	buf += "\n";
	out << buf;

	return true;
}

QString clsLogIntegratorLib::makeOutLogFileName(QString fPath)
{
	QString LatestSaveDate = SaveDateListPath1.takeFirst();
	QStringList SaveDateList( SaveDateListPath1 + SaveDateListPath2 );
	for( int i=0; i<SaveDateList.size(); i++ )
		if( SaveDateList.at(i).compare(LatestSaveDate) > 0 )
			LatestSaveDate = SaveDateList.at(i);

	QString DirPath = fPath + "/" + LatestSaveDate;
	ForceDirectories( DirPath );
	if( QDir(DirPath).exists() == false )
		return "";

	return( DirPath + "/" + LotNo + "_"+ OutTime + ".csv" );
}

QString clsLogIntegratorLib::makeOutErrLogFileName(QString fPath,QString Date)
{
	QString DirPath = fPath + "/" + QString("統合失敗フォルダ");
	ForceDirectories( DirPath );
	if( QDir(DirPath).exists() == false )
		return "";

	return( DirPath + "/" + Date + "_"+ OutTime + ".csv" );
}

bool clsLogIntegratorLib::writeErrLogHeader() {
	QString fnam = file.fileName();
	QTextStream out(&file);
	QString buf = QString("品種,ロット番号,基板番号,保存日付,保存時間,保存HD名,読み込んだログの数");
	buf += "\n";
	out << buf;

	return true;
}

void clsLogItem::InitializeProperties(void)
{
	Hinsyu = LotNo = BaseNo = SaveDate = SaveTime = HDName = NgNo = NgResult = "";
	UpperOrLower = 0;	// 0, magic number, means this surface type is undefined
}

bool clsLogItem::SetPropertiesFromFileName(QString filename)
{
	QRegularExpression regexp("(..........)_(.)_(....)_(......)\\.csv");
	if( regexp.indexIn(filename) == -1 )
		return false;
	QString SurfaceType = regexp.capturedTexts()[2];
	if( SurfaceType == "B" )	// this code below uses magic numbers
		UpperOrLower = 1;
	else if( SurfaceType == "F" )
		UpperOrLower = 2;
	else
		UpperOrLower = 0;

	return true;
}

bool clsLogItem::SetProperty(QString buf)
{
	if ( buf.isEmpty() || buf.isNull() ) {
		return true;
	}
	QStringList lst = buf.split(",");
	if(lst.size() <= 1){
		//QMessageBox::critical(NULL, QString("エラー"), QString("ログファイルの読み込みに失敗したため、処理を中止します。以下の項目でエラーが発生しました。\n") + buf);
		return false;
	}
	QString itm = lst.at(0);
	QString val = lst.at(1);
	if ( lst.size() > 2 ) {
		for( int i=2; i<lst.size(); i++ )
			val += ","+lst.at(i);
	}
	if ( itm == QString("品種") ) {
		Hinsyu = val;
	}
	if ( itm == QString("ロット番号") ) {
		LotNo = val;
	}
	if ( itm == QString("基板番号") ) {
		BaseNo = val;
	}
	if ( itm == QString("保存年月日") ) {
		SaveDate = val;
	}
	if ( itm == QString("保存時刻") ) {
		SaveTime = val;
	}
	if ( itm == QString("HD名") ) {
		HDName = val;
	}
	if ( itm == QString("個片番号") ) {
		NgNo = val;
	}
	if ( itm == QString("個片結果") ) {
		NgResult = val;
	}
	return true;
}

void clsLogItem::calcNgCnt() {
	QStringList lstNgNo = NgNo.split(",");
	QStringList lstRes  = NgResult.split(",");
	QMap<QString, QString> MapNgLst;
	for( int i=0; i<lstNgNo.size(); i++ ){
		MapNgLst.insert(lstNgNo[i], lstRes[i]);
	}
	NgLst.RemoveAll();
	for( int i=1; i<=MAX_KOHENNO; i++ ){
		clsLogResult *rec = new clsLogResult();
		rec->NgNo     = QString::number(i);
		rec->NgResult = MapNgLst.value(QString(i<10?"0":"")+QString::number(i));
		NgLst.AppendList(rec);
	}
}

//引数srcがthisにとって統合するログにふさわしい上下・日時のときtrue, それ以外はfalseを返す
bool clsLogItem::SetAnotherItem(clsLogItem *src)
{
	//上（下）面同士を統合しようとしているとき
	const QString DateTimeFormat = "yyyyMMddhhmmss";
	if( this->UpperOrLower == src->UpperOrLower ){
		if( QDateTime::fromString(SaveDate+SaveTime, DateTimeFormat) <= QDateTime::fromString(src->SaveDate+src->SaveTime, DateTimeFormat) ){
			if(this->AnotherItem!=NULL){	//同じ面なら、後に生成された方のログsrcを使用する
				clsLogItem *AnotherItemOrg = this->AnotherItem;
				*src = *AnotherItem;
				*this = *AnotherItem;
			}else{
				*this = *src;
			}
		}
		return false;
	}else if( AnotherItem != NULL ){
		if( *AnotherItem == *src )
			return false;
		if( QDateTime::fromString(src->SaveDate+src->SaveTime, DateTimeFormat) <= QDateTime::fromString(AnotherItem->SaveDate+AnotherItem->SaveTime, DateTimeFormat) ){
			return false;	//AnotherItemの方が後に生成されているとき
		}
	}
	//統合したものを記憶しておく
	if(AnotherItem==NULL)
		AnotherItem = new clsLogItem;
	*AnotherItem = *src;
	return true;
}

//統合関数
bool clsLogItem::IntegrateProperty(clsLogItem *src)
{
	//NG個片数の統合
	for( clsLogResult *cur=src->NgLst.GetFirst(); cur!=NULL; cur=cur->GetNext() ) {
		bool flg = true;	//whether to append this item
		for( clsLogResult *NgRec=NgLst.GetFirst(); NgRec!=NULL; NgRec=NgRec->GetNext() ) {
			if ( NgRec->NgNo == cur->NgNo ) {
				if ( cur->NgResult == "NG" ) {
					if(NgRec->NgResult != "-") {
						NgRec->NgResult = "NG";
					}
				}
				else if ( cur->NgResult == "-" ) {
					NgRec->NgResult = "-";
				}
				flg = false;
				break;
			}
		}
		if ( flg == true ) {
			clsLogResult *p = new clsLogResult();
			*p = *cur;
			NgLst.AppendList(p);
		}
	}
	NgLst.sort();

	//保存日時の統合
	//必ず下流側を時間に設定する
	if(UpperOrLower==1){
	//if( (this->SaveDate+this->SaveTime).compare(src->SaveDate+src->SaveDate) > 0){
		this->SaveDate = src->SaveDate;
		this->SaveTime = src->SaveTime;
	}

	//HD名称の統合
	QStringList HDNames;
	if( HDName.isEmpty() == false )
		HDNames += HDName.split(",");
	if( src->HDName.isEmpty() == false )
		HDNames += src->HDName.split(",");
	for( int i=0; i<HDNames.size(); i++ )
		HDNames[i] = HDNames[i].replace( QRegularExpression( "(HD[^\\-]+)-.+", Qt::CaseSensitive), "\\1" );
	//重複の削除
	HDNames.sort();
	{
		int i=0;
		while( i+1<HDNames.size() ){
			if( HDNames.at(i) == HDNames.at(i+1) )
				HDNames.removeAt(i+1);
			else
				i++;
		}
	}
	HDName = HDNames.join(",");

	return true;
}

clsLogItem &clsLogItem::operator =(clsLogItem &src) {
	Hinsyu = src.Hinsyu;
	LotNo  = src.LotNo;
	BaseNo = src.BaseNo;
	SaveDate = src.SaveDate;
	SaveTime = src.SaveTime;
	HDName = src.HDName;
	NgNo = src.NgNo;
	NgResult = src.NgResult;
	AnotherItem = src.AnotherItem;

	NgLst.RemoveAll();
	for( clsLogResult *cur=src.NgLst.GetFirst(); cur!=NULL; cur=cur->GetNext() ) {
		clsLogResult *nrec = new clsLogResult;
		*nrec = *cur;
		NgLst.AppendList(nrec);
	}
	return *this;
}

clsLogResult &clsLogResult::operator =(clsLogResult &src) {
	NgNo     = src.NgNo;
	NgResult = src.NgResult;
	return *this;
}

void clsLogResultContainer::sort()
{
	clsLogResult *a = GetFirst();
	if ( a == NULL ) return;
	if ( a->GetNext() == NULL ) return;
	bool flg = false;
	while( 1 ) {
		flg = false;
		clsLogResult *cur = GetFirst();
		while( 1 ) {
			clsLogResult *nxt = cur->GetNext();
			if ( nxt == NULL ) break;

			if ( cur->NgNo.toInt() > nxt->NgNo.toInt() ) {
				flg = true;
				Swap(cur,nxt);
			}
			cur = cur->GetNext();
			if ( cur == NULL ) break;
		}
		if ( flg == false ) break;
	}
}

int clsLogResultContainer::cntNg()
{
	clsLogResult *cur = GetFirst();
	int cnt = 0;
	for( int i=0; i<GetNumber(); i++ ) {
		if ( cur->NgResult == "NG" ) {
			cnt ++;
		}
		cur = cur->GetNext();
	}
	return cnt;
}

bool clsLogItem::operator==(clsLogItem &src) {
//	if ( Hinsyu   != src.Hinsyu   ) return false;
	if ( LotNo    != src.LotNo    ) return false;
	if ( BaseNo   != src.BaseNo   ) return false;
	if ( SaveDate != src.SaveDate ) return false;
	if ( SaveTime != src.SaveTime ) return false;
//	if ( HDName   != src.HDName   ) return false;
	return true;
}

bool clsLogItem::chkOutSame(clsLogItem &src) {
//	if ( Hinsyu   != src.Hinsyu   ) return false;
	if ( LotNo    != src.LotNo    ) return false;
	if ( BaseNo   != src.BaseNo   ) return false;
//	if ( SaveDate != src.SaveDate ) return false;
//	if ( HDName   != src.HDName   ) return false;
	return true;
}

void clsLogItemContainer::sort() {
	clsLogItem *a = GetFirst();
	if ( a == NULL ) return;
	if ( a->GetNext() == NULL ) return;
	bool flg = false;
	while( 1 ) {
		flg = false;
		clsLogItem *cur = GetFirst();
		while( 1 ) {
			clsLogItem *nxt = cur->GetNext();
			if ( nxt == NULL ) break;

			if ( cur->BaseNo.toInt() > nxt->BaseNo.toInt() ) {
				flg = true;
				Swap(cur,nxt);
			}
			cur = cur->GetNext();
			if ( cur == NULL ) break;
		}
		if ( flg == false ) break;
	}
}
