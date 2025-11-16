#ifndef PRECISIONCHECKERLIB_H
#define PRECISIONCHECKERLIB_H

#include <QPainter>
#include "precisioncheckerlib_global.h"
#include "mtGraphicUnit.h"

class	CImgCtrl;
class	ParamSet;
class	frm3d;
class	LayersBase;

class	PrecisionCheckerLib
{
public:
	PrecisionCheckerLib();
	~PrecisionCheckerLib();

	int CurrentPage;

	void	setPrm();
	void	SlotOnPaint(LayersBase *Layers,QPainter &pnt);

	void on_ParamButton_clicked();
	void on_Focus_clicked();
	void on_Brightness_clicked();
	void on_Resolution_clicked();
	void on_Angle_clicked();
	void on_GRP_clicked(int x1, int y1, int x2, int y2);
	void on_Histgram_clicked(int x1, int y1, int x2, int y2);

	bool	chkBit(int page ,int x ,int y);
	int		chkFlexArea(int page ,int x ,int y);

	void	BuildShow(LayersBase *Base ,int page);

	int getImgWid();
	int getImgHei();

private:
	CImgCtrl *objCtrl;
	ParamSet *objPrm;
	frm3d *obj3d;

	void	setInitRotation();
};

#endif // PRECISIONCHECKERLIB_H
