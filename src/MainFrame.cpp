#include "wxwidgets/MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	CenterOnScreen();
	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxStaticText* display = new wxStaticText(panel, wxID_ANY, "0");
	display->SetFont(wxFontInfo(24));
	vbox->Add(display, 0, wxALIGN_RIGHT | wxRIGHT | wxTOP | wxBOTTOM, 25);

	wxGridSizer* grid = new wxGridSizer(0, 4, 5, 5);

	const char* labels[] = {
		"7", "8", "9", "/",
		"4", "5", "6", "*",
		"1", "2", "3", "-",
		"0", ".", "(", ")",
		"C", "<-", "=", "+"
	};

	for (const auto& l : labels) {
		wxButton* btn = new wxButton(panel, wxID_ANY, l);
		btn->SetFont(wxFontInfo(18));
		grid->Add(btn, 1, wxEXPAND);
	}

	vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

	panel->SetSizer(vbox);
	panel->Layout();
}