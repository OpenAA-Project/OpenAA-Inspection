/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockSearchWay.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XBlockSearchWay.h"

const	int LEVEL3SWIFT=1;
const   int BlockGroupSWNumb=15;

struct  L3SwingProcess
{
    int Dx;
    int Dy;
};

static	struct  L3SwingProcess  SW[BlockGroupSWNumb]={
                    {   0           ,0              },
                    {   -LEVEL3SWIFT,0              },
                    {   0           ,-LEVEL3SWIFT   },
                    {   +LEVEL3SWIFT,0              },
                    {   0           ,+LEVEL3SWIFT   },
                    {   -LEVEL3SWIFT,-LEVEL3SWIFT   },
                    {   +LEVEL3SWIFT,-LEVEL3SWIFT   },
                    {   -LEVEL3SWIFT,+LEVEL3SWIFT   },
                    {   +LEVEL3SWIFT,+LEVEL3SWIFT   },

                    {   0           ,-2*LEVEL3SWIFT   },
                    {   0           ,+2*LEVEL3SWIFT   },
                    {   -LEVEL3SWIFT,-2*LEVEL3SWIFT   },
                    {   +LEVEL3SWIFT,-2*LEVEL3SWIFT   },
                    {   -LEVEL3SWIFT,+2*LEVEL3SWIFT   },
                    {   +LEVEL3SWIFT,+2*LEVEL3SWIFT   }

                    };
static	struct  L3SwingProcess  SW2[]={
                    {   -2*LEVEL3SWIFT  ,0                  },
                    {   0               ,-2*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,0                  },
                    {   0               ,+2*LEVEL3SWIFT     },
                    {   -2*LEVEL3SWIFT  ,-2*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,-2*LEVEL3SWIFT     },
                    {   -2*LEVEL3SWIFT  ,+2*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,+2*LEVEL3SWIFT     },

                    {   -2*LEVEL3SWIFT  ,+LEVEL3SWIFT       },
                    {   -2*LEVEL3SWIFT  ,-LEVEL3SWIFT       },
                    {   +LEVEL3SWIFT    ,-2*LEVEL3SWIFT     },
                    {   -LEVEL3SWIFT    ,-2*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,+LEVEL3SWIFT       },
                    {   +2*LEVEL3SWIFT  ,-LEVEL3SWIFT       },
                    {   +LEVEL3SWIFT    ,+2*LEVEL3SWIFT     },
                    {   -LEVEL3SWIFT    ,+2*LEVEL3SWIFT     },

                    {   -3*LEVEL3SWIFT  ,0                  },
                    {   0               ,-3*LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,0                  },
                    {   0               ,+3*LEVEL3SWIFT     },
                    {   -3*LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   -3*LEVEL3SWIFT  ,+3*LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,+3*LEVEL3SWIFT     },

                    {   -3*LEVEL3SWIFT  ,+  LEVEL3SWIFT     },
                    {   -3*LEVEL3SWIFT  ,+2*LEVEL3SWIFT     },
                    {   -3*LEVEL3SWIFT  ,-  LEVEL3SWIFT     },
                    {   -3*LEVEL3SWIFT  ,-2*LEVEL3SWIFT     },
                    {   +  LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   -  LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   -2*LEVEL3SWIFT  ,-3*LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,+  LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,+2*LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,-  LEVEL3SWIFT     },
                    {   +3*LEVEL3SWIFT  ,-2*LEVEL3SWIFT     },
                    {   +  LEVEL3SWIFT  ,+3*LEVEL3SWIFT     },
                    {   +2*LEVEL3SWIFT  ,+3*LEVEL3SWIFT     },
                    {   -  LEVEL3SWIFT  ,+3*LEVEL3SWIFT     },
                    {   -2*LEVEL3SWIFT  ,+3*LEVEL3SWIFT     }

                    };
                    /*
                    {   -2*LEVEL3SWIFT  ,0              },
                    {   0               ,-2*LEVEL3SWIFT },
                    {   +2*LEVEL3SWIFT  ,0              },
                    {   0               ,+2*LEVEL3SWIFT },
                    {   -2*LEVEL3SWIFT  ,-2*LEVEL3SWIFT },
                    {   +2*LEVEL3SWIFT  ,-2*LEVEL3SWIFT },
                    {   -2*LEVEL3SWIFT  ,+2*LEVEL3SWIFT },
                    {   +2*LEVEL3SWIFT  ,+2*LEVEL3SWIFT }
                    };
                    */




