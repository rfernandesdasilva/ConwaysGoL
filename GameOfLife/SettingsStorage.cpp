#include "SettingsStorage.h"

wxBEGIN_EVENT_TABLE(SettingsStorage, wxDialog)
EVT_SPINCTRL(15000,SettingsStorage::OnSpinCtrl)
EVT_COLOURPICKER_CHANGED(15051,SettingsStorage::OnColourPickerCtrl) // live cell id
EVT_COLOURPICKER_CHANGED(15054, SettingsStorage::OnColourPickerCtrl) // dead cell id
EVT_CHECKBOX(15067, SettingsStorage::OnCheckBox)
wxEND_EVENT_TABLE()

SettingsStorage::SettingsStorage(wxWindow* _parent, SettingsBar* _settings, std::string labelName) 
	: wxDialog(_parent, wxID_ANY, labelName) { // passed labelName to change windowName based on which configuration
	
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
	p_sizerMainBox->Add(CreateLiveCellSettingBoxClrPicker()); 
	p_sizerMainBox->Add(CreateDeadCellSettingBoxClrPicker());

	p_sizerMainBox->Add(CreateNeighborCountCheckBox());

	wxSizer* button = CreateButtonSizer(wxOK | wxCANCEL);
	p_sizerMainBox->Add(button);
}

SettingsStorage::~SettingsStorage() {

}

wxBoxSizer* SettingsStorage::CreateSettingBoxSpinCtrl() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);
	
	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Interval(ms): //TEMP");

	spinCtrl = new wxSpinCtrl(this, 15000, "Test"); // max at 100 as default

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(spinCtrl);

	return p_sizerSetting;
}

wxBoxSizer* SettingsStorage::CreateLiveCellSettingBoxClrPicker() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);

	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Live Cell Color: //TEMP");

	// getLive color here just sets the color of the box to the color picked 
	colorCtrl = new wxColourPickerCtrl(this, 15051);
	colorCtrl->SetColour(p_settings->getLiveCellColor());

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(colorCtrl);

	return p_sizerSetting;
}

wxBoxSizer* SettingsStorage::CreateDeadCellSettingBoxClrPicker() {
	wxBoxSizer* p_sizerSetting = new wxBoxSizer(wxHORIZONTAL);
	
	// label creation
	wxStaticText* labelCtrl = new wxStaticText(this, wxID_ANY, "Dead Cell Color: //TEMP");

	// getDead color here just sets the color of the box to the color picked 
	colorCtrl = new wxColourPickerCtrl(this, 15054); 
	colorCtrl->SetColour(p_settings->getDeadCellColor());

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(colorCtrl);

	return p_sizerSetting;
}

// maximum allowed value is 100. need to configure this?
// no negative values.
void SettingsStorage::OnSpinCtrl(wxSpinEvent& _event) {
	p_settings->interval = _event.GetValue();
	p_settings->SaveData();
}
void SettingsStorage::OnColourPickerCtrl(wxColourPickerEvent& _event) {
	wxColor color = _event.GetColour();

	if (_event.GetId() == 15051) {
		p_settings->redLive = color.GetRed();
		p_settings->greenLive = color.GetGreen();
		p_settings->blueLive = color.GetBlue();
		p_settings->SaveData();
	}
	else {
		p_settings->redDead = color.GetRed();
		p_settings->greenDead = color.GetGreen();
		p_settings->blueDead = color.GetBlue();
		p_settings->SaveData();
	}
	
	//Refresh();
}

wxBoxSizer* SettingsStorage::CreateNeighborCountCheckBox() {
	wxCheckBox* checkBox = new wxCheckBox(this, 15067, "Show Neighbor Count: //TEMP");
	checkBox->SetValue(false);

	wxBoxSizer* p_checkBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	p_checkBoxSizer->AddStretchSpacer();
	p_checkBoxSizer->Add(checkBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
	p_checkBoxSizer->AddStretchSpacer();
	
	return p_checkBoxSizer;
}

void SettingsStorage::OnCheckBox(wxCommandEvent& _checkBoxEvent) {
	if (_checkBoxEvent.IsChecked()) {
		//p_settings->setNeighborSize();
		//display
	}
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
// - on clicking Ok, it is refreshing the dialog window.
// - review the SettingsStorage events, as I feel there is something wrong with the colorPick event.
// - review class/file Names, as they are really bad rn.



