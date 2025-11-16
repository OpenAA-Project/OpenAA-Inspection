#pragma once

#include "XDLLOnly.h"

class GUICmdSetCameraWindow : public GUIDirectMessage
{
public:
	QLabel *label;
	bool ret;

public:
	GUICmdSetCameraWindow(LayersBase *Base):GUIDirectMessage(Base),label(NULL),ret(false){};
};

class GUICmdResetCameraWindow : public GUIDirectMessage
{
public:
	bool ret;

public:
	GUICmdResetCameraWindow(LayersBase *Base):GUIDirectMessage(Base),ret(false){};
};