SearchWayList::SearchWayList(void)
{
    SWWay[0].SetSearchWay (SW ,sizeof(SW )/sizeof(SW [0]));
    SWWay[1].SetSearchWay (SW ,sizeof(SW )/sizeof(SW [0]));
    SWWay[2].SetSearchWay (SW ,sizeof(SW )/sizeof(SW [0]));
    SWWay2.SetSearchWay(SW2,sizeof(SW2)/sizeof(SW2[0]));
}

SearchWay   *SearchWayList::SearchFreeWay(int searchlen)
{
    for(SearchWay *w=FreeWay.GetFirst();w!=NULL;w=w->GetNext()){
		if(w->SearchLen==searchlen){
            return(w);
        }
	}
    SearchWay   *k=new SearchWay();
    k->SetSearchWay(searchlen);
    FreeWay.AppendList(k);
    return(k);
}

SearchWay::SearchWay(void)
{
    SearchLen=0;
}

void    SearchWay::SetSearchWay(int searchlen)
{
    SWay.RemoveAll();
    SWay.AppendList(new XYClass(0,0));
    SearchLen=searchlen;

	/*
	for(int Lx=-searchlen;Lx<=searchlen;Lx++){
		for(int Ly=-searchlen;Ly<=searchlen;Ly++){
			SWay.AppendList(new XYClass(Lx,Ly));
		}
	}
	*/

        if(searchlen<4){
            for(int i=2;i<=searchlen;i+=2){
                int x,y;
                y= -i;
                for(x= -i;x<i;x+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x=i;
                for(y= -i;y<i;y+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                y=i;
                for(x=i;x>-i;x-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x= -i;
                for(y=i;y>-i;y-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                }

            for(int i=1;i<=searchlen;i+=2){
                int x,y;
                y=-i;
                for(x= -i;x<i;x+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x=i;
                for(y= -i;y<i;y+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                y=i;
                for(x=i;x>-i;x-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x=-i;
                for(y=i;y>-i;y-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                }

            for(int i=1;i<=searchlen;i++){
                int x,y;
                y= -i;
                for(x= -i;x<i;x++){
					if((((x&1)==0) && ((y&1)==0)) || (((x&1)!=0) && ((y&1)!=0))){
                        continue;
					}
                    SWay.AppendList(new XYClass(x,y));
                    }
                x=i;
                for(y= -i;y<i;y++){
					if((((x&1)==0) && ((y&1)==0)) || (((x&1)!=0) && ((y&1)!=0))){
                        continue;
					}
                    SWay.AppendList(new XYClass(x,y));
                    }
                y=i;
                for(x=i;x>-i;x--){
					if((((x&1)==0) && ((y&1)==0)) || (((x&1)!=0) && ((y&1)!=0))){
                        continue;
					}
                    SWay.AppendList(new XYClass(x,y));
                    }
                x= -i;
                for(y=i;y>-i;y--){
					if((((x&1)==0) && ((y&1)==0)) || (((x&1)!=0) && ((y&1)!=0))){
                        continue;
					}
                    SWay.AppendList(new XYClass(x,y));
                    }
                }
            }
        else{
            for(int i=2;i<=searchlen;i+=2){
                int x,y;
                y= -i;
                for(x= -i;x<i;x+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x=i;
                for(y= -i;y<i;y+=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                y=i;
                for(x=i;x>-i;x-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                x= -i;
                for(y=i;y>-i;y-=2){
                    SWay.AppendList(new XYClass(x,y));
                    }
                }
            }
}
void    SearchWay::SetSearchWay(struct L3SwingProcess sw[] ,int swnumb)
{
    SWay.RemoveAll();
    for(int i=0;i<swnumb;i++){
        SWay.AppendList(new XYClass(sw[i].Dx,sw[i].Dy));
        }
}

void    SearchWay::ToTop(XYClass *d)
{
    SWay.RemoveList(d);
    SWay.InsertList(0,d);
}

