#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qpushbutton.h>

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
    void on_btnStart_clicked();

    void on_btn00_clicked();

    void on_btn01_clicked();

    void on_btn02_clicked();

    void on_btn10_clicked();

    void on_btn11_clicked();

    void on_btn12_clicked();

    void on_btn20_clicked();

    void on_btn21_clicked();

    void on_btn22_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *buttons[3][3];
    int feld[3][3];
    int currentPlayer;
    bool gameRunning;
    void spielzug(int z, int s);
    int pruefeGewinner();
    void robotplays();
};
#endif // MAINWINDOW_H
