#include "PropertyHalconResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\RegistHalconFunc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "RegistHalconFunc.h"
#include "XHalconInspection.h"

RegistHalconFunc::RegistHalconFunc(PropertyHalconForm *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	PClass=parent;

	//フォームのコンポーネントを配列に入れる
	HLabel[0]	=ui.label_1;
	HLabel[1]	=ui.label_2;
	HLabel[2]	=ui.label_3;
	HLabel[3]	=ui.label_4;
	HLabel[4]	=ui.label_5;
	HLabel[5]	=ui.label_6;
	HLabel[6]	=ui.label_7;
	HLabel[7]	=ui.label_8;
	HLabel[8]	=ui.label_9;
	HLabel[9]	=ui.label_10;
	ComboBox[0]	=ui.cbArg_1;
	ComboBox[1]	=ui.cbArg_2;
	ComboBox[2]	=ui.cbArg_3;
	ComboBox[3]	=ui.cbArg_4;
	ComboBox[4]	=ui.cbArg_5;
	ComboBox[5]	=ui.cbArg_6;
	ComboBox[6]	=ui.cbArg_7;
	ComboBox[7]	=ui.cbArg_8;
	ComboBox[8]	=ui.cbArg_9;
	ComboBox[9]	=ui.cbArg_10;
	FLabel[0]	=ui.label_1_1;
	FLabel[1]	=ui.label_2_1;
	FLabel[2]	=ui.label_3_1;
	FLabel[3]	=ui.label_4_1;
	FLabel[4]	=ui.label_5_1;
	FLabel[5]	=ui.label_6_1;
	FLabel[6]	=ui.label_7_1;
	FLabel[7]	=ui.label_8_1;
	FLabel[8]	=ui.label_9_1;
	FLabel[9]	=ui.label_10_1;

	//コンボボックスにファンクション文字列を入れる
	int FuncListCount	=PClass->TempLib->FuncListCount;
	HalconFuncString	=PClass->TempLib->HalconFuncString;
	for(int i=0;i<FuncListCount;i++)
		ui.cbFunc->addItem(HalconFuncString[i]);

	ArgRegionList.append(LangSolver.GetString(RegistHalconFunc_LS,LID_12)/*""*/);
	ArgTupleList.append(LangSolver.GetString(RegistHalconFunc_LS,LID_13)/*""*/);
//	for(HalconSampleList *HSampleList=PClass->TempSample->GetPrev();HSampleList!=NULL;HSampleList=HSampleList->GetPrev()){
	for(HalconSampleList *HSampleList=PClass->TempSample;HSampleList!=NULL;HSampleList=HSampleList->GetPrev()){
		for(HalconArg *HArg=HSampleList->ArgList.GetFirst();HArg!=NULL;HArg=HArg->GetNext()){
			if(HArg->AType==Region){
				if(ArgRegionList.contains(QString(HArg->Arg))==false)
					ArgRegionList.append(QString(HArg->Arg));
			}
			else if(HArg->AType==Tuple){
				if(ArgTupleList.contains(QString(HArg->Arg))==false)
					ArgTupleList.append(QString(HArg->Arg));
			}
		}
	}

	connect(ui.cbFunc,	SIGNAL(currentIndexChanged(int)),this,SLOT(cbFunCcurrentIndexChanged(int)));
	connect(ui.pbOK,	SIGNAL(clicked()),				 this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,SIGNAL(clicked()),				 this,SLOT(pbCancelClicked()));

	//初期設定
	if(PClass->TempSample->FuncName.isEmpty())
		VisibleSet(true,0);
	else{
		ui.cbFunc->setCurrentIndex(ui.cbFunc->findText(PClass->TempSample->FuncName));
		int Index=0;
		for(HalconArg *HArg=PClass->TempSample->ArgList.GetFirst();HArg!=NULL;HArg=HArg->GetNext(),Index++)
			ComboBox[Index]->setCurrentIndex(ComboBox[Index]->findText(QString(HArg->Arg)));
	}
}

RegistHalconFunc::~RegistHalconFunc()
{
}

void RegistHalconFunc::cbFunCcurrentIndexChanged(int Index)
{
	HLabelStringList.clear();
	FLabelStringList.clear();
	for(int i=0;i<10;i++){
		ComboBox[i]	->clear();
	}
	if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_14)/*"area_center"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_15)/*"Regions"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_16)/*"Area"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_17)/*"Row"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_18)/*"Column"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_19)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_20)/*"integer"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_21)/*"pointy(real)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_22)/*"pointy(real)"*/;
		VisibleSet(true,4);
		SetCombInformation(Region,1,Tuple,3);
