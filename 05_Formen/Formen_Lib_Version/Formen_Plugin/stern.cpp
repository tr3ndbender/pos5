#include "stern.h"
#include <QtMath>

// ecken (aus der Basisklasse) = Anzahl der Zacken
Stern::Stern(int x, int y, int radius, int zacken) : RegelmaessigesPolygon(x, y, radius, zacken)
{
    name = "Stern";
    help = "Datenformat: x,y,radius,zacken";
}

void Stern::draw(QPainter &painter)
{
    // 2 * ecken Punkte: gerade Nummern aussen (radius), ungerade innen (radius / 2)
    QPolygon p;
    int n = 2 * ecken;
    for (int i = 0; i < n; i++)
    {
        double r = (i % 2 == 0) ? radius : radius / 2.0;
        double rad = qDegreesToRadians(-90.0 + i * 360.0 / n);
        p << QPoint(x + qRound(r * qCos(rad)), y + qRound(r * qSin(rad)));
    }
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *Stern::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new Stern(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
