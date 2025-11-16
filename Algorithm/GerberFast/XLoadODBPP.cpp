#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "swap.h"
#include "XCrossObj.h"
//#include "zlib.h"
#include <QTemporaryFile>

extern	int	DebugDCode;
extern	int	DbgPage	;
extern	int	DCodeDebug;
extern	int	DbgID	;



QString	GerberFastBase::UnzipInTemp(const QString &FeatureFileNameZ)
{
	QFileInfo	FInfo(FeatureFileNameZ);
	int	Len=FInfo.size();
	BYTE	*src=new BYTE[Len+100];
	BYTE	*dst=new BYTE[Len*10];
	
	QString	Param=ODBArchiverParameter.replace("$GerberFile",FeatureFileNameZ);;
	QProcess::execute (ODBArchiverExeFile,QStringList(Param));

	delete	[]src;
	delete	[]dst;

	return ".\\Feature";
}

bool	GerberFastBase::LoadODBPPDirectories(const QString &TopPath , bool OnlyFile
											, ODBStepContainer &StepContainer
											,QStringList &LayerPathList
											,ODBLayerContainer	&MatrixLayers)
{
	QDir	TopDir(TopPath);

	QFileInfoList	PathList=TopDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<PathList.count();i++){
		QFileInfo	FInfo=PathList[i];
		QString	PathName=FInfo.fileName().toUpper();
		if(PathName==QString("MATRIX")){
			QString	AbsPath=FInfo.absoluteFilePath();
			if(LoadMatrixFile(AbsPath+::GetSeparator()+QString("matrix"),StepContainer ,MatrixLayers)==false){
				return false;
			}
		}
		if(PathName==QString("STEPS")){
			QDir	StepDir(TopPath+::GetSeparator()+QString("Steps"));
			QFileInfoList	StepList=StepDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
			for(int j=0;j<StepList.count();j++){
				QString	StepUnitPath=StepList[j].absoluteFilePath();
				QString	LayerPath=StepUnitPath;//+::GetSeparator()+QString("Layers");
				LayerPathList.append(LayerPath);
			}
		}
	}
	if(LayerPathList.count()==0)
		return false;
	return true;
}

bool	GerberFastBase::LoadODBFeatureDirectories(bool OnlyFile
											, ODBStepContainer &StepContainer 
											, QStringList &LayerPathList
											, QStringList &FileList
											,ODBLayerContainer	&MatrixLayers)
{

	for(ODBStepList *s=StepContainer.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Usage==false)
			continue;
		QString	AbsPath;
		for(int k=0;k<LayerPathList.count();k++){
			QFileInfo	FInfo(LayerPathList[k]);
			if(FInfo.fileName().toUpper()==s->Name){
				AbsPath=LayerPathList[k]+::GetSeparator()+QString("Layers");
				break;
			}
		}

		for(ODBLayer *Ly=MatrixLayers.GetFirst();Ly!=NULL;Ly=Ly->GetNext()){
			//if(Ly->Type=="Document"){
				QString	FeatureFileName	=AbsPath+::GetSeparator()+Ly->Name+::GetSeparator()+QString("Features");
				QString	FeatureFileNameZ=AbsPath+::GetSeparator()+Ly->Name+::GetSeparator()+QString("Features.Z");
			
				QFile	FeatureFileZ(FeatureFileNameZ);
				if(FeatureFileZ.exists()==true){
					FileList.append(FeatureFileNameZ);
					if(OnlyFile==false){
						QString	ZZZFileName=UnzipInTemp(FeatureFileNameZ);

						GerberFileLayerContainer		TmpFileLayerList((GerberFastInPage *)GetPageData(0));
						GerberFileLayer	*Layer=new GerberFileLayer(&TmpFileLayerList);
						Layer->LayerName	=Ly->Name;
						Layer->FileName		=ZZZFileName;
						char	tmpFileName[1000];
						::QString2Char(ZZZFileName,tmpFileName,sizeof(tmpFileName));
						::ChangePathSeparator(/**/'\\',/**/'/',tmpFileName);

						FILE	*file=fopen(tmpFileName,/**/"rt");
						int	LineNumber;
						Layer->LoadODBPP(this,file,LineNumber);
						fclose(file);
						remove(tmpFileName);
						delete	Layer;
					}
				}
				else{
					FileList.append(FeatureFileName);
					if(OnlyFile==false){
						GerberFileLayerContainer		TmpFileLayerList((GerberFastInPage *)GetPageData(0));
						GerberFileLayer	*Layer=new GerberFileLayer(&TmpFileLayerList);
						Layer->LayerName	=Ly->Name;
						Layer->FileName		=FeatureFileName;
						char	tmpFileName[1000];
						::QString2Char(FeatureFileName,tmpFileName,sizeof(tmpFileName));
						::ChangePathSeparator(/**/'\\',/**/'/',tmpFileName);

						FILE	*file=fopen(tmpFileName,/**/"rt");
						int	LineNumber;
						Layer->LoadODBPP(this,file,LineNumber);
						delete	Layer;
					}
				}
			//}
		}
	}
	return true;
}

