#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(400,400)) {
	p_drawingPanel = new DrawingPanel(this, v_board);
	p_sizer = new wxBoxSizer(wxVERTICAL);

	p_sizer->Add(p_drawingPanel,1, wxEXPAND | wxALL);
	this->SetSizer(p_sizer);

	this->Bind(wxEVT_SIZE, &MainWindow::onResize, this);

	MainWindow::InitGrid();
}

MainWindow::~MainWindow() {

};


void MainWindow::onResize(wxSizeEvent& _event) {
	wxSize newSize = _event.GetSize();

	p_drawingPanel->SetSize(newSize);
	_event.Skip();
}

void MainWindow::InitGrid() {
	v_board.resize(gridSize);

	for (int i = 0; i < v_board.size(); i++) {
		v_board[i].resize(gridSize);
	}

	p_drawingPanel->SetGridSize(gridSize);
}