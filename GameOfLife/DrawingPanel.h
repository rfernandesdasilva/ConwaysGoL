#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& _event);
	void SetSize(wxSize& _size);

	void SetGridSize(int _gridSize);
private:
	int gridSize;
	int cellSize = 10; // hardcoded for now
	//std::vector<std::vector<bool>>& r_board;
};

