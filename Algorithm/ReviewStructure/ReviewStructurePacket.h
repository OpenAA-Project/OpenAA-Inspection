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

#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"

#include "ReviewStructureItems.h"
#include "XReviewStructure.h"

/////////////////////////////////////////////////////
// ReviewGUI���瑗�M���Ă����p�P�b�g


// ?�X??�ǂݍ��ݗv��
// ?�X??�f??���ǂݍ��܂���
class	CmdLoadMainMaster : public GUIDirectMessage
{
public:
	// Send
	int		PhaseCode;
	int		PhaseCount;
	int		MachineID;
	int		MasterCode;
	int		viewNo;
	Review::SideType side;

	// Recieve
	bool	Ret;

	CmdLoadMainMaster(LayersBase *base):GUIDirectMessage(base),PhaseCode(-1),PhaseCount(-1),MachineID(-1),MasterCode(-1),viewNo(-1),side(Review::NoSide),Ret(false){};
};


// �X��?�u�ǂݍ��ݗv��
class	CmdLoadSlave	 : public GUIDirectMessage
{
public:
	int		PhaseCode;
	int		MasterCode;
	int		MachineID;
	int		LocalPage;
	bool	Ret;

	CmdLoadSlave(LayersBase *base):GUIDirectMessage(base),PhaseCode(-1),MasterCode(-1),MachineID(-1),LocalPage(-1),Ret(false){};
};

class	CmdLoadPageImage : public GUIDirectMessage
{
public:
	int		MasterCode;
	int		MachineID;
	Review::SideType side;
	int		Phase;
	bool	Ret;

	CmdLoadPageImage(LayersBase *base):GUIDirectMessage(base),MasterCode(-1),MachineID(-1),side(Review::NoSide),Phase(-1),Ret(false){};
};

// ���b�g�ꗗ�̎擾
class	CmdServerSelectLotList : public GUIDirectMessage
{
public:
	// Send
	int		MasterCode;
	int		MachineID;
public:
	// Recive
	LotInfoList	list;
	bool		Ret;
public:
	CmdServerSelectLotList(LayersBase *base):GUIDirectMessage(base),MasterCode(-1),MachineID(-1),list(),Ret(false){};
};

// ���b�g�̃Z�b�g
class	CmdServerSetLot : public GUIDirectMessage
{
public:
	// Send
	QString LotFileName;// xml�t?�C����
	Review::SideType side;// ?���w��
	int viewNo;// ��
public:
	// Recive
	bool	Ret;
public:
	CmdServerSetLot(LayersBase *base)
		:GUIDirectMessage(base),LotFileName(/**/""),side(Review::NoSide),viewNo(-1),Ret(false){};
};

class	CmdSetMachineID : public GUIDirectMessage
{
public:
	// Send
	int	MachineIDFront;
	int	MachineIDBack;
public:
	CmdSetMachineID(LayersBase *base)
		:GUIDirectMessage(base),MachineIDFront(-1),MachineIDBack(-1){}
};


// ���b�g�ꗗ�̗v��
class	CmdServerReqCurrentLot : public GUIDirectMessage
{
public:
	// Recive
	LotInfoItem FrontCurrentLotInfo;
	LotInfoItem BackCurrentLotInfo;
	LotInfoList FrontLotList;
	LotInfoList BackLotList;
	QStringList FrontReqServerEnumTableList;
	QStringList BackReqServerEnumTableList;
	bool	Ret;
public:
	CmdServerReqCurrentLot(LayersBase *base)
		:GUIDirectMessage(base),FrontCurrentLotInfo(),BackCurrentLotInfo(),FrontLotList(),BackLotList(),FrontReqServerEnumTableList(),BackReqServerEnumTableList(),Ret(false){};
};

// ���b�g���X�g�̃A�b�v�f?�g�Ǝ擾
class	CmdServerUpdateLotList : public GUIDirectMessage
{
public:
	// Recive
	LotInfoList	FrontLotList;

	LotInfoList	BackLotList;
public:
	CmdServerUpdateLotList(LayersBase *base)
		:GUIDirectMessage(base),FrontLotList(),BackLotList(){};
};

