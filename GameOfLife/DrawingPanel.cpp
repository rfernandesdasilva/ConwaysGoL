#include "DrawingPanel.h"
#include "wx/graphics.h";
#include "wx/dcbuffer.h";	

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& p_board)
	: wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(150, 150)), r_board(p_board) {

	p_settings = new SettingsBar();

	// There is need to have control over the rendering of the DrawingPanel. 
	//In order to tell this to the wxPanel
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);

	//In the DrawingPanel cpp file, the wxPanel needs to know to use the OnPaint method when it renders.
}

DrawingPanel::~DrawingPanel() {

}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	//LOAD CHANGES
	p_settings->LoadData();

	// Next there is need for what wxWidgets calls a wxGraphicsContext. Think of this like a drawing surface.
	wxGraphicsContext* p_context;
	p_context = wxGraphicsContext::Create(dc);

	if (!p_context) {
		return;
	}

	p_context->SetPen(*wxBLACK);
	p_context->SetBrush(*wxWHITE);

	//panel size
	//professor uses GetSize().x and y, and uses floats instead.
	// interactive window'is INSANEEE use it

	float cell_width = GetSize().x / (float)p_settings->gridSize;
	float cell_height = GetSize().y / (float)p_settings->gridSize;

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			if (r_board[i][j]) {
				p_context->SetBrush(p_settings->getLiveCellColor()); // if the block is true, paint this color
			}
			p_context->DrawRectangle(i * cell_width, j* cell_height, cell_width, cell_height);
			p_context->SetBrush(*wxWHITE);
		}
	}
}

void DrawingPanel::SetSize(wxSize& _size) {
	wxPanel::SetSize(_size);
	Refresh();
}

void DrawingPanel::SetGridSize(int _gridSize) {
	p_settings->gridSize = _gridSize;
}

void DrawingPanel::OnClick(wxMouseEvent& _mouseEvent) {
	int x = _mouseEvent.GetX();
	int y = _mouseEvent.GetY();

	wxSize drawingSize = wxWindow::GetClientSize();
	int cell_width = drawingSize.GetWidth() / p_settings->gridSize;
	int cell_height = drawingSize.GetHeight() / p_settings->gridSize;

	int column = x / cell_width;
	int row = y / cell_height;

	r_board[column][row] = true;
	Refresh();
}
