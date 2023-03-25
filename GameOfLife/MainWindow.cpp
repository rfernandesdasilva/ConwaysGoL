#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include "next.xpm"

#include "wx/numdlg.h"
#include "wx/filedlg.h"
#include <wx/stream.h>
#include <wx/wfstream.h>

#include "SettingsStorage.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

//windowResize
EVT_SIZE(MainWindow::onResize)

//play, pause, clear, next, timedEvent(for pause)
EVT_MENU(10998, MainWindow::PlayButton)
EVT_MENU(20998, MainWindow::PauseButton)
EVT_MENU(26754, MainWindow::TrashButton)
EVT_MENU(12345, MainWindow::NextButton)
EVT_TIMER(14896, MainWindow::TimedEvent)

//random/seed
EVT_MENU(16821, MainWindow::OnRandom)
EVT_MENU(12821, MainWindow::OnRandomSeed)

//files
EVT_MENU(wxID_NEW, MainWindow::OnNew)
EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
EVT_MENU(wxID_SAVE, MainWindow::OnSave)
EVT_MENU(wxID_SAVEAS, MainWindow::OnSaveAs)
EVT_MENU(wxID_EXIT, MainWindow::OnExit)
EVT_MENU(16870, MainWindow::OnImport)

//universeTypes
EVT_MENU(12785, MainWindow::OnToroidalToggle)
EVT_MENU(17942, MainWindow::OnFiniteToggle) 
EVT_MENU(12781, MainWindow::OnShowCountToggle) 
EVT_MENU(11625, MainWindow::OnGridToggle)
EVT_MENU(11627, MainWindow::OnThickGridToggle)
EVT_MENU(12788, MainWindow::OnHudToggle) // 12788

//// grid but inside the view
//p_viewGrid = new wxMenuItem(p_viewSettings, 11625, "Grid Toggle", "", wxITEM_CHECK);
//p_viewThickGrid = new wxMenuItem(p_viewSettings, 11627, "Grid 10x Toggle", "", wxITEM_CHECK);

//reset settigns
EVT_MENU(14539, MainWindow::OnResetSettings)

