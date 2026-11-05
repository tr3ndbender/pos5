#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

#include "tinyxml2_statlib_ueben2.h"

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
    void on_pushButton_clicked();

    void on_treeWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    tinyxml2::XMLDocument doc;
    void fuellebaum(tinyxml2::XMLElement *root, QTreeWidgetItem *item);
    QHash<QTreeWidgetItem*, tinyxml2::XMLElement*> elemente;
};
#endif // MAINWINDOW_H
