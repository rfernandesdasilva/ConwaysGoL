#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {

	gameWindow = new MainWindow();
	gameWindow->Show();
	return true;
}