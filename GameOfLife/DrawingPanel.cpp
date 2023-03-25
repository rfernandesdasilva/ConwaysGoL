#include "DrawingPanel.h"
#include "wx/graphics.h";
#include "wx/dcbuffer.h";	

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& p_board, std::vector<std::vector<int>>& _neighbors,
	SettingsBar* _settings)
	: wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(150, 150)), r_board(p_board), neighborCount(_neighbors) {

	m_parent = parent;
	p_settings = _settings;
	neighborCount = _neighbors;

	// There is need to have control over the rendering of the DrawingPanel. 
	//In order to tell this to the wxPanel
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->SetDoubleBuffered(true);

	//In the DrawingPanel cpp file, the wxPanel needs to know to use the OnPaint method when it renders.
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

	p_context->SetPen(wxColor(0, 0, 0, 64));
	p_context->SetBrush(*wxWHITE);

	if (!p_settings->showGrid) {
		p_context->SetPen(p_settings->getDeadCellColor());
	}

	//font for neighbor count
	p_context->SetFont(wxFontInfo(10), *wxRED);

	float cell_width = GetSize().x / (float)p_settings->gridSize;
	float cell_height = GetSize().y / (float)p_settings->gridSize;

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			p_context->SetBrush(p_settings->getDeadCellColor());

			/*float cell_width = GetSize().x / (float)p_settings->gridSize;
			float cell_height = GetSize().y / (float)p_settings->gridSize;*/

			if (r_board[i][j]) {
				p_context->SetBrush(p_settings->getLiveCellColor()); 
			}
			p_context->DrawRectangle(i * cell_width, j * cell_height, cell_width, cell_height);

			wxString count = std::to_string(neighborCount[i][j]);
			if (neighborCount[i][j] > 0 && p_settings->showCount) {

				double textWidth, textHeight;

				p_context->GetTextExtent(count, &textWidth, &textHeight);
				p_context->DrawText(count, (i * cell_width) + cell_width / 2 - textWidth / 2, 
					(j * cell_height) + cell_height / 2 - textHeight / 2);
			}
		}
	}

	if (p_settings->showThickGrid) {
		dc.SetPen(wxPen(wxColor(0, 0, 0), 2));

		int solidLines = p_settings->gridSize / 10;

		for (int i = 0; i < solidLines; i++) {
			wxPoint vStart((i + 1) * cell_width * 10, 0);
			wxPoint vEnd((i + 1) * cell_width * 10, GetSize().y);
			dc.DrawLine(vStart, vEnd);

			wxPoint hStart(0, (i + 1) * cell_height * 10);
			wxPoint hEnd(GetSize().x, (i + 1) * cell_height * 10);
			dc.DrawLine(hStart, hEnd);
		}
	}

	// Draw the HUD text if enabled
	if (p_settings->showHud) {
		p_context->SetFont(wxFontInfo(15), *wxRED);
		double textWidth, textHeight;

		p_context->GetTextExtent(DrawHud(), &textWidth, &textHeight);
		p_context->DrawText(DrawHud(), 10, GetSize().y - textHeight - 10);
	}

	delete p_context;
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

	if (r_board[column][row] == true) { // i can re-click if I made a mistake and remove the already true with this
		r_board[column][row] = false;
	}
	else {
		r_board[column][row] = true;
	}
	Refresh();
}

wxString DrawingPanel::DrawHud() {

	wxString boundaryType;
	if (p_settings->isFinite) {
		boundaryType = "Finite";
	}
	else {
		boundaryType = "Toroidal";
	}

	wxString hudText = wxString::Format("Generations: %d, Living Cells: %d, Boundary Type: %s, Universe Size: %d",
		p_settings->_generation, p_settings->_livingCells, boundaryType, p_settings->gridSize);

	return hudText;
}