//menuBar
EVT_MENU(19981,MainWindow::OnMenuColor) // cell config 19921
EVT_MENU(19921, MainWindow::OnMenuCell)
wxEND_EVENT_TABLE()


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(400,400)) {

	// settings
	p_settings = new SettingsBar();
	p_settings->LoadData();

	// statusBar stuff
	p_statusBar = CreateStatusBar();
	livingCells = 0;
	p_settings->_generation = 0;
	generation = 0;
	p_settings->_livingCells = 0;
	UpdateStatusBar();

	p_timer = new wxTimer(this, 14896); // randomID

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

	// menuBar
	p_menuBar = new wxMenuBar();
	this->SetMenuBar(p_menuBar);

	// menu Options - Cell Configuration
	wxMenu* p_menuOptions = new wxMenu();
	p_menuOptions->Append(19981, "Color Options");
	p_menuOptions->Append(19921, "Cell Options");
	p_menuOptions->AppendSeparator();
	p_menuOptions->Append(14539, "Reset Settings");

	// Randomize
	wxMenu* p_randomOptions = new wxMenu();
	p_randomOptions->AppendSeparator();
	p_randomOptions->Append(16821, "Randomize with Time");
	p_randomOptions->Append(12821, "Randomize with Seed");

	// File Settings
	wxMenu* p_fileOptions = new wxMenu();
	p_fileOptions->Append(wxID_NEW, "&New\tCtrl+N");
	p_fileOptions->Append(wxID_OPEN, "&Open\tCtrl+O");
	p_fileOptions->Append(wxID_SAVE, "&Save\tCtrl+S");
	p_fileOptions->Append(wxID_SAVEAS, "Save &As\tCtrl+Shift+S");
	p_fileOptions->AppendSeparator();
	p_fileOptions->Append(16870, "Import\tCtrl+I");
	p_fileOptions->Append(wxID_EXIT, "E&xit\tAlt+F4");


	// view Settings
	p_viewSettings = new wxMenu();
	p_FiniteOption = new wxMenuItem(p_viewSettings, 17942, "Finite Toggle", "", wxITEM_CHECK);
	p_ToroidalOption = new wxMenuItem(p_viewSettings, 12785, "Toroidal Toggle", "", wxITEM_CHECK);
	p_viewNeighbors = new wxMenuItem(p_viewSettings, 12781, "Display Neighbor Count", "", wxITEM_CHECK);

	// grid but inside the view
	p_viewGrid = new wxMenuItem(p_viewSettings, 11625, "Grid Toggle", "", wxITEM_CHECK);
	p_viewThickGrid = new wxMenuItem(p_viewSettings, 11627, "Grid 10x Toggle", "", wxITEM_CHECK);

	p_viewHud = new wxMenuItem(p_viewSettings, 12788, "HUD Toggle", "", wxITEM_CHECK);
	
	p_FiniteOption->SetCheckable(true);
	p_ToroidalOption->SetCheckable(true);
	p_viewNeighbors->SetCheckable(true);

	p_viewGrid->SetCheckable(true);
	p_viewThickGrid->SetCheckable(true);

	p_viewHud->SetCheckable(true);

	p_viewSettings->Append(p_FiniteOption);
	p_viewSettings->Append(p_ToroidalOption);
	p_viewSettings->Append(p_viewNeighbors);

	p_viewSettings->Append(p_viewGrid);
	p_viewSettings->Append(p_viewThickGrid);

	p_viewSettings->Append(p_viewHud);

	//check if it is true already
	if (p_settings->isFinite) {
		p_FiniteOption->Check(true);
		p_ToroidalOption->Check(false);
	}
	else {
		p_FiniteOption->Check(false);
		p_ToroidalOption->Check(true);
	}

	if (p_settings->showCount) {
		p_viewNeighbors->Check(true);
	}
	else {
		p_viewNeighbors->Check(false);
	}

	if (p_settings->showGrid) {
		p_viewGrid->Check(true);
	}
	else {
		p_viewGrid->Check(false);
	}

	if (p_settings->showThickGrid) {
		p_viewThickGrid->Check(true);
	}
	else {
		p_viewThickGrid->Check(false);
	}

	if (p_settings->showThickGrid) {
		p_viewThickGrid->Check(true);
	}
	else {
		p_viewThickGrid->Check(false);
	}

	// append the menuBar
	p_menuBar->Append(p_fileOptions, "File");
	p_menuBar->Append(p_viewSettings, "View");
	p_menuBar->Append(p_menuOptions, "Settings");
	p_menuBar->Append(p_randomOptions, "Randomize");

	//drawing panel
	p_drawingPanel = new DrawingPanel(this, v_board, neighborCount, p_settings);
	p_sizer = new wxBoxSizer(wxVERTICAL);

	p_sizer->Add(p_drawingPanel,1, wxEXPAND | wxALL);
	this->SetSizer(p_sizer);

	MainWindow::InitGrid();
	this->Layout();
}

MainWindow::~MainWindow() {
	delete p_timer;
};

void MainWindow::UpdateStatusBar() {
	wxString statusText = wxString::Format("Generation: %d, Living Cells: %d, Show Neighbor: %s", generation, livingCells, std::to_string(p_settings->showCount));
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
	v_board.resize(p_settings->gridSize);
	neighborCount.resize(p_settings->gridSize);
	for (int i = 0; i < v_board.size(); i++) {
		v_board[i].resize(p_settings->gridSize);
		neighborCount[i].resize(p_settings->gridSize);
	}

	p_drawingPanel->SetGridSize(p_settings->gridSize);
}

void MainWindow::PlayButton(wxCommandEvent& _playEvent) {
	p_timer->Start(p_settings->interval);
	Refresh();
}

