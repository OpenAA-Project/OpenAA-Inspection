/*
 * Copyright (C) 2023
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




#if	!defined(XOUTLINEINSPECT_H)
#define	XOUTLINEINSPECT_H

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XDataInLayer.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

class	ImageBuffer;
class	OutlineInPage;
class   OutlineInLayer;
class	OutlineBase;
class	OutlineItem;
class	XOutlineList;

#define	MAXGENTENOUTLINEDOTNUMB	10000
#define MaxPadSeparations   10

#define	OutlineInspectionVersion	1
#define	DefLibTypeOutlineInspect			3

class	OutlineInspectLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	Code;			/*	�֊s�f�[�^�ւ̃C���f�b�N�X	���ӂ̒l*/
	QString	LibName;		/*	���C�u������			*/
	int32	OutlineJanle;	/*	�\��	*/

	WORD	GenColorBlack;	/*	������	���o�P�x�̈Ñ�		*/
	WORD	GenColorWhite;	/*	������	���o�P�x�̖���		*/
	int32	GenSizeMin;		/*	������	���o�T�C�Y�̍ŏ�	*/
	int32	GenSizeMax;		/*	������	���o�T�C�Y�̍ő�	*/
	int32	GenGap;			/*	������	�����Ԋu		*/
	bool	GenFat;			/*	������	���������ւ̒��o	*/

	int32	InsVNumb;		/*	�������@�m�f�x�N�g������	*/
	int32	InsSizeBlack;	/*	�������@���׍ŏ��T�C�Y�Ñ�	*/
	int32	InsSizeWhite;	/*	�������@���׍ŏ��T�C�Y����	*/
	int32	InsCornerBlack;	/*	�������@�p�����̍ŏ��T�C�Y�Ñ�	*/
	int32	InsCornerWhite;	/*	�������@�p�����̍ŏ��T�C�Y����	*/
	int32	InsOKWidthBlack;/*	�������@����	*/
	int32	InsOKWidthWhite;/*	�������@����	*/
	WORD	SelfSearch;		/*	�������@�T������	*/

	OutlineInspectLibrary(int LibType,LayersBase *Base);

	virtual	AlgorithmLibrary &operator=(const AlgorithmLibrary &src)	override;
	virtual	bool	SaveBlob(QIODevice *file)	override;
	virtual	bool	LoadBlob(QIODevice *file)	override;
};

class	OutlineInspectLibraryContainer : public AlgorithmLibraryContainer
{
public:
	OutlineInspectLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~OutlineInspectLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeOutlineInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Outline Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new OutlineInspectLibrary(GetLibType(),GetLayersBase());	}
};

//===============================================================================================
struct  XOutlineStruct
{
    XYClass		*TmpXY;
    int         TmpXYNumb;
    NPListPack<XYClass> m;
    BYTE        **data;
    int         xbyte;
    int         NowX;
    int         NowY;
	int			DotPerLine;
	int			MaxLines;
};

class   XOutlineStructList : public NPList<XOutlineStructList>
{
  public:
    struct  XOutlineStruct  *d;
    int MinX,MaxX,MinY,MaxY;

    XOutlineStructList(void){   d=NULL; }
    ~XOutlineStructList(void){}

    void    CalcMinMax(void);
};

//===============================================================================================
struct   XOutlineListResult
{
    ushort  X,Y;                        //�X�v���C�����̓_
    short   Vx,Vy;                      //�P�ʖ@���x�N�g���@���W�r�b�g�͏����@
    float   ResultBorder;   //���E��

    XOutlineListResult(void);
	int32	GetByte(void)		;
	bool    Load(QIODevice *);
	bool    Save(QIODevice *);
};

class   XOutlineResultPack : public AddedDataClass
{
  friend    class   XOutlineList;

    struct  XOutlineListResult      *List;
    int                             ListNumb;
    float   Mx,My;
  public:

    XOutlineResultPack(void);
    ~XOutlineResultPack(void);

	static	AddedDataClass	*GetPointer(WORD kind);
	bool    Load(QIODevice *);
	bool    Save(QIODevice *);
	int32	GetByte(void)		;

    void    Initial(int OListNumb);
    void    SetMxy(double mx ,double my);
    bool    SetResult(XOutlineList *br ,int n ,float Dk);
    void    Move(int dx, int dy);
    void    MakeAverageBorder(void);
    void    MakeAverageBorderInner(int StartI ,int ZoneNumb);
    double  GetBorder(int index);

    XOutlineResultPack  &operator=(XOutlineResultPack &src);

