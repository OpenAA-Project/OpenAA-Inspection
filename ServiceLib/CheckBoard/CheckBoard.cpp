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

#include "CheckBoard.h"
#include "ShowRebootForm.h"
#include "XForWindows.h"

CheckBoard::CheckBoard(const QString &_BoardName
                    ,bool    _CheckExistence
                    ,int	 _LinkWidth
                    ,int     _WaitingSec
                    ,QWidget *parent)
    : QMainWindow(parent)
	,BoardName(_BoardName)
	,CheckExistence(_CheckExistence)
	,LinkWidth(_LinkWidth)
	,WaitingSec(_WaitingSec)
{
    ui.setupUi(this);

	CurrentSec=0;

	ui.progressBar->setMaximum(WaitingSec);
	ui.progressBar->setValue(CurrentSec);
	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(OnTimerTicked()));
	TM.start();
}

CheckBoard::~CheckBoard()
{}

void CheckBoard::OnTimerTicked()
{
	CurrentSec++;
	ui.progressBar->setValue(CurrentSec);
	if(CurrentSec>=WaitingSec){
		TM.stop();

		NPListPack<BoardInfoList> BoardInfo;
		GetBoardInfo(BoardInfo);
		bool RebootNeededByExistence = false;
		bool RebootNeededByLinkWidth = false;

		if(CheckExistence==true){
			RebootNeededByExistence =true;
			for(BoardInfoList *a=BoardInfo.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->BoardName.compare(BoardName,Qt::CaseInsensitive)==0){
					RebootNeededByExistence = false;
				}
			}
		}
		if(LinkWidth!=0){
			RebootNeededByLinkWidth =true;
			for(BoardInfoList *a=BoardInfo.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->BoardName.compare(BoardName,Qt::CaseInsensitive)==0){
					if(a->LinkWidth==LinkWidth){
						RebootNeededByLinkWidth = false;
					}
				}
			}
		}
		int RebootReasonIndex = -1;
		if(RebootNeededByExistence==true){
			RebootReasonIndex = 0;
		}
		else if(RebootNeededByLinkWidth==true){
			RebootReasonIndex = 1;
		}
		if(RebootReasonIndex>=0){
			ShowRebootForm *SRF = new ShowRebootForm(RebootReasonIndex);
			connect(SRF,SIGNAL(SignalTimeUp()),this,SLOT(SlotReboot()));
			SRF->show();
		}
	}
}

void CheckBoard::on_pushButtonStopCheck_clicked()
{
	close();
}

void CheckBoard::SlotReboot()
{
	::MtShutdownSelfPC( true, true);
	close();
}

