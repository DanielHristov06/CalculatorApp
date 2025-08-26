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

	auto IsOp = [](wxUniChar c) { return wxString("+-*/").Find(c) != wxNOT_FOUND; };
	auto IsNum = [](wxUniChar c) { return c != 0 && wxIsdigit(c); };

	const wxString label = b->GetLabel();
	const wxString expr = mExpr->GetValue();
	const bool empty = expr.IsEmpty();
	const wxUniChar last = empty ? wxUniChar(0) : expr.Last();
	const wxString cur = mDisplay->GetValue();

	if (label.size() == 1 && IsOp(label[0])) {
		const wxChar op = label[0];

		if (!(cur == "0" || cur.empty())) {
			mExpr->AppendText(cur);
			mDisplay->SetValue("0");
		}
		
		const wxString expr2 = mExpr->GetValue();
		const bool empty2 = expr2.IsEmpty();
		if (empty2) return;
		const wxUniChar last2 = empty2 ? wxUniChar(0) : expr2.Last();

		if (IsOp(last2)) {
			expr2.Last() = op;
			mExpr->SetValue(expr2);
		}
		else if (last2 == '(') {
			return;
		}
		else {
			mExpr->AppendText(wxString(op));
		}
		return;
	}

	if (label == "(") {
		if (empty || IsOp(last) || last == '(') {
			mExpr->AppendText(label);
			++parenDepth;
		}
		return;
	}
	else if (label == ")") {
		if (parenDepth <= 0) return;

		wxString expr2 = mExpr->GetValue();
		bool empty2 = expr2.IsEmpty();
		wxUniChar last2 = empty2 ? wxUniChar(0) : expr2.Last();

		const wxString cur = mDisplay->GetValue();
		if ((empty2 || IsOp(last2) || last2 == '(') && !(cur == "0" || cur.empty())) {
			mExpr->AppendText(cur);
			mDisplay->SetValue("0");

			// recompute after flush
			expr2 = mExpr->GetValue();
			empty2 = expr2.IsEmpty();
			last2 = empty2 ? wxUniChar(0) : expr2.Last();
		}

		if (!empty2 && (IsNum(last2) || last2 == ')')) {
			mExpr->AppendText(")");
			--parenDepth;
		}
		return;
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
	if (mDisplay->GetValue() != "0") mExpr->AppendText(mDisplay->GetValue());
	const std::string expr = mExpr->GetValue().ToStdString();
	mDisplay->SetValue(wxString::Format("%g", calc::evaluate(expr)));
	mExpr->SetValue("");
}