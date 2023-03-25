#pragma once
#include "wx/wx.h"
#include "Settings.h"

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& p_board, std::vector<std::vector<int>>& _neighbors,
		SettingsBar* _settings);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& _event);
	void SetSize(wxSize& _size);
	void SetGridSize(int _gridSize);
	void OnClick(wxMouseEvent& _mouseEvent);

	wxString DrawHud();

	wxDECLARE_EVENT_TABLE();
private:
	int cellSize = 10; // hardcoded for now
	std::vector<std::vector<bool>>& r_board;
	std::vector<std::vector<int>>& neighborCount;

	//settings
	SettingsBar* p_settings;

};

