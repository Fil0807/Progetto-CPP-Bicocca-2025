#include "findreplacedialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

FindReplaceDialog::FindReplaceDialog(QTextEdit *editor, QWidget *parent)
    : QDialog(parent), textEdit(editor) {
    setWindowTitle("Cerca");
    QVBoxLayout *layout = new QVBoxLayout(this);

    findLineEdit = new QLineEdit(this);
    replaceLineEdit = new QLineEdit(this);
    findButton = new QPushButton("Trova", this);
    replaceButton = new QPushButton("Sostituisci", this);
    replaceAllButton = new QPushButton("Sostituisci Tutto", this);
    caseSensitiveCheckBox = new QCheckBox("Case Sensitive", this);
    wholeWordCheckBox = new QCheckBox("Trova parola intera", this);

    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(caseSensitiveCheckBox);
    layout->addWidget(wholeWordCheckBox);
    layout->addWidget(findButton);
    layout->addWidget(replaceButton);
    layout->addWidget(replaceAllButton);

    connect(findButton, &QPushButton::clicked, this, &FindReplaceDialog::findText);
    connect(replaceButton, &QPushButton::clicked, this, &FindReplaceDialog::replaceText);
    connect(replaceAllButton, &QPushButton::clicked, this, &FindReplaceDialog::replaceAllText);
}


//Metodo per la ricerca di testo
//evidenza il testo trovato e permette di navigare tra tutte le occorrenze se multiple
void FindReplaceDialog::findText() {

    QTextDocument::FindFlags flags;
    if (caseSensitiveCheckBox->isChecked()) flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordCheckBox->isChecked()) flags |= QTextDocument::FindWholeWords;

    if (!textEdit->find(findLineEdit->text(), flags)) {
        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        textEdit->setTextCursor(cursor);
        textEdit->find(findLineEdit->text(), flags);
    }
}


//Metodo per la sostituzione di testo
//Utilizza il metodo findText() per selezionare le occorrenze
void FindReplaceDialog::replaceText() {
    findText();
    if (textEdit->textCursor().hasSelection()) {
        QTextCursor cursor = textEdit->textCursor();
        cursor.insertText(replaceLineEdit->text());
        textEdit->setTextCursor(cursor);
        cursor.movePosition(QTextCursor::Start);
    }
}


//Metodo per la sostituzione di tutte le occorrenze trovate
//Tramite il metodo findText() trova tutte le occorrenze e le modifica
void FindReplaceDialog::replaceAllText() {
    QString findText = findLineEdit->text();
    QString replaceText = replaceLineEdit->text();
    if (findText.isEmpty()) return;

    QTextDocument::FindFlags flags;
    if (caseSensitiveCheckBox->isChecked()) flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordCheckBox->isChecked()) flags |= QTextDocument::FindWholeWords;

    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();

    cursor.movePosition(QTextCursor::Start);
    textEdit->setTextCursor(cursor);

    while (textEdit->find(findText, flags)) {
        QTextCursor matchCursor = textEdit->textCursor();
        matchCursor.insertText(replaceText);
        textEdit->setTextCursor(matchCursor);
    }

    cursor.endEditBlock();
}


