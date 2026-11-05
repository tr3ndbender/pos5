#include "rechtwinkligesdreieck.h"

RechtwinkligesDreieck::RechtwinkligesDreieck(int x, int y, int breite, int hoehe) : Dreieck(x, y, breite, hoehe)
{
    name = "Rechtwinkliges Dreieck";
    help = "Datenformat: x,y,breite,hoehe";
}

void RechtwinkligesDreieck::draw(QPainter &painter)
{
    // rechter Winkel unten links
    QPolygon p;
    p << QPoint(x, y);
    p << QPoint(x, y + hoehe);
    p << QPoint(x + breite, y + hoehe);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *RechtwinkligesDreieck::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new RechtwinkligesDreieck(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