    //void    Draw(Graphics::TBitmap *m ,int movx ,int movy ,double ZoomRate);
};

class   XOutlineList //: public NPList<XOutlineList>
{
    int32	X,Y;                        //�X�v���C�����̓_
    short   Vx,Vy;                      //�P�ʖ@���x�N�g���@���W�r�b�g�͏����@
    WORD    PCol,MCol;
    short   VLen;           //=ceil(hypot(Vx/256.0,Vy/256.0)*256.0) ���W�r�b�g�͏���

    float   UVx;
    float   UVy;            //�P�ʖ@���x�N�g��
  public:
    WORD    KensaAvr;       //�x�N�g���T���͈͂ł̌����f�[�^�̕��ϋP�x�i臒l�j
    WORD    LooseThre;      //�����f�[�^�ɂ��鋫�E�������l���

    bool    Selected;       //�T���̂��߂̑I���t���O

    XOutlineList(void){ X=Y=0;  Vx=Vy=0;    Selected=false; LooseThre=0;    UVx=0;  UVy=0;    }
    XOutlineList(XOutlineList &src);
    XOutlineList(int x,int y,float vx,float vy);
    ~XOutlineList(void){}
    bool    Initial(ImageBuffer &Buff);
    bool    operator!=(XOutlineList &src);
    XOutlineList    &operator=(XOutlineList &src);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
    void    Get(int &px, int &py ,float &vx ,float &vy){
            px=X;
            py=Y;
            vx=(float)Vx/256.0;
            vy=(float)Vy/256.0;
            }
    void    Get(int &px, int &py){
            px=X;
            py=Y;
            }
    double  GetSita(void);
    double  GetVLen(void);
    int     GetVLenInt(void){   return((((int)VLen)+255)>>8);   }
    void    CopyVFrom(XOutlineList *src);
    void    SetV(double vx, double vy);
    void    ReverseV(void){ Vx=-Vx; Vy=-Vy; }
    int     GetEndPointX1(void){ return(X+(((Vx>0)?((Vx+127)>>8):((Vx-127)>>8))));  }
    int     GetEndPointY1(void){ return(Y+(((Vy>0)?((Vy+127)>>8):((Vy-127)>>8))));  }
    int     GetEndPointX2(void){ return(X-(((Vx>0)?((Vx+127)>>8):((Vx-127)>>8))));  }
    int     GetEndPointY2(void){ return(Y-(((Vy>0)?((Vy+127)>>8):((Vy-127)>>8))));  }
    int     GetLVPointX(int r){ return(X+Vx*r/VLen);    }
    int     GetLVPointY(int r){ return(Y+Vy*r/VLen);    }
    int     GetRVectorX(int r){ return(Vx*r/VLen);    }
    int     GetRVectorY(int r){ return(Vy*r/VLen);    }
    int     GetCenterX(void){   return(X);  }
    int     GetCenterY(void){   return(Y);  }

    double    GetKensaOutlineShift(DataInLayer *Ly,OutlineItem &b ,int searchdot ,double mx, double my ,int NowCCol);
    int   GetEndPoint1Color(ImageBuffer &Buff, int mx ,int my);
    int   GetEndPoint2Color(ImageBuffer &Buff, int mx ,int my);
    double GetOutlineShift(ImageBuffer &Buff ,int mx, int my,int SlopDot
                                        ,double &ix ,double &iy);
    double GetOutlineShift(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                        ,int NowCCol ,int NowPCol ,int NowMCol
                                        ,double &ix ,double &iy);

    double  GetOutlineShiftForGenten(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                        ,int NowCCol ,int NowPCol ,int NowMCol
                                        ,double &ix ,double &iy);

    int    GetThrePoint(int Thre , ImageBuffer &data , int mx ,int my ,int cv ,int DarkDiff ,int BrightDiff);
    void   CalcThreshold(ImageBuffer &data , int mx ,int my);
    void   CalcVLen(void);
    void    Set(int x,int y,float vx,float vy){
            X=(ushort)x;
            Y=(ushort)y;
            Vx=(short)(vx*256.0);
            Vy=(short)(vy*256.0);
            CalcVLen();
            Selected=false;
            }

    void    MoveTo(int dx ,int dy);
    bool   IsideOfRectangle(int x1 ,int y1 ,int x2 ,int y2);

    int     GetX(void)	{	return(X);			}
    int     GetY(void)	{	return(Y);			}
    double  GetVx(void)	{	return(Vx/256.0);	}
    double  GetVy(void)	{	return(Vy/256.0);	}

    double  GetUnitVx(void){    return(UVx);   }
    double  GetUnitVy(void){    return(UVy);   }

