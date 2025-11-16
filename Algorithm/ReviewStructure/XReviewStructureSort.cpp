#include "XReviewStructure.h"

bool ReviewPIBase::CompYLesser(const NGNailItem &item1, const NGNailItem &item2)
{
	if(item1.TargetPosY == item2.TargetPosY){
		return item1.TargetPosX > item2.TargetPosX;
	}else{
		return item1.TargetPosY > item2.TargetPosY;
	}
}

bool ReviewPIBase::CompYGreater(const NGNailItem &item1, const NGNailItem &item2)
{
	return !CompYLesser(item1, item2);
}

bool ReviewPIBase::CompXLesser(const NGNailItem &item1, const NGNailItem &item2)
{
	if(item1.TargetPosX+item1.OutlineOffsetX == item2.TargetPosX+item2.OutlineOffsetX){
		return item1.TargetPosY+item1.OutlineOffsetY > item2.TargetPosY+item2.OutlineOffsetY;
	}else{
		return item1.TargetPosX+item1.OutlineOffsetX > item2.TargetPosX+item2.OutlineOffsetX;
	}
}

bool ReviewPIBase::CompXGreater(const NGNailItem &item1, const NGNailItem &item2)
{
	return !CompXLesser(item1, item2);
}

bool ReviewPIBase::CompLibTypeLesser(const NGNailItem &item1, const NGNailItem &item2)
{
	if(item1.getLibraryRal() != item2.getLibraryRal()){
		return (item1.getLibraryRal() > item2.getLibraryRal());
	}else{
		return CompYLesser(item1, item2);
	}
}

bool ReviewPIBase::CompLibTypeGreater(const NGNailItem &item1, const NGNailItem &item2)
{
	return !CompLibTypeLesser(item1, item2);
}

bool ReviewPIBase::CompNGCauseLesser(const NGNailItem &item1, const NGNailItem &item2)
{
	if(item1.getLibraryCode() != item2.getLibraryCode()){
		return (item1.getLibraryCode() > item2.getLibraryCode());
	}else{
		return CompYLesser(item1, item2);
	}
}

bool ReviewPIBase::CompNGCauseGreater(const NGNailItem &item1, const NGNailItem &item2)
{
	return !CompNGCauseLesser(item1, item2);
}
bool ReviewPIBase::CompArea(const NGNailItem &item1, const NGNailItem &item2)
{
	if(item1.getArea().isEmpty()==true){
		if(item2.getArea().isEmpty()==true){
			return CompYLesser(item1, item2);
		}
		return false;
	}
	if(item2.getArea().isEmpty()==true){
		return true;
	}
	if(item1.getArea()==item2.getArea()){
		return CompYLesser(item1, item2);
	}
	return (item1.getArea() < item2.getArea());
}

bool ReviewPIBase::CompPhaseLesser(const NGNailItem &item1, const NGNailItem &item2)
{
	return item1.phase > item2.phase;
}

bool ReviewPIBase::CompPhaseGreater( const NGNailItem &item1, const NGNailItem &item2)
{
	return !CompPhaseLesser(item1, item2);
}

bool ReviewPIBase::CompHistoryInspectIDGreater(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return item1.getInspectID() < item2.getInspectID();
}

bool ReviewPIBase::CompHistoryInspectIDLesser(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return !CompHistoryInspectIDGreater(item1, item2);
}

bool ReviewPIBase::CompHistoryInspectTimeGreater(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return item1.getInspectedTime() < item2.getInspectedTime();
}

bool ReviewPIBase::CompHistoryInspectTimeLesser(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return !CompHistoryInspectTimeGreater(item1, item2);
}

bool ReviewPIBase::CompHistoryNGCountGreater(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	int count1 = 0;
	int count2 = 0;

	if(item1.hasFront()){
		count1 += item1.getFront()->NGCount;
	}
	if(item1.hasBack()){
		count1 += item1.getBack()->NGCount;
	}
	if(item2.hasFront()){
		count2 += item2.getFront()->NGCount;
	}
	if(item2.hasBack()){
		count2 += item2.getBack()->NGCount;
	}

	return count1 < count2;
}

bool ReviewPIBase::CompHistoryNGCountLesser(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return !CompHistoryNGCountGreater(item1, item2);
}

bool ReviewPIBase::CompHistoryNGCountOnlyFrontGreater(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	if(item1.hasFront()==false && item2.hasFront()==false){
		return true;
	}
	if(item1.hasFront()==true && item2.hasFront()==true){
		return item1.getFront()->NGCount < item2.getFront()->NGCount;
	}
	if(item1.hasFront()==true && item2.hasFront()==false){
		return true;
	}
	if(item1.hasFront()==false && item2.hasFront()==true){
		return false;
	}
	return true;
}

