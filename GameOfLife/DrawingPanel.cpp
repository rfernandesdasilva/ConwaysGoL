#include "DrawingPanel.h"
#include "wx/graphics.h";
#include "wx/dcbuffer.h";	

DrawingPanel::DrawingPanel(wxWindow* parent) 
	: wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize(150,150)){

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

	p_context->SetPen(*wxBLACK);
	p_context->SetBrush(*wxWHITE);

	int k = 0;
	int p = 0;
	
	// -> will loop 225 times
	// -> p is the columns. each loop it gets added by 1 and multiplied by 10 
	// (15 squared each 10cells apart from each other)
	// -> when it reaches a number that is divisible by 15, it resets to a new row.
	// ->skips the 0 which is the first.

	//panel size
	//professor uses GetSize().x and y, and uses floats instead.
	// interactive window'is INSANEEE use it

	wxSize drawingSize = wxWindow::GetClientSize();
	int cell_width = drawingSize.GetWidth() / gridSize;
	int cell_height = drawingSize.GetHeight() / gridSize;


	for (int i = 0; i < gridSize*gridSize; i++) {
		// p* multiplied by the width that we just got in the code up there
		p_context->DrawRectangle(p* cell_width, k, cell_width, cell_height);
		p++;

		if (p % gridSize == 0) {
			if (i == 0) {
				continue;
			}
			else {
				k = k + cell_height;
				p = 0;
			}
		}

	}
}

void DrawingPanel::SetSize(wxSize& _size) {
	wxPanel::SetSize(_size);
	Refresh();
}

void DrawingPanel::SetGridSize(int _gridSize) {
	gridSize = _gridSize;
}
