#include "XDXFOperation.h"
#include "swap.h"
#include "XCrossObj.h"

static	int	DbgCode=0;

int	ScanInt(char *fp)
{
	if(*fp<'0' || '9'<*fp)
		return -1;
	int	RetN=0;
	while('0'<=*fp && *fp<='9'){
		int	n=*fp-'0';
		RetN=RetN*10+n;
		fp++;
	}
	return RetN;
}

double	ScanDouble(char *fp)
{
	double	d;
	sscanf(fp,/**/"%lf",&d);
	return d;
}

const int	MaxBuffSize=1000;


int	GetLines(FILE *f ,char text[],char &TopCode ,int &LineNumber)
{
	char	Buff[MaxBuffSize];
	if(fgets(Buff,MaxBuffSize-1,f)==NULL)
		return -1;

	char	*fp=Buff;
	TopCode=*fp;
	while(*fp==' ' || *fp=='\t'){
		fp++;
	}
	LineNumber++;
	int	Code=ScanInt(fp);

	if(fgets(Buff,MaxBuffSize-1,f)==NULL)
		return -2;
	char	*tp=Buff;
	while(*tp==' ' || *fp=='\t'){
		tp++;
	}
	LineNumber++;
	strcpy(text,tp);
	return Code;
}
	


bool	DXFOperationInPage::LoadDXF(FILE *f ,int &ErrorLine ,QStringList &SpecialGroupName,int FileNo)
{
	DXFLayerList.RemoveAll();

	char	Buff[MaxBuffSize];
	bool	Ret=false;
	int	LineNumber=0;
	char	TopCode;
	int	Code=GetLines(f ,Buff,TopCode,LineNumber);
	while(Code>=0){
		Code=LoadDXFParagram(f ,FileNo,Code ,Buff,LineNumber,SpecialGroupName);
	}
	
	if(Code==-1){
		return true;
	}
	ErrorLine=LineNumber;
	return false;
}


