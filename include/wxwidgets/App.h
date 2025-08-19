#pragma once
#include <wx/wx.h>
#include "MainFrame.h"

class App : public wxApp {
private:
	MainFrame* mainFrame = nullptr;

public:
	bool OnInit() override;
};