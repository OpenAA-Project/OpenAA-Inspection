#ifndef MATRIXCELLLISTFORM_H
#define MATRIXCELLLISTFORM_H

#include "XGUIFormBase.h"
#include "ui_MatrixCellListForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "mtToolButtonColored.h"
#include "MatrixHeader.h"

class	MatrixCell : public NPList<MatrixCell>
{
public:
	int	x1,y1,x2,y2;
	QString		AreaName;
	QStringList	Namings;
	enum	DrawAttr {
		_Normal		=0
		,_Active	=1
		,_NGArea	=2
	}Attr;
	int	IndexX,IndexY;
	QImage	*Img;

	MatrixCell(void){	Attr=_Normal;	Img=NULL;	}
	~MatrixCell(void);

	void	Draw(QPainter &pnt,int movx, int movy ,double ZoomRate,DrawAttr Attr,const QColor &FrameDefaultColor);
	void	WholeDraw(QPainter &pnt,int movx, int movy ,double ZoomRate,DrawAttr Attr,const QColor &FrameDefaultColor);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	void	GetCenter(int &cx ,int &cy){	cx=(x1+x2)/2;	cy=(y1+y2)/2;	}
};

class	NGPieceList : public NPList<NGPieceList>
{
public:
	int	x1,y1,x2,y2;
	QString	NGPieceName;
	bool	NG;
	QColor	FrameColor;
	QImage	*Img[10];
	QColor	ColList[10];

	NGPieceList(void);
	~NGPieceList(void);

	void	Draw(QPainter &pnt,int movx, int movy ,double ZoomRate);
	QImage	*GetImg(int W, int H);
};

class	PieceColorInfo : public NPList<PieceColorInfo>
{
public:
	QString	NGPieceName;
	QColor	FrameColor;

	PieceColorInfo(void){}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class MatrixCellListForm : public GUIFormBase,public FunctionServerClass
{
	Q_OBJECT

public:
	NPListPack<NGPieceList>	NGPieces;
	NPListPack<MatrixCell>	MatrixCellData;
	int		CellSizeX;
	int		CellSizeY;	
	int		StartX	,StartY;
	int		EndX	,EndY;
	int		CellType;
	QString	LogPath;

	QString	DisplayImageRoot;
	QString	DisplayImageName;
	QString	DisplayImageInst;
	QString	WholeImageInstName;
	MatrixCell	***MatrixCellDim;
	int		MatrixCellDimXNumb;
	int		MatrixCellDimYNumb;
	mtToolButtonColored	ButtonFrameColor;
	QColor	FrameDefaultColor;

	NPListPack<PieceColorInfo>	PieceColorInfoForLoad;

	MatrixCellListForm(LayersBase *Base ,QWidget *parent = 0);
	~MatrixCellListForm();

	virtual void	BuildForShow(void)	override;
	void	Draw(QPainter &pnt,int movx ,int movy ,double ZoomRate);
	void	WholeDraw(QPainter &pnt,int movx ,int movy ,double ZoomRate);

	void	CreateCells(int CellType);
	void	MakeIndex(int CellType);
	void	ShowList(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void 	WriteLog(void);
	void	ClickImagePanel(int GlobalPosX,int GlobalPosY);

private:
	Ui::MatrixCellListFormClass ui;

	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
	bool	SaveMatrixCell(QIODevice *f);
	bool	LoadMatrixCell(QIODevice *f);

private slots:
	void on_toolButtonPiece_clicked();
	void on_tableWidget_itemSelectionChanged();
	void on_tableWidget_clicked(const QModelIndex &);
	void on_pushButtonSet_clicked();
	void	ResizeAction();
};

class	CmdSaveMatrixCellFile	:public GUIDirectMessage
{
public:
	QIODevice	*FL;
	CmdSaveMatrixCellFile(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdLoadMatrixCellFile	:public GUIDirectMessage
{
public:
	QIODevice	*FL;
	CmdLoadMatrixCellFile(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdCreateMatrixCell	:public GUIDirectMessage
{
public:
	CmdCreateMatrixCell(LayersBase *base):GUIDirectMessage(base){}
};


#endif // MATRIXCELLLISTFORM_H
