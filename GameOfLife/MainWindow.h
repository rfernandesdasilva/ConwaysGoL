#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h";

class MainWindow : public wxFrame
{
private:
	DrawingPanel* p_drawingPanel;
public:
	MainWindow();
	~MainWindow();
};

