#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calclib.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btn0_clicked();


    void on_btnPlus_clicked();
    void on_btnMinus_clicked();
    void on_btnMal_clicked();
    void on_btnDividiert_clicked();
    void on_btnKomma_clicked();
    void on_btnKlammerAuf_clicked();
    void on_btnKlammerZu_clicked();


    void on_btnAuswerten_clicked();



private:
    Ui::MainWindow *ui;
    QString rechnung = "";
    CalcLib calc;
};
#endif // MAINWINDOW_H
