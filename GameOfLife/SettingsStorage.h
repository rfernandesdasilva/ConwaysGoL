#pragma once

#include "wx/wx.h"
#include "Settings.h"
#include "wx/clrpicker.h"
#include "wx/spinctrl.h"

class SettingsStorage : public wxDialog
{
public:
	SettingsStorage(wxWindow* _parent, SettingsBar* _settings);
	~SettingsStorage();

	wxBoxSizer* CreateSettingBoxSpinCtrl(); // created these methods more for organization and reading clarity
	wxBoxSizer* CreateSettingBoxClrPicker();

	void OnSpinCtrl(wxSpinEvent& _event);
	void OnColourPickerCtrl(wxColourPickerEvent& _event);

	wxDECLARE_EVENT_TABLE();
private:
	wxBoxSizer* p_sizerMainBox;
	wxSpinCtrl* spinCtrl;
	wxColourPickerCtrl* colorCtrl;

	SettingsBar* p_settings;
};

