#include "dreieck.h"
#include <iostream>

Dreieck::Dreieck(int x, int y, int breite, int hoehe) : Form("Dreieck", "Datenformat: x,y,breite,hoehe", x, y), breite(breite), hoehe(hoehe)
{

}

void Dreieck::draw(QPainter &painter)
{
    QPolygon p;
    p << QPoint(x + breite/2, y);
    p << QPoint(x, y+hoehe);

    p << QPoint(x + breite, y + hoehe);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *Dreieck::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new Dreieck(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
