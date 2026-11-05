#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>


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
    QString pfad = QFileDialog::getOpenFileName(
        this,                                  // Elternfenster
        "XML-Datei öffnen",                    // Titel des Dialogs
        QDir::homePath(),                      // Startordner
        "XML-Dateien (*.xml);;Alle Dateien (*)"   // Filter
        );

    // TinyXML will C-String (const char*), Qt liefert QString -> umwandeln.
    // Fehlt noch: if (pfad.isEmpty()) return;  und Pruefen, ob LoadFile == XML_SUCCESS
    doc.LoadFile(pfad.toStdString().c_str()); //file laden

    tinyxml2::XMLElement *wurzel = doc.RootElement(); //root Element bestimmen (Bibliothek)
    if (!wurzel) return;

    qDebug() << wurzel->Name();

    ui->treeWidget->clear();
    elemente.clear();


    fuelleBaum(wurzel, new QTreeWidgetItem(ui->treeWidget));
    //linkedlsit
    /*for (tinyxml2::XMLElement *kind = wurzel->FirstChildElement(); //erstes Child von Root
         kind != nullptr;
         kind = kind->NextSiblingElement())
    {
        QTreeWidgetItem *kindItem = new QTreeWidgetItem(wurzelItem);   // Eltern = wurzelItem
        kindItem->setText(0, kind->Name());
    }*/




}
                    //wurzel                //new QTreeWidgetItem(ui->treeWidget);
// Rekursion: jede Zeile im Baum = ein XML-Element. Fuer jedes Kind ruft sich die Funktion selbst auf.
// Endet von allein, wenn ein Element keine Kinder hat.
void MainWindow::fuelleBaum(tinyxml2::XMLElement *root, QTreeWidgetItem *item) {

    item->setText(0, root->Name());// das erste Element oben benennen sonst steht dort leer
    elemente[item] = root;

    tinyxml2::XMLElement *kind = root->FirstChildElement(); //erstes Element

    if (kind == nullptr || kind == NULL) return;

    //vordefinieren
    QTreeWidgetItem *kindItem;


    while ( true ) {
        if (kind == nullptr) break;

        //Einfügen und Text setzen
        kindItem = new QTreeWidgetItem(item);   // Eltern = wurzelItem
        kindItem->setText(0, kind->Name());
        elemente[kindItem] = kind; // wir mappen kindItem auf Kind.
        //Kinditem ist das item im TreeWidget und Kind ist das aus der XML

        //Rekursion
        fuelleBaum(kind, kindItem);

        //schleife weitergehen
        kind = kind->NextSiblingElement();

    }
}

void MainWindow::on_treeWidget_itemSelectionChanged()
{
    QString ausgabe = "";

    // QHash: Baum-Zeile -> XML-Element. .value() liefert nullptr, wenn nichts gefunden (auch bei currentItem()==nullptr)
    tinyxml2::XMLElement *element = elemente.value(ui->treeWidget->currentItem());
    if (!element) return;


    // Attribute sind eine verkettete Liste: a = a->Next() ist Pflicht, sonst Endlosschleife
    for (const tinyxml2::XMLAttribute *a = element->FirstAttribute(); a ; a= a->Next()) {
        //qDebug() << a->Name() << a->Value();

        ausgabe.append(a->Name());
        ausgabe.append(" ");
        ausgabe.append(a->Value());
        ausgabe.append("\n");
    }
    if (ausgabe.length() == 0) {
        ausgabe.append("Keine Attribute vorhanden");

    }
    // Aufgabe verlangt auch den Inhalt: const char *t = element->GetText(); if (t) ausgabe += t;
    ui->textEdit->setText(ausgabe);



}

