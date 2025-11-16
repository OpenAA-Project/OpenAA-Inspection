#include "PropertyDotRegulationFormResource.h"
#include "PropertyDotRegulationForm.h"
#include "XPropertyDotRegulationPacket.h"
#include "XDisplayImage.h"
#include <QString.h>

extern	char	*sRoot;
extern	char	*sName;

PropertyDotRegulationForm::PropertyDotRegulationForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
}

PropertyDotRegulationForm::~PropertyDotRegulationForm()
{

}
void	PropertyDotRegulationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddDotRegulationAreaPacket	*AddDotRegulationAreaPacketVar=dynamic_cast<AddDotRegulationAreaPacket *>(packet);
	if(AddDotRegulationAreaPacketVar!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(AddDotRegulationAreaPacketVar->Area ,PageList);
		if(PageN<=0)
			return;

		for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
			int	LocalPage=PList->GetValue();
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

			FlexArea	A=AddDotRegulationAreaPacketVar->Area;
			GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
			GUICmdReqAddDotRegulationArea	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
			DNewMsg.Area=A;
			DNewMsg.Layers=AddDotRegulationAreaPacketVar->Layers;
			DNewMsg.Send(NULL,globalPage ,0);
		}
		return;
	}
}
void PropertyDotRegulationForm::on_pushButtonPickup_clicked()
{
	int	Thre=ui.spinBoxThreshold->value();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotRegulationImagePanel" ,/**/"");
	DisplayImageWithAlgorithm	*ImgPanel=(DisplayImageWithAlgorithm	*)GProp;
	IntList	LayerList;
	ImgPanel->GetActiveLayerList(LayerList);

	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			int	Layer=L->GetValue();

			GUICmdReqPickup	DMsg(GetLayersBase(),sRoot,sName,globalPage);
			DMsg.Threshold=Thre;
			DMsg.Layer=Layer;
			DMsg.Send(NULL,globalPage ,0);
		}
	}
	ImgPanel->repaint();
}

QList<qreal> removeLargeDiff(const QList<qreal> &list, qreal threshold)
{
	QList<qreal> ret;
	QList<qreal> buff;
	
	qreal average = 0;
	for(int i=0; i<list.count()-1; i++){
		average += (list[i+1] - list[i]);
		buff << (list[i+1] - list[i]);
	}
	average /= list.count();

	for(int i=0; i<list.count()-1; i++){
		if(qAbs(buff[i] - average)<threshold){
			ret << buff[i];
		}
	}

	return ret;
}

void PropertyDotRegulationForm::on_pushButtonXPosList_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotRegulationImagePanel" ,/**/"");
	DisplayImageWithAlgorithm	*ImgPanel=(DisplayImageWithAlgorithm	*)GProp;
	IntList	LayerList;
	ImgPanel->GetActiveLayerList(LayerList);

	QString	FileName=QFileDialog::getSaveFileName ( 0, LangSolver.GetString(PropertyDotRegulationForm_LS,LID_0)/*"XPos"*/
														, /**/"", /**/"text files(*.txt)");
	if(FileName.isNull()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly | QIODevice::Text)==true){
			QTextStream		Txt(&File);
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
					int	Layer=L->GetValue();
					
					GUICmdReqXPosList	DMsg(GetLayersBase(),sRoot,sName,globalPage);
					GUICmdAckXPosList	AMsg(GetLayersBase(),sRoot,sName,globalPage);
					DMsg.Layer=Layer;
					if(DMsg.Send(globalPage,0,AMsg)==true){
						QList<qreal> list;
						for(int i=0;i<AMsg.List.count();i++){
							list << AMsg.List[i];
							//Txt<<QString::number(AMsg.List[i])<<QString("\r\0d");
						}

						list = removeLargeDiff(list, 5);

						qreal average = 0;

						for(int i=0; i<list.count(); i++){
							average += list[i];
							Txt<<QString::number(list[i])<<Qt::endl;
						}
						Txt<< /**/"Sum,"<<QString::number(average)<<Qt::endl;
						Txt<< /**/"Average,"<<QString::number(average/list.count())<<Qt::endl;//QString("\r\0d");
						Txt<< /**/"Resolution,"<<1000.0/(average/list.count())<<Qt::endl;
					}
				}
			}
		}
	}
}

void PropertyDotRegulationForm::on_pushButtonYPosList_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotRegulationImagePanel" ,/**/"");
	DisplayImageWithAlgorithm	*ImgPanel=(DisplayImageWithAlgorithm	*)GProp;
	IntList	LayerList;
	ImgPanel->GetActiveLayerList(LayerList);

	QString	FileName=QFileDialog::getSaveFileName ( 0, LangSolver.GetString(PropertyDotRegulationForm_LS,LID_1)/*"YPos"*/);
	if(FileName.isNull()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			QTextStream		Txt(&File);
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
					int	Layer=L->GetValue();
					
					GUICmdReqYPosList	DMsg(GetLayersBase(),sRoot,sName,globalPage);
					GUICmdAckYPosList	AMsg(GetLayersBase(),sRoot,sName,globalPage);
					DMsg.Layer=Layer;
					if(DMsg.Send(globalPage,0,AMsg)==true){
						QList<qreal> list;
						for(int i=0;i<AMsg.List.count();i++){
							list << AMsg.List[i];
							//Txt<<QString::number(AMsg.List[i])<<QString("\r\0d");
						}

						list = removeLargeDiff(list, 5);

						qreal average = 0;

						for(int i=0; i<list.count(); i++){
							average += list[i];
							Txt<<QString::number(list[i])<<Qt::endl;
						}
						Txt<< /**/"Sum,"<<QString::number(average)<<Qt::endl;
						Txt<< /**/"Average,"<<QString::number(average/list.count())<<Qt::endl;//QString("\r\0d");
						Txt<< /**/"Resolution,"<<1000.0/(average/list.count())<<Qt::endl;
					}
				}
			}
		}
	}
}

void PropertyDotRegulationForm::on_pushButtonBrightness_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotRegulationImagePanel" ,/**/"");
	DisplayImageWithAlgorithm	*ImgPanel=(DisplayImageWithAlgorithm	*)GProp;
	IntList	LayerList;
	ImgPanel->GetActiveLayerList(LayerList);

	QString	FileName=QFileDialog::getSaveFileName ( 0, LangSolver.GetString(PropertyDotRegulationForm_LS,LID_2)/*"Brightness"*/);
	if(FileName.isNull()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			QTextStream		Txt(&File);
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
					int	Layer=L->GetValue();
					
					GUICmdReqBrightnessList	DMsg(GetLayersBase(),sRoot,sName,globalPage);
					GUICmdAckBrightnessList	AMsg(GetLayersBase(),sRoot,sName,globalPage);
					DMsg.Layer=Layer;
					if(DMsg.Send(globalPage,0,AMsg)==true){
						for(int L=0;L<AMsg.List.count();L++){
							for(int C=0;C<AMsg.List.GetColumnCount(L);C++){
								if(C!=0)
									Txt<</**/",";
								Txt<<AMsg.List.Get(C,L);
							}
							Txt<</**/"\r\n";
						}
					}
				}
			}
		}
	}

}
