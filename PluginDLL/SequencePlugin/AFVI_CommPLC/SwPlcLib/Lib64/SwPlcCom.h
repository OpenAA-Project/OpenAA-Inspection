/*
 * Copyright(C) 2015 Seiwa Giken Co., Ltd.
 *				All Right Reserved
 */

#ifndef _SWPLCCOM_H
#define	_SWPLCCOM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define SWPLC_TYPE_SERIAL	0
#define SWPLC_TYPE_TCP		1
#define SWPLC_TYPE_UDP		2
#define SWPLC_TYPE_CUSTOM	3

#define SWPLC_ERROR_TRIAL_TIMEOVER		-2		// 試用時間が超過しました
#define SWPLC_INVALID_ID				-1		// 通信IDが不正です
#define SWPLC_OK						0		// 正常
#define SWPLC_ERROR						1		// 実行エラー
#define SWPLC_ERROR_LOADFILE			2		// ファイルのロードに失敗しました
#define SWPLC_ERROR_LOADLIBRARY			3		// 通信ライブラリのロードに失敗しました
#define SWPLC_ERROR_PARAM				4		// 通信パラメータが不正です
#define SWPLC_ERROR_OPTIONPARAM			5		// オプションパラメータが不正です
#define SWPLC_ERROR_PORT				6		// 通信ポートの初期化に失敗しました
#define SWPLC_ERROR_BUSY				7		// 前回実行したコマンドが完了していません
#define SWPLC_ERROR_NOCOMMAND			8		// 実行コマンドが登録されていません
#define SWPLC_ERROR_OUTOFMEMORY			9		// 送受信用メモリが足りません(問合せデータ数を少なくしてください)
#define SWPLC_ERROR_TAG_RANGE			10		// タグIDが範囲外です
#define SWPLC_ERROR_TAG_NOTFOUND		11		// タグIDが登録されていません
#define SWPLC_ERROR_TAG_INVALIDTYPE		12		// タグのデータ型が不正です
#define SWPLC_ERROR_DATATYPE_MISMATCH	13		// データ型が一致しません
#define SWPLC_ERROR_SHAREMEM			14		// 共有データメモリの初期化に失敗しました(ポート名称を確認してください)
#define SWPLC_ERROR_TAG_DATACOUNT		15		// タグのデータ数が不正です
#define SWPLC_PORT_CLOSE				100		// ポートクローズ
#define SWPLC_PORT_OPEN					101		// ポートオープン
#define SWPLC_PORT_CONNECTED			102		// TCPコネクション確立
#define SWPLC_TAG_STATUS_NONE			200		// タグステータス不明
#define SWPLC_TAG_STATUS_ERROR			201		// タグステータスエラー
#define SWPLC_RESPONSE_IDLE				1000	// 実行するコマンドがありません
#define SWPLC_RESPONSE_DONE				1001	// コマンド実行完了
#define SWPLC_RESPONSE_BUSY				1002	// コマンド実行中
#define SWPLC_RESPONSE_ABORT			1003	// コマンド実行中断
#define SWPLC_RESPONSE_TIMEOUT			1004	// コマンド応答タイムアウト
#define SWPLC_RESPONSE_ERROR_PLC		1005	// PLCエラー

#define SWPLC_DATATYPE_DEFAULT			0
#define SWPLC_DATATYPE_SHORT			1
#define SWPLC_DATATYPE_USHORT			2
#define SWPLC_DATATYPE_INT				3
#define SWPLC_DATATYPE_UINT				4
#define SWPLC_DATATYPE_LONG				5
#define SWPLC_DATATYPE_ULONG			6
#define SWPLC_DATATYPE_FLOAT			7
#define SWPLC_DATATYPE_DOUBLE			8
#define SWPLC_DATATYPE_BIT				9
#define SWPLC_DATATYPE_BIT2				10

#define DEVICENAME_LENGTH	32

typedef struct SwPlcTag_t{
	int		tagId;						/* タグID */
	char	device[DEVICENAME_LENGTH];	/* デバイス名 */
	int		address;					/* レジスタアドレス番号 */
	int		dataType;					/* データ型 1:Short 2:UShort 3:Int 4:UInt 5:Long 6:ULong 7:Float 8:Double 9:Bit 10:Bit2  */
	int		count;						/* データ数 */
	int		monitor;					/* モニタ登録 0:Off 1:On */
	int		notify;						/* 通知登録 0:Off 1:On */
} SwPlcTag;

typedef int SWPLC_HANDLE;

#define SWPLC_MSG_RESPONSE		0
#define SWPLC_MSG_DATACHANGED	1

typedef void (CALLBACK *SwPlcNotifyCallBackFunc)( UINT msg, SWPLC_HANDLE handle, int param );

