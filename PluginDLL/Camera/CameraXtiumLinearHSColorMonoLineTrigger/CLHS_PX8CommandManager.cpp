/*
 * Copyright (C) 2018
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

#include "CLHS_PX8CommandManager.h"

#include <QStringList>
#include <QVector>

QPair<QList<bool>, CLHS_PX8Setting> CLHS_PX8CommandAnalyzer::analyze(const QString &str)
{
	QStringList ComStep = str.split(QChar((char)0x04), QString::SkipEmptyParts);// �e�R�}���h�I�[���؂��ŕ���(0x04)

	CLHS_PX8Setting setting;
	QList<bool> flagList = QVector<bool>(TYPE_ENUM_COUNT, false).toList();
	
	for(int cs=0; cs<ComStep.count(); cs++){
		QStringList list = ComStep[cs].split('\r', QString::SkipEmptyParts);// �R�}���h�ԐM�敪���ŕ���(CR)

		// ��){>OK>r200, >CMD OVR ERR!, EOF}
		for(int i=0; i<list.count(); i++){
			QStringList parts = list[i].split('>');// �R�}���h�̊J�n�����ŕ���('>')
			if(parts.isEmpty()==false){
				if(parts.contains("CMD ERR!") || list.contains("CMD OVR ERR!") || list.contains("VAL ERR!") || list.contains("MEM ERR!")){
					continue;// �G���[�ɂ��莟�̃R�}���h�ԓ���
				}else{
					if(parts.count()>=2){// 2�ڂ��{��
						CLHS_PX8Type type = checkCmd(parts[1]);// �^�C�v�I��
						if(type==TYPE_ENUM_COUNT)continue;
						double value1;
						double value2=-99999999;
						if(checkValue(parts[1], value1,value2)==true){// �l�擾
							// ������
							flagList[type] = true;
							if(value2>-99999999){
								setData(type, setting, value2);
							}
							else{
								setData(type, setting, value1);
							}
						}
					}
				}
			}
		}
	}

	return QPair<QList<bool>, CLHS_PX8Setting>(flagList, setting);
}

CLHS_PX8Type CLHS_PX8CommandAnalyzer::checkCmd(const QString &recieve)
{
	QString cmdStr;

	QString trmStr = recieve.trimmed();

	for(int i=0; i<trmStr.count(); i++){
		if(trmStr[i].isNumber()==true){// ���l
			break;
		}
		if(trmStr[i]==QChar(' ')){// �}�C�i�X�l
			break;
		}
		cmdStr.append(recieve[i]);
	}

	if(cmdStr=="gax"){
		return TYPE_AnalogGain;
	}else if(cmdStr=="gdx"){
		return TYPE_DigitalGain;
	}else if(cmdStr=="odx"){
		return TYPE_DigitalOffset;
	}else if(cmdStr=="inm"){
		return TYPE_ExposureMode;
	}else if(cmdStr=="int"){
		return TYPE_ExposureTime;
	}else if(cmdStr=="tpn"){
		return TYPE_UseTestPattern;
	}else if(cmdStr=="rev"){
		return TYPE_ScanDirection;
	}else{
		return TYPE_ENUM_COUNT;
	}
}

bool CLHS_PX8CommandAnalyzer::checkValue(const QString &recieve, double &value1,double &value2)
{
	int index = recieve.indexOf('>');// �R�}���h�J�n�_

	// ���l�܂Ŕ��΂�
	for(index = index+1; index<recieve.count(); index++){
		if(recieve[index].isNumber()==true){// ���l
			break;
		}
		if(recieve[index]==QChar(' ')){// �}�C�i�X�l
			break;
		}
	}

	QString valueStr;
	for(index++; index<recieve.count(); index++){
		if(recieve[index]!='.' && recieve[index].isNumber()==false && recieve[index]!=QChar('-')){// ���l�������̓}�C�i�X�l
			break;
		}
		valueStr.append(recieve[index]);
	}

	bool ok;
	value1 = valueStr.toDouble(&ok);
	
	if(recieve[index]==','|| recieve[index]==' '){
		QString valueStr2;
		for(index++; index<recieve.count(); index++){
			if(recieve[index]!='.' && recieve[index].isNumber()==false && recieve[index]!=QChar('-')){// ���l�������̓}�C�i�X�l
				break;
			}
			valueStr2.append(recieve[index]);
		}
		value2 = valueStr2.toDouble(&ok);
	}
	

	return ok;
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Type type, CLHS_PX8Setting &buffer, double value)
{
	switch(type){
	case TYPE_AnalogGain:
		buffer.AnalogGain = value;
		break;
	case TYPE_DigitalGain:
		buffer.DigitalGain = value;
		break;
	case TYPE_DigitalOffset:
		buffer.DigitalOffset = value;
		break;

	case TYPE_ExposureMode:
		buffer.ExposureMode = value;
		break;
	case TYPE_ExposureTime:
		buffer.ExposureTime = value;
		break;
	case TYPE_UseTestPattern:
		buffer.EnableTestPattern = ((value==0) ? false : true);
		break;
	case TYPE_ScanDirection:
		buffer.ScanDirection = ((value==0) ? true : false);
		break;
	default:
		break;
	}
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Setting &buffer, const QPair<QList<bool>, CLHS_PX8Setting> &sorce)
{
	if(sorce.first.count()!=TYPE_ENUM_COUNT)return;

	for(int i=0; i<sorce.first.count(); i++){
		if(sorce.first[i]==true){
			setData( (CLHS_PX8Type)i, buffer, sorce.second.getData((CLHS_PX8Type)i) );
		}
	}
}

void CLHS_PX8CommandAnalyzer::setData(CLHS_PX8Setting &buffer, const QString &recieve)
{
	setData(buffer, analyze(recieve));
}