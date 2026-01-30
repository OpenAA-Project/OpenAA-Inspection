/*
 * Copyright (C) 2023
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



#include "XSourceGenerator.h"
#include <QBuffer>

NetSystem	NetSystemData;
//=====================================================================

NetItem::NetItem(NetSystem *parent)
{
	Parent		=parent;
	FrameColor	=Qt::red;
	InnerColor	=Qt::green;
	Radius		=60;
}

bool	NetItem::Save(QTextStream &txt)
{
	txt<<"{\n";
	txt<<"\t\tRootNameID:"<<DLLRoot<<":"<<DLLName<<":"<<IDName<<"\n";
	txt<<"\t\tSourceFileName:"<<SourceFileName<<"\n";
	txt<<"\t\tPos:"<<Position.x()<<","<<Position.y()<<"\n";
	txt<<"\t\tFrameColor:"<<FrameColor.alpha()<<","<<FrameColor.red()<<","<<FrameColor.green()<<","<<FrameColor.blue()<<"\n";
	txt<<"\t\tInnerColor:"<<InnerColor.alpha()<<","<<InnerColor.red()<<","<<InnerColor.green()<<","<<InnerColor.blue()<<"\n";
	txt<<"\t\tRemark:"<<Remark<<"\n";
	txt<<"}\n";
	return true;
}
bool	NetItem::Load(QTextStream &txt)
{
	while(txt.atEnd()==false){
		QString	L=txt.readLine(1000);
		L=L.trimmed();
		if(L=="}")
			break;
		QString	KeyTag=L.section(':',0,0);
		if(KeyTag=="tRootNameID"){
			DLLRoot=L.section(':',1,1);
			DLLName=L.section(':',2,2);
			IDName =L.section(':',3,3);
		}
		else if(KeyTag=="SourceFileName"){
			SourceFileName=L.section(':',1);
		}
		else if(KeyTag=="Pos"){
			QString	M=L.section(':',1);
			Position.setX(M.section(',',0,0).toInt());
			Position.setY(M.section(',',1,1).toInt());
		}
		else if(KeyTag=="FrameColor"){
			QString	M=L.section(':',1);
			FrameColor.setAlpha(M.section(',',0,0).toInt());
			FrameColor.setRed  (M.section(',',1,1).toInt());
			FrameColor.setGreen(M.section(',',2,2).toInt());
			FrameColor.setBlue (M.section(',',3,3).toInt());
		}
		else if(KeyTag=="InnerColor"){
			QString	M=L.section(':',1);
			InnerColor.setAlpha(M.section(',',0,0).toInt());
			InnerColor.setRed  (M.section(',',1,1).toInt());
			InnerColor.setGreen(M.section(',',2,2).toInt());
			InnerColor.setBlue (M.section(',',3,3).toInt());
		}
		else if(KeyTag=="Remark"){
			Remark=L.section(':',1);
		}
	}

	return true;
}

bool	NetItem::IsInclude(QPoint &pos)
{
	QPoint	L=Position-pos;

	if(L.manhattanLength ()<Radius)
		return true;
	return false;
}
void	NetItem::Draw(QPainter &Pnt)
{
	Pnt.setPen(FrameColor);
	Pnt.setBrush(InnerColor);
	Pnt.drawEllipse(Position.x()-Radius,Position.y()-Radius,2*Radius,2*Radius);
	QString	Str= QString("Root:")	+DLLRoot+QString("\n")
				+QString("Name:")	+DLLName+QString("\n")
				+QString("IDName:")	+IDName+QString("\n")
				+QString("File:")+SourceFileName+QString("\n")
				+QString("Remark:")+Remark;
	Pnt.drawText(Position.x()-Radius,Position.y()-Radius,2*Radius,2*Radius, Qt::AlignCenter ,Str);
}

NetItem	&NetItem::operator=(NetItem &src)
{
	QByteArray	Buff;
	QTextStream	Str(&Buff);

	src.Save(Str);
	Str.seek(0);
	Load(Str);
	return *this;
}

bool	NetArrow::IsInclude(QPoint &pos)
{
	return true;
}
void	NetArrow::Draw(QPainter &Pnt)
{
	if(RootFrom==RootTo && NameFrom==NameTo && IDFrom==IDTo){
	}
	else{
		if(Parent!=NULL){
			NetItem	*c1	=Parent->SearchItem(RootFrom,NameFrom,IDFrom);
			NetItem	*c2	=Parent->SearchItem(RootTo	,NameTo	 ,IDTo	);
			if(c1!=NULL && c2!=NULL){
			}
		}
	}
}

NetItem	*NetSystem::SearchItem(QString root ,QString name ,QString ID)
{
	for(NetItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->DLLRoot==root && c->DLLName==name && c->IDName==ID)
			return c;
	}
	return NULL;
}