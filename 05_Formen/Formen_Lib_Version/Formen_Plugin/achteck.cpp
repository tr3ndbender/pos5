#include "achteck.h"

// Achteck = regelmaessiges Polygon mit 8 Ecken (erbt draw, nur Konstruktor + parseForm noetig)
Achteck::Achteck(int x, int y, int radius) : RegelmaessigesPolygon(x, y, radius, 8)
{
    name = "Octagon";
    help = "Datenformat: x,y,radius";
}

Form *Achteck::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 3)
    {
        return new Achteck(d[0].toInt(), d[1].toInt(), d[2].toInt());
    }
    return nullptr;
}
