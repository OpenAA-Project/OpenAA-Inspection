
/*

class	_YLinePattern
{
public:
	int	AddXByte;
	int	AddY;
	int	AddL2RByte;
	BYTE	PatternL,PatternR;

	_YLinePattern(void);
	~_YLinePattern(void);

	void	SetBit(int x1,int x2, int y);
};

class	_ShapePattern
{
public:
	YLinePattern	*Shape;
	int				ShapeLen;

	_ShapePattern(void);
	~_ShapePattern(void);

	void	MakeCirclePattern(int Turn,int bit)
};

class	_BitShape
{
public:
	ShapePattern	WholePattern;
	ShapePattern	DifPattern[8];

	_BitShape(void){}
	~_BitShape(void){}

	void	MakeBitShape(int Turn,int bit);
};

//------------------------------------------------------------

_YLinePattern::_YLinePattern(void)
{	
	AddL2RByte	=0;
	PatternL	=0;
	PatternR	=0;
	AddXByte	=0;
	AddY		=0;
}

_YLinePattern::~_YLinePattern(void)
{
}

void	_YLinePattern::SetBit(int x1,int x2, int y)
{
	AddY	=y;
	int	XBPos1	=x1>>3;
	int	XBPos2	=x2>>3;
	int	XpPos1,XpPos2;
	if(x1>=0){
		XpPos=x1&0x7;
	}
	else{
	}


	AddXByte	=XBPos1;
	AddL2RByte	=XBPos2-XBPos1;
	PatternL	=0xFF>>(8-x1
	PatternR;
}

_ShapePattern::_ShapePattern(void)
{	
	Shape=NULL;
	ShapeLen=0;
}
_ShapePattern::~_ShapePattern(void)
{
	if(Shape!=NULL){
		delete	[]Shape;
		Shape=NULL;
		ShapeLen=0;
	}
}

void	_ShapePattern::MakeCirclePattern(int Turn,int bit)
{
	Shape=new YLinePattern[2*Turn+1];

	int	N=0;
	for(int ry=-Turn;ry<=Turn;ry++,N++){
		int	Q=sqrt(Turn*Turn-ry*ry);
		int	rx1=bit-Q;
		int	rx2=bit+Q;
		Shape[N].SetBit(rx1,rx2,ry);
	}

}

void	_BitShape::MakeBitShape(int Turn,int bit)
{
	WholePattern.MakeCirclePattern(Turn,bit);
}

//------------------------------------------------------------

void    FatArea(int Turn BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDo)
{
	_BitShape	BitShape[8];

	for(int bit=0;bit<8;bit++){
		BitShape[bit].MakeBitShape(Turn,bit);

}

*/