bool	GerberFastBase::LoadMatrixFile(const QString &AbsFileName
										, ODBStepContainer &StepContainer 
										, ODBLayerContainer &MatrixLayers)
{
	QFile	File(AbsFileName);
	if(File.open(QIODevice::ReadOnly)==false)
		return false;

	QTextStream	Str(&File);
	while(Str.atEnd()==false){
		QString	LineStr=Str.readLine().trimmed();
		if(LineStr.left(4).toUpper()==QString("STEP")){
			ODBStepList	*Step=new ODBStepList();
			while(Str.atEnd()==false){
				LineStr=Str.readLine().trimmed();
				QStringList	StrList=LineStr.split('=');
				if(StrList[0].trimmed().toUpper()==QString("COL")){
					bool	ok;
					Step->Col	=StrList[1].trimmed().toInt(&ok);
					if(ok==false)
						return false;
				}
				else if(StrList[0].trimmed().toUpper()==QString("NAME")){
					Step->Name=StrList[1].trimmed();
				}
				else if(StrList[0].trimmed().toUpper()==QString("}")){
					StepContainer.AppendList(Step);
					break;
				}
			}
		}
		else if(LineStr.left(5).toUpper()==QString("LAYER")){
			ODBLayer	*Ly=new ODBLayer();
			while(Str.atEnd()==false){
				LineStr=Str.readLine().trimmed();
				QStringList	StrList=LineStr.split('=');
				if(StrList[0].trimmed().toUpper()==QString("ROW")){
					bool	ok;
					Ly->Row	=StrList[1].trimmed().toInt(&ok);
					if(ok==false)
						return false;
				}
				else if(StrList[0].trimmed().toUpper()==QString("CONTEXT")){
					if(StrList[1].trimmed().toUpper()==QString("BOARD")){
						Ly->Context="Board";
					}
				}
				else if(StrList[0].trimmed().toUpper()==QString("TYPE")){
					if(StrList[1].trimmed().toUpper()==QString("COMPONENT")){
						Ly->Type="Component";
					}
					else if(StrList[1].trimmed().toUpper()==QString("DOCUMENT")){
						Ly->Type="Document";
					}
				}
				else if(StrList[0].trimmed().toUpper()==QString("NAME")){
					Ly->Name=StrList[1].trimmed();
				}
				else if(StrList[0].trimmed().toUpper()==QString("POLARITY")){
					if(StrList[1].trimmed().toUpper()==QString("POSITIVE")){
						Ly->Polarity=true;
					}
					else{
						Ly->Polarity=false;
					}
				}
				else if(StrList[0].trimmed().toUpper()==QString("START_NAME")){
					Ly->Start_Name=StrList[1].trimmed();
				}
				else if(StrList[0].trimmed().toUpper()==QString("END_NAME")){
					Ly->End_Name=StrList[1].trimmed();
				}
				else if(StrList[0].trimmed().toUpper()==QString("}")){
					MatrixLayers.AppendList(Ly);
					break;
				}
			}
		}
	}
	return true;
}

