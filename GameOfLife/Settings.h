#pragma once

#include "wx/wx.h"
#include <fstream>

struct SettingsBar {

	//interval and gridSize settings
	int gridSize = 15;
	int interval = 50;

	// live cells color, rgb
	unsigned int redLive = 136;
	unsigned int greenLive = 136;
	unsigned int blueLive = 136;
	unsigned int alphaLive = 255;

	// dead cells color, rgb
	unsigned int redDead = 255;
	unsigned int greenDead = 255;
	unsigned int blueDead = 255;
	unsigned int alphaDead;

	bool showGrid;
	bool showThickGrid;

	// show neighbor count
	bool showCount;
	std::vector<std::vector<int>> neighborCount;

	// universe type
	bool isToroidal = true;
	bool isFinite;

	wxColor getLiveCellColor() {
		// get uints and change to wxcolor
		return wxColor(redLive, greenLive, blueLive, alphaLive);
	}

	wxColor getDeadCellColor() {
		// get uints and change to wxcolor
		return wxColor(redDead, greenDead, blueDead, alphaDead);
	}

	void setLivingCellColor(wxColor _liveColor) {
		redLive = _liveColor.GetRed();
		greenLive = _liveColor.GetGreen();
		blueLive = _liveColor.GetBlue();
		alphaLive = _liveColor.GetAlpha();
	}

	void setDeadCellColor(wxColor _deadColor) {
		redDead = _deadColor.GetRed();
		greenDead = _deadColor.GetGreen();
		blueDead = _deadColor.GetBlue();
		alphaDead = _deadColor.GetAlpha();
	}

	void resetSettings() {
		SettingsBar* temp = new SettingsBar();

		gridSize = temp->gridSize;
		interval = temp->interval;

		// live cells color, rgb
		redLive = temp->redLive;
		greenLive = temp->greenLive;
		blueLive = temp->blueLive;
		alphaLive = temp->alphaLive;

		// dead cells color, rgb
		redDead = temp->redDead;
		greenDead = temp->greenDead;
		blueDead = temp->blueDead;
		alphaDead = temp->alphaDead;

		// show neighbor count
		showCount = temp->showCount;
		neighborCount = temp->neighborCount;

		// universe type
		isToroidal = temp->isToroidal;
		isFinite = temp->isFinite;

		delete temp;
	}

	void LoadData() {
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(SettingsBar));
		file.close();
	}

	void SaveData() {
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(SettingsBar));
		file.close();
	}
};