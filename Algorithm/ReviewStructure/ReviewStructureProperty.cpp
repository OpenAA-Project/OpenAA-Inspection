/*
 * Copyright (C) 2017
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

#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

#define ToStr(x) #x

// ������
ReviewStructureProperty::PropertyBase(void)
	:AbstructProperty()
{
	initialize();
}

void ReviewStructureProperty::initialize()
{
	// �\�[�g�w��
	NGNailListSortOrder = Review::OrderOfSortNG::_Order_YLesser;
	HistoryListSortOrder = Review::OrderOfSortHistory::_Order_InspectionIDGreater;
	
	// NG�摜�ۑ��̃t�H�[�}�b�g
	SaveNGImageFileNameFormat = /**/"%m-%M/%l/%i/%S/%n-%N.png";

	// NG�摜�̐��ǂݍ��ݐ������肷�鐔�l
	// ���ݗ������炱�̑O�ゾ�����ǂݍ��݂���
	PreLoadNGImageLength = 4;

	// XML�T�[�o�[�ւ̃A�N�Z�X�p�A�h���X�ƃ|�[�g�ԍ�
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

// �x�[�X��
QString ReviewStructureProperty::baseName() const
{
	return /**/"ReviewProperty";
}

// �Z�N�V������
QString ReviewStructureProperty::sectionName() const
{
	return /**/"ReviewStructure";
}

// �P�̕ۑ��p�t�@�C����
QString ReviewStructureProperty::filename() const
{
	return /**/"ReviewStructrue";
}

// �o�b�t�@�����̕���
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

// SectionBuffer�쐬
SectionBuffer ReviewStructureProperty::toBuffer(void) const// ���X�g�փR���o�[�g
{
	SectionBuffer buffer;
	
	// �Z�N�V�������L�q
	buffer.setSectionName(sectionName());

	// �f�[�^�ݒ�
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

// �Ή��N���X�����̃f�[�^�󂯎���
bool ReviewStructureProperty::fromInstance(ReviewPIBase *parent)// �ΏۃN���X���烊�X�g�쐬
{
	if(parent==NULL)return false;

	fromBuffer( parent->getProperty().toBuffer() );

	return true;
}

// �Ή��N���X�ւ̃f�[�^���n��
bool ReviewStructureProperty::toInstance(ReviewPIBase *parent) const// �ΏۃN���X�փR���o�[�g
{
	if(parent==NULL)return false;

	parent->setProperty(*this);

	return true;
}
