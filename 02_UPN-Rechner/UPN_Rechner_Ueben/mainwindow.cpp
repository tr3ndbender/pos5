#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStack>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //3 + 4 * 5 => 345*+

    QString eingabe = ui->eingabeLe->displayText();
    QStringList tokens = eingabe.split(' ', Qt::SkipEmptyParts);   // "3 4 +" -> ["3","4","+"], doppelte Leerzeichen ignorieren

    QStack<double> numStack;
    bool ok = false;

    /*foreach(QString token, tokens) {

    }*/

    for (const QString &token : tokens) {
        bool ok = false;
        double zahl = token.toDouble(&ok);   // &ok = Adresse: toDouble schreibt true/false hinein

        if (ok) {
            numStack.push(zahl);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (numStack.size() < 2) {
                QMessageBox::warning(this, "Fehler", "Zu wenige Operanden");
                return;
            }
            // Reihenfolge wichtig: oberster Wert ist der RECHTE Operand (3 4 - = 3-4)
            double b = numStack.pop();   // zuerst b (oberster Wert)
            double a = numStack.pop();   // dann a

            if (token == "+")      numStack.push(a + b);
            else if (token == "-") numStack.push(a - b);
            else if (token == "*") numStack.push(a * b);
            else {
                if (b == 0) {
                    QMessageBox::warning(this, "Fehler", "Division durch 0");
                    return;
                }
                numStack.push(a / b);
            }
        }
        else {
            QMessageBox::warning(this, "Fehler", "Ungültiges Token: " + token);
            return;
        }
    }

    if (numStack.size() != 1) {
        QMessageBox::warning(this, "Fehler", "Ungültiger Ausdruck");
        return;
    }
    ui->ergebnisLbl->setText(QString::number(numStack.pop()));



}

