/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XGrouperConcrete.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XGROUPERCONCRETE_H)
#define	XGROUPERCONCRETE_H

#include "XGrouper.h"
#include "XDot.h"
#include "XDataInLayer.h"

//=====================================================================

//画像スタックへのポインタを保持するのみ
class   FilterConnect2Lists : public FilterBase
{
  public:
    int     FileNo;
	int		TeacherCode;

	FilterConnect2Lists(LayersBase *abase ,int id):FilterBase(abase ,id){	FileNo=0;	}

    virtual char    *GetName(void)          {   return "Root";  }
    virtual int     GetParamNumb(void)      {   return 1;   }
    virtual int     NeedSourceNumb(void)    {   return 0;   }
    virtual char    *GetParamTitle(int n)   {   return "File No";  }
    virtual double  GetParam(int n)         {   return FileNo;   }
    virtual void    SetParam(int n ,double d){	FileNo=d;	}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterConnect2Lists(abase ,id);   }
    virtual void    InitialCalc(GroupImages &Images ,FilterContainer &gbase);
    virtual bool    Calculate(void)         {   return true;    }
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};


//モノクロ化する
class   FilterMono : public FilterBase
{
  public:
    double  BaseR;
    double  BaseG;
    double  BaseB;

    double  DivR;
    double  DivG;
    double  DivB;

