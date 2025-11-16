#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "swap.h"
#include "XCrossObj.h"

extern	int	DebugDCode;
extern	int	DbgPage	;
extern	int	DCodeDebug;
extern	int	DbgID	;

static	int	DbgLine=0;
static	double	DbgX=22.89824;
static	double	DbgY=185.65270;
static	int		DbgD=0;


//======================================================================
GerberFileLayer::GerberFileLayer(GerberFileLayerContainer *parent)
{
	Parent=parent;

	XNum	=3;
	XPNum	=4;
	YNum	=3;
	YPNum	=4;
	Unit	=1.0;
	XMultiply	=1.0;
	YMultiply	=1.0;

	LeadingZero	=false;
	TrailingZero=false;
	AbsMode		=true;

	RepeatCountX	=1;
	RepeatCountY	=1;
	RepeatDistanceX	=0.0;
	RepeatDistanceY	=0.0;
	Interporate360	=false;
	PolygonMode		=false;
	Polarity		=true;

	FileLayerID		=-1;
	LibID			=-1;
	ShrinkDot		=0;

	CurrentGCode	=-1;
	CurrentDCode	=-1;
	LastSelectedD	=-1;
	LastGCode		=-1;
	CurrentX		=0;
	CurrentY		=0;
	Shutter			=true;
	PolygonMode		=false;
	ViewInvert		=false;
}

bool	GerberFileLayer::Save(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,XNum)==false)
		return false;
	if(::Save(f,XPNum)==false)
		return false;
	if(::Save(f,YNum)==false)
		return false;
	if(::Save(f,YPNum)==false)
		return false;
	if(::Save(f,Unit)==false)
		return false;
	if(::Save(f,XMultiply)==false)
		return false;
	if(::Save(f,YMultiply)==false)
		return false;

	if(::Save(f,RepeatCountX)==false)
		return false;
	if(::Save(f,RepeatCountY)==false)
		return false;
	if(::Save(f,RepeatDistanceX)==false)
		return false;
	if(::Save(f,RepeatDistanceY)==false)
		return false;
	if(::Save(f,Interporate360)==false)
		return false;
	if(::Save(f,Polarity)==false)
		return false;

	if(::Save(f,LeadingZero)==false)
		return false;
	if(::Save(f,TrailingZero)==false)
		return false;
	if(::Save(f,AbsMode)==false)
		return false;
	if(::Save(f,LayerName)==false)
		return false;

	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;

	if(DCodeList.Save(f)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;

	if(::Save(f,ImageName)==false)
		return false;

	return true;
}

bool	GerberFileLayer::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,XNum)==false)
		return false;
	if(::Load(f,XPNum)==false)
		return false;
	if(::Load(f,YNum)==false)
		return false;
	if(::Load(f,YPNum)==false)
		return false;
	if(::Load(f,Unit)==false)
		return false;
	if(::Load(f,XMultiply)==false)
		return false;
	if(::Load(f,YMultiply)==false)
		return false;

	if(::Load(f,RepeatCountX)==false)
		return false;
	if(::Load(f,RepeatCountY)==false)
		return false;
	if(::Load(f,RepeatDistanceX)==false)
		return false;
	if(::Load(f,RepeatDistanceY)==false)
		return false;
	if(::Load(f,Interporate360)==false)
		return false;
	if(::Load(f,Polarity)==false)
		return false;

	if(::Load(f,LeadingZero)==false)
		return false;
	if(::Load(f,TrailingZero)==false)
		return false;
	if(::Load(f,AbsMode)==false)
		return false;
	if(::Load(f,LayerName)==false)
		return false;

	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;

	if(DCodeList.Load(f)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,ImageName)==false)
			return false;
	}

	return true;
}

GerberDCodeBase	*GerberFileLayer::FindDCode(int dcode)
{
	return DCodeList.FindDCode(dcode);
}

char	*strchrlimitted(char *fp ,char c ,char Term)
{
	while(*fp!=0){
		if(*fp==c)
			return fp;
		if(*fp==Term)
			return NULL;
		fp++;
	}
	return NULL;
}

bool	GerberFileLayer::LoadApertureHole(char *fp ,ApertureHole &Hole)
{
	if((fp=strchrlimitted(fp,/**/'X',/**/'*'))!=NULL){
		fp++;
		double	HoleW;
		if(matchscanf(fp,/**/"%lf",&HoleW)==1){
			if((fp=strchrlimitted(fp,/**/'X',/**/'*'))!=NULL){
				fp++;
				double	HoleH;
				if(matchscanf(fp,/**/"%lf",&HoleH)==1){
					Hole.HoleType=ApertureHole::_ApertureHole_Rectangle;
					Hole.WSize=HoleW*Unit;
					Hole.HSize=HoleH*Unit;
				}
			}
			else{
				Hole.HoleType=ApertureHole::_ApertureHole_Circle;
				Hole.WSize=HoleW*Unit;
				Hole.HSize=HoleW*Unit;
			}
		}
	}
	return true;
}

char	*CheckMacroInst(char *Buff ,int &DCode ,char MacroName[] ,int MaxLen)
{
	char	*fp=Buff;
	if('0'<=*fp && *fp<='9'){
		DCode=0;
		while('0'<=*fp && *fp<='9'){
			DCode*=10;
			DCode+=*fp-'0';
			fp++;
		}
		for(int i=0;i<MaxLen;i++){
			MacroName[i]=*fp;
			fp++;
			if(*fp==',' || *fp=='*' || *fp==0){
				MacroName[i+1]=0;
				return fp;
			}
		}
	}
	return NULL;
}

bool	MakeParam(char *fp,DoubleList &RetParam)
{
	QString	s(fp);
	QStringList	List=s.split(',');
	for(int i=0;i<List.count();i++){
		bool	ok;
		double	d=List[i].toDouble(&ok);
		if(ok==false)
			return false;
		RetParam.Add(d);
	}
	return true;
}

bool	____strcpy(char *dst ,char *src ,char c ,int maxlen)
{
	for(int i=0;i<maxlen;i++){
		if(src[i]==0){
			dst[i]=0;
			return true;
		}
		if(src[i]==c){
			if(i+1<maxlen){
				dst[i]=src[i];
				i++;
			}
			dst[i]=0;
			return true;
		}
		dst[i]=src[i];
	}
	return false;
}

