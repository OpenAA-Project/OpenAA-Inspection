#ifndef CIMGCTRL_PACK_H
#define CIMGCTRL_PACK_H
#include "XFlexArea.h"
#include "XDataInLayer.h"
#include "NList.h"

class clsPadCnt : public NPList<clsPadCnt> 
{
public :
	clsPadCnt(){
	}
	clsPadCnt(clsPadCnt &src){}
	clsPadCnt(int _cnt) {
		cnt = _cnt;
	}

	int cnt;
};

class clsPadArea : public NPList<clsPadArea>
{
public :
	double x;
	double y;
	double val;
	PureFlexAreaList *FArea;

	clsPadArea(void){	FArea=NULL;	}
	clsPadArea(PureFlexAreaList *_obj) {
		FArea = _obj;
		FArea->GetWeightCenter(x,y);
		val = x*x+y*y;
	}
	clsPadArea(clsPadArea &src){
		x=src.x;
		y=src.y;
		FArea=new PureFlexAreaList();
		*FArea=*src.FArea;
	}
};

class	clsPadAreaPack : public NPListPack<clsPadArea>
{
public:
	clsPadAreaPack(void){}
	clsPadAreaPack(clsPadAreaPack &src)
	{
		for(clsPadArea *a=src.GetFirst();a!=NULL;a=a->GetNext()){
			clsPadArea *b=new clsPadArea(*a);
			AppendList(b);
		}
	}
};


#endif