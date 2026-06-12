#define NOMINMAX
#include <QApplication>
#include "luminogui/LuminoGUI.h"
#include "twitch_irc/twitch_irc.hpp"
#include <Windows.h>

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

    QApplication app(argc, argv);
    app.setStyle("Fusion");
    Lumino::LuminoGUI mainWindow;
    const QRect sr = mainWindow.screen()->availableGeometry();
    const QRect wr({}, mainWindow.frameSize().boundedTo(sr.size()));
    irc_handler();
    mainWindow.resize(wr.size());
    mainWindow.move(sr.center() - wr.center());
    mainWindow.show();


    return app.exec();
}