bool	GerberFileLayer::LoadGerberData(GerberFastBase *GBase ,FILE *file ,bool TestMode)
{
	CurrentGCode	=-1;
	CurrentDCode	=-1;
	LastSelectedD	=-1;
	CurrentX		=0;
	CurrentY		=0;
	Shutter	=false;
	int		MeanfulContent=0;

	const int	MaxBuffSize=1000000;
	char	*Buff=new char[MaxBuffSize];
	Buff[MaxBuffSize-1]=0;

	int	LineNumber;
	char	*NextP=NULL;
	for(LineNumber=0;fgets(Buff,MaxBuffSize-1,file)!=NULL;LineNumber++){
		if(LineNumber==DbgLine){
			DbgD++;
		}
		int	BlockCount=0;
		for(char *Lp=Buff;*Lp!=0;BlockCount++){

			if(TestMode==true && (LineNumber>500 || BlockCount>500)){
				if(MeanfulContent<3){
					delete	[]Buff;
					return false;
				}
				delete	[]Buff;
				return true;
			}
LoopPoint:;
			if(Lp[0]==/**/'*' && Lp[1]==/**/'%'){
				Lp++;
			}
			if(Lp[0]==/**/'%'){
				NextP=strstr(&Lp[1],"*%");
				if(NextP!=NULL){
					NextP+=2;
				}
				if(strnicmp(&Lp[1],/**/"FS",2)==0){
					if(Lp[3]==/**/'L'){
						LeadingZero=true;
					}
					else if(Lp[3]==/**/'T'){
						TrailingZero=true;
					}
					if(Lp[4]==/**/'A'){
						AbsMode=true;
					}
					else if(Lp[4]==/**/'I'){
						AbsMode=false;
					}
					char	*fp=&Lp[5];
					while(*fp=='N' || *fp=='M'){
						if(*fp=='N'){
							int	IntPos;
							fp++;
							matchscanf(fp,/**/"%d",&IntPos);
							fp++;
						}
						else{
							int	DecPos;
							fp++;
							matchscanf(fp,/**/"%d",&DecPos);
							fp++;
						}
					}
						
					int	x,y;
					if(matchscanf(fp,/**/"X%dY%d",&x,&y)==2){
						XNum=x/10;
						XPNum=x%10;
						YNum=y/10;
						YPNum=y%10;
						XMultiply=1.0/pow(10.0,XPNum);
						YMultiply=1.0/pow(10.0,YPNum);
						MeanfulContent++;
					}
				}	
				else if(strnicmp(&Lp[1],/**/"MOMM",4)==0){
					Unit=1.0;
					MeanfulContent++;
				}	
				else if(strnicmp(&Lp[1],/**/"MOIN",4)==0){
					Unit=25.4;
					MeanfulContent++;
				}	
				else if(strnicmp(&Lp[1],/**/"LN",2)==0){
					char	cbuff[1000];
					____strcpy(cbuff,&Lp[3],'*',sizeof(cbuff)-1);
					char	*fp=strchr(cbuff,/**/'*');
					if(fp!=NULL){
						*fp=0;
					}
					LayerName=cbuff;
				}
				else if(strnicmp(&Lp[1],/**/"LP",2)==0){
					if(Lp[3]==/**/'D'){
						Polarity=true;
					}
					else{
						Polarity=false;
					}
				}
				else if(strnicmp(&Lp[1],/**/"IN",2)==0){
					char	cbuff[1000];
					____strcpy(cbuff,&Lp[3],'*',sizeof(cbuff)-1);
					char	*fp=strchr(cbuff,/**/'*');
					if(fp!=NULL){
						*fp=0;
					}
					ImageName=cbuff;
				}
				else if(strnicmp(&Lp[1],/**/"IF",2)==0){
					char	cbuff[1000];
					____strcpy(cbuff,&Lp[3],'*',sizeof(cbuff)-1);
					char	*fp=strchr(cbuff,/**/'*');
					if(fp!=NULL){
						*fp=0;
					}
					FILE	*file=fopen(cbuff,/**/"rt");
					if(file!=NULL){
						LoadGerberData(GBase,file,TestMode);
					}
				}
				else if(strnicmp(&Lp[1],/**/"SR",2)==0){
					if(matchscanf(&Lp[3],/**/"X%dY%dI%lfJ%lf*%",&RepeatCountX,&RepeatCountY,&RepeatDistanceX,&RepeatDistanceY)==4){
						RepeatDistanceX*=Unit;
						RepeatDistanceY*=Unit;
						MeanfulContent++;
					}
				}
				else if(strnicmp(&Lp[1],/**/"ADD",3)==0){
					int		dcode;
					char	CType;
					if(matchscanf(&Lp[4],/**/"%d%c,",&dcode,&CType)==2){
						char	*fp=strchr(&Lp[4],/**/',');
						if(fp==NULL || *fp==0)
							break;
						fp++;
						if(CType==/**/'C' || CType==/**/'c'){
							double	ToolD;
							if(matchscanf(fp,/**/"%lf",&ToolD)==1){
								GerberDCodeBase	*hd=DCodeList.FindDCode(dcode);
								GerberDCodeCircle	*md=dynamic_cast<GerberDCodeCircle *>(hd);
								if(hd==NULL || md==NULL){
									GerberDCodeCircle	*d=new GerberDCodeCircle(&DCodeList);
									d->HSize	=ToolD*Unit;
									d->WSize	=ToolD*Unit;
									d->DCode=dcode;
									DCodeList.AppendList(d);
									LoadApertureHole(fp ,d->Hole);
									MeanfulContent++;
								}
								else{
									md->HSize	=ToolD*Unit;
									md->WSize	=ToolD*Unit;
								}
							}
						}
						else if(CType==/**/'R' || CType==/**/'r'){
							double	ToolDx,ToolDy;
							if(matchscanf(fp,/**/"%lfX%lf",&ToolDx,&ToolDy)==2){
								GerberDCodeBase	*hd=DCodeList.FindDCode(dcode);
								GerberDCodeRectangle	*md=dynamic_cast<GerberDCodeRectangle *>(hd);
								if(hd==NULL || md==NULL){
									GerberDCodeRectangle	*d=new GerberDCodeRectangle(&DCodeList);
									d->WSize	=ToolDx*Unit;
									d->HSize	=ToolDy*Unit;
									d->DCode=dcode;
									DCodeList.AppendList(d);
									if((fp=strchr(fp,/**/'X'))!=NULL){
										fp++;
										LoadApertureHole(fp ,d->Hole);
									}
									MeanfulContent++;
								}
								else{
									md->WSize	=ToolDx*Unit;
									md->HSize	=ToolDy*Unit;
								}
							}
						}
						else if(CType==/**/'O' || CType==/**/'o'){
							double	ToolDx,ToolDy;
							if(matchscanf(fp,/**/"%lfX%lf",&ToolDx,&ToolDy)==2){
								GerberDCodeBase	*hd=DCodeList.FindDCode(dcode);
								GerberDCodeObround	*md=dynamic_cast<GerberDCodeObround *>(hd);
								if(hd==NULL || md==NULL){
									GerberDCodeObround	*d=new GerberDCodeObround(&DCodeList);
									d->WSize	=ToolDx*Unit;
									d->HSize	=ToolDy*Unit;
									d->DCode=dcode;
									DCodeList.AppendList(d);
									if((fp=strchr(fp,/**/'X'))!=NULL){
										fp++;
										LoadApertureHole(fp ,d->Hole);
									}
									MeanfulContent++;
								}
								else{
									md->WSize	=ToolDx*Unit;
									md->HSize	=ToolDy*Unit;
								}
							}
						}
						else if(CType==/**/'P' || CType==/**/'p'){
							double	ToolD;
							int		ToolS;
							if(matchscanf(fp,/**/"%lfX%d",&ToolD,&ToolS)==2){
								GerberDCodeBase	*hd=DCodeList.FindDCode(dcode);
								GerberDCodePolygon	*md=dynamic_cast<GerberDCodePolygon *>(hd);
								if(hd==NULL || md==NULL){
									GerberDCodePolygon	*d=new GerberDCodePolygon(&DCodeList);
									d->Diameter	=ToolD*Unit;
									d->Sides	=ToolS;
									d->DCode=dcode;
									DCodeList.AppendList(d);
									if((fp=strchr(fp,/**/'X'))!=NULL){
										fp++;
										LoadApertureHole(fp ,d->Hole);
									}
									MeanfulContent++;
								}
								else{
									md->Diameter	=ToolD*Unit;
									md->Sides		=ToolS;
								}
							}
						}
					}
					else{
						int		dcode;
						char	MacroStr[1000];
						char	*fp=CheckMacroInst(&Lp[4],dcode,MacroStr ,1000);
						if(fp!=NULL){
							GerberDCodeBase	*hd=DCodeList.FindDCode(dcode);
							GerberDCodeMacro	*md=dynamic_cast<GerberDCodeMacro *>(hd);
							if(hd==NULL || md==NULL){
								GerberApertureMacro	*Macro=DCodeList.FindMacro(MacroStr);
								if(Macro!=NULL){
									GerberDCodeMacro	*d=new GerberDCodeMacro(&DCodeList);
									d->DCode=dcode;
									d->Macro=Macro;
									while(*fp==' ' || *fp=='\t' || *fp=='\n' || *fp=='\r')
										fp++;
									if(*fp==','){
										MakeParam(fp,d->Param);
									}
									if(Macro->Primitives.Make(d->InstMacro , d->Param)==true){
										DCodeList.AppendList(d);
										MeanfulContent++;
									}
									else{
										delete	[]Buff;
										return false;
									}
								}
							}
						}	
					}
				}
				else if(strnicmp(&Lp[1],/**/"AM",2)==0){
					char	cbuff[100000];
					____strcpy(cbuff,&Lp[3],'*',sizeof(cbuff)-1);
					char	*gp=strchr(cbuff,/**/'*');
					if(gp!=NULL){
						*gp=0;
						QString	MacroName	=cbuff;
						GerberApertureMacro	*M=new GerberApertureMacro();
						M->MacroName	=MacroName;
						char	*ParamBuff=new char[1000000];
						char	*fp=strchr(&Lp[3],/**/'*');
						if(fp!=NULL){
							fp++;
							strcpy(ParamBuff,fp);
						}
						else{
							ParamBuff[0]=0;
						}
						while(strchr(ParamBuff,/**/'%')==NULL){
							if(fgets(Buff,MaxBuffSize-1,file)==NULL)
								break;
							LineNumber++;
							strcat(ParamBuff,Buff);
						}
						if(M->LoadFromGerber(ParamBuff,Unit)==true){
							DCodeList.Macros.AppendList(M);
							delete	[]ParamBuff;
							MeanfulContent++;
						}
						else{
							delete	[]ParamBuff;
							delete	M;
							delete	[]Buff;
							return false;
						}
					}
				}
			}
			else{
				//Format	Gn Xm.n Ym.n Im.n Jm.n Dn Mn *
					
				int	G;
				double	X,Y,I,J;
				int		D;
				int		M;

				if(GetLine(Lp,G,X,Y,I,J,D,M)==false){
					delete	[]Buff;
					return false;
				}

				NextP=strchr(&Lp[1],'*');
				if(NextP!=NULL){
					NextP++;
				}
				/*
				for(int t=1;Lp[t]!=0;t++){
					if(Lp[t]=='*'){
						if(Lp[t+1]=='%'){
							NextP=&Lp[t+2];
						}
						else{
							NextP=&Lp[t+1];
						}
						break;
					}
				}
				*/

				if(fabs(X-DbgX)<0.001 && fabs(Y-DbgY)<0.001)
					DbgD++;

				if(G==0){
					CurrentGCode=G;
				}
				if(G==4){
					Lp=NextP;
					continue;
				}
				else if(G==1 || G==10 || G==11 ||G==12 || (G==-1 && D==1 && M!=2) || (G==-1 && D==2 && M!=2) || (G==-1 && D==3 && M!=2)){
					if(D==1){
						Shutter=true;
						if(PolygonMode==false){
							if((AbsMode==true  && (fabs(CurrentX-X)>0.0000001 || fabs(CurrentY-Y)>0.0000001))
							|| (AbsMode==false && (fabs(X)>0.0000001 || fabs(Y)>0.0000001))){
								GerberDCodeBase	*DCode=DCodeList.FindDCode(CurrentDCode);
								if(DCode==NULL){
									delete	[]Buff;
									return false;
								}
								for(int Xn=0;Xn<RepeatCountX;Xn++){
									for(int Yn=0;Yn<RepeatCountY;Yn++){
										if(TestMode==false){
											GerberFastItemLine	*Item=new GerberFastItemLine();
											Item->SetDCode(DCode);
											Item->SetFileLayer(this);
											Item->PosiImage	=Polarity;
											Item->PosX1	=CurrentX+RepeatDistanceX*Xn;
											Item->PosY1	=CurrentY+RepeatDistanceY*Yn;
											Item->OrgPosX1	=CurrentX+RepeatDistanceX*Xn;
											Item->OrgPosY1	=CurrentY+RepeatDistanceY*Yn;
											if(AbsMode==true){
												Item->PosX2	=X+RepeatDistanceX*Xn;
												Item->PosY2	=Y+RepeatDistanceY*Yn;
												Item->OrgPosX2	=X+RepeatDistanceX*Xn;
												Item->OrgPosY2	=Y+RepeatDistanceY*Yn;
											}
											else{
												Item->PosX2	=CurrentX+X+RepeatDistanceX*Xn;
												Item->PosY2	=CurrentY+Y+RepeatDistanceY*Yn;
												Item->OrgPosX2	=CurrentX+X+RepeatDistanceX*Xn;
												Item->OrgPosY2	=CurrentY+Y+RepeatDistanceY*Yn;
											}
											if(Parent!=NULL && Parent->GetParent()!=NULL){
												Parent->GetParent()->AppendItem(Item);
												if(Item->GetID()==DbgID){
													DCodeDebug++;
												}
											}
										}
										MeanfulContent++;
									}
								}
							}
							else{
								GerberDCodeBase	*DCode=DCodeList.FindDCode(CurrentDCode);
								if(DCode==NULL){
									delete	[]Buff;
									return false;
								}
								for(int Xn=0;Xn<RepeatCountX;Xn++){
									for(int Yn=0;Yn<RepeatCountY;Yn++){
										if(TestMode==false){
											GerberFastItemFlash	*Item=new GerberFastItemFlash();
											Item->SetDCode(DCode);
											Item->SetFileLayer(this);
											Item->PosiImage	=Polarity;
											if(AbsMode==true){
												Item->PosX	=X+RepeatDistanceX*Xn;
												Item->PosY	=Y+RepeatDistanceY*Yn;
												Item->OrgPosX	=X+RepeatDistanceX*Xn;
												Item->OrgPosY	=Y+RepeatDistanceY*Yn;
												if(fabs(X-DbgX)<0.001 && fabs(Y-DbgY)<0.001)
													DbgD++;
												}
											else{
												Item->PosX		=CurrentX+X+RepeatDistanceX*Xn;
												Item->PosY		=CurrentY+Y+RepeatDistanceY*Yn;
												Item->OrgPosX	=CurrentX+X+RepeatDistanceX*Xn;
												Item->OrgPosY	=CurrentY+Y+RepeatDistanceY*Yn;
											}
											if(Parent!=NULL && Parent->GetParent()!=NULL){
												Parent->GetParent()->AppendItem(Item);
												if(Item->GetID()==DbgID){
													DCodeDebug++;
												}
											}
										}
										MeanfulContent++;
									}
								}
							}	
						}
						else{
							if((AbsMode==true  && (fabs(CurrentX-X)>0.0000001 || fabs(CurrentY-Y)>0.0000001))
							|| (AbsMode==false && (fabs(X)>0.0000001 || fabs(Y)>0.0000001))
							|| PolygonPoints.GetFirst()==NULL){
								if(AbsMode==true){
									if(TestMode==false){
										DoubleForPolygonList	*c=new DoubleForPolygonList(X,Y,CurrentX,CurrentY);
										PolygonPoints.AppendList(c);
									}
									MeanfulContent++;
								}
								else{
									if(TestMode==false){
										DoubleForPolygonList	*c=new DoubleForPolygonList(CurrentX+X,CurrentY+Y,CurrentX,CurrentY);
										PolygonPoints.AppendList(c);
									}
									MeanfulContent++;
								}
							}
						}
						if(AbsMode==true){
							CurrentX=X;
							CurrentY=Y;
						}
						else{
							CurrentX+=X;
							CurrentY+=Y;
						}
					}
					else if(D==2){
						Shutter=false;
						if(AbsMode==true){
							CurrentX=X;
							CurrentY=Y;
						}
						else{
							CurrentX+=X;
							CurrentY+=Y;
						}
					}
					else if(D==3){
						GerberDCodeBase	*DCode=DCodeList.FindDCode(CurrentDCode);
						if(DCode==NULL){
							delete	[]Buff;
							return false;
						}
						for(int Xn=0;Xn<RepeatCountX;Xn++){
							for(int Yn=0;Yn<RepeatCountY;Yn++){
								if(TestMode==false){
									GerberFastItemFlash	*Item=new GerberFastItemFlash();
									Item->SetDCode(DCode);
									Item->SetFileLayer(this);
									Item->PosiImage	=Polarity;

									if(AbsMode==true){
										Item->PosX	=X+RepeatDistanceX*Xn;
										Item->PosY	=Y+RepeatDistanceY*Yn;
										Item->OrgPosX	=X+RepeatDistanceX*Xn;
										Item->OrgPosY	=Y+RepeatDistanceY*Yn;
										if(fabs(X-DbgX)<0.001 && fabs(Y-DbgY)<0.001)
											DbgD++;
									}
									else{
										Item->PosX	=CurrentX+X+RepeatDistanceX*Xn;
										Item->PosY	=CurrentY+Y+RepeatDistanceY*Yn;
										Item->OrgPosX	=CurrentX+X+RepeatDistanceX*Xn;
										Item->OrgPosY	=CurrentY+Y+RepeatDistanceY*Yn;
									}
									if(Parent!=NULL && Parent->GetParent()!=NULL){
										Parent->GetParent()->AppendItem(Item);
										if(Item->GetID()==DbgID){
											DCodeDebug++;
										}
									}
								}
								MeanfulContent++;
							}
						}

						Shutter=false;
						if(AbsMode==true){
							CurrentX=X;
							CurrentY=Y;
						}
						else{
							CurrentX+=X;
							CurrentY+=Y;
						}
					}
					else if(D==-1){
						Shutter=false;
						if(AbsMode==true){
							CurrentX=X;
							CurrentY=Y;
						}
						else{
							CurrentX+=X;
							CurrentY+=Y;
						}
					}
					else if(D>=10){
						CurrentDCode=D;
					}
					CurrentGCode=G;
				}
				else if(G==2){
					if(PolygonMode==false){
						if(D==1){
							GerberDCodeBase	*DCode=DCodeList.FindDCode(CurrentDCode);
							if(DCode==NULL){
								delete	[]Buff;
								return false;
							}
							for(int Xn=0;Xn<RepeatCountX;Xn++){
								for(int Yn=0;Yn<RepeatCountY;Yn++){
									if(TestMode==false){
										GerberFastItemArc	*Item=new GerberFastItemArc();
										Item->SetDCode(DCode);
										Item->SetFileLayer(this);
										Item->PosiImage	=Polarity;

										if(fabs(Item->OrgCenterX-DbgX)<0.001 && fabs(Item->OrgCenterY-DbgY)<0.001)
											DbgD++;
											
										Item->Radius	=hypot(I,J);
										Item->OrgRadius	=Item->Radius;
										double	EndX,EndY;
										if(AbsMode==true){
											EndX=X;
											EndY=Y;
										}
										else{
											EndX=CurrentX+X;
											EndY=CurrentY+Y;
										}
										if(Interporate360==false){
											double	CenterX1	=CurrentX+I;
											double	CenterY1	=CurrentY+J;
											double	s1=fabs(hypot(CurrentX-CenterX1,CurrentY-CenterY1)
														   -hypot(EndX-CenterX1,EndY-CenterY1));
												
											double	CenterX2	=CurrentX-I;
											double	CenterY2	=CurrentY+J;
											double s2=fabs(hypot(CurrentX-CenterX2,CurrentY-CenterY2)
														  -hypot(EndX-CenterX2,EndY-CenterY2));

											double	CenterX3	=CurrentX+I;
											double	CenterY3	=CurrentY-J;
											double s3=fabs(hypot(CurrentX-CenterX3,CurrentY-CenterY3)
														  -hypot(EndX-CenterX3,EndY-CenterY3));

											double	CenterX4	=CurrentX-I;
											double	CenterY4	=CurrentY-J;
											double s4=fabs(hypot(CurrentX-CenterX4,CurrentY-CenterY4)
														  -hypot(EndX-CenterX4,EndY-CenterY4));
											if(s1<=s2 && s1<=s3 && s1<=s4){
												Item->CenterX	=CurrentX+I;
												Item->CenterY	=CurrentY+J;
												Item->OrgCenterX=CurrentX+I;
												Item->OrgCenterY=CurrentY+J;
												}
											else if(s2<=s1 && s2<=s3 && s2<=s4){
												Item->CenterX	=CurrentX-I;
												Item->CenterY	=CurrentY+J;
												Item->OrgCenterX=CurrentX-I;
												Item->OrgCenterY=CurrentY+J;
											}
											else if(s3<=s1 && s3<=s2 && s3<=s4){
												Item->CenterX	=CurrentX+I;
												Item->CenterY	=CurrentY-J;
												Item->OrgCenterX=CurrentX+I;
												Item->OrgCenterY=CurrentY-J;
											}
											else{
												Item->CenterX	=CurrentX-I;
												Item->CenterY	=CurrentY-J;
												Item->OrgCenterX=CurrentX-I;
												Item->OrgCenterY=CurrentY-J;
											}
										}
										else{
											Item->CenterX	=CurrentX+I;
											Item->CenterY	=CurrentY+J;
											Item->OrgCenterX=CurrentX+I;
											Item->OrgCenterY=CurrentY+J;
										}

										Item->EndAngle=GetSita(CurrentX-Item->CenterX ,CurrentY-Item->CenterY);
										Item->StartAngle	=GetSita(EndX-Item->CenterX ,EndY-Item->CenterY);

										Item->OrgStartAngle	=Item->StartAngle;
										Item->OrgEndAngle	=Item->EndAngle;

										Item->CenterX+=RepeatDistanceX*Xn;
										Item->CenterY+=RepeatDistanceY*Yn;
										Item->OrgCenterX+=RepeatDistanceX*Xn;
										Item->OrgCenterY+=RepeatDistanceY*Yn;
										if(Parent!=NULL && Parent->GetParent()!=NULL){
											Parent->GetParent()->AppendItem(Item);
											if(Item->GetID()==DbgID){
												DCodeDebug++;
											}
										}
									}
									MeanfulContent++;
								}
							}

							//Shutter=false;
							if(AbsMode==true){
								CurrentX=X;
								CurrentY=Y;
							}
							else{
								CurrentX+=X;
								CurrentY+=Y;
							}
						}
						else if(D>=10){
							CurrentDCode=D;
						}
					}
					else{
						if(D==1){
							if(AbsMode==true){
								if(TestMode==false){
									double	CenterX=CurrentX+I;
									double	CenterY=CurrentY+J;
									DoubleForPolygonList	*c=new DoubleForPolygonList(CenterX,CenterY
																						,GetSita(X-CenterX ,Y-CenterY)
																						,GetSita(CurrentX-CenterX ,CurrentY-CenterY)
																						,1
																						,X,Y
																						,CurrentX,CurrentY
																						,true);
									PolygonPoints.AppendList(c);
								}
								MeanfulContent++;
							}
							else{
								if(TestMode==false){
									double	CenterX=CurrentX+I;
									double	CenterY=CurrentY+J;
									DoubleForPolygonList	*c=new DoubleForPolygonList(CenterX,CenterY
																						,GetSita(CurrentX+X-CenterX ,CurrentX+Y-CenterY)
																						,GetSita(CurrentX-CenterX ,CurrentY-CenterY)
																						,1
																						,CurrentX+X,CurrentY+Y
																						,CurrentX,CurrentY
																						,true);
									PolygonPoints.AppendList(c);
								}
								MeanfulContent++;
							}
							if(AbsMode==true){
								CurrentX=X;
								CurrentY=Y;
							}
							else{
								CurrentX+=X;
								CurrentY+=Y;
							}
						}
						else if(D>=10){
							CurrentDCode=D;
						}
					}
					CurrentGCode=-1;
				}
				else if(G==3){
					if(PolygonMode==false){
						if(D==1){
							GerberDCodeBase	*DCode=DCodeList.FindDCode(CurrentDCode);
							if(DCode==NULL){
								delete	[]Buff;
								return false;
							}
							for(int Xn=0;Xn<RepeatCountX;Xn++){
								for(int Yn=0;Yn<RepeatCountY;Yn++){
									if(TestMode==false){
										GerberFastItemArc	*Item=new GerberFastItemArc();
										Item->SetDCode(DCode);
										Item->SetFileLayer(this);
										Item->PosiImage	=Polarity;
							
										Item->Radius	=hypot(I,J);
										Item->OrgRadius	=Item->Radius;
										double	EndX,EndY;
										if(AbsMode==true){
											EndX=X;
											EndY=Y;
										}
										else{
											EndX=CurrentX+X;
											EndY=CurrentY+Y;
										}
										if(Interporate360==false){
											double	CenterX1	=CurrentX+I;
											double	CenterY1	=CurrentY+J;
											double	s1=fabs(hypot(CurrentX-CenterX1,CurrentY-CenterY1)
														   -hypot(EndX-CenterX1,EndY-CenterY1));
											
											double	CenterX2	=CurrentX-I;
											double	CenterY2	=CurrentY+J;
											double s2=fabs(hypot(CurrentX-CenterX2,CurrentY-CenterY2)
														  -hypot(EndX-CenterX2,EndY-CenterY2));

											double	CenterX3	=CurrentX+I;
											double	CenterY3	=CurrentY-J;
											double s3=fabs(hypot(CurrentX-CenterX3,CurrentY-CenterY3)
														  -hypot(EndX-CenterX3,EndY-CenterY3));
												
											double	CenterX4	=CurrentX-I;
											double	CenterY4	=CurrentY-J;
											double s4=fabs(hypot(CurrentX-CenterX4,CurrentY-CenterY4)
														  -hypot(EndX-CenterX4,EndY-CenterY4));
											if(s1<=s2 && s1<=s3 && s1<=s4){
												Item->CenterX	=CurrentX+I;
												Item->CenterY	=CurrentY+J;
												Item->OrgCenterX=CurrentX+I;
												Item->OrgCenterY=CurrentY+J;
											}
											else if(s2<=s1 && s2<=s3 && s2<=s4){
												Item->CenterX	=CurrentX-I;
												Item->CenterY	=CurrentY+J;
												Item->OrgCenterX=CurrentX-I;
												Item->OrgCenterY=CurrentY+J;
											}
											else if(s3<=s1 && s3<=s2 && s3<=s4){
												Item->CenterX	=CurrentX+I;
												Item->CenterY	=CurrentY-J;
												Item->OrgCenterX=CurrentX+I;
												Item->OrgCenterY=CurrentY-J;
											}
											else{
												Item->CenterX	=CurrentX-I;
												Item->CenterY	=CurrentY-J;
												Item->OrgCenterX=CurrentX-I;
												Item->OrgCenterY=CurrentY-J;
											}
										}
										else{
											Item->CenterX	=CurrentX+I;
											Item->CenterY	=CurrentY+J;
											Item->OrgCenterX=CurrentX+I;
											Item->OrgCenterY=CurrentY+J;
										}

										Item->StartAngle=GetSita(CurrentX-Item->CenterX ,CurrentY-Item->CenterY);
										if(fabs(Item->OrgCenterX-DbgX)<0.001 && fabs(Item->OrgCenterY-DbgY)<0.001)
											DbgD++;
										Item->EndAngle	=GetSita(EndX-Item->CenterX ,EndY-Item->CenterY);
										
										Item->OrgStartAngle	=Item->StartAngle;
										Item->OrgEndAngle	=Item->EndAngle;
										//if(fabs(Item->StartAngle - Item->EndAngle)<0.00001){
										//	DbgD++;
										//}
										
										Item->CenterX+=RepeatDistanceX*Xn;
										Item->CenterY+=RepeatDistanceY*Yn;
										Item->OrgCenterX+=RepeatDistanceX*Xn;
										Item->OrgCenterY+=RepeatDistanceY*Yn;
										if(Parent!=NULL && Parent->GetParent()!=NULL){
											Parent->GetParent()->AppendItem(Item);
											if(Item->GetID()==DbgID){
												DCodeDebug++;
											}
										}
									}
									MeanfulContent++;
								}
							}
							//Shutter=false;
							if(AbsMode==true){
								CurrentX=X;
								CurrentY=Y;
							}
							else{
								CurrentX+=X;
								CurrentY+=Y;
							}
						}
						else if(D>=10){
							CurrentDCode=D;
						}
					}
					else{
						if(D==1){
							if(AbsMode==true){
								if(TestMode==false){
									double	CenterX=CurrentX+I;
									double	CenterY=CurrentY+J;
									DoubleForPolygonList	*c=new DoubleForPolygonList(CenterX,CenterY
																						,GetSita(CurrentX-CenterX ,CurrentY-CenterY)
																						,GetSita(X-CenterX ,Y-CenterY)
																						,1
																						,X,Y
																						,CurrentX,CurrentY
																						,false);
									PolygonPoints.AppendList(c);
								}
								MeanfulContent++;
							}
							else{
								if(TestMode==false){
									double	CenterX=CurrentX+I;
									double	CenterY=CurrentY+J;
									DoubleForPolygonList	*c=new DoubleForPolygonList(CenterX,CenterY
																						,GetSita(CurrentX-CenterX ,CurrentY-CenterY)
																						,GetSita(CurrentX+X-CenterX ,CurrentX+Y-CenterY)
																						,1
																						,CurrentX+X,CurrentY+Y
																						,CurrentX,CurrentY
																						,false);
									PolygonPoints.AppendList(c);
								}
								MeanfulContent++;
							}
							if(AbsMode==true){
								CurrentX=X;
								CurrentY=Y;
							}
							else{
								CurrentX+=X;
								CurrentY+=Y;
							}
						}
						else if(D>=10){
							CurrentDCode=D;
						}
					}
					CurrentGCode=-1;
				}
				else if(G==4){
					CurrentGCode=G;
				}
				else if(G==36){
					PolygonPoints.RemoveAll();
					PolygonMode=true;
					CurrentGCode=-1;
				}
				else if(G==37){
					int	N=PolygonPoints.GetNumber();
					//if(N>3){
						for(int Xn=0;Xn<RepeatCountX;Xn++){
							for(int Yn=0;Yn<RepeatCountY;Yn++){
								if(TestMode==false){
									GerberFastItemPolygon	*Item=new GerberFastItemPolygon();
									Item->SetFileLayer(this);
									Item->PosiImage	=Polarity;
									Item->OrgPoints=new GerberFastItemPolygon::PointStruct[N];
									for(int i=0;i<N;i++){
										Item->OrgPoints[i].Initial();
									}
									int	n=0;
									for(DoubleForPolygonList *d=PolygonPoints.GetFirst();d!=NULL;d=d->GetNext()){
										Item->OrgPoints[n]	=*d;
										if(d->Mode==0){
											Item->OrgPoints[n].Data.PosX =d->X+RepeatDistanceX*Xn;
											Item->OrgPoints[n].Data.PosY =d->Y+RepeatDistanceY*Yn;
											Item->OrgPoints[n].Data.LastX=d->LastX+RepeatDistanceX*Xn;
											Item->OrgPoints[n].Data.LastY=d->LastY+RepeatDistanceY*Yn;
											Item->OrgPoints[n].Data.PointType=GerberFastItemPolygon::PointStruct::_Line;
											n++;
										}
										else if(d->Mode==1){
											if(d->X!=d->LastX || d->Y!=d->LastY || PolygonPoints.GetCount()<3){
												Item->OrgPoints[n].Data.PosX		=d->X+RepeatDistanceX*Xn;
												Item->OrgPoints[n].Data.PosY		=d->Y+RepeatDistanceY*Yn;
												Item->OrgPoints[n].Data.CenterX		=d->CenterX+RepeatDistanceX*Xn;
												Item->OrgPoints[n].Data.CenterY		=d->CenterY+RepeatDistanceY*Yn;
												Item->OrgPoints[n].Data.LastX		=d->LastX+RepeatDistanceX*Xn;
												Item->OrgPoints[n].Data.LastY		=d->LastY+RepeatDistanceY*Yn;
												Item->OrgPoints[n].Data.PointType	=GerberFastItemPolygon::PointStruct::_Arc;
												Item->OrgPoints[n].MakeRadius(Item->OrgPoints[n].Data.PosX	 ,Item->OrgPoints[n].Data.PosY
																			, Item->OrgPoints[n].Data.LastX	 ,Item->OrgPoints[n].Data.LastY 
																			, Item->OrgPoints[n].Data.CenterX,Item->OrgPoints[n].Data.CenterY
																			, Item->OrgPoints[n].Data.RadiusX,Item->OrgPoints[n].Data.RadiusY);
												if(d->ClockWise==true){
													Item->OrgPoints[n].Data.EndAngle	=GetSita((Item->OrgPoints[n].Data.PosX -Item->OrgPoints[n].Data.CenterX)/Item->OrgPoints[n].Data.RadiusX
																								,(Item->OrgPoints[n].Data.PosY -Item->OrgPoints[n].Data.CenterY)/Item->OrgPoints[n].Data.RadiusY);
													Item->OrgPoints[n].Data.StartAngle	=GetSita((Item->OrgPoints[n].Data.LastX -Item->OrgPoints[n].Data.CenterX)/Item->OrgPoints[n].Data.RadiusX
																								,(Item->OrgPoints[n].Data.LastY -Item->OrgPoints[n].Data.CenterY)/Item->OrgPoints[n].Data.RadiusY);
													Item->OrgPoints[n].Data.ReverseStartEnd	=false;
												}
												else{
													Item->OrgPoints[n].Data.StartAngle	=GetSita((Item->OrgPoints[n].Data.PosX -Item->OrgPoints[n].Data.CenterX)/Item->OrgPoints[n].Data.RadiusX
																								,(Item->OrgPoints[n].Data.PosY -Item->OrgPoints[n].Data.CenterY)/Item->OrgPoints[n].Data.RadiusY);
													Item->OrgPoints[n].Data.EndAngle	=GetSita((Item->OrgPoints[n].Data.LastX -Item->OrgPoints[n].Data.CenterX)/Item->OrgPoints[n].Data.RadiusX
																								,(Item->OrgPoints[n].Data.LastY -Item->OrgPoints[n].Data.CenterY)/Item->OrgPoints[n].Data.RadiusY);
													Item->OrgPoints[n].Data.ReverseStartEnd	=true;
												}
												n++;
											}
										}
									}
									Item->OrgPosCount=n;
									Item->InitialFromOrg();
									if(Parent!=NULL && Parent->GetParent()!=NULL){
										Parent->GetParent()->AppendItem(Item);
										if(Item->GetID()==DbgID){
											DCodeDebug++;
										}
									}
								}
								MeanfulContent++;
							}
						}
					//}
					PolygonPoints.RemoveAll();
					PolygonMode=false;
					CurrentGCode=-1;
				}
				else if(G==54){
					CurrentDCode=D;
					CurrentGCode=-1;
				}
				else if(G==70){
					Unit=25.4;
					CurrentGCode=-1;
				}
				else if(G==71){
					Unit=1.0;
					CurrentGCode=-1;
				}
				else if(G==74){
					Interporate360=false;
					CurrentGCode=-1;
				}
				else if(G==75){
					Interporate360=true;
					CurrentGCode=-1;
				}
				else if(G==90){
					AbsMode=true;
					CurrentGCode=-1;
				}
				else if(G==91){
					AbsMode=false;
					CurrentGCode=-1;
				}
				else if(G==-1){
					if(D>=10){
						CurrentDCode=D;
					}
					else if(D==1){
					}
					else if(D==2){
						CurrentX=X;
						CurrentY=Y;
					}
				}
				if(M==0 || M==1 || M==2 || M==30){
					if(MeanfulContent>3){
						delete	[]Buff;
						return true;
					}
					delete	[]Buff;
					return false;
				}
				else if(Lp[0]=='*' || Lp[0]=='\n'){
					//continue;
				}
				else{
					LastSelectedD=D;
				}
			}
			if(NextP!=NULL){
				if(*NextP==0 || (NextP[0]==0x0a && NextP[1]==0)){
					break;
				}
				Lp=NextP;
				//goto	LoopPoint;
			}
			else if(NextP==NULL){
				break;
			}
		}
	}
	if(LineNumber==0){
		delete	[]Buff;
		return false;
	}
	if(MeanfulContent<3){
		delete	[]Buff;
		return false;
	}
	delete	[]Buff;
	return true;
}

