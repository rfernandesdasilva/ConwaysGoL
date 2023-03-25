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
	unsigned int alphaLive;

	// dead cells color, rgb
	unsigned int redDead;
	unsigned int greenDead;
	unsigned int blueDead;
	unsigned int alphaDead;

	// backGround color
	unsigned int bgRed;
	unsigned int bgGreen;
	unsigned int bgBlue;
	unsigned int bgAlpha;

	// show neighbor count
	bool showCount = false;
	std::vector<std::vector<int>> neighborCount;

	// universe type
	bool isToroidal = true;
	bool isFinite = false;

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

	void setBgColor(wxColor _bgColor) {
		bgRed = _bgColor.GetRed();
		bgGreen = _bgColor.GetGreen();
		bgBlue = _bgColor.GetBlue();
		bgAlpha = _bgColor.GetAlpha();
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

		// backGround color
		bgRed = temp->bgRed;
		bgGreen = temp->bgGreen;
		bgBlue = temp->bgBlue;
		bgAlpha = temp->bgAlpha;

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