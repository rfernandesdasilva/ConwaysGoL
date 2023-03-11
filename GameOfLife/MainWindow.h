#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h";

class MainWindow : public wxFrame
{
private:
	DrawingPanel* p_drawingPanel;
	wxBoxSizer* p_sizer;
	std::vector<std::vector<bool>> v_board;

	int gridSize = 15;
public:
	MainWindow();
	~MainWindow();
	void onResize(wxSizeEvent& _event);
	void InitGrid();
	wxDECLARE_EVENT_TABLE();
};