static	char	*GetNum(char *fp ,int &n)
{
	int	digit=0;
	n=0;
	int	Sign=1;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}

	while('0'<=*fp && *fp<='9'){
		int	k=*fp-'0';
		n*=10;
		n+=k;
		fp++;
		digit++;
	}
	if(digit==0)
		return NULL;
	n=n*Sign;
	return fp;
}

static	char	*GetNumTrailingZero(char *fp ,int &n ,int Num ,int PNum)
{
	int	digit=0;
	n=0;
	int	Sign=1;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}
	while('0'<=*fp && *fp<='9'){
		int	k=*fp-'0';
		n*=10;
		n+=k;
		fp++;
		digit++;
	}
	for(int i=digit;i<(Num+PNum);i++){
		n*=10;
	}
	if(digit==0)
		return NULL;
	n=n*Sign;
	return fp;
}

static	char	*GetNumInclude0(char *fp ,int &n)
{
	int	digit=0;
	n=0;
	int	Sign=1;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}

	while('0'<=*fp && *fp<='9'){
		int	k=*fp-'0';
		n*=10;
		n+=k;
		fp++;
		digit++;
	}

	n=n*Sign;
	return fp;
}

static	char	*GetNumTrailingZeroInclude0(char *fp ,int &n ,int Num ,int PNum)
{
	int	digit=0;
	n=0;
	int	Sign=1;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}
	while('0'<=*fp && *fp<='9'){
		int	k=*fp-'0';
		n*=10;
		n+=k;
		fp++;
		digit++;
	}
	for(int i=digit;i<(Num+PNum);i++){
		n*=10;
	}

	n=n*Sign;
	return fp;
}

