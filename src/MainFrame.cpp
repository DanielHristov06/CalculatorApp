#include "wxwidgets/MainFrame.h"
#include "calculator/Parser.h"
#include <string>

MainFrame::MainFrame(const wxString& title, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	CenterOnScreen();
	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	mDisplay = new wxTextCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_RIGHT | wxBORDER_NONE);
	mDisplay->SetFont(wxFontInfo(24));
	vbox->Add(mDisplay, 0, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 25);

	wxGridSizer* grid = new wxGridSizer(0, 4, 5, 5);

	const wxString labels[] = {
		"7", "8", "9", "/",
		"4", "5", "6", "*",
		"1", "2", "3", "-",
		"0", ".", "(", ")",
		"C", "<-", "=", "+"
	};

	for (const auto& l : labels) {
		wxButton* btn = new wxButton(panel, wxID_ANY, l);
		btn->SetFont(wxFontInfo(18));
		if (l == "C") btn->Bind(wxEVT_BUTTON, &MainFrame::OnClear, this);
		else if (l == "<-") btn->Bind(wxEVT_BUTTON, &MainFrame::OnBackspace, this);
		else if (l == "=") btn->Bind(wxEVT_BUTTON, &MainFrame::OnEquals, this);
		else btn->Bind(wxEVT_BUTTON, &MainFrame::OnButton, this);
		grid->Add(btn, 1, wxEXPAND);
	}

	vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

	panel->SetSizer(vbox);
	panel->Layout();
}

void MainFrame::OnButton(wxCommandEvent& e) {
	wxButton* b = wxDynamicCast(e.GetEventObject(), wxButton);
	if (!b) return;
	const wxString t = b->GetLabel();
	if (mDisplay->GetValue() == "0") mDisplay->Clear();
	mDisplay->AppendText(t);
}

void MainFrame::OnClear(wxCommandEvent& e) {
	mDisplay->SetValue("0");
}

void MainFrame::OnBackspace(wxCommandEvent& e) {
	wxString s = mDisplay->GetValue();
	if (s.size() <= 1) mDisplay->SetValue("0");
	else { s.RemoveLast(); mDisplay->SetValue(s); }
}

void MainFrame::OnEquals(wxCommandEvent& e) {
	const std::string expr = mDisplay->GetValue().ToStdString();
	mDisplay->SetValue(wxString::Format("%g", calc::evaluate(expr)));
}