static	char	*GetInt(char *fp,int &SymbolNumber)
{
	int		Sign=1;
	while(*fp==' ' || *fp=='\t')	fp++;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}
	int	n=*fp-(int)'0';
	if(n<0 || 9<n)
		return NULL;
	SymbolNumber=0;
	while(*fp!=0){
		n=*fp-(int)'0';
		if(0<=n && n<=9){
			SymbolNumber*=10;
			SymbolNumber+=n;
			fp++;
		}
		else{
			break;
		}
	}
	SymbolNumber = Sign*SymbolNumber;
	while(*fp==' ' || *fp=='\t')	fp++;
	return fp;
}

static	char	*Get1Char(char *fp ,char &C)
{
	while(*fp==' ' || *fp=='\t')	fp++;
	C=*fp;
	fp++;
	while(*fp==' ' || *fp=='\t')	fp++;
	return fp;
}

static	char	*GetDouble(char *fp,double &SymbolNumber)
{
	int		Sign=1;
	while(*fp==' ' || *fp=='\t')	fp++;
	if(*fp=='-'){
		Sign=-1;
		fp++;
	}
	else if(*fp=='+'){
		Sign=1;
		fp++;
	}
	int	n=*fp-(int)'0';
	if((n<0 || 9<n) && *fp!='.')
		return NULL;
	SymbolNumber=0;
	while(*fp!=0){
		n=*fp-(int)'0';
		if(0<=n && n<=9){
			SymbolNumber*=10;
			SymbolNumber+=n;
			fp++;
		}
		else{
			break;
		}
	}
	if(*fp=='.'){
		fp++;
		double	Digit=1;
		while(*fp!=0){
			n=*fp-(int)'0';
			if(0<=n && n<=9){
				Digit*=0.1;
				SymbolNumber+=n*Digit;
				fp++;
			}
			else{
				break;
			}
		}
	}
	SymbolNumber = Sign*SymbolNumber;
	while(*fp==' ' || *fp=='\t')	fp++;
	return fp;
}

void	Make1234(int d ,bool &n1 ,bool &n2 ,bool &n3 ,bool &n4)
{
	int	d1=d%10;
	int	d2=(d/10)%10;
	int	d3=(d/100)%10;
	int	d4=(d/1000)%10;

	if(d1==1 || d2==1 || d3==1 || d4==1)
		n1=true;
	else
		n1=false;
	if(d1==2 || d2==2 || d3==2 || d4==2)
		n2=true;
	else
		n2=false;
	if(d1==3 || d2==3 || d3==3 || d4==3)
		n3=true;
	else
		n3=false;
	if(d1==4 || d2==4 || d3==4 || d4==4)
		n4=true;
	else
		n4=false;
}

