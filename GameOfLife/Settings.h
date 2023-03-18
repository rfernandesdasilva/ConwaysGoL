#pragma once

#include "wx/wx.h"

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
};