void MainWindow::PauseButton(wxCommandEvent& _pauseEvent) {
	p_timer->Stop();
}

void MainWindow::TrashButton(wxCommandEvent& _trashEvent) {
	livingCells = 0;
 	generation = 0;
	p_settings->_generation = 0;
	p_settings->_livingCells = 0;

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			v_board[i][j] = false;
			neighborCount[i][j] = 0;
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

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			int checkRow = _row + i;
			int checkCol = _column + j;

			if (p_settings->isFinite) {
				if (checkRow < 0 || checkCol < 0) {
					continue;
				}
				if (checkRow >= p_settings->gridSize || checkCol >= p_settings->gridSize) {
					continue;
				}
			}
			else {
				if (checkRow < 0) {
					checkRow = p_settings->gridSize - 1;
				}
				if (checkCol < 0) {
					checkCol = p_settings->gridSize - 1;
				}
				if (checkRow >= p_settings->gridSize) {
					checkRow = 0;
				}
				if (checkCol >= p_settings->gridSize) {
					checkCol = 0;
				}
			}
			if (v_board[checkRow][checkCol]) {
				result++;
			}
		}
	}
	return result;
}

void MainWindow::TimedEvent(wxTimerEvent& _timer) {
	CreateNextGen();
	_timer.Skip();
}

void MainWindow::CreateNextGen() {

	std::vector<std::vector<bool>> sandbox;
	sandbox.resize(p_settings->gridSize);

	for (int i = 0; i < sandbox.size(); i++) {
		sandbox[i].resize(p_settings->gridSize);
	}

	livingCells = 0;
	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			int count = CheckNeighboors(i, j);
			if (v_board[i][j] && count < 2) {
				sandbox[i][j] = false;
			}
			else if (v_board[i][j] && count > 3) {
				sandbox[i][j] = false;
			}
			else if (v_board[i][j] && (count == 2 || count == 3)) {
				sandbox[i][j] = true;
				livingCells++;
			}
			else if (!v_board[i][j] && count == 3) {
				sandbox[i][j] = true;
				livingCells++;
			}
			else {
				sandbox[i][j] = false;
			}
		}
	}

	v_board.swap(sandbox);

	// doing this outside of the main loop fix the generation behind
	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			int count = CheckNeighboors(i, j);
			neighborCount[i][j] = count;
		}
	}

	p_drawingPanel->Refresh();
	generation++;
	p_settings->_generation = generation;
	p_settings->_livingCells = livingCells;
	UpdateStatusBar();
}

void MainWindow::OnRandom(wxCommandEvent& _randomEvent) {
	RandomDefault();

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			int randomValue = rand() % RAND_MAX + 1;
			if (randomValue % 2 == 0) { // if even
				v_board[i][j] = true;
			}
			else { // if odd
				v_board[i][j] = false;
			}
		}
	}

	p_drawingPanel->Refresh();
	generation++;
	p_settings->_generation = generation;
	UpdateStatusBar();
}

void MainWindow::OnRandomSeed(wxCommandEvent& _rSeedEvent) {
	long seed = 0;
	seed = wxGetNumberFromUser("Enter a Seed value:", "Number Input", "Seed input:", seed, LONG_MIN, LONG_MAX);

	RandomSeed(seed);

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			int randomValue = rand() % RAND_MAX + 1;
			if (randomValue % 2 == 0) { // if even
				v_board[i][j] = true;
			}
			else { // if odd
				v_board[i][j] = false;
			}
		}
	}

	p_drawingPanel->Refresh();
	generation++;
	p_settings->_generation = generation;
	UpdateStatusBar();
}

void MainWindow::RandomSeed(int seed) {
	srand(seed);
}

void MainWindow::RandomDefault() {
	srand(time(NULL));
}

