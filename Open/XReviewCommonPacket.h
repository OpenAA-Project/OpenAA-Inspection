#pragma once

#include <QDialog>

#include "XDLLOnly.h"
#include "XReviewCommon.h"

namespace ReviewCommonPacket{

class CmdReqSettingPropertyDialog : public GUIDirectMessage
{
public:
	//Recieve
	QDialog *m_dialog;
	QString m_GroupName;
	QString m_GUIName;

public:
	void setDialog(QDialog *dlg){ m_dialog = dlg; };
	void setGroupName(const QString &name){ m_GroupName = name; };
	void setGUIName(const QString &name){ m_GUIName = name; };

	QDialog *dialog() const { return m_dialog; };
	QString groupName() const { return m_GroupName; };
	QString GUIName() const { return m_GUIName; };

public:
	bool isValid() const { return (dialog()!=NULL && groupName().isEmpty()==false && GUIName().isEmpty()==false); };

public:
	CmdReqSettingPropertyDialog(LayersBase *Base):GUIDirectMessage(Base),m_dialog(NULL),m_GroupName(),m_GUIName(){};
};

class CmdMoveVRSWithAlignment : public GUIDirectMessage
{
	friend class ReviewPIBase;
public:
	void setMachineID(int id){ _MachineID = id; };
	void setX(int x_){ _x = x_; };
	void setY(int y_){ _y = y_; };
	void setPhase(int phase_){ _phase = phase_; };
	void setPage(int page_){ _page = page_; };
	void setOutlineOffset(const QPoint &offset){ _outlineOffset = offset; _isOutlineOffsetEnable = true; };
	void setOutlineOffsetEnable(bool enable){ _isOutlineOffsetEnable=enable; };

	int machineID() const { return _MachineID; };
	int x() const { return _x; };
	int y() const { return _y; };
	int phase() const { return _phase; };
	int page() const { return _page; };
	QPoint outlineOffset() const { return _outlineOffset; };
	bool isOutlineOffsetEnable() const { return _isOutlineOffsetEnable; };

public:
	bool isEnable() const { return (machineID()!=-1 && phase()!=-1 && page()!=-1); };

private:
	int _MachineID;
	int _x;
	int _y;
	int _phase;
	int _page;

	QPoint _outlineOffset;
	bool _isOutlineOffsetEnable;

public:
	QString errorMsg() const { return _errMsg; };
	bool hasError() const { return !errorMsg().isEmpty(); };

private:
	void _setErrorMsg(const QString &msg){ _errMsg = msg; };

private:
	QString _errMsg;
	
public:
	CmdMoveVRSWithAlignment(LayersBase *Base):GUIDirectMessage(Base),_MachineID(-1),_x(0),_y(0),_phase(-1),_page(-1),_outlineOffset(),_isOutlineOffsetEnable(false),_errMsg(){};
};

class CmdMoveVRSToOrigin : public GUIDirectMessage
{
public:
	CmdMoveVRSToOrigin(LayersBase *Base):GUIDirectMessage(Base){};
};

}