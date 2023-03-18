#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "SettingsStorage.h"
#include "Settings.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* p_drawingPanel;
	wxBoxSizer* p_sizer;
	std::vector<std::vector<bool>> v_board;

	//settings
	SettingsBar* p_settings;
	SettingsStorage* p_settingsDialog;

	int generation;
	int livingCells;
	wxStatusBar* p_statusBar;

	wxToolBar* p_toolBar;

	wxTimer* p_timer;
	int milliseconds = 50;

	wxMenuBar* p_menuBar;

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

	//menuEvent
	void OnMenu(wxCommandEvent& _menuEvent);

	wxDECLARE_EVENT_TABLE();
};