bool ReviewPIBase::CompHistoryNGCountOnlyFrontLesser(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return !CompHistoryNGCountOnlyFrontGreater(item1, item2);
}

bool ReviewPIBase::CompHistoryNGCountOnlyBackGreater(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	if(item1.hasBack()==false && item2.hasBack()==false){
		return true;
	}
	if(item1.hasBack()==true && item2.hasBack()==true){
		return item1.getBack()->NGCount < item2.getBack()->NGCount;
	}
	if(item1.hasBack()==true && item2.hasBack()==false){
		return true;
	}
	if(item1.hasBack()==false && item2.hasBack()==true){
		return false;
	}
	return true;
}

bool ReviewPIBase::CompHistoryNGCountOnlyBackLesser(const OrganizedHistoryItem &item1, const OrganizedHistoryItem &item2)
{
	return !CompHistoryNGCountOnlyBackGreater(item1, item2);
}

QList<int> ReviewPIBase::createNGNailListPhaseBorder(NGNailList &list)
{
	QList<int> retList;
	int currentPhase=INT_MIN;
	for(int i=0; i<list.count(); i++){
		if(currentPhase!=list[i].phase){
			retList.append(i);
			currentPhase=list[i].phase;
		}
	}
	if(retList.isEmpty()==false){
		retList.append(list.count());
	}
	return retList;
}

void ReviewPIBase::sortNGNailList()
{
	#pragma omp for
	for(int i=0; i<getOrganizedHistoryList().count(); i++){
		OrganizedHistoryList::Iterator it = getOrganizedHistoryIterator(i);
		if(it->hasFront()==true){
			qStableSort(it->getFront()->getNGNails().begin(), it->getFront()->getNGNails().end(), CompPhaseGreater);
		}
		if(it->hasBack()==true){
			qStableSort(it->getBack()->getNGNails().begin(), it->getBack()->getNGNails().end(), CompPhaseGreater);
		}
	}

	bool (*compFunc)(const NGNailItem &, const NGNailItem &);

	switch(getProperty().NGNailListSortOrder){
	case Review::OrderOfSortNG::_Order_YLesser:
		compFunc = CompYLesser;
		break;
	case Review::OrderOfSortNG::_Order_YGreater:
		compFunc = CompYGreater;
		break;
	case Review::OrderOfSortNG::_Order_XLesser:
		compFunc = CompXLesser;
		break;
	case Review::OrderOfSortNG::_Order_XGreater:
		compFunc = CompXGreater;
		break;
	case Review::OrderOfSortNG::_Order_NGCauseLesser:
		compFunc = CompNGCauseLesser;
		break;
	case Review::OrderOfSortNG::_Order_NGCauseGreater:
		compFunc = CompNGCauseGreater;
		break;
	case Review::OrderOfSortNG::_Order_LibTypeLesser:
		compFunc = CompLibTypeLesser;
		break;
	case Review::OrderOfSortNG::_Order_LibTypeGreater:
		compFunc = CompLibTypeGreater;
		break;
	case Review::OrderOfSortNG::_Order_Area:
		compFunc = CompArea;
		break;
	default:
		// 
		return;
		break;
	}

	int histryCount = getOrganizedHistoryList().count();
	OrganizedHistoryList::Iterator it,beginIt,endIt;
	beginIt = getOrganizedHistoryIteratorBegin();
	endIt = getOrganizedHistoryIteratorEnd();

	for(OrganizedHistoryList::Iterator it=beginIt; it!=endIt; it++){
		if(it->hasFront()==true){
			QList<int> borderList = createNGNailListPhaseBorder(it->getFront()->getNGNails());
			for(int i=0; i<borderList.count()-1; i++){
				qStableSort(it->getFront()->getNGNails().begin() + borderList[i],
					it->getFront()->getNGNails().begin() + borderList[i+1], compFunc);
			}
		}
		if(it->hasBack()==true){
			QList<int> borderList = createNGNailListPhaseBorder(it->getBack()->getNGNails());
			for(int i=0; i<borderList.count()-1; i++){
				qStableSort(it->getBack()->getNGNails().begin() + borderList[i],
					it->getBack()->getNGNails().begin() + borderList[i+1], compFunc);
			}
		}
	}

	//switch(state().NGNailListSortOrder){
	//case Review::OrderOfSortNG::_Order_FromBottomLeftToRight:
	//	#pragma omp for
	//	for(int i=0; i<histryCount; i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompFromBottomLeftToRight);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompFromBottomLeftToRight);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompFromBottomLeftToRight);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompFromBottomLeftToRight);
	//		}
	//	}
	//	break;
	//case Review::OrderOfSortNG::_Order_FromTopLeftToRight:
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack.count(); i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompFromTopLeftToRight);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompFromTopLeftToRight);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompFromTopLeftToRight);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompFromTopLeftToRight);
	//		}
	//	}
	//	break;
	//case Review::OrderOfSortNG::_Order_NGCauseLesser:
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack.count(); i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompNGCauseLesser);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompNGCauseLesser);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompNGCauseLesser);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompNGCauseLesser);
	//		}
	//	}
	//	break;
	//case Review::OrderOfSortNG::_Order_NGCauseGreater:
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack.count(); i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompNGCauseGreater);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompNGCauseGreater);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompNGCauseGreater);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompNGCauseGreater);
	//		}
	//	}
	//	break;
	//case Review::OrderOfSortNG::_Order_LibTypeLesser:
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack.count(); i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompLibTypeLesser);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompLibTypeLesser);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompLibTypeLesser);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompLibTypeLesser);
	//		}
	//	}
	//	break;
	//case Review::OrderOfSortNG::_Order_LibTypeGreater:
	//	#pragma omp for
	//	for(int i=0; i<HistoryPack.count(); i++){
	//		if(HistoryPack[i].hasFront()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getFront()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getFront()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getFront()->getNGNails().begin() + borderList[j+1], CompLibTypeGreater);
	//			}
	//			//qStableSort(HistoryPack[i].getFront()->NGNails.begin(), HistoryPack[i].getFront()->NGNails.end(), CompLibTypeGreater);
	//		}
	//		if(HistoryPack[i].hasBack()==true){
	//			QList<int> borderList = createNGNailListPhaseBorder(HistoryPack[i].getBack()->getNGNails());
	//			for(int j=0; j<borderList.count()-1; j++){
	//				qStableSort(HistoryPack[i].getBack()->getNGNails().begin() + borderList[j],
	//					HistoryPack[i].getBack()->getNGNails().begin() + borderList[j+1], CompLibTypeGreater);
	//			}
	//			//qStableSort(HistoryPack[i].getBack()->NGNails.begin(), HistoryPack[i].getBack()->NGNails.end(), CompLibTypeGreater);
	//		}
	//	}
	//	break;
	//default:
	//	// ������Ȃ�
	//	break;
	//}
}