int WINAPI SwPlcLoadFile( SWPLC_HANDLE* handle, const char* fileName );
int WINAPI SwPlcLoadFileEx( SWPLC_HANDLE* handle, const char* fileName, const char* portName, const char* libFileName, int type, const char* param, const char* option );
int WINAPI SwPlcLoadTag( const char* fileName, SwPlcTag tags[], int* tagCount );
int WINAPI SwPlcInitPort( SWPLC_HANDLE* handle, const char* portName, const char* libFileName, int type, SwPlcTag tags[], int tagCount, const char* param, const char* option );
int WINAPI SwPlcClosePort( SWPLC_HANDLE handle );
int WINAPI SwPlcComStatus( SWPLC_HANDLE handle );
int WINAPI SwPlcExecute( SWPLC_HANDLE handle );
int WINAPI SwPlcResponse( SWPLC_HANDLE handle, int wait );
int WINAPI SwPlcClear( SWPLC_HANDLE handle );
int WINAPI SwPlcGetPlcErrorCode( SWPLC_HANDLE handle, int *pErrorCode );
int WINAPI SwPlcAbort( SWPLC_HANDLE handle );
int WINAPI SwPlcSetNotify( SWPLC_HANDLE handle, SwPlcNotifyCallBackFunc callBackFunc );
int WINAPI SwPlcRead( SWPLC_HANDLE handle, int tagId );
int WINAPI SwPlcWriteBit( SWPLC_HANDLE handle, int tagId, unsigned char data );
int WINAPI SwPlcWriteBitArray( SWPLC_HANDLE handle, int tagId, unsigned char data[], int count );
int WINAPI SwPlcWriteShort( SWPLC_HANDLE handle, int tagId, short data );
int WINAPI SwPlcWriteShortArray( SWPLC_HANDLE handle, int tagId, short data[], int count );
int WINAPI SwPlcWriteUShort( SWPLC_HANDLE handle, int tagId, unsigned short data );
int WINAPI SwPlcWriteUShortArray( SWPLC_HANDLE handle, int tagId, unsigned short data[], int count );
int WINAPI SwPlcWriteInt( SWPLC_HANDLE handle, int tagId, int data );
int WINAPI SwPlcWriteIntArray( SWPLC_HANDLE handle, int tagId, int data[], int count );
int WINAPI SwPlcWriteUInt( SWPLC_HANDLE handle, int tagId, unsigned int data );
int WINAPI SwPlcWriteUIntArray( SWPLC_HANDLE handle, int tagId, unsigned int data[], int count );
int WINAPI SwPlcWriteLong( SWPLC_HANDLE handle, int tagId, __int64 data );
int WINAPI SwPlcWriteLongArray( SWPLC_HANDLE handle, int tagId, __int64 data[], int count );
int WINAPI SwPlcWriteULong( SWPLC_HANDLE handle, int tagId, unsigned __int64 data );
int WINAPI SwPlcWriteULongArray( SWPLC_HANDLE handle, int tagId, unsigned __int64 data[], int count );
int WINAPI SwPlcWriteFloat( SWPLC_HANDLE handle, int tagId, float data );
int WINAPI SwPlcWriteFloatArray( SWPLC_HANDLE handle, int tagId, float data[], int count );
int WINAPI SwPlcWriteDouble( SWPLC_HANDLE handle, int tagId, double data );
int WINAPI SwPlcWriteDoubleArray( SWPLC_HANDLE handle, int tagId, double data[], int count );
int WINAPI SwPlcGetBit( SWPLC_HANDLE handle, int tagId, unsigned char* data );
int WINAPI SwPlcGetBitArray( SWPLC_HANDLE handle, int tagId, unsigned char data[], int count );
int WINAPI SwPlcGetShort( SWPLC_HANDLE handle, int tagId, short* data );
int WINAPI SwPlcGetShortArray( SWPLC_HANDLE handle, int tagId, short data[], int count );
int WINAPI SwPlcGetUShort( SWPLC_HANDLE handle, int tagId, unsigned short* data );
int WINAPI SwPlcGetUShortArray( SWPLC_HANDLE handle, int tagId, unsigned short data[], int count );
int WINAPI SwPlcGetInt( SWPLC_HANDLE handle, int tagId, int* data );
int WINAPI SwPlcGetIntArray( SWPLC_HANDLE handle, int tagId, int data[], int count );
int WINAPI SwPlcGetUInt( SWPLC_HANDLE handle, int tagId, unsigned int* data );
int WINAPI SwPlcGetUIntArray( SWPLC_HANDLE handle, int tagId, unsigned int data[], int count );
int WINAPI SwPlcGetLong( SWPLC_HANDLE handle, int tagId, __int64* data );
int WINAPI SwPlcGetLongArray( SWPLC_HANDLE handle, int tagId, __int64 data[], int count );
int WINAPI SwPlcGetULong( SWPLC_HANDLE handle, int tagId, unsigned __int64* data );
int WINAPI SwPlcGetULongArray( SWPLC_HANDLE handle, int tagId, unsigned __int64 data[], int count );
int WINAPI SwPlcGetFloat( SWPLC_HANDLE handle, int tagId, float* data );
int WINAPI SwPlcGetFloatArray( SWPLC_HANDLE handle, int tagId, float data[], int count );
int WINAPI SwPlcGetDouble( SWPLC_HANDLE handle, int tagId, double* data );
int WINAPI SwPlcGetDoubleArray( SWPLC_HANDLE handle, int tagId, double data[], int count );
int WINAPI SwPlcSetMonitorInterval( SWPLC_HANDLE handle, int ms );
int WINAPI SwPlcMonitorStatus( SWPLC_HANDLE handle );
int WINAPI SwPlcGetMonitorPlcErrorCode( SWPLC_HANDLE handle, int *pErrorCode );
int WINAPI SwPlcWriteLog( SWPLC_HANDLE handle, const char* logString );

#ifdef __cplusplus
}
#endif
#endif