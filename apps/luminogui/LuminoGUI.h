#pragma once
#include <QMainWindow>
#include <QstatusBar>
#include <QScreen>

namespace Lumino {
    class LuminoGUI : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit LuminoGUI(QWidget* parent = nullptr);
    private:
        void setupUi();
        void buildChatArea();
    };
}