#include "DXMLParser.h"

void LotXMLPCEParser::analyze(QDomElement &elem)
{
	m_data.clear();
	errMsg.clear();
	if(elem.tagName().toUpper()==/**/"PCE"){
		bool ok = true;
		if(elem.hasAttribute(/**/"PAGE")==false){
			errMsg = "PCE：要素[PAGE]は必ず記述されていなければなりません\n";
			ok = false;
		}
		if(elem.hasAttribute(/**/"AREA")==false){
			errMsg += "PCE：要素[AREA]は必ず記述されていなければなりません\n";
			ok = false;
		}
		if(ok==false){
			return;
		}

		m_data.setMasterID(elem.attribute(/**/"MASTER", /**/"-1").toInt());
		m_data.setPage(elem.attribute(/**/"PAGE", /**/"-1").toInt());
		m_data.setPieceID(elem.attribute(/**/"PIECEID", /**/"-1").toInt());
		m_data.setPieceName(elem.attribute(/**/"PIECENAME", /**/""));
		
		if(elem.hasAttribute(/**/"AREA")==true){
			QString area = elem.attribute(/**/"AREA");
			if(area.isEmpty()==false){
				uchar type = area.at(0).cell();
				switch(type){
				case 'R':
					m_data.setAreaType(PCEItem::AreaType::Rect);
					break;
				case 'E':
					m_data.setAreaType(PCEItem::AreaType::Ellipse);
					break;
				case 'P':
					m_data.setAreaType(PCEItem::AreaType::Polygon);
					break;
				case 'T':
					m_data.setAreaType(PCEItem::AreaType::RotateEllipse);
					break;
				case 'G':
					m_data.setAreaType(PCEItem::AreaType::Ring);
					break;
				default:
					m_data.setAreaType(PCEItem::AreaType::None);
					break;
				}

				if(type=='R' || type=='E' || type=='P' || type=='G'){
					if(area.length()>1){
						QStringList list = area.mid(1).split(',');
						QList<QPoint> posList;
						for(int i=0; i<list.count()-1; i+=2){
							QPoint p;
							p.setX(list[i].toInt());
							p.setY(list[i+1].toInt());
							posList.append(p);
						}
						m_data.setAreaPointList(posList);
					}
				}else if(type=='T'){
					if(area.length()>1){
						QStringList list = area.mid(1).split(',');
						QList<QPoint> posList;
						if(list.count()>=5){
							for(int i=0; i<list.count()-1; i+=2){
								QPoint p;
								p.setX(list[i].toInt());
								p.setY(list[i+1].toInt());
								posList.append(p);
							}
							m_data.setAreaPointList(posList);
							if(list.count()%2!=0){
								m_data.setRotate(list.last().toInt());
							}
						}
					}
				}
			}
		}

		m_data.setReserveData(elem.attribute(/**/"RESV", /**/""));
	}
}

void LotXMLInsLibParser::analyze(QDomElement &elem){
	data.TypeNameList.clear();
	data.Ral = /**/"";
	data.LibCode = -1;
	data.LibName = /**/"";
	if(elem.tagName().toUpper()==/**/"INSLIB"){
		if(!elem.hasAttribute(/**/"RAL")){
			errMsg = "INSLIB：要素[RAL]は必ず記述されていなければなりません";
			return;
		}else{
			data.Ral = elem.attribute(/**/"RAL");
		}
		data.LibCode = elem.attribute(/**/"LIBCODE", /**/"-1").toInt();

		if(!elem.hasAttribute(/**/"LIBNAME")){
			errMsg = "INSLIB：要素[LIBNAME]は必ず記述されていなければなりません";
			return;
		}else{
			data.LibName = elem.attribute(/**/"LIBNAME");
		}

		LotXMLInsLibTypeNameParser TypeNameParser;// TYPENAMEタグXML専用パーサインスタンス作成
		TypeNameParser.analyze(elem);// XMLをパース
		data.TypeNameList.append(TypeNameParser.getData());// 作成されたデータを追加

		//if(elem.hasChildNodes()==true){// 子XML存在
		//	for(QDomElement libChildElem = elem.firstChildElement(); !libChildElem.isNull(); libChildElem = libChildElem.nextSiblingElement()){// 各子XML
		//		if(elem.tagName()=="TYPENAME"){// 子XMLのタグがTYPENAMEだった場合
		//			LotXMLInsLibTypeNameParser TypeNameParser;// TYPENAMEタグXML専用パーサインスタンス作成
		//			TypeNameParser.analyze(elem);// XMLをパース
		//			data.TypeNameList.append(TypeNameParser.getData());// 作成されたデータを追加
		//		}
		//	}
		//}
	}
}

