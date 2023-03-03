#include "DrawingPanel.h"
#include "wx/graphics.h";
#include "wx/dcbuffer.h";	

DrawingPanel::DrawingPanel() : wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(150,150)){

	// There is need to have control over the rendering of the DrawingPanel. 
	//In order to tell this to the wxPanel
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);

	//In the DrawingPanel cpp file, the wxPanel needs to know to use the OnPaint method when it renders.
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel() {

}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();


	// Next there is need for what wxWidgets calls a wxGraphicsContext. Think of this like a drawing surface.
	wxGraphicsContext* p_context;
	p_context = wxGraphicsContext::Create(dc);

	if (!p_context) {
		return;
	}


}