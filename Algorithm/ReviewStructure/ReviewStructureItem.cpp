#include "ReviewStructureItems.h"
#include "XReviewStructure.h"


HistoryItem::HistoryItem(ReviewPIBase *pBase)
{
	PBase=pBase;
	m_NGReader = new NGImageReaderOneFile(PBase->getProperty().NGImagePath
										,pBase->GetParamGlobal()->TransDatabaseIP
										,pBase->GetParamGlobal()->ImageFileCachePort,NULL);
};

void HistoryItem::createReader(void)
{
	if(m_NGReader==NULL){
		m_NGReader = new NGImageReaderOneFile(PBase->getProperty().NGImagePath
											,PBase->GetParamGlobal()->TransDatabaseIP
											,PBase->GetParamGlobal()->ImageFileCachePort
											,NULL);
		m_NGReader->setFilename(m_Filename);
		m_NGReader->setIDXList(m_IDXList);
	}
};

bool	ReviewNGPoint::operator==(const ReviewNGPoint &src)
{
	if(x==src.x && y==src.y && TypeCode==src.TypeCode && LibCode==src.LibCode)
		return true;
	return false;
}