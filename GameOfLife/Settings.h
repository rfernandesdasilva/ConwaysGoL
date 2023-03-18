#pragma once

#include "wx/wx.h"
#include <fstream>

struct SettingsBar {

	//interval and gridSize settings
	int gridSize = 15;
	int interval = 50;

	// live cells color, rgb
	unsigned int redLive;
	unsigned int greenLive;
	unsigned int blueLive;

	// dead cells color, rgb
	unsigned int redDead;
	unsigned int greenDead;
	unsigned int blueDead;
	
	wxColor getLiveCellColor() {
		// get uints and change to wxcolor
		return wxColor(redLive, greenLive, blueLive);
	}

	wxColor getDeadCellColor() {
		// get uints and change to wxcolor
		return wxColor(redDead, greenDead, blueDead);
	}

	void setLivingCellColor(wxColor _liveColor) {
		redLive = _liveColor.GetRed();
		greenLive = _liveColor.GetGreen();
		blueLive = _liveColor.GetBlue();
	}

	void setDeadCellColor(wxColor _deadColor) {
		redDead = _deadColor.GetRed();
		greenDead = _deadColor.GetGreen();
		blueDead = _deadColor.GetBlue();
	}

	void LoadData() {
		//Load Data
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(SettingsBar));
		file.close();
	}

	void SaveData() {
		//Save Data
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(SettingsBar));
		file.close();
	}
};