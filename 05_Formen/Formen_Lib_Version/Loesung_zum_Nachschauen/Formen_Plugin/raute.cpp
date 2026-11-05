#include "raute.h"

// Raute = Parallelogramm mit gleich langen Seiten
Raute::Raute(int x, int y, int seite, int winkel) : Paralellogramm(x, y, seite, seite, winkel)
{
    name = "Raute";
    help = "Datenformat: x,y,seite,winkel";
}

Form *Raute::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new Raute(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
