/*
 * Copyright (C) 2022
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

#if	!defined(XREVIEWSTRUCTURE_H)
#define	XREVIEWSTRUCTURE_H

#include "XDateTime.h"
#include <QtXml/QDomElement>
#include <QTransform>
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XResult.h"
#include "XDataAlgorithm.h"
#include "XMLClient.h"
#include "XReviewCommon.h"
//#include "ReviewStructurePacket.h"
//#include "XMLISTReader.h"

#include "ReviewStructureItems.h"
#include "XMLWriter.h"
#include "XReviewPropertyBase.h"
#include "ReviewStructureVRSSetting.h"
#include "ReviewSequenceThread.h"
#include "XSaveCSVInReview.h"

namespace Ui{
class ReviewStructureClass;
}

class XMLWriter;

#define	ReviewVersion	3

//class	ReviewPIItem;
class	ReviewPIInPage;

void AppendDebugLog(QString str);

static const QString CommSettingFile = /**/"ReviewServerComm.dat";

/*
class	ReviewPIThreshold : public AlgorithmThreshold
{
public:
	ReviewPIThreshold(ReviewPIItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	Save(QIODevice *f)			override	{	return true;	}
	virtual	bool	Load(QIODevice *f)			override	{	return true;	};
	virtual	int		GetSize(void)	override	{	return sizeof(this);	}
};

class	ReviewPIItem : public AlgorithmItemPI
{
public:

	ReviewPIItem(void){}

	const	ReviewPIThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ReviewPIThreshold *)GetThresholdBaseReadable(base);	}
	ReviewPIThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ReviewPIThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ReviewPIThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void		Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
};
*/

//�P�y�[�W���̂m�f����
// �@�\�ꗗ
/*
 �E

*/
class	NGDataInPage
{
public:
	NGDataInPage(){clear();};
	void clear(){
		NGTime = XDateTime();
		Parent = NULL;
		Page = -1;
		PhaseNumber = -1;
		NGList = NGNailList();
	};
public:
	XDateTime		NGTime;
	ReviewPIInPage	*Parent;

	int		Page;
	int		PhaseNumber;					//�����Ėʂ����ʂ�
	NGNailList NGList;	//�P�y�[�W���̂m�f���񃊃X�g�R���e�i�@���Ԃ͓K��

	NGDataInPage	&operator=(NGDataInPage &src);
	bool	LoadAndBuildFromXML(void);
};

class   ReviewPIInPage : public AlgorithmInPagePI
{
	NGDataInPage	LastNGHistory;
	NGDataInPage	CurrentNGHistory;	//�����\�����̂m�f����
	NGDataInPage	NextNGHistory;

public:
	ReviewPIInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override{	return NULL;	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
private:
	bool	LoadSlave(int MasterCode ,int MachineID ,int PhaseCode);
	QString getMasterImageName(int MasterCode ,int MachineID ,int PhaseCode, QString path);
};

// Review�̃A���S���Y���̃��C���N���X
// �f�[�^�̂قƂ��ǂ��ێ����AXML�Ƃ̒ʐM�A�f�[�^�̏����AGUI�����̃f�[�^�v���ɉ�����
// ���{�I�Ƀ��N�G�X�g���󂯂�GUI�Ƃ̒ʐM�Ŋ��������悤�ɂ���
// (GUI1��ReviewPIBase��GUI2�Ƃ����͖̂����AGUI1��ReviewPIBase��GUI1�ŏI�����B�������AGUI���m�̒ʐM�͗L��)
//
// GUI��ReviewPIBase�Ƀf�[�^�̗v�����s�����ꍇ�A�K�X�f�[�^���R�s�[���Ďg�p���邱�ƁB
//  ReviewPIBase���ۑ������|�C���^��GUI���ۑ����Ă����ꍇ�A
//  ReviewPIBase�����̃|�C���^���𖳌��Ƃ����Ƃ��̑Ή�������A�A�N�Z�X�G���[���N�����\�����傫�����߁B
//
/*

�@�\�̎��s�͑S�ăp�P�b�g�ɂ����v�����󂯂ĊJ�n������
[���s]
�E�}�X�^�[�f�[�^�̓ǂݍ���
�E�w�肳�ꂽ�t�@�C�����Ŏw�肳�ꂽ�\���ɑ΂��ă��b�g�̓K�p�A�����щ��͂ɂ����f�[�^�č\��

[�ԐM]
�E�ǂݍ��܂ꂽ�}�X�^�[�f�[�^�ɑΉ����郍�b�g�ꗗ�̃��X�g
�E�\���̗������X�g�̃|�C���^


*/

//class ReviewPIBaseProperty
//{
//public:
//	// �\�[�g�w��
//	Review::OrderOfSortNG NGNailListSortOrder;
//	Review::OrderOfSortHistory HistoryListSortOrder;
//	
//	// NG�摜�ۑ��̃t�H�[�}�b�g
//	QString SaveNGImageFileNameFormat;
//
//	// NG�摜�̐��ǂݍ��ݐ������肷�鐔�l
//	// ���ݗ������炱�̑O�ゾ�����ǂݍ��݂���
//	int		PreLoadNGImageLength;
//
//	// XML�T�[�o�[�ւ̃A�N�Z�X�p�A�h���X�ƃ|�[�g�ԍ�
//	QString XMLServerIPAddress;
//	int		XMLServerPortNo;
//};

class ReviewPIBase;

template<>
class PropertyBase<ReviewPIBase> : public AbstructProperty
{
public:
	PropertyBase(void);

public:
	void initialize(void);

public:
	QString baseName() const;
	QString sectionName() const;
	QString filename() const;

public:
	bool fromBuffer(const SectionBuffer &buffer);
	SectionBuffer toBuffer(void) const;// ���X�g�փR���o�[�g
	bool fromInstance(ReviewPIBase *parent);// �ΏۃN���X���烊�X�g�쐬
	bool toInstance(ReviewPIBase *parent) const;// �ΏۃN���X�փR���o�[�g

public:
	PropertyBase<ReviewPIBase> &operator=(const PropertyBase<ReviewPIBase> &other){
		fromBuffer( other.toBuffer() );
		return *this;
	};

public:
	// �\�[�g�w��
	Review::OrderOfSortNG NGNailListSortOrder;
	Review::OrderOfSortHistory HistoryListSortOrder;
	
	// NG�摜�ۑ��̃t�H�[�}�b�g
	QString SaveNGImageFileNameFormat;

	// NG�摜�̐��ǂݍ��ݐ������肷�鐔�l
	// ���ݗ������炱�̑O�ゾ�����ǂݍ��݂���
	int		PreLoadNGImageLength;

	// XML�T�[�o�[�ւ̃A�N�Z�X�p�A�h���X�ƃ|�[�g�ԍ�
	QString XMLServerIPAddress;
	int		XMLServerPortNo;
	QString	NGImagePath;
	QString	DirectoryToSaveCSV;
	bool	CSVUnitMM;
	int		CSVOffsetX;
	int		CSVOffsetY;
	bool	CSVReverseX;
	bool	CSVReverseY;
	double	CSVMagnificationX;
	double	CSVMagnificationY;

	quint32 SkipMasterImageRate;// 0(1/1),1(1/2),2(1/4)...
	bool VRSOperationEnable;
};

typedef PropertyBase<ReviewPIBase> ReviewStructureProperty;

class	ReviewPIBase : public QObject, public AlgorithmBase
{
	Q_OBJECT

	int	VRSOffsetX,VRSOffsetY;
	int	VRSDiffX,VRSDiffY;
public:// construct, destruct
	QString	ReplacedNGImagePath;


