#pragma once

#include <QString>
#include <QMultiHash>
#include "XDateTime.h"
#include <QStringList>

#include "XTypeDef.h"

#include "ReviewStructureItems.h"

#include "XStringXMLParser.h"

class LotXMLPCEParser : public StringXMLParser
{
public:
	LotXMLPCEParser()
		:StringXMLParser(),m_data(){};

public:
	void analyze(QDomElement &elem);
	void clear(){ StringXMLParser::clear(); m_data=PCEItem(); };

public:
	PCEItem getData() const { return m_data; };

private:
	PCEItem m_data;
};

// StringXMLParserを親クラスとするパーサを行うクラス
// 実装関数は、
//
// (必須)
// パース結果を保持するメンバ変数
// analyze(QDomElement &elem) : パースメイン関数
//
// (適宜)
// コンストラクタ、デストラクタ
// getXXX() : パーサしたデータの取得
// 

class LotXMLInsLibParser : public StringXMLParser
{
public:
	LotXMLInsLibParser()
		:StringXMLParser(){};

public:
	class LotXMLInsLibTypeNameParser : public StringXMLParser{
	public:
		LotXMLInsLibTypeNameParser()
			:StringXMLParser(){};

	public:
		void analyze(QDomElement &elem);
		void clear(){ data.clear(); };

	public:
		InsLibraryItem::TypeNameTag getData(void){ return data; };

	public:
		InsLibraryItem::TypeNameTag data;
	};

public:
	InsLibraryItem getData(){ return data; };

public:
	void analyze(QDomElement &elem);
	void clear(){ StringXMLParser::clear(); data=InsLibraryItem(); };

private:
	InsLibraryItem data;
};


// <NGP ～ />
class LotXMLNgpParser : public StringXMLParser
{
public:
	LotXMLNgpParser():StringXMLParser(){};

private:
	ReviewNGPoint Data;

public:
	ReviewNGPoint getData(){ return Data; };
	void analyze(QDomElement &elem);
	void clear(){ StringXMLParser::clear(); Data=ReviewNGPoint(); };
};

// <NGI ~>
class NGITagData
{
public:
	NGITagData()
	{
		clear();
	};

	void clear()
	{
		// デフォルトで無効な値
		x = -1;
		y = -1;
		width = -1;
		height = -1;
		IDX = -1;
		Index = -1;

		// デフォルトでずれ無し
		AlignedX = 0;
		AlignedY = 0;

		// チェック済みフラグ
		isChecked = false;
		FKey = Review::NoFKey;
	};
public:
	int x,y;
	int width,height;
	int IDX;
	int Index;

	int AlignedX;// アライメントずれ量
	int AlignedY;// 

	bool isChecked;
	Review::FKey FKey;
};

class ISTPage
{
public:
	ISTPage(int page = -1, int parentPhase = -1)
		:NGPList(QList<ReviewNGPoint>()), NGIList(QList<NGITagData>())
	{
		setCurrentPage( page );
		setParentPhase( parentPhase );
	};

	void clear(){
		m_parentPhase = -1;
		m_Page = -1;
	};
	
	QList<ReviewNGPoint> getNGPList(){ return NGPList; };
	QList<NGITagData> getNGIList(){ return NGIList; };
	int getNGPCount(){ return NGPList.count(); };
	int getNGICount(){ return NGIList.count(); };

	void appendNGP(const ReviewNGPoint &NGP)	{ NGPList.append(NGP); };
	void appendNGI(const NGITagData &NGI)		{ NGIList.append(NGI); };
	ReviewNGPoint getNGP(int i){ return NGPList[i]; };
	NGITagData getNGI(int i){ return NGIList[i]; };

	int parentPhase(){ return m_parentPhase; };
	int currentPage(){ return m_Page; };
	void setParentPhase(int phase){ m_parentPhase = phase; };
	void setCurrentPage(int page){ m_Page = page; };
private:
	int m_parentPhase;
	int m_Page;

