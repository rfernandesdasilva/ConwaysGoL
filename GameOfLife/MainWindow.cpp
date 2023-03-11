#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include "next.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::onResize)
EVT_MENU(10998, MainWindow::PlayButton)
EVT_MENU(10998, MainWindow::PauseButton)
EVT_MENU(10998, MainWindow::TrashButton)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(400,400)) {

	// statusBar stuff
	p_statusBar = CreateStatusBar();
	livingCells = 0;
	generation = 0;
	UpdateStatusBar();


	//figure out if I can organize this into a method for reading clarity
	p_toolBar = CreateToolBar();

	wxBitmap playIcon(play_xpm);
	p_toolBar->AddTool(10998, "Play", playIcon);

	wxBitmap pauseIcon(pause_xpm);
	p_toolBar->AddTool(20998, "Pause", pauseIcon);

	wxBitmap trashIcon(trash_xpm);
	p_toolBar->AddTool(30998, "Trash", trashIcon);
	
	wxBitmap nextIcon(next_xpm);
	p_toolBar->AddTool(40998, "Next", nextIcon);

	p_toolBar->Realize(); // render the icons onto the screen

	//drawing panel
	p_drawingPanel = new DrawingPanel(this, v_board);
	p_sizer = new wxBoxSizer(wxVERTICAL);

	p_sizer->Add(p_drawingPanel,1, wxEXPAND | wxALL);
	this->SetSizer(p_sizer);

	MainWindow::InitGrid();
	this->Layout();
}

MainWindow::~MainWindow() {

};

void MainWindow::UpdateStatusBar() {
	wxString statusText = wxString::Format("Generation: %d, Living Cells: %d", generation, livingCells);
	p_statusBar->SetStatusText(statusText);
}

void MainWindow::onResize(wxSizeEvent& _event) {
	wxSize newSize = _event.GetSize();

	// Before running that line, add a check to make sure that the drawing panel is not nullptr.  
	if (p_drawingPanel == nullptr) {
		return;
	}
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

void MainWindow::PlayButton(wxCommandEvent& _playEvent) {

}

void MainWindow::PauseButton(wxCommandEvent& _pauseEvent) {

}

void MainWindow::TrashButton(wxCommandEvent& _trashEvent) {

}

void MainWindow::NextButton(wxCommandEvent& _nextEvent) {

}