void ReviewPIBase::sortHistoryList()
{
	OrganizedHistoryList::Iterator beginIt,endIt;
	beginIt = getOrganizedHistoryIteratorBegin();
	endIt = getOrganizedHistoryIteratorEnd();

	bool (*compFunc)(const OrganizedHistoryItem &, const OrganizedHistoryItem &);

	switch(getHistorySortOrder()){
	case Review::OrderOfSortHistory::_Order_InspectionIDGreater:
		compFunc = CompHistoryInspectIDGreater;
		break;
	case Review::OrderOfSortHistory::_Order_InspectionIDLesser:
		compFunc = CompHistoryInspectIDLesser;
		break;
	case Review::OrderOfSortHistory::_Order_InspectionTimeGreater:
		compFunc = CompHistoryInspectTimeGreater;
		break;
	case Review::OrderOfSortHistory::_Order_InspectionTimeLesser:
		compFunc = CompHistoryInspectTimeLesser;
		break;
	case Review::OrderOfSortHistory::_Order_NGCountGreater:
		compFunc = CompHistoryNGCountGreater;
		break;
	case Review::OrderOfSortHistory::_Order_NGCountLesser:
		compFunc = CompHistoryNGCountLesser;
		break;
	case Review::OrderOfSortHistory::_Order_NGCount_OnlyFrontGreater:
		compFunc = CompHistoryNGCountOnlyFrontGreater;
		break;
	case Review::OrderOfSortHistory::_Order_NGCount_OnlyFrontLesser:
		compFunc = CompHistoryNGCountOnlyFrontLesser;
		break;
	case Review::OrderOfSortHistory::_Order_NGCount_OnlyBackGreater:
		compFunc = CompHistoryNGCountOnlyBackGreater;
		break;
	case Review::OrderOfSortHistory::_Order_NGCount_OnlyBackLesser:
		compFunc = CompHistoryNGCountOnlyBackLesser;
		break;
	default:
		return;
		break;
	}

	qStableSort(beginIt, endIt, compFunc);
}
