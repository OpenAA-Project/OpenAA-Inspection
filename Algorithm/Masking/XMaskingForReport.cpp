/*
 * Copyright (C) 2025
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


#include "XMaskingResource.h"
#include "XMasking.h"

class	MaskingTypeList : public NPList<MaskingTypeList>
{
public:
    bool							Effective;		// true=譛牙柑繧ｨ繝ｪ繧｢
    AlgorithmLibraryListContainer	SelAreaID;		// 髯仙ｮ壹�繧ｹ繧ｯ
	int								ItemCount;

	MaskingTypeList(void){	Effective=true;	ItemCount=0;	}
};

void	MaskingBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	NPListPack<MaskingTypeList>	MaskingTypeListContainer;

	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPagePLI	*Pg=(AlgorithmInPagePLI *)GetPageData(page);
		for(int layer=0;layer<Pg->GetLayerNumb();layer++){
			MaskingInLayer	*L=(MaskingInLayer *)Pg->GetLayerData(layer);
			int	N=L->GetItemCount();
			for(int i=0;i<N;i++){
				AlgorithmItemPLI	*item=(AlgorithmItemPLI *)L->GetItemRoot(i);
				const	AlgorithmThreshold	*t=item->GetThresholdBaseReadable();
				MaskingThreshold	*MThre=dynamic_cast<MaskingThreshold *>((AlgorithmThreshold	*)t);
				if(MThre!=NULL){
					bool	Found=false;
					for(MaskingTypeList *m=MaskingTypeListContainer.GetFirst();m!=NULL;m=m->GetNext()){
						if(m->Effective==MThre->Effective && m->SelAreaID==MThre->SelAreaID){
							m->ItemCount++;
							Found=true;
							break;
						}
					}
					if(Found==false){
						MaskingTypeList *mm=new MaskingTypeList();
						mm->Effective	=MThre->Effective;
						mm->SelAreaID	=MThre->SelAreaID;
						mm->ItemCount	=1;
						MaskingTypeListContainer.AppendList(mm);
					}
				}
			}
		}
	}
	for(MaskingTypeList *m=MaskingTypeListContainer.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->Effective==true){
			RetContainer.Add(QString(LangSolver.GetString(XMaskingForReport_LS,LID_19)/*"Effective : "*/)+QString::number(m->SelAreaID.GetCount())
							,QString::number(m->ItemCount));
		}
	}
}
void	MaskingThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XMaskingForReport_LS,LID_20)/*"Effective"*/		,Effective);
	for(AlgorithmLibraryList *a=SelAreaID.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(a->GetLibType());
		if(ABase!=NULL){
			AlgorithmLibraryContainer	*ALibC=ABase->GetLibraryContainer();
			if(ALibC!=NULL){
				QString	LibTypeName=GetLayersBase()->GetLibTypeName(a->GetLibType());
				QString	LibName=ALibC->GetLibraryName(a->GetLibID());
				QString	s=LibTypeName
						 +QString(/**/" : ")
						 +LibName;

				RetContainer.Add(LangSolver.GetString(XMaskingForReport_LS,LID_21)/*"SelAreaID"*/,s);
			}
		}
	}
}