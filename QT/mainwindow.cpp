#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "findreplacedialog.h"

MainWindow::MainWindow() {
    textEdit = new QTextEdit(this);
    QFont font = textEdit->font();
    font.setPointSize(14);
    textEdit->setFont(font);
    setCentralWidget(textEdit);

    //Creazione barra menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("File");

    //Aggiunta azioni al menu
    QAction *newFileAction = fileMenu->addAction("Nuovo");
    QAction *openFileAction = fileMenu->addAction("Apri");
    QAction *saveFileAction = fileMenu->addAction("Salva");
    QAction *saveAsFileAction = fileMenu->addAction("Salva con nome");
    QAction *findReplaceAction = fileMenu->addAction("Cerca");

    setMenuBar(menuBar);

    //Collegamenti azioni - slot
    connect(newFileAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsFileAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(findReplaceAction, &QAction::triggered, this, &MainWindow::openFindReplaceDialog);
}

MainWindow::~MainWindow() {}


//Metodo usato per la creazione di un nuovo file
//Pulisce da eventuale testo residuo
void MainWindow::newFile() {
    textEdit->clear();
    currentFile.clear();
}


//Metodo usato per caricare un file nell'editor
//Apre una finestra per la selezione del file da caricare
void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Apri File", "", "Text Files (*.txt *.md)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this, "Errore", "Impossibile aprire il file");
            return;
        }

        try {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            currentFile = fileName;
            file.close();
        } catch (...) {
            QMessageBox::warning(this, "Errore", "Si è verificato un errore durante l'apertura del file");
            file.close();
        }

    }
}


//Metodo usato per salvare il file attualmente aperto
void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        QFile file(currentFile);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Errore", "Impossibile salvare il file");
            return;
        }

        try {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        } catch(...) {
            QMessageBox::warning(this, "Errore", "Si è verificato un errore durante il salvataggio");
            file.close();
        }
    }
}


//Metodo usato per salvare il file attualmente aperto con un nuovo nome
//Apre una finestra per selezione percorso e assegnare nome ed estensione
void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva File", "", "Text Files (*.txt *.md)");
    if (!fileName.isEmpty()) {
        currentFile = fileName;
        saveFile();
    }
}


//Metodo usato per l'apertura del menu di modifica
void MainWindow::openFindReplaceDialog() {
    FindReplaceDialog dialog(textEdit, this);
    dialog.exec();
}
