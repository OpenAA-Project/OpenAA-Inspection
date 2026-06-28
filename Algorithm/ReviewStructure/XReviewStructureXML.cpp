/*
 * Copyright (C) 2022
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

#include "XReviewStructure.h"
#include "DXMLParser.h"
#include "ui_XMLServerCommForm.h"
#include <QProgressDialog>
#include <QElapsedTimer>
#include "XGeneralFunc.h"

class XMLWriter;

bool ReviewPIBase::XML_Open()
{
	QElapsedTimer time;
	bool ch;
	qDebug() << /**/"XML_OpenFuncion_Start";
	time.restart();
	if(getXMLServerHandle()->GetState()==true){
		qDebug() << /**/"XML_Open:EndFirst=" << time.elapsed();
		return true;
	}

	time.start();
	ch = getXMLServerHandle()->Open();
	qDebug() << Q_FUNC_INFO << ":server open = " << time.elapsed();

	qDebug() << getXMLServerHandle()->GetState();

	if(ch==true){
		time.restart();
		if(getXMLWriter()->isRunning()==false){
			getXMLWriter()->start();
			//if(xmlWriter->isRunning()==false){
		//	xmlWriter->setReady();

		//	xmlWriter->set(IPAddress, PortNo);

		//	xmlWriter->start();

		//	QTime time;
		//	time.start();

		//	while(1){
		//		static int count=0;
		//		if(xmlWriter->isRunning()==true){
		//			break;
		//		}else if(time.elapsed()>200){
		//			xmlWriter->start();
		//			time.restart();
		//			count++;
		//		}
		//		if(count>10){
		//			QMessageBox::warning(NULL, "XMLServerError", "XMLWriter do not work.");
		//			break;
		//		}
		//	}
		//}
		//if(xmlWriter->getIPAddress()!=IPAddress || xmlWriter->getPort()!=PortNo){
		//	if(xmlWriter->isRunning()){
		//		xmlWriter->stop();
		//		qDebug() << "wait Stop Thread";
		//		while(!xmlWriter->isFinished()){}
		//		xmlWriter->setReady();
		//	}
		//	// ?J????J?n
		//	xmlWriter->open(IPAddress, PortNo);
		//	xmlWriter->start();
		//	QTime timer;
		//	timer.start();
		//	while(timer.elapsed()<50){}
		//	while(!xmlWriter->isRunning()){
		//		xmlWriter->start();
		//		timer.restart();
		//		while(timer.elapsed()>100){}
		//		qDebug() << "Running Check";
		//	}
		//}
			while(!getXMLWriter()->isRunning()){
				if(time.elapsed()>2000){
					return false;
				}
				GSleep(100);
			}// ???
			qDebug() << /**/"XML_Open:EndStopAndRestart=" << time.elapsed();
		}else{
			qDebug() << /**/"XML_Open:EndRestart=" << time.elapsed();
		}
		return true;
	}

	if(getXMLWriter()->isRunning()==true){
		getXMLWriter()->stop();
		qDebug() << /**/"XMLWriter is stopping";
		time.restart();
		bool termed = false;
		while(!getXMLWriter()->isFinished()){
			if(time.elapsed()>2000){
				getXMLWriter()->terminate();
			}
			GSleep(100);
			if(termed==true){
				if(getXMLWriter()->isFinished()==true || time.elapsed()>5000){
					break;
				}
			}
		}
		getXMLWriter()->setReady();
		qDebug() << /**/"XMLWriter was stopped=" << time.elapsed();
	}

	QDialog *xmlCommDlg = new QDialog;
	Ui::XMLServerCommClass ui;
	ui.setupUi(xmlCommDlg);

	ui.leAddress->setText(getXMLServerIPAddress());
	ui.lePort->setText(QString::number(getXMLServerPortNo()));

	GetLayersBase()->CloseProcessingForm();
	QMessageBox mbox;
	mbox.setText("tring to connect...");
	mbox.setStandardButtons(QMessageBox::StandardButton::NoButton);

	do{
		mbox.setVisible(false);

		xmlCommDlg->exec();
		getXMLServerHandle()->Set(ui.leAddress->text(), ui.lePort->text().toInt());
		
		mbox.show();
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	}while(getXMLServerHandle()->Open()==false);
	
	mbox.setVisible(false);
	
	setXMLServerState(ui.leAddress->text(), ui.lePort->text().toInt());

	QFile file(CommSettingFile);
	file.open(QIODevice::WriteOnly);
	::Save(&file, getXMLServerIPAddress());
	::Save(&file, getXMLServerPortNo());
	::Save(&file, getNGImagePath());
	file.close();

	getProperty().XMLServerIPAddress = ui.leAddress->text();
	getProperty().XMLServerPortNo = ui.lePort->text().toInt();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
	
	time.restart();
	qDebug() << /**/"xmlWriter starting";
	getXMLWriter()->set(getXMLServerIPAddress(), getXMLServerPortNo());
	getXMLWriter()->setReady();
	getXMLWriter()->start();
	qDebug() << /**/"xmlWriter started.=" << time.elapsed();
	
	qDebug() << /**/"XML_Open:EndLast";
	return true;
}

