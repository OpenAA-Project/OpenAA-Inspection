
/*********************************************/
/*  BMP FILE 作成用のマクロ定義			     */
/*********************************************/

#define BMP_FHD_SIZ    14        // BITMAPFILEHEADER 
#define BMP_HD_SIZ     40        // BITMAPINFOHEADER
#define BMP_BUF_SIZ   (BMP_FHD_SIZ+BMP_HD_SIZ+1024)

/**********************************************/
/*  TIFF FILE 作成用構造体					  */
/**********************************************/
typedef struct{
	char	*img;					/*  Image memory address  */
	short	byteperpix;				/*  Byte per Pixcel  */
	short	gscalebit;				/*  gray scale bit  */
	short	xsize;					/*  Image Xsize  */
	short	ysize;					/*  Image Ysize  */
	short	xoffset;				/*  X offset length */
	short	yoffset;				/*  Y offset length */
	short	xviewsize;				/*  X viewport size */
	short	yviewsize;				/*  Y viewport size */
	short	foam;					/*  Image saved format  */
	char	endian;					/*	Endian	*/
	char	*fnamept;				/*	Image File Name */
}IPM_FILEIMG;


typedef struct {
    BYTE        Red;
    BYTE        Green;
    BYTE        Blue;
    BYTE        Reserved;
}IPM_PALENTRY;


typedef struct {
  IPM_PALENTRY   rgb[256];
}IPMPALETTE;


typedef struct{
	unsigned short	tag;
	unsigned short	type;
	unsigned long	count;
	unsigned long	value;
}TIFF_IFD;

typedef struct{
	unsigned long	den;					/* Denominator */
	unsigned long	num;					/* Numerator */
}TIFF_RATIONAL;

typedef struct{
	unsigned short	order;
	unsigned short	version;
	unsigned long	ptr;
	unsigned short	dummy;
	unsigned short	entry;
	TIFF_IFD		nst;
	TIFF_IFD		iw;
	TIFF_IFD		il;
	TIFF_IFD		bps;
	TIFF_IFD		cmp;
	TIFF_IFD		pi;
	TIFF_IFD		so;
	TIFF_IFD		_or;
	TIFF_IFD		spp;					//8500Verでは削除されてたもの
	TIFF_IFD		rps;
	TIFF_IFD		sbc;
	TIFF_IFD		xr;
	TIFF_IFD		yr;
	TIFF_IFD		ru;
	unsigned long	end;
	TIFF_RATIONAL	xrd;
	TIFF_RATIONAL	yrd;
}IPM_IFD;

typedef struct{
	unsigned short r;
	unsigned short g;
	unsigned short b;
}RGBBIT;
/**********************************************/
/*  TIFF FILE 作成用のマクロ定義			  */
/**********************************************/

#define NewSubfileType			    0x00fe
#define ImageWidth					0x0100
#define ImageLength					0x0101
#define BitsPerSample				0x0102
#define Compression					0x0103
#define PhotometricInterpretation	0x0106
#define StripOffsets				0x0111
#define Orientation					0x0112
#define SamplePerPixel				0x0115
#define RowsPerPixel				0x0116
#define StripByteCount				0x0117
#define XResorution					0x011a
#define YResorution					0x011b
#define ResorutionUnit				0x0128

#define Type_BYTE					0x00000001L
#define Type_SHORT					0x00000003L
#define Type_LONG					0x00000004L
#define Type_RATIONAL				0x00000005L

/**********************************************/
/*  TYPEﾌｫｰﾏｯﾄ	表示,ﾌｧｲﾙ保存で使用
//  FILETYPE はFORMATﾒﾝﾊﾞｰで使用
//  COLORMSK はTYPEﾒﾝﾊﾞｰで使用
//  TUPTYPE  はTYPEﾒﾝﾊﾞｰで使用
/**********************************************/
#define TYPE_BITMAP				(0x00000001)
#define TYPE_TIFF				(0x00000002)
#define FILETYPE				(0x00000003)

#define MONOTONE				(0x00000000)
#define RGBCOLOR				(0x00000200)
#define COLORMSK				(0x00000300)

#define TYPE_4TUP				(0x00000010)
#define TYPE_2TUP				(0x00000020)
#define TYPE_4TUPMIRROR			(0x00000030)
#define TYPE_2TUPMIRROR			(0x00000040)
#define TYPE_4TUPA				(0x00000050)
#define TYPE_4TUPDUAL			(0x00000060)
#define TYPE_2TUPDUAL			(0x00000070)
#define TUPTYPE					(0x000001FF)

#define	TYPE_BAYER_MASK			(0x000000A0)		// 200809追加
#define	TYPE_BAYER				(0x000000A0)		// 200809追加
#define TYPE_BAYER_TUP          (0x000000A1)		// 200809追加(bit0が'1'の時はTAP)
#define TYPE_BAYER_10BIT        (0x000000A2)		// 200809追加(暫定)
#define TYPE_BAYER_12BIT        (0x000000A4)		// 200809追加(暫定)
#define TYPE_BAYER_14BIT        (0x000000A6)		// 200809追加(暫定)
#define TYPE_BAYER_16BIT        (0x000000A8)		// 200809追加(暫定)

#define TYPE_BAYER_ELSE_8BIT_MASK	(0x000000AE)		// 200809追加(暫定) Bayerを示す値0xA0 + bit3～bit1をﾏｽｸ
#define	TYPE_BAYER_COLOR_24BIT		(RGBCOLOR + 0xA2)	// 200809追加(暫定) Bayerを24bitｶﾗｰにするためのﾏｸﾛ(DLLの仕様に合わせる苦肉の策)
#define	TYPE_TUP_MASK				(0x000000F0)		// 200809追加(暫定)

#define TYPE_10TO8				(0x00001000)
#define TYPE_30TO24				(0x00002000)
#define SHIFTTYPE				(0x00007000)