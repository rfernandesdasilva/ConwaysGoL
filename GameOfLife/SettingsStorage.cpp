#include "SettingsStorage.h"

wxBEGIN_EVENT_TABLE(SettingsStorage, wxDialog)
EVT_SPINCTRL(15000,SettingsStorage::OnSpinCtrl)
EVT_COLOURPICKER_CHANGED(15051,SettingsStorage::OnColourPickerCtrl)
wxEND_EVENT_TABLE()


SettingsStorage::SettingsStorage(wxWindow* _parent, SettingsBar* _settings) 
	: wxDialog(_parent, wxID_ANY, "Sample Title") {
	
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
}

SettingsStorage::~SettingsStorage() {

}

wxBoxSizer* SettingsStorage::CreateSettingBoxSpinCtrl() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);
	
	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Setting1//TEMP");

	spinCtrl = new wxSpinCtrl(this, 15000, "Test");

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(spinCtrl);

	return p_sizerSetting;
}

wxBoxSizer* SettingsStorage::CreateSettingBoxClrPicker() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);

	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Setting2//TEMP");

	colorCtrl = new wxColourPickerCtrl(this, 15051);

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(colorCtrl);

	return p_sizerSetting;
}

void SettingsStorage::OnSpinCtrl(wxSpinEvent& _event) {
	// do something
}
void SettingsStorage::OnColourPickerCtrl(wxColourPickerEvent& _event) {
	// do something
}


