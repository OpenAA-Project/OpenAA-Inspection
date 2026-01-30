/*
 * Copyright (C) 2025
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


#ifndef OUTSEQUENCESHOWYESNO_H
#define OUTSEQUENCESHOWYESNO_H

#include <QWidget>

namespace Ui {
class OutSequenceShowYesNo;
}
class   ThreadSequence;
class   Sequence;
class	SeqControl;

class OutSequenceShowYesNo : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceShowYesNo(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceShowYesNo();

    void	ShowMessage(QString &msg);
    int                     WRegID;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;
    ThreadSequence  *SeqParent;
private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();

private:
    Ui::OutSequenceShowYesNo *ui;
    virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // OUTSEQUENCESHOWYESNO_H