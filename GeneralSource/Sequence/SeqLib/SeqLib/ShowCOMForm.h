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

#ifndef SHOWCOMFORM_H
#define SHOWCOMFORM_H

#include <QWidget>

namespace Ui {
class ShowCOMForm;
}

class CommOperand;

class ShowCOMForm : public QWidget
{
    Q_OBJECT

    CommOperand *OpeIndex;
public:
    explicit ShowCOMForm(CommOperand *Ope ,QWidget *parent = nullptr);
    ~ShowCOMForm();

private:
    Ui::ShowCOMForm *ui;
    virtual void closeEvent(QCloseEvent *event)     override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    QString GetBinaryStr(const QByteArray &str);

private slots:
	void	SlotTx(const QByteArray &str);
	void	SlotRx(const QByteArray &str);
};

#endif // SHOWCOMFORM_H