bool ReviewPIBase::XML_Open(QString Address, int Port)
{
	if(getXMLServerIPAddress()==Address && getXMLServerPortNo()==Port){
		return XML_Open();
	}else{
		// ???~
		getXMLServerHandle()->Close();
		getXMLWriter()->stop();
		getXMLWriter()->setReady();

		// ???
		getXMLServerHandle()->Set(Address, Port);
		getXMLWriter()->set(Address, Port);
		setXMLServerState(Address, Port);
	}
	return XML_Open();
}

bool ReviewPIBase::XML_Close()
{
	return getXMLServerHandle()->Close();
}

class	RetListDIm
{
public:
	QString	OriginalName;
	QString	TagName;
	int		TailNumber;

	RetListDIm	&operator=(RetListDIm &src);
};
RetListDIm	&RetListDIm::operator=(RetListDIm &src)
{
	OriginalName	=src.OriginalName;
	TagName			=src.TagName;
	TailNumber		=src.TailNumber;
	return *this;
}


bool ReviewPIBase::XML_GetLot(int MasterCode,int MachineID, QStringList &list)
{
	QElapsedTimer time;
	time.start();
	XMLOpener opener(this);
	if(opener.isOpen()==false){
		return false;
	}
	qDebug() << Q_FUNC_INFO << " @ check open:" << MasterCode << "," << MachineID << " = " << time.elapsed() << "ms";

	time.restart();
	QStringList retList;
	QString FolderFilter = QString(/**/"%1-%2").arg(MachineID).arg(MasterCode);
	if(getXMLServerHandle()->EnumTables(FolderFilter, retList)==false)
		return false;
	//
	int	N=retList.count();
	RetListDIm	*Dim=new RetListDIm[N];
	for(int i=0;i<N;i++){
		QString	BodyName;
		Dim[i].OriginalName=retList[i];
		Dim[i].TailNumber	=-1;
		int	n=retList[i].count();
		if(n>0){
			n--;
			QChar	c=retList[i].at(n);
			if(c.isDigit()==true){
				while(retList[i].at(n).isDigit()==true){
					n--;
				}
				QString	NumberStr=retList[i].mid(n+1);
				Dim[i].TagName	 =retList[i].left(n);
				bool	ok;
				Dim[i].TailNumber=NumberStr.toInt(&ok);
				if(ok==false)
					Dim[i].TailNumber=-1;
			}
		}
	}
	bool	Flag;
	do{
		Flag=false;
		for(int i=0;i<N-1;i++){
			if(Dim[i].TagName==Dim[i+1].TagName
			&& Dim[i].TailNumber>=0 && Dim[i+1].TailNumber>=0
			&& Dim[i].TailNumber>Dim[i+1].TailNumber){
				RetListDIm	Tmp;
				Tmp=Dim[i];
				Dim[i]=Dim[i+1];
				Dim[i+1]=Tmp;
				Flag=true;
			}
		}
	}while(Flag==true);

	retList.clear();
	for(int i=0;i<N;i++){
		retList.append(Dim[i].OriginalName);
	}
	delete	[]Dim;

	qDebug() << Q_FUNC_INFO << " @ enum tables:" << MasterCode << "," << MachineID << " = " << time.elapsed() << "ms";

	list = retList;

	return true;
}

