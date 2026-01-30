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

#ifndef OUTSEQUENCEINPUT_H
#define OUTSEQUENCEINPUT_H

#include <QWidget>
#include <QString>
#include <QShowEvent>
#include <QCloseEvent>

namespace Ui {
class OutSequenceInput;
}
class	SeqControl;
class	ThreadSequence;

class OutSequenceInput : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceInput(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceInput();

    volatile    bool    OnAwake;
    bool        OKMode;
    QString		MessageData;
    QString		DefaultString;
    QString		Ret;
    void	ShowMessage(QString &msg ,QString &defaultstring);

    virtual void showEvent ( QShowEvent * event )	override;
    virtual void closeEvent ( QCloseEvent * e )		override;
    ThreadSequence  *SeqParent;

private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();

private:
    Ui::OutSequenceInput *ui;
};

#endif // OUTSEQUENCEINPUT_H