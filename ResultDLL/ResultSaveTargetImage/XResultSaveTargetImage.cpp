#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultSaveTargetImage.h"
#include "XLotInformation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <QVariant>
#include "XGeneralStocker.h"

ImageBuffersListWithFlag::ImageBuffersListWithFlag(int tPhaseNumb ,int tPageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines)
	:ShouldWrite(false),PhaseNumb(tPhaseNumb),PageNumb(tPageNumb)
{
	PageImage	=new ImageBufferListContainer*[PhaseNumb];
	for(int phase=0;phase<PhaseNumb;phase++){
		PageImage[phase]=new ImageBufferListContainer[PageNumb];
		for(int page=0;page<PageNumb;page++){
			for(int layer=0;layer<LayerNumb;layer++){
				(PageImage[phase])[page].AppendList(new ImageBufferList(ImageBufferTarget ,DotPerLine ,MaxLines));
			}
		}
	}
	Number=0;
}

ImageBuffersListWithFlag::~ImageBuffersListWithFlag(void)
{
	if(PageImage!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<PageNumb;page++){
				int	LayerNumb=(PageImage[phase])[page].GetCount();
				for(int layer=0;layer<LayerNumb;layer++){
					(PageImage[phase])[page].RemoveAll();
				}
			}
			delete	[]PageImage[phase];
		}
		delete	[]PageImage;
		PageImage=NULL;
	}

}

ImageBuffersListWithFlag	&ImageBuffersListWithFlag::operator=(ImageBuffersListWithFlag &src)
{
	if(PageImage!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<PageNumb;page++){
				int	LayerNumb=(PageImage[phase])[page].GetCount();
				for(int layer=0;layer<LayerNumb;layer++){
					ImageBufferList	*d=(	PageImage[phase])[page].GetItem(layer);
					ImageBufferList	*s=(src.PageImage[phase])[page].GetItem(layer);
					if(d!=NULL && s!=NULL){
						*d=*s;
					}
				}
			}
		}
	}
	return *this;
}

int	ImageBuffersListWithFlag::GetDotPerLine(void)
{
	if(PageImage!=NULL){
		ImageBufferList	*s=PageImage[0][0].GetFirst();
		if(s!=NULL){
			return s->GetWidth();
		}
	}
	return 0;
}
int	ImageBuffersListWithFlag::GetMaxLines(void)	
{
	if(PageImage!=NULL){
		ImageBufferList	*s=PageImage[0][0].GetFirst();
		if(s!=NULL){
			return s->GetHeight();
		}
	}
	return 0;
}
int	ImageBuffersListWithFlag::GetLayerNumb(void)
{
	if(PageImage!=NULL){
		int	LayerNumb=(PageImage[0])[0].GetCount();
		return LayerNumb;
	}
	return 0;
}
int	ImageBuffersListWithFlag::GetPageNumb(void)
{
	return PageNumb;
}
int	ImageBuffersListWithFlag::GetPhaseNumb(void)
{
	return PhaseNumb;
}

ImageBuffer	*ImageBuffersListWithFlag::GetBuffer(int phase,int page,int layer)
{
	if(PageImage!=NULL && 0<=phase && phase<PhaseNumb && 0<=page && page<PageNumb){
		ImageBufferList	*s=PageImage[phase][page].GetItem(layer);
		if(s!=NULL){
			return s;
		}
	}
	return NULL;
}

