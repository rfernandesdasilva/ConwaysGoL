#pragma once

#include "wx/wx.h"
#include "Settings.h"
#include "wx/clrpicker.h"
#include "wx/spinctrl.h"

#include <string>

class SettingsStorage : public wxDialog
{
public:
	SettingsStorage(wxWindow* _parent, SettingsBar* t_settings, std::string labelName);
	~SettingsStorage();

	wxBoxSizer* CreateSettingBoxSpinCtrl(); // created these methods more for organization and reading clarity
	wxBoxSizer* CreateLiveCellSettingBoxClrPicker();
	wxBoxSizer* CreateDeadCellSettingBoxClrPicker();

	void OnSpinCtrl(wxSpinEvent& _event);
	void OnSpinCtrlGrid(wxSpinEvent& _event);
	void OnColourPickerCtrl(wxColourPickerEvent& _event);

	wxBoxSizer* CreateNeighborCountCheckBox();
	void OnCheckBox(wxCommandEvent& _checkBoxEvent);

	wxDECLARE_EVENT_TABLE();
private:
	wxBoxSizer* p_sizerMainBox;
	wxSpinCtrl* spinCtrl; // interval
	wxSpinCtrl* spinCtrlGrid; // gridSize
	wxColourPickerCtrl* colorCtrl;

	SettingsBar* p_settings;
};