void ReviewPIBase::XML_ClearLot(Review::SideType side)
{
	deleteHistoryNGImageReader(side);
	getHistoryList(side).clear();
	getInsLibHash(side).clear();
	clearCurrentLotInfo(side);
	clearRoundCurrentNGNailIterator();
	clearRoundCurrentOrganizedHistoryIterator();
	setCurrentLotInfo(side, LotInfoItem());

	//if(side==Review::Front){
	//	FrontHistoryList.clear();
	//	FrontInsLibHash.clear();
	//	//FrontInsLibSearchHash.clear();
	//	FrontLotFilename.clear();
	//}else if(side==Review::Back){
	//	BackHistoryList.clear();
	//	BackInsLibHash.clear();
	//	//BackInsLibSearchHash.clear();
	//	BackLotFilename.clear();
	//}
	clearPCEList(side);

	updateInsLibSearchHash(side);
	OrganizeHistoryList();
	sortHistoryList();
	sortNGNailList();
}

static	int	RemovedItem=0;

bool ReviewPIBase::XML_SetLotToSide(QString lotFile, Review::SideType side)
{
	// ???b?g??NG?`?F?b?N?????
	if(getXMLWriter()->isEmpty()==false){
		int remainMax = getXMLWriter()->count();
		QProgressDialog progressXML("", "", 0, 100, (QWidget*)GetLayersBase()->GetMainWidget());
		progressXML.setCancelButton(NULL);
		progressXML.setWindowModality(Qt::WindowModal);
		while(getXMLWriter()->isEmpty()==false){
			int remain = getXMLWriter()->count();
			progressXML.setLabelText(QString("XML writer is adding NG checked.\nNG is cheked.\nremain...%1/%2").arg(remain).arg(remainMax));
			progressXML.setValue((remainMax-remain)/qreal(remainMax)*100);
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}

	LotInfoList currentLotInfoList = getLotInfoAllList(side);
	LotInfoItem lotItem;

	QString TableName = Review::makeLotFileName(getMasterInfo(side).MasterCode, getMasterInfo(side).MachineID, lotFile);
	bool ok = false;
	for(int i=0; i<currentLotInfoList.count(); i++){
		if(currentLotInfoList[i].TableName==TableName){
			lotItem = currentLotInfoList[i];
			break;
		}
	}

	if(lotItem.isEmpty()==true){
		lotItem = XML_GetLotInfo(TableName);
		if(lotItem.isEmpty()==true){
			XML_ClearLot(side);
			return false;
		}else{
			currentLotInfoList.append( lotItem );
			setLotInfoAllList( side, currentLotInfoList );
		}
	}

	XMLOpener opener(this);
	if(opener.isOpen()==false){
		return false;
	}

	// XML?t?@?C?????n???h???擾
	XMLOperationHandle *xmlOperatorHdl = getXMLServerHandle()->OpenXMLOperation(lotItem.TableName);
	if(xmlOperatorHdl==NULL){
		return false;
	}

	// ?o??t?H?[?}?b?g?A?????t?H?[?}?b?g????(?f?t?H???g)
	QString outputFormat = /**/"<* *>*</*>";
	QString selectFormat = /**/"<*/>";
	QString orderFormat = /**/"";

	// XML????????o?b?t?@
	QString retStr;
	QStringList strList;
	
	QString processStr;

	// ??????^?[?Q?b?g???

	XML_ClearLot(side);

	QList<HistoryItem> *TagetHistoryList;
	processStr += QString(/**/" [") + Review::toString(side) + QString(/**/"]");
	TagetHistoryList = &getHistoryList(side);

	//============================================================================================
	// PCE
	//

	outputFormat = /**/"<PCE */>";
	selectFormat = /**/"<PCE */>";
	orderFormat = /**/"";
	
	if(xmlOperatorHdl->Select(outputFormat, selectFormat, orderFormat, strList)==false){
		return false;
	}

	PCEList lotPCEList;
	for(int i=0; i<strList.count(); i++){
		LotXMLPCEParser parser;
		if(parser.setContent(strList[i])==true){
			lotPCEList.append(parser.getData());
		}
	}

	setPCEList(side, lotPCEList);

	//============================================================================================
	// LIBCODE
	//

	// ?o?b?t?@????

	InsLibraryHash InsLibHash;

	// ????????N???A
	InsLibHash.clear();

	// ?o??A?????t?H?[?}?b?g?A?\?[?g?w?????????
	outputFormat = /**/"<INSLIB */>";
	selectFormat = /**/"<INSLIB */>";
	orderFormat = /**/"LIBCODE";
	
	if(xmlOperatorHdl->Select(outputFormat, selectFormat, orderFormat, strList)==true){
		// LIBCODE???p?p?[?T
		LotXMLInsLibParser parser;

		GetLayersBase()->ShowProcessingForm("XML:Analyzing Library Infomation",false, strList.size());

		// INSLIB???[?v
		GetLayersBase()->ShowProcessingForm("XML:Analyzing Library Infomation",false, strList.count());
		for(QStringList::ConstIterator it=strList.constBegin(); it!=strList.constEnd(); it++){
			GetLayersBase()->StepProcessing(-1,"XML:Analyzing Library Infomation");
			// ??????????????i?[
			if(parser.setContent(*it)==true){
				// Success
				if(InsLibHash.contains(parser.getData().Ral, parser.getData())==false){
					InsLibHash.insert(parser.getData().Ral, parser.getData());//??????Β??

				}
			}else{
				// Error
				continue;
			}
			GetLayersBase()->StepProcessing(-1);
		}
		GetLayersBase()->CloseProcessingForm();
	}

	// ?Z?b?g
	setInsLibHash(side, InsLibHash);

	//qDebug() << getInsLibHash(side).uniqueKeys();

	updateInsLibSearchHash(side);

	
	// ?o??A?????t?H?[?}?b?g?A?\?[?g?w?????????
	outputFormat = /**/"<* *>*</*>";
	selectFormat = /**/"<IST */>";///**/"<IST><RES>NG</RES></IST>";// NG???
	orderFormat = /**/"EID<INSPECT/>";

	// XMLServer????M
	// FirstNext???[?h
	xmlOperatorHdl->Select(/**/"<Count/>", selectFormat, /**/"", strList);

	if(strList.isEmpty()==true){
		OrganizeHistoryList();
		sortNGNailList();
		GetLayersBase()->CloseProcessingForm();
		return true;
	}

	int ISTCount = XML_CountAnalyze( strList.first() );

	GetLayersBase()->ShowProcessingForm("XML:Receiving Inspection Data from XMLServer",false, ISTCount);

	strList.clear();
	xmlOperatorHdl->SelectFirst(outputFormat, selectFormat, orderFormat, retStr);
	QString ISTStepStr = "Receiving Inspection Data from XMLServer";
	if(retStr==/**/"<BOF/>" || retStr==/**/"<EOF/>"){
		// clear();
		GetLayersBase()->CloseProcessingForm();
		TagetHistoryList->clear();
		OrganizeHistoryList();
		sortNGNailList();
		return true;
	}else{
		do{
			strList.append(retStr);
			GetLayersBase()->StepProcessing(-1,ISTStepStr);
		}while(xmlOperatorHdl->SelectNext(retStr) && retStr!=/**/"<BOF/>" && retStr!=/**/"<EOF/>");
	}

	// IST???p?p?[?T
	LotXMLIstParser IstParser;

	GetLayersBase()->ShowProcessingForm("XML:Analizing inspection data",false, strList.count());
	processStr = "XML:Analyzing Inspection Data";

	// IST???[?v
	for(QStringList::Iterator ist_str=strList.begin(); ist_str!=strList.end(); ist_str++){
		GetLayersBase()->StepProcessing(-1,processStr);
		if(ist_str->isEmpty() || ist_str->isNull()){
			continue;
		}

		// ??????????????i?[
		if(IstParser.setContent((*ist_str))==true){
			// Success
			// IST?O???[?o????????
			ISTInfomation ISTInfo = IstParser.getISTInfo();

			// nail?f?[?^??
			HistoryItem HItem(this);

			// IST??f?[?^?i?[
			HItem.InspectedTime = ISTInfo.ISTDay;// ????
			HItem.Side = side;// ???\ //
			HItem.setInspectID(ISTInfo.InspectID);// ????ID
			HItem.Result = ISTInfo.result;// ????
			HItem.InspectedMachine	=ISTInfo.MachineID;

			// ????????K?v??t?@?C????IDX?　?A???????NG?????v?Z
			HItem.NGCount = 0;// ??????
			QList<int> IDXList;// JDT?t?@?C???????o???????g??
			for(int phase=0; phase<IstParser.getPhaseCount(); phase++){
				for(int page=0; page<IstParser.getPageCount(phase); page++){
					HItem.NGCount += IstParser.getNGPCount(phase, page);

					QList<NGITagData> data = IstParser.getNGIListPack(phase, page);
					for(QList<NGITagData>::ConstIterator it=data.constBegin(); it!=data.constEnd(); it++){
						if(IDXList.contains(it->IDX)==false){
							IDXList.append(it->IDX);
						}
					}
				}
			}

			// XML??????t?@?C??????p?X(*?t??)
			ParamGlobal *param = GetLayersBase()->GetParamGlobal();
			QString filepath;
			//QString filepathhead = GetLayersBase()->GetParamGlobal()->KeepFilteredImage;
			//qDebug() << "Test:" << filepathhead;
			QString		ImageFilePath=getNGImagePath();	//getPropertyUi()->leNGImagePath->text();
			if(ImageFilePath.isEmpty()==true){
				ImageFilePath="Y:";
			}

			QChar	MTop=ISTInfo.NGImageFileFormat.at(0);
			int		MIndex=ISTInfo.NGImageFileFormat.indexOf("NGImage");
			if(MTop==/**/'\\' || MTop==/**/'/' && MIndex>0){
				QString	STmp=ISTInfo.NGImageFileFormat.mid(MIndex);
				ISTInfo.NGImageFileFormat=STmp;
			}

			if(ImageFilePath.isEmpty()==false){
				QChar ch = ImageFilePath.at(ImageFilePath.length()-1);
				if(ch==/**/'\\' || ch==/**/'/'){
					filepath = ImageFilePath + ISTInfo.NGImageFileFormat;
				}else{
					filepath = ImageFilePath + QDir::separator() + ISTInfo.NGImageFileFormat;
				}
			}

			QStringList JDTFileNames;
			for(int iIDX=0; iIDX<IDXList.count(); iIDX++){
				QString repFilename = filepath;
				repFilename.replace(/**/"*", QString::number(IDXList[iIDX]));
				JDTFileNames.append(repFilename);
				if(side==Review::Back){
				}
			}
			HItem.setJDTFilename(filepath);
			HItem.setJDTFileIDXList(IDXList);

			NGNailList NGNails;

			for(int phase=0; phase<IstParser.getPhaseCount(); phase++){
				for(int page=0; page<IstParser.getPageCount(phase); page++){
					QList<NGITagData> NGIList = IstParser.getNGIListPack(phase, page);
					QList<ReviewNGPoint> NGPList = IstParser.getNGPListPack(phase, page);
					
					{
						QList<ReviewNGPoint>::Iterator it;

						//#pragma omp parallel
						//#pragma omp single private(it)
						for(it=NGPList.begin(); it!=NGPList.end(); it++){
							//#pragma omp task
							{
								if(it->TypeCode!=-1){
									it->Tag = getInsLibraryItemTypeNameTag(side, it->Ral, it->LibCode, it->TypeCode);
								}else{
									QString ral = it->Ral;
									int LibCode = it->LibCode;
									QHash<int, QHash<int, InsLibraryItem::TypeNameTag> > ralHash = getInsLibSearchHash(side)[ral];
									//if(ralHash.isEmpty()==false){
									//	qDebug() << ralHash.keys();
									//}
									QHash<int, InsLibraryItem::TypeNameTag> list = ralHash[LibCode];

									QList<int> indexList = list.keys();
									InsLibraryItem::TypeNameTag selectedTag;
									selectedTag.NGPriority = INT_MAX;
									bool found=false;
									for(int i=0; i<indexList.count(); i++){
										InsLibraryItem::TypeNameTag item = list.value(indexList[i]);
										    
										// Qt6のQHashは1キーにつき1つの値なので、内側のループは不要
										if(item.NGPriority < selectedTag.NGPriority){
										    selectedTag = item;
										    found = true;
										}
									}
									if(found==true){
										it->Tag = selectedTag;
									}
								}
								it->PCEItems = getPCEMatch(side, getMasterInfo(side).MachineID, page, it->AraList());
							}
						}
					}

					for(QList<NGITagData>::ConstIterator it=NGIList.constBegin(); it!=NGIList.constEnd(); it++){
						//JDTImage jdtItem;
						//files[IDXList.indexOf(it->IDX)].findImage(it->x, it->y, jdtItem);// ????f?[?^?????????????C???X?^???X
						// ?f?[?^??i?[
						NGNailItem nail;
						nail.TargetPosX = it->x;
						nail.TargetPosY = it->y;
						nail.MasterPosX = it->x;// - it->AlignedX;
						nail.MasterPosY = it->y;// - it->AlignedY;
						nail.NGImageWidth = it->width;
						nail.NGImageHeight = it->height;
						nail.page = IstParser.getISTData()[phase][page].currentPage();
						nail.phase = IstParser.getISTData()[phase][page].parentPhase();
						nail.isChecked = it->isChecked;
						nail.FKey = it->FKey;
						nail.IDX = it->IDX;

						QPoint p = getMasterWholePageOutline(getCurrentSideType(), nail.phase, nail.page);
						nail.OutlineOffsetX=p.x();
						nail.OutlineOffsetY=p.y();

						//nail.NGImageFilename = JDTFileNames[IDXList.indexOf(it->IDX)];

						//NGImageReader *reader = new NGImageReader;
						//reader->setFilename(JDTFileNames[IDXList.indexOf(it->IDX)]);
						//reader->setPos(it->x, it->y);

						//nail.NGImage = reader;// ??????X???b?h??C???X?^???X???Z?b?g

						//qDebug() << reader->filename();
						//qDebug() << reader->pos();

						//reader->image().save("test.png", "PNG");

						{
						int NGPCount = NGPList.count();
						QVector<bool> apFlag(NGPCount, false);

						#pragma omp parallel
						{
							int i;
							#pragma omp single private(i)
							for(i=0; i<NGPCount; i++){
								#pragma omp task
								{
									//int	Gx=NGPList[i].x-NGPList[i].ItemSearchedX-NGPList[i].AlignedX;
									//int	Gy=NGPList[i].y-NGPList[i].ItemSearchedY-NGPList[i].AlignedY;
									int	Gx=NGPList[i].x;
									int	Gy=NGPList[i].y;
									if(Gx >= it->x &&
										(Gx - it->x) <= it->width &&
										Gy >= it->y &&
										(Gy - it->y) <= it->height){
										apFlag[i] = true;
									}
								}
							}
						}
						
						for(int i=0; i<NGPCount; i++){
							if(apFlag[i] == true){
								nail.NGPointList.append(NGPList[i]);
							}
						}
						}

						// ?A???S???Y????f?[?^??i?[
						if(nail.NGPointList.count()>0){
							bool	AllMatched=false;
							for(int d=0;d<NGNails.count();d++){
								bool	Matched=true;
								for(int i=0;i<NGNails[d].NGPointList.count();i++){
									bool	Found=false;
									ReviewNGPoint	dp=NGNails[d].NGPointList[i];
									for(int j=0;j<nail.NGPointList.count();j++){
										if(dp==nail.NGPointList[j]){
											Found=true;
											break;
										}
									}
									if(Found==false){
										Matched=false;
										break;
									}
								}
								if(Matched==true){
									AllMatched=true;
									break;
								}
							}
							if(AllMatched==false){
								NGNails.append( nail );
							}
							else{
								RemovedItem++;
							}
						}
					}
				}
			}
			HItem.setNGNails(NGNails);
			TagetHistoryList->append(HItem);
		}else{
			// Error
			continue;
		}
	}
	GetLayersBase()->CloseProcessingForm();

	std::sort(TagetHistoryList->begin(), TagetHistoryList->end());// ID????\?[?g
	OrganizeHistoryList();
	sortHistoryList();
	sortNGNailList();
	
	delete xmlOperatorHdl;

	setCurrentLotInfo(side, lotItem);

	//setCurrentLotTableName(side, lotFile);// ex)"0-389/2011-11-28--17-43-43"

	return true;
}

int	ReviewPIBase::XML_CountAnalyze(const QString &CountXML)
{
	if(CountXML.length()<2){
		return -1;
	}
	
	QString retStr = CountXML.mid(CountXML.indexOf(/**/'\"')+1);
	retStr = retStr.left(retStr.lastIndexOf(/**/'\"'));

	bool ok;
	int count;
	count = retStr.toInt(&ok);

	if(ok==true){
		return count;
	}else{
		return -1;
	}
}