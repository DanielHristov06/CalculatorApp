#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title, const wxSize& size);

private:
	int parenDepth = 0;
	bool mError = false;

	wxTextCtrl* mExpr = nullptr;
	wxTextCtrl* mDisplay = nullptr;

	void ResetAll();

	void OnButton(wxCommandEvent& e);
	void OnClear(wxCommandEvent& e);
	void OnBackspace(wxCommandEvent& e);
	void OnEquals(wxCommandEvent& e);
};