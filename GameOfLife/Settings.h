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
	bool showCount;
	std::vector<std::vector<int>> neighborCount;

	// universe type
	bool isToroidal;
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

	void setBgColor(wxColor _bgColor) {
		bgRed = _bgColor.GetRed();
		bgGreen = _bgColor.GetGreen();
		bgBlue = _bgColor.GetBlue();
		bgAlpha = _bgColor.GetAlpha();
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