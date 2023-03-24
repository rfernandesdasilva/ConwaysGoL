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
	
	//show count
	std::vector<std::vector<int>> neighborCount;

	wxMenuBar* p_menuBar;
	wxString fileName = wxEmptyString;


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

	// randomHandlers
	void OnRandom(wxCommandEvent& _randomEvent);
	void OnRandomSeed(wxCommandEvent& _rSeedEvent);

	// random helpers
	void RandomSeed(int seed);
	void RandomDefault();

	//menuEvent
	void OnMenu(wxCommandEvent& _menuEvent);

	//FileEvents
	void OnNew(wxCommandEvent& _newEvent);
	void OnOpen(wxCommandEvent& _openEvent);
	void OnSave(wxCommandEvent& _saveEvent);
	void OnSaveAs(wxCommandEvent& _saveAsEvent);
	void OnExit(wxCommandEvent& _exitEvent);

	void ClearUniverse();

	wxDECLARE_EVENT_TABLE();
};