bool	GerberFileLayer::LoadODBPP(GerberFastBase *GBase ,FILE *file ,int &LineNumber)
{
	char	Buff[1000];
	double	Unit	=25.4;
	double	SymbolUnit	=25.4/1000.0;

	for(LineNumber=0;fgets(Buff,sizeof(Buff)-1,file)!=NULL;LineNumber++){
		char	*fp=Buff;
		while(*fp==' ' || *fp=='\t')	fp++;
		if(*fp=='$'){
			fp++;
			int	SymbolNumber=-1;
			if((fp=GetInt(fp,SymbolNumber))==NULL)
				return false;
			if(strncmp(fp,"rect",4)==0){
				fp+=4;
				while(*fp==' ' || *fp=='\t')	fp++;
				double	W,H;
				if((fp=GetDouble(fp,W))==NULL)
					return false;
				if(*fp!='x')
					return false;
				fp++;
				while(*fp==' ' || *fp=='\t')	fp++;
				if((fp=GetDouble(fp,H))==NULL)
					return false;
				if(strncmp(fp,"xr",2)==0){
					double	Rad;
					fp+=2;
					if((fp=GetDouble(fp,Rad))==NULL)
						return false;
					if(*fp=='x'){
						fp++;
						while(*fp==' ' || *fp=='\t')	fp++;
						int	Corner;
						if((fp=GetInt(fp,Corner))==NULL)
							return false;
						bool n1 ,n2 ,n3 ,n4;
						Make1234(Corner,n1 ,n2 ,n3 ,n4);
						GerberDCodeRectRCorner	*d=new GerberDCodeRectRCorner(&DCodeList);
						d->DCode	=SymbolNumber;
						d->HSize	=H*SymbolUnit;
						d->WSize	=W*SymbolUnit;
						d->Radius	=Rad*SymbolUnit;
						d->Attr.Rounded		=true;
						d->Attr.TopRight	= n1;
						d->Attr.TopLeft		= n2;
						d->Attr.BottomLeft	= n3;
						d->Attr.BottomRight	= n4;
						DCodeList.AppendList(d);
					}
					else{
						GerberDCodeRectRCorner	*d=new GerberDCodeRectRCorner(&DCodeList);
						d->DCode	=SymbolNumber;
						d->HSize	=H*SymbolUnit;
						d->WSize	=W*SymbolUnit;
						d->Radius	=Rad*SymbolUnit;
						d->Attr.Rounded		= true;
						d->Attr.TopRight	= true;
						d->Attr.TopLeft		= true;
						d->Attr.BottomLeft	= true;
						d->Attr.BottomRight	= true;
						DCodeList.AppendList(d);
					}
				}
				else if(strncmp(fp,"xc",2)==0){
					double	Rad;
					fp+=2;
					if((fp=GetDouble(fp,Rad))==NULL)
						return false;
					if(*fp=='x'){
						fp++;
						while(*fp==' ' || *fp=='\t')	fp++;
						int	Corner;
						if((fp=GetInt(fp,Corner))==NULL)
							return false;
						bool n1 ,n2 ,n3 ,n4;
						Make1234(Corner,n1 ,n2 ,n3 ,n4);
						GerberDCodeRectRCorner	*d=new GerberDCodeRectRCorner(&DCodeList);
						d->DCode	=SymbolNumber;
						d->HSize	=H*SymbolUnit;
						d->WSize	=W*SymbolUnit;
						d->Radius	=Rad*SymbolUnit;
						d->Attr.Rounded		=false;
						d->Attr.TopRight	= n1;
						d->Attr.TopLeft		= n2;
						d->Attr.BottomLeft	= n3;
						d->Attr.BottomRight	= n4;
						DCodeList.AppendList(d);
					}
					else{
						GerberDCodeRectRCorner	*d=new GerberDCodeRectRCorner(&DCodeList);
						d->DCode	=SymbolNumber;
						d->HSize	=H*SymbolUnit;
						d->WSize	=W*SymbolUnit;
						d->Radius	=Rad*SymbolUnit;
						d->Attr.Rounded		= false;
						d->Attr.TopRight	= true;
						d->Attr.TopLeft		= true;
						d->Attr.BottomLeft	= true;
						d->Attr.BottomRight	= true;
						DCodeList.AppendList(d);
					}
				}
				else{
					GerberDCodeRectangle	*d=new GerberDCodeRectangle(&DCodeList);
					d->DCode	=SymbolNumber;
					d->HSize	=H*SymbolUnit;
					d->WSize	=W*SymbolUnit;
					DCodeList.AppendList(d);
				}
			}
			else if(strncmp(fp,"oval",4)==0){
				fp+=4;
				while(*fp==' ' || *fp=='\t')	fp++;
				double	W,H;
				if((fp=GetDouble(fp,W))==NULL)
					return false;
				if(*fp!='x')
					return false;
				fp++;
				while(*fp==' ' || *fp=='\t')	fp++;
				if((fp=GetDouble(fp,H))==NULL)
					return false;

				GerberDCodeObround	*d=new GerberDCodeObround(&DCodeList);
				d->DCode	=SymbolNumber;
				d->HSize	=H*SymbolUnit;
				d->WSize	=W*SymbolUnit;
				DCodeList.AppendList(d);
			}
			else if(strncmp(fp,"di",2)==0){
				fp+=2;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"oct",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"donut_rc",8)==0){
				fp+=8;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"donut_r",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"donut_sr",8)==0){
				fp+=8;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"donut_s",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"donut_o",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"hex_l",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"hex_s",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"bfr",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"bfs",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"tri",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"oval_h",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"thr",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"ths",3)==0){
				fp+=3;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"s_ths",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"s_tho",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"s_thr",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"sr_ths",6)==0){
				fp+=6;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"rc_ths",6)==0){
				fp+=6;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"rc_tho",6)==0){
				fp+=6;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"oblong_ths",10)==0){
				fp+=10;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"hplate",6)==0){
				fp+=6;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"rhplate",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"fhplate",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"radhplate",9)==0){
				fp+=9;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"dshape",6)==0){
				fp+=6;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"cross",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"dogbone",7)==0){
				fp+=7;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"dpack",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"el",2)==0){
				fp+=2;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"moire",5)==0){
				fp+=5;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"hole",4)==0){
				fp+=4;
				while(*fp==' ' || *fp=='\t')	fp++;
			}
			else if(strncmp(fp,"r",1)==0){
				fp+=1;
				while(*fp==' ' || *fp=='\t')	fp++;
				double	Diameter;
				if((fp=GetDouble(fp,Diameter))==NULL)
					return false;
				GerberDCodeCircle	*d=new GerberDCodeCircle(&DCodeList);
				d->DCode	=SymbolNumber;
				d->HSize	=Diameter*SymbolUnit;
				d->WSize	=Diameter*SymbolUnit;
				DCodeList.AppendList(d);
			}
			else if(strncmp(fp,"s",1)==0){
				fp+=1;
				while(*fp==' ' || *fp=='\t')	fp++;
				double	Length;
				if((fp=GetDouble(fp,Length))==NULL)
					return false;
				GerberDCodeRectangle	*d=new GerberDCodeRectangle(&DCodeList);
				d->DCode	=SymbolNumber;
				d->HSize	=Length*SymbolUnit;
				d->WSize	=Length*SymbolUnit;
				DCodeList.AppendList(d);
			}
		}
		else if(*fp=='L'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
				
			double	xs,ys,xe,ye;
			int		sym_num;
			char	Polarity;
			int		DCode;

			if((fp=GetDouble(fp,xs))==NULL)
				return false;
			if((fp=GetDouble(fp,ys))==NULL)
				return false;
			if((fp=GetDouble(fp,xe))==NULL)
				return false;
			if((fp=GetDouble(fp,ye))==NULL)
				return false;
						
			if((fp=GetInt(fp,sym_num))==NULL)
				return false;
			if((fp=Get1Char(fp ,Polarity))==NULL)
				return false;
			if((fp=GetInt(fp,DCode))==NULL)
				return false;

			GerberDCodeBase	*D=DCodeList.FindDCode(sym_num);
			if(D==NULL)
				return false;
			GerberFastItemLine	*Item=new GerberFastItemLine();
			Item->SetFileLayer(this);
			Item->PosX1	=xs*Unit;
			Item->PosY1	=ys*Unit;
			Item->PosX2	=xe*Unit;
			Item->PosY2	=ye*Unit;
			Item->ZoomAperture	=1;
			Item->OrgPosX1	=Item->PosX1;
			Item->OrgPosY1	=Item->PosY1;
			Item->OrgPosX2	=Item->PosX2;
			Item->OrgPosY2	=Item->PosY2;
			Item->SetDCode(D);
			Item->SetPosiImage((Polarity=='P')?true:false);
								
			if(Parent!=NULL && Parent->GetParent()!=NULL){
				Parent->GetParent()->AppendItem(Item);
				if(Item->GetID()==DbgID){
					DCodeDebug++;
				}
			}
		}
		else if(*fp=='P'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
				
			double	x,y;
			int		apt;
			char	Polarity;
			int		DCode;
			int		orient_def;

			if((fp=GetDouble(fp,x))==NULL)
				return false;
			if((fp=GetDouble(fp,y))==NULL)
				return false;
						
			if((fp=GetInt(fp,apt))==NULL)
				return false;
			if((fp=Get1Char(fp ,Polarity))==NULL)
				return false;
			if((fp=GetInt(fp,DCode))==NULL)
				return false;
			if((fp=GetInt(fp,orient_def))==NULL)
				return false;
			double	GAngle;

			GerberDCodeBase	*D=DCodeList.FindDCode(apt);
			if(D==NULL)
				return false;
			GerberFastItemFlash	*Item=new GerberFastItemFlash();
			Item->SetFileLayer(this);
			Item->PosX	=x*Unit;
			Item->PosY	=y*Unit;
			Item->ZoomAperture	=1;
			Item->OrgPosX	=Item->PosX;
			Item->OrgPosY	=Item->PosY;
			Item->SetDCode(D);
			Item->SetPosiImage((Polarity=='P')?true:false);
			switch(orient_def){
				case 0:	
					Item->Angle=0;
					Item->ModeMirrorX=false;
					Item->ModeMirrorY=false;
					break;
				case 1:	
					Item->Angle=90.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=false;
					Item->ModeMirrorY=false;
					break;
				case 2:	
					Item->Angle=180.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=false;
					Item->ModeMirrorY=false;
					break;
				case 3:	
					Item->Angle=270.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=false;
					Item->ModeMirrorY=false;
					break;
				case 4:	
					Item->Angle=0;
					Item->ModeMirrorX=true;
					Item->ModeMirrorY=false;
					break;
				case 5:	
					Item->Angle=90.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=true;
					Item->ModeMirrorY=false;
					break;
				case 6:	
					Item->Angle=180.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=true;
					Item->ModeMirrorY=false;
					break;
				case 7:	
					Item->Angle=270.0/360.0*2.0*M_PI;
					Item->ModeMirrorX=true;
					Item->ModeMirrorY=false;
					break;
				case 8:
					if((fp=GetDouble(fp,GAngle))==NULL)
						return false;
					Item->Angle=GAngle/360.0*2.0*M_PI;
					Item->ModeMirrorX=false;
					Item->ModeMirrorY=false;
					break;
				case 9:
					if((fp=GetDouble(fp,GAngle))==NULL)
						return false;
					Item->Angle=GAngle/360.0*2.0*M_PI;
					Item->ModeMirrorX=true;
					Item->ModeMirrorY=false;
					break;
				default:
					return false;
			}
								
			if(Parent!=NULL && Parent->GetParent()!=NULL){
				Parent->GetParent()->AppendItem(Item);
				if(Item->GetID()==DbgID){
					DCodeDebug++;
				}
			}
		}
		else if(*fp=='A'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
				
			double	xs,ys,xe,ye,xc,yc;
			int		sym_num;
			char	Polarity;
			int		DCode;
			char	CW;

			if((fp=GetDouble(fp,xs))==NULL)
				return false;
			if((fp=GetDouble(fp,ys))==NULL)
				return false;
			if((fp=GetDouble(fp,xe))==NULL)
				return false;
			if((fp=GetDouble(fp,ye))==NULL)
				return false;
			if((fp=GetDouble(fp,xc))==NULL)
				return false;
			if((fp=GetDouble(fp,yc))==NULL)
				return false;
						
			if((fp=GetInt(fp,sym_num))==NULL)
				return false;
			if((fp=Get1Char(fp ,Polarity))==NULL)
				return false;
			if((fp=GetInt(fp,DCode))==NULL)
				return false;
			if((fp=Get1Char(fp ,CW))==NULL)
				return false;

			GerberDCodeBase	*D=DCodeList.FindDCode(sym_num);
			if(D==NULL)
				return false;
			GerberFastItemArc	*Item=new GerberFastItemArc();
			Item->SetFileLayer(this);
			Item->CenterX	=xc*Unit;
			Item->CenterY	=yc*Unit;
			Item->Radius	=hypot(xc-xs,yc-ys)*Unit;
			Item->StartAngle=GetSita(xs-xc,ys-yc);
			Item->EndAngle	=GetSita(xe-xc,ye-yc);
			if(CW=='Y'){
				swap(Item->StartAngle,Item->EndAngle);
			}
			Item->ZoomAperture	=1;

			Item->OrgCenterX	=Item->CenterX;
			Item->OrgCenterY	=Item->CenterY;
			Item->OrgRadius		=Item->Radius;
			Item->OrgStartAngle	=Item->StartAngle;
			Item->OrgEndAngle	=Item->EndAngle;

			Item->SetDCode(D);
			Item->SetPosiImage((Polarity=='P')?true:false);
								
			if(Parent!=NULL && Parent->GetParent()!=NULL){
				Parent->GetParent()->AppendItem(Item);
				if(Item->GetID()==DbgID){
					DCodeDebug++;
				}
			}
		}
		else if(*fp=='T'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
		}
		else if(*fp=='B'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
		}
		else if(*fp=='S'){
			fp++;
			while(*fp==' ' || *fp=='\t')	fp++;
				
			char	Polarity;
			int		DCode;

			if((fp=Get1Char(fp ,Polarity))==NULL)
				return false;
			if((fp=GetInt(fp,DCode))==NULL)
				return false;

			NPListPack<DoubleForPolygonList>	PolygonPoints;
			double	xbs,ybs;
			double	start_x,start_y;
			char	poly_type='I';
			for(;fgets(Buff,sizeof(Buff)-1,file)!=NULL;LineNumber++){
				char	*fp=Buff;
				while(*fp==' ' || *fp=='\t')	fp++;
				if(strncmp(fp,"OB",2)==0){
					fp+=2;
					while(*fp==' ' || *fp=='\t')	fp++;

					if((fp=GetDouble(fp,xbs))==NULL)
						return false;
					if((fp=GetDouble(fp,ybs))==NULL)
						return false;
					if((fp=Get1Char(fp ,poly_type))==NULL)
						return false;
					PolygonPoints.RemoveAll();
					start_x	=xbs;
					start_y	=ybs;
				}
				else if(strncmp(fp,"OS",2)==0){
					fp+=2;
					while(*fp==' ' || *fp=='\t')	fp++;

					double	x,y;
					char	cw;
					if((fp=GetDouble(fp,x))==NULL)
						return false;
					if((fp=GetDouble(fp,y))==NULL)
						return false;
					if((fp=Get1Char(fp ,cw))==NULL)
						return false;
					DoubleForPolygonList	*s=new DoubleForPolygonList();
					s->LastX	=xbs;
					s->LastY	=ybs;
					s->X	=x;
					s->Y	=y;
					s->Mode	=0;
					PolygonPoints.AppendList(s);
					xbs=x;
					ybs=y;
				}
				else if(strncmp(fp,"OC",2)==0){
					fp+=2;
					while(*fp==' ' || *fp=='\t')	fp++;

					double	xe,ye;
					double	xc,yc;
					char	cw;
					if((fp=GetDouble(fp,xe))==NULL)
						return false;
					if((fp=GetDouble(fp,ye))==NULL)
						return false;
					if((fp=GetDouble(fp,xc))==NULL)
						return false;
					if((fp=GetDouble(fp,yc))==NULL)
						return false;
					if((fp=Get1Char(fp ,cw))==NULL)
						return false;

					DoubleForPolygonList	*s=new DoubleForPolygonList();
					s->Mode	=1;
					s->LastX	=xbs;
					s->LastY	=ybs;
					s->X		=xe;
					s->Y		=ye;
					s->CenterX	=xc;
					s->CenterY	=yc;
					s->StartAngle	=GetSita(xbs-xc,ybs-yc);
					s->EndAngle	=GetSita(xe-xc,ye-yc);
					if(cw=='N'){
						swap(s->StartAngle,s->EndAngle);
					}
					PolygonPoints.AppendList(s);
					xbs=xe;
					ybs=ye;
				}
				else if(strncmp(fp,"OE",2)==0){
					fp+=2;
					while(*fp==' ' || *fp=='\t')	fp++;

					if(start_x!=xbs || start_y!=ybs){
						DoubleForPolygonList	*s=new DoubleForPolygonList();
						s->LastX	=xbs;
						s->LastY	=ybs;
						s->X	=start_x;
						s->Y	=start_y;
						s->Mode	=0;
						PolygonPoints.AppendList(s);
					}
					int	N=PolygonPoints.GetNumber();

					GerberFastItemPolygon	*Item=new GerberFastItemPolygon();
					Item->SetFileLayer(this);
					Item->PosiImage	=Polarity;
					Item->OrgPoints=new GerberFastItemPolygon::PointStruct[N];
					int	n=0;
					for(DoubleForPolygonList *d=PolygonPoints.GetFirst();d!=NULL;d=d->GetNext()){
						Item->OrgPoints[n]	=*d;
						if(d->Mode==0){
							Item->OrgPoints[n].Data.PosX =d->X*Unit;
							Item->OrgPoints[n].Data.PosY =d->Y*Unit;
							Item->OrgPoints[n].Data.LastX=d->LastX*Unit;
							Item->OrgPoints[n].Data.LastY=d->LastY*Unit;
							Item->OrgPoints[n].Data.PointType=GerberFastItemPolygon::PointStruct::_Line;
						}
						else if(d->Mode==1){
							Item->OrgPoints[n].Data.PosX		=d->X*Unit;
							Item->OrgPoints[n].Data.PosY		=d->Y*Unit;
							Item->OrgPoints[n].Data.CenterX		=d->CenterX*Unit;
							Item->OrgPoints[n].Data.CenterY		=d->CenterY*Unit;
							Item->OrgPoints[n].Data.LastX		=d->LastX*Unit;
							Item->OrgPoints[n].Data.LastY		=d->LastY*Unit;
							Item->OrgPoints[n].Data.PointType	=GerberFastItemPolygon::PointStruct::_Arc;
							Item->OrgPoints[n].Data.StartAngle	=d->StartAngle;
							Item->OrgPoints[n].Data.EndAngle	=d->EndAngle;
						}
						n++;
					}
					Item->OrgPosCount=N;
					Item->SetPosiImage((Polarity=='P')?true:false);
					Item->InitialFromOrg();
					if(Parent!=NULL && Parent->GetParent()!=NULL){
						Parent->GetParent()->AppendItem(Item);
						if(Item->GetID()==DbgID){
							DCodeDebug++;
						}
					}
					PolygonPoints.RemoveAll();
				}
				else if(strncmp(fp,"SE",2)==0){
					fp+=2;
					while(*fp==' ' || *fp=='\t')	fp++;
					break;
				}
			}
		}
	}
	return true;
}
