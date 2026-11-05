#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>

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
    QString filePath = QFileDialog::getOpenFileName(
        this,                                   // statt nullptr
        "Datei auswählen",
        QDir::homePath(),                       // "/home/user" gibt es auf dem Mac nicht
        "XML-Dateien (*.xml)"
        );
    if (filePath.isEmpty()) return;             // Abbrechen gedrückt

    tinyxml2::XMLError error = doc.LoadFile(filePath.toStdString().c_str());   // QString → C-String
    if (error != tinyxml2::XML_SUCCESS) {
        std::cout << "Fehler beim Laden der Datei: " << doc.ErrorName() << std::endl;
        return;                                 // sonst geht's mit leerem doc weiter
    }

    tinyxml2::XMLElement *root = doc.RootElement();
    if (!root) return;
    //std::cout << root->Name() << std::endl; //bei cout muss man endl machen sonst gehts nd was ein scheiß
    qDebug() << root->Name();

    ui->treeWidget->clear();
    fuellebaum(root, new QTreeWidgetItem(ui->treeWidget)); //in QTreeWidgetItem steht immer der parent drin
}

void MainWindow::fuellebaum(tinyxml2::XMLElement *root, QTreeWidgetItem *item) {

    item->setText(0,root->Name());
    elemente[item] = root;

    tinyxml2::XMLElement *kind = root->FirstChildElement();
    while (kind != nullptr) {
        fuellebaum(kind, new QTreeWidgetItem(item));
        qDebug() << kind->Name();
        kind = kind->NextSiblingElement();
    }
}


void MainWindow::on_treeWidget_itemSelectionChanged()
{
    QString ausgabe;

    QTreeWidgetItem *current = ui->treeWidget->currentItem();

    tinyxml2::XMLElement *element = elemente.value(current);
    const tinyxml2::XMLAttribute *a = element->FirstAttribute();
    while (a != nullptr) {
        ausgabe.append(QString::fromUtf8(a->Name()));
        ausgabe.append(QString::fromUtf8(" "));
        ausgabe.append(QString::fromUtf8(a->Value()));
        ausgabe.append(QString::fromUtf8("\n"));
        ui->textEdit->setText(ausgabe);
        a = a->Next();
    }

}

