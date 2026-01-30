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

#ifndef INTEGRATIONTHUMBNAILFORM_H
#define INTEGRATIONTHUMBNAILFORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationThumbnailForm;
}
class	IntegrationThumbnailForm;

class	ThumbnailPanel : public NPList<ThumbnailPanel> , public QWidget
{
	friend	class IntegrationThumbnailForm;

	IntegrationThumbnailForm	*Parent;
	int		ID;
	EachMaster	*Master;
	QImage	*Image;
	int		Phase;
	int		Page;
	IntegBindedNGArea	*Point;
public:
	int	Row,Column;

	ThumbnailPanel(int id,IntegrationThumbnailForm *p ,EachMaster *m,int phase,int page,IntegBindedNGArea *point);
	~ThumbnailPanel(void);

	void	MakeImage(void);
private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};


class IntegrationThumbnailForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	friend	class	ThumbnailPanel;

	NPListPack<ThumbnailPanel>	Panels;
	InspectionList			*CurrentInspection;
	int	CurrentIndex;
public:
	int32	ShownMachineCode;	//-1:Nothing
	int32	ShownPhase;
	bool	ShowMaster;
	int32	ThumbnailWidth;
	int32	ThumbnailHeight;
	int32	ThumbnailMergin;
	double	ZoomRate;
	bool	ShowInformation;

    explicit IntegrationThumbnailForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationThumbnailForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
	void	ResizeAction();

private:
    Ui::IntegrationThumbnailForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	ShowNGImages(void);

	virtual	void keyPressEvent( QKeyEvent * event )	override;
	ThumbnailPanel	*GetPanel(int index);
	ThumbnailPanel	*GetPanel(int row ,int column);
	ThumbnailPanel	*GetPanelRight(int row);

	QString	GetInformation(NGPoint *p);

	void	RepaintPanel(void);
	void	BroadcastNGPoint(void);
	void	ShowNGImages(int _ShownPhase,EachMaster *m);
	virtual	void	StartLot	(void)	override;
};



#endif // INTEGRATIONTHUMBNAILFORM_H