#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow editor;
    editor.setWindowTitle("Editor di Testo");
    editor.resize(600, 400);
    editor.show();
    return app.exec();
}
