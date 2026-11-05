#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tinyxml2_static.h"
#include <QTreeWidgetItem>



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
    void fuelleBaum(tinyxml2::XMLElement *root, QTreeWidgetItem *item);
    tinyxml2::XMLDocument doc;   // MEMBER: die XMLElement-Zeiger gehoeren dem doc. Lokal im Slot -> danach ungueltig

    QHash<QTreeWidgetItem*, tinyxml2::XMLElement*> elemente;
    //wir mappen die labels die wir jetzt haben zu den werten aus der XML
    //jetzt gerade ohne das: Bibliothek :
    // danach: Bibliothek : Name, Ort
    //Wir haben jetzt die Attribute dabei

};
#endif // MAINWINDOW_H
