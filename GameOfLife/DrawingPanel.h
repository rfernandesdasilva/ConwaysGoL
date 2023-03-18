#pragma once
#include "wx/wx.h"
#include "Settings.h"

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& p_board);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& _event);
	void SetSize(wxSize& _size);
	void SetGridSize(int _gridSize);
	void OnClick(wxMouseEvent& _mouseEvent);

	wxDECLARE_EVENT_TABLE();
private:
	int cellSize = 10; // hardcoded for now
	std::vector<std::vector<bool>>& r_board;

	//settings
	SettingsBar* p_settings;
};

