#include "wxwidgets/MainFrame.h"
#include "calculator/Parser.h"
#include <string>

MainFrame::MainFrame(const wxString& title, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	CenterOnScreen();
	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	mExpr = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_RIGHT | wxBORDER_NONE);
	mExpr->SetFont(wxFontInfo(18));
	vbox->Add(mExpr, 0, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 25);

	mDisplay = new wxTextCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_RIGHT | wxBORDER_NONE);
	mDisplay->SetFont(wxFontInfo(24));
	vbox->Add(mDisplay, 0, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 25);

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
	const wxButton* b = wxStaticCast(e.GetEventObject(), wxButton);
	if (!b) return;
	const wxString label = b->GetLabel();

	if (label.size() == 1 && IsOp(label[0])) {
		const wxChar op = label[0];

		const wxString cur = mDisplay->GetValue();
		if (!(cur == "0" || cur.empty())) {
			mExpr->AppendText(cur);
			mDisplay->SetValue("0");
		}

		wxString expr = mExpr->GetValue();
		if (expr.empty()) return;

		if (!expr.empty() && IsOp(expr.Last())) {
			expr.Last() = op;
			mExpr->SetValue(expr);
		}
		else {
			mExpr->AppendText(wxString(op));
		}
		return;
	}

	if (label == "(") {
		mExpr->AppendText(label);
		return;
	}
	else if (label == ")") {
		if (!IsOp(mExpr->GetValue().Last()) && mExpr->GetValue().Last() != '(') {
			mExpr->AppendText(label);
			return;
		}
		else return;
	}

	if (mDisplay->GetValue() == "0" && label != ".") {
		mDisplay->Clear();
	}

	mDisplay->AppendText(label);
}

void MainFrame::OnClear(wxCommandEvent& e) {
	mDisplay->SetValue("0");
	mExpr->SetValue("");
}

void MainFrame::OnBackspace(wxCommandEvent& e) {
	wxString s = mDisplay->GetValue();
	if (s.size() <= 1) mDisplay->SetValue("0");
	else { s.RemoveLast(); mDisplay->SetValue(s); }
}

void MainFrame::OnEquals(wxCommandEvent& e) {
	mExpr->AppendText(mDisplay->GetValue());
	const std::string expr = mExpr->GetValue().ToStdString();
	mDisplay->SetValue(wxString::Format("%g", calc::evaluate(expr)));
	mExpr->SetValue("");
}

bool MainFrame::IsOp(const wxChar& c) {
	return wxString("+-*/").Find(c) != wxNOT_FOUND;
}