void LotXMLInsLibParser::LotXMLInsLibTypeNameParser::analyze(QDomElement &elem){
	data.clear();
	//if(elem.tagName().toUpper()=="TYPENAME"){
		data.TCode = elem.attribute(/**/"TCODE", /**/"-1").toInt();
		data.TName = elem.attribute(/**/"TNAME", /**/"");
		if(elem.hasAttribute(/**/"NGCOLOR")){
			QStringList rgbList = elem.attribute(/**/"NGCOLOR").split(/**/",", QString::SplitBehavior::SkipEmptyParts);
			int r = rgbList[0].toInt();
			int g = rgbList[1].toInt();
			int b = rgbList[2].toInt();
			data.NGColor = QColor(qRgb(r,g,b));
		}else{
			data.NGColor = QColor(Qt::red);
		}
		if(elem.hasAttribute(/**/"NGSHAPE")){
			QString shape = elem.attribute(/**/"NGSHAPE");
			if(shape.toLower()==/**/"circle"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Circle;
			}else if(shape.toLower()==/**/"filled circle"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_FilledCircle;
			}else if(shape.toLower()==/**/"rectangle"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Rectangle;
			}else if(shape.toLower()==/**/"filled rectangle"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_FilledRect;
			}else if(shape.toLower()==/**/"x"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_X;
			}else if(shape.toLower()==/**/"star"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Star;
			}else if(shape.toLower()==/**/"filled star"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_FilledStar;
			}else if(shape.toLower()==/**/"cross"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Cross;
			}else if(shape.toLower()==/**/"sharp"){
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Sharp;
			}else{
				data.NGShape = LibNGTypeItem::NGShapeType::NG_Circle;
			}
		}else{
			data.NGShape = LibNGTypeItem::NGShapeType::NG_Circle;
		}
		data.NGBlink = elem.attribute(/**/"NGBLINK", /**/"0").toInt();
		data.NGPriority = elem.attribute(/**/"NGPRIORITY", /**/"0").toInt();
		data.Wait = elem.attribute(/**/"WAIT", /**/"0").toInt();
	//}
}

void LotXMLNgpParser::analyze(QDomElement &elem){
	QString tag = elem.tagName();
	if(tag.toUpper()==/**/"NGP"){
		QStringList errList;
		
		Data.x = elem.attribute(/**/"X", /**/"-1").toInt();
		if(Data.x==-1){
			errList << "NGP : 要素[X]は必ず記述されていなければなりません";
		}
		
		Data.y = elem.attribute(/**/"Y", /**/"-1").toInt();
		if(Data.y==-1){
			errList << "NGP : 要素[Y]は必ず記述されていなければなりません";
		}

		Data.AlignedX = elem.attribute(/**/"MX", /**/"0").toInt();
		Data.AlignedY = elem.attribute(/**/"MY", /**/"0").toInt();
		Data.ItemSearchedX = elem.attribute(/**/"HX", /**/"0").toInt();
		Data.ItemSearchedY = elem.attribute(/**/"HY", /**/"0").toInt();
		Data.LibCode = elem.attribute(/**/"LC", /**/"-1").toInt();
		Data.TypeCode = elem.attribute(/**/"TC", /**/"-1").toInt();
		Data.result1 = elem.attribute(/**/"RS1", /**/"-1").toInt();
		Data.result2 = elem.attribute(/**/"RS2", /**/"-1").toInt();
		Data.Ral = elem.attribute(/**/"RAL", /**/"");
		Data.Ly = elem.attribute(/**/"LY", /**/"-1").toInt();
		Data.Ara = elem.attribute(/**/"ARA", /**/"");

		for(int i=0; i<errList.size(); i++){// エラーの数だけメッセージに追加 エラーが無ければ何もしない
			errMsg += errList[i] + /**/'\n';
		}
		return;
	}else{
		errMsg = "このXML構文は \"NGP\" のタグで始まっていません";
		return;
	}
}

void LotXMLNgiParser::analyze(QDomElement &elem){
	QString tag;
	tag = elem.tagName();
	if(tag.toUpper()==/**/"NGI"){
		QStringList errList;
		Data.x = elem.attribute(/**/"X", /**/"-1").toInt();
		if(Data.x==-1){
			errList << "NGP : 要素[X]は必ず記述されていなければなりません";
		}

		Data.y = elem.attribute(/**/"Y", /**/"-1").toInt();
		if(Data.y==-1){
			errList << "NGP : 要素[Y]は必ず記述されていなければなりません";
		}

		Data.width = elem.attribute(/**/"W", /**/"-1").toInt();
		Data.height = elem.attribute(/**/"H", /**/"-1").toInt();
		Data.IDX = elem.attribute(/**/"IDX", /**/"-1").toInt();
		Data.Index = elem.attribute(/**/"Index", /**/"-1").toInt();
		Data.AlignedX = elem.attribute(/**/"MX", /**/"0").toInt();
		Data.AlignedY = elem.attribute(/**/"MY", /**/"0").toInt();
		Data.isChecked = ((elem.attribute(/**/"Checked", /**/"0").toInt()==1) ? true : false);
		Data.FKey = Review::IntToFKey(elem.attribute(/**/"FK", QString::number(Review::FKeyToInt(Review::NoFKey))).toInt());

		for(int i=0; i<errList.size(); i++){// エラーの数だけメッセージに追加 エラーが無ければ何もしない
			errMsg += errList[i] + /**/'\n';
		}
	}else{
		errMsg = "このXML構文は \"NGI\" のタグで始まっていません";
		return;
	}
}

