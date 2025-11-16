#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

#define ToStr(x) #x

// 初期化
ReviewStructureProperty::PropertyBase(void)
	:AbstructProperty()
{
	initialize();
}

void ReviewStructureProperty::initialize()
{
	// ソート指定
	NGNailListSortOrder = Review::OrderOfSortNG::_Order_YLesser;
	HistoryListSortOrder = Review::OrderOfSortHistory::_Order_InspectionIDGreater;
	
	// NG画像保存のフォーマット
	SaveNGImageFileNameFormat = /**/"%m-%M/%l/%i/%S/%n-%N.png";

	// NG画像の先読み込み数を決定する数値
	// 現在履歴からこの前後だけ先読み込みする
	PreLoadNGImageLength = 4;

	// XMLサーバーへのアクセス用アドレスとポート番号
	XMLServerIPAddress	= /**/"localhost";
	XMLServerPortNo		= 12345;
	NGImagePath			= /**/"\\\\192.168.0.8\\Data2";

	SkipMasterImageRate = 0;
	VRSOperationEnable	= false;
	CSVUnitMM			=false;
	CSVOffsetX			=0;
	CSVOffsetY			=0;
	CSVReverseX			=false;
	CSVReverseY			=false;
	CSVMagnificationX	=1.0;
	CSVMagnificationY	=1.0;
}

// ベース名
QString ReviewStructureProperty::baseName() const
{
	return /**/"ReviewProperty";
}

// セクション名
QString ReviewStructureProperty::sectionName() const
{
	return /**/"ReviewStructure";
}

// 単体保存用ファイル名
QString ReviewStructureProperty::filename() const
{
	return /**/"ReviewStructrue";
}

// バッファからの復元
bool ReviewStructureProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(buffer.sectionName()!=sectionName()){
		return false;
	}

	NGNailListSortOrder = static_cast<Review::OrderOfSortNG>(buffer.value(ToStr(NGNailListSortOrder)).toInt());
	HistoryListSortOrder = static_cast<Review::OrderOfSortHistory>(buffer.value(ToStr(HistoryListSortOrder)).toInt());
	SaveNGImageFileNameFormat	= buffer.value(ToStr(SaveNGImageFileNameFormat));
	PreLoadNGImageLength		= buffer.value(ToStr(PreLoadNGImageLength)).toInt();
	XMLServerIPAddress			= buffer.value(ToStr(XMLServerIPAddress));
	XMLServerPortNo				= buffer.value(ToStr(XMLServerPortNo)).toInt();
	NGImagePath					= buffer.value(ToStr(NGImagePath));
	SkipMasterImageRate			= buffer.value(ToStr(SkipMasterImageRate)).toInt();
	VRSOperationEnable			= toBool(buffer.value(ToStr(VRSOperationEnable)));
	DirectoryToSaveCSV			= buffer.value(ToStr(DirectoryToSaveCSV));
	CSVUnitMM					= toBool(buffer.value(ToStr(CSVUnitMM)));
	CSVOffsetX					= buffer.value(ToStr(CSVOffsetX)).toInt();
	CSVOffsetY					= buffer.value(ToStr(CSVOffsetY)).toInt();
	CSVReverseX					= toBool(buffer.value(ToStr(CSVReverseX)));
	CSVReverseY					= toBool(buffer.value(ToStr(CSVReverseY)));
	CSVMagnificationX			= buffer.value(ToStr(CSVMagnificationX)).toDouble();
	CSVMagnificationY			= buffer.value(ToStr(CSVMagnificationY)).toDouble();
	return true;
}

// SectionBuffer作成
SectionBuffer ReviewStructureProperty::toBuffer(void) const// リストへコンバート
{
	SectionBuffer buffer;
	
	// セクション名記述
	buffer.setSectionName(sectionName());

	// データ設定
	buffer.setValue(ToStr(NGNailListSortOrder), QString::number(static_cast<int>(NGNailListSortOrder)));
	buffer.setValue(ToStr(HistoryListSortOrder), QString::number(static_cast<int>(HistoryListSortOrder)));
	buffer.setValue(ToStr(SaveNGImageFileNameFormat), SaveNGImageFileNameFormat);
	buffer.setValue(ToStr(PreLoadNGImageLength), QString::number(PreLoadNGImageLength));
	buffer.setValue(ToStr(XMLServerIPAddress), XMLServerIPAddress);
	buffer.setValue(ToStr(XMLServerPortNo), QString::number(XMLServerPortNo));
	buffer.setValue(ToStr(NGImagePath), NGImagePath);
	buffer.setValue(ToStr(SkipMasterImageRate)	, QString::number(SkipMasterImageRate));
	buffer.setValue(ToStr(VRSOperationEnable)	, fromBool(VRSOperationEnable));
	buffer.setValue(ToStr(DirectoryToSaveCSV)	, DirectoryToSaveCSV);
	buffer.setValue(ToStr(CSVUnitMM)			, fromBool(CSVUnitMM));
	buffer.setValue(ToStr(CSVOffsetX)			, QString::number(CSVOffsetX));
	buffer.setValue(ToStr(CSVOffsetY)			, QString::number(CSVOffsetY));
	buffer.setValue(ToStr(CSVReverseX)			, fromBool(CSVReverseX));
	buffer.setValue(ToStr(CSVReverseY)			, fromBool(CSVReverseY));
	buffer.setValue(ToStr(CSVMagnificationX)	, QString::number(CSVMagnificationX,'f'));
	buffer.setValue(ToStr(CSVMagnificationY)	, QString::number(CSVMagnificationY,'f'));
	return buffer;
}

// 対応クラスからのデータ受け取り
bool ReviewStructureProperty::fromInstance(ReviewPIBase *parent)// 対象クラスからリスト作成
{
	if(parent==NULL)return false;

	fromBuffer( parent->getProperty().toBuffer() );

	return true;
}

// 対応クラスへのデータ引渡し
bool ReviewStructureProperty::toInstance(ReviewPIBase *parent) const// 対象クラスへコンバート
{
	if(parent==NULL)return false;

	parent->setProperty(*this);

	return true;
}

