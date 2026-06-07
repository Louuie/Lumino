#include "LuminoGUI.h"

Lumino::LuminoGUI::LuminoGUI(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Lumino");
	setMinimumSize(1280, 720);
	statusBar()->showMessage("Ready to chat!");
}


void Lumino::LuminoGUI::setupUi() {

}

void Lumino::LuminoGUI::buildChatArea() {

}
