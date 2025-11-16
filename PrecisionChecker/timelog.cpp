#include "clsplot3d.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <stdio.h>

//#define DEBUG

void CImgCtrl::startTimeLog() {
}

void CImgCtrl::wrtTimeLog(char *mess) {
#ifdef DEBUG
	QTime tim = QTime::currentTime();
	QFile file("D:/Tmp/timelog.log");
	if ( !file.open(QIODevice::Append|QIODevice::Text) ) return;

	QTextStream out(&file);
	out << tim.toString("hh:mm:ss.zzz") << "," << mess << "\n";
	file.close();
#endif
}

void CImgCtrl::endTimeLog() {
}

void CImgCtrl::dbgPrtFlexAreaList(int nPageIdx, bool flg) {
#ifdef DEBUG
	QString fnm;
	if ( flg == true ) fnm = fnm.sprintf("D:/Tmp/FAreaCenter_%d.dat",nPageIdx);
	else fnm = fnm.sprintf("D:/Tmp/FAreaCenter_%d_dst.dat",nPageIdx);
	QFile file(fnm);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return;
	QTextStream out(&file);
	for( PureFlexAreaList *c=tblFArea[nPageIdx].GetFirst(); c!=NULL; ) {
		double x,y;
		c->GetWeightCenter(x,y);
		QString tmp;
		QString buf = tmp.sprintf("%f,%f\n",x,y);
		out << buf;
		c = c->GetNext();
	}
	file.close();
#endif
}

void CImgCtrl::dbgPrtFlexAreaList(PureFlexAreaListContainer &lst, int no) {
#ifdef DEBUG
	QString fnm;
	fnm = fnm.sprintf("D:/Tmp/FAreaCenter_tmp_%d.dat",no);
	QFile file(fnm);
	if ( !file.open(QIODevice::Append|QIODevice::Text) ) return;
	QTextStream out(&file);
	out << "\n";
	int idx = 0;
	for( PureFlexAreaList *c=lst.GetFirst(); c!=NULL; ) {
		double x,y;
		c->GetWeightCenter(x,y);
		QString tmp;
		QString buf = tmp.sprintf("%d,%f,%f\n",idx,x,y);
		out << buf;
		c = c->GetNext();
		idx ++;
	}
	file.close();
#endif
}

void CImgCtrl::dbgPrtPadCnt(NPListPack<clsPadCnt> &lst, int no) {
#ifdef DEBUG
	QString fnm;
	fnm = fnm.sprintf("D:/Tmp/PadCnt_%d.dat",no);
	QFile file(fnm);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return;
	QTextStream out(&file);
	int idx = 0;
	for( clsPadCnt *c=lst.GetFirst(); c!=NULL; ) {
		QString tmp;
		QString buf = tmp.sprintf("%d,%d,\n",idx,c->cnt);
		out << buf;
		c = c->GetNext();
		idx ++;
	}
	file.close();
#endif
}

void CImgCtrl::dbgPrtPadArea(clsPadAreaPack &lst, NPListPack<clsPadCnt> &clst, int no) {
#ifdef DEBUG
	QString fnm;
	fnm = fnm.sprintf("D:/Tmp/PadArea_%d.dat",no);
	QFile file(fnm);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return;
	QTextStream out(&file);
	int idx = 0;
	int lin = 0;
	int cnt = 0;

	clsPadArea *c=NULL, *pre=NULL;
	clsPadCnt  *cn = clst.GetFirst();

	while( cn!=NULL ) {
		if ( c==NULL ) {
			QString tbuf = QString::number(lin)+":\n";
			out << tbuf;
			c = lst.GetFirst();
		}
		for(int i=0; i<cn->cnt; i++ ) {
			QString tmp;
			QString buf = tmp.sprintf("%d,%f,%f,%f\n",idx,c->x,c->y,c->val);
			out << buf;
			c = c->GetNext();
			idx++;
		}
		lin ++;
		QString tbuf = "count="+QString::number(cn->cnt)+"\n"+QString::number(lin)+":\n";
		out << tbuf;
		cn = cn->GetNext();
	}
	file.close();
#endif
}