	QList<ReviewNGPoint> NGPList;
	QList<NGITagData> NGIList;
};

class ISTPhase : public QList<ISTPage>
{
public:
	ISTPhase(){m_Phase = -1;};
public:
	int currentPhase(){ return m_Phase; };
	void setCurrentPhase(int phase){ m_Phase = phase; };
private:
	int m_Phase;
};

class LotXMLNgiParser : public StringXMLParser
{
public:
	LotXMLNgiParser():StringXMLParser(),Data(NGITagData()){};

public:
	NGITagData getData(){ return Data; };

	void analyze(QDomElement &elem);
	void clear(){ StringXMLParser::clear(); Data=NGITagData(); };

private:
	NGITagData Data;
};

class ISTInfomation{
	public:
		ISTInfomation(){
			clear();
		};
	public:
		void clear(){
			ISTDay = XDateTime();
			NGImageFileFormat = /**/"";
			MasterID = -1;
			MasterName = /**/"";
			MachineID = -1;
			InspectID = -1;
			result = QStringList();
		};
		XDateTime ISTDay;// IST::DAY
		QString NGImageFileFormat;//IST::NGJ
		int32 MasterID;//IST::MNM::MID
		QString MasterName;//IST::MNM
		int32 MachineID;//IST::MAC
		int32 InspectID;//IST::INSPECT::EID
		QStringList result;//IST::RES
};

class ISTSingle : public QList<ISTPhase>
{
public:
	ISTInfomation ISTInfo;
};

class ISTMultiList : public QList<ISTSingle>
{};

// <IST ～>*</IST>
class LotXMLIstParser : public StringXMLParser
{
public:
	LotXMLIstParser():StringXMLParser(){ clear(); };
	void clear(){
		StringXMLParser::clear();
		ISTData = ISTSingle();
	};
public:
	
public:
	ISTSingle getISTData(){ return ISTData; };
	int getPhaseCount(){ return ISTData.count(); };
	int getPageCount(int phase){ return ISTData[phase].count(); };
	int getNGPCount(int phase, int page){ return ISTData[phase][page].getNGPCount(); };
	int getNGICount(int phase, int page){ return ISTData[phase][page].getNGICount(); };

	QList<ReviewNGPoint> getNGPListPack(int phase,int page){ return ISTData[phase][page].getNGPList(); };
	QList<NGITagData> getNGIListPack(int phase, int page){ return ISTData[phase][page].getNGIList(); };
	void appendNGP(int phase, int page, ReviewNGPoint &NGP){
		sizeUp(phase, page);

		ISTData[phase][page].appendNGP(NGP);
	};
	void appendNGI(int phase, int page, NGITagData &NGI){
		sizeUp(phase, page);

		ISTData[phase][page].appendNGI(NGI);
	};
	ISTInfomation getISTInfo(){ return ISTData.ISTInfo; };

	void sizeUp(int phase, int page){
		while(ISTData.size()<phase+1)
			ISTData.append(QList<ISTPhase>());
		while(ISTData[phase].size()<page+1)
			ISTData[phase].append(ISTPage(page, phase));
	};

	void analyze(QDomElement &elem);

private:
	ISTSingle ISTData;
	QString LotFilename;
	QString LotName;
};

// <LOT LID="LotFilename">LotName</LOT>
class LotSingleParser : public StringXMLParser
{
public:
	LotSingleParser():StringXMLParser(){ clear(); };
	void clear(){
		LotFilename = /**/"";
		LotName = /**/"";
	};

public:
	void analyze(QDomElement &elem){
		if(elem.tagName()==/**/"LOT"){
			LotFilename = elem.attribute(/**/"LID", /**/"");
			LotName = getCurrentTagText(elem);
		}
	};

	QString getLotFilename(){ return LotFilename; };
	QString getLotName(){ return LotName; };

private:
	QString LotFilename;
	QString LotName;
};