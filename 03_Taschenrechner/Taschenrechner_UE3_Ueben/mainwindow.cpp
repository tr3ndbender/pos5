#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"

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

//Zahlen
void MainWindow::on_btn1_clicked()
{
    rechnung.append("1");
    ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn2_clicked()
{
    rechnung.append("2");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn3_clicked()
{
    rechnung.append("3");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn4_clicked()
{
    rechnung.append("4");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn5_clicked()
{
    rechnung.append("5");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn6_clicked()
{
    rechnung.append("6");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn7_clicked()
{
    rechnung.append("7");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn8_clicked()
{
    rechnung.append("8");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn9_clicked()
{
    rechnung.append("9");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btn0_clicked()
{
    rechnung.append("0");ui->rechnungLineEdit->setText(rechnung);
}

//Funktionszeichen

void MainWindow::on_btnPlus_clicked() {
    rechnung.append("+");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnMinus_clicked() {
    rechnung.append("-");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnMal_clicked() {
    rechnung.append("*");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnDividiert_clicked() {
    rechnung.append("/");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnKomma_clicked() {
    rechnung.append(".");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnKlammerAuf_clicked() {
    rechnung.append("(");ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnKlammerZu_clicked() {
    rechnung.append(")");ui->rechnungLineEdit->setText(rechnung);
}


void MainWindow::on_btnAuswerten_clicked()
{
    QString ergebnis =calc.calculate(rechnung);   // Methode auf dem OBJEKT calc (nicht CalcLib::calculate)

    if(ergebnis == "Fehler") {
        rechnung.clear();
        ui->rechnungLineEdit->setText("Fehler");
    } else {
        ui->rechnungLineEdit->setText(ergebnis);
        rechnung = ergebnis;   // Ergebnis wird neue Rechnung -> man kann damit weiterrechnen
    }





}

