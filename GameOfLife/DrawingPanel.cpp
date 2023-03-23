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
	
	neighborCount.resize(p_settings->gridSize);

	for (int i = 0; i < neighborCount.size(); i++) {
		neighborCount[i].resize(p_settings->gridSize);
	}

	// Next there is need for what wxWidgets calls a wxGraphicsContext. Think of this like a drawing surface.
	wxGraphicsContext* p_context;
	p_context = wxGraphicsContext::Create(dc);

	if (!p_context) {
		return;
	}

	p_context->SetPen(*wxBLACK);
	p_context->SetBrush(*wxWHITE);

	// red = dead next gen
	// green alive next gen
	// implement that.

	//font for neighbor count
	p_context->SetFont(wxFontInfo(16), *wxRED);

	float cell_width = GetSize().x / (float)p_settings->gridSize;
	float cell_height = GetSize().y / (float)p_settings->gridSize;

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			if (p_settings->showCount) {
				CheckNeighboors(i,j); // test

				wxString count = std::to_string(neighborCount[i][j]);
				wxDouble* x = new wxDouble;
				wxDouble* y = new wxDouble;

				*x = ((double)i * (double)cell_width) / 2;
				*y = ((double)j * (double)cell_height) / 2;

				p_context->GetTextExtent(count, x, y);
				p_context->DrawText(count, *x, *y);
			}

			if (r_board[i][j]) {
				p_context->SetBrush(p_settings->getLiveCellColor()); // if the block is true, paint this color
				p_context->DrawRectangle(i * cell_width, j * cell_height, cell_width, cell_height);
				continue;
			}

			//font for neighbor count if it is not a cell
			p_context->SetFont(wxFontInfo(16), *wxGREEN);

			p_context->SetBrush(p_settings->getDeadCellColor());
			p_context->DrawRectangle(i * cell_width, j* cell_height, cell_width, cell_height);
			//p_context->SetBrush(p_settings->getDeadCellColor());
		}
	}
}

int DrawingPanel::CheckNeighboors(int _row, int _column) {

	//row-1, column-1          row-1, column         row - 1, column+1
	//row, column-1            row, column           row, column+1
	//row+1, column-1          row+1, column         row+1, column+1

	// how to check if it is in bounds: 
	// -> check if the row >= 0 && row < gridSize
	// -> check if column >= 0 && column < gridSize

	// the algorithm will run max 8 times, as it is the max amount of neighboors possible.
	// i and j have to start on -1 so it checks those ranges first.

	int result = 0;
	for (int i = _row - 1; i <= _row + 1; i++) {
		for (int j = _column - 1; j <= _column + 1; j++) {
			if (i >= 0 && i < p_settings->gridSize && j >= 0 && j < p_settings->gridSize) {
				if (i != _row || j != _column) {
					if (neighborCount[i][j]) {
						result++;
					}
				}
			}
		}
	}
	neighborCount[_row][_column] = result;

	return result;
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
