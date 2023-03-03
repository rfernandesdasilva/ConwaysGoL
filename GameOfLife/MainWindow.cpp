#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(500,500)) {
	p_drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow() {

};
		