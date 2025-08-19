#include "wxwidgets/App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	mainFrame = new MainFrame("Calculator", wxSize(480, 640));
	mainFrame->Show();
	return true;
}