// Kein eigenes draw: wird von der Basisklasse geerbt (Vererbung).
// name/help sind protected -> duerfen hier ueberschrieben werden.
#include "square.h"

// Quadrat = Rechteck mit gleichen Seiten
Square::Square(int x, int y, int seite) : Rectangle(x, y, seite, seite)
{
    name = "Square";
    help = "Datenformat: x,y,seite";
}

Form *Square::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 3)
    {
        return new Square(d[0].toInt(), d[1].toInt(), d[2].toInt());
    }
    return nullptr;
}
