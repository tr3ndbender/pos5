#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "factory.h"
#include "register.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    formen = new QList<Form*>();
    factory = new Factory();

    // statt Plugins laden: Funktion aus der Library direkt aufrufen
    registerForm(factory);   // meldet je ein Prototyp-Objekt jeder Form bei der Factory an
    ui->form_select->insertItems(0, factory->getFormList());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Factory sucht den Prototyp per Name und ruft dessen parseForm(text) -> neues Objekt oder nullptr
    Form *f = factory->createForm(ui->form_select->currentText(), ui->data_input->text());
    if(f)
    {
        formen->append(f);
    }
    update();
}

void MainWindow::on_form_select_currentTextChanged(const QString &arg1)
{
    ui->help_text->setText(factory->getHelpText(arg1));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    QListIterator<Form*> iter(*formen);
    while( iter.hasNext() )
    {
        iter.next()->draw(painter);   // Polymorphie: ruft automatisch das draw der echten Klasse auf
    }
}
