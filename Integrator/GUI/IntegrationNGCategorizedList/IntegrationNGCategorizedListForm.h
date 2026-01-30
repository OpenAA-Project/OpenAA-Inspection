/*
 * Copyright (C) 2022
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

#ifndef INTEGRATIONNGCATEGORIZEDLISTFORM_H
#define INTEGRATIONNGCATEGORIZEDLISTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class IntegrationNGCategorizedListForm;
}
class NGTypeList;

class IntegrationNGCategorizedListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit IntegrationNGCategorizedListForm(LayersBase *Base,QWidget *parent = 0);
    ~IntegrationNGCategorizedListForm();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonEXCEL_clicked();

private:
    Ui::IntegrationNGCategorizedListForm *ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;
    void    MakeList(void);
    QString	GetNGName(NGTypeList *p);

	Book	*XLSXBook;
	Sheet	*XLSXSheet;
	Format	*Lang;
	Font	*Fnt;

    void	WriteCell (int Row, int Col ,const QString &Str);
    void	WriteCellV(int Row, int Col ,const QVariant &Data);

};

#endif // INTEGRATIONNGCATEGORIZEDLISTFORM_H