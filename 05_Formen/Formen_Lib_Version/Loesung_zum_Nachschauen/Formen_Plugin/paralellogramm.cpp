#include "paralellogramm.h"
#include <QtMath>
#include <iostream>

Paralellogramm::Paralellogramm(int x, int y, int breite, int laenge, int winkel)
    : Form("Paralellogramm", "Datenformat: x,y,breite,laenge,winkel", x, y), breite(breite), laenge(laenge), winkel(winkel)
{

}

void Paralellogramm::draw(QPainter &painter)
{
    // breite = schraege Seite, laenge = Grundseite
    double rad = qDegreesToRadians(winkel);
    double h = breite * sin(rad);
    double l1 = breite * cos(rad);

    QPolygon p;
    p << QPoint(x+l1, y);
    p << QPoint(x + l1 + laenge, y);
    p << QPoint(x + laenge, y + h);
    p << QPoint(x, y+h);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *Paralellogramm::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 5)
    {
        return new Paralellogramm(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt(), d[4].toInt());
    }
    return nullptr;
}