void LotXMLIstParser::analyze(QDomElement &elem){
	clear();
	QString tag;
	tag = elem.tagName();
	if(tag.toUpper()==/**/"IST"){

		// elem = (<IST >)
		ISTData.ISTInfo.ISTDay = XDateTime::fromString(elem.attribute(/**/"DAY"
									, XDateTime().toString(/**/"yyMMddhhmmss"))
									, /**/"yyMMddhhmmss").addYears(100);
		QString	TmpNGJ=elem.attribute(/**/"NGJ", /**/"");
		ISTData.ISTInfo.NGImageFileFormat =TmpNGJ.replace(/**/'/',/**/'\\');

		ISTData.ISTInfo.MachineID = elem.attribute(/**/"MAC", /**/"-1").toInt();

		if(elem.hasChildNodes()){
			for(QDomElement istChildElem = elem.firstChildElement(); !istChildElem.isNull(); istChildElem = istChildElem.nextSiblingElement()){
				// istChildElem = <IST >(<~ >)
				tag = istChildElem.tagName();
				if(tag.toUpper()==/**/"MNM"){
					ISTData.ISTInfo.MasterID = istChildElem.attribute(/**/"MID", /**/"-1").toInt();
					ISTData.ISTInfo.MasterName = getCurrentTagText(istChildElem);
				}else if(tag.toUpper()==/**/"INSPECT"){
					ISTData.ISTInfo.InspectID = istChildElem.attribute(/**/"EID", /**/"-1").toInt();
				}else if(tag.toUpper()==/**/"RES"){
					ISTData.ISTInfo.result.append(getCurrentTagText(istChildElem));
				}else if(tag.toUpper()==/**/"LOT"){
					LotFilename = istChildElem.attribute(/**/"LID", /**/"");
					LotName = getCurrentTagText(istChildElem);
				}else if(tag.toUpper()==/**/"PHASE"){
					//<Phase CODE="0"><Page CODE="0"><NGP ～></Phase></Page>
					//<Phase CODE="0"><Page CODE="1"><NGP ～></Phase></Page>
					// ...を想定

					// ページ番号取得
					int currentPhase = istChildElem.attribute(/**/"CODE").toInt();

					ISTData.append(ISTPhase());// ページ追加
					ISTData.last().setCurrentPhase(currentPhase);

					// Phaseタグの子のタグを検索
					if(elem.hasChildNodes()){
						// 子タグメインループ
						for(QDomElement phaseChildElem = istChildElem.firstChildElement(); !phaseChildElem.isNull(); phaseChildElem = phaseChildElem.nextSiblingElement()){
							// pageChildElem = <IST ><Phase >(<~ >)
							tag = phaseChildElem.tagName();
							// Page
							if(tag.toUpper()==/**/"PAGE"){
								int currentPage = phaseChildElem.attribute(/**/"CODE").toInt();

								ISTData.last().append(ISTPage(currentPage, currentPhase));// フェイズ追加

								if(phaseChildElem.hasChildNodes()){
									for(QDomElement pageChildElem = phaseChildElem.firstChildElement(); !pageChildElem.isNull(); pageChildElem = pageChildElem.nextSiblingElement()){
										// phaseChildElem = <IST ><Page ><PHASE >(<~ >)
										tag = pageChildElem.tagName();
										if(tag.toUpper()==/**/"NGP"){
											// NGPElem = <IST ><Page ><PHASE >(<NGP ~>)
											LotXMLNgpParser parser;
											parser.analyze(pageChildElem);// <NGP ~>をパース

											if(parser.isError()==false){
												ISTData.last().last().appendNGP( parser.getData() );
											}else{
												ISTData.last().last().appendNGP( ReviewNGPoint() );
											}
										}else if(tag.toUpper()==/**/"NGI"){
											// NGPElem = <IST ><Page ><PHASE >(<NGI ~>)
											LotXMLNgiParser parser;
											parser.analyze(pageChildElem);

											if(parser.isError()==false){
												ISTData.last().last().appendNGI( parser.getData() );
											}else{
												ISTData.last().last().appendNGI( NGITagData() );
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}else{
		errMsg = "このXML構文は \"IST\" のタグで始まっていません";
	}
}