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

#include "XMacro.h"
#include <QApplication>
#include <QWidgetList>
#include <QWidget>
#include "SeqFor64Connector.h"

const	int		HostPort=15500;
const	int		WaitPeekMessageSec=3000;
const   char	*HostName="192.168.10.100";


bool    SenderSocket::SendStr(QString s)
{
	if(state() == QAbstractSocket::ConnectedState){
		char	buff[100];
		QString2Char(s,buff ,sizeof(buff));
		int	Len=strlen(buff);
		if(write(buff,Len)==Len){
			flush();
			return true;
		}
	}
	return false;
}
void	SenderSocket::SlotReadyRead()
{
	qint64 Len=read(&ReqBuffer[0], sizeof(ReqBuffer) - 1);
    if (Len <= 0)
        return;
    // Remove end of line marker
    while ((Len > 0) && ((ReqBuffer[Len - 1] == '\r') || (ReqBuffer[Len - 1] == '\n')))
        Len--;
    ReqBuffer[Len] = 0;
    ReqMode=false;
	if(stricmp(ReqBuffer,"UnitStart")==0){
		UnitStart=true;
	}
}

//SenderSocket	*MachineSocket=NULL;

//================================================================================================

void    SeqFor64Connector::TryConnection(QApplication &App )
{
    if(MachineSocket==NULL){
		QWidgetList	L=App.topLevelWidgets();
		if(L.count()==0)
			MachineSocket=new SenderSocket(&App);
		else{
            QWidget *w=L.value(0);
			MachineSocket=new SenderSocket(w);
        }

		MachineSocket->connect(MachineSocket,SIGNAL(readyRead()),MachineSocket,SLOT(SlotReadyRead()));
	}
    if (MachineSocket->state() == QAbstractSocket::UnconnectedState) {
		MachineSocket->connectToHost ( QString(HostName), HostPort, QIODevice::ReadWrite | QIODevice::Text) ;
		MachineSocket->waitForConnected (1000);
	}
}

bool    SeqFor64Connector::IsConnectedToServer(void)
{
    if(MachineSocket==NULL)
        return(false);
    if(MachineSocket->state()==QAbstractSocket::ConnectedState)
        return(true);
    return(false);
}

//================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SeqFor64Connector";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "SeqFor64Connector";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"SeqFor64Connector");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	SeqFor64Connector	*LSeq=new SeqFor64Connector();
	return LSeq;
}

DEFFUNCEX		bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	SeqFor64Connector	*LSeq=(SeqFor64Connector *)handle;

    if(cmdstr=="InitStage"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->SendStr("InitStage\r\n");
		}
	}
    else
    if(cmdstr=="StartStage"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->SendStr("StartStage\r\n");
		}
	}
    else
    if(cmdstr=="RepeatStage"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->SendStr("RepeatStage\r\n");
		}
	}
    else
    if(cmdstr=="SetResult1"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->SendStr("SetResult1\r\n");
		}
	}
    else
    if(cmdstr=="SetResult2"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->SendStr("SetResult2\r\n");
		}
	}
    return(true);
}

bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	SeqFor64Connector	*LSeq=(SeqFor64Connector *)handle;

    if(cmdstr=="SetResult"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->ReqMode=true;
            LSeq->MachineSocket->SendStr(QString("SetResult")
								 +QString::number(*data)
                                 +QString("\r\n"));
            App.processEvents();
		}
	}
    else
    if(cmdstr=="IsStartKensa"){
        if(LSeq->IsConnectedToServer()==false)
            LSeq->TryConnection(App);
        if(LSeq->IsConnectedToServer()==true){
            LSeq->MachineSocket->ReqMode=true;
            LSeq->MachineSocket->SendStr("IsStartKensa\r\n");
            for(time_t t=time(NULL);time(NULL)-t<WaitPeekMessageSec;){
                App.processEvents();
                *data=0;
                if(LSeq->MachineSocket->ReqMode==false){
                    if(sscanf(LSeq->MachineSocket->ReqBuffer,"%d",data)==1)
                        break;
				}
			}
		}
	}
    return(true);
}

void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
	SeqFor64Connector	*LSeq=(SeqFor64Connector *)handle;

	if(LSeq->MachineSocket!=NULL && LSeq->IsConnectedToServer()==true){
		LSeq->MachineSocket->disconnectFromHost();
		LSeq->MachineSocket->waitForDisconnected(1000);
	}
	delete	LSeq->MachineSocket;
	delete	LSeq;
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}