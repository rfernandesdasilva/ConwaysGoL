#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& _event);

private:
	int gridSize = 15;
	int cellSize = 10; // hardcoded for now
};

