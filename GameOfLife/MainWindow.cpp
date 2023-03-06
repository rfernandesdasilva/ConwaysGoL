#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(750,750)) {
	p_drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow() {

};
		