#ifndef CIMGCTRL_H
#define CIMGCTRL_H
#include "XFlexArea.h"
#include "XDataInLayer.h"
#include "NList.h"
#include "CImgCtrl_pack.h"


class CImgCtrl
{
public:
	CImgCtrl();
	~CImgCtrl();

	int nThreshValueMin;
	int nThreshValueMax;
	bool bThreshMode;

	void makeImgTbl(int _nPage, int _nWid, int _nHei);
	void setImgTblBuf();
	void setImgTblBuf(int nPageIdx, DataInPage *dp);

	bool chkBit(int nPageIdx, int nXPnt, int nYPnt);

	bool setFlexArea(int nPageIdx);
	int chkFlexArea(int nPageIdx,int nXPnt, int nYPnt);

	BYTE ***oImgTbl;
	PureFlexAreaListContainer *tblFArea;
	int nLstCnt;

	int nWid;
	int nHei;
	int nBytWid;
	int nBytHei;
	int nPage;

	double dRadEMargin;

	BYTE ***oFAreaBitBuf;

	/// pbg
	NPListPack<clsPadCnt> *tblPadCnt;

	clsPadAreaPack	 *tblPadArea;

	void setRangePatternByte(int min, int max);
	void setThreshValue(int min, int max, bool mode);

	void viewHistgram(int nPageIdx, int x1, int y1, int x2, int y2);

private:
	BYTE **oTmp;

	void setFAreaBitBuf(int nPageIdx);
	void setFAreaBitBufOnBit(int nPageIdx, int nXPnt, int nYPnt);
	void setFAreaBitBufOnRange(int nPageIdx, int nXPnt1, int nXPnt2, int nYPnt );

	void sortFAreaLst(int nPageIdx);
	int sortFAreaLstLine(clsPadAreaPack &lstSrc, clsPadAreaPack &lstDst, clsPadArea *minFArea);
	clsPadArea *getMinFArea(clsPadAreaPack &lst);
	clsPadArea *getNextFArea(clsPadAreaPack &lst, clsPadArea *minFArea);

	void calcLen(double x1, double x2, double y1, double y2, double &len, double &rad);

	double getLineRadian(clsPadArea *minFArea,clsPadAreaPack &lstSrc);
	bool chkFAreaRadian(clsPadArea *area, double x1, double y1, double srad);
	double radBase;

	int nMinPatternByte;
	int nMaxPatternByte;

	// デバック関連
	void dbgOutImgTblBuf(BYTE **bitBuff, int nPageIdx);
	void dbgPrtFlexAreaList(int nPageIdx, bool flg=false);
	void dbgPrtFlexAreaList(PureFlexAreaListContainer &lst,int no=0);
	void dbgPrtPadCnt(NPListPack<clsPadCnt> &lst, int no=0);
	void dbgPrtPadArea(clsPadAreaPack &lst, NPListPack<clsPadCnt> &clst, int no=0);

	bool chkIllFlexArea(int x, int y, int cnt, int nPage);
	bool chkYAxis(clsPadArea *minFArea, clsPadArea *cur);

	void startTimeLog();
	void wrtTimeLog(char *mess);
	void endTimeLog();

	int nStartY;
	int getThreshHold(ImageBuffer *ibfBuf, int i);
	int getThreshHold1(ImageBuffer *ibfBuf, int startX, int endX, int nStartY=0);
	int getThreshHold2(ImageBuffer *ibfBuf, int startX, int endX, int nStartY=0);
	int getThreshHold3(ImageBuffer *ibfBuf, int startX, int endX, int nStartY=0);

	bool unitThreshold(int nPageIdx, ImageBuffer *ibfBuf);
	int getThreshold_unit(int *hist, int n, double *k);
	int getThreshold_unit2(int *hist, int n, double *k);

	// ラベリング関連
	bool labelFArea(int nPageIdx);
	int labelFAreaLstLine(clsPadAreaPack &lstSrc, clsPadAreaPack &lstDst, clsPadArea *minFArea);
	clsPadArea *getLabelNextFArea(clsPadArea *minFArea,clsPadAreaPack &lstSrc);

	int ImgDevCnt;
	int calcHistgram(int nPageIdx, int x1, int y1, int x2, int y2, QList<double> &arrX, QList<double> &arrY);
};

#endif // CIMGCTRL_H
