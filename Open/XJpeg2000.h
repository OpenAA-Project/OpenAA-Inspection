#if	!defined(XJPEG2000_H)
#define	XJPEG2000_H


extern	"C"
{

struct	ConvertJpeg2000RawStruct
{
	int 		XLen;
	int 		YLen;
	unsigned char *RawData;
	int			RawDataByte;
	int			AllocatedRawDataByte;
};

struct	ConvertJpeg2000Struct
{
	int 		XLen;
	int 		YLen;
	unsigned char *Jp2kData;
	int			Jp2kDataByte;
	int			AllocatedJp2kDataByte;
};


bool	ConvertDataToJpeg2000Dim(struct	ConvertJpeg2000RawStruct InpData[]
								,struct	ConvertJpeg2000Struct JpegData[]
								,int DimCount);
/*
	複数の画像データをJPEG2000に変換する
	引数
		InpData	:	入力する画像情報配列のデータポインタ
		JpegData:	ＪＰＥＧ２０００データの格納領域の配列ポインタがセットされる
		DimCount:	配列数(画像数）
	戻値
		変換に成功した場合、true

	変換後のJPEG2000データサイズをOutDataのJp2kDataByteに設定する
*/
bool	ConvertDataFromJpeg2000Dim(	 struct	ConvertJpeg2000Struct JpegData[]
									,struct	ConvertJpeg2000RawStruct RawData[]
									,int DimCount);
/*
	複数のJPEG2000から元画像データに変換する
	引数
		JpegData:	ＪＰＥＧ２０００データの格納領域の配列ポインタがセットされる
		RawData	:	出力する画像情報配列のデータポインタ
		DimCount:	配列数(画像数）
	戻値
		変換に成功した場合、true
*/

};

#endif