	ReviewPIBase(LayersBase *Base,EntryPointBase *EPoint);
	~ReviewPIBase(void);

public:// inhert functions
	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new ReviewPIInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)	override{	return QString(/**/"ReviewPI");				}
	QString	GetDefaultFileName(void)	override{	return QString(/**/"ConfigReviewPI.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	virtual void Initial(LayersBase *Base)	override;

public:// manage master image buffer
	bool freeMasterBufferEnable;
	bool getFreeMasterBufferEnable() const { return freeMasterBufferEnable; };
	void setFreeMasterBufferEnable(bool enable){ freeMasterBufferEnable = enable; };

	void deleteHistoryNGImageReader(Review::SideType side);

private:// manage at History
	void OrganizeHistoryList(void);// ���\�̗������X�g�����A�܂Ƃ߂����X�g�𐶐����� (OrganizedHistoryList = (FrontHistoryList + BackHistoryList) �̂悤�Ȋ���)
	OrganizedHistoryList::Iterator getOrganizedHistoryIterator(int GlobalIndex);
	QList<OrganizedHistoryItem>::iterator	getOrganizedHistoryIteratorBegin();
	QList<OrganizedHistoryItem>::iterator	getOrganizedHistoryIteratorEnd();

	void setCurrentOrganizedHistory(Review::ListLocate locate, int GlobalIndex = -1);
	void setCurrentOrganizedHistory(int GlobalIndex = 0);

private:// manage at NGNail
	void setCurrentNGNail(Review::ListLocate locate, int GlobalIndex = -1);
	void setCurrentNGNail(int GlobalIndex = 0);

private:// for prepare load NGImage
	void loadNGImageRoundCurrent(void);
	void loadNGImage(int OrgHistroyIndex);

private:// function of sort
	// �\�[�g���s�֐�
	void sortNGNailList();
	void sortHistoryList();

private:// function of sort compare
	static bool CompYLesser			(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompYGreater		(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompXLesser			(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompXGreater		(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompNGCauseLesser	(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompNGCauseGreater	(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompLibTypeLesser	(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompLibTypeGreater	(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompArea			(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompPhaseLesser		(const NGNailItem &item1, const NGNailItem &item2);
	static bool CompPhaseGreater	(const NGNailItem &item1, const NGNailItem &item2);

	static bool CompHistoryInspectIDGreater			(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryInspectIDLesser			(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryInspectTimeGreater		(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryInspectTimeLesser		(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountGreater			(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountLesser			(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountOnlyFrontGreater	(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountOnlyFrontLesser	(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountOnlyBackGreater	(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);
	static bool CompHistoryNGCountOnlyBackLesser	(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2);

	QList<int> createNGNailListPhaseBorder(NGNailList &list);// NGNailList�̃t�F�C�Y�\�[�g���ʂ����͂Ƃ��A���E�𓾂�

	//QString	IODLL_FileName;
	//QString	Sequence_FileName;
	//QString	IODefine_FileName;
	//QString	LocalDatabase_FileName;
	//QString	LocalDatabase_HostName;
	//QString	XMLServerHostName;
	//int		XMLServerPortNumber;
	//QString	ImageFilePath;

public:// function to communication with GUI
	// GUI�����̒ʐM�̎��M�֐�
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

// TransmitDirectly�Ŏg�p�������e�R�}���h�ɉ����ċ@�\�����֐�
// packet��NULL�A�������͏����Ώۂł͂Ȃ��ꍇ�A��������false���Ԃ��B
// packet�������Ώۂ̏ꍇ�͕K��true���Ԃ��B
private:// TransmitDirectly function list
	// �}�X�^�[�f�[�^�֌W
	bool	ReciveCmdLoadMainMaster(GUIDirectMessage *packet);
	bool	ReciveCmdLoadSlave(GUIDirectMessage *packet);
	bool	ReciveCmdServerSelectLotList(GUIDirectMessage *packet);
	bool	ReciveCmdServerSetLot(GUIDirectMessage *packet);
	bool	ReciveCmdServerReqCurrentLot(GUIDirectMessage *packet);
	bool	ReciveCmdServerUpdateLotList(GUIDirectMessage *packet);
	bool	ReciveCmdReqMasterDataInfo(GUIDirectMessage *packet);
	bool	ReciveCmdUpdateMasterBuff(GUIDirectMessage *packet);
	bool	ReciveCmdReqWholeImage(GUIDirectMessage *packet);
	bool	ReciveCmdReqMasterImagePiece(GUIDirectMessage *packet);
	bool	ReciveCmdReqMasterImagePieceOnOneImage(GUIDirectMessage *packet);
	bool	ReciveCmdLoadPageImage(GUIDirectMessage *packet);
	bool	ReciveCmdReqWholeImageInfo(GUIDirectMessage *packet);
	bool	ReciveCmdReqMasterInfoFromDataBase(GUIDirectMessage *packet);
	bool	ReciveCmdFreeLayersImageMemory(GUIDirectMessage *packet);
	bool	ReciveCmdReqMasterImageList(GUIDirectMessage *packet);
	bool	ReciveCmdLoadMasterImage(GUIDirectMessage *packet);
	bool	ReciveCmdLoadMaster(GUIDirectMessage *packet);

	// NGNail�֌W
	bool	ReciveCmdReqAdjacentCurrentNG(GUIDirectMessage *packet);
	bool	ReciveCmdMoveCurrentNGNail(GUIDirectMessage *packet);
	bool	ReciveCmdSetCurrentNGNail(GUIDirectMessage *packet);
	bool	ReciveCmdSetCurrentNGChecked(GUIDirectMessage *packet);
	bool	ReciveCmdSetNGChecked(GUIDirectMessage *packet);
	bool	ReciveCmdSetSortNGOrder(GUIDirectMessage *packet);
	bool	ReciveCmdReqSortNGOrder(GUIDirectMessage *packet);
	bool	ReciveCmdSetSortHistoryOrder(GUIDirectMessage *packet);
	bool	ReciveCmdReqSortHistoryOrder(GUIDirectMessage *packet);
	//bool	ReciveCmdReqNGShape(GUIDirectMessage *packet);
	bool	ReciveCmdSaveCurrentNGImage(GUIDirectMessage *packet);

	// �����֌W
	bool	ReciveCmdReqOrganizedHistoryList(GUIDirectMessage *packet);
	bool	ReciveCmdSetCurrentHistory(GUIDirectMessage *packet);
	bool	ReciveCmdReqCurrentHistory(GUIDirectMessage *packet);
	bool	ReciveCmdMoveCurrentHistory(GUIDirectMessage *packet);
	bool	ReciveCmdMoveCurrentHistoryToNGBoard(GUIDirectMessage *packet);
	bool	ReciveCmdReqHistoryAllChecked(GUIDirectMessage *packet);
	//bool	ReciveCmdReqCurrentNGPointListWithShape(GUIDirectMessage *packet);
	bool	ReciveCmdSaveCurrentHistoryNGImages(GUIDirectMessage *packet);

	// XML�֌W
	bool	ReciveCmdSetFKeyToNGNail(GUIDirectMessage *packet);
	bool	ReciveCmdClearFKeyToNGNail(GUIDirectMessage *packet);
	bool	ReciveCmdReqFKeyColorList(GUIDirectMessage *packet);
	bool	ReciveCmdReqInsLib(GUIDirectMessage *packet);
	bool	ReciveCmdUpdateCurrentLotData(GUIDirectMessage *packet);
	bool	ReciveCmdReqInsLibItemTag(GUIDirectMessage *packet);
	bool	ReciveCmdReqInsLIbWaitTime(GUIDirectMessage *packet);
	bool	ReciveCmdClearSideLot(GUIDirectMessage *packet);
	bool	ReciveCmdReqPCEList(GUIDirectMessage *packet);
	bool	ReciveCmdUpdateLotInfoList(GUIDirectMessage *packet);
	bool	ReciveCmdReqCurrentLotAllList(GUIDirectMessage *packet);
	bool	ReciveCmdReqCurrentLotInfo(GUIDirectMessage *packet);

	// �����֘A
	bool	ReciveCmdReqSaveFormatMacroList(GUIDirectMessage *packet);

	// VRS�֘A
	bool	ReciveCmdReqVRSSetting(GUIDirectMessage *packet);
	bool	ReciveCmdSetVRSSetting(GUIDirectMessage *packet);
	bool	ReciveCmdReqVRSAlignment(GUIDirectMessage *packet);
	bool	ReciveCmdSetVRSAlignment(GUIDirectMessage *packet);
	bool	ReciveCmdReqVRSMotorState(GUIDirectMessage *packet);
	bool	ReciveCmdSetVRSMotorState(GUIDirectMessage *packet);
	bool	ReciveCmdReqCameraAlignment(GUIDirectMessage *packet);
	bool	ReciveCmdSetCameraAlignment(GUIDirectMessage *packet);
	bool	ReciveCmdReqSequenceEnable(GUIDirectMessage *packet);
	bool	ReciveCmdSetSequenceEnable(GUIDirectMessage *packet);
	bool	ReciveCmdMoveVRSToCurrentNG(GUIDirectMessage *packet);
	bool	ReciveCmdClearVRSCommandBuffer(GUIDirectMessage *packet);
	bool	ReciveCmdMoveVRSOnCameraView(GUIDirectMessage *packet);
	bool	ReciveCmdMoveVRSWithAlignment(GUIDirectMessage *packet);
	bool	ReciveCmdMoveVRSToOrigin(GUIDirectMessage *packet);
	bool	ReciveCmdMoveVRSToEscape(GUIDirectMessage *packet);;
	bool	ReciveCmdMoveVRSDirectory(GUIDirectMessage *packet);

	// GUI���ʍ���
	bool	ReciveCommonCmdReqSettingPropertyDialog(GUIDirectMessage *packet);
	//bool	ReciveCommonCmdMoveVRSWithAlignment(GUIDirectMessage *packet)
	//bool	ReciveCommonCmdMoveVRSToOrigin(GUIDirectMessage *packet);

private:// load Master data and image
	// �}�X�^�[�̓ǂݍ���
	bool	LoadMaster(Review::SideType side, int PhaseCode ,int MasterCode
		,int32 &iMachineID,int &iPhaseNumb, MasterDataInfo &infoBuff, bool addMode);
	QImage	GetMasterWholeImage(Review::SideType side, int phase, int width, int height ,double ZoomImageFromFile);
	QImage	GetMasterImagePiece(Review::SideType side, int phase, int page,  int x, int y, int width, int height);
	QImage	GetMasterImagePiece(Review::SideType side, int phase,  int x, int y, int width, int height);
	bool	LoadMasterImage(int skipCount ,int LayerNumb ,QList<QImage> &ImageByPage ,const QString &FileName);
	// �}�X�^�[�R�[�h�̃t�F�C�Y���̎擾
	int		GetPhaseNumb(int masterCode);
	bool	LoadPageImage(QIODevice &file ,QImage &TargetPageImages,bool &Ret);
	bool	LoadMasterImage(int skipCount ,int LayerNumb ,QList<QImage> &ImageByPage 
					,QIODevice &file);

private:// manage with XMLServer
	// XMLServer�̃I�[�v��
	bool	XML_Open();
	bool	XML_Open(QString Address, int Port);
	// XMLServer�̃N���[�Y
	bool	XML_Close();
	// XMLServer�Ƀ��b�g�����̎擾�v��
	bool	XML_GetLot(int MasterCode,int MachineID, QStringList &list);
	// XMLServer�Ɏw�肵�����b�g�̐ݒu
	bool	XML_SetLotToSide(QString lotFile, Review::SideType side);
	void	XML_ClearLot(Review::SideType side);
	// XML��<Count/>�𐔒l������
	int		XML_CountAnalyze(const QString &CountXML);
	// XML���烍�b�g�������擾����
	LotInfoItem	XML_GetLotInfo(const QString &TableName);
	////
	//bool	XML_SetCurrentPosToNGI(XMLOperationHandle *operationHandle, int EID, int page, int phase, int Target_X, int Target_Y);
	//bool	XML_SetCurrentPosToNGI(QString TableName, int EID, int phase, int page, int Target_X, int Target_Y);

	class XMLOpener{
	public:
		XMLOpener(ReviewPIBase *parent):m_parent(parent){
			ok = m_parent->XML_Open();
		}
		~XMLOpener(){
			//m_parent->XML_Close();
		};
		bool isOpen(){
			return ok;
		};
		bool close(){
			ok = !m_parent->XML_Close();
			return !ok;
		};
		bool open(){
			ok = m_parent->XML_Open();
			return ok;
		};
	private:
		ReviewPIBase *m_parent;
		bool ok;
	};

private:// manage color of FKey
	//void setFKeyColor(const QList<QColor> &list){ FKeyColorList = list; };
	//void setFKeyColor(int index, const QColor &color){ if(index>=0 && index<FKeyColorList.count())FKeyColorList[index] = color; };
	QColor getFKeyColor(Review::FKey key){ return Review::getDefaultFKeyColor(key);/*FKeyColorList[Review::FKeyToInt(key)];*/ };

private:// current side type
	Review::SideType getSideType(const NGNailItemRef &refItem) const;
	Review::SideType getCurrentSideType() const;

private:// XML�����̍č\�z�֘A
	InsLibraryItem::TypeNameTag getInsLibraryItemTypeNameTag(Review::SideType side, QString Ral, int LC, int TC) const;
	InsLibraryItem getInsLibraryItem(Review::SideType side, QString Ral, int LC) const;
	InsLibraryList getInsLibraryList(Review::SideType side, QString Ral) const;

	void updateInsLibSearchHash(Review::SideType side);

private:
	PCEList m_FrontPCEList;
	PCEList m_BackPCEList;

private:// function of PCE Tag in XML
	PCEList getPCEList(Review::SideType side) const{
		return switchSide(side, m_FrontPCEList, m_BackPCEList, PCEList());
		if(Review::isFront(side)==true){
			return m_FrontPCEList;
		}else if(Review::isBack(side)==true){
			return m_BackPCEList;
		}else{
			// none
		}
	};

	void setPCEList(Review::SideType side, const PCEList &list){
		if(Review::isFront(side)==true){
			m_FrontPCEList = list;
		}else if(Review::isBack(side)==true){
			m_BackPCEList = list;
		}else{
			// none
		}
	};

	void clearPCEList(Review::SideType side){
		setPCEList(side, PCEList());
	};

	void clearPCEList(){
		setPCEList(Review::Front, PCEList());
		setPCEList(Review::Back, PCEList());
	};

	PCEList getPCEMatch(Review::SideType side, int MasterID, int page, const QStringList &PCENameList) const;

private:// for rebuild from XML
	// �e�v�f���P��������NG�f�[�^�̏W�����\��
	HistoryList	m_FrontHistoryList;// �\ //
	HistoryList	m_BackHistoryList;// ��

	// ShowHistoryListForReview�ŕ\�����郊�X�g
	OrganizedHistoryList m_HistoryPack;// ��������ID�ł܂Ƃ߂��������X�g

	LotInfoItem m_FrontCurrentLotInfo;
	LotInfoItem m_BackCurrentLotInfo;

	LotInfoList m_FrontLotInfoAllList;
	LotInfoList m_BackLotInfoAllList;

	InsLibraryHash m_FrontInsLibHash;
	InsLibraryHash m_BackInsLibHash;

	InsLibSearchHash m_FrontInsLibSearchHash;
	InsLibSearchHash m_BackInsLibSearchHash;

	ForSaveTotalLot	CurrentBundle;
	bool	SaveCSV(void);
	bool	LoadCSV(void);

public:
	inline const HistoryList &getHistoryList(Review::SideType side) const { return isFront(side) ? m_FrontHistoryList : m_BackHistoryList; };
	inline HistoryList &getHistoryList(Review::SideType side) { return isFront(side) ? m_FrontHistoryList : m_BackHistoryList; };
	void setHistoryList(Review::SideType side, const HistoryList &list){
		if(isFront(side)){
			m_FrontHistoryList = list;
		}else{
			m_BackHistoryList = list;
		}
		OrganizeHistoryList();
	};

	inline const OrganizedHistoryList &getOrganizedHistoryList() const { return m_HistoryPack; };
	inline OrganizedHistoryList &getOrganizedHistoryList(){ return m_HistoryPack; };
	void setOrganizedHistoryList(const OrganizedHistoryList &pack){ m_HistoryPack = pack; };

	inline const LotInfoItem getCurrentLotInfo(Review::SideType side) const { return isFront(side) ? m_FrontCurrentLotInfo : m_BackCurrentLotInfo; };
	inline LotInfoItem getCurrentLotInfo(Review::SideType side) { return isFront(side) ? m_FrontCurrentLotInfo : m_BackCurrentLotInfo; };
	void setCurrentLotTableName(Review::SideType side, const QString &tablename){
		if(isFront(side)==true){
			m_FrontCurrentLotInfo.TableName = tablename;
		}else{
			m_BackCurrentLotInfo.TableName = tablename;
		}
	}
	void setCurrentLotName(Review::SideType side, const QString &lotname){
		if(isFront(side)){
			m_FrontCurrentLotInfo.LotName = lotname;
		}else{
			m_BackCurrentLotInfo.LotName = lotname;
		}
	}
	void setCurrentLotRemark(Review::SideType side, const QString &remark){
		if(isFront(side)){
			m_FrontCurrentLotInfo.Remark = remark;
		}else{
			m_BackCurrentLotInfo.Remark = remark;
		}
	}
	void setCurrentLotInfo(Review::SideType side, const LotInfoItem &info){
		if(isFront(side)){
			m_FrontCurrentLotInfo = info;
		}else{
			m_BackCurrentLotInfo = info;
		}
	}
	void clearCurrentLotInfo(Review::SideType side){
		setCurrentLotInfo(side, LotInfoItem());
	};

	LotInfoList getLotInfoAllList(Review::SideType side) const { return isFront(side) ? m_FrontLotInfoAllList : m_BackLotInfoAllList; };
	void setLotInfoAllList(Review::SideType side, LotInfoList &list){
		if(isFront(side)==true){
			m_FrontLotInfoAllList = list;
		}else{
			m_BackLotInfoAllList = list;
		}
	}
	void clearLotInfoAllList(Review::SideType side){
		if(isFront(side)==true){
			m_FrontLotInfoAllList.clear();
		}else{
			m_BackLotInfoAllList.clear();
		}
	};

	inline const InsLibraryHash &getInsLibHash(Review::SideType side) const { return isFront(side) ? m_FrontInsLibHash : m_BackInsLibHash; };
	inline InsLibraryHash &getInsLibHash(Review::SideType side) { return isFront(side) ? m_FrontInsLibHash : m_BackInsLibHash; };
	inline const InsLibraryHash *getInsLibHashPtr(Review::SideType side) const { return isFront(side) ? &m_FrontInsLibHash : &m_BackInsLibHash; };
	inline InsLibraryHash *getInsLibHashPtr(Review::SideType side) { return isFront(side) ? &m_FrontInsLibHash : &m_BackInsLibHash; };
	void setInsLibHash(Review::SideType side, const InsLibraryHash &hash){ if(isFront(side)){ m_FrontInsLibHash =  hash; }else{ m_BackInsLibHash = hash; } };

	inline const InsLibSearchHash &getInsLibSearchHash(Review::SideType side) const { return (isFront(side)) ? m_FrontInsLibSearchHash : m_BackInsLibSearchHash; };
	inline InsLibSearchHash &getInsLibSearchHash(Review::SideType side){ return (isFront(side)) ? m_FrontInsLibSearchHash : m_BackInsLibSearchHash; };
	void setInsLibSearchHash(Review::SideType side, const InsLibSearchHash &hash){ (isFront(side)) ? m_FrontInsLibSearchHash=hash : m_BackInsLibSearchHash=hash; };


private:// setting value to save and load
	ReviewStructureProperty m_property;
	VRSSetting				m_VRSSetting;
	VRSAlignment			m_VRSFrontAlignment, m_VRSBackAlignment;
	//// �\�[�g�w��
	//Review::OrderOfSortNG NGNailListSortOrder;
	//Review::OrderOfSortHistory HistoryListSortOrder;

	//// F�L�[�̐F���X�g
	////QList<QColor> FKeyColorList;// 13�v�f�Œ�
	//
	//// NG�摜�ۑ��̃t�H�[�}�b�g
	//QString SaveNGImageFileNameFormat;

	//// NG�摜�̐��ǂݍ��ݐ������肷�鐔�l
	//// ���ݗ������炱�̑O�ゾ�����ǂݍ��݂���
	//int		PreLoadNGImageLength;

	//// XML�T�[�o�[�ւ̃A�N�Z�X�p�A�h���X�ƃ|�[�g�ԍ�
	//QString XMLServerIPAddress;
	//int		XMLServerPortNo;

	//Review::OrginPosition TopSide,BottomSide;// ���̑S�̉摜�̕\���ɂ�������ʒu

private:
	Ui::ReviewStructureClass *m_propertyUi;
	QDialog *m_propertyDialog;

private:
	void setPropertyUi(Ui::ReviewStructureClass *ui){ m_propertyUi = ui; };
	Ui::ReviewStructureClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };

	void setVRSSetting(const VRSSetting &setting);
	inline const VRSSetting &getVRSSetting() const { return m_VRSSetting; };
	inline VRSSetting &getVRSSetting() { return m_VRSSetting; };

	void setVRSAlignment(const VRSAlignment &setting);
	inline const VRSAlignment &getVRSAlignment(Review::SideType side) const { return (Review::isFront(side)==true ? m_VRSFrontAlignment : m_VRSBackAlignment); };
	inline VRSAlignment &getVRSAlignment(Review::SideType side) { return (Review::isFront(side)==true ? m_VRSFrontAlignment : m_VRSBackAlignment); };
	void clearVRSAlignment(Review::SideType side){ if(Review::isFront(side)==true){ m_VRSFrontAlignment = VRSAlignment(); }else{ m_VRSBackAlignment = VRSAlignment(); }; };
	void clearVRSAlignment(){ clearVRSAlignment(Review::Front); clearVRSAlignment(Review::Back); };
	void appendVRSAlignment(Review::SideType side, int machineID){
		VRSAlignment vrsalign;
		vrsalign.setMachineID(machineID);

		SettingFileReader reader;
		if(reader.load(vrsalign.filename())==true){
			vrsalign.fromBuffer( reader.sectionBuffer(vrsalign.sectionName()) );
		}

		if(Review::isFront(side)){
			m_VRSFrontAlignment = vrsalign;
		}else{
			m_VRSBackAlignment = vrsalign;
		}
	};

	void saveVRSSetting() const;

	void initProperty(void);

public slots:
	void slot_propertyModified();

public:// property get and set
	inline const ReviewStructureProperty &getProperty() const { return m_property; };
	inline ReviewStructureProperty &getProperty() { return m_property; };
	ReviewStructureProperty *getPropertyPtr() { return &m_property; }
	void setProperty(const ReviewStructureProperty &property);
	void setPropertyToUi(const ReviewStructureProperty &property);
	void getPropertyFromUi(ReviewStructureProperty &property);
	void updateProperty(void);

	inline int getMasterImageNormalizeZoomRate() const { return getProperty().SkipMasterImageRate+1;/*qPow(2, getProperty().SkipMasterImageRate);*/ };
	
public:
	// �\�[�g�ݒ�
	void setNGSortOrder(Review::OrderOfSortNG order){ if(getProperty().NGNailListSortOrder!=order){getProperty().NGNailListSortOrder = order; sortNGNailList(); } };
	void setHistorySortOrder(Review::OrderOfSortHistory order){ if(getProperty().HistoryListSortOrder!=order){ getProperty().HistoryListSortOrder = order; sortHistoryList(); } };
	Review::OrderOfSortNG getNGSortOrder() const { return getProperty().NGNailListSortOrder; };
	Review::OrderOfSortHistory getHistorySortOrder() const { return getProperty().HistoryListSortOrder; };

	void setSaveNGImageFileNameFormat(const QString &format){ getProperty().SaveNGImageFileNameFormat = format; };
	QString getSaveNGImageFileNameFormat() const { return getProperty().SaveNGImageFileNameFormat; };

	void setPreLoadNGImageLength(int length){ if(length>=0){ getProperty().PreLoadNGImageLength=length; }else{ getProperty().PreLoadNGImageLength=0; } };
	int getPreLoadNGImageLength() const { return getProperty().PreLoadNGImageLength; };

	void setXMLServerState(const QString &IPAddress, int portNo, bool nowReconnect=false);
	QString getXMLServerIPAddress() const { return getProperty().XMLServerIPAddress; };
	int getXMLServerPortNo() const { return getProperty().XMLServerPortNo; };
	QString	getNGImagePath() const { return getProperty().NGImagePath; };

	void setVRSAlignmentToWhole(Review::SideType side, const VRSAlignment::ThreePointAlignment &alignItem)
	{
		getVRSAlignment(side).setAffinSeedToWhole(alignItem);
	}

	void setVRSAlignmentToEachPage(Review::SideType side, const QList<VRSAlignment::ThreePointAlignment> &alignList)
	{
		getVRSAlignment(side).setAffinSeedToEachPage(alignList);
	}

	void setVRSAlignmentType(Review::SideType side, Review::VRSAlignmentType type)
	{
		getVRSAlignment(side).setAlignmentType(type);
	}

	VRSAlignment::ThreePointAlignment getVRSAlignmentFromWhole(Review::SideType side) const
	{
		return getVRSAlignment(side).getAffinSeedFromWhole();
	};
	QList<VRSAlignment::ThreePointAlignment> getVRSAlignmentFromEachPage(Review::SideType side) const
	{
		return getVRSAlignment(side).getAffinSeedFromEachPage();
	};

	QTransform getVRSMatrixFromWhole(Review::SideType side) const;
	QList<QTransform> getVRSMatrixFromEachPage(Review::SideType side) const;
	QTransform getVRSMatrixFromEachPage(Review::SideType side, int page) const;

public:// SaveNGImageFileNameFormat�Ǘ�
	QString convertedSaveNGFileName(Review::SideType side, const OrganizedHistoryList::Iterator &hIt, NGNailList::Iterator ngIt) const;

private:// for XML access
	// access xml server on another thread
	XMLWriter *m_xmlWriter;

	// XML�T�[�o�[�̃n���h��
	XMLServerHandle *m_xmlServerHdl;// ���b�g�擾���p

public:
	inline const XMLWriter *getXMLWriter() const { return m_xmlWriter; };
	inline const XMLServerHandle *getXMLServerHandle() const { return m_xmlServerHdl; };

private:
	inline XMLWriter *getXMLWriter() { return m_xmlWriter; };
	inline XMLServerHandle *getXMLServerHandle() { return m_xmlServerHdl; };

private:// for current state
	// ���ڗ��������̎���(�C�e���[�^)
	// ���я���HistoryListSortOrder�ɏ]��
	OrganizedHistoryList::Iterator m_PreviousOrganizedHistory;	// �O�̗���
	OrganizedHistoryList::Iterator m_CurrentOrganizedHistory;	// ���݂̗���
	OrganizedHistoryList::Iterator m_NextOrganizedHistory;	// ���̗���

	// CurrentOrganizedHistory��NG����(�C�e���[�^)
	// ���я���NGNailListSortOrder�ɏ]��
	NGNailList::Iterator	m_PreviousNGNail;		// �O��NGNail
	NGNailList::Iterator	m_CurrentNGNail;	// ���݂�NGNail
	NGNailList::Iterator	m_NextNGNail;		// ����NGNail

public:
	OrganizedHistoryList::Iterator getRoundCurrentOrganizedHistoryIterator(Review::NearPosType pos) const {
		switch(pos){
		case Review::NearPosType::PreviousPos:
			return m_PreviousOrganizedHistory;
			break;
		case Review::NearPosType::CurrentPos:
			return m_CurrentOrganizedHistory;
			break;
		case Review::NearPosType::NextPos:
			return m_NextOrganizedHistory;
			break;
		default:
			return OrganizedHistoryList::Iterator();
			break;
		}
	};

	void getRoundCurrentOrganizedHistoryIterator(OrganizedHistoryList::Iterator &previous, OrganizedHistoryList::Iterator &current, OrganizedHistoryList::Iterator &next) const {
		previous = getRoundCurrentOrganizedHistoryIterator(Review::PreviousPos);
		current = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
		next = getRoundCurrentOrganizedHistoryIterator(Review::NextPos);
	};

	void setRoundCurrentOrganizedHistoryIterator(Review::NearPosType pos, const OrganizedHistoryList::Iterator ite)
	{
		switch(pos){
		case Review::NearPosType::PreviousPos:
			m_PreviousOrganizedHistory = ite;
			break;
		case Review::NearPosType::CurrentPos:
			m_CurrentOrganizedHistory = ite;
			break;
		case Review::NearPosType::NextPos:
			m_NextOrganizedHistory = ite;
			break;
		default:
			break;
		}
	};

	void setRoundCurrentOrganizedHistoryIterator(const OrganizedHistoryList::Iterator previous, const OrganizedHistoryList::Iterator current, const OrganizedHistoryList::Iterator next){
		setRoundCurrentOrganizedHistoryIterator(Review::PreviousPos, previous);
		setRoundCurrentOrganizedHistoryIterator(Review::CurrentPos, current);
		setRoundCurrentOrganizedHistoryIterator(Review::NextPos, next);
	};

	void clearRoundCurrentOrganizedHistoryIterator(){
		setRoundCurrentOrganizedHistoryIterator(Review::PreviousPos	, OrganizedHistoryList::Iterator());
		setRoundCurrentOrganizedHistoryIterator(Review::CurrentPos	, OrganizedHistoryList::Iterator());
		setRoundCurrentOrganizedHistoryIterator(Review::NextPos		, OrganizedHistoryList::Iterator());
	};

	NGNailList::Iterator getRoundCurrentNGNailIterator(Review::NearPosType pos) const {
		switch(pos){
		case Review::NearPosType::PreviousPos:
			return m_PreviousNGNail;
			break;
		case Review::NearPosType::CurrentPos:
			return m_CurrentNGNail;
			break;
		case Review::NearPosType::NextPos:
			return m_NextNGNail;
			break;
		default:
			return NGNailList::Iterator();
			break;
		}
	};

	void getRoundCurrentNGNailIterator(NGNailList::Iterator &previous, NGNailList::Iterator &current, NGNailList::Iterator &next) const {
		previous	= getRoundCurrentNGNailIterator(Review::PreviousPos);
		current		= getRoundCurrentNGNailIterator(Review::CurrentPos);
		next		= getRoundCurrentNGNailIterator(Review::NextPos);
	};

	void setRoundCurrentNGNailIterator(Review::NearPosType pos, const NGNailList::Iterator ite){
		switch(pos){
		case Review::NearPosType::PreviousPos:
			m_PreviousNGNail = ite;
			break;
		case Review::NearPosType::CurrentPos:
			if(ite!=NGNailList::Iterator() && isSequenceEnable()==true){

				if(ite==m_CurrentNGNail){
					if(isSequenceEnable()==true){
						sendVRSToMoveXY(*ite);
					}
				}else{
					int oldSide = -1;
					int newSide = -1;
					int oldPhase = -1;
					int newPhase = -1;
					int oldInsID = -1;
					int newInsID = -1;

					if(m_CurrentNGNail!=NGNailList::Iterator()){
						oldSide = getSideType(*m_CurrentNGNail);
						oldPhase = m_CurrentNGNail->phase;
						oldInsID = m_CurrentNGNail->InspectID;
					}

					Review::SideType tNewSide = getSideType(*ite);
					newSide = static_cast<int>(tNewSide);
					newInsID = ite->InspectID;
		
					if(isSequenceEnable()==true){
						if(oldSide!=newSide || oldPhase!=ite->phase || oldInsID!=newInsID){
							//sendVRSToEscapePosition();
							//QMessageBox mbox;
							//mbox.setWindowTitle("Set Board");
							//mbox.setText(QString("Next is %1.").arg(Review::toString(tNewSide)));
							//mbox.exec();
						}

						sendVRSToMoveXY(*ite);
					}
				}
			}
			m_CurrentNGNail = ite;
			break;
		case Review::NearPosType::NextPos:
			m_NextNGNail = ite;
			break;
		default:
			break;
		}
	};

	void setRoundCurrentNGNailIterator(const NGNailList::Iterator &previous, const NGNailList::Iterator &current, const NGNailList::Iterator &next){
		setRoundCurrentNGNailIterator(Review::PreviousPos, previous);
		setRoundCurrentNGNailIterator(Review::CurrentPos, current);
		setRoundCurrentNGNailIterator(Review::NextPos, next);
	};

	void clearRoundCurrentNGNailIterator(){
		setRoundCurrentNGNailIterator(Review::PreviousPos	, NGNailList::Iterator());
		setRoundCurrentNGNailIterator(Review::CurrentPos	, NGNailList::Iterator());
		setRoundCurrentNGNailIterator(Review::NextPos		, NGNailList::Iterator());
	};

private:// for MasterData
	// �@�B�����A���������Жʌ����@�����ʌ����@���B
	// �Жʂ̏ꍇ��Front�̂݁A���ʂ̏ꍇ�͂����ɉ�����Back���g�p�����B
	Review::OrganizedSideType m_MachineType;

	// �ǂݍ��񂾃}�X�^�[�f�[�^�̏���
	MasterDataInfo m_FrontMasterInfo;
	MasterDataInfo m_BackMasterInfo;

	// �A�E�g���C��
	QList<QList<QPoint> > m_FrontOutline;
	QList<QList<QPoint> > m_BackOutline;

private:
	inline const MasterDataInfo getMasterInfo(Review::SideType side) const { return ((isFront(side)==true) ? m_FrontMasterInfo : m_BackMasterInfo); };
	inline MasterDataInfo getMasterInfo(Review::SideType side) { return ((isFront(side)==true) ? m_FrontMasterInfo : m_BackMasterInfo); };
	inline const MasterDataInfo *getMasterInfoPtr(Review::SideType side) const { return ((isFront(side)==true) ? &m_FrontMasterInfo : &m_BackMasterInfo); };
	inline MasterDataInfo *getMasterInfoPtr(Review::SideType side) { return ((isFront(side)==true) ? &m_FrontMasterInfo : &m_BackMasterInfo); };

private:
	template<typename T>
	inline const T switchSide(Review::SideType side, const T &front, const T &back, const T &noside) const {
		switch(side){
		case Review::Front:
			return front;
			break;
		case Review::Back:
			return back;
			break;
		default:
			return noside;
			break;
		}
		return noside;
	};

	template<typename T>
	inline T switchSide(Review::SideType side, T &front, T &back, T &noside) const {
		switch(side){
		case Review::Front:
			return front;
			break;
		case Review::Back:
			return back;
			break;
		default:
			return noside;
			break;
		}
		return noside;
	};
	
	template<typename T>
	inline const T switchSide(Review::SideType side, const T &front, const T &back) const {
		return switchSide(side, front, back, T());
	};

	template<typename T>
	inline T switchSide(Review::SideType side, T &front, T &back) const {
		return switchSide(side, front, back, T());
	};

private:
	QList<QList<QImage> >	 getMasterWholePageImageList(Review::SideType side) const {
	//QList<QList<DataInPage*> >	 getMasterWholePageImageList(Review::SideType side){
		//QList<QList<DataInPage*> > list;
		//int backPhaseNumb = 0;
		//if(getMasterInfo(Review::Back).isEmpty()==false){
		//	backPhaseNumb = getMasterInfo(Review::Back).PhaseNumb;
		//}
		//if(Review::isFront(side)==true){
		//	QList<QImage> imageList;
		//	for(int phase=0; phase<GetLayersBase()->GetPhaseNumb()-backPhaseNumb; phase++){
		//		QList<DataInPage*> tlist;
		//		for(int page=0; page<getMasterInfo(Review::Front).PageNumb; page++){
		//			for(int layer=0; layer<getMasterInfo(Review::Front).LayerNumb; layer++){
		//				tlist << GetLayersBase()->GetPhaseData()[phase]->GetPageData(page);
		//			}
		//		}
		//		list << tlist;
		//	}
		//}else if(Review::isBack(side)==true){
		//	QList<QImage> imageList;
		//	int backPhaseNumb = 0;
		//	for(int phase=GetLayersBase()->GetPhaseNumb()-backPhaseNumb; phase<GetLayersBase()->GetPhaseNumb(); phase++){
		//		QList<DataInPage*> tlist;
		//		for(int page=0; page<getMasterInfo(Review::Back).PageNumb; page++){
		//			for(int layer=0; layer<getMasterInfo(Review::Back).LayerNumb; layer++){
		//				tlist << GetLayersBase()->GetPhaseData()[phase]->GetPageData(page);
		//			}
		//		}
		//		list << tlist;
		//	}
		//}
		//return list;
		//for(int phase=0; phase<GetLayersBase()->GetPhaseNumb(); phase++){
		//	for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
		//		for(int layer=0; layer<GetLayersBase()->GetLayerNumb(); layer++){
		//			GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetLayerData(layer)->GetMasterBuff()
		//		}
		//	}
		//}
		return switchSide(side, m_FrontMasterWholePageImageList, m_BackMasterWholePageImageList);
	};
	QList<QList<QImage> >	*getMasterWholePageImageListPtr(Review::SideType side) { return switchSide(side, &m_FrontMasterWholePageImageList, &m_BackMasterWholePageImageList, (QList<QList<QImage> >*)NULL); };
	
	QList<QImage>			 getMasterWholePageImageList(Review::SideType side, int phase) const{
	//QList<DataInPage*>			 getMasterWholePageImageList(Review::SideType side, int phase){
		return getMasterWholePageImageList(side)[phase];
	};
	QList<QImage>			*getMasterWholePageImageListPtr(Review::SideType side, int phase) { return getMasterWholePageImageListPtr(side)!=NULL ? &(*getMasterWholePageImageListPtr(side))[phase] : NULL; };
	
	QList<QSize >			 getMasterWholeImageSize(Review::SideType side) const { return switchSide(side, m_FrontMasterWholeImageSize, m_BackMasterWholeImageSize); };
	QList<QSize >			*getMasterWholeImageSizePtr(Review::SideType side){ return switchSide(side, &m_FrontMasterWholeImageSize, &m_BackMasterWholeImageSize, (QList<QSize >*)NULL); };
	
	QSize					 getMasterWholeImageSize(Review::SideType side, int phase) const { return getMasterWholeImageSize(side)[phase]; };
	QSize					*getMasterWholeImageSizePtr(Review::SideType side, int phase){ return getMasterWholeImageSizePtr(side)!=NULL ? &(*getMasterWholeImageSizePtr(side))[phase] : NULL; };

	QList<QList<QPoint> >	 getMasterWholeImgDrawPoints(Review::SideType side) const { return switchSide(side, m_FrontMasterWholeImageDrawPoints, m_BackMasterWholeImageDrawPoints); };
	QList<QList<QPoint> >	*getMasterWholeImgDrawPointsPtr(Review::SideType side){ return switchSide(side, &m_FrontMasterWholeImageDrawPoints, &m_BackMasterWholeImageDrawPoints, (QList<QList<QPoint> >*)NULL); };

	QList<QPoint>			 getMasterWholeImgDrawPoints(Review::SideType side, int phase) const { return getMasterWholeImgDrawPoints(side)[phase]; };
	QList<QPoint>			*getMasterWholeImgDrawPointsPtr(Review::SideType side, int phase){ return getMasterWholeImgDrawPointsPtr(side)!=NULL ? &(*getMasterWholeImgDrawPointsPtr(side))[phase] : NULL; };

	QList<QList<QPoint> >	 getMasterWholePageOutlineList(Review::SideType side){ return switchSide(side, m_FrontOutline, m_BackOutline); };
	QList<QList<QPoint> >	*getMasterWholePageOutlineListPtr(Review::SideType side){ return switchSide(side, &m_FrontOutline, &m_BackOutline, (QList<QList<QPoint> >*)NULL); };
	
	QList<QPoint>			 getMasterWholePageOutlineList(Review::SideType side, int phase){ return getMasterWholePageOutlineList(side)[phase]; };
	QList<QPoint>			*getMasterWholePageOutlineListPtr(Review::SideType side, int phase){ return getMasterWholePageOutlineListPtr(side)!=NULL ? &(*getMasterWholePageOutlineListPtr(side))[phase] : NULL; };

	QPoint					 getMasterWholePageOutline(Review::SideType side, int phase, int page){ return getMasterWholePageOutlineList(side,phase)[page]; };
	QPoint					*getMasterWholePageOutlinePtr(Review::SideType side, int phase, int page){ return getMasterWholePageOutlineListPtr(side, phase)!=NULL ? &(*getMasterWholePageOutlineListPtr(side, phase))[page] : NULL; };

private:
	void loadOutlineOffset(Review::SideType side, int MachineID, int MasterCode);

private:// for MasterImage
	// �S�̉摜�o�b�t�@
	// 20120315 �傫�������o�b�t�@���m�ۂ��悤�Ƃ����ƃ������G���[�ƂȂ邽�ߎg�p�֎~
	//QImage FrontWholeImage;
	//QImage BackWholeImage;

	// �S�̉摜�y�[�W�o�b�t�@
	QList<QList<QImage> > m_FrontMasterWholePageImageList;
	QList<QList<QImage> > m_BackMasterWholePageImageList;
	QList<QSize >	m_FrontMasterWholeImageSize;// �S�̃}�X�^�[�摜���\�������Ƃ��̃T�C�Y
	QList<QSize >	m_BackMasterWholeImageSize;
	QList<QList<QPoint> > m_FrontMasterWholeImageDrawPoints;// �S�̉摜���Ńy�[�W���\���t�����ۂ̈ʒu
	QList<QList<QPoint> > m_BackMasterWholeImageDrawPoints;

private:
	QList<QList<QImage> > getMasterWholePageImageList(Review::SideType side){ return switchSide(side, m_FrontMasterWholePageImageList, m_BackMasterWholePageImageList, QList<QList<QImage> >()); };
	QList<QImage> getMasterWholePageImageList(Review::SideType side, int phase){ return getMasterWholePageImageList(side)[phase]; };
	QImage getMasterWholePageImage(Review::SideType side, int phase, int page){ return getMasterWholePageImageList(side, phase)[page]; };

	QList<QSize> getMasterWholeImageSize(Review::SideType side){ return switchSide(side, m_FrontMasterWholeImageSize, m_BackMasterWholeImageSize, QList<QSize>()); };

private:
	ReviewSequenceThread *m_VRSThread;

public:
	void setSequenceThread(ReviewSequenceThread *thread){
		if(m_VRSThread==thread){
			return;
		}
		setSequenceEnable(false);
		m_VRSThread = thread;
		if(m_VRSThread!=NULL){
			setSequenceEnable(true);
		}
	};
	ReviewSequenceThread *getSequenceThread() const { return m_VRSThread; };
	bool hasSequenceThread() const { return m_VRSThread!=NULL; };
	void setSequenceEnable(bool enable){ m_isSequenceEnable = enable; };
	bool isSequenceEnable(bool checkVRSEnableProperty=true) const { return (m_isSequenceEnable && hasSequenceThread()==true && (checkVRSEnableProperty==false || getProperty().VRSOperationEnable==true)); };

private:
	bool m_isSequenceEnable;

private:
	ReviewSequenceRequire VRSCommandToSafty(const ReviewSequenceRequire &reqItem){
		ReviewSequenceRequire ret = reqItem;
		if((ret.getMotorRequireTypeFlags() & ReviewSequence::MotorRequireMoveX)!=0 && ret.getMoveX()<=-100000){
			ret.setMoveX(-99999);
		}
		if((ret.getMotorRequireTypeFlags() & ReviewSequence::MotorRequireMoveY)!=0 && ret.getMoveY()<=-100000){
			ret.setMoveY(-99999);
		}
		return ret;
	};

	bool checkForExchangeBoard(Review::SideType oldSide, Review::SideType newSide, const OrganizedHistoryItem &oldHistory, const OrganizedHistoryItem &newHistory, const NGNailItem &oldNG, const NGNailItem &newNG){
		if(oldSide!=newSide || !(oldHistory==newHistory) || oldNG.phase!=newNG.phase){
			return true;
		}else{
			return false;
		}
	};

	bool	EscapeLastTime;
	int		ZHeightBeforeEscape;

	void sendVRSToOrigin(bool checkVRSEnable=true){
		/*
		const VRSSetting &vrs = getVRSSetting();

		ReviewSequenceRequire reqItem;
		reqItem.setMoveXY(vrs.getVRSSideSetting().MotorOrigin.x(), vrs.getVRSSideSetting().MotorOrigin.y());

		if(isSequenceEnable(checkVRSEnable)==true){
			getSequenceThread()->append( VRSCommandToSafty( reqItem ) );
		}
		*/
		ReviewSequenceRequire req;
		req.setMotorRequireTypeFlags(ReviewSequence::MotorRequireMoveOrigin);
		//req.setMoveXY(x, y);
		if(isSequenceEnable(checkVRSEnable)==true){
			getSequenceThread()->append( VRSCommandToSafty( req ) );
		}
		EscapeLastTime=false;
	};

	void sendVRSToEscapePosition(bool checkVRSEnable=true){
		const VRSSetting &vrs = getVRSSetting();

		ReviewSequenceRequire reqItem;
		reqItem.setMoveXY(vrs.getVRSSideSetting().EscapePosition.x(), vrs.getVRSSideSetting().EscapePosition.y());

		if(isSequenceEnable(checkVRSEnable)==true){
			getSequenceThread()->append( VRSCommandToSafty( reqItem ) );
		}
		sendVRSToMoveZ(vrs.getVRSSideSetting().EscapePosition.z(), true);
	};

	void sendVRSToMoveXY(int x, int y, bool checkVRSEnable=true){
		ReviewSequenceRequire req;
	if(EscapeLastTime==false){
			req.setMotorRequireTypeFlags(ReviewSequence::MotorRequireMoveXY);
			req.setMoveXY(x, y);
			if(isSequenceEnable(checkVRSEnable)==true){
				getSequenceThread()->append( VRSCommandToSafty( req ) );
			}
		}
		else{
			ReviewSequenceRequire req;
			req.setMotorRequireTypeFlags(ReviewSequence::MotorRequireMoveXYZ);
			req.setMoveXYZ(x, y ,ZHeightBeforeEscape);
			if(isSequenceEnable(checkVRSEnable)==true){
				getSequenceThread()->append( VRSCommandToSafty( req ) );
			}
		}
		EscapeLastTime=false;
	};
	void sendVRSToMoveXYZ(int x, int y,int z, bool checkVRSEnable=true){
		ReviewSequenceRequire req;
		req.setMotorRequireTypeFlags(ReviewSequence::MotorRequireMoveXYZ);
		req.setMoveXYZ(x, y ,z);
		EscapeLastTime=true;
		if(isSequenceEnable(checkVRSEnable)==true){
			getSequenceThread()->append( VRSCommandToSafty( req ) );
		}
	};
	void sendVRSToMoveXY(Review::SideType side, int phase, int page, int x, int y, bool checkVRSEnable=true){
		QPoint p = getMasterWholePageOutline(getCurrentSideType(), phase, page);

		int convertedX = x;
		int convertedY = y;

		int sx = x + p.x();
		int sy = y + p.y();

		if(getVRSAlignment(side).getAlignmentType()==Review::VRSAlingmentWholeImage){
			QTransform matrix = getVRSAlignment(side).getWholeAffinMatrix();
			
			convertedX = sx * matrix.m11() + sy * matrix.m12() + matrix.dx() + getVRSSetting().getVRSSideSetting().MotorOffset.x();// mx = ix * a + iy * b + c
			convertedY = sy * matrix.m21() + sy * matrix.m22() + matrix.dy() + getVRSSetting().getVRSSideSetting().MotorOffset.y();// my = ix * d + iy * e + f
		}else{
			QTransform matrix = getVRSAlignment(side).getEachPageAffinMatrix(page);
			
			convertedX = sx * matrix.m11() + sy * matrix.m12() + matrix.dx() + getVRSSetting().getVRSSideSetting().MotorOffset.x();// mx = ix * a + iy * b + c
			convertedY = sx * matrix.m21() + sy * matrix.m22() + matrix.dy() + getVRSSetting().getVRSSideSetting().MotorOffset.y();// my = ix * d + iy * e + f
		}

		convertedX = qBound(INT_MIN, convertedX, getSequenceThread()->pulsePerMM_x()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.width());
		convertedY = qBound(-99999, convertedY, getSequenceThread()->pulsePerMM_y()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.height());

		sendVRSToMoveXY(convertedX+VRSOffsetX, convertedY+VRSOffsetY, checkVRSEnable);
	};

	void sendVRSToMoveXYAsWhole(Review::SideType side, int phase, int page, int x, int y, bool checkVRSEnable=true){
		QPoint p = getMasterWholePageOutline(getCurrentSideType(), phase, page);

		int convertedX = x;
		int convertedY = y;

		int sx = x + p.x();
		int sy = y + p.y();

		QTransform matrix = getVRSAlignment(side).getWholeAffinMatrix();

		convertedX = sx * matrix.m11() + sy * matrix.m12() + matrix.dx() + getVRSSetting().getVRSSideSetting().MotorOffset.x();// mx = ix * a + iy * b + c
		convertedY = sx * matrix.m21() + sy * matrix.m22() + matrix.dy() + getVRSSetting().getVRSSideSetting().MotorOffset.y();// my = ix * d + iy * e + f

		convertedX = qBound(INT_MIN, convertedX, getSequenceThread()->pulsePerMM_x()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.width());
		convertedY = qBound(-99999, convertedY, getSequenceThread()->pulsePerMM_y()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.height());

		sendVRSToMoveXY(convertedX, convertedY, checkVRSEnable);

		//qDebug() << "x,y=" << x << "," << y;
		//qDebug() << "OutlineOffset:" << p;
		//qDebug() << "AffinMatrix:" << matrix;
		//qDebug() << "ConvertedXY=" << convertedX << "," << convertedY;
	};
	
	void sendVRSToMoveXYAsEachPage(Review::SideType side, int phase, int page, int x, int y, bool checkVRSEnable=true){
		if(phase<0 || page<0)return;

		QPoint p = getMasterWholePageOutline(getCurrentSideType(), phase, page);

		int convertedX = x;
		int convertedY = y;

		int sx = x + p.x();
		int sy = y + p.y();

		QTransform matrix = getVRSAlignment(side).getEachPageAffinMatrix(page);
		
		convertedX = sx * matrix.m11() + sy * matrix.m12() + matrix.dx() + getVRSSetting().getVRSSideSetting().MotorOffset.x();// mx = ix * a + iy * b + c
		convertedY = sx * matrix.m21() + sy * matrix.m22() + matrix.dy() + getVRSSetting().getVRSSideSetting().MotorOffset.y();// my = ix * d + iy * e + f

		convertedX = qBound(INT_MIN, convertedX, getSequenceThread()->pulsePerMM_x()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.width());
		convertedY = qBound(-99999, convertedY, getSequenceThread()->pulsePerMM_y()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.height());

		sendVRSToMoveXY(convertedX, convertedY, checkVRSEnable);
	};

	void sendVRSToMoveXY(const NGNailItem &item, bool checkVRSEnable=true){
		sendVRSToMoveXY(getSideType(item), item.phase, item.page, item.TargetPosX + item.NGImageWidth/2, item.TargetPosY + item.NGImageHeight/2, checkVRSEnable);
	};
	
	void sendVRSToMoveXY(Review::SideType side, const NGNailItem &item, bool checkVRSEnable=true){
		sendVRSToMoveXY(side, item.phase, item.page, item.TargetPosX + item.NGImageWidth/2, item.TargetPosY + item.NGImageHeight/2);
	};

	void sendVRSToMoveZ(int z, bool checkVRSEnable=true){
		ReviewSequenceRequire req;
		req.setMotorRequireTypeFlags(ReviewSequence::MotorRequireMoveZ);
		req.setMoveZ(z);
		ZHeightBeforeEscape=z;
		if(isSequenceEnable(checkVRSEnable)==true){
			getSequenceThread()->append(req);
		}
	};

	void sendVRSToMoveXYZ(Review::SideType side, int phase, int page, int x, int y, int z, bool checkVRSEnable=true){
		sendVRSToMoveXY(side, phase, page, x, y, checkVRSEnable);
		sendVRSToMoveZ(z, checkVRSEnable);
	};

	void	InitialCSVLotList(void);
	void	SaveBundleOnHistry(int CurrentRow ,int InspectionID ,XDateTime &InspectionTime);
};

#endif