#include "HookMeasureForm.h"
#include "ui_HookMeasureForm.h"
#include "XDisplayImagePacket.h"
#include <QFontMetrics>
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "swap.h"

void	CalcCircleFrom3PointsCover(int X1, int Y1
								,  int X2, int Y2
								,  int X3, int Y3
								,  double &Cx, double &Cy ,double &R)
{
	if(CalcCircleFrom3Points( X1, Y1
							 ,X2, Y2
							 ,X3, Y3
							 ,Cx, Cy ,R,0.01)==false){
		Cx=(X1+X2+X3)/3;
		Cy=(Y1+Y2+Y3)/3;
		R=max(hypot(Cx-X1,Cy-Y1),hypot(Cx-X2,Cy-Y2),hypot(Cx-X3,Cy-Y3));
	}
}
void	CalcCircleFrom3PointsCover(double X1, double Y1
								,  double X2, double Y2
								,  double X3, double Y3
								,  double &Cx, double &Cy ,double &R)
{
	if(CalcCircleFrom3Points( X1, Y1
							 ,X2, Y2
							 ,X3, Y3
							 ,Cx, Cy ,R,0.01)==false){
		Cx=(X1+X2+X3)/3;
		Cy=(Y1+Y2+Y3)/3;
		R=max(hypot(Cx-X1,Cy-Y1),hypot(Cx-X2,Cy-Y2),hypot(Cx-X3,Cy-Y3));
	}
}

HookMeasureForm::MeasuredList::MeasuredList(HookMeasureForm *P)
	:Parent(P)
{
	Step=0;
	Status	=_MLA_Normal;
	ID=0;
	LineWidth	=-1;
	LineType	=__LT_Solid;
	ArrowSize	=0;
	TextSize	=-1;
	Action		=_MLA_Nothing;
}

HookMeasureForm::MeasuredList::MeasuredList(HookMeasureForm *P,const MeasuredList &src)
{
	Action	=src.Action;
	Step	=src.Step;
	P2PA	=src.P2PA;
	P2PB	=src.P2PB;
	PN		=src.PN	;
	P2PC	=src.P2PC;
	P2PD	=src.P2PD;
	P2PE	=src.P2PE;
	P2PF	=src.P2PF;
	Parent	=P;
	Status	=src.Status;

	LineWidth	=src.LineWidth	;
	LineType	=src.LineType	;
	ArrowSize	=src.ArrowSize	;
	TextSize	=src.TextSize	;
	Action		=src.Action		;
}

void	DrawText(QPainter &pnt ,int cx ,int cy,const QPen &TextPen ,const QPen &OutlineColor ,const QString &TextStr)
{
	pnt.setPen(OutlineColor);
	for(int y=-1;y<=1;y++){
		for(int x=-1;x<=1;x++){
			if(x==0 && y==0){
				continue;
			}
			pnt.drawText(cx+x,cy+y   , TextStr);
		}
	}
	pnt.setPen(TextPen);
	pnt.drawText(cx,cy   , TextStr);
}

