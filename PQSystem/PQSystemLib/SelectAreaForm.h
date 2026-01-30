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

#ifndef SELECTAREAFORM_H
#define SELECTAREAFORM_H

#include <QDialog>
#include "mtGraphicUnit.h"
#include "XFlexArea.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAreaForm;
}
class PQSystemRunner;

class SelectAreaForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    PQSystemRunner	*Parent;
	mtGraphicUnit	GPanel;
public:
    explicit SelectAreaForm(PQSystemRunner *runner ,QWidget *parent = 0);
    ~SelectAreaForm();
    
	FlexArea	SelectArea;

private slots:
    void on_comboBoxSelectSlave_currentIndexChanged(int index);
    void on_pushButtonSelectArea_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseWheel(int delta ,int x,int y);
	void	SlotDrawEnd(void);
protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;

private:
    Ui::SelectAreaForm *ui;
};

#endif // SELECTAREAFORM_H