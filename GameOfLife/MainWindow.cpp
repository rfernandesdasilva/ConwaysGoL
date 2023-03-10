#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Sample Title",
	wxPoint(0,0), wxSize(400,400)) {
	p_drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow() {

};
		