bool	ImageBuffersListWithFlag::WriteOut(void)
{
	QFileInfo	Info(FileName);

	::ForceDirectories(Info.absolutePath());

	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=2;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPhaseNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetLayerNumb())==false)
		return false;

	if(::Save(&WFile,(int)GetDotPerLine())==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines())==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	int	YCountBase=100;
	QByteArray    Data;
	Data.resize(YCountBase*GetDotPerLine());

	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	YCount=YCountBase;
			for(int TopY=0;TopY<GetMaxLines();TopY+=YCount){
				if(TopY+YCount>GetMaxLines())
					YCount=GetMaxLines()-TopY;
				Data.resize(YCount*GetDotPerLine());
				for(int Layer=0;Layer<GetLayerNumb();Layer++){
					ImageBuffer	*s=GetBuffer(phase , page ,Layer);
					BYTE	*Dest=(BYTE *)Data.data();
					for(int y=TopY;y<TopY+YCount;y++){
						memcpy(Dest,s->GetY(y),GetDotPerLine());
						Dest+=GetDotPerLine();
					}
					if(WFile.write(Data)!=Data.size()){
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool	ImageBuffersListWithFlag::WriteOut(int UseLayer)
{
	QFileInfo	Info(FileName);

	::ForceDirectories(Info.absolutePath());

	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=2;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPhaseNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	int	tLayerNumb=1;
	if(::Save(&WFile,(int)tLayerNumb)==false)
		return false;

	if(::Save(&WFile,(int)GetDotPerLine())==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines())==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	int	YCountBase=100;
	QByteArray    Data;
	Data.resize(YCountBase*GetDotPerLine());

	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	YCount=YCountBase;
			for(int TopY=0;TopY<GetMaxLines();TopY+=YCount){
				if(TopY+YCount>GetMaxLines())
					YCount=GetMaxLines()-TopY;
				Data.resize(YCount*GetDotPerLine());

				ImageBuffer	*s=GetBuffer(phase , page ,UseLayer);
				BYTE	*Dest=(BYTE *)Data.data();
				for(int y=TopY;y<TopY+YCount;y++){
					memcpy(Dest,s->GetY(y),GetDotPerLine());
					Dest+=GetDotPerLine();
				}
				if(WFile.write(Data)!=Data.size()){
					return false;
				}
			}
		}
	}
	return true;
}

//=============================================================================================

ResultSaveTargetImage::ResultSaveTargetImage(LayersBase *Base)
	:ResultDLLBaseRoot(Base)
{
	AllocatedCount	=3;
	UseGeneralStockerToGetPath	=false;
	Terminated		=false;
	SavedFolder	=/**/"D:\\LogImage";
	OnlyNG		=true;
	UseGeneralStockerToGetPath	=false;
	UseLayer	=-1;
	
	SetParam(&PathList					, /**/"Setting"	,/**/"PathList"						,"Path list to save"				);
	SetParam(&AllocatedCount			, /**/"Setting"	,/**/"AllocatedCount"				,"count to allocate Buffer"			);
	SetParam(&UseGeneralStockerToGetPath, /**/"Setting"	,/**/"UseGeneralStockerToGetPath"	,"Use GeneralStocker to get path"	);
	SetParam(&OnlyNG					, /**/"Setting"	,/**/"OnlyNG"						,"Save image of only NG result"		);
	SetParam(&UseLayer					, /**/"Setting"	,/**/"UseLayer"						,"-1:Save all layers ,0-:Only this layer"		);
}

ResultSaveTargetImage::~ResultSaveTargetImage(void)
{
	Terminated=true;
	wait(2000);
}

ExeResult	ResultSaveTargetImage::ExecuteInitialAfterEdit	(int ExeID,ResultInspection *Res)
{
	MutexImageList.lock();
	if(ImageList.GetCount()!=0
	&& ImageList.GetFirst()->GetDotPerLine()!=GetDotPerLine(-1)
	&& ImageList.GetFirst()->GetMaxLines()	!=GetMaxLines(-1)
	&& ImageList.GetFirst()->GetLayerNumb()	!=GetLayerNumb(-1)){
		ImageList.RemoveAll();
	}
	while(ImageList.GetCount()<AllocatedCount){
		ImageBuffersListWithFlag	*a=new ImageBuffersListWithFlag(GetPhaseNumb()
																	,GetPageNumb()
																	,GetLayerNumb(-1)
																	,GetDotPerLine(-1),GetMaxLines(-1));
		ImageList.AppendList(a);
	}
	MutexImageList.unlock();
	if(isRunning()==false){
		start();
	}
	return _ER_true;
}

bool	ResultSaveTargetImage::OutputResultDirectly(int mode ,ResultInspection &Res,GUIDirectMessage *packet)
{
	if(mode==-1){
		bool3	ShouldWrite=false3;

		bool3	ResultOk;
		bool	ResultMaxError,ResultTimeOut;

		ResultPkNgPacket	*ResultPkNgPacketVar=dynamic_cast<ResultPkNgPacket *>(packet);
		if(ResultPkNgPacketVar!=NULL){
			ResultOk=ResultPkNgPacketVar->Ok;
			ResultMaxError	=ResultPkNgPacketVar->MaxError;
			ResultTimeOut	=ResultPkNgPacketVar->TimeOver;
		}
		else{
			Res.GatherResult(ResultOk,ResultMaxError,ResultTimeOut,true,false);
		}

		QString	tSavedFolder	=SavedFolder;
		QString	tSavedFileName;
		QString	SavedFileName;
		if(UseGeneralStockerToGetPath==true){
			QList<QVariant> Arguments;
			QList<QVariant> ReturnedValues;
			Arguments << DiskSpaceToCheck;
			if( true==(GetLayersBase()->GetGeneralStocker()->GetData("GetFolder", ReturnedValues, Arguments)) ){
				if(ReturnedValues.count()>=2){
					tSavedFolder	=ReturnedValues[0].toString();
					tSavedFileName	=ReturnedValues[1].toString();
				}
			}
		}
		if(tSavedFileName.isEmpty()==true){
			tSavedFileName=QDateTime::currentDateTime().toString(/**/"yyMMdd-hhmmss");
		}
		if(OnlyNG==true && ShouldWrite==true3){
			SavedFileName=tSavedFileName + QString(/**/"-NG.pix");
		}
		else if(OnlyNG==false && (ShouldWrite==true3 || ShouldWrite==false3)){
			if(ResultOk==true3)
				SavedFileName=tSavedFileName + QString(/**/"-OK.pix");
			else
				SavedFileName=tSavedFileName + QString(/**/"-NG.pix");
		}
		int	MaxNumber=0;
		for(ImageBuffersListWithFlag *s=ImageList.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->Number>MaxNumber){
				MaxNumber=s->Number;
			}
		}
		MaxNumber++;	
			
		ImageBuffersListWithFlag	*Buff=GetEmptyBuffer();
		if(Buff!=NULL){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				PageDataInOnePhase	*Pd=GetLayersBase()->GetPageDataPhase(phase);
				for(int page=0;page<GetPageNumb();page++){
					DataInPage *Pg=Pd->GetPageData(page);
					for(int layer=0;layer<Pg->GetLayerNumb();layer++){
						DataInLayer	*Ly=Pg->GetLayerData(layer);
						ImageBuffer	*L=Buff->GetBuffer(phase,page,layer);
						if(L!=NULL){
							*L=Ly->GetTargetBuff();
						}
					}
				}
			}
			Buff->FileName=tSavedFolder+::GetSeparator()+SavedFileName;
			Buff->ShouldWrite=true;
			Buff->Number=MaxNumber;
		}
	}
	return true;
}

ImageBuffersListWithFlag	*ResultSaveTargetImage::GetEmptyBuffer(void)
{
	for(ImageBuffersListWithFlag *s=ImageList.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ShouldWrite==false){
			return s;
		}
	}
	return NULL;
}

void	ResultSaveTargetImage::run()
{
	while(GetLayersBase()->GetOnTerminating()==false && Terminated==false){
		MutexImageList.lock();
		ImageBuffersListWithFlag *M=NULL;
		int		OldestNumber=999999999;
		for(ImageBuffersListWithFlag *s=ImageList.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->ShouldWrite==true){
				if(s->Number<OldestNumber){
					OldestNumber=s->Number;
					M	=s;
				}
			}
		}
		if(M!=NULL){
			if(UseLayer<0 || GetLayerNumb(0)<=UseLayer){
				M->WriteOut();
			}
			else{
				M->WriteOut(UseLayer);
			}
			M->ShouldWrite=false;
		}
		MutexImageList.unlock();

		msleep(200);
	}
}
