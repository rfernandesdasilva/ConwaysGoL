#include "SettingsStorage.h"

wxBEGIN_EVENT_TABLE(SettingsStorage, wxDialog)
EVT_SPINCTRL(15000,SettingsStorage::OnSpinCtrl)
EVT_SPINCTRL(15020, SettingsStorage::OnSpinCtrlGrid)
EVT_COLOURPICKER_CHANGED(15051,SettingsStorage::OnColourPickerCtrl) // live cell id
EVT_COLOURPICKER_CHANGED(15054, SettingsStorage::OnColourPickerCtrl) // dead cell id
EVT_CHECKBOX(15067, SettingsStorage::OnCheckBox)
wxEND_EVENT_TABLE()

SettingsStorage::SettingsStorage(wxWindow* _parent, SettingsBar* _settings, std::string labelName) 
	: wxDialog(_parent, wxID_ANY, labelName) { // passed labelName to change windowName based on which configuration
	
	p_settings = _settings;

	// vertically
	p_sizerMainBox = new wxBoxSizer(wxVERTICAL);

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

	wxString intervalStr;
	intervalStr = wxString::Format("%d", p_settings->interval);
	spinCtrl = new wxSpinCtrl(this, 15000, intervalStr); // max at 100 as default

	p_sizerSetting->Add(labelCtrl);
	p_sizerSetting->Add(spinCtrl);

	// gridSize
	// label creation
	wxStaticText* labelCtrlGrid = new wxStaticText(this, wxID_ANY, "GridSize(cells): //TEMP");

	wxString gridStr;
	gridStr = wxString::Format("%d", p_settings->gridSize); // display current values!
	spinCtrlGrid = new wxSpinCtrl(this, 15020, gridStr); // max at 100 as default

	p_sizerSetting->Add(labelCtrlGrid);
	p_sizerSetting->Add(spinCtrlGrid);


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
}

void SettingsStorage::OnSpinCtrlGrid(wxSpinEvent& _event) {
	p_settings->gridSize = _event.GetValue();
}

void SettingsStorage::OnColourPickerCtrl(wxColourPickerEvent& _event) {
	wxColor color = _event.GetColour();

	if (_event.GetId() == 15051) {
		p_settings->redLive = color.GetRed();
		p_settings->greenLive = color.GetGreen();
		p_settings->blueLive = color.GetBlue();
		p_settings->alphaLive = color.GetAlpha();
	}
	else {
		p_settings->redDead = color.GetRed();
		p_settings->greenDead = color.GetGreen();
		p_settings->blueDead = color.GetBlue();
		p_settings->alphaDead = color.GetAlpha();
	}
	
	p_settings->SaveData();
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
	if (_checkBoxEvent.IsChecked() && p_settings->showCount == false) {
		p_settings->showCount = true;
		p_settings->SaveData();
	} // caso: nao está checkado e é true: turn to fasle.
}


