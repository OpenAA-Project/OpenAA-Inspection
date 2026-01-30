/*
 * Copyright (C) 2021
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

#ifndef SHOWOPERATIONALPANEL_H
#define SHOWOPERATIONALPANEL_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class ShowOperationalPanel;
}

class	DisplaySimPanelBusLine : public DisplaySimPanel
{
	BYTE	**BMapOpen;
	BYTE	**BMapShort;
	BYTE	**BMapBinary;
	int		BMapXByte;
	int		BMapYLen;
	int		MapXPos, MapYPos;

	bool	ModeShowMapOpen ;
	bool	ModeShowMapShort;
	bool	ModeShowMapBinary;
	QImage* ResultImageOpen;
	QImage* ResultImageShort;
	QImage* ResultImageBinary;
public:
	DisplaySimPanelBusLine(LayersBase* base, QWidget* parent = 0);
	~DisplaySimPanelBusLine(void);

	virtual	void	SetInitial(int ItemID, FlexArea& InitialArea);

	void	CopyMap(BYTE **MapOpen , BYTE **MapShort , BYTE** MapBinary ,int XByte ,int YLen
					,int XPos ,int YPos);

	void	SetModeMap(bool ModeShowMapOpen ,bool ModeShowMapShort, bool ModeShowMapBinary);
protected:
	virtual	void	PaintAfter(QPainter& pnt);
};

class ShowOperationalPanel : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
public:
    explicit ShowOperationalPanel(LayersBase *Base,QWidget *parent = 0);
    ~ShowOperationalPanel();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

    void on_pushButtonCalc_clicked();
    void on_checkBoxDarkside_clicked();
    void on_checkBoxCompareToMaster_clicked();
    void on_checkBoxReduceNoise_clicked();
    void on_EditBinarizedLength_valueChanged(int arg1);
    void on_EditReferredBrightness_valueChanged(int arg1);
    void on_checkBoxAutoBinarize_clicked();
    void on_EditSearchDotToMaster_valueChanged(int arg1);
    void on_EditMinWidth_valueChanged(int arg1);
    void on_EditMinGap_valueChanged(int arg1);
    void on_EditOKNickRate_valueChanged(int arg1);
    void on_EditOKShortRate_valueChanged(int arg1);
    void on_toolButtonSimShowOpen_clicked();
    void on_toolButtonSimShowShort_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditMinSize_valueChanged(int arg1);

    void on_toolButtonSimShowBinary_clicked();

private:
    Ui::ShowOperationalPanel *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;
	DisplaySimPanelBusLine		SimPanel;
	bool	OnChanging;

	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	CreateThreshld(void);

	int		MinWidth;	
	int		MinGap;		
	int		LimitDot;	
	int64	MinArea;
	int64	MaxArea;
	int		MinSize;
	bool	Darkside;
	bool	CompareToMaster;
	bool	AutoBinarize;
	bool	ReduceNoise;
	int		BinarizedLength;
	int		ReferredBrightness;
	int		SearchDotToMaster;
	int		WidthToIgnoreEdge;
	int		OKNickRate;			//0-100% for MinWidth
	int		OKShortRate;		//0-100% for MinGap
	int		BrightnessWidthInsideL ;
	int		BrightnessWidthInsideH ;
	int		BrightnessWidthOutsideL;
	int		BrightnessWidthOutsideH;
};

#endif // SHOWOPERATIONALPANEL_H