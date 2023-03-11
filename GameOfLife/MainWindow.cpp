#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include "next.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::onResize)
EVT_MENU(10998, MainWindow::PlayButton)
EVT_MENU(20998, MainWindow::PauseButton)
EVT_MENU(26754, MainWindow::TrashButton)
EVT_MENU(12345, MainWindow::NextButton)
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
	p_toolBar->AddTool(26754, "Trash", trashIcon);
	
	wxBitmap nextIcon(next_xpm);
	p_toolBar->AddTool(12345, "Next", nextIcon);

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
	livingCells = 0;
 	generation = 0;

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			v_board[i][j] = false;
		}
	}

	UpdateStatusBar();
	Refresh();
}

void MainWindow::NextButton(wxCommandEvent& _nextEvent) {
	CreateNextGen();
}

int MainWindow::CheckNeighboors(int _row, int _column) {

	//row-1, column-1          row-1, column         row - 1, column+1
	//row, column-1            row, column           row, column+1
	//row+1, column-1          row+1, column         row+1, column+1

	// how to check if it is in bounds: 
	// -> check if the row >= 0 && row < gridSize
	// -> check if column >= 0 && column < gridSize

	// the algorithm will run max 8 times, as it is the max amount of neighboors possible.
	// i and j have to start on -1 so it checks those ranges first.

	int result = 0;
	for (int i = _row-1; i <= _row+1; i++) {
		for (int j = _column-1; j <= _column+1; j++) {
			if (i >= 0 && i < gridSize && j >= 0 && j < gridSize) {
				if (i != _row || j != _column) {
					if (v_board[i][j]) {
						result++;
					}
				}
			}
		}
	}


	return result;
}

void MainWindow::CreateNextGen() {

	std::vector<std::vector<bool>> sandbox;
	sandbox.resize(gridSize);
	for (int i = 0; i < sandbox.size(); i++) {
		sandbox[i].resize(gridSize);
	}

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			int count = CheckNeighboors(i, j);
			
			if (v_board[i][j] && count < 2) {
				sandbox[i][j] = false;
				livingCells--;
				continue;
			} 
			if (v_board[i][j] && count > 3) {
				sandbox[i][j] = false;
				livingCells--;
				continue;
			}
			if (count == 2 || count == 3) {
				{
					if (v_board[i][j]) {
						sandbox[i][j] = true;
						livingCells++;
						continue;
					}
				}
			}
			if (!v_board[i][j] && count == 3) {
				sandbox[i][j] = true;
				livingCells++;
				continue;
			}
		}
	}

	v_board.swap(sandbox);
	generation++;
	UpdateStatusBar();
	Refresh();
}