    FilterMono(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "モノクロ";  }
    virtual int     GetParamNumb(void)      {   return  3;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMono(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//２値化する
class   FilterBinarize : public FilterBase
{
  public:
    double  ThreshL;
    double  ThreshH;
    double  DivThrL;
    double  DivThrH;

    FilterBinarize(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "２値化";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterBinarize(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//平均２値化
class   FilterAverageBinarize : public FilterBase
{
  public:
    double  ThreshL;
    double  ThreshH;
	double  AreaDot;
    double  DivThrL;
    double  DivThrH;
	double  DivAreaDot;

    FilterAverageBinarize(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "平均２値化";  }
    virtual int     GetParamNumb(void)      {   return  3;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterAverageBinarize(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//膨張する
class   FilterEnfat : public FilterBase
{
  public:
    double  Turn;
    double  DivTurn;

    FilterEnfat(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "膨張";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterEnfat(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//収縮する
class   FilterShrink : public FilterBase
{
  public:
    double  Turn;
    double  DivTurn;

    FilterShrink(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "収縮";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterShrink(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//明暗反転する
class   FilterOpposite : public FilterBase
{
  public:

    FilterOpposite(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "明暗反転";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterOpposite(abase ,id);   }
    virtual bool    Calculate(void);
};

//加算する
class   FilterAdd : public FilterBase
{
  public:

    FilterAdd(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "加算";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterAdd(abase ,id);   }
    virtual bool    Calculate(void);
};

//減算する
class   FilterSub : public FilterBase
{
  public:

    FilterSub(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "減算";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterSub(abase ,id);   }
    virtual bool    Calculate(void) ;
};

//係数倍する
class   FilterMul : public FilterBase
{
  public:
    double  MulData;
    double  DivMul;

    FilterMul(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "実数倍";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMul(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//相互相関画像を生成
class   FilterCoef : public FilterBase
{
  public:

    FilterCoef(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "相関";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterCoef(abase ,id);   }
    virtual bool    Calculate(void)        ;
};

//反転画像を生成
class   FilterNot : public FilterBase
{
  public:

    FilterNot(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "NOT";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterNot(abase ,id);   }
    virtual bool    Calculate(void)        ;
};

//ＡＮＤする
class   FilterAnd : public FilterBase
{
  public:

    FilterAnd(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "AND";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterAnd(abase ,id);   }
    virtual bool    Calculate(void);
};

//ＯＲする
class   FilterOr : public FilterBase
{
  public:

    FilterOr(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "OR";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterOr(abase ,id);   }
    virtual bool    Calculate(void);
};

//XORする
class   FilterXor : public FilterBase
{
  public:

    FilterXor(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "XOR";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterXor(abase ,id);   }
    virtual bool    Calculate(void);
};

//２値画像を輪郭化する
class   FilterOutline : public FilterBase
{
  public:

    FilterOutline(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "輪郭化";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterOutline(abase ,id);   }
    virtual bool    Calculate(void);
};

//多値画像から線分をピックアップする
class   FilterLineEmphasis : public FilterBase
{
  public:
    int     WindowLen;
    double  LineWidth;
    int     DivWindowLen;
    double  DivLineWidth;

    FilterLineEmphasis(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "線強調";  }
    virtual int     GetParamNumb(void)      {   return 2;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n);
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n);
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterLineEmphasis(abase ,id);   }
    virtual bool    Calculate(void);
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//自然画像のラプラス演算（２次微分）
class   FilterLaplace : public FilterBase
{
  public:

    FilterLaplace(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "ﾗﾌﾟﾗｼｱﾝ";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterLaplace(abase ,id);   }
    virtual bool    Calculate(void);
};

//自然画像の勾配演算（１次微分）
class   FilterGradiant : public FilterBase
{
  public:

    FilterGradiant(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "勾配";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterGradiant(abase ,id);   }
    virtual bool    Calculate(void);
};

//しきい値関数
class   FilterThreshold : public FilterBase
{
  public:
    double  MaxClusterLength;   //最大許容長さ
    int     MaxClusterDots;     //最大許容面積
    double  MaxLongShortRate;   //最大許容縦横比

    double  DivMaxClusterLength;   //最大許容長さ
    int     DivMaxClusterDots;     //最大許容面積
    double  DivMaxLongShortRate;   //最大許容縦横比


    FilterThreshold(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "しきい値";  }
    virtual int     GetParamNumb(void)      {   return 2;   }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterThreshold(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//判定結果割り当て関数
class   FilterAlloc : public FilterBase
{
  public:
    ConclusionBin   Result[10];
    int     ResultMap[1000];
    int     Archievement;

    FilterAlloc(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "結果割当";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 0;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d){}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterAlloc(abase ,id);   }
    virtual void    InitialCalc(GroupImages &Images ,FilterContainer &gbase);
    virtual bool    Calculate(void) ;
    virtual bool    Learn(void);
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//輝度対数変換する
class   FilterTransLog : public FilterBase
{
  public:
    double  Strength;
    double  DivStrength;

    FilterTransLog(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "対数変換";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterTransLog(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//相対２値化
class   FilterRelativeBinarize : public FilterBase
{
  public:
    double  ThreshL;
    double  ThreshH;
	double	AvrArea;
    double  DivThrL;
    double  DivThrH;
	double	DivAvrArea;

    FilterRelativeBinarize(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "相対２値";  }
    virtual int     GetParamNumb(void)      {   return  3;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)     ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)       ;
    virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterRelativeBinarize(abase ,id);   }
    virtual bool    Calculate(void) ;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//画像
class   FilterImage : public FilterBase
{
  public:
    GColor  **PixelData;

    FilterImage(LayersBase *abase ,int id):FilterBase(abase,id){  PixelData=NULL; }
    ~FilterImage(void);

    virtual char    *GetName(void)          {   return "画像";  }
    virtual int     GetParamNumb(void)      {   return 0;   }
    virtual int     NeedSourceNumb(void)    {   return 0;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id);
    bool    Copy(void);
    virtual bool    Calculate(void);
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//差分
class   FilterRelativeSub : public FilterBase
{
  public:
    int SwayLen;
    int DivSwayLen;

    FilterRelativeSub(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "差分";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   {   return "微小部分探索距離";  }
    virtual double  GetParam(int n)         {   return SwayLen;   }
    virtual void    SetParam(int n ,double d){  SwayLen=d;  }
    virtual double  GetDiv(int n)           {   return DivSwayLen;   }
    virtual void    SetDiv(int n ,double d) {   DivSwayLen=d;  }
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterRelativeSub(abase ,id);   }
    virtual bool    Calculate(void) ;
};

//周期線除去
class   FilterLineNotch : public FilterBase
{
  public:
    double FreqDots;
    double DivFreqDots;

    FilterLineNotch(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "周期線除去";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "直線ドット";  }
    virtual double  GetParam(int n)         {   return FreqDots;   }
    virtual void    SetParam(int n ,double d){  FreqDots=d;  }
    virtual double  GetDiv(int n)           {   return DivFreqDots;   }
    virtual void    SetDiv(int n ,double d) {   DivFreqDots=d;  }
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterLineNotch(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//細線化
class   FilterLinearize : public FilterBase
{
  public:

    FilterLinearize(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "細線化";  }
    virtual int     GetParamNumb(void)      {   return  0;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterLinearize(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}
};

//最長パス
class   FilterMakeMaxPath : public FilterBase
{
  public:

    FilterMakeMaxPath(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "最長パス";  }
    virtual int     GetParamNumb(void)      {   return  0;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   {   return "";  }
    virtual double  GetParam(int n)         {   return 0;   }
    virtual void    SetParam(int n ,double d){}
    virtual double  GetDiv(int n)           {   return 0;   }
    virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMakeMaxPath(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}
};

//フラクタル次元フィルター
class   FilterFractalDim : public FilterBase
{
  public:
    double	MinDim;
    double	MaxDim;

    FilterFractalDim(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "フラクタル次元";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)      ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterFractalDim(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//ノイズ除去
class   FilterRemoveNoise : public FilterBase
{
  public:
	double	FilterBankNo;
    double	Strength;
    double	DivStrength;

    FilterRemoveNoise(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "ノイズ除去";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)      ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterRemoveNoise(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//孤立点除去
class   FilterRemoveStandAlone : public FilterBase
{
  public:
    double	AloneDots;
    double	Distance;
    double	DivAloneDots;
    double	DivDistance;

    FilterRemoveStandAlone(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "孤立点除去";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n);
    virtual double  GetParam(int n)      ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterRemoveStandAlone(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//学習マッチ
class   FilterMatchLearn : public FilterBase
{
  public:

    FilterMatchLearn(LayersBase *abase ,int id):FilterBase(abase,id){}

    virtual char    *GetName(void)          {   return "学習マッチ";  }
    virtual int     GetParamNumb(void)      {   return  0;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
	virtual char    *GetParamTitle(int n)	{	return "";	}
	virtual double  GetParam(int n)			{	return 0;	}
	virtual void    SetParam(int n ,double d){}
	virtual double  GetDiv(int n)           {	return 0;	}
	virtual void    SetDiv(int n ,double d) {}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMatchLearn(abase ,id);   }
    virtual bool    Calculate(void) ;
private:
	void	Match(GrouperImageItem &TmpImage ,FlexAreaImageList *L);
};


//長さ統計
class   FilterStatisticLength : public FilterBase
{
  public:
    double	Length[100];
	double	SearchDot;
	double	MinLength;
	double	Threshold;
	double	DivSearchDot;
	double	DivMinLength;
	double	DivThreshold;
	
	class	StatisticLengthList : public NPList<StatisticLengthList>
	{
	public:
		int		PosX,PosY;
		double	A;			//傾き
		StatisticLengthList(int x ,int y ,double a){	PosX=x;	PosY=y;	A=a;	}
	};
	NPListPack<StatisticLengthList>	LengthList;


    FilterStatisticLength(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "長さ統計";  }
    virtual int     GetParamNumb(void)      {   return  3;  }
    virtual int     NeedSourceNumb(void)    {   return 100;   }
	virtual char    *GetParamTitle(int n);
	virtual double  GetParam(int n);
	virtual void    SetParam(int n ,double d);
	virtual double  GetDiv(int n);
	virtual void    SetDiv(int n ,double d);
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterStatisticLength(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);

	virtual	void	DrawOnPanel(QImage &Img ,double ZoomRate ,int Movx ,int Movy);

private:
	double	GetLength(DotListContainer *d);
	bool	Match(DotListContainer *d1 ,DotListContainer *d2);
	bool	IsExtended(double LenDim[],int Counter,double &D);
};

//正規分布乖離
class   FilterDisorderRegular : public FilterBase
{
  public:
    double	AreaDot;
    double	Gain;
    double	DivAreaDot;
    double	DivGain;

    FilterDisorderRegular(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "正規分布乖離";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterDisorderRegular(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//エルゴード性
class   FilterErgod : public FilterBase
{
  public:
    double	AreaDot;
    double	Gain;
    double	DivAreaDot;
    double	DivGain;

    FilterErgod(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "エルゴード性";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterErgod(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};


//輝点除去
class   FilterRemoveSpot : public FilterBase
{
  public:
    double	AreaDot;
    double	Gain;
    double	DivAreaDot;
    double	DivGain;

    FilterRemoveSpot(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "輝点除去";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterRemoveSpot(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//近傍接続
class   FilterConnectNearBy : public FilterBase
{
  public:
    double	Distance;
    double	DivDistance;

    FilterConnectNearBy(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "近傍接続";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
	virtual char    *GetParamTitle(int n)	{	return "探索距離";	}
	virtual double  GetParam(int n)			{	return Distance;	}
	virtual void    SetParam(int n ,double d){	Distance=d;	}
	virtual double  GetDiv(int n)           {	return DivDistance;	}
	virtual void    SetDiv(int n ,double d) {	DivDistance=d;		}
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterConnectNearBy(abase ,id);   }
    virtual bool    Calculate(void) ;
	virtual	QString	GetExplain(void)	{	return "２値化画像に対して有効";	}

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
private:
	void	SetLine(int x1 ,int y1 ,int x2, int y2);

};


//平均化
class   FilterMedian : public FilterBase
{
  public:
    double	AreaDot;
    double	DivAreaDot;

    FilterMedian(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "中央平均化";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMedian(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};


//モザイク化
class   FilterMosaic : public FilterBase
{
  public:
    double	AreaDot;
    double	DivAreaDot;

    FilterMosaic(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "モザイク化";  }
    virtual int     GetParamNumb(void)      {   return  1;  }
    virtual int     NeedSourceNumb(void)    {   return 1;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterMosaic(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};

//線強調
class   FilterLineEmphasizer : public FilterBase
{
  public:
    double	AreaDot;
    double	Gain;
    double	DivAreaDot;
    double	DivGain;

	FilterLineEmphasizer(LayersBase *abase ,int id);

    virtual char    *GetName(void)          {   return "線強調";  }
    virtual int     GetParamNumb(void)      {   return  2;  }
    virtual int     NeedSourceNumb(void)    {   return 2;   }
    virtual char    *GetParamTitle(int n)   ;
    virtual double  GetParam(int n)         ;
    virtual void    SetParam(int n ,double d);
    virtual double  GetDiv(int n)           ;
    virtual void    SetDiv(int n ,double d) ;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)    {   return new FilterLineEmphasizer(abase ,id);   }
    virtual bool    Calculate(void) ;

	virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
};


#endif