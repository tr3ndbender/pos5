#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
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

void MainWindow::on_btnStart_clicked()
{
    currentPlayer = QRandomGenerator::global()->bounded(1,3);   // 1 oder 2 (obere Grenze exklusiv)

    // Zeiger-Array auf die 9 Buttons -> spaeter per buttons[z][s] ansprechbar.
    // Besser im Konstruktor (sonst Absturz, wenn vor "Start" geklickt wird).
    buttons[0][0] = ui ->btn00;
    buttons[0][1] = ui ->btn01;
    buttons[0][2] = ui ->btn02;
    buttons[1][0] = ui ->btn10;
    buttons[1][1] = ui ->btn11;
    buttons[1][2] = ui ->btn12;
    buttons[2][0] = ui ->btn20;
    buttons[2][1] = ui ->btn21;
    buttons[2][2] = ui ->btn22;

    for (int s = 0; s < 3; s++) {
        for (int z = 0; z < 3; z++) {
            feld[s][z] = 0;
            buttons[s][z]->setText("");

        }
    }
    gameRunning = true;

    if (ui -> cmbSpieler1->currentText() == "PC" && currentPlayer == 1) robotplays();
    if (ui -> cmbSpieler2->currentText() == "PC" && currentPlayer == 2) robotplays();
}

void MainWindow::spielzug(int z, int s) {

    if (feld[z][s] != 0 || gameRunning == false) return;

    if (pruefeGewinner() != 0) return;

           if (currentPlayer == 1) {
        buttons[z][s]->setText("X");
        feld[z][s] = currentPlayer;

        int ergebnis = pruefeGewinner();
        if (ergebnis != 0) {
            if (ergebnis == 3) {
                QMessageBox::information(this, "Spielende", "Unentschieden!");
            } else QMessageBox::information(this, "Spilenede", "Spieler " + QString::number(currentPlayer) + "gewinnt");
        }

        currentPlayer = 2;
    } else {
        buttons[z][s]->setText("O");
        feld[z][s] = currentPlayer;

        int ergebnis = pruefeGewinner();
        if (ergebnis != 0) {
            if (ergebnis == 3) {
                QMessageBox::information(this, "Spielende", "Unentschieden!");
            } else QMessageBox::information(this, "Spilenede", "Spieler " + QString::number(currentPlayer) + "gewinnt");
        }
        currentPlayer = 1;
    }
}

// Rueckgabe: 0 = Spiel laeuft, 1/2 = dieser Spieler hat gewonnen, 3 = Unentschieden
int MainWindow::pruefeGewinner()
    {
        // 3 Zeilen und 3 Spalten
        for (int i = 0; i < 3; i++) {
            if (feld[i][0] != 0 && feld[i][0] == feld[i][1] && feld[i][1] == feld[i][2])
                return feld[i][0];
            if (feld[0][i] != 0 && feld[0][i] == feld[1][i] && feld[1][i] == feld[2][i])
                return feld[0][i];
        }
        // 2 Diagonalen
        if (feld[1][1] != 0) {
            if (feld[0][0] == feld[1][1] && feld[1][1] == feld[2][2]) return feld[1][1];
            if (feld[0][2] == feld[1][1] && feld[1][1] == feld[2][0]) return feld[1][1];
        }
        // Noch ein freies Feld? Dann geht es weiter.
        for (int z = 0; z < 3; z++)
            for (int s = 0; s < 3; s++)
                if (feld[z][s] == 0) return 0;

        return 3;   // alles voll, kein Gewinner
    }

// ACHTUNG: rekursiv bis ein freies Feld getroffen wird.
// Ist KEIN Feld mehr frei, ruft sie sich endlos auf -> Absturz.
// Sauberer: alle freien Felder in eine QList<QPoint> sammeln und eines zufaellig waehlen (siehe Cheat-Sheet 03).
void MainWindow::robotplays() {
    int zeile = QRandomGenerator::global()->bounded(0,3);
    int spalte = QRandomGenerator::global()->bounded(0,3);

    if (feld[zeile][spalte] == 0) spielzug(zeile, spalte);
    else robotplays();
}


void MainWindow::on_btn00_clicked()
{
    spielzug(0,0);
    // Hinweis: PC zieht hier auch, wenn der Klick ungueltig war oder das Spiel vorbei ist.
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}

void MainWindow::on_btn01_clicked()
{
    spielzug(0,1);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn02_clicked()
{
    spielzug(0,2);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn10_clicked()
{
    spielzug(1,0);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn11_clicked()
{
    spielzug(1,1);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn12_clicked()
{
    spielzug(1,2);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn20_clicked()
{
    spielzug(2,0);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn21_clicked()
{
    spielzug(2,1);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}


void MainWindow::on_btn22_clicked()
{
    spielzug(2,2);
    if (ui -> cmbSpieler1->currentText() == "PC" || ui -> cmbSpieler2->currentText() == "PC") robotplays();
}