void MainWindow::OnMenuColor(wxCommandEvent& _menuColorEvent) {
	p_settings->LoadData();
	p_settingsDialog = new SettingsStorage(this, p_settings, "Color Options");
	p_settingsDialog->ShowModal();
	
	if (p_settingsDialog->ShowModal() == wxID_OK) {
		InitGrid();
		p_settings->SaveData();
		Refresh(); 
	}
}

void MainWindow::OnMenuCell(wxCommandEvent& _menuCellEvent) {
	p_settings->LoadData();
	p_settingsDialog = new SettingsStorage(this, p_settings, "Cell Options");
	p_settingsDialog->ShowModal();

	if (p_settingsDialog->ShowModal() == wxID_OK) {
		InitGrid();
		p_settings->SaveData();
		Refresh();
	}
}

void MainWindow::ClearUniverse() {
	generation = 0;
	p_settings->_generation = 0;
	livingCells = 0;
	p_settings->_livingCells = 0;

	for (int i = 0; i < p_settings->gridSize; i++) {
		for (int j = 0; j < p_settings->gridSize; j++) {
			v_board[i][j] = false;
			neighborCount[i][j] = 0;
		}
	}

	UpdateStatusBar();
	Refresh();
}

void MainWindow::OnNew(wxCommandEvent& _newEvent) {
	
	ClearUniverse();
	fileName.clear();
}

