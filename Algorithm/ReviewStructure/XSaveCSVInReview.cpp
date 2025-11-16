#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"


void	ReviewPIBase::InitialCSVLotList(void)
{
	if(CurrentBundle.FocusPoint!=NULL){
		CurrentBundle.FocusPoint->Leaving	=XDateTime::currentDateTime();
	}
	if(CurrentBundle.HistryList.IsEmpty()==false){
		SaveCSV();
	}

	CmdReqMasterDataInfo LoadedMaster(GetLayersBase());
	TransmitDirectly(&LoadedMaster);

	// •\‘¤
	// Ý’è
	//ReciveCmdServerSelectLotList( &SelectLotCmd );
	//LotInfoList	FrontLotList = getLotInfoAllList(Review::Front);
	//LotInfoList	BackLotList = getLotInfoAllList(Review::Back);
	LotInfoItem FrontLot	=getCurrentLotInfo(Review::Front);
	LotInfoItem BackLot		=getCurrentLotInfo(Review::Back);

	// •\‘¤‚Ìî•ñ‚ðŠi”[
	CurrentBundle.MasterIDTop	=getMasterInfo(Review::Front).MasterCode;
	CurrentBundle.MachineIDTop	=getMasterInfo(Review::Front).MachineID;
	CurrentBundle.MasterNameTop	=LoadedMaster.FrontMasterDataInfo.MasterName;
	CurrentBundle.LotTableNameTop	=FrontLot.TableName;
	CurrentBundle.LotNameTop		=FrontLot.LotName;
	
	// — ‘¤
	// Ý’è

	// — ‘¤‚Ìî•ñ‚ðŠi”[
	CurrentBundle.MasterIDBack	=getMasterInfo(Review::Back).MasterCode;
	CurrentBundle.MachineIDBack	=getMasterInfo(Review::Back).MachineID;
	CurrentBundle.MasterNameBack=LoadedMaster.BackMasterDataInfo.MasterName;
	CurrentBundle.LotTableNameBack	=BackLot.TableName;
	CurrentBundle.LotNameBack		=BackLot.LotName;
	
	CurrentBundle.HistryList.RemoveAll();
	CurrentBundle.FocusPoint=NULL;
}


void	ReviewPIBase::SaveBundleOnHistry(int CurrentRow ,int InspectionID ,XDateTime &InspectionTime)
{
	CurrentBundle.CurrentRow	=CurrentRow;
	bool	Found=false;
	for(ForSaveOneInspection *c=CurrentBundle.HistryList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->LineNumber==CurrentBundle.CurrentRow){
			Found=true;
			c->Entering			=XDateTime::currentDateTime();
			c->InspectionID		=InspectionID;
			c->InspectionTime	=InspectionTime;
			break;
		}
	}
	if(Found==false){
		ForSaveOneInspection	*cc=new ForSaveOneInspection();
		cc->Entering		=XDateTime::currentDateTime();
		cc->LineNumber		=CurrentBundle.CurrentRow;
		cc->InspectionID	=InspectionID;
		cc->InspectionTime	=InspectionTime;
		CurrentBundle.HistryList.AppendList(cc);
	}
}


bool	ReviewPIBase::SaveCSV(void)
{
	if(CurrentBundle.HistryList.IsEmpty()==true){
		return true;
	}
	if(m_property.DirectoryToSaveCSV.isEmpty()==true){
		return true;
	}
	QString	FileName=m_property.DirectoryToSaveCSV
					+::GetSeparator()
					//+QString::number(CurrentBundle.MachineIDTop)
					//+QString("-")
					+CurrentBundle.LotTableNameTop
					+QString("++")
					+CurrentBundle.LotNameTop
					+QString(".csv");
	QFileInfo	FInfo(FileName);
	::ForceDirectories(FInfo.path());
	bool	ret= CurrentBundle.SaveCSV(FileName,this);

	QString	ListingFileName=m_property.DirectoryToSaveCSV
					+QString("/ListingReview")
					+QString(".csv");
	CurrentBundle.AppendListing(ListingFileName,FileName);
	return ret;
}

bool	ReviewPIBase::LoadCSV(void)
{
	if(m_property.DirectoryToSaveCSV.isEmpty()==true){
		return true;
	}
	QString	FileName=m_property.DirectoryToSaveCSV
					+::GetSeparator()
					//+QString::number(CurrentBundle.MachineIDTop)
					//+QString("-")
					+CurrentBundle.LotTableNameTop
					+QString("++")
					+CurrentBundle.LotNameTop
					+QString(".csv");
	return CurrentBundle.LoadCSV(FileName);
}