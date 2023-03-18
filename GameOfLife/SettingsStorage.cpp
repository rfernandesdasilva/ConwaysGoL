#include "SettingsStorage.h"

wxBEGIN_EVENT_TABLE(SettingsStorage, wxDialog)
EVT_SPINCTRL(15000,SettingsStorage::OnSpinCtrl)
EVT_COLOURPICKER_CHANGED(15051,SettingsStorage::OnColourPickerCtrl)
wxEND_EVENT_TABLE()


SettingsStorage::SettingsStorage(wxWindow* _parent, SettingsBar* _settings) 
	: wxDialog(_parent, wxID_ANY, "Cell Settings") {
	
	p_settings = _settings;

	// vertically
	p_sizerMainBox = new wxBoxSizer(wxVERTICAL);

	// unsure if this is correct.
	// Create a wxBoxSizer pointer for the main box and set it to a new wxBoxSizer.  
	// Pass in wxVertical as an argument for the new object.  
	// Using SetSizer, set the main sizer of the window to this sizer.

	this->SetSizer(p_sizerMainBox);

	//childSizers
	// label wxStaticText control(this, id, text), wxSpingCtrl
	p_sizerMainBox->Add(CreateSettingBoxSpinCtrl());
	// label wxStaticText control(this, id, text), wxColourPickerCtrl
	p_sizerMainBox->Add(CreateSettingBoxClrPicker());

	wxSizer* button = CreateButtonSizer(wxOK | wxCANCEL);
	p_sizerMainBox->Add(button);
}

SettingsStorage::~SettingsStorage() {

}

wxBoxSizer* SettingsStorage::CreateSettingBoxSpinCtrl() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);
	
	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Interval(ms): //TEMP");

	spinCtrl = new wxSpinCtrl(this, 15000, "Test");

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(spinCtrl);

	return p_sizerSetting;
}

wxBoxSizer* SettingsStorage::CreateSettingBoxClrPicker() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);

	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Cell Color: //TEMP");

	colorCtrl = new wxColourPickerCtrl(this, 15051);

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(colorCtrl);

	return p_sizerSetting;
}

// maximum allowed value is 100. need to configure this?
// no negative values.
void SettingsStorage::OnSpinCtrl(wxSpinEvent& _event) {
	p_settings->interval = _event.GetValue();
}
void SettingsStorage::OnColourPickerCtrl(wxColourPickerEvent& _event) {
	wxColor color = _event.GetColour();
	p_settings->redLive = color.GetRed();
	p_settings->greenLive = color.GetGreen();
	p_settings->blueLive = color.GetBlue();
	Refresh();
}

// TODO: 
// - fix the layout of the dialog.
// - understand how the saveData and loadData have to be called.
// - review the way I am passing pointers between classes; i feel there is something wrong there.
// - the interval is working properly, but the RBG saving is not.
// - randomize
// - rename TEMP naming labels
// - should the window close on clicking ok? I think so!
// - color for deadCells, and color for liveCells. this means we need a way to select between them, or two different 
// color pickers.
// 