/*
		for(int i=0;i<ArgRegionList.count();i++)
			ComboBox[0]	->addItem(ArgRegionList[i]);
		for(int i=0;i<ArgTupleList.count();i++){
			ComboBox[1]	->addItem(ArgTupleList[i]);
			ComboBox[2]	->addItem(ArgTupleList[i]);
			ComboBox[3]	->addItem(ArgTupleList[i]);
		}
		ATypeList[0]=Region;
		ATypeList[1]=Tuple;
		ATypeList[2]=Tuple;
		ATypeList[3]=Tuple;
*/
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_23)/*"closing_circle"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_24)/*"Region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_25)/*"RegionClosing"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_26)/*"Radius"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_27)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_28)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_29)/*"real"*/;
		VisibleSet(true,3);
		SetCombInformation(Region,2,Tuple,1);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_30)/*"concat_obj"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_31)/*"Objects1"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_32)/*"Objects2"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_33)/*"ObjectsConcat"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_34)/*"object"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_35)/*"object"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_36)/*"object"*/;
		VisibleSet(true,3);
		SetCombInformation(Region,3);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_37)/*"connection"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_38)/*"Region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_39)/*"ConnectedRegions"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_40)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_41)/*"region"*/;
		VisibleSet(true,2);
		SetCombInformation(Region,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_42)/*"count_obj"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_43)/*"Objects"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_44)/*"Number"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_45)/*"object"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_46)/*"integer"*/;
		VisibleSet(true,2);
		SetCombInformation(Region,1,Tuple,1);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_47)/*"difference"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_48)/*"Region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_49)/*"Sub"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_50)/*"RegionDifference"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_51)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_52)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_53)/*"region"*/;
		VisibleSet(true,3);
		SetCombInformation(Region,3);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_54)/*"emphasize"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_55)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_56)/*"ImageEmphasize"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_57)/*"MaskWidth"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_58)/*"MaskHeight"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_59)/*"Factor"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_60)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_61)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_62)/*"extent.x(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_63)/*"extent.y(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_64)/*"real"*/;
		VisibleSet(true,5);
		SetCombInformation(Region,2,Tuple,3);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_65)/*"gen_image1"*/ || HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_66)/*"gen_image3"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_67)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_68)/*"Layer"*/;
		VisibleSet(true,1);
		SetCombInformation(Region,1,Tuple,1);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_69)/*"get_region_points"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_70)/*"Region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_71)/*"Rows"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_72)/*"Columns"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_73)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_74)/*"coordinates.y(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_75)/*"coordinates.x(integer)"*/;
		VisibleSet(true,3);
		SetCombInformation(Region,1,Tuple,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_76)/*"invert_image"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_77)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_78)/*"imageInvert"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_79)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_80)/*"image"*/;
		VisibleSet(true,2);
		SetCombInformation(Region,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_81)/*"mean_image"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_82)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_83)/*"ImageMean"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_84)/*"MaskWidth"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_85)/*"MaskHeight"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_86)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_87)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_88)/*"extent.x(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_89)/*"extent.y(integer)"*/;
		VisibleSet(true,4);
		SetCombInformation(Region,2,Tuple,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_90)/*"min_max_gray"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_91)/*"Regions"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_92)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_93)/*"Percent"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_94)/*"Min"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_95)/*"Max"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_96)/*"Range"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_97)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_98)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_99)/*"number(real)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_100)/*"real"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_101)/*"real"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_102)/*"real"*/;
		VisibleSet(true,6);
		SetCombInformation(Region,2,Tuple,4);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_103)/*"select_obj"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_104)/*"Objects"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_105)/*"ObjectSelected"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_106)/*"Index"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_107)/*"object"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_108)/*"object"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_109)/*"integer"*/;
		VisibleSet(true,3);
		SetCombInformation(Region,2,Tuple,1);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_110)/*"select_shape"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_111)/*"Regions"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_112)/*"SelectedRegions"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_113)/*"Features"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_114)/*"Operation"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_115)/*"Min"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_116)/*"Max"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_117)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_118)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_119)/*"string"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_120)/*"string"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_121)/*"real"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_122)/*"real"*/;
		VisibleSet(true,6);
		SetCombInformation(Region,2,Tuple,4);
		SetCombInformation(PClass->TempLib->FeaturesList,2);
		SetCombInformation(PClass->TempLib->OperationList,3);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_123)/*"threshold"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_124)/*"Image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_125)/*"Region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_126)/*"MinGray"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_127)/*"MaxGray"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_128)/*"image"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_129)/*"region"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_130)/*"number(real)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_131)/*"number(real)"*/;
		VisibleSet(true,4);
		SetCombInformation(Region,2,Tuple,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_132)/*"tuple_max"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_133)/*"Tuple"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_134)/*"Max"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_135)/*"number(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_136)/*"number(real)"*/;
		VisibleSet(true,2);
		SetCombInformation(Tuple,2);
	}
	else if(HalconFuncString[Index]==LangSolver.GetString(RegistHalconFunc_LS,LID_137)/*"tuple_sum"*/){
		HLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_138)/*"Tuple"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_139)/*"Sum"*/;
		FLabelStringList << LangSolver.GetString(RegistHalconFunc_LS,LID_140)/*"number(integer)"*/ << LangSolver.GetString(RegistHalconFunc_LS,LID_141)/*"number(real)"*/;
		VisibleSet(true,2);
		SetCombInformation(Tuple,2);
	}
	else{
		VisibleSet(true,0);
	}
}