class	CmdUpdateForSaveLotList : public GUIDirectMessage
{
public:
	// Recive
public:
	CmdUpdateForSaveLotList(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdReqForSaveBundle: public GUIDirectMessage
{
public:
	int	CurerntRow;
	int	InspectionID;
	XDateTime	InspectionTime;
	int	Halt;
public:
	CmdReqForSaveBundle(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdReqForSaveNGList: public GUIDirectMessage
{
public:
	ForSaveOneInspection	Data;
	bool	Top;
	int		NGPoints;
public:
	CmdReqForSaveNGList(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdSetCurrentNGInfo: public GUIDirectMessage
{
public:
	int			InspectedMachine;
	XDateTime	InspectionTimeFirst;
	XDateTime	InspectionTimeLast;
	int			NGCountTop;
	int			NGCountBack;
public:
	CmdSetCurrentNGInfo(LayersBase *base)
		:GUIDirectMessage(base){	NGCountTop=0;	NGCountBack=0;	InspectedMachine=0;	};
};

class	CmdSetCurrentRowNGListForSave: public GUIDirectMessage
{
public:
	int		CurrentRow;
public:
	CmdSetCurrentRowNGListForSave(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdSetHaltForSave: public GUIDirectMessage
{
public:
	int		Halt;
public:
	CmdSetHaltForSave(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdSetCountOkNgForSave: public GUIDirectMessage
{
public:
	int		CountOK;
	int		CountNG;
	int		CountHalt;
public:
	CmdSetCountOkNgForSave(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdSetFKeyForSave: public GUIDirectMessage
{
public:
	int		Key;
public:
	CmdSetFKeyForSave(LayersBase *base)
		:GUIDirectMessage(base){};
};
class	CmdRemoveFKeyForSave: public GUIDirectMessage
{
public:

public:
	CmdRemoveFKeyForSave(LayersBase *base)
		:GUIDirectMessage(base){};
};


// XML��IST?�O�P�ɂ��P�v�f�Ƃ��闚�����X�g���Ԃ�
// ���g��IST�ւ�?�C��?�ϐ��������A
class	CmdReqOrganizedHistoryList : public GUIDirectMessage
{
public:
	// Recive
	OrganizedHistoryListPtr listPtr;
	bool Ret;
public:
	CmdReqOrganizedHistoryList(LayersBase *base)
		:GUIDirectMessage(base),listPtr(NULL),Ret(false){};
};

// NGNailItem�̏�������XML��NGI�̗v�f�Ƃ���F�L?�̏������Y�t����
// ���łɕt�������Ă����ꍇ�͏㏑��������
// CurrentNG�ɑΉ�����XML?�O�𐶐����AXML�T?�o?��F�L?���t?���ꂽXML?���ɍX�V������
class	CmdSetFKeyToNGNail : public GUIDirectMessage
{
public:
	// Send
	Review::FKey key;
	// Recieve
	QColor	FKeyColor;
	bool Ret;
public:
	CmdSetFKeyToNGNail(LayersBase *base)
		:GUIDirectMessage(base),key(Review::NoFKey),FKeyColor(),Ret(false){};
};

// NGNailItem�̏�������XML��NGI��F�L?�v�f���폜����
// F�L?�v�f�������ꍇ�͉������Ȃ�
// CurrentNGIndexes�����I�΂���
class	CmdClearFKeyToNGNail : public GUIDirectMessage
{
public:
	// Recieve
	QColor CheckedColor;
	bool Ret;
public:
	CmdClearFKeyToNGNail(LayersBase *base)
		:GUIDirectMessage(base),CheckedColor(),Ret(false){};
};

// �S�̉摜���Ԃ�
class	CmdReqWholeImage : public GUIDirectMessage
{
	friend class ReviewPIBase;
private:
	// Send
	int m_ReqPhase;// �t�F�C�Y
	QSize m_ReqSize;// �o�̓T�C�Y
	// Recieve
	QImage m_FrontWholePic;
	QImage m_BackWholePic;
	QSize m_FrontWholeOrizinalSize;
	QSize m_BackWholeOrizinalSize;
	qreal m_FrontZoomRate;
	qreal m_BackZoomRate;
	int m_FrontSkipMasterImageRate;
	int m_BackSkipMasterImageRate;
public:
	double ZoomImageFromFile;
public:
	void setReqPhase(int phase){ m_ReqPhase = phase; };
	void setReqSize(const QSize &size){ m_ReqSize = size; };
	void setReqWidth(int width){ QSize size = reqSize(); size.setWidth(width); setReqSize(size); };
	void setReqHeight(int height){ QSize size = reqSize(); size.setHeight(height); setReqSize(size); };

	int reqPhase() const { return m_ReqPhase; };
	QSize reqSize() const { return m_ReqSize; };
	int reqWidth() const { return reqSize().width(); };
	int reqHeight() const { return reqSize().height(); };

private:
	void _setWholePic(Review::SideType side, const QImage &image){ Review::switchSideSetValue(side, m_FrontWholePic, m_BackWholePic, image); };
	void _setWholePic(const QImage &frontImage, const QImage &backImage){ m_FrontWholePic = frontImage; m_BackWholePic = backImage; };
	void _setWholeSize(Review::SideType side, const QSize &size){ Review::switchSideSetValue(side, m_FrontWholeOrizinalSize, m_BackWholeOrizinalSize, size); };
	void _setWholeSize(const QSize &frontSize, const QSize &backSize){ m_FrontWholeOrizinalSize = frontSize; m_BackWholeOrizinalSize = backSize; };
	void _setSkipMasterImageRate(Review::SideType side, int rate){ Review::switchSideSetValue(side, m_FrontSkipMasterImageRate, m_BackSkipMasterImageRate, rate); };
	void _setSkipMasterImageRate(int frontRate, int backRate){ m_FrontSkipMasterImageRate = frontRate; m_BackSkipMasterImageRate = backRate; };
	void _setZoomRate(Review::SideType side, qreal rate){ Review::switchSideSetValue(side, m_FrontZoomRate, m_BackZoomRate, rate); };
	void _setZoomRate(qreal frontZoomRate, qreal backZoomRate){ m_FrontZoomRate = frontZoomRate; m_BackZoomRate = backZoomRate; };

public:
	QImage getWholePic(Review::SideType side) const { return Review::switchSide(side, m_FrontWholePic, m_BackWholePic); };
	QSize getWholeSize(Review::SideType side) const { return Review::switchSide(side, m_FrontWholeOrizinalSize, m_BackWholeOrizinalSize); };
	int getSkipMasterImageRate(Review::SideType side) const { return Review::switchSide(side, m_FrontSkipMasterImageRate, m_BackSkipMasterImageRate, -1); };
	qreal getZoomRate(Review::SideType side) const { return Review::switchSide(side, m_FrontZoomRate, m_BackZoomRate, -1.0); };

public:
	CmdReqWholeImage(LayersBase *base)
		:GUIDirectMessage(base)
		,m_ReqPhase(-1)					,m_ReqSize()
		,m_FrontWholePic()				,m_BackWholePic()
		,m_FrontZoomRate(-1)			,m_BackZoomRate(-1)
		,m_FrontSkipMasterImageRate(-1)	,m_BackSkipMasterImageRate(-1)
		,ZoomImageFromFile(1.0){};
};

class	CmdReqWholeImageInfo : public GUIDirectMessage
{
public:
	QList<QSize> FrontWholeOrizinalSize;
	QList<QSize> BackWholeOrizinalSize;
	QList<QList<QPoint> > FrontOutlineOffset;
	QList<QList<QPoint> > BackOutlineOffset;
	QList<QList<QPoint> > FrontOutlineDrawOffset;
	QList<QList<QPoint> > BackOutlineDrawOffset;

	qreal zoomRate;// 0~

	QSize getWholeOriginalSize(Review::SideType side, int phase){
		if(Review::isFront(side)==true && FrontWholeOrizinalSize.count()>phase){
			return FrontWholeOrizinalSize[phase];
		}else if(Review::isBack(side)==true && BackWholeOrizinalSize.count()>phase){
			return BackWholeOrizinalSize[phase];
		}else{
			return QSize();
		}
	};

	QList<QPoint> getOutlineOffsetList(Review::SideType side, int phase){
		if(Review::isFront(side)==true && FrontOutlineOffset.count()>phase){
			return FrontOutlineOffset[phase];
		}else if(Review::isBack(side)==true && BackOutlineOffset.count()>phase){
			return BackOutlineOffset[phase];
		}else{
			return QList<QPoint>();
		}
	};

	QList<QPoint> getOutlineDrawOffsetList(Review::SideType side, int phase){
		if(Review::isFront(side)==true && FrontOutlineDrawOffset.count()>phase){
			return FrontOutlineDrawOffset[phase];
		}else if(Review::isBack(side)==true && BackOutlineDrawOffset.count()>phase){
			return BackOutlineDrawOffset[phase];
		}else{
			return QList<QPoint>();
		}
	};

public:
	CmdReqWholeImageInfo(LayersBase *base)
		:GUIDirectMessage(base),FrontWholeOrizinalSize(),BackWholeOrizinalSize(),FrontOutlineOffset(),BackOutlineOffset(),zoomRate(1.0){};
};

// �I�𒆂̗������ݒ�
class	CmdSetCurrentHistory : public GUIDirectMessage
{
public:
	// Send
	//Review::RefType refType;
	int Index;
	int InspectID;
	//OrganizedHistoryIndex OrgHistoryPtr;
	//OrganizedHistoryItem OrgHistoryItem;
	// Recieve
	bool Ret;
public:
	CmdSetCurrentHistory(LayersBase *base)
		:GUIDirectMessage(base),Index(-1),InspectID(-1),Ret(false){};
};

// �I�𒆂̗������擾
class	CmdReqCurrentHistory : public GUIDirectMessage
{
private:
	// Recieve
	OrganizedHistoryIndex m_OrgHistoryPtr;
	int m_index;
public:
	void setOrganizedHistroyPtr(const OrganizedHistoryIndex ptr){ m_OrgHistoryPtr = ptr; };
	const OrganizedHistoryIndex historyPrt() const { return m_OrgHistoryPtr; }
	void setIndex(int i){ m_index = i; };
	int index() const { return m_index; };
	bool Ret;
public:
	CmdReqCurrentHistory(LayersBase *base)
		:GUIDirectMessage(base),m_OrgHistoryPtr(NULL),m_index(-1),Ret(false){};
};

// �������C�u�����̃n�b�V�����v������
class	CmdReqInsLib : public GUIDirectMessage
{
public:
	// Recieve
	InsLibraryHash FrontInsLibHash;
	InsLibraryHash BackInsLibHash;

	bool Ret;
public:
	CmdReqInsLib(LayersBase *base)
		:GUIDirectMessage(base),FrontInsLibHash(),BackInsLibHash(),Ret(false){};
};

// NGNail�̃��X�g��??�g�����w�肷��
class	CmdSetSortNGOrder : public GUIDirectMessage
{
public:
	// Send
	Review::OrderOfSortNG order;
public:
	CmdSetSortNGOrder(LayersBase *base)
		:GUIDirectMessage(base),order(Review::_Order_YLesser){};
};

class	CmdReqSortNGOrder : public GUIDirectMessage
{
public:
	// Recieve
	Review::OrderOfSortNG order;
public:
	CmdReqSortNGOrder(LayersBase *base)
		:GUIDirectMessage(base),order(Review::_Order_YLesser){};
};

// HistoryList��??�g�����w�肷��
class	CmdSetSortHistoryOrder : public GUIDirectMessage
{
public:
	// Send
	Review::OrderOfSortHistory order;
public:
	CmdSetSortHistoryOrder(LayersBase *base)
		:GUIDirectMessage(base),order(Review::OrderOfSortHistory::_Order_InspectionIDGreater){};
};

class	CmdReqSortHistoryOrder : public GUIDirectMessage
{
public:
	// Recieve
	Review::OrderOfSortHistory order;
public:
	CmdReqSortHistoryOrder(LayersBase *base)
		:GUIDirectMessage(base),order(Review::OrderOfSortHistory::_Order_InspectionIDGreater){};
};

// ���݂�NG���猩�āA�O����NG�����邩�ǂ���
class	CmdReqAdjacentCurrentNG : public GUIDirectMessage
{
private:
	// Recieve
	NGNailIndex m_nextNG;		// ����NG
	NGNailIndex m_currentNG;
	NGNailIndex m_previousNG;	// �O��NG
	OrganizedHistoryIndex m_nextHistory;		// ���̗���
	OrganizedHistoryIndex m_currentHistory;
	OrganizedHistoryIndex m_previousHistory;	// �����̗���
	int		m_currentNGIndex;
	Review::SideType m_currentSide;

public:
	bool	existNextNG() const { return (nextNG()!=NULL); };		// ����NG�����邩�ǂ���
	bool	existCurrentNG() const { return (currentNG()!=NULL); };		// ���݂�NG�����邩�ǂ���
	bool	existPreviousNG() const { return (previousNG()!=NULL); };	// ������NG�����邩�ǂ���
	bool	existNextHistory() const { return (nextHistory()!=NULL); };		// ���̗��������邩�ǂ���
	bool	existCurrentHistory() const { return (currentHistory()!=NULL); };	// ���݂̗��������邩�ǂ���
	bool	existPreviousHistory() const { return (previousHistory()!=NULL); };	// �����̗��������邩�ǂ���

	const NGNailIndex nextNG() const { return m_nextNG; };		// ����NG
	const NGNailIndex currentNG() const { return m_currentNG; };
	const NGNailIndex previousNG() const { return m_previousNG; };	// �O��NG
	const OrganizedHistoryIndex nextHistory() const { return m_nextHistory; };		// ���̗���
	const OrganizedHistoryIndex currentHistory() const { return m_currentHistory; };
	const OrganizedHistoryIndex previousHistory() const { return m_previousHistory; };	// �����̗���
	int		currentNGIndex() const { return m_currentNGIndex; };
	Review::SideType currentSide() const { return m_currentSide; };
	
	void setNextNG(const NGNailIndex ng){ m_nextNG = ng; };		// ����NG
	void setCurrentNG(const NGNailIndex ng){ m_currentNG = ng; };
	void setPreviousNG(const NGNailIndex ng){ m_previousNG = ng; };	// �O��NG
	void setNextHistory(const OrganizedHistoryIndex history){ m_nextHistory = history; };		// ���̗���
	void setCurrentHistory(const OrganizedHistoryIndex history){ m_currentHistory = history; };
	void setPreviousHistory(const OrganizedHistoryIndex history){ m_previousHistory = history; };	// �����̗���
	void setCurrentNGIndex(int index){ m_currentNGIndex = index; };
	void setCurrentSide(Review::SideType side){ m_currentSide = side; };

	bool	Ret;
public:
	CmdReqAdjacentCurrentNG(LayersBase *base)
		:GUIDirectMessage(base),m_nextNG(NULL),m_currentNG(NULL),m_previousNG(NULL),m_nextHistory(NULL),m_currentHistory(NULL),m_previousHistory(NULL)
		,m_currentNGIndex(-1),m_currentSide(Review::NoSide),Ret(false){};
};

// NG���O���Ɉړ��������R?���h
class	CmdMoveCurrentNGNail : public GUIDirectMessage
{
public:
	// Send
	Review::Direction direction;
	NGNailIndex CurrentNGPtr;// �ύX���̒���NGNail
	int index;
	// Recieve
	bool	Ret;
public:
	CmdMoveCurrentNGNail(LayersBase *base)
		:GUIDirectMessage(base),direction(Review::Next),CurrentNGPtr(NULL),index(-1),Ret(false){};
};

// �������O���Ɉړ��������R?���h
class	CmdMoveCurrentHistory : public GUIDirectMessage
{
public:
	// Send
	Review::Direction direction;
	// Recieve
	OrganizedHistoryIndex CurrentHistoryPtr;
	// Recieve
	bool	Ret;
public:
	CmdMoveCurrentHistory(LayersBase *base)
		:GUIDirectMessage(base),direction(Review::Next),CurrentHistoryPtr(NULL),Ret(false){};
};

// ������NG�܂ňړ��������R?���h
class	CmdMoveCurrentHistoryToNGBoard : public GUIDirectMessage
{
public:
	// Send
	Review::Direction direction;
	// Recieve
	OrganizedHistoryIndex CurrentHistoryPtr;
	// Recieve
	bool	Ret;
public:
	CmdMoveCurrentHistoryToNGBoard(LayersBase *base)
		:GUIDirectMessage(base),direction(Review::Next),CurrentHistoryPtr(NULL),Ret(false){};
};

// NG�̈ʒu���ݒ肷���R?���h
class	CmdSetCurrentNGNail : public GUIDirectMessage
{
public:
	// Send
	Review::RefType refType;

	// refType==Ref_Index
	Review::ListLocate locate;	// Front	: �擪�Ɉړ�
								// End		: �Ō����Ɉړ�
								// Manual	: Index�Ɉړ�
	int Index;// �g���Ȃ��ꍇ-1(default)
	// refType==Ref_Instance
	NGNailItemRef refItem;
	// Recieve
	bool	Ret;
public:
	CmdSetCurrentNGNail(LayersBase *base)
		:GUIDirectMessage(base),refType(Review::Ref_Index),locate(Review::First),Index(-1),refItem(NGNailItemRef()),Ret(false){};
};

// �ǂݍ�����?�X??�f??�̏������擾
class	CmdReqMasterDataInfo : public GUIDirectMessage
{
public:
	// Recieve
	MasterDataInfo FrontMasterDataInfo;
	MasterDataInfo BackMasterDataInfo;
	bool	Ret;
public:
	Review::OrganizedSideType sideType(){
		if(FrontMasterDataInfo.isEmpty()==false && BackMasterDataInfo.isEmpty()==false){
			return Review::OrganizedSideType::Both;
		}
		if(FrontMasterDataInfo.isEmpty()==false && BackMasterDataInfo.isEmpty()==true){
			return Review::OrganizedSideType::FrontOnly;
		}
		if(FrontMasterDataInfo.isEmpty()==true && BackMasterDataInfo.isEmpty()==false){
			return Review::OrganizedSideType::BackOnly;
		}
		return Review::OrganizedSideType::None;
	};

	MasterDataInfo getInfo(Review::SideType side){
		if(Review::isFront(side)==true){
			return FrontMasterDataInfo;
		}else{
			return BackMasterDataInfo;
		}
	};
public:
	CmdReqMasterDataInfo(LayersBase *base)
		:GUIDirectMessage(base),FrontMasterDataInfo(),BackMasterDataInfo(),Ret(false){};
};

// ����NGNail��?�F�b�N�ςݏ������t?����
class	CmdSetCurrentNGChecked : public GUIDirectMessage
{
public:
	// Send
	bool	isChecked;
	// Recieve
	bool	Ret;
public:
	CmdSetCurrentNGChecked(LayersBase *base)
		:GUIDirectMessage(base),isChecked(true),Ret(false){};
};

// ����History��NGNail��?�F�b�N�ςݏ������t?����
class	CmdSetNGChecked : public GUIDirectMessage
{
public:
	Review::SideType side;// ?���w��
	int begin;// �J�nIndex
	int length;// ����>=0
	// Recieve
	bool	Ret;
public:
	CmdSetNGChecked(LayersBase *base)
		:GUIDirectMessage(base),side(Review::NoSide),begin(0),length(1),Ret(false){};
};

// F�L?�̃J��?���X�g���擾
class	CmdReqFKeyColorList : public GUIDirectMessage
{
public:
	// Recieve
	QList<QColor> list;
	bool	Ret;
public:
	CmdReqFKeyColorList(LayersBase *base)
		:GUIDirectMessage(base),Ret(false){};
};

// ?�X??�摜���X�V
class	CmdUpdateMasterBuff : public GUIDirectMessage
{
public:
	// Send
	Review::SideType side;
	int		phase;
	// Recieve
	bool	Ret;
public:
	CmdUpdateMasterBuff(LayersBase *base)
		:GUIDirectMessage(base),side(Review::NoSide),phase(-1),Ret(false){};
};

// ?�X??�摜�̈ꕔ���擾
class	CmdReqMasterImagePiece : public GUIDirectMessage
{
public:
	// Send
	Review::SideType side;
	int	phase;
	int page;
	int MasterX;
	int MasterY;
	int Width;
	int Height;
	// Recieve
	QImage image;
	bool Ret;

public:
	void setData(Review::SideType side, NGNailItem &item){
		this->side = side;
		this->phase = item.phase;
		this->page = item.page;
		MasterX = item.MasterPosX;
		MasterY = item.MasterPosY;
		Width = item.NGImageWidth;
		Height = item.NGImageHeight;
	};
	void setData(Review::SideType side, int phase, int page, const QRect &rect){
		MasterX = rect.left();
		MasterY = rect.top();
		Width = rect.width();
		Height = rect.height();
		this->phase = phase;
		this->page = page;
	};
	static CmdReqMasterImagePiece fromNGNailItem(LayersBase *Base, Review::SideType side, NGNailItem &item){
		CmdReqMasterImagePiece ret(Base);
		ret.side = side;
		ret.phase = item.phase;
		ret.page = item.page;
		ret.MasterX = item.MasterPosX;
		ret.MasterY = item.MasterPosY;
		ret.Width = item.NGImageWidth;
		ret.Height = item.NGImageHeight;

		return ret;
	};

public:
	CmdReqMasterImagePiece(LayersBase *Base, Review::SideType side, NGNailItem &item)
		:GUIDirectMessage(Base),image(),Ret(false)
	{
		setData(side, item);
	};
	CmdReqMasterImagePiece(LayersBase *base)
		:GUIDirectMessage(base),side(Review::NoSide),phase(-1),page(-1),MasterX(-1),MasterY(-1),Width(-1),Height(-1),image(),Ret(false){};
};

class CmdReqMasterImagePieceOnOneImage : public GUIDirectMessage
{
public:
	// Send
	Review::SideType side;
	int	phase;
	int MasterX;
	int MasterY;
	int Width;
	int Height;
	// Recieve
	QImage image;
	bool Ret;

public:
	void setData(Review::SideType side, int phase, const QRect& rect){
		this->side = side;
		this->phase = phase;

		MasterX = rect.left();
		MasterY = rect.top();
		Width = rect.width();
		Height = rect.height();
	};
public:
	CmdReqMasterImagePieceOnOneImage(LayersBase *base)
		:GUIDirectMessage(base),side(Review::NoSide),phase(-1),MasterX(-1),MasterY(-1),Width(-1),Height(-1),image(),Ret(false){};
};
// �w�肵���������X�g�̃C���f�b�N�X�A��������EID�ł��Ă������P�̗����ɂ��Ă��ׂĂ�NGNail��?�F�b�N�ς݂ł��邩�ǂ����𒲍�����
class	CmdReqHistoryAllChecked : public GUIDirectMessage
{
public:
	// Send
	int index;
	int EID;
	// Recieve
	bool isAllChecked;
	bool Ret;
public:	
	CmdReqHistoryAllChecked(LayersBase *Base)
		:GUIDirectMessage(Base),index(-1),EID(-1),isAllChecked(false),Ret(false)
	{};
};

//class	CmdReqNGShape : public GUIDirectMessage
//{
//public:
//	// Send
//	int LC;
//	int TC;
//	// Recieve
//	LibNGTypeItem::NGShapeType NGShape;
//	bool Ret;
//public:
//	CmdReqNGShape(LayersBase *Base)
//		:GUIDirectMessage(Base),LC(-1),TC(-1),NGShape(LibNGTypeItem::NGShapeType::NG_Circle),Ret(false)
//	{};
//};
//
//class	CmdReqCurrentNGPointListWithShape : public GUIDirectMessage
//{
//public:
//	// Recieve
//	ReviewNGPointWithShapeList list;
//	bool Ret;
//public:
//	CmdReqCurrentNGPointListWithShape(LayersBase *Base)
//		:GUIDirectMessage(Base),list(),Ret(false)
//	{};
//};

class	CmdUpdateCurrentLotData : public GUIDirectMessage
{
public:
	CmdUpdateCurrentLotData(LayersBase *base)
		:GUIDirectMessage(base){};
};

// ?�X??�f??�̏������擾����
class	CmdReqMasterInfoFromDataBase : public GUIDirectMessage
{
public:
	// Send
	int MasterCode;

	// Recieve
	MasterDataInfo info;
	bool Ret;
public:
	CmdReqMasterInfoFromDataBase(LayersBase *Base):GUIDirectMessage(Base),MasterCode(-1),info(),Ret(false){};
};

// ���C��?�̃��������J������
class	CmdFreeLayersImageMemory : public GUIDirectMessage
{
public:
	CmdFreeLayersImageMemory(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdClearSideLot : public GUIDirectMessage
{
public:
	Review::SideType side;

public:
	CmdClearSideLot(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdReqPCEList : public GUIDirectMessage
{
public:
	// Receive
	PCEList FrontList;
	PCEList BackList;
public:
	CmdReqPCEList(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdReqSaveFormatMacroList : public GUIDirectMessage
{
public:
	//Recieve
	QList<QPair<QString, QString> > macroSimbolInfoPairList;

public:
	CmdReqSaveFormatMacroList(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdSaveCurrentNGImage : public GUIDirectMessage
{
public:
	// Send
	int NGSingRoundSize;
	bool drawNGShape;

	// Recieve
	bool Ret;

public:
	CmdSaveCurrentNGImage(LayersBase *Base):GUIDirectMessage(Base),NGSingRoundSize(0),drawNGShape(false),Ret(false){};
};

class CmdSaveCurrentHistoryNGImages : public GUIDirectMessage
{
public:
	// Send
	int NGSingRoundSize;
	bool drawNGShape;

	// Recieve
	bool Ret;

public:
	CmdSaveCurrentHistoryNGImages(LayersBase *Base):GUIDirectMessage(Base),NGSingRoundSize(0),drawNGShape(false),Ret(false){};
};

class CmdUpdateLotInfoList : public GUIDirectMessage
{
public:
	LotInfoList FrontLotList;
	LotInfoList BackLotList;
public:
	CmdUpdateLotInfoList(LayersBase *Base):GUIDirectMessage(Base),FrontLotList(),BackLotList(){};
};

class CmdReqCurrentLotAllList : public GUIDirectMessage
{
public:
	LotInfoList FrontLotList;
	LotInfoList BackLotList;

public:
	CmdReqCurrentLotAllList(LayersBase *Base):GUIDirectMessage(Base),FrontLotList(),BackLotList(){};
};

class CmdReqCurrentLotInfoData : public GUIDirectMessage
{
public:
	QString	FrontLotID;
	QString	FrontLotName;
	QString	BackLotID;
	QString	BackLotName;

public:
	CmdReqCurrentLotInfoData(LayersBase *Base):GUIDirectMessage(Base){};
};
//class CmdReqCurrentVRSPosition : public GUIDirectMessage
//{
//public:
//	int x;
//	int y;
//	int z;
//	bool Ret;
//
//public:
//	void setPoint(int x_, int y_){ x = x_; y = y_; };
//	void setPoint(const QPoint &p){ setPoint(p.x(), p.y()); };
//	QPoint point(){ return (Ret==true ? QPoint(x,y) : QPoint()); };
//
//public:
//	CmdReqCurrentVRSPosition(LayersBase *Base):GUIDirectMessage(Base),x(0),y(0),z(0),Ret(false){};
//};
//
//class CmdSetCurrentVRSPosition : public GUIDirectMessage
//{
//public:
//	int x() const { return _x; };
//	int y() const { return _y; };
//	int z() const { return _z; };
//
//	bool isEnableX() const { return _x_enable; };
//	bool isEnableY() const { return _y_enable; };
//	bool isEnableZ() const { return _z_enable; };
//
//	void setX(int x_){ _x = x_; setEnableX(true); };
//	void setY(int y_){ _y = y_; setEnableY(true); };
//	void setZ(int z_){ _z = z_; setEnableZ(true); };
//	
//	void set(int x_){ setX(x_); };
//	void set(int x_, int y_){ setX(x_); setY(y_); };
//	void set(int x_, int y_, int z_){ setX(x_); setY(y_); setZ(z_); };
//
//	void setEnableX(bool enable){ _x_enable = enable; };
//	void setEnableY(bool enable){ _y_enable = enable; };
//	void setEnableZ(bool enable){ _z_enable = enable; };
//	
//	void setEnable(bool x_enable){ setEnableX(x_enable); };
//	void setEnable(bool x_enable, bool y_enable){ setEnable(x_enable); setEnableY(y_enable); };
//	void setEnable(bool x_enable, bool y_enable, bool z_enable){ setEnable(x_enable, y_enable); setEnableZ(z_enable); };
//
//private:
//	int _x;
//	int _y;
//	int _z;
//
//	bool _x_enable;
//	bool _y_enable;
//	bool _z_enable;
//
//public:
//	void setPoint(int x_, int y_){ set(x_, y_); setEnable(true, true); };
//	void setPoint(const QPoint &p){ setPoint(p.x(), p.y()); };
//	QPoint point() const { return QPoint(x(),y()); };
//
//public:
//	CmdSetCurrentVRSPosition(LayersBase *Base):GUIDirectMessage(Base),_x(0),_y(0),_z(0),_x_enable(false),_y_enable(false),_z_enable(false){};
//};

class CmdReqVRSSetting : public GUIDirectMessage
{
public:
	VRSSetting setting;

public:
	CmdReqVRSSetting(LayersBase *Base):GUIDirectMessage(Base),setting(){};
};

class CmdSetVRSSetting : public GUIDirectMessage
{
public:
	VRSSetting setting;

public:
	CmdSetVRSSetting(LayersBase *Base):GUIDirectMessage(Base),setting(){};
};

class CmdReqVRSValue : public GUIDirectMessage
{
public:
	int reqMotorFlags;

	int x_position;
	int y_position;
	int z_position;

	int x_pulusPerMM;
	int y_pulusPerMM;
	int z_pulusPerMM;

	bool x_enable;
	bool y_enable;
	bool z_enable;

public:
	CmdReqVRSValue(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdSetVRSValue : public GUIDirectMessage
{
private:
	int _x;
	int _y;
	int _z;

	bool _x_set;
	bool _y_set;
	bool _z_set;

public:
	int x(void) const { return _x; };
	int y(void) const { return _y; };
	int z(void) const { return _z; };

	void setEnableX(bool enable){ _x_set = enable; };
	void setEnableY(bool enable){ _y_set = enable; };
	void setEnableZ(bool enable){ _z_set = enable; };

	bool isEnableX(void) const { return _x_set; };
	bool isEnableY(void) const { return _y_set; };
	bool isEnableZ(void) const { return _z_set; };

	void setX(int x){ _x = x; _x_set = true; };
	void setY(int y){ _y = y; _y_set = true; };
	void setZ(int z){ _z = z; _z_set = true; };
	void setXY(int x, int y){ setX(x); setY(y); };
	void setXYZ(int x, int y, int z){ setXY(x,y); setZ(z); };

public:
	CmdSetVRSValue(LayersBase *Base):GUIDirectMessage(Base),_x(0),_y(0),_z(0),_x_set(false),_y_set(false),_z_set(false){};
};

class CmdReqMasterImageList : public GUIDirectMessage
{
public:
	class ConstImageList{
	protected:
		ConstImageList(){};
	public:
		ConstImageList(const QList<QList<QImage> > &list=QList<QList<QImage> >())
			:m_imageList(list)
		{};
		ConstImageList(ConstImageList &other):m_imageList(other.getImageList()){};

	public:
		const QList<QList<QImage> > getImageList() const { return m_imageList; };

	public:
		const QList<QList<QImage> > m_imageList;

	protected:
		ConstImageList &operator =(const ConstImageList &other){ return *this; };
	};

public:
	ConstImageList *FrontImageList;
	ConstImageList *BackImageList;

	QList<QList<QPoint> > FrontOutlineList;
	QList<QList<QPoint> > BackOutlineList;

	int MasterImageNormalizeZoomRate;

public:
	void setImageList(Review::SideType side, ConstImageList *ptr){
		if(Review::isFront(side)==true){
			if(FrontImageList!=NULL){
				delete FrontImageList;
			}
			FrontImageList = ptr;
		}else if(Review::isBack(side)==true){
			if(BackImageList!=NULL){
				delete BackImageList;
			}
			BackImageList = ptr;
		}else{
			// none
		}
	};
	void setImageList(ConstImageList *frontPtr, ConstImageList *backPtr){
		setImageList(Review::Front, frontPtr);
		setImageList(Review::Back, backPtr);
	};
	void setOutlineList(Review::SideType side, QList<QList<QPoint> > outlineList){
		if(Review::isFront(side)==true){
			FrontOutlineList = outlineList;
		}else if(Review::isBack(side)==true){
			BackOutlineList = outlineList;
		}else{
			// none
		}
	};
	void setOutlineList(const QList<QList<QPoint> > &frontOutlineList, const QList<QList<QPoint> > &backOutlineList){
		setOutlineList(Review::Front, frontOutlineList);
		setOutlineList(Review::Back, backOutlineList);
	}

	QList<QList<QImage> > getImageList(Review::SideType side) const {
		QList<QList<QImage> > flist,blist;
		if(FrontImageList!=NULL){
			flist = FrontImageList->getImageList();
		}
		if(BackImageList!=NULL){
			blist = BackImageList->getImageList();
		}
		return Review::switchSide(side, flist, blist, QList<QList<QImage> >());
	};
	QList<QImage> getImageList(Review::SideType side, int phase) const {
		if(phase<0)return QList<QImage>();

		QList<QList<QImage> > list = getImageList(side);
		
		if(Review::isIndexEnableList(phase, list)==false){
			return QList<QImage>();
		}

		return list[phase];
	};
	QImage getImage(Review::SideType side, int phase, int page) const {
		if(phase<0 || page<0)return QImage();

		QList<QImage> list = getImageList(side, phase);

		if(Review::isIndexEnableList(page, list)==false){
			return QImage();
		}

		return list[page];
	};
	QList<QList<QPoint> > getOutlineOffsetList(Review::SideType side) const { return Review::switchSide(side, FrontOutlineList, BackOutlineList, QList<QList<QPoint> >()); };
	QList<QPoint> getOutlineOffsetList(Review::SideType side, int phase) const {
		if(phase<0)return QList<QPoint>();
		
		QList<QList<QPoint> > list = getOutlineOffsetList(side);

		if(Review::isIndexEnableList(phase, list)==false){
			return QList<QPoint>();
		}

		return list[phase];
	};
	QPoint getOutlineOffset(Review::SideType side, int phase, int page){
		if(phase<0 || page<0)return QPoint();

		QList<QPoint> list = getOutlineOffsetList(side, phase);

		if(Review::isIndexEnableList(page, list)==false){
			return QPoint();
		}

		return list[phase];
	};

	bool hasSide(Review::SideType side){ return Review::switchSide(side, (FrontImageList!=NULL), (BackImageList!=NULL), false); };
	bool isEmpty(Review::SideType side){ return getImageList(side).isEmpty(); };
public:
	CmdReqMasterImageList(LayersBase *Base):GUIDirectMessage(Base),FrontImageList(NULL),BackImageList(NULL),FrontOutlineList(),BackOutlineList(){};
	~CmdReqMasterImageList()
	{
		if(FrontImageList!=NULL){
			delete FrontImageList;
		}
		if(BackImageList!=NULL){
			delete BackImageList;
		}
	};
};

class CmdReqVRSAlignment : public GUIDirectMessage
{
public:
	// Recieve
	VRSAlignment frontAlignment, backAlignment;
	//Review::ThreeValue<QRect> InspectionWholeRects;
	//Review::ThreeValue<QRect> MachineWholeRects;

	//QList<Review::ThreeValue<QRect> > InspectionEachPageRects;
	//QList<Review::ThreeValue<QRect> > MachineEachPageRects;

public:
	inline const VRSAlignment &getAlignment(Review::SideType side) const { return (Review::isFront(side) ? frontAlignment : backAlignment); };
	inline VRSAlignment &getAlignment(Review::SideType side){ return (Review::isFront(side) ? frontAlignment : backAlignment); };

public:
	CmdReqVRSAlignment(LayersBase *Base):GUIDirectMessage(Base),frontAlignment(),backAlignment()/*,InspectionWholeRects(),MachineWholeRects(),InspectionEachPageRects(),MachineEachPageRects()*/{};
};

class CmdSetVRSAlignment : public GUIDirectMessage
{
public:
	void setSide(Review::SideType side){ _side = side; };

	void setVRSAlignmentType(Review::VRSAlignmentType type){
		_type = type;
		VRSAlignmentTypeIsChanged = true;
	};

	void setInspectionWholeRects(const Review::ThreeValue<QRect> &rects){
		InspectionWholeRects = rects;
		InspectionWholeRectsIsChanged = true;
	};
	void setMachineWholeRects(const Review::ThreeValue<QRect> &rects){
		MachineWholeRects = rects;
		MachineWholeRectsIsChanged = true;
	};
	void setInspectionEachPageRects(const QList<Review::ThreeValue<QRect>> &rects){
		InspectionEachPageRects = rects;
		InspectionEachPageRectsIsChanged = true;
	};
	void setMachineEachPageRects(const QList<Review::ThreeValue<QRect>> &rects){
		MachineEachPageRects = rects;
		MachineEachPageRectsIsChanged = true;
	};
	void setWholeRects(Review::AlignmentSide align_side, const Review::ThreeValue<QRect> &rects){
		switch(align_side){
		case Review::AlignmentSide::AlignmentSide_Inspection:
			setInspectionWholeRects(rects);
			break;
		case Review::AlignmentSide::AlignmentSide_VRSMachine:
			setMachineWholeRects(rects);
			break;
		default:
			Q_ASSERT("CmdSetVRSAlignment get error on setWholeRects!");
			break;
		}
	};
	void setEachPageRects(Review::AlignmentSide align_side, const QList<Review::ThreeValue<QRect> > &rects){
		switch(align_side){
		case Review::AlignmentSide::AlignmentSide_Inspection:
			setInspectionEachPageRects(rects);
			break;
		case Review::AlignmentSide::AlignmentSide_VRSMachine:
			setMachineEachPageRects(rects);
			break;
		default:
			Q_ASSERT("CmdSetVRSAlignment get error on setEachPageRects!");
			break;
		}
	};

public:
	Review::SideType side() const { return _side; };

	Review::VRSAlignmentType getVRSAlignmentType() const { return _type; };

	Review::ThreeValue<QRect> getInspectionWholeRects() const {
		return InspectionWholeRects;
	};
	Review::ThreeValue<QRect> getMachineWholeRects() const {
		return MachineWholeRects;
	};
	QList<Review::ThreeValue<QRect>> getInspectionEachPageRects() const {
		return InspectionEachPageRects;
	};
	QList<Review::ThreeValue<QRect>> getMachineEachPageRects() const {
		return MachineEachPageRects;
	};

	bool isVRSAlignmentTypeChanged() const {
		return VRSAlignmentTypeIsChanged;
	};

	bool isInspectionWholeRectsChanged() const {
		return InspectionWholeRectsIsChanged;
	};
	bool isMachineWholeRectsChanged() const {
		return MachineWholeRectsIsChanged;
	};
	bool isInspectionEachPageRectsChanged() const {
		return InspectionEachPageRectsIsChanged;
	};
	bool isMachineEachPageRectsChanged() const {
		return MachineEachPageRectsIsChanged;
	};

private:
	Review::SideType _side;

	Review::VRSAlignmentType _type;

	bool VRSAlignmentTypeIsChanged;

	Review::ThreeValue<QRect> InspectionWholeRects;
	Review::ThreeValue<QRect> MachineWholeRects;

	bool InspectionWholeRectsIsChanged;
	bool MachineWholeRectsIsChanged;

	QList<Review::ThreeValue<QRect>> InspectionEachPageRects;
	QList<Review::ThreeValue<QRect>> MachineEachPageRects;

	bool InspectionEachPageRectsIsChanged;
	bool MachineEachPageRectsIsChanged;

public:
	CmdSetVRSAlignment(LayersBase *Base)
		:GUIDirectMessage(Base)
		,_side(Review::NoSide)
		,VRSAlignmentTypeIsChanged(false)
		,InspectionWholeRects()
		,MachineWholeRects()
		,InspectionWholeRectsIsChanged(false)
		,MachineWholeRectsIsChanged(false)
		,InspectionEachPageRects()
		,MachineEachPageRects()
		,InspectionEachPageRectsIsChanged(false)
		,MachineEachPageRectsIsChanged(false)
		{};
};

class CmdReqVRSMotorState : public GUIDirectMessage
{
public:
	int x;
	int y;
	int z;
	bool x_enable;
	bool y_enable;
	bool z_enable;

	bool ret;

public:
	CmdReqVRSMotorState(LayersBase *Base):GUIDirectMessage(Base),x(0),y(0),z(0),x_enable(false),y_enable(false),z_enable(false){};
};

class CmdSetVRSMotorState : public GUIDirectMessage
{
public:
	int x() const { return _x; };
	int y() const { return _y; };
	int z() const { return _z; };

	void setX(int val, bool enable=true){ _x = val; _x_enable = enable; };
	void setY(int val, bool enable=true){ _y = val; _y_enable = enable; };
	void setZ(int val, bool enable=true){ _z = val; _z_enable = enable; };

	bool isXEnable() const { return _x_enable; };
	bool isYEnable() const { return _y_enable; };
	bool isZEnable() const { return _z_enable; };
	bool isXYEnable() const { return (isXEnable() && isYEnable()); };
	bool isXYZEnable() const { return (isXYEnable() && isZEnable()); };

	bool isEmpty() const { return !(isXEnable()==true || isYEnable()==true || isZEnable()==true); };

	void setXEnable(bool enable){ _x_enable = enable; };
	void setYEnable(bool enable){ _y_enable = enable; };
	void setZEnable(bool enable){ _z_enable = enable; };

	bool ret;

private:
	int _x;
	int _y;
	int _z;
	bool _x_enable;
	bool _y_enable;
	bool _z_enable;

public:
	CmdSetVRSMotorState(LayersBase *Base):GUIDirectMessage(Base),_x(0),_y(0),_z(0),_x_enable(false),_y_enable(false),_z_enable(false){};
};

class CmdReqCameraAlignment : public GUIDirectMessage
{
public:
	void setSide(Review::SideType side_){ _side = side_; };
	Review::SideType side() const { return _side; };

	void setVRSAlignmentType(Review::VRSAlignmentType type_){ _type = type_; };
	Review::VRSAlignmentType VRSAlignmentType() const { return _type; };

	void setPage(int page_){ _page = page_; };
	int page() const { return _page; };

	void setNumber(int number_){ _number = number_; };
	int number() const { return _number; };

	void setPoint(const QPoint &point_){ MachineCenter = point_; };
	QPoint point() const { return MachineCenter; };

public:
	bool isEnable(){
		do{
			if(side()==Review::NoSide)break;
			if(VRSAlignmentType()==Review::VRSAlignmentType::VRSAlingmentEachPage && page()<0)break;
			if(Review::isBetween(0, number(), 2)==false)break;
			return true;
		}while(false);
		return false;
	};

private:
	Review::SideType _side;
	Review::VRSAlignmentType _type;
	int _page;// >=0; if type==Review::VRSAlignmentType::VRSAlingmentWholeImage, this is ineffectively.
	int _number;// 0~2

	QPoint MachineCenter;

public:
	CmdReqCameraAlignment(Review::SideType side, LayersBase *Base):GUIDirectMessage(Base),_side(side)
																	,_type(Review::VRSAlignmentType::VRSAlingmentWholeImage),_page(-1),_number(-1),MachineCenter(){};
};

class CmdSetCameraAlignment : public GUIDirectMessage
{
public:
	void setSide(Review::SideType side_){ _side = side_; };
	Review::SideType side() const { return _side; };

	void setVRSAlignmentType(Review::VRSAlignmentType type_){ _type = type_; };
	Review::VRSAlignmentType VRSAlignmentType() const { return _type; };

	void setPage(int page_){ _page = page_; };
	int page() const { return _page; };

	void setNumber(int number_){ _number = number_; };
	int number() const { return _number; };

	void setRect(const QRectF &rect_){ _rect = rect_; };
	QRectF rect() const { return _rect; };

public:
	bool isEnable(){
		do{
			if(side()==Review::NoSide)break;
			if(VRSAlignmentType()==Review::VRSAlignmentType::VRSAlingmentEachPage && page()<0)break;
			if(Review::isBetween(0, number(), 2)==false)break;
			if(rect().isValid()==false)break;
			return true;
		}while(false);
		return false;
	};

private:
	Review::SideType _side;
	Review::VRSAlignmentType _type;
	int _page;// >=0; if type==Review::VRSAlignmentType::VRSAlingmentWholeImage, this is ineffectively.
	int _number;// 0~2
	QRectF _rect;// (-1.0,-1.0)~(1.0,1.0); (0,0) is center.

public:
	CmdSetCameraAlignment(Review::SideType side, LayersBase *Base):GUIDirectMessage(Base),_side(side),_type(Review::VRSAlignmentType::VRSAlingmentWholeImage),_page(-1),_number(-1),_rect(){};
};

class CmdReqSequenceEnable : public GUIDirectMessage
{
public:
	bool enable;
public:
	CmdReqSequenceEnable(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdSetSequenceEnable : public GUIDirectMessage
{
public:
	bool enable;
public:
	CmdSetSequenceEnable(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdMoveVRSToCurrentNG : public GUIDirectMessage
{
public:
	bool checkVRSEnable;
public:
	CmdMoveVRSToCurrentNG(LayersBase *Base):GUIDirectMessage(Base),checkVRSEnable(true){};
};

class CmdClearVRSCommandBuffer : public GUIDirectMessage
{
public:
	CmdClearVRSCommandBuffer(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdMoveVRSOnCameraView : public GUIDirectMessage
{
public:
	// -1..1; 0 is center.
	qreal x;
	qreal y;
public:
	CmdMoveVRSOnCameraView(LayersBase *Base):GUIDirectMessage(Base){};
};

class CmdMoveVRSWithAlignment : public GUIDirectMessage
{
public:
	Review::SideType side;
	Review::VRSAlignmentType type;
	int x;
	int y;

	int phase;
	int page;
public:
	CmdMoveVRSWithAlignment(LayersBase *Base):GUIDirectMessage(Base),type(Review::VRSAlignmentType::VRSAlingmentWholeImage),x(0),y(0),phase(-1),page(-1){};
};

class CmdMoveVRSToOrigin : public GUIDirectMessage
{
public:
	void setCheckVRSEnable(bool enable){ m_checkVRSEnable = enable; };
	bool isCheckVRSEnable() const { return m_checkVRSEnable; };

private:
	bool m_checkVRSEnable;

public:
	CmdMoveVRSToOrigin(LayersBase *Base):GUIDirectMessage(Base),m_checkVRSEnable(true){};
};

class CmdMoveVRSToEscape : public GUIDirectMessage
{
public:
	void setCheckVRSEnable(bool enable){ m_checkVRSEnable = enable; };
	bool isCheckVRSEnable() const { return m_checkVRSEnable; };

private:
	bool m_checkVRSEnable;

public:
	CmdMoveVRSToEscape(LayersBase *Base):GUIDirectMessage(Base),m_checkVRSEnable(true){};
};

class CmdLoadMasterImage : public GUIDirectMessage
{
public:
	Review::SideType side;
	QList<Review::MasterImageFileData> imgDataList;

public:
	CmdLoadMasterImage(LayersBase *Base):GUIDirectMessage(Base),side(Review::NoSide),imgDataList(){};
};

class CmdLoadMaster : public GUIDirectMessage
{
public:
	int MasterCode;

public:
	bool isEnable() const { return (MasterCode>=1); };

public:
	CmdLoadMaster(LayersBase *Base):GUIDirectMessage(Base),MasterCode(-1){};
};

class CmdReqCurrentLotInfo : public GUIDirectMessage
{
	friend class ReviewPIBase;

public:
	LotInfoItem getLotInfo(Review::SideType side) const { return Review::switchSide(side, m_frontLotInfo, m_backLotInfo, LotInfoItem()); };

private:
	LotInfoItem m_frontLotInfo, m_backLotInfo;

	void _setLotInfo(Review::SideType side, const LotInfoItem &info){
		if(Review::isFront(side)==true){
			m_frontLotInfo = info;
		}else if(Review::isBack(side)==true){
			m_backLotInfo = info;
		}else{
			return;
		}
	}
public:
	CmdReqCurrentLotInfo(LayersBase *Base):GUIDirectMessage(Base),m_frontLotInfo(),m_backLotInfo(){};
};

class CmdMoveVRSDirectory : public GUIDirectMessage
{
	friend class ReviewPIBase;
public:
	void setMachineID(int id){ _MachineID = id; };
	void setX(int x_){ _x = x_; };
	void setY(int y_){ _y = y_; };
	void setPhase(int phase_){ _phase = phase_; };
	void setPage(int page_){ _page = page_; };
	void setOutlineOffset(const QPoint &offset){ _outlineOffset = offset; _isOutlineOffsetEnable = true; };
	void setOutlineOffsetEnable(bool enable){ _isOutlineOffsetEnable; };

	int machineID() const { return _MachineID; };
	int x() const { return _x; };
	int y() const { return _y; };
	int phase() const { return _phase; };
	int page() const { return _page; };
	QPoint outlineOffset() const { return _outlineOffset; };
	bool isOutlineOffsetEnable() const { return _isOutlineOffsetEnable; };

public:
	bool isEnable() const { return (machineID()!=-1 && phase()!=-1 && page()!=-1); };

private:
	int _MachineID;
	int _x;
	int _y;
	int _phase;
	int _page;

	QPoint _outlineOffset;
	bool _isOutlineOffsetEnable;

public:
	QString errorMsg() const { return _errMsg; };
	bool hasError() const { return !errorMsg().isEmpty(); };

private:
	void _setErrorMsg(const QString &msg){ _errMsg = msg; };

private:
	QString _errMsg;
	
public:
	CmdMoveVRSDirectory(LayersBase *Base):GUIDirectMessage(Base),_MachineID(-1),_x(0),_y(0),_phase(-1),_page(-1),_outlineOffset(),_isOutlineOffsetEnable(false),_errMsg(){};
};

class	CmdSetOffsetVRS : public GUIDirectMessage
{
public:
	// Send
public:
	CmdSetOffsetVRS(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdResetDiffVRS : public GUIDirectMessage
{
public:
	// Send
public:
	CmdResetDiffVRS(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdAddDiffVRSX : public GUIDirectMessage
{
public:
	int	Dx;
public:
	CmdAddDiffVRSX(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdAddDiffVRSY : public GUIDirectMessage
{
public:
	int	Dy;
public:
	CmdAddDiffVRSY(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdAddDiffVRSXY : public GUIDirectMessage
{
public:
	int	Dx,Dy;
public:
	CmdAddDiffVRSXY(LayersBase *base)
		:GUIDirectMessage(base){};
};

class	CmdReqCSVOffset : public GUIDirectMessage
{
public:
	bool	CSVUnitMM;
	int		CSVOffsetX;
	int		CSVOffsetY;
	bool	CSVReverseX;
	bool	CSVReverseY;
	double	CSVMagnificationX;
	double	CSVMagnificationY;

public:
	CmdReqCSVOffset(LayersBase *base)
		:GUIDirectMessage(base){};
};