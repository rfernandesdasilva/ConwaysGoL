#pragma once

#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp
{
private:
	MainWindow* m_gameWindow = nullptr;
public:
	App();
	~App();
	virtual bool OnInit();
};

