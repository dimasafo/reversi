#include <QApplication>

#include "guibase.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GuiBase gui;
    gui.show();

    return app.exec();
}
