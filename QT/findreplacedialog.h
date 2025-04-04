#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>
#include <QTextEdit>

class QLineEdit;
class QPushButton;
class QCheckBox;

class FindReplaceDialog : public QDialog {
    Q_OBJECT
public:
    FindReplaceDialog(QTextEdit *editor, QWidget *parent = nullptr);

private slots:
    void findText();        //Ricerca il testo inserito
    void replaceText();     //Sostituisce il testo trovato con quello dato
    void replaceAllText();  //Sostituisce tutto il testo corrispondente a quello dato

private:
    QTextEdit *textEdit;
    QLineEdit *findLineEdit;           //Campo per l'input per il testo da trovare
    QLineEdit *replaceLineEdit;        //Campo per l'input per il testo da sostituire
    QPushButton *findButton;           //Bottone "Trova"
    QPushButton *replaceButton;        //Bottone "sostituisci"
    QPushButton *replaceAllButton;     //Bottone "sostituisci tutto"
    QCheckBox *caseSensitiveCheckBox;  //CheckBox per attivare/disattivare il case sensitive
    QCheckBox *wholeWordCheckBox;      //CheckBox per attivare/disattivare la ricerca di solo parole intere
};

#endif // FINDREPLACEDIALOG_H
