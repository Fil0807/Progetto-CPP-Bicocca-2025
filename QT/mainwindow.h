#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void newFile();                //Crea nuovo file
    void openFile();               //Apre file
    void saveFile();               //Salva file
    void saveFileAs();             //Salva file con nome
    void openFindReplaceDialog();  //Apre finestra di modifica e ricerca

private:
    QTextEdit *textEdit;
    QString currentFile;
};
#endif // MAINWINDOW_H