bool	GerberFileLayer::GetLine(char *Buff,int &G,double &X,double &Y,double &I,double &J,int &D,int &M)
{
	char	*fp=Buff;
	while(*fp==' ' || *fp=='\t')	fp++;

	G=CurrentGCode;
	if(AbsMode==true){
		X=CurrentX;
		Y=CurrentY;
	}
	else{
		X=0.0;
		Y=0.0;
	}
	D=LastSelectedD;
	if(Shutter==false)
		D=-1;
	I=0;
	J=0;
	M=-1;

	if(*fp=='G'){
		int	N;
		fp=GetNum(fp+1,N);
		if(fp==NULL){
			return false;
		}
		G=N;
	}
	if(*fp=='X'){
		int	N;
		if(TrailingZero==false){
			fp=GetNumInclude0(fp+1,N);
		}
		else{
			fp=GetNumTrailingZeroInclude0(fp+1 ,N ,XNum ,XPNum);
		}
		if(fp==NULL){
			return false;
		}
		X=N*XMultiply*Unit;	
	}
	if(*fp=='Y'){
		int	N;
		if(TrailingZero==false){
			fp=GetNumInclude0(fp+1,N);
		}
		else{
			fp=GetNumTrailingZeroInclude0(fp+1 ,N ,YNum ,YPNum);
		}
		if(fp==NULL){
			return false;
		}
		Y=N*YMultiply*Unit;	
	}
	if(*fp=='I'){
		int	N;
		if(TrailingZero==false){
			fp=GetNumInclude0(fp+1,N);
		}
		else{
			fp=GetNumTrailingZeroInclude0(fp+1 ,N ,XNum ,XPNum);
		}
		if(fp==NULL){
			return false;
		}
		I=N*XMultiply*Unit;	
		if(G==-1){
			G=LastGCode;
		}
	}
	if(*fp=='J'){
		int	N;
		if(TrailingZero==false){
			fp=GetNumInclude0(fp+1,N);
		}
		else{
			fp=GetNumTrailingZeroInclude0(fp+1 ,N ,YNum ,YPNum);
		}
		if(fp==NULL){
			return false;
		}
		J=N*YMultiply*Unit;	
		if(G==-1){
			G=LastGCode;
		}
	}
	if(*fp=='D'){
		int	N;
		fp=GetNum(fp+1,N);
		if(fp==NULL){
			return false;
		}
		D=N;
		if(D==1)
			Shutter=true;
		else if(D==2)
			Shutter=false;
	}
	if(*fp=='M'){
		int	N;
		fp=GetNum(fp+1,N);
		if(fp==NULL){
			return false;
		}
		M=N;
	}

	LastGCode=G;
		
	return true;
}

void	GerberFileLayer::ReqApertureList(struct	ApertureInfo *Dim ,int DimCount)
{
	for(int i=0;i<DimCount;i++){
		GerberDCodeBase	*d=FindDCode(Dim[i].ApertureNumber);
		if(d!=NULL){
			d->MakeApertureInfo(Dim[i]);
		}
	}
}

void	GerberFileLayer::SetApertureList(struct	ApertureInfo *Dim ,int DimCount)
{
	for(int i=0;i<DimCount;i++){
		GerberDCodeBase	*d=FindDCode(Dim[i].ApertureNumber);
		if(d!=NULL){
			d->SetApertureInfo(Dim[i]);
		}
	}
}



GerberFileLayerContainer::GerberFileLayerContainer(GerberFastInPage *parent)
{
	Parent=parent;
}
int		GerberFileLayerContainer::GetMaxFileLayerID(void)
{
	int	MaxID=0;
	for(GerberFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FileLayerID>MaxID){
			MaxID=a->FileLayerID;
		}
	}
	return MaxID;
}
GerberFileLayer	*GerberFileLayerContainer::Find(int ID)
{
	for(GerberFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FileLayerID==ID)
			return a;
	}
	return NULL;
}

GerberFileLayer	*GerberFileLayerContainer::FindByLibID(int LibID)
{
	for(GerberFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID)
			return a;
	}
	return NULL;
}
GerberFileLayerContainer	&GerberFileLayerContainer::operator=(const GerberFileLayerContainer &src)
{
	NPListPackSaveLoad<GerberFileLayer>::operator=(src);
	return *this;
}
GerberFastBase	*GerberFileLayer::GetGerberBase(void)
{
	AlgorithmBase	*B=Parent->GetParent()->GetParentBase();
	return (GerberFastBase *)B;
}
//----------------------------------------------------------------------------------------------------------
bool	GerberFileLayer::LoadNCData(GerberFastBase *GBase ,FILE *f,bool TestMode)
{
	int		MeanfulContent=0;
	const int	MaxBuffSize=1000000;
	char	*Buff=new char[MaxBuffSize];
	Buff[MaxBuffSize-1]=0;
	int	LineNumber;

	int		DCode;
	double	Diameter;
	int		XNum,YNum;
	bool	LoadedTCode=false;

	double	Mul=pow(0.1,GBase->NCSmallNum);
	double	Unit=(GBase->NCUnitInchi==true)?25.4:1;
	double	LastX=0;
	double	LastY=0;
	GerberDCodeBase	*DCodePoint=NULL;
	for(LineNumber=0;fgets(Buff,MaxBuffSize-1,f)!=NULL;LineNumber++){
		if(LineNumber==DbgLine){
			DbgD++;
		}
		if(TestMode==true && LineNumber>500){
			if(MeanfulContent<3){
				delete	[]Buff;
				return false;
			}
			delete	[]Buff;
			return true;
		}

		if(matchscanf(Buff,"T%dC%lf",&DCode,&Diameter)==2){
			if(TestMode==false){
				GerberDCodeCircle	*C=new GerberDCodeCircle(&DCodeList);
				C->HSize	=Diameter*Unit;
				C->WSize	=Diameter*Unit;
				C->DCode	=DCode;
				DCodeList.AppendList(C);
				DCodePoint=C;
			}
			LoadedTCode=true;
			MeanfulContent++;
		}
		else if(matchscanf(Buff,"X%dY%d",&XNum,&YNum)==2){
			if(DCodePoint!=NULL && TestMode==false){
				GerberFastItemFlash	*Item=new GerberFastItemFlash();
				Item->SetDCode(DCodePoint);
				Item->SetFileLayer(this);
				Item->PosiImage	=true;

				Item->PosX	=XNum*Mul*Unit;
				Item->PosY	=YNum*Mul*Unit;
				Item->OrgPosX	=Item->PosX;
				Item->OrgPosY	=Item->PosY;
				LastX			=Item->PosX;
				LastY			=Item->PosY;

				if(Parent!=NULL && Parent->GetParent()!=NULL){
					Parent->GetParent()->AppendItem(Item);
					if(Item->GetID()==DbgID){
						DCodeDebug++;
					}
				}
			}
			if(LoadedTCode==true){
				MeanfulContent++;
			}
		}
		else if(matchscanf(Buff,"X%d",&XNum)==1){
			if(DCodePoint!=NULL && TestMode==false){
				GerberFastItemFlash	*Item=new GerberFastItemFlash();
				Item->SetDCode(DCodePoint);
				Item->SetFileLayer(this);
				Item->PosiImage	=true;

				Item->PosX	=XNum*Mul*Unit;
				Item->PosY	=LastY;
				Item->OrgPosX	=Item->PosX;
				Item->OrgPosY	=Item->PosY;
				LastX			=Item->PosX;
				LastY			=Item->PosY;

				if(Parent!=NULL && Parent->GetParent()!=NULL){
					Parent->GetParent()->AppendItem(Item);
					if(Item->GetID()==DbgID){
						DCodeDebug++;
					}
				}
			}
			if(LoadedTCode==true){
				MeanfulContent++;
			}
		}
		else if(matchscanf(Buff,"Y%d",&YNum)==1){
			if(DCodePoint!=NULL && TestMode==false){
				GerberFastItemFlash	*Item=new GerberFastItemFlash();
				Item->SetDCode(DCodePoint);
				Item->SetFileLayer(this);
				Item->PosiImage	=true;

				Item->PosX	=LastX;
				Item->PosY	=YNum*Mul*Unit;
				Item->OrgPosX	=Item->PosX;
				Item->OrgPosY	=Item->PosY;
				LastX			=Item->PosX;
				LastY			=Item->PosY;

				if(Parent!=NULL && Parent->GetParent()!=NULL){
					Parent->GetParent()->AppendItem(Item);
					if(Item->GetID()==DbgID){
						DCodeDebug++;
					}
				}
			}
			if(LoadedTCode==true){
				MeanfulContent++;
			}
		}
		else if(matchscanf(Buff,"T%d",&DCode)==1){
			if(TestMode==false){
				DCodePoint	=DCodeList.FindDCode(DCode);
				if(DCodePoint==NULL){
					delete	[]Buff;
					return false;
				}
			}
			LoadedTCode=true;
			MeanfulContent++;
		}
		else if(strcmp(Buff,"M30")==0){
			break;
		}
	}
	if(MeanfulContent<3){
		delete	[]Buff;
		return false;
	}
	delete	[]Buff;
	return true;
}