void	HookMeasureForm::MeasuredList::Draw(QPainter &pnt	,double ZoomRate,int movx ,int movy)
{
	if(Action==_MLA_Nothing)
		return;

	QColor	RCircleColor=GetReverseColor(CircleColor);
	QColor	tLineColor	=LineColor;
	if(Status==MeasuredList::_MLA_Selected){
		tLineColor	=Qt::red;
		RCircleColor=Qt::cyan;
	}
	else
	if(Status==MeasuredList::_M_A_Modify){
		tLineColor	=Qt::magenta;
		RCircleColor=Qt::cyan;
	}

	QPen	LPen(tLineColor);
	QColor	TextOutlineColor(255-tLineColor.red(),255-tLineColor.green(),255-tLineColor.blue());
	QPen	TextOutlinePen(TextOutlineColor);

	switch(LineType){
	case HookMeasureForm::__LT_Solid		:
		LPen.setStyle(Qt::SolidLine);	break;
	case HookMeasureForm::__LT_DashLine		:
		LPen.setStyle(Qt::DashLine);	break;
	case HookMeasureForm::__LT_DotLine		:
		LPen.setStyle(Qt::DotLine);		break;
	case HookMeasureForm::__LT_DashDotLine	:
		LPen.setStyle(Qt::DashDotLine);	break;
	case HookMeasureForm::__LT_DashDotDotLine:
		LPen.setStyle(Qt::DashDotDotLine);	break;
	default:
		LPen.setStyle(Qt::SolidLine);	break;
	}
	int	tLineWidth=LineWidth*ZoomRate;
	if(tLineWidth>0)
		LPen.setWidth(tLineWidth);
	else
		LPen.setWidth(1);

	int		CircleSize=Parent->CircleSize;

	if(TextSize>0)
		TextFont.setPointSize(TextSize);
	else
		TextFont.setPointSize(12);
	TextFont.setWeight(QFont::Bold);
	int	TextHeight=QFontMetrics(TextFont).height();
	pnt.setFont(TextFont);
	QString	Msg;
	bool	Flag=false;
	DataInPage	*Pg=NULL;
	int	Page=Parent->GetTargetPage();
	if(Page>=0){
		Pg=Parent->GetLayersBase()->GetPageData(Page);
	}

	if(Action==_MLA_Point2Point){
		if(Step>=1){
			int	x1=(P2PA.x()+movx)*ZoomRate;
			int	y1=(P2PA.y()+movy)*ZoomRate;
			int	x2=(P2PB.x()+movx)*ZoomRate;
			int	y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

			pnt.setPen(LPen);
			pnt.drawLine(x1,y1,x2,y2);
			int	cx=(x1+x2)/2;
			int	cy=(y1+y2)/2;
			//pnt.drawText(cx,cy   ,QString("Len=")+QString::number(hypot(P2PA.x()-P2PB.x(),P2PA.y()-P2PB.y()),'f',1));
			double	realX1,realY1;
			double	realX2,realY2;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					Msg= QString::number(hypot(realX1-realX2,realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
						+Parent->GetParamGlobal()->UnitName;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					Msg= QString::number(hypot(realX1-realX2,realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
						+Parent->GetParamGlobal()->UnitName;
				}
				else{
					Msg=QString::number(hypot(P2PA.x()-P2PB.x(),P2PA.y()-P2PB.y()),'f',Parent->GetParamGlobal()->SmallNumberFigure);
				}
			}
			DrawText(pnt,cx,cy,LPen ,TextOutlinePen 
						,QString(tr("長さ="))
						+Msg);
		}
	}
	else if(Action==_MLA_FoldedLines){
		if(PN.count()>0){
			QPoint	Last=PN.first();
			int	x1=(Last.x()+movx)*ZoomRate;
			int	y1=(Last.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			double	Len=0;
			double	LenR=0;
			int	MinX=Last.x();
			int	MinY=Last.y();
			int	MaxX=Last.x();
			int	MaxY=Last.y();
			bool	HasReal=true;
			for(int i=1;i<PN.count();i++){
				QPoint	P=PN[i];
				if(P==Last){
					continue;
				}
				int	x2=(P.x()+movx)*ZoomRate;
				int	y2=(P.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				double	D=hypot(Last.x()-P.x(),Last.y()-P.y());
				Len+=D;

				pnt.setPen(LPen);
				pnt.drawLine(x1,y1,x2,y2);
				int	cx=(x1+x2)/2;
				int	cy=(y1+y2)/2;
				
				double	realX1,realY1;
				double	realX2,realY2;
				if(Pg!=NULL){
					if(Pg->HasRealTransform(P.x()	 ,P.y())==true
					&& Pg->TransformImageToReal(Last.x() ,Last.y(),realX1 ,realY1)==true
					&& Pg->TransformImageToReal(P.x()	 ,P.y()	  ,realX2 ,realY2)==true){
						double	DR=hypot(realX1-realX2,realY1-realY2);
						Msg= QString::number(DR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName;
						LenR+=DR;
						Flag=true;
					}
				}
				if(Flag==false){
					if(Parent->GetLayersBase()->HasRealTransform(P.x()	 ,P.y())==true
					&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(Last.x() ,Last.y() ,realX1 ,realY1)==true
					&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P.x()	 ,P.y()	   ,realX2 ,realY2)==true){
						double	DR=hypot(realX1-realX2,realY1-realY2);
						Msg= QString::number(DR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName;

						LenR+=DR;
					}
					else{
						Msg= QString::number(D,'f',Parent->GetParamGlobal()->SmallNumberFigure);
						HasReal=false;
					}
				}
				DrawText(pnt,cx,cy,LPen ,TextOutlinePen 
							,QString(tr("長さ="))
							+Msg);
				MinX=min(MinX,P.x());
				MinY=min(MinY,P.y());
				MaxX=max(MaxX,P.x());
				MaxY=max(MaxY,P.y());
				Last=P;
				x1=(Last.x()+movx)*ZoomRate;
				y1=(Last.y()+movy)*ZoomRate;
			}
			if(HasReal==true){
				DrawText(pnt,((MinX+MaxX)/2+movx)*ZoomRate,((MinY+MaxY)/2+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("全長="))
							+QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure) );
			}
			else{
				DrawText(pnt,((MinX+MaxX)/2+movx)*ZoomRate,((MinY+MaxY)/2+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("全長="))
							+QString::number(Len ,'f',Parent->GetParamGlobal()->SmallNumberFigure) );
			}
		}
	}
	else if(Action==_MLA_Arc){
		if(Step==1){
			{
				int	x1=(P2PA.x()+movx)*ZoomRate;
				int	y1=(P2PA.y()+movy)*ZoomRate;
				int	x2=(P2PB.x()+movx)*ZoomRate;
				int	y2=(P2PB.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}
			int	Cx=(P2PA.x()+P2PB.x())/2;
			int	Cy=(P2PA.y()+P2PB.y())/2;
			double	R=hypot(P2PA.x()-Cx,P2PA.y()-Cy);
			{
				if(R>0){
					int	x1=(Cx-R+movx)*ZoomRate;
					int	y1=(Cy-R+movy)*ZoomRate;
					int	x2=(Cx+R+movx)*ZoomRate;
					int	y2=(Cy+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			double	Len=M_PI*R;
			double	realX1,realY1;
			double	realX2,realY2;
			double	RR=0;
			double	LenR=0;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y(),realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					double	RCx=(realX1+realX2)/2.0;
					double	RCy=(realY1+realY2)/2.0;
					RR=hypot(realX1-RCx,realY1-RCy);
					LenR=M_PI*RR;
					Msg=QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					double	RCx=(realX1+realX2)/2.0;
					double	RCy=(realY1+realY2)/2.0;
					RR=hypot(realX1-RCx,realY1-RCy);
					LenR=M_PI*RR;
					Msg=QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitName;
				}
				else{
					Msg=QString::number(Len,'f',Parent->GetParamGlobal()->SmallNumberFigure);
				}
			}
			DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen 
								,QString(tr("円周長さ="))
								+Msg);
		}
		else if(Step>=2){
			{
				int	x1=(P2PA.x()+movx)*ZoomRate;
				int	y1=(P2PA.y()+movy)*ZoomRate;
				int	x2=(P2PB.x()+movx)*ZoomRate;
				int	y2=(P2PB.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}

			double	RR=0;
			double Cx, Cy ,R;
			CalcCircleFrom3PointsCover(	 P2PA.x(), P2PA.y()
										,P2PB.x(), P2PB.y()
										,P2PC.x(), P2PC.y()
										,Cx, Cy ,R);
			double	realX1,realY1;
			double	realX2,realY2;
			double	realX3,realY3;
			bool	HasReal=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Pg->TransformImageToReal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					double RCx, RCy;
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx, RCy ,RR);
					HasReal=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					double RCx, RCy;
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx, RCy ,RR);
					HasReal=true;
				}
			}
			double	Len=0;
			int	Px=Cx;
			int	Py=Cy;
			double	LenR=0;
			{
				if(R>0){
					int	x1=(Cx-R+movx)*ZoomRate;
					int	y1=(Cy-R+movy)*ZoomRate;
					int	x2=(Cx+R+movx)*ZoomRate;
					int	y2=(Cy+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					double	s1=-GetSita(P2PA.x()-Cx,P2PA.y()-Cy);
					double	s2=-GetSita(P2PB.x()-Cx,P2PB.y()-Cy);
					double	s3=-GetSita(P2PC.x()-Cx,P2PC.y()-Cy);
					s1=RegulateAngle(s1);
					s2=RegulateAngle(s2);
					s3=RegulateAngle(s3);
					if(s1<=s3 && s3<=s2){
						pnt.drawArc(x1,y1,x2-x1,y2-y1,s1*5760/(2*M_PI),(s2-s1)*5760/(2*M_PI));
						Len	=(s2-s1)*R;
						LenR=(s2-s1)*RR;
						double	ks=(s1+s2)/2;
						Px=Cx+R*cos(ks);
						Py=Cy-R*sin(ks);
					}
					else if(s2<=s3 && s3<=s1){
						pnt.drawArc(x1,y1,x2-x1,y2-y1,s2*5760/(2*M_PI),(s1-s2)*5760/(2*M_PI));
						Len	=(s1-s2)*R;
						LenR=(s1-s2)*RR;
						double	ks=(s1+s2)/2;
						Px=Cx+R*cos(ks);
						Py=Cy-R*sin(ks);
					}
					else if(s2<=s1 && (s1<=s3 || s3<=s2)){
						pnt.drawArc(x1,y1,x2-x1,y2-y1,s1*5760/(2*M_PI),(2*M_PI-s1)*5760/(2*M_PI));
						pnt.drawArc(x1,y1,x2-x1,y2-y1,0,s2*5760/(2*M_PI));
						Len	=(2*M_PI-s1)*R + s2*R;
						LenR=(2*M_PI-s1)*RR + s2*RR;

						double	ks=(s1+s2)/2+M_PI;
						Px=Cx+R*cos(ks);
						Py=Cy-R*sin(ks);
					}
					else if(s1<=s2 && (s2<=s3 || s3<=s1)){
						pnt.drawArc(x1,y1,x2-x1,y2-y1,s2*5760/(2*M_PI),(2*M_PI-s2)*5760/(2*M_PI));
						pnt.drawArc(x1,y1,x2-x1,y2-y1,0,s1*5760/(2*M_PI));
						Len	=(2*M_PI-s2)*R + s1*R;
						LenR=(2*M_PI-s2)*RR + s1*RR;

						double	ks=(s1+s2)/2+M_PI;
						Px=Cx+R*cos(ks);
						Py=Cy-R*sin(ks);
					}
				}
			}
			if(HasReal==true){
				DrawText(pnt,(Px+movx)*ZoomRate,(Py+movy)*ZoomRate,LPen ,TextOutlinePen   
							,QString(tr("円弧長="))
							+QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);

				DrawText(pnt,(Px+movx)*ZoomRate,(Py+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="  ))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Px+movx)*ZoomRate,(Py+movy)*ZoomRate,LPen ,TextOutlinePen   
							,QString(tr("円弧長="))
							+QString::number(Len,'f',Parent->GetParamGlobal()->SmallNumberFigure));

				DrawText(pnt,(Px+movx)*ZoomRate,(Py+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="  ))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
	}
	else if(Action==_MLA_Angle){
		if(Step>=1){
			int	x1=(P2PA.x()+movx)*ZoomRate;
			int	y1=(P2PA.y()+movy)*ZoomRate;
			int	x2=(P2PB.x()+movx)*ZoomRate;
			int	y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

			pnt.setPen(LPen);
			pnt.drawLine(x1,y1,x2,y2);
		}

		if(Step>=3){
			double	s2=0;
			double	s1=0;
			int	x1=(P2PC.x()+movx)*ZoomRate;
			int	y1=(P2PC.y()+movy)*ZoomRate;
			int	x2=(P2PD.x()+movx)*ZoomRate;
			int	y2=(P2PD.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

			pnt.setPen(LPen);
			pnt.drawLine(x1,y1,x2,y2);
		
			double	X ,Y;
			GetCrossPoint(P2PA.x(),P2PA.y(), P2PB.x(),P2PB.y()
						, P2PC.x(),P2PC.y(), P2PD.x(),P2PD.y() 
						, X ,Y);

			if(hypot(X-P2PA.x(),Y-P2PA.y())<hypot(X-P2PB.x(),Y-P2PB.y()))
				s1=GetSita(P2PB.x()-P2PA.x(),P2PB.y()-P2PA.y());
			else
				s1=GetSita(P2PA.x()-P2PB.x(),P2PA.y()-P2PB.y());

			if(hypot(X-P2PC.x(),Y-P2PC.y())<hypot(X-P2PD.x(),Y-P2PD.y()))
				s2=GetSita(P2PD.x()-P2PC.x(),P2PD.y()-P2PC.y());
			else
				s2=GetSita(P2PC.x()-P2PD.x(),P2PC.y()-P2PD.y());

			double	R1=hypot((P2PA.x()+P2PB.x())/2-X,(P2PA.y()+P2PB.y())/2-Y);
			double	R2=hypot((P2PC.x()+P2PD.x())/2-X,(P2PC.y()+P2PD.y())/2-Y);
			double	R=min(R1,R2);

			s1=RegulateAngle(-s1);
			s2=RegulateAngle(-s2);
			double	d=DiffSita(s1 ,s2);
			int	Px=X;
			int	Py=Y;
			pnt.setPen(LPen);
			if(s1<s2){
				if((s2-s1)<M_PI){
					pnt.drawArc((X+movx-R)*ZoomRate,(Y+movy-R)*ZoomRate,2*R*ZoomRate,2*R*ZoomRate,s1*5760/(2*M_PI),(s2-s1)*5760/(2*M_PI));
						
					double	ks=(s1+s2)/2;
					Px=X+R*cos(ks);
					Py=Y-R*sin(ks);
				}
				else{
					pnt.drawArc((X+movx-R)*ZoomRate,(Y+movy-R)*ZoomRate,2*R*ZoomRate,2*R*ZoomRate,s2*5760/(2*M_PI),d*5760/(2*M_PI));
					double	ks=(s2+s2+d)/2;
					Px=X+R*cos(ks);
					Py=Y-R*sin(ks);
				}
			}
			else if(s2<s1){
				if((s1-s2)<M_PI){
					pnt.drawArc((X+movx-R)*ZoomRate,(Y+movy-R)*ZoomRate,2*R*ZoomRate,2*R*ZoomRate,s2*5760/(2*M_PI),(s1-s2)*5760/(2*M_PI));
					double	ks=(s1+s2)/2;
					Px=X+R*cos(ks);
					Py=Y-R*sin(ks);
				}
				else{
					pnt.drawArc((X+movx-R)*ZoomRate,(Y+movy-R)*ZoomRate,2*R*ZoomRate,2*R*ZoomRate,s1*5760/(2*M_PI),d*5760/(2*M_PI));
					double	ks=(s1+s1+d)/2;
					Px=X+R*cos(ks);
					Py=Y-R*sin(ks);
				}
			}
			DrawText(pnt,(Px+movx)*ZoomRate,(Py+movy)*ZoomRate,LPen ,TextOutlinePen
							,QString(tr("角度="))
							+QString::number(d*360.0/(2*M_PI),'f',Parent->GetParamGlobal()->SmallNumberFigure));
		}
	}
	else if(Action==_MLA_Rectangle){
		if(Step>=1){
			int	x1=(P2PA.x()+movx)*ZoomRate;
			int	y1=(P2PA.y()+movy)*ZoomRate;
			int	x2=(P2PB.x()+movx)*ZoomRate;
			int	y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

			pnt.setPen(LPen);
			pnt.drawLine(x1,y1,x1,y2);
			pnt.drawLine(x1,y2,x2,y2);
			pnt.drawLine(x2,y2,x2,y1);
			pnt.drawLine(x2,y1,x1,y1);
			int	cx=(x1+x2)/2;
			int	cy=(y1+y2)/2;
			double	realX1,realY1;
			double	realX2,realY2;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					DrawText(pnt,cx,cy,LPen ,TextOutlinePen
								,QString(tr("横="))
								+QString::number(fabs(realX1-realX2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitName);
					DrawText(pnt,cx,cy+TextHeight,LPen ,TextOutlinePen
								,QString(tr("縦="))
								+QString::number(fabs(realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitName);
					DrawText(pnt,cx,cy+TextHeight*2,LPen ,TextOutlinePen
								,QString(tr("面積="))
								+QString::number(fabs(realX1-realX2)*fabs(realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitSquareName);
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					DrawText(pnt,cx,cy,LPen ,TextOutlinePen
								,QString(tr("横="))
								+QString::number(fabs(realX1-realX2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitName);
					DrawText(pnt,cx,cy+TextHeight,LPen ,TextOutlinePen
								,QString(tr("縦="))
								+QString::number(fabs(realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitName);
					DrawText(pnt,cx,cy+TextHeight*2,LPen ,TextOutlinePen
								,QString(tr("面積="))
								+QString::number(fabs(realX1-realX2)*fabs(realY1-realY2),'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitSquareName);
				}
				else{
					DrawText(pnt,cx,cy,LPen ,TextOutlinePen
								,QString(tr("横="))
								+QString::number(abs(P2PA.x()-P2PB.x()),'f',Parent->GetParamGlobal()->SmallNumberFigure));
					DrawText(pnt,cx,cy+TextHeight,LPen ,TextOutlinePen
								,QString(tr("縦="))
								+QString::number(abs(P2PA.y()-P2PB.y()),'f',Parent->GetParamGlobal()->SmallNumberFigure));
					DrawText(pnt,cx,cy+TextHeight*2,LPen ,TextOutlinePen
								,QString(tr("面積="))
								+QString::number(abs(P2PA.x()-P2PB.x())*abs(P2PA.y()-P2PB.y()),'f',Parent->GetParamGlobal()->SmallNumberFigure));
				}
			}
		}
	}
	else if(Action==_MLA_PolyLine){
		if(PN.count()>=1){
			QPointF Points[1000];
			QPointF PointsR[1000];
			int		PointsNumb=0;
			QPoint	Last=PN.last();
			int	x1=(Last.x()+movx)*ZoomRate;
			int	y1=(Last.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);

			int	MinX=Last.x();
			int	MinY=Last.y();
			int	MaxX=Last.x();
			int	MaxY=Last.y();
			bool	HasReal=true;
			for(int i=0;i<PN.count();i++){
				QPoint	P=PN[i];

				if(i<1000){
					Points[i]=P;
					double	realX1,realY1;

					Flag=false;
					if(Pg!=NULL){
						if(Pg->HasRealTransform(P.x() ,P.y())==true
						&& Pg->TransformImageToReal(P.x() ,P.y() ,realX1 ,realY1)==true){
							PointsR[i]=QPointF(realX1 ,realY1);
							Flag=true;
						}
					}
					if(Flag==false){
						if(Parent->GetLayersBase()->HasRealTransform(P.x() ,P.y())==true
						&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P.x() ,P.y() ,realX1 ,realY1)==true){
							PointsR[i]=QPointF(realX1 ,realY1);
						}
						else{
							HasReal=false;
						}
					}
					PointsNumb++;
				}
				int	x2=(P.x()+movx)*ZoomRate;
				int	y2=(P.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

				pnt.setPen(LPen);
				pnt.drawLine(x1,y1,x2,y2);

				MinX=min(MinX,P.x());
				MinY=min(MinY,P.y());
				MaxX=max(MaxX,P.x());
				MaxY=max(MaxY,P.y());
				Last=P;
				x1=(Last.x()+movx)*ZoomRate;
				y1=(Last.y()+movy)*ZoomRate;
			}
			if(PointsNumb>=3){
				double	Area	=GetAreaPolygon(Points ,PointsNumb);
				double	AreaR	=GetAreaPolygon(PointsR,PointsNumb);
				if(HasReal==true){
					DrawText(pnt,((MinX+MaxX)/2+movx)*ZoomRate,((MinY+MaxY)/2+movy)*ZoomRate,LPen ,TextOutlinePen
								,QString(tr("面積="))
								+QString::number(AreaR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
								+Parent->GetParamGlobal()->UnitSquareName);
				}
				else{
					DrawText(pnt,((MinX+MaxX)/2+movx)*ZoomRate,((MinY+MaxY)/2+movy)*ZoomRate,LPen ,TextOutlinePen
								,QString(tr("面積="))
								+QString::number(Area,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				}
			}
		}
	}
	else if(Action==_MLA_Circle){
		if(Step>=1){
			{
				int	x1=(P2PA.x()+movx)*ZoomRate;
				int	y1=(P2PA.y()+movy)*ZoomRate;
				int	x2=(P2PB.x()+movx)*ZoomRate;
				int	y2=(P2PB.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}
			int	Cx=(P2PA.x()+P2PB.x())/2;
			int	Cy=(P2PA.y()+P2PB.y())/2;
			double	R=hypot(P2PA.x()-Cx,P2PA.y()-Cy);
			double	realX1,realY1;
			double	realX2,realY2;
			double	RR=0;
			bool	HasReal=false;
			Flag=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					double	RCx=(realX1+realX2)/2.0;
					double	RCy=(realY1+realY2)/2.0;
					RR=hypot(realX1-RCx,realY1-RCy);
					HasReal=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					double	RCx=(realX1+realX2)/2.0;
					double	RCy=(realY1+realY2)/2.0;
					RR=hypot(realX1-RCx,realY1-RCy);
					HasReal=true;
				}
			}
			{
				if(R>0){
					int	x1=(Cx-R+movx)*ZoomRate;
					int	y1=(Cy-R+movy)*ZoomRate;
					int	x2=(Cx+R+movx)*ZoomRate;
					int	y2=(Cy+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasReal==true){
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
	}
	else if(Action==_MLA_Isolation){
		int	x1;
		int	y1;
		int	x2;
		int	y2;
		if(Step>=1){
			x1=(P2PA.x()+movx)*ZoomRate;
			y1=(P2PA.y()+movy)*ZoomRate;
			x2=(P2PB.x()+movx)*ZoomRate;
			y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);

			pnt.setPen(LPen);
			pnt.drawLine(x1,y1,x2,y2);
			
		}
		if(Step>=2){
			int	hx=P2PB.x()-P2PA.x();
			int	hy=P2PB.y()-P2PA.y();
			int	cx=P2PC.x();
			int	cy=P2PC.y();
			double	D=(hx*hx+hy*hy);
			if(fabs(D)>0.01){
				double	k=((P2PA.x()-cx)*hx+(P2PA.y()-cy)*hy)/D;
				int	X3=hx*k+cx;
				int	Y3=hy*k+cy;
				int	X4=hx*(k+1)+cx;
				int	Y4=hy*(k+1)+cy;
				int	x3=(X3+movx)*ZoomRate;
				int	y3=(Y3+movy)*ZoomRate;
				int	x4=(X4+movx)*ZoomRate;
				int	y4=(Y4+movy)*ZoomRate;
				pnt.setPen(LPen);
				pnt.drawLine(x3,y3,x4,y4);

				pnt.drawLine((x1+x2)/2,(y1+y2)/2,(x3+x4)/2,(y3+y4)/2);

				double	Len=hypot(P2PA.x()-X3,P2PA.y()-Y3);


				double	realX1,realY1;
				double	realX2,realY2;
				double	realX3,realY3;
				double	LenR=0;
				bool	HasReal=false;
				if(Pg!=NULL){
					if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
					&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
					&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
					&& Pg->TransformImageToReal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
						double	hxR=realX2-realX1;
						double	hyR=realY2-realY1;
						double	cxR=realX3;
						double	cyR=realY3;
						double	DR=(hxR*hxR+hyR*hyR);
						if(DR>=0.0001){
							double	kR=((realX1-cxR)*hxR+(realY1-cyR)*hyR)/DR;
							double	X3R=hxR*kR+cxR;
							double	Y3R=hyR*kR+cyR;
							LenR=hypot(realX1-X3R,realY1-Y3R);
							HasReal=true;
							Flag=true;
						}
					}
				}
				if(Flag==false){
					if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
					&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
					&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
					&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){

						double	hxR=realX2-realX1;
						double	hyR=realY2-realY1;
						double	cxR=realX3;
						double	cyR=realY3;
						double	DR=(hxR*hxR+hyR*hyR);
						if(DR>=0.0001){
							double	kR=((realX1-cxR)*hxR+(realY1-cyR)*hyR)/DR;
							double	X3R=hxR*kR+cxR;
							double	Y3R=hyR*kR+cyR;
							LenR=hypot(realX1-X3R,realY1-Y3R);
							HasReal=true;
						}
					}
				}

				double	mcx=(P2PA.x()+P2PB.x()+X3+X4)/4;
				double	mcy=(P2PA.y()+P2PB.y()+Y3+Y4)/4;
				if(HasReal==true){
					DrawText(pnt,(mcx+movx)*ZoomRate,(mcy+movy)*ZoomRate,LPen ,TextOutlinePen
						,QString(tr("距離="))
						+QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
						+Parent->GetParamGlobal()->UnitName);
				}
				else{
					DrawText(pnt,(mcx+movx)*ZoomRate,(mcy+movy)*ZoomRate,LPen ,TextOutlinePen
						,QString(tr("距離="))
						+QString::number(Len,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				}
			}
		}
	}
	else if(Action==_MLA_Circle3){
		if(Step==1){
			
			int	x1=(P2PA.x()+movx)*ZoomRate;
			int	y1=(P2PA.y()+movy)*ZoomRate;
			int	x2=(P2PB.x()+movx)*ZoomRate;
			int	y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			
			int	Cx=(P2PA.x()+P2PB.x())/2;
			int	Cy=(P2PA.y()+P2PB.y())/2;
			double	R=hypot(P2PA.x()-Cx,P2PA.y()-Cy);
			double	realX1= x1,realY1= y1;
			double	realX2= x2,realY2= y2;
			bool	HasReal=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					HasReal=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					HasReal=true;
				}
			}
			double	CxR=(realX1+realX2)/2;
			double	CyR=(realY1+realY2)/2;
			double	RR=hypot(realX1-CxR,realY1-CyR);
			{
				if(R>0){
					int	x1=(Cx-R+movx)*ZoomRate;
					int	y1=(Cy-R+movy)*ZoomRate;
					int	x2=(Cx+R+movx)*ZoomRate;
					int	y2=(Cy+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasReal==true){
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
		else if(Step>=2){
			{
				int	x1=(P2PA.x()+movx)*ZoomRate;
				int	y1=(P2PA.y()+movy)*ZoomRate;
				int	x2=(P2PB.x()+movx)*ZoomRate;
				int	y2=(P2PB.y()+movy)*ZoomRate;
				int	x3=(P2PC.x()+movx)*ZoomRate;
				int	y3=(P2PC.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x3-CircleSize,y3-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x3-(CircleSize-1),y3-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}
			double Cx, Cy ,R;
			CalcCircleFrom3PointsCover(P2PA.x(), P2PA.y()
									,  P2PB.x(), P2PB.y()
									,  P2PC.x(), P2PC.y()
									,  Cx, Cy ,R);
			double	RR=0;
			double	realX1,realY1;
			double	realX2,realY2;
			double	realX3,realY3;
			bool	HasReal=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Pg->TransformImageToReal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					double RCx, RCy;
					CalcCircleFrom3PointsCover(realX1 ,realY1
											  ,realX2 ,realY2
											  ,realX3 ,realY3
											  ,RCx, RCy ,RR);
					HasReal=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					double RCx, RCy;
					CalcCircleFrom3PointsCover(realX1 ,realY1
											  ,realX2 ,realY2
											  ,realX3 ,realY3
											  ,RCx, RCy ,RR);
					HasReal=true;
				}
			}
			{
				if(R>0){
					int	x1=(Cx-R+movx)*ZoomRate;
					int	y1=(Cy-R+movy)*ZoomRate;
					int	x2=(Cx+R+movx)*ZoomRate;
					int	y2=(Cy+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasReal==true){
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate+TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
	}
	else if(Action==_MLA_CenterCircle){
		double Cx1, Cy1;
		double Cx2, Cy2;
		double RCx1=0.0, RCy1=0.0;
		double RCx2=0.0, RCy2=0.0;
		bool	HasRealA=false;
		if(Step==1){
			
			int	x1=(P2PA.x()+movx)*ZoomRate;
			int	y1=(P2PA.y()+movy)*ZoomRate;
			int	x2=(P2PB.x()+movx)*ZoomRate;
			int	y2=(P2PB.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			
			Cx1=(P2PA.x()+P2PB.x())/2;
			Cy1=(P2PA.y()+P2PB.y())/2;
			double	R=hypot(P2PA.x()-Cx1,P2PA.y()-Cy1);

			double	realX1=x1,realY1=y1;
			double	realX2=x2,realY2=y2;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					HasRealA=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true){
					HasRealA=true;
				}
			}
			RCx1=(realX1+realX2)/2;
			RCy1=(realY1+realY2)/2;
			double	RR=hypot(realX1-RCx1,realY1-RCy1);
			{
				if(R>0){
					int	x1=(Cx1-R+movx)*ZoomRate;
					int	y1=(Cy1-R+movy)*ZoomRate;
					int	x2=(Cx1+R+movx)*ZoomRate;
					int	y2=(Cy1+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasRealA==true){
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
			Cx2=Cx1;
			Cy2=Cy1;
		}
		else if(Step>=2){
			{
				int	x1=(P2PA.x()+movx)*ZoomRate;
				int	y1=(P2PA.y()+movy)*ZoomRate;
				int	x2=(P2PB.x()+movx)*ZoomRate;
				int	y2=(P2PB.y()+movy)*ZoomRate;
				int	x3=(P2PC.x()+movx)*ZoomRate;
				int	y3=(P2PC.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x3-CircleSize,y3-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x3-(CircleSize-1),y3-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}
			double R;
			CalcCircleFrom3PointsCover(P2PA.x(), P2PA.y()
									,  P2PB.x(), P2PB.y()
									,  P2PC.x(), P2PC.y()
									,  Cx1, Cy1 ,R);
			double	RR=0;
			double	realX1,realY1;
			double	realX2,realY2;
			double	realX3,realY3;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Pg->TransformImageToReal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Pg->TransformImageToReal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx1, RCy1 ,RR);
					HasRealA=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PA.x() ,P2PA.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PA.x() ,P2PA.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PB.x() ,P2PB.y() ,realX2 ,realY2)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PC.x() ,P2PC.y() ,realX3 ,realY3)==true){
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx1, RCy1 ,RR);
					HasRealA=true;
				}
			}
			{
				if(R>0){
					int	x1=(Cx1-R+movx)*ZoomRate;
					int	y1=(Cy1-R+movy)*ZoomRate;
					int	x2=(Cx1+R+movx)*ZoomRate;
					int	y2=(Cy1+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasRealA==true){
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate ,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
			Cx2=Cx1;
			Cy2=Cy1;
		}
		else{
			return;
		}
		bool	HasRealB=false;
		if(Step==3 || Step==4){			
			int	x1=(P2PD.x()+movx)*ZoomRate;
			int	y1=(P2PD.y()+movy)*ZoomRate;
			int	x2=(P2PE.x()+movx)*ZoomRate;
			int	y2=(P2PE.y()+movy)*ZoomRate;
			pnt.setPen(Parent->CircleColor);
			pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
			pnt.setPen(RCircleColor);
			pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			
			Cx2=(P2PD.x()+P2PE.x())/2;
			Cy2=(P2PD.y()+P2PE.y())/2;
			double	R=hypot(P2PD.x()-Cx2,P2PD.y()-Cy2);

			double	realX1=x1,realY1=y1;
			double	realX2=x2,realY2=y2;
			Flag=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PD.x() ,P2PD.y())==true
				&& Pg->TransformImageToReal(P2PD.x() ,P2PD.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PE.x() ,P2PE.y() ,realX2 ,realY2)==true){
					HasRealB=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PD.x() ,P2PD.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PD.x() ,P2PD.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PE.x() ,P2PE.y() ,realX2 ,realY2)==true){
					HasRealB=true;
				}
			}
			RCx2=(realX1+realX2)/2;
			RCy2=(realY1+realY2)/2;
			double	RR=hypot(realX1-RCx2,realY1-RCy2);
			{
				if(R>0){
					int	x1=(Cx2-R+movx)*ZoomRate;
					int	y1=(Cy2-R+movy)*ZoomRate;
					int	x2=(Cx2+R+movx)*ZoomRate;
					int	y2=(Cy2+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasRealB==true){
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
		else if(Step>=5){
			{
				int	x1=(P2PD.x()+movx)*ZoomRate;
				int	y1=(P2PD.y()+movy)*ZoomRate;
				int	x2=(P2PE.x()+movx)*ZoomRate;
				int	y2=(P2PE.y()+movy)*ZoomRate;
				int	x3=(P2PF.x()+movx)*ZoomRate;
				int	y3=(P2PF.y()+movy)*ZoomRate;
				pnt.setPen(Parent->CircleColor);
				pnt.drawArc(x1-CircleSize,y1-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x2-CircleSize,y2-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.drawArc(x3-CircleSize,y3-CircleSize,2*CircleSize,2*CircleSize,0,5759);
				pnt.setPen(RCircleColor);
				pnt.drawArc(x1-(CircleSize-1),y1-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x2-(CircleSize-1),y2-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
				pnt.drawArc(x3-(CircleSize-1),y3-(CircleSize-1),2*(CircleSize-1),2*(CircleSize-1),0,5759);
			}
			double R;
			CalcCircleFrom3PointsCover(P2PD.x(), P2PD.y()
									, P2PE.x(), P2PE.y()
									, P2PF.x(), P2PF.y()
									,Cx2, Cy2 ,R);
			double	RR=0;
			double	realX1,realY1;
			double	realX2,realY2;
			double	realX3,realY3;
			Flag=false;
			if(Pg!=NULL){
				if(Pg->HasRealTransform(P2PD.x() ,P2PD.y())==true
				&& Pg->TransformImageToReal(P2PD.x() ,P2PD.y() ,realX1 ,realY1)==true
				&& Pg->TransformImageToReal(P2PE.x() ,P2PE.y() ,realX2 ,realY2)==true
				&& Pg->TransformImageToReal(P2PF.x() ,P2PF.y() ,realX3 ,realY3)==true){
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx2, RCy2 ,RR);
					HasRealB=true;
					Flag=true;
				}
			}
			if(Flag==false){
				if(Parent->GetLayersBase()->HasRealTransform(P2PD.x() ,P2PD.y())==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PD.x() ,P2PD.y() ,realX1 ,realY1)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PE.x() ,P2PE.y() ,realX2 ,realY2)==true
				&& Parent->GetLayersBase()->GetRealMatrixFromGlobal(P2PF.x() ,P2PF.y() ,realX3 ,realY3)==true){
					
					CalcCircleFrom3PointsCover(realX1 ,realY1
											,  realX2 ,realY2
											,  realX3 ,realY3
											,  RCx2, RCy2 ,RR);
					HasRealB=true;
				}
			}
			{
				if(R>0){
					int	x1=(Cx2-R+movx)*ZoomRate;
					int	y1=(Cy2-R+movy)*ZoomRate;
					int	x2=(Cx2+R+movx)*ZoomRate;
					int	y2=(Cy2+R+movy)*ZoomRate;
					pnt.setPen(LPen);
					pnt.drawArc(x1,y1,x2-x1,y2-y1,0,5759);
				}
			}
			if(HasRealB==true){
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*RR*RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitSquareName);
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(RR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate,LPen ,TextOutlinePen 
							,QString(tr("面積="))
							+QString::number(M_PI*R*R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
				DrawText(pnt,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate +TextHeight,LPen ,TextOutlinePen 
							,QString(tr("半径="))
							+QString::number(R,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
	
		if(Step>=5){
			double	Cx=(Cx1+Cx2)/2;
			double	Cy=(Cy1+Cy2)/2;
			double	Len	=hypot(Cx2-Cx1,Cy2-Cy1);
			double	LenR=hypot(RCx2-RCx1,RCy2-RCy1);
			pnt.setPen(LPen);
			pnt.drawLine((Cx1+movx)*ZoomRate,(Cy1+movy)*ZoomRate,(Cx2+movx)*ZoomRate,(Cy2+movy)*ZoomRate);

			if(HasRealA==true && HasRealB==true){
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen  
							,QString(tr("距離="))
							+QString::number(LenR,'f',Parent->GetParamGlobal()->SmallNumberFigure)
							+Parent->GetParamGlobal()->UnitName);
			}
			else{
				DrawText(pnt,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate,LPen ,TextOutlinePen  
							,QString(tr("距離="))
							+QString::number(Len,'f',Parent->GetParamGlobal()->SmallNumberFigure));
			}
		}
	}
}

inline	void	MulPoint(QPoint &Point, double m[6])
{
	if(Point.isNull()==false){
		double	X=Point.x();
		double	Y=Point.y();
		Point.setX(X*m[0]+Y*m[1]+m[2]);
		Point.setY(X*m[3]+Y*m[4]+m[5]);
	}
}

void	HookMeasureForm::MeasuredList::Transform(double m[6])
{
	MulPoint(P2PA,m);
	MulPoint(P2PB,m);
	MulPoint(P2PC,m);
	MulPoint(P2PD,m);
	MulPoint(P2PE,m);
	MulPoint(P2PF,m);
	for(int i=0;i<PN.count();i++){
		MulPoint(PN[i],m);
	}
}

HookMeasureForm::MeasuredList	&HookMeasureForm::MeasuredList::operator=(const HookMeasureForm::MeasuredList &src)
{
	Parent	=src.Parent;
	LineColor	=src.LineColor	;
	CircleColor	=src.CircleColor;	
	LineWidth	=src.LineWidth	;
	ArrowSize	=src.ArrowSize	;
	LineType	=src.LineType	;

	Step	=src.Step;
	P2PA	=src.P2PA;
	P2PB	=src.P2PB;
	P2PC	=src.P2PC;
	P2PD	=src.P2PD;
	P2PE	=src.P2PE;
	P2PF	=src.P2PF;
	PN.clear();
	for(int i=0;i<src.PN.count();i++){
		QPoint	P=src.PN[i];
		PN.append(P);
	}
	Action	=src.Action;
	return *this;
}
bool	HookMeasureForm::MeasuredList::operator==(HookMeasureForm::MeasuredList &src)
{
	if(LineColor	!=src.LineColor	)
		return false;
	if(CircleColor	!=src.CircleColor)
		return false;
	if(LineWidth	!=src.LineWidth	)
		return false;
	if(ArrowSize	!=src.ArrowSize	)
		return false;
	if(LineType		!=src.LineType	)
		return false;

	if(P2PA	!=src.P2PA
	|| P2PB	!=src.P2PB
	|| P2PC	!=src.P2PC
	|| P2PD	!=src.P2PD
	|| P2PE	!=src.P2PE
	|| P2PF	!=src.P2PF)
		return false;
	if(PN.count()!=src.PN.count())
		return false;
	for(int i=0;i<src.PN.count();i++){
		QPoint	P1=PN[i];
		QPoint	P2=src.PN[i];
		if(P1!=P2){
			return false;
		}
	}
	if(Action	!=src.Action)
		return false;
	return true;
}
void	HookMeasureForm::MeasuredList::Swap(HookMeasureForm::MeasuredList &s)
{
	swap(LineColor,s.LineColor);
	swap(CircleColor,s.CircleColor);
	swap(LineWidth,s.LineWidth);
	swap(ArrowSize,s.ArrowSize);

	HookMeasureForm::__LineType	iLineType=LineType;
	LineType=s.LineType;
	s.LineType=iLineType;

	swap(P2PA,s.P2PA);
	swap(P2PB,s.P2PB);
	swap(P2PC,s.P2PC);
	swap(P2PD,s.P2PD);
	swap(P2PE,s.P2PE);
	swap(P2PF,s.P2PF);

	QList<QPoint>	TmpPN;
	TmpPN=PN;
	PN=s.PN;
	s.PN=TmpPN;

	swap(ID,s.ID);
	swap(Step,s.Step);
}

void	HookMeasureForm::MeasuredList::MoveTo(int dx ,int dy)
{
	QPoint	AddedXY(dx,dy);
	P2PA+=AddedXY;
	P2PB+=AddedXY;
	P2PC+=AddedXY;
	P2PD+=AddedXY;
	P2PE+=AddedXY;
	P2PF+=AddedXY;
	for(int i=0;i<PN.count();i++){
		PN[i].setX(PN[i].x()+dx);
		PN[i].setY(PN[i].y()+dy);
	}
}

bool	HookMeasureForm::MeasuredList::EditSelection(int GlobalPosX,int GlobalPosY,int Distance)
{
	if(Action==_MLA_Point2Point){
		if(GetLengthLine2Point(P2PA.x(),P2PA.y(),P2PB.x(),P2PB.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=1;
			return true;
		}
	}
	else if(Action==_MLA_FoldedLines){
		for(int i=0;i<PN.count()-1;i++){
			QPoint	P1=PN[i];
			QPoint	P2=PN[i+1];
			if(GetLengthLine2Point(P1.x(),P1.y(),P2.x(),P2.y()
								,  GlobalPosX , GlobalPosY)<Distance){
				Step=1;
				return true;
			}
		}
	}
	else if(Action==_MLA_Arc){
		double Cx, Cy ,R;
		CalcCircleFrom3PointsCover(P2PA.x(), P2PA.y()
								,  P2PB.x(), P2PB.y()
								,  P2PC.x(), P2PC.y()
								,  Cx, Cy ,R);
		double	r=hypot(GlobalPosX-Cx,GlobalPosY-Cy);
		if(fabs(R-r)<Distance){			
			if(R>0){
				double	s =-GetSita(GlobalPosX-Cx,GlobalPosY-Cy);
				double	s1=-GetSita(P2PA.x()-Cx,P2PA.y()-Cy);
				double	s2=-GetSita(P2PB.x()-Cx,P2PB.y()-Cy);
				double	s3=-GetSita(P2PC.x()-Cx,P2PC.y()-Cy);
				s =RegulateAngle(s );
				s1=RegulateAngle(s1);
				s2=RegulateAngle(s2);
				s3=RegulateAngle(s3);
				if(s1<=s3 && s3<=s2 && s1<=s && s<=s2){
					Step=3;
					return true;
				}
				else if(s2<=s3 && s3<=s1 && s2<=s && s<=s1){
					Step=3;
					return true;
				}
				else if(s2<=s1 && (s1<=s3 || s3<=s2) && (s1<=s || s<=s2)){
					Step=3;
					return true;
				}
				else if(s1<=s2 && (s2<=s3 || s3<=s1) && (s2<=s || s<=s1)){
					Step=3;
					return true;
				}
			}		
		}
	}
	else if(Action==_MLA_CenterCircle){
		double	R1;
		double	Cx1,Cy1;
		CalcCircleFrom3PointsCover(P2PA.x(), P2PA.y()
								,  P2PB.x(), P2PB.y()
								,  P2PC.x(), P2PC.y()
								,  Cx1, Cy1 ,R1);		
		double	r1=hypot(GlobalPosX-Cx1,GlobalPosY-Cy1);
		if(fabs(R1-r1)<Distance){
			return true;
		}		
		double	R2;
		double	Cx2,Cy2;
		CalcCircleFrom3PointsCover(P2PD.x(), P2PD.y()
								,  P2PE.x(), P2PE.y()
								,  P2PF.x(), P2PF.y()
								,  Cx2, Cy2 ,R2);
		double	r2=hypot(GlobalPosX-Cx2,GlobalPosY-Cy2);
		if(fabs(R2-r2)<Distance){
			return true;
		}
		if(GetLengthLine2Point((int)Cx1,(int)Cy1,(int)Cx2,(int)Cy2
							,  GlobalPosX , GlobalPosY)<Distance){
			return true;
		}
	}
	else if(Action==_MLA_Angle){
		if(GetLengthLine2Point(P2PA.x(),P2PA.y(),P2PB.x(),P2PB.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=4;
			return true;
		}
		if(GetLengthLine2Point(P2PC.x(),P2PC.y(),P2PD.x(),P2PD.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=4;
			return true;
		}
	}
	else if(Action==_MLA_Rectangle){
		if(GetLengthLine2Point(P2PA.x(),P2PA.y(),P2PB.x(),P2PA.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=2;
			return true;
		}
		if(GetLengthLine2Point(P2PB.x(),P2PA.y(),P2PB.x(),P2PB.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=2;
			return true;
		}
		if(GetLengthLine2Point(P2PB.x(),P2PB.y(),P2PA.x(),P2PB.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=2;
			return true;
		}
		if(GetLengthLine2Point(P2PA.x(),P2PB.y(),P2PA.x(),P2PA.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=2;
			return true;
		}
	}
	else if(Action==_MLA_PolyLine){
		for(int i=0;i<PN.count()-1;i++){
			QPoint	P1=PN[i];
			QPoint	P2=PN[i+1];
			if(GetLengthLine2Point(P1.x(),P1.y(),P2.x(),P2.y()
								,  GlobalPosX , GlobalPosY)<Distance){
				Step=1;
				return true;
			}
		}
		if(PN.count()>=3){
			QPoint	P1=PN[PN.count()-1];
			QPoint	P2=PN[0];
			if(GetLengthLine2Point(P1.x(),P1.y(),P2.x(),P2.y()
								,  GlobalPosX , GlobalPosY)<Distance){
				Step=1;
				return true;
			}
		}
	}
	else if(Action==_MLA_Circle){
		int	iCx=(P2PA.x()+P2PB.x())/2;
		int	iCy=(P2PA.y()+P2PB.y())/2;
		double	iR=hypot(P2PA.x()-iCx,P2PA.y()-iCy);
		double	r=hypot(GlobalPosX-iCx,GlobalPosY-iCy);
		if(fabs(iR-r)<Distance){
			Step=2;
			return true;
		}
	}
	else if(Action==_MLA_Isolation){
		if(GetLengthLine2Point(P2PA.x(),P2PA.y(),P2PB.x(),P2PB.y()
								,GlobalPosX , GlobalPosY)<Distance){
			Step=3;
			return true;
		}
		int	hx=P2PB.x()-P2PA.x();
		int	hy=P2PB.y()-P2PA.y();
		int	cx=P2PC.x();
		int	cy=P2PC.y();
		double	D=(hx*hx+hy*hy);
		if(fabs(D)>0.01){
			double	k=((P2PA.x()-cx)*hx+(P2PA.y()-cy)*hy)/D;
			int	X3=hx*k+cx;
			int	Y3=hy*k+cy;
			int	X4=hx*(k+1)+cx;
			int	Y4=hy*(k+1)+cy;
			if(GetLengthLine2Point(X3,Y3,X4,Y4
									,GlobalPosX , GlobalPosY)<Distance){
				Step=3;
				return true;
			}
		}
	}
	else if(Action==_MLA_Circle3){
		double Cx, Cy ,R;
		CalcCircleFrom3PointsCover(P2PA.x(), P2PA.y()
								,  P2PB.x(), P2PB.y()
								,  P2PC.x(), P2PC.y()
								,  Cx, Cy ,R);
		double	r=hypot(GlobalPosX-Cx,GlobalPosY-Cy);
		if(fabs(R-r)<Distance){
			Step=3;
			return true;
		}
	}
	return false;
}


bool	HookMeasureForm::MeasuredList::Save(QIODevice *f)
{
	BYTE	Ver=1;

	if(::Save(f,Ver	)==false)	return false;
	if(::Save(f,ID	)==false)	return false;

	if(::Save(f,LineColor		)==false)	return false;
	if(::Save(f,CircleColor		)==false)	return false;
	if(::Save(f,LineWidth		)==false)	return false;
	if(::Save(f,ArrowSize		)==false)	return false;
	if(::Save(f,(int32)LineType	)==false)	return false;

	if(::Save(f,Step)==false)	return false;
	if(::Save(f,P2PA)==false)	return false;
	if(::Save(f,P2PB)==false)	return false;
	int32	N=PN.count();
	if(::Save(f,N)==false)	return false;
	for(int i=0;i<N;i++){
		if(::Save(f,PN[i])==false)	return false;
	}
	if(::Save(f,P2PC)==false)	return false;
	if(::Save(f,P2PD)==false)	return false;
	if(::Save(f,P2PE)==false)	return false;
	if(::Save(f,P2PF)==false)	return false;

	BYTE	tAction=(BYTE)Action;
	if(::Save(f,tAction)==false)	return false;
	BYTE	tStatus=(BYTE)Status;
	if(::Save(f,tStatus)==false)	return false;
	return true;
}

bool	HookMeasureForm::MeasuredList::Load(QIODevice *f)
{
	BYTE	Ver;

	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,ID)==false)	return false;

	if(::Load(f,LineColor		)==false)	return false;
	if(::Load(f,CircleColor		)==false)	return false;
	if(::Load(f,LineWidth		)==false)	return false;
	if(::Load(f,ArrowSize		)==false)	return false;
	int32	iLineType;
	if(::Load(f,iLineType		)==false)	return false;
	LineType	=(HookMeasureForm::__LineType)iLineType;

	if(::Load(f,Step)==false)	return false;
	if(::Load(f,P2PA)==false)	return false;
	if(::Load(f,P2PB)==false)	return false;
	int32	N;
	if(::Load(f,N)==false)	return false;
	PN.clear();
	for(int i=0;i<N;i++){
		QPoint	P;
		if(::Load(f,P)==false)	return false;
		PN.append(P);
	}
	if(::Load(f,P2PC)==false)	return false;
	if(::Load(f,P2PD)==false)	return false;
	if(::Load(f,P2PE)==false)	return false;
	if(::Load(f,P2PF)==false)	return false;

	BYTE	tAction;
	if(::Load(f,tAction)==false)	return false;
	Action=(MLA_Action)tAction;

	BYTE	tStatus;
	if(::Load(f,tStatus)==false)	return false;
	Status=(MLA_Status)tStatus;
	return true;
}
