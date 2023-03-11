#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h";

class MainWindow : public wxFrame
{
private:
	DrawingPanel* p_drawingPanel;
	wxBoxSizer* p_sizer;
	std::vector<std::vector<bool>> v_board;

	int gridSize = 15;

	int generation;
	int livingCells;
	wxStatusBar* p_statusBar;

	wxToolBar* p_toolBar;

	wxTimer* p_timer;
	int milliseconds = 50;

public:
	MainWindow();
	~MainWindow();
	void onResize(wxSizeEvent& _event);
	void InitGrid();
	void UpdateStatusBar();

	void PlayButton(wxCommandEvent& _playEvent);
	void PauseButton(wxCommandEvent& _pauseEvent);
	void TrashButton(wxCommandEvent& _trashEvent);
	void NextButton(wxCommandEvent& _nextEvent);

	int CheckNeighboors(int _row, int _column);

	void CreateNextGen();

	void TimedEvent(wxTimerEvent& _timer);

	wxDECLARE_EVENT_TABLE();
};

