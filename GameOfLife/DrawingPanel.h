#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel();
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);

private:

};

