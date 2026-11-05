// Kein eigenes draw: wird von der Basisklasse geerbt (Vererbung).
// name/help sind protected -> duerfen hier ueberschrieben werden.
#include "sechseck.h"

// Sechseck = regelmaessiges Polygon mit 6 Ecken
Sechseck::Sechseck(int x, int y, int radius) : RegelmaessigesPolygon(x, y, radius, 6)
{
    name = "Sechseck";
    help = "Datenformat: x,y,radius";
}

Form *Sechseck::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 3)
    {
        return new Sechseck(d[0].toInt(), d[1].toInt(), d[2].toInt());
    }
    return nullptr;
}
