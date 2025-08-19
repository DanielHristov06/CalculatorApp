#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title, const wxSize& size);

private:
	wxStaticText* mDisplay = nullptr;

	void OnButton(wxCommandEvent& e);
	void OnClear(wxCommandEvent& e);
	void OnBackspace(wxCommandEvent& e);
	void OnEquals(wxCommandEvent& e);

	void AppendToDisplay(const wxString& s);
};