void RegistHalconFunc::VisibleSet(bool Visible,int VisibleCnt)
{
	for(int i=0;i<10;i++){
		if(i<VisibleCnt){
			HLabel[i]	->setVisible(Visible);
			ComboBox[i]	->setVisible(Visible);
			FLabel[i]	->setVisible(Visible);
			HLabel[i]	->setText(HLabelStringList[i]);
			FLabel[i]	->setText(FLabelStringList[i]);
		}
		else{
			HLabel[i]	->setVisible(!Visible);
			ComboBox[i]	->setVisible(!Visible);
			FLabel[i]	->setVisible(!Visible);
		}
	}
	ui.line		->setGeometry(ui.line->x(),		50+30*VisibleCnt,ui.line->width(),		ui.line->height());
	ui.pbOK		->setGeometry(ui.pbOK->x(),		70+30*VisibleCnt,ui.pbOK->width(),		ui.pbOK->height());
	ui.pbCancel	->setGeometry(ui.pbCancel->x(),	70+30*VisibleCnt,ui.pbCancel->width(),	ui.pbCancel->height());
	resize(width(),120+30*VisibleCnt);
}

void RegistHalconFunc::SetCombInformation(ArgType Type1,int CntType1,ArgType Type2,int CntType2)
{
	SetCombInformation(Type1,CntType1);
	SetCombInformation(Type2,CntType2,CntType1);
}

void RegistHalconFunc::SetCombInformation(ArgType Type,int CntType,int Index)
{
	if(Type==Region){
		for(int Cnt=0;Cnt<CntType;Cnt++,Index++){
			for(int i=0;i<ArgRegionList.count();i++)
				ComboBox[Index]->addItem(ArgRegionList[i]);
			ATypeList[Index]=Type;
		}
	}
	else if(Type==Tuple){
		for(int Cnt=0;Cnt<CntType;Cnt++,Index++){
			for(int i=0;i<ArgTupleList.count();i++)
				ComboBox[Index]->addItem(ArgTupleList[i]);
			ATypeList[Index]=Type;
		}
	}
}

void RegistHalconFunc::SetCombInformation(char **List,int Index)
{
	int Size=sizeof(List)/sizeof(List[0]);
	for(int i=0;i<Size;i++)
		ComboBox[Index]->addItem(QString(List[i]));
}

void RegistHalconFunc::pbOKClicked()
{
	PClass->TempSample->FuncName=HalconFuncString[ui.cbFunc->currentIndex()];
	PClass->TempSample->ArgList.RemoveAll();
	for(int i=0;i<10;i++){
		if(ComboBox[i]->isVisible()){
			HalconArg *P=new HalconArg(ComboBox[i]->currentText().toStdString().c_str());
			P->AType=ATypeList[i];
			PClass->TempSample->ArgList.AppendList(P);
		}
	}

	accept();
}

void RegistHalconFunc::pbCancelClicked()
{
	reject();
}
