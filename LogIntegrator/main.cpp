/*
 * Copyright (C) 2012
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

#include <QtCore/QCoreApplication>
#include "LogIntegratorlib.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QString Path1 = "D:/";	//HDD�̃p�X1����
	QString Path2 = "";		//HDD�̃p�X2����
	QString OutPath = "";	//���O�̏o�͐��t�H���_
	QString SaveDate = "";	//�ۑ����������H
	QString LotNo = "";		//���b�g�ԍ�
	QString BaseNo = "";	//���ԍ�
	bool SilentFlg = false;	//�H

	for( int i=1; i<argc; i++ ) {
		if ( *argv[i] == 'P' || *argv[i] == 'p' ) {
			char *fp = argv[i]+1;
			Path1 = QString(fp);
		}
		if ( *argv[i] == 'Q' || *argv[i] == 'q' ) {
			char *fp = argv[i]+1;
			Path2 = QString(fp);
		}
		if ( *argv[i] == 'O' || *argv[i] == 'o' ) {
			char *fp = argv[i]+1;
			OutPath = QString(fp);
		}
		if ( *argv[i] == 'D' || *argv[i] == 'd' ) {
			char *fp = argv[i]+1;
			SaveDate = QString(fp);
		}
		if ( *argv[i] == 'L' || *argv[i] == 'l' ) {
			char *fp = argv[i]+1;
			LotNo = QString(fp);
		}
		if ( *argv[i] == 'B' || *argv[i] == 'b' ) {
			char *fp = argv[i]+1;
			BaseNo = QString(fp);
		}
		if ( *argv[i] == 'S' || *argv[i] == 's' ) {
			SilentFlg = true;
		}
	}

	if ( Path1 == "" ) {
		return 1;
	}
	if ( OutPath == "" ) {
		OutPath = Path1;
	}
	clsLogIntegratorLib obj;
	obj.setPath1(Path1);
	obj.setPath2(Path2);
	obj.setOutPath(OutPath);
	obj.setSaveDate(SaveDate);
	obj.setLotNo(LotNo);
	obj.setBaseNo(BaseNo);
	if ( SaveDate != "" ) {
		if ( obj.makeLogIntegrate() == false ) {
			return 2;
		}
	} else if ( LotNo != "" ) {
		if ( obj.makeLogIntegrateSearch() == false ) {
			return 2;
		}
	} else {
		return 0;
	}

	if ( obj.outLog() == false ) {
		return 3;	//this application cannot find the path
	}

	//if ( obj.errChk() == false ) {
		obj.showErrDialog();
		a.exec();
	//}
	return 0;
}

//�}�b�`���O�������ǂ����𖈉��\�����