void MainWindow::OnOpen(wxCommandEvent& _openEvent) {
	// Open the file dialog to choose a file
	wxFileDialog openFileDialog(this, _("Open .cells file"), "", "",
		"Cells files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	// Reset the universe and delete any saved filename
	ClearUniverse();
	fileName.clear();
	fileName = openFileDialog.GetPath();

	// Open the file for reading
	std::ifstream infile(openFileDialog.GetPath().ToStdString());

	// Read the contents of the file into the universe
	std::string line;
	int row = 0, col = 0;
	while (std::getline(infile, line))
	{
		// !comments - there is nothing to comment? lol!
		if (line.empty() || line[0] == '!') {
			continue;
		}

		if (row == 0)
		{
			p_settings->gridSize = line.size(); // if the gridSize is bigger for some reason
		}

		// Iterate through the characters in the line and set the corresponding cell
		for (col = 0; col < line.size(); ++col)
		{
			if (line[col] == '*')
			{
				v_board[row][col] = true;
			}
		}
		++row;
	}

	// Close the file
	infile.close();

	// Update the display
	p_drawingPanel->Refresh();
	UpdateStatusBar();
}

void MainWindow::OnSave(wxCommandEvent& _saveEvent) {
	// If the filename has not been set yet, use Save As
	if (fileName.empty())
	{
		OnSaveAs(_saveEvent);
		return;
	}

	// Open the file for writing
	std::ofstream outfile(fileName.ToStdString());

	// Write the contents of the universe to the file
	for (int i = 0; i < p_settings->gridSize; i++)
	{
		for (int j = 0; j < p_settings->gridSize; j++)
		{
			if (v_board[i][j])
			{
				outfile << '*';
			}
			else
			{
				outfile << '.';
			}
		}
		outfile << std::endl;
	}

	// Close the file
	outfile.close();
}

void MainWindow::OnSaveAs(wxCommandEvent& _saveAsEvent) {
	wxFileDialog saveFileDialog(this, _("Save As .cells file"), "", "", "CELLS files (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	fileName = saveFileDialog.GetPath();

	// Open the file for writing
	std::ofstream outfile(fileName.ToStdString());

	// Write the contents of the universe to the file
	for (int i = 0; i < p_settings->gridSize; i++)
	{
		for (int j = 0; j < p_settings->gridSize; j++)
		{
			if (v_board[i][j])
			{
				outfile << '*';
			}
			else
			{
				outfile << '.';
			}
		}
		outfile << std::endl;
	}

	// Close the file
	outfile.close();
}

void MainWindow::OnExit(wxCommandEvent& _exitEvent) {
	Close();
}

void MainWindow::OnToroidalToggle(wxCommandEvent& _toroidalEvent) {
	if(!p_settings->isToroidal) {
		p_ToroidalOption->Check(true);
		p_settings->isToroidal = true;
		p_settings->isFinite = false;
		p_FiniteOption->Check(false);
	}
	else {
		p_ToroidalOption->Check(false);
		p_settings->isToroidal = false;
		p_settings->isFinite = true;
		p_FiniteOption->Check(true);
	}
}

void MainWindow::OnFiniteToggle(wxCommandEvent& _finiteEvent) {
	if (!p_settings->isFinite) {
		p_FiniteOption->Check(true);
		p_settings->isFinite = true;
		p_settings->isToroidal = false;
		p_ToroidalOption->Check(false);
	}
	else {
		p_viewNeighbors->Check(false);
		p_settings->isFinite = false;
		p_settings->isToroidal = true;
		p_ToroidalOption->Check(true);
	}
}

void MainWindow::OnShowCountToggle(wxCommandEvent& _showCountEvent) {
	if (!p_settings->showCount) {
		p_viewNeighbors->Check(true);
		p_settings->showCount = true; 
	}
	else {
		p_viewNeighbors->Check(false);
		p_settings->showCount = false;
	}
	p_drawingPanel->Refresh();
	UpdateStatusBar();
	p_settings->SaveData();
}

void MainWindow::OnGridToggle(wxCommandEvent& _gridEvent) {
	if (!p_settings->showGrid) {
		p_viewGrid->Check(true);
		p_settings->showGrid = true;
	}
	else {
		p_viewGrid->Check(false);
		p_settings->showGrid = false;
	}
	p_drawingPanel->Refresh();
	UpdateStatusBar();
	p_settings->SaveData();
}

void MainWindow::OnThickGridToggle(wxCommandEvent& _thickGridEvent) {
	if (!p_settings->showThickGrid) {
		p_viewThickGrid->Check(true);
		p_settings->showThickGrid = true;
	}
	else {
		p_viewThickGrid->Check(false);
		p_settings->showThickGrid = false;
	}
	p_drawingPanel->Refresh();
	UpdateStatusBar();
	p_settings->SaveData();
}

void MainWindow::OnHudToggle(wxCommandEvent& _hudEvent) {
	if (!p_settings->showHud) {
		p_viewHud->Check(true);
		p_settings->showHud = true;
	}
	else {
		p_viewHud->Check(false);
		p_settings->showHud = false;
	}
	p_drawingPanel->Refresh();
	UpdateStatusBar();
	p_settings->SaveData();

}

void MainWindow::OnResetSettings(wxCommandEvent& _resetEvent) {
	p_settings->resetSettings();
	UpdateStatusBar();
	p_drawingPanel->Refresh();
}

void MainWindow::OnImport(wxCommandEvent& _importEvent) {
	// Open the file dialog to choose a file
	wxFileDialog openFileDialog(this, _("Open .cells file"), "", "",
		"Cells files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	// Reset the universe and delete any saved filename
	ClearUniverse();
	fileName.clear();
	fileName = openFileDialog.GetPath();

	// Open the file for reading
	std::ifstream infile(openFileDialog.GetPath().ToStdString());

	// Read the contents of the file into the universe
	std::string line;
	int row = 0, col = 0;
	while (std::getline(infile, line))
	{
		// !comments - there is nothing to comment? lol!
		if (line.empty() || line[0] == '!') {
			continue;
		}

		if (row == 0)
		{
			p_settings->gridSize = line.size(); // if the gridSize is bigger for some reason
		}

		// Iterate through the characters in the line and set the corresponding cell
		for (col = 0; col < line.size(); ++col)
		{
			if (line[col] == '*')
			{
				v_board[row][col] = true;
			}
		}
		++row;
	}

	// Close the file
	infile.close();

	// Update the display
	p_drawingPanel->Refresh();
	UpdateStatusBar();
}