    void    CopyThreshold(XOutlineList &src);
};

class	OutlineThreshold :public AlgorithmThreshold
{
public: 
	int32			InsVNumb;		/*	�������@�m�f�x�N�g������	*/
	int32			InsSizeBlack;	/*	�������@���׍ŏ��T�C�Y�Ñ�	*/
	int32			InsSizeWhite;	/*	�������@���׍ŏ��T�C�Y����	*/
	int32			InsCornerBlack;	/*	�������@�p�����̍ŏ��T�C�Y�Ñ�	*/
	int32			InsCornerWhite;	/*	�������@�p�����̍ŏ��T�C�Y����	*/
	int32			InsOKWidthBlack;/*	�������@����	*/
	int32           InsOKWidthWhite;/*	�������@����	*/
	WORD			SelfSearch;

	OutlineThreshold(AlgorithmItemRoot *parent);
	~OutlineThreshold(void);
	virtual	void	CopyFrom(const AlgorithmThreshold &src)   override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)    const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)				   	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	OutlineItem : public AlgorithmItemPLI
{
public:
	FlexArea		FLines;
	//int32			LibID;			//���C�u����ID

	XOutlineList    *OList;	            // PAD�֊s
    int             OListNumb;

    QPoint		*VectorIndex;			//���㐶��

	OutlineItem(void);
	~OutlineItem(void);
    virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new OutlineItem();	}
	virtual	OutlineItem	&operator=(const AlgorithmItemRoot &src)	override;
	const OutlineThreshold	*GetThresholdR(void){	return (const OutlineThreshold *)GetThresholdBaseReadable();	}
	OutlineThreshold		*GetThresholdW(void){	return (OutlineThreshold *)GetThresholdBaseWritable();	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new OutlineThreshold(this);	} 
	
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	MoveTo(int dx ,int dy)	override;

	static  void     OutlineFunc(struct XOutlineStruct &d ,int x ,int y,int &ONestLevel);
    static  void    AdjustOutline(NPListPack<XOutlineStructList>  &OStructList
                            ,int xbyte ,int XLenDot ,int YLen
							,int OutlineVectorsMin);
    //static  XOutlineList  *__fastcall  MakeOutlineList(NPListPack<XYClass> &B ,int &DListNumb
	 static  XOutlineList  * MakeOutlineList(NPListPack<XYClass> &B ,int &DListNumb

                                                        ,int OutlinePrecision
														,int OutlineSeparation);
	void    CalcPadOutlineVector(void);
	void	CalcOnGenerate(ResultInItemPLI &result);
	void	StartKensa(ResultInItemPLI &result,int SomeCode);

private:
	int		SearchFittable(int mx, int my ,double &dx ,double  &dy);
	bool	KensaOnOutlineDust(double &mx, double &my ,ResultInItemPLI &result);
};


//===============================================================================================

class   OutlineInLayer : public AlgorithmInLayerPLI
{
public:
	OutlineInLayer(AlgorithmInPageRoot *parent);
	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override{	return(new OutlineItem());	}

	void	MakeData(OutlineInspectLibrary *Lib ,int NoZone=100);
    virtual bool    Save(QIODevice *f)      override;
    virtual bool    Load(QIODevice *f)      override;

private:
    void    SupressOutlineDot(NPListPack<XYClass> &B);
    void    AddBlock(ImageBuffer &Buff ,NPListPack<XYClass> &B ,OutlineInspectLibrary &Lib);
	int     GetCrossY(int Y ,QPoint d[] ,int PointNumb,int X[]);
};


class   OutlineInPage : public AlgorithmInPagePLI
{
public:
	OutlineInPage(void);
	OutlineInPage(AlgorithmBase *parent);
	~OutlineInPage(void);

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new OutlineInLayer(parent));	}
	//virtual	AlgorithmItemRoot		*CreateItem(int layer,int ItemClassType){	return GetLayerData(layer)->NewChild(0);	}

};

class	OutlineBase : public AlgorithmBase
{
public:
	static	int			OutlineSeparation;

	OutlineBase(LayersBase *Base):AlgorithmBase(Base){}
	~OutlineBase(void){}

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)    override{	return(new OutlineInPage(parent));	}
    virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override{   return NULL;    }
	virtual QString	GetDefaultFileName(void)	override    {	return QString("ConfigOutline.dat");		}
};

extern	OutlineBase	OutlineBaseData;

inline  double  XOutlineResultPack::GetBorder(int index)
{
    if(index<ListNumb){
        return(List[index].ResultBorder);
        }
    return(0);
}

#endif