int	DXFOperationInPage::LoadDXFParagram(FILE *f ,int FileNo ,int Code ,char text[],int &LineNumber,QStringList &SpecialGroupName)
{
	char	Buff[MaxBuffSize];
	char	TopCode;
	int	Error=0;

	if(Code==0){
		if(strnicmp(text,/**/"SECTION",7)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}
				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"ENDSEC",6)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"CLASS",5)==0){
			SectionClasses	*Cls=new SectionClasses();
			SectionClassesData.AppendList(Cls);
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
				if(Code==1){
					Cls->RecordName	=Buff;
				}
				else
				if(Code==2){
					Cls->ClassName	=Buff;
				}
				else
				if(Code==3){
					Cls->ApplicationName	=Buff;
				}
				else
				if(Code==90){
					int	FlagCode=ScanInt(Buff);
					if((FlagCode&0x01)!=0)
						Cls->FunctionFlag.EnableDelete=true;
					if((FlagCode&0x02)!=0)
						Cls->FunctionFlag.EnableTransform=true;
					if((FlagCode&0x04)!=0)
						Cls->FunctionFlag.EnableChangeColor=true;
					if((FlagCode&0x08)!=0)
						Cls->FunctionFlag.EnableChangeLayer=true;
					if((FlagCode&0x10)!=0)
						Cls->FunctionFlag.EnableChangeLineType=true;
					if((FlagCode&0x20)!=0)
						Cls->FunctionFlag.EnableChangeScale=true;
					if((FlagCode&0x40)!=0)
						Cls->FunctionFlag.EnableShow=true;
					if((FlagCode&0x80)!=0)
						Cls->FunctionFlag.EnableClone=true;
					if((FlagCode&0x100)!=0)
						Cls->FunctionFlag.EnableChangeLineWidth=true;
					if((FlagCode&0x200)!=0)
						Cls->FunctionFlag.EnableChangePrintStyle=true;
					if((FlagCode&0x400)!=0)
						Cls->FunctionFlag.IneffectiveWarningDialog=true;
					if((FlagCode&0x8000)!=0)
						Cls->FunctionFlag.R13J=true;
				
				}
				else
				if(Code==91){
					Cls->CountInstance=ScanInt(Buff);
				}
				else
				if(Code==281){
				}
				else
				if(Code==282){
				}
			}
		}
		else
		if(strnicmp(text,/**/"TABLE",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
				if(Code==2){
					DXFLayer	*L=new DXFLayer(&DXFLayerList);
					L->LayerName	=QString(Buff).trimmed();
					L->LayerID=DXFLayerList.GetMaxFileLayerID()+1;
					DXFLayerList.AppendList(L);
				}
			}
		}
		else
		if(strnicmp(text,/**/"VPORT",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LTYPE",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"STYLE",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"APPID",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"BLOCK_RECORD",12)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"DIMSTYLE",8)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"VIEW",4)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"BLOCK",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"ENDBLK",6)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LAYER",5)==0){
			DXFLayer	*L=new DXFLayer(&DXFLayerList);
			L->LayerID=DXFLayerList.GetMaxFileLayerID()+1;
			DXFLayerList.AppendList(L);
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
				if(Code==2){
					L->LayerName	=QString(Buff).trimmed();
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						L->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						L->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						L->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						L->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					L->ColorCode=ScanInt(Buff);
				}
			}
		}
		else
		if(strnicmp(text,/**/"ENDTAB",6)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"EOF",3)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LINE",4)==0){
			DXFOperationItemLine	*Item=new DXFOperationItemLine();
			Item->FileNo=FileNo;
			Item->SetSelected(true);
			AppendItem(Item);
			bool	Deletable=false;
			double	ExtrusionX[3];
			double	ExtrusionY[3];
			double	ExtrusionZ[3];
			ExtrusionX[0]=0;
			ExtrusionX[1]=0;
			ExtrusionX[2]=0;
			ExtrusionY[0]=0;
			ExtrusionY[1]=0;
			ExtrusionY[2]=0;
			ExtrusionZ[0]=0;
			ExtrusionZ[1]=0;
			ExtrusionZ[2]=0;

			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					if(Deletable==true){
						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

						RemoveItem(Item);
						delete	Item;

						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}


					}
					if(ExtrusionZ[0]<0){
						Item->PosX1=ExtrusionZ[0]*Item->PosX1;
						Item->PosX2=ExtrusionZ[0]*Item->PosX2;
					}
					return Code;
				}

				if(TopCode==' ' && Code==0){
					if(Deletable==true){
						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}
						RemoveItem(Item);
						delete	Item;

						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}


					}
					if(ExtrusionZ[0]<0){
						Item->PosX1=ExtrusionZ[0]*Item->PosX1;
						Item->PosX2=ExtrusionZ[0]*Item->PosX2;
					}
					strcpy(text,Buff);
					return Code;
				}
				else
				if(Code==8){
					DXFLayer	*L=DXFLayerList.FindLayer(QString(Buff).trimmed());
					if(L!=NULL){
						Item->SetDXFLayer(L);
						if(Item->ColorCode==0){
							Item->ColorCode=L->ColorCode;
						}
					}
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						Item->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						Item->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						Item->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						Item->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					Item->ColorCode=ScanInt(Buff);
					//if(Item->ColorCode<=0){
					if(Item->ColorCode<0){
						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}
						//if(Deletable==false){
							RemoveItem(Item);
							Deletable=true;
						//}

						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

					}
				}
				else
				if(Code==10){
					Item->OrgPosX1=Item->PosX1=ScanDouble(Buff);
				}
				else
				if(Code==20){
					Item->OrgPosY1=Item->PosY1=ScanDouble(Buff);

					if(Item->OrgPosX1==0.0 && Item->OrgPosY1==0.0){
						DbgCode=1;
					}
				}
				else
				if(Code==11){
					Item->OrgPosX2=Item->PosX2=ScanDouble(Buff);
				}
				else
				if(Code==21){
					Item->OrgPosY2=Item->PosY2=ScanDouble(Buff);
				}
				else
				if(Code==230){
					ExtrusionZ[0]=ScanDouble(Buff);
				}
				else
				if(Code==370){
					Item->Width=ScanDouble(Buff);
					if(Item->Width<0){
						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

						//if(Deletable==false){
							RemoveItem(Item);
							Deletable=true;
						//}

						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

					}
				}
				else
				if(Code==0){
				}
			}
		}
		else
		if(strnicmp(text,/**/"ARC",3)==0){
			DXFOperationItemArc	*Item=new DXFOperationItemArc();
			Item->FileNo=FileNo;
			Item->SetSelected(true);
			AppendItem(Item);
			bool	Deletable=false;
			double	ExtrusionX[3];
			double	ExtrusionY[3];
			double	ExtrusionZ[3];
			ExtrusionX[0]=0;
			ExtrusionX[1]=0;
			ExtrusionX[2]=0;
			ExtrusionY[0]=0;
			ExtrusionY[1]=0;
			ExtrusionY[2]=0;
			ExtrusionZ[0]=0;
			ExtrusionZ[1]=0;
			ExtrusionZ[2]=0;
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					if(Deletable==true){
						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

						RemoveItem(Item);
						delete	Item;

						{
							int	N=Data.GetNumber();
							int	k=0;
							for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++);
							if(k!=N){
								Error=1;
							}
						}

					}
					if(ExtrusionZ[0]<0){
						Item->CenterX=ExtrusionZ[0]*Item->CenterX;
						Item->StartAngle	=M_PI-Item->StartAngle;
						Item->EndAngle		=M_PI-Item->EndAngle;
						swap(Item->StartAngle,Item->EndAngle);
						Item->StartAngle	=RegulateAngle(Item->StartAngle);
						Item->EndAngle		=RegulateAngle(Item->EndAngle);
					}
					return Code;
				}

				if(TopCode==' ' && Code==0){
					if(Deletable==true){
						RemoveItem(Item);
						delete	Item;

					}
					if(ExtrusionZ[0]<0){
						Item->CenterX=ExtrusionZ[0]*Item->CenterX;
						Item->StartAngle	=M_PI-Item->StartAngle;
						Item->EndAngle		=M_PI-Item->EndAngle;
						swap(Item->StartAngle,Item->EndAngle);
						Item->StartAngle	=RegulateAngle(Item->StartAngle);
						Item->EndAngle		=RegulateAngle(Item->EndAngle);
					}

					strcpy(text,Buff);
					return Code;
				}
				else
				if(Code==8){
					DXFLayer	*L=DXFLayerList.FindLayer(QString(Buff).trimmed());
					if(L!=NULL){
						Item->SetDXFLayer(L);
						if(Item->ColorCode==0){
							Item->ColorCode=L->ColorCode;
						}
					}
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						Item->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						Item->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						Item->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						Item->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					Item->ColorCode=ScanInt(Buff);
					//if(Item->ColorCode<=0){
					if(Item->ColorCode<0){
						//if(Deletable==false){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==10){
					Item->OrgCenterX=Item->CenterX=ScanDouble(Buff);
				}
				else
				if(Code==20){
					Item->OrgCenterY=Item->CenterY=ScanDouble(Buff);
				}
				else
				if(Code==40){
					Item->OrgRadius=Item->Radius=ScanDouble(Buff);
				}
				else
				if(Code==50){
					Item->OrgStartAngle=Item->StartAngle=ScanDouble(Buff)*2.0*M_PI/360.0;
				}
				else
				if(Code==51){
					Item->OrgEndAngle=Item->EndAngle=ScanDouble(Buff)*2.0*M_PI/360.0;
				}
				else
				if(Code==230){
					double	Tx=ScanDouble(Buff);
					ExtrusionZ[0]=Tx;
				}
				else
				if(Code==370){
					Item->Width=ScanDouble(Buff);
					if(Item->Width<0){

						//if(Deletable==false){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==0){
				}
			}
		}
		else
		if(strnicmp(text,/**/"CIRCLE",6)==0){
			DXFOperationItemCircle	*Item=new DXFOperationItemCircle();
			Item->FileNo=FileNo;
			Item->SetSelected(true);
			AppendItem(Item);
			bool	Deletable=false;
			double	ExtrusionX[3];
			double	ExtrusionY[3];
			double	ExtrusionZ[3];
			ExtrusionX[0]=0;
			ExtrusionX[1]=0;
			ExtrusionX[2]=0;
			ExtrusionY[0]=0;
			ExtrusionY[1]=0;
			ExtrusionY[2]=0;
			ExtrusionZ[0]=0;
			ExtrusionZ[1]=0;
			ExtrusionZ[2]=0;
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					if(Deletable==true){

						RemoveItem(Item);
						delete	Item;

					}
					if(ExtrusionZ[0]<0){
						Item->CenterX=ExtrusionZ[0]*Item->CenterX;
					}
					return Code;
				}

				if(TopCode==' ' && Code==0){
					if(Deletable==true){

						RemoveItem(Item);
						delete	Item;

					}
					if(ExtrusionZ[0]<0){
						Item->CenterX=ExtrusionZ[0]*Item->CenterX;
					}
					strcpy(text,Buff);
					return Code;
				}
				else
				if(Code==8){
					DXFLayer	*L=DXFLayerList.FindLayer(QString(Buff).trimmed());
					if(L!=NULL){
						Item->SetDXFLayer(L);
						if(Item->ColorCode==0){
							Item->ColorCode=L->ColorCode;
						}
					}
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						Item->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						Item->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						Item->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						Item->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					Item->ColorCode=ScanInt(Buff);
					//if(Item->ColorCode<=0){
					if(Item->ColorCode<0){
						//if(Deletable==false){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==10){
					Item->OrgCenterX=Item->CenterX=ScanDouble(Buff);
				}
				else
				if(Code==20){
					Item->OrgCenterY=Item->CenterY=ScanDouble(Buff);
				}
				else
				if(Code==40){
					Item->OrgRadius=Item->Radius=ScanDouble(Buff);
				}
				else
				if(Code==230){
					ExtrusionZ[0]=ScanDouble(Buff);
				}
				else
				if(Code==370){
					Item->Width=ScanDouble(Buff);
					if(Item->Width<0){

						//if(Deletable==true){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==0){
				}
			}
		}
		else
		if(strnicmp(text,/**/"LWPOLYLINE",10)==0){
			DXFOperationItemLWPolyLine	*Item=new DXFOperationItemLWPolyLine();
			Item->FileNo=FileNo;
			Item->SetSelected(true);
			AppendItem(Item);
			bool	Deletable=false;
			double	PosX=0;
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					if(Deletable==true){

						RemoveItem(Item);
						delete	Item;

					}
					return Code;
				}

				if(TopCode==' ' && Code==0){
					if(Deletable==true){

						RemoveItem(Item);
						delete	Item;

					}
					strcpy(text,Buff);
					return Code;
				}
				else
				if(Code==8){
					DXFLayer	*L=DXFLayerList.FindLayer(QString(Buff).trimmed());
					if(L!=NULL){
						Item->SetDXFLayer(L);
						if(Item->ColorCode==0){
							Item->ColorCode=L->ColorCode;
						}
					}
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						Item->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						Item->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						Item->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						Item->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					Item->ColorCode=ScanInt(Buff);
					//if(Item->ColorCode<=0){
					if(Item->ColorCode<0){
						//if(Deletable==true){
							RemoveItem(Item);
							Deletable=true;
						//}
					}
				}
				else
				if(Code==10){
					PosX=ScanDouble(Buff);
				}
				else
				if(Code==20){
					double	PosY=ScanDouble(Buff);
					XYDoubleClass	*p=new XYDoubleClass(PosX,PosY);
					Item->OrgPoints.AppendList(p);
					XYDoubleClass	*q=new XYDoubleClass(PosX,PosY);
					Item->Points.AppendList(q);
				}
				else
				if(Code==370){
					Item->Width=ScanDouble(Buff);
					if(Item->Width<0){

						//if(Deletable==true){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==0){
				}
			}
		}
		else
		if(strnicmp(text,/**/"POLYLINE",8)==0){
			DXFOperationItemPolyLine	*Item=new DXFOperationItemPolyLine();
			Item->FileNo=FileNo;
			Item->SetSelected(true);
			AppendItem(Item);
			bool	Deletable=false;
			double	PosX=0;
			double	PosY=0;
			double	LastPosX=0;
			double	LastPosY=0;
			double	Angle;
			int		LineType=0;	//1:Line	2:Arc
			int		LastLineType=0;
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					if(Deletable==true){
						RemoveItem(Item);
						delete	Item;

					}
					return Code;
				}
				if(Code==8){
					DXFLayer	*L=DXFLayerList.FindLayer(QString(Buff).trimmed());
					if(L!=NULL){
						Item->SetDXFLayer(L);
						if(Item->ColorCode==0){
							Item->ColorCode=L->ColorCode;
						}
					}
				}
				else
				if(Code==6){
					if(strnicmp(Buff,/**/"CONTINUOUS",10)==0){
						Item->LineType=CONTINUOUS;
					}
					else
					if(strnicmp(Buff,/**/"HIDDEN",6)==0){
						Item->LineType=HIDDEN;
					}
					else
					if(strnicmp(Buff,/**/"CENTER",6)==0){
						Item->LineType=CENTER;
					}
					else
					if(strnicmp(Buff,/**/"PHANTOM",7)==0){
						Item->LineType=PHANTOM;
					}
				}
				else
				if(Code==62){
					Item->ColorCode=ScanInt(Buff);
					//if(Item->ColorCode<=0){
					if(Item->ColorCode<0){
						//if(Deletable==true){
							RemoveItem(Item);
							Deletable=true;
						//}
					}
				}
				else
				if(Code==10){
					LastPosX=PosX;
					PosX=ScanDouble(Buff);
					LineType=1;
				}
				else
				if(Code==20){
					LastPosY=PosY;
					PosY=ScanDouble(Buff);
				}
				else
				if(Code==42){
					double	AngleTangent=ScanDouble(Buff);
					Angle=atan(AngleTangent)*4;
					LineType=2;
				}
				else
				if(Code==370){
					Item->Width=ScanDouble(Buff);
					if(Item->Width<0){

						//if(Deletable==true){
							RemoveItem(Item);
							Deletable=true;
						//}

					}
				}
				else
				if(Code==0){
					if(strnicmp(Buff,"VERTEX",6)==0){
						if(LastLineType==1){
							Item->AddItemLine(LastPosX,LastPosY,PosX,PosY);
						}
						if(LastLineType==2){
							Item->AddItemArc(LastPosX,LastPosY,PosX,PosY,Angle,0.2);
						}
						LastLineType=LineType;
					}
					if(strnicmp(Buff,"SEQEND",6)==0){
						if(LastLineType==1){
							Item->AddItemLine(LastPosX,LastPosY,PosX,PosY);
						}
						if(LastLineType==2){
							Item->AddItemArc(LastPosX,LastPosY,PosX,PosY,Angle,0.2);
						}
						if(Deletable==true){
							RemoveItem(Item);
							delete	Item;
								
						}
						strcpy(text,Buff);
						return Code;
					}
				}
			}
		}
		else
		if(strnicmp(text,/**/"DICTIONARY",10)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"ACAD_PROXY_OBJECT",17)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"ACDBDICTIONARYWDFLT",19)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"ACDBPLACEHOLDER",15)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"DATATABLE",9)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"DICTIONARYVAR",13)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"DIMASSOC",8)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"FIELD",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"GEODATA",7)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"GROUP",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"IDBUFFER",8)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"IMAGEDEF",8)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"IMAGEDEF_REACTOR",16)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LAYER_INDEX",11)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LAYER_FILTER",12)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LAYOUT",6)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"LIGHTLIST",9)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"MATERIAL",8)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"MLINESTYLE",10)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"OBJECT_PTR",10)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"PLOTSETTINGS",12)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"RASTERVARIABLES",15)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"TABLESTYLE",10)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"UNDERLAYDEFINITION",18)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"VISUALSTYLE",11)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"XRECORD",7)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"TCOPTIONALDATA",14)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"MLEADERSTYLE",12)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else
		if(strnicmp(text,/**/"SCALE",5)==0){
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
		else{
			SpecialGroupName.append(text);
			for(;;){
				int Code=GetLines(f ,Buff,TopCode,LineNumber);
				if(Code<0){
					return Code;
				}

				if(TopCode==' ' && Code==0){
					strcpy(text,Buff);
					return Code;
				}
			}
		}
	}
	return -1;
}
	
