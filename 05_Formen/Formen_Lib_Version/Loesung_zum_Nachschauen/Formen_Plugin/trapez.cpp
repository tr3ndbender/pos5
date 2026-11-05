#include "trapez.h"
#include <iostream>

Trapez::Trapez(int x, int y, int breite_oben, int breite_unten, int hoehe)
    : Form("Trapez", "Datenformat: x,y,breite_oben,breite_unten, Höhe", x, y), breite_oben(breite_oben), breite_unten(breite_unten), hoehe(hoehe)
{

}

void Trapez::draw(QPainter &painter)
{
    QPolygon p;
    p << QPoint(x + (breite_unten - breite_oben) / 2 , y);
    p << QPoint(x + (breite_unten - breite_oben) / 2 + breite_oben , y);
    p << QPoint(x + breite_unten, y + hoehe);
    p << QPoint(x, y + hoehe);


    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *Trapez::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 5)
    {
        return new Trapez(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt(), d[4].toInt());
    }
    return nullptr;
}
