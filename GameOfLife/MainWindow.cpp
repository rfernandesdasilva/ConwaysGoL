#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(1000,1000)) {
	p_drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow() {

};
		