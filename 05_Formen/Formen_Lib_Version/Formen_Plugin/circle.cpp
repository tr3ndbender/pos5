// Kein eigenes draw: wird von der Basisklasse geerbt (Vererbung).
// name/help sind protected -> duerfen hier ueberschrieben werden.
#include "circle.h"

// Kreis = Ellipse mit gleichen Radien
Circle::Circle(int x, int y, int radius) : Ellipse(x, y, radius, radius)
{
    name = "Circle";
    help = "Datenformat: x,y,radius";
}

Form *Circle::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 3)
    {
        return new Circle(d[0].toInt(), d[1].toInt(), d[2].toInt());
    }
    return nullptr;
}
