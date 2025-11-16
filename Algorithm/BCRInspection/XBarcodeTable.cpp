#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "DTKBarReader.h"


struct BarcodeTableStruct
{
	const	char	*TypeName;
	uint32			EnumCode;
	CheckBoxInTable	*Cb;
};

static	struct BarcodeTableStruct	BarcodeTypeTable[]={
	{	"Unknown"		,BT_Unknown		,NULL	},
	{	"Code11"		,BT_Code11		,NULL	},
	{	"Code39"		,BT_Code39		,NULL	},
	{	"Code93"		,BT_Code93		,NULL	},
	{	"Code128"		,BT_Code128		,NULL	},
	{	"Codabar"		,BT_Codabar		,NULL	},
	{	"Inter2of5"		,BT_Inter2of5	,NULL	},
	{	"PatchCode"		,BT_PatchCode	,NULL	},
	{	"EAN8"			,BT_EAN8		,NULL	},
	{	"UPCE"			,BT_UPCE		,NULL	},
	{	"EAN13"			,BT_EAN13		,NULL	},
	{	"UPCA"			,BT_UPCA		,NULL	},
	{	"Plus2"			,BT_Plus2		,NULL	},
	{	"Plus5"			,BT_Plus5		,NULL	},
	{	"PDF417"		,BT_PDF417		,NULL	},
	{	"DataMatrix"	,BT_DataMatrix	,NULL	},
	{	"QRCode"		,BT_QRCode		,NULL	},
	{	"Postnet"		,BT_Postnet		,NULL	},
	{	"Planet"		,BT_Planet		,NULL	},
	{	"RM4SCC"		,BT_RM4SCC		,NULL	},
	{	"AustraliaPost"	,BT_AustraliaPost		,NULL	},
	{	"IntelligentMail",BT_IntelligentMail	,NULL	},
	{	"Code39Extended",BT_Code39Extended		,NULL	},
	{	"MicroQRCode"	,BT_MicroQRCode			,NULL	},
	{	"PharmaCode"	,BT_PharmaCode			,NULL	},
	{	"UCC128"		,BT_UCC128				,NULL	},
	{	"RSS14"			,BT_RSS14				,NULL	},
	{	"RSSLimited"	,BT_RSSLimited			,NULL	},
	{	"RSSExpanded"	,BT_RSSExpanded			,NULL	},
	{	"All"			,BT_All					,NULL	},
	{	"All_1D"		,BT_All_1D				,NULL	},
	{	"All_2D"		,BT_All_2D				,NULL	},
};

static	struct BarcodeTableStruct	BarcodeOrientationTable[]={
	{	"LeftToRight"	,BO_LeftToRight		,NULL	},
	{	"RightToLeft"	,BO_RightToLeft		,NULL	},
	{	"TopToBottom"	,BO_TopToBottom		,NULL	},
	{	"BottomToTop"	,BO_BottomToTop		,NULL	},
	{	"All"			,BO_All				,NULL	}
};

int	GetBarcodeTypeTableCount(void)
{
	return sizeof(BarcodeTypeTable)/sizeof(BarcodeTypeTable[0]);
}

int	GetBarcodeTypeTable(int n,QString &TypeName)
{
	if(n<sizeof(BarcodeTypeTable)/sizeof(BarcodeTypeTable[0])){
		TypeName=BarcodeTypeTable[n].TypeName;
		return BarcodeTypeTable[n].EnumCode;
	}
	return -1;
}

int	GetBarcodeOrientationTableCount(void)
{
	return sizeof(BarcodeOrientationTable)/sizeof(BarcodeOrientationTable[0]);
}

int	GetBarcodeOrientationTable(int n,QString &TypeName)
{
	if(n<sizeof(BarcodeOrientationTable)/sizeof(BarcodeOrientationTable[0])){
		TypeName=BarcodeOrientationTable[n].TypeName;
		return BarcodeOrientationTable[n].EnumCode;
	